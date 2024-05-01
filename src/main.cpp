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
	const uint32_t grid_size = 64;
	const uint32_t group_size = 128;
	constexpr float32_t radius = 0.1f;
	constexpr float32_t ifps = 1.0f / 400.0f;

    constexpr uint32_t size = 16;
	constexpr uint32_t num_particles = size * size * size;
    constexpr uint32_t kernel_buffers = 10;

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

    // Clear grid kernel
    Kernel clearGrid = device.createKernel().setUniforms(1).setStorages(2, false);
    if(!clearGrid.loadShaderGLSL("../src/clearGrid.comp", "GROUP_SIZE=%uu", group_size)) return 1;
    if(!clearGrid.create()) return 1;

    // Particle to grid kernel
    Kernel particleToGrid = device.createKernel().setUniforms(1).setStorages(kernel_buffers, false);
    if(!particleToGrid.loadShaderGLSL("../src/particleToGrid.comp", "GROUP_SIZE=%uu", group_size)) return 1;
    if(!particleToGrid.create()) return 1;

    // Update Grid Kernel
    Kernel updateGrid = device.createKernel().setUniforms(1).setStorages(2, false);
    if(!updateGrid.loadShaderGLSL("../src/updateGrid.comp", "GROUP_SIZE=%uu", group_size)) return 1;
    if(!updateGrid.create()) return 1;

    // Grid to particle kernel
    Kernel gridToParticle = device.createKernel().setUniforms(1).setStorages(kernel_buffers, false);
    if(!gridToParticle.loadShaderGLSL("../src/gridToParticle.comp", "GROUP_SIZE=%uu", group_size)) return 1;
    if(!gridToParticle.create()) return 1;

	// create pipeline
	Pipeline pipeline = device.createPipeline();
	pipeline.setUniformMask(0, Shader::MaskVertex);
	pipeline.setColorFormat(window.getColorFormat());
	pipeline.setDepthFormat(window.getDepthFormat());
	pipeline.setDepthFunc(Pipeline::DepthFuncLess);
	pipeline.addAttribute(Pipeline::AttributePosition, FormatRGBAf32, 0, 0, sizeof(Vector4f), 1);
    pipeline.addStorage(Shader::MaskFragment, false); // To pass velocity into fragment

    if(!pipeline.loadShaderGLSL(Shader::TypeVertex, "../src/main.vert")) return 1;
	if(!pipeline.loadShaderGLSL(Shader::TypeFragment, "../src/main.frag")) return 1;
	if(!pipeline.create()) return 1;
	
	// create particles
	Array<Vector4f> particle_positions(num_particles);
	Array<Vector4f> particle_velocities(num_particles);
    Array<Matrix4x4f> particle_momentum(num_particles);
    Array<Matrix4x4f> particle_deformation(num_particles);
    Array<float> particle_masses(num_particles);
    Array<float> particle_volumes(num_particles);

    Array<Vector4f> cell_velocities(grid_size * grid_size * grid_size);
    Array<float> cell_masses(grid_size * grid_size * grid_size);

	Matrix4x4f transform = Matrix4x4f::translate(0.0f, 0.0f, size * radius * 2.0f) * Matrix4x4f::rotateY(35.3f) * Matrix4x4f::rotateX(45.0f);
	for(uint32_t z = 0, index = 0; z < size; z++) {
		float32_t Z = (z - size * 0.5f) * radius * 2.0f;
		for(uint32_t y = 0; y < size; y++) {
			float32_t Y = (y - size * 0.5f) * radius * 2.0f;
			for(uint32_t x = 0; x < size; x++, index++) {
				float32_t X = (x - size * 0.5f) * radius * 2.0f;
				if(index < num_particles) {
                    // set initial particle mass, velocity, pos
					particle_positions[index] = transform * Vector4f(X, Y, Z, 1.0f);
                    particle_velocities[index] = Vector4f(0.0f, 0.0f, 0.0f, 0.0f);
                    particle_masses[index] = 1.0f;
                    particle_volumes[index] = 0.0f;
                    particle_momentum[index] = Matrix4x4f (0.0f); // fully 0 matrix
                    particle_deformation[index] = Matrix4x4f(1.0f, 0.0f, 0.0f, 0.0f,
                                                             0.0f, 1.0f, 0.0f, 0.0f,
                                                             0.0f, 0.0f, 1.0f, 0.0f,
                                                             0.0f, 0.0f, 0.0f, 1.0f); // Identity matrix
				}
			}
		}
	}

    // Initialize cell masses & velocities to 0
    // Will use same data later on to reset the buffers every frame
    for (uint32_t i = 0; i <grid_size * grid_size * grid_size; i++) {
        cell_masses[i] = 0;
        cell_velocities[i] = Vector4f(0.0f);
    }
	
	// create particle buffers
	Buffer particle_position_buffers[2];
	Buffer particle_velocity_buffers[2];
    Buffer particle_mass_buffer;
    Buffer particle_volume_buffer;
    Buffer particle_momentum_buffer;
    Buffer particle_deformation_buffer;

	particle_position_buffers[0] = device.createBuffer(Buffer::FlagVertex | Buffer::FlagStorage, particle_positions.get(), particle_positions.bytes());
    particle_position_buffers[1] = device.createBuffer(Buffer::FlagVertex | Buffer::FlagStorage, particle_positions.bytes());
    particle_velocity_buffers[0] = device.createBuffer(Buffer::FlagStorage, particle_velocities.get(), particle_velocities.bytes());
    particle_velocity_buffers[1] = device.createBuffer(Buffer::FlagStorage, particle_velocities.bytes());
    particle_mass_buffer = device.createBuffer(Buffer::FlagStorage, particle_masses.get(), particle_masses.bytes());
    particle_volume_buffer = device.createBuffer(Buffer::FlagStorage, particle_volumes.get(), particle_volumes.bytes());
    particle_momentum_buffer = device.createBuffer(Buffer::FlagStorage, particle_momentum.get(), particle_momentum.bytes());
    particle_deformation_buffer = device.createBuffer(Buffer::FlagStorage, particle_deformation.get(), particle_deformation.bytes());

    if(!particle_position_buffers[0] || !particle_position_buffers[1]) return 1;
    if(!particle_velocity_buffers[0] || !particle_velocity_buffers[1]) return 1;
    if (!particle_momentum_buffer || !particle_deformation_buffer) return 1;
    if (!particle_mass_buffer || !particle_volume_buffer) return 1;

    // create cell buffers
    Buffer cell_velocity_buffer = device.createBuffer(Buffer::FlagStorage, cell_velocities.get(), cell_velocities.bytes());
    Buffer cell_mass_buffer = device.createBuffer(Buffer::FlagStorage,  cell_masses.get(), cell_masses.bytes());

    if (!cell_velocity_buffer || !cell_mass_buffer) return 1;
	
	// create target
	Target target = device.createTarget(window);
    
    // create base persepctive, using for rotation
    Matrix4x4f baseView = Matrix4x4f::lookAt(Vector3f(16.0f, 0.0f, 8.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 0.0f, 1.0f));
	
	// main loop
	DECLARE_GLOBAL
	window.run([&]() -> bool {
		DECLARE_COMMON
		
		Window::update();
		
		if(!window.render()) return false;
		
		// window title
		if(fps > 0.0f) window.setTitle(String::format("%s %.1f FPS", title.get(), fps));
		
		// reset simulation
		if(window.getKeyboardKey(' ')) {
			device.setBuffer(particle_position_buffers[0], particle_positions.get());
			device.setBuffer(particle_velocity_buffers[0], particle_velocities.get());
            device.setBuffer(particle_deformation_buffer, particle_deformation.get());
            device.setBuffer(particle_momentum_buffer, particle_momentum.get());
            device.setBuffer(particle_mass_buffer, particle_masses.get());
            device.setBuffer(particle_volume_buffer, particle_volumes.get());

            device.setBuffer(cell_velocity_buffer, cell_velocities.get());
            device.setBuffer(cell_mass_buffer, cell_masses.get());

			frame_counter = 0;
		}
		if(window.getKeyboardKey('s')) {
			simulate = false;
		}

        // create command list
        Compute compute = device.createCompute();

        // swap buffers
        if(simulate) {
            swap(particle_position_buffers[0], particle_position_buffers[1]);
            swap(particle_velocity_buffers[0], particle_velocity_buffers[1]);
        }

        // compute parameters
        ComputeParameters compute_parameters;
        compute_parameters.size = num_particles;
        compute_parameters.ifps = ifps;
        compute_parameters.radius = radius;
        compute_parameters.grid_size = grid_size;
        compute_parameters.grid_scale = 0.25f / radius;
        compute_parameters.ranges_offset = TS_ALIGN4(num_particles) * 2;

        // Zero-Out cell mass/velocity
        {
            compute.setKernel(clearGrid);
            compute.setUniform(0, compute_parameters);
            compute.setStorageBuffers(0, {
                    cell_velocity_buffer, cell_mass_buffer,
            });
            compute.dispatch(grid_size);

            compute.barrier({cell_velocity_buffer, cell_mass_buffer});
        }

        // Particle to Grid
        {
            compute.setKernel(particleToGrid);
            compute.setUniform(0, compute_parameters);
            compute.setStorageBuffers(0, {
                    particle_position_buffers[1], particle_velocity_buffers[1],
                    particle_momentum_buffer, particle_deformation_buffer,
                    particle_mass_buffer, particle_volume_buffer,
                    cell_velocity_buffer, cell_mass_buffer,
            });
            compute.dispatch(num_particles);

            compute.barrier({particle_position_buffers[1], particle_velocity_buffers[1],
                             particle_position_buffers[0], particle_velocity_buffers[0],
                             particle_momentum_buffer, particle_deformation_buffer,
                             particle_mass_buffer, particle_volume_buffer,
                             cell_velocity_buffer, cell_mass_buffer});
        }

        // Calculate Grid Velocities
        {
            compute.setKernel(updateGrid);
            compute.setUniform(0, compute_parameters);
            compute.setStorageBuffers(0, {
                    cell_velocity_buffer, cell_mass_buffer,
            });
            compute.dispatch(grid_size*grid_size*grid_size);
            compute.barrier({cell_velocity_buffer, cell_mass_buffer,});
        }

        // Grid to Particle
        {
            compute.setKernel(gridToParticle);
            compute.setUniform(0, compute_parameters);
            compute.setStorageBuffers(0, {
                    particle_position_buffers[1], particle_velocity_buffers[1],
                    particle_position_buffers[0], particle_velocity_buffers[0],
                    particle_momentum_buffer, particle_deformation_buffer,
                    particle_mass_buffer, particle_volume_buffer,
                    cell_velocity_buffer, cell_mass_buffer,
            });
            compute.dispatch(num_particles);

            compute.barrier({particle_position_buffers[1], particle_velocity_buffers[1],
                             particle_position_buffers[0], particle_velocity_buffers[0],
                             particle_momentum_buffer, particle_deformation_buffer,
                             particle_mass_buffer, particle_volume_buffer,
                             cell_velocity_buffer, cell_mass_buffer});
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
//			common_parameters.modelview = Matrix4x4f::lookAt(Vector3f(16.0f, 0.0f, 8.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 0.0f, 1.0f));
            common_parameters.modelview = baseView;
			if(target.isFlipped()) common_parameters.projection = Matrix4x4f::scale(1.0f, -1.0f, 1.0f) * common_parameters.projection;
			common_parameters.radius = radius;
            
            // move around scene (1 and 2 = x, 3 and 4 = y, 5 and 6 = z)
            constexpr float sens = 0.05f;
            if(window.getKeyboardKey('1')) {
                baseView = baseView * Matrix4x4f::rotateX(-sens);
            }
            if(window.getKeyboardKey('2')) {
                baseView = baseView * Matrix4x4f::rotateX(sens);
            }
            if(window.getKeyboardKey('3')) {
                baseView = baseView * Matrix4x4f::rotateY(-sens);
            }
            if(window.getKeyboardKey('4')) {
                baseView = baseView * Matrix4x4f::rotateY(sens);
            }
            if(window.getKeyboardKey('5')) {
                baseView = baseView * Matrix4x4f::rotateZ(-sens);
            }
            if(window.getKeyboardKey('6')) {
                baseView = baseView * Matrix4x4f::rotateZ(sens);
            }

			// draw particles
			command.setPipeline(pipeline);
			command.setUniform(0, common_parameters);
			command.setIndices({ 0, 1, 2, 2, 3, 0 });
			command.setVertexBuffer(0, particle_position_buffers[0]);
            command.setStorageBuffer(0, particle_velocity_buffers[0]);
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
