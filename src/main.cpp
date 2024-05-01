#include <common.h>
#include <math/TellusimMath.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimPipeline.h>
#include <platform/TellusimKernel.h>
#include <platform/TellusimCommand.h>
#include <platform/TellusimCompute.h>
#include <parallel/TellusimPrefixScan.h>
#include <parallel/TellusimRadixSort.h>
#include <parallel/TellusimSpatialGrid.h>
#include <iostream>

#include <io/LasReader.hpp>
#include <pdal/Writer.hpp>
#include <pdal/Streamable.hpp>
#include <pdal/PointView.hpp>
#include <pdal/util/ProgramArgs.hpp>

using namespace Tellusim;

int32_t main(int32_t argc, char **argv) {
	
	DECLARE_WINDOW
	
	// create window
	String title = String::format("%s Tellusim::SpatialGrid", window.getPlatformName());
	if(!window.create(title) || !window.setHidden(false)) return 1;
	
	// structures
	struct ComputeParameters {
		uint32_t size;
		float32_t ifps;
		float32_t radius;
		uint32_t grid_size;
		float32_t grid_scale;
		uint32_t ranges_offset;
	};
	
	struct CommonParameters {
		Matrix4x4f projection;
		Matrix4x4f modelview;
		float32_t radius;
	};

	// spatial parameters
	const uint32_t grid_size = 32;
	const uint32_t group_size = 128;
	constexpr float32_t radius = 0.08f;
    float32_t ifps = 1.0f / 50.0f;

    //read .las file
    pdal::Options options;
    pdal::LasReader reader;
    //pick a file to read
    options.add("filename", "../src/models/cs184_60k.las");
    reader.setOptions(options);
    pdal::PointTable table;
    reader.prepare(table);
    pdal::PointViewSet pointViewSet = reader.execute(table);
    pdal::PointViewPtr view = *pointViewSet.begin();
    uint32_t num_particles = view->size();

	// create device
	Device device(window);
	if(!device) return 1;
	
	// check compute shader support
	if(!device.hasShader(Shader::TypeCompute)) {
		TS_LOG(Error, "compute shader is not supported\n");
		return 0;
	}
	
	// shader cache
	Shader::setCache("main.cache");
	
	// create kernel
	Kernel kernel = device.createKernel().setUniforms(1).setStorages(9, false);
	if(!kernel.loadShaderGLSL("../src/main.comp", "COMPUTE_SHADER=1; GROUP_SIZE=%uu", group_size)) return 1;
	if(!kernel.create()) return 1;

    // Create pressure/density kernel
    Kernel pressureDensity = device.createKernel().setUniforms(1).setStorages(6, false);
    if(!pressureDensity.loadShaderGLSL("../src/pressureDensity.comp", "COMPUTE_SHADER=1; GROUP_SIZE=%uu", group_size)) return 1;
    if(!pressureDensity.create()) return 1;

	// create pipeline
	Pipeline pipeline = device.createPipeline();
	pipeline.setUniformMask(0, Shader::MaskVertex);
	pipeline.setColorFormat(window.getColorFormat());
	pipeline.setDepthFormat(window.getDepthFormat());
	pipeline.setDepthFunc(Pipeline::DepthFuncLess);
	pipeline.addAttribute(Pipeline::AttributePosition, FormatRGBAf32, 0, 0, sizeof(Vector4f), 1);
    pipeline.addStorage(Shader::MaskFragment, false); // Pass velocity into fragment

    if(!pipeline.loadShaderGLSL(Shader::TypeVertex, "../src/main.vert", "VERTEX_SHADER=1")) return 1;
	if(!pipeline.loadShaderGLSL(Shader::TypeFragment, "../src/main.frag", "FRAGMENT_SHADER=1")) return 1;
	if(!pipeline.create()) return 1;
	
	// create particles
	Array<Vector4f> positions(num_particles);
	Array<Vector4f> velocities(num_particles);
    Array<float> densities(num_particles);
    Array<float> pressures(num_particles);
    Array<float> masses(num_particles);
    Array<Vector4f> interactionForces(1);

	Matrix4x4f transform = Matrix4x4f::translate(0.0f, -3.0f, 3.2f)  * Matrix4x4f::scale(1.8f) * Matrix4x4f::rotateZ(90.0f)  *Matrix4x4f::rotateX(80.0f) ;

    for (pdal::PointId idx = 0; idx < num_particles; ++idx) {
        positions[idx] = transform * Vector4f(view->getFieldAs<double>(pdal::Dimension::Id::X, idx),
                                                       view->getFieldAs<double>(pdal::Dimension::Id::Y, idx),
                                                       view->getFieldAs<double>(pdal::Dimension::Id::Z, idx),
                                                       1.0f);
        velocities[idx] = Vector4f(0.0f);
        pressures[idx] = 0.0f;
        densities[idx] = 0.0f;
        masses[idx] = 0.7f;
    }
    interactionForces[0] = Vector4f(0.0f);

    // create buffers
	Buffer position_buffers[2];
	Buffer velocity_buffers[2];

    Buffer density_buffer;
    Buffer pressure_buffer;
    Buffer mass_buffer;
    Buffer interactionBuffer;
	position_buffers[0] = device.createBuffer(Buffer::FlagVertex | Buffer::FlagStorage, positions.get(), positions.bytes());
	position_buffers[1] = device.createBuffer(Buffer::FlagVertex | Buffer::FlagStorage, positions.bytes());
	velocity_buffers[0] = device.createBuffer(Buffer::FlagStorage, velocities.get(), velocities.bytes());
	velocity_buffers[1] = device.createBuffer(Buffer::FlagStorage, velocities.bytes());

    density_buffer = device.createBuffer(Buffer::FlagStorage, densities.get(), densities.bytes());
    pressure_buffer = device.createBuffer(Buffer::FlagStorage, pressures.get(), pressures.bytes());

    mass_buffer = device.createBuffer(Buffer::FlagStorage, masses.get(), masses.bytes());
    interactionBuffer = device.createBuffer(Buffer::FlagStorage, interactionForces.get(), interactionForces.bytes());
    if(!position_buffers[0] || !position_buffers[1]) return 1;
	if(!velocity_buffers[0] || !velocity_buffers[1]) return 1;
	if (!mass_buffer) return 1;

	// create spatial grid
	RadixSort radix_sort;
	PrefixScan prefix_scan;
	SpatialGrid spatial_grid;
	if(!radix_sort.create(device, RadixSort::ModeSingle, prefix_scan, num_particles, group_size)) return 1;
	if(!spatial_grid.create(device, radix_sort, group_size)) return 1;
	
	// create spatial buffer
	uint32_t hashes_size = num_particles * 2;
	uint32_t ranges_size = group_size * group_size * group_size * 2;
	auto spatial_buffer = device.createBuffer(Buffer::FlagStorage, sizeof(uint32_t) * (hashes_size + ranges_size));
	if(!spatial_buffer || !device.clearBuffer(spatial_buffer)) return 1;
	
	// create target
	Target target = device.createTarget(window);
    Matrix4x4f baseView = Matrix4x4f::lookAt(Vector3f(16.0f, 0.0f, 8.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 0.0f, 1.0f));

    bool paused = false;
    // main loop
	DECLARE_GLOBAL
	window.run([&]() -> bool {
		DECLARE_COMMON
		
		Window::update();
		
		if(!window.render()) return false;
		
		// window title
		if(fps > 0.0f) { window.setTitle(String::format("%s, %u particles, %.1f FPS, %.3f dt", title.get(), num_particles, fps, ifps)); }

		// reset simulation
		if(window.getKeyboardKey('r')) {
			device.setBuffer(position_buffers[0], positions.get());
			device.setBuffer(velocity_buffers[0], velocities.get());
            device.setBuffer(pressure_buffer, pressures.get());
            device.setBuffer(density_buffer, densities.get());
			frame_counter = 0;
		}
        // move around scene (1 and 2 = x, 3 and 4 = y, 5 and 6 = z)
        float sens = 10.0f * ifps;
        float moveSpeed = 1.5f * ifps;

        if (window.getKeyboardKey('1')) baseView *= Matrix4x4f::rotateX(-sens);
        if (window.getKeyboardKey('2')) baseView *= Matrix4x4f::rotateX(sens);
        if (window.getKeyboardKey('3')) baseView *= Matrix4x4f::rotateY(-sens);
        if (window.getKeyboardKey('4')) baseView *= Matrix4x4f::rotateY(sens);
        if (window.getKeyboardKey('5')) baseView *=Matrix4x4f::rotateZ(-sens);
        if (window.getKeyboardKey('6')) baseView *= Matrix4x4f::rotateZ(sens);
        if (window.getKeyboardKey('w')) baseView *= Matrix4x4f::translate(moveSpeed, 0.f, 0.0f);
        if (window.getKeyboardKey('s')) baseView *= Matrix4x4f::translate(-moveSpeed, 0.0f, 0.0f);
        if (window.getKeyboardKey('a')) baseView *= Matrix4x4f::translate(0.0f, moveSpeed, 0.0f);
        if (window.getKeyboardKey('d')) baseView *= Matrix4x4f::translate(0.0f, -moveSpeed, 0.0f);
        if (window.getKeyboardKey('q')) baseView *= Matrix4x4f::translate(0.0f, 0.0f, moveSpeed);
        if (window.getKeyboardKey('e')) baseView *= Matrix4x4f::translate(0.0f, 0.0f, -moveSpeed);
        if (window.getKeyboardKey('p')) paused = !paused;
        if (window.getKeyboardKey('.')) {
            ifps += 0.0005;
            ifps = min (0.05f, ifps);
        }
        if (window.getKeyboardKey(',')) {
            ifps -= 0.0005;
            ifps = max(0.0005f, ifps);
        }

        // create command list
        Compute compute = device.createCompute();

        // swap buffers
        if(simulate && !paused) {
            swap(position_buffers[0], position_buffers[1]);
            swap(velocity_buffers[0], velocity_buffers[1]);
        }

        // compute parameters
        ComputeParameters compute_parameters;
        compute_parameters.size = num_particles;
        compute_parameters.ifps = ifps;
        compute_parameters.radius = radius;
        compute_parameters.grid_size = grid_size;
        compute_parameters.grid_scale = 0.25f / radius;
        compute_parameters.ranges_offset = TS_ALIGN4(num_particles) * 2;

        {
            compute.setKernel(pressureDensity);
            compute.setUniform(0, compute_parameters);
            compute.setStorageBuffers(0, {
                    spatial_buffer,
                    position_buffers[1], velocity_buffers[1],
                    pressure_buffer, density_buffer,
                    mass_buffer
            });
            compute.dispatch(num_particles);
            compute.barrier({spatial_buffer,
                            position_buffers[1], velocity_buffers[1],
                            pressure_buffer, density_buffer, mass_buffer});
        }

        {
			// set simulation kernel
			compute.setKernel(kernel);
			compute.setUniform(0, compute_parameters);
			compute.setStorageBuffers(0, {
                spatial_buffer,
				position_buffers[0], velocity_buffers[0],
				position_buffers[1], velocity_buffers[1],
                pressure_buffer, density_buffer,
                mass_buffer, interactionBuffer
			});
			compute.dispatch(num_particles);
			compute.barrier(spatial_buffer);

			// dispatch spatial grid
			spatial_grid.dispatch(compute, spatial_buffer, 0, num_particles, 20);
			compute.barrier({spatial_buffer,
                             position_buffers[0], velocity_buffers[0],
                             position_buffers[1], velocity_buffers[1],
                             pressure_buffer, density_buffer,
                             mass_buffer, interactionBuffer});
		}
		
		// window target
		target.setClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		target.begin();
		{
			// create command list
			Command command = device.createCommand(target);
			
			// common parameters
			CommonParameters common_parameters;
			common_parameters.projection = Matrix4x4f::perspective(60.0f, (float32_t)window.getWidth() / window.getHeight(), 0.1f, 1000.0f);
			common_parameters.modelview = baseView;
			if(target.isFlipped()) common_parameters.projection = Matrix4x4f::scale(1.0f, -1.0f, 1.0f) * common_parameters.projection;
			common_parameters.radius = radius;

            float mouseX = window.getMouseX()/100.0f - 5.0f;
            float mouseY = window.getMouseY()/100.0f - 5.0f;

            if (mouseX > -5.0f && mouseX < 10.0f && mouseY > -6.0f && mouseY < 6.0f)
                interactionForces[0] = Vector4f(-mouseY, mouseX, 0.0f, 1.0f);
            else
                interactionForces[0] = Vector4f(0.0f, 0.0f, 0.0f, 0.0f);
            device.setBuffer(interactionBuffer, interactionForces.get());

			// draw particles
			command.setPipeline(pipeline);
			command.setUniform(0, common_parameters);
			command.setIndices({ 0, 1, 2, 2, 3, 0 });
			command.setVertexBuffer(0, position_buffers[0]);
            command.setStorageBuffer(0, velocity_buffers[0]);
			command.drawElementsInstanced(6, 0, num_particles);
		}
		target.end();
		
		if(!window.present()) return false;
		
		if(!device.check()) return false;
		
		return true;
	});
	
	// finish context
	window.finish();
	
	return 0;
}
