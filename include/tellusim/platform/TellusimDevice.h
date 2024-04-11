// Copyright (C) 2018-2024, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_PLATFORM_DEVICE_H__
#define __TELLUSIM_PLATFORM_DEVICE_H__

#include <format/TellusimImage.h>
#include <platform/TellusimQuery.h>
#include <platform/TellusimFence.h>
#include <platform/TellusimBuffer.h>
#include <platform/TellusimShader.h>
#include <platform/TellusimSampler.h>
#include <platform/TellusimTexture.h>
#include <platform/TellusimTracing.h>
#include <platform/TellusimTarget.h>
#include <platform/TellusimPlatform.h>

/*
 */
namespace Tellusim {
	
	/* Prototypes
	 */
	class Kernel;
	class Pipeline;
	class Traversal;
	class Compute;
	class Command;
	class Context;
	class Surface;
	class Window;
	
	/**
	 * Device class
	 */
	class TS_API Device {
			
			TS_DECLARE_PTR(Device, 3)
			
		public:
			
			Device();
			explicit Device(Context &context);
			explicit Device(Surface &surface);
			explicit Device(Window &window);
			virtual ~Device();
			
			/// device platform
			Platform getPlatform() const;
			
			TS_INLINE const char *getPlatformName() const { return Tellusim::getPlatformName(getPlatform()); }
			
			/// device index
			uint32_t getIndex() const;
			
			/// device info
			String getName() const;
			String getVendor() const;
			String getVersion() const;
			
			/// device features
			struct Features {
				
				bool threadAccess;				// thread access support
				
				bool sparseBuffer;				// sparse buffers support
				
				bool sparseTexture;				// sparse textures support
				bool sparseArrayTexture;		// sparse array textures support
				bool cubeArrayTexture;			// cube array textures support
				bool textureTable;				// texture tables support
				
				bool baseInstanceIndex;			// base instance index support
				bool drawIndirectIndex;			// draw indirect index support
				bool drawIndirectCount;			// draw indirect count support
				bool taskIndirectCount;			// task indirect count support
				
				bool vertexStorage;				// vertex shader storage support
				bool vertexIndexLayer;			// vertex shader index layer support
				bool geometryPassthrough;		// geometry shader passthrough support
				bool fragmentBarycentric;		// fragment shader barycentric support
				bool fragmentStencilExport;		// fragment shader stencil export support
				
				bool dualSourceBlending;		// dual source blending support
				bool depthRangeOneToOne;		// depth buffer range one to one
				
				bool conservativeRaster;		// conservative raster support
				bool viewportSwizzle;			// viewport swizzle support
				
				bool conditionalRendering;		// conditional rendering support
				
				bool rayTracing;				// ray tracing shaders support
				bool computeTracing;			// compute shader tracing support
				bool fragmentTracing;			// fragment shader tracing support
				bool indirectTracing;			// build indirect tracing support
				uint32_t recursionDepth;		// ray tracing recursion depth
				
				bool subgroupVote;				// shader subgroup vote support
				bool subgroupMath;				// shader subgroup math support
				bool subgroupShuffle;			// shader subgroup shuffle support
				uint32_t subgroupSize;			// shader subgroup operations size
				
				bool shaderu8;					// shader 8-bit integer support
				bool shaderf16;					// shader 16-bit floating-point support
				bool shaderu16;					// shader 16-bit integer support
				bool shaderf64;					// shader 64-bit floating-point support
				bool shaderu64;					// shader 64-bit integer support
				
				bool atomicGroupf32;			// atomic group 32-bit floating-point support
				bool atomicGroupu64;			// atomic group 64-bit integer support
				bool atomicBufferf32;			// atomic buffer 32-bit floating-point support
				bool atomicBufferu64;			// atomic buffer 64-bit integer support
				bool atomicTexturef32;			// atomic texture 32-bit floating-point support
				bool atomicTextureu32;			// atomic texture 32-bit integer support
				bool atomicTextureu64;			// atomic texture 64-bit integer support
				
				bool matrix16f16;				// matrix 16x16x16 16-bit floating point support
				bool matrix16x8x8f16;			// matrix 16x8x8 16-bit floating point support
				bool matrix16x8x16f16;			// matrix 16x8x16 16-bit floating point support
				bool matrix16f16f32;			// matrix 16x16x16 16/32-bit floating point support
				bool matrix16x8x8f16f32;		// matrix 16x8x8 16/32-bit floating point support
				bool matrix16x8x16f16f32;		// matrix 16x8x16 16/32-bit floating point support
				
				uint32_t uniformAlignment;		// uniform buffer alignment in bytes
				uint32_t storageAlignment;		// storage buffer alignment in bytes
				
				uint32_t maxTextureSamples;		// maximum texture samples
				uint32_t maxTexture2DSize;		// maximum 2D texture size
				uint32_t maxTexture3DSize;		// maximum 3D texture size
				uint32_t maxTextureLayers;		// maximum texture layers
				
				uint32_t maxGroupSizeX;			// maximum compute shader group size X
				uint32_t maxGroupSizeY;			// maximum compute shader group size Y
				uint32_t maxGroupSizeZ;			// maximum compute shader group size Z
				uint32_t maxGroupCountX;		// maximum compute shader group count X
				uint32_t maxGroupCountY;		// maximum compute shader group count Y
				uint32_t maxGroupCountZ;		// maximum compute shader group count Z
				
				uint32_t maxTaskCount;			// maximum task shader count
				uint32_t maxTaskMemory;			// maximum task shader memory
				uint32_t maxTaskMeshes;			// maximum task shader meshes
				
				uint32_t maxMeshMemory;			// maximum mesh shader memory
				uint32_t maxMeshVertices;		// maximum mesh shader vertices
				uint32_t maxMeshPrimitives;		// maximum mesh shader primitives
				
				uint32_t maxViewportCount;		// maximum viewport count
				uint32_t maxClipCullCount;		// maximum clip cull count
				
				uint64_t maxUniformSize;		// maximum uniform size in bytes
				uint64_t maxStorageSize;		// maximum storage size in bytes
				
				uint32_t groupMemory;			// shared group memory in bytes
				uint64_t videoMemory;			// dedicated video memory in bytes
				
				uint32_t vendorID;				// vendor identifier
				uint32_t deviceID;				// device identifier
				uint32_t pciBusID;				// pci bus identifier
				uint32_t pciDomainID;			// pci domain identifier
				uint32_t pciDeviceID;			// pci device identifier
			};
			
			const Features &getFeatures() const;
			
			/// device types
			bool hasQuery(Query::Type type) const;
			bool hasShader(Shader::Type type) const;
			
			/// device formats
			bool hasTarget(Format format) const;
			bool hasTexture(Format format) const;
			bool hasSurface(Format format) const;
			
			/// create device
			Device createDevice(uint32_t index, uint32_t frames = 3) const;
			Device createCommandDevice(uint32_t frames = 3) const;
			Device createComputeDevice(uint32_t frames = 3) const;
			Device createCopyDevice(uint32_t frames = 3) const;
			
			/// create query
			Query createQuery() const;
			Query createQuery(Query::Type type) const;
			
			/// create fence
			Fence createFence() const;
			Fence createFence(Fence &shared) const;
			Fence createFence(Fence::Flags flags) const;
			
			/// create buffer
			Buffer createBuffer() const;
			Buffer createBuffer(Buffer &shared) const;
			Buffer createBuffer(Buffer::Flags flags, size_t size, Format format = FormatUnknown) const;
			Buffer createBuffer(Buffer::Flags flags, const void *src, size_t size, Format format = FormatUnknown) const;
			
			/// create sampler
			Sampler createSampler() const;
			Sampler createSampler(const Sampler &sampler) const;
			Sampler createSampler(Sampler::Filter filter, Sampler::WrapMode mode = Sampler::WrapModeRepeat, uint32_t anisotropy = Sampler::MaxAnisotropy) const;
			
			/// create texture
			Texture createTexture() const;
			Texture createTexture(Texture &shared) const;
			Texture createTexture(Texture::Type type, Format format, const Size &size, uint32_t layers, Texture::Flags flags = Texture::DefaultFlags) const;
			Texture createTexture(Texture::Type type, Format format, const Size &size, Texture::Flags flags = Texture::DefaultFlags) const;
			Texture createTexture(const Image &image, Texture::Flags flags = Texture::DefaultFlags, Async *async = nullptr) const;
			
			Texture createTexture2D(Format format, uint32_t size, Texture::Flags flags = Texture::DefaultFlags) const;
			Texture createTexture3D(Format format, uint32_t size, Texture::Flags flags = Texture::DefaultFlags) const;
			Texture createTextureCube(Format format, uint32_t size, Texture::Flags flags = Texture::DefaultFlags) const;
			
			Texture createTexture2D(Format format, uint32_t width, uint32_t height, Texture::Flags flags = Texture::DefaultFlags) const;
			Texture createTexture3D(Format format, uint32_t width, uint32_t height, uint32_t depth, Texture::Flags flags = Texture::DefaultFlags) const;
			
			Texture createTexture2D(Format format, uint32_t width, uint32_t height, uint32_t layers, Texture::Flags flags = Texture::DefaultFlags) const;
			Texture createTextureCube(Format format, uint32_t size, uint32_t layers, Texture::Flags flags = Texture::DefaultFlags) const;
			
			Texture loadTexture(const char *name, Texture::Flags flags = Texture::DefaultFlags, Image::Flags image_flags = Image::FlagNone, uint32_t offset = 0, Async *async = nullptr) const;
			Texture loadTexture(const String &name, Texture::Flags flags = Texture::DefaultFlags, Image::Flags image_flags = Image::FlagNone, uint32_t offset = 0, Async *async = nullptr) const;
			Texture loadTexture(Stream &stream, Texture::Flags flags = Texture::DefaultFlags, Image::Flags image_flags = Image::FlagNone, uint32_t offset = 0, Async *async = nullptr) const;
			
			/// create tracing
			Tracing createTracing() const;
			Tracing createTracing(const Tracing &tracing) const;
			Tracing createTracing(uint32_t num_instances, Buffer instance_buffer = Buffer::null, size_t instance_offset = 0, Tracing::Flags flags = Tracing::DefaultFlags) const;
			Tracing createTracing(uint32_t num_vertices, Format vertex_format, size_t vertex_stride, uint32_t num_indices, Format index_format, Tracing::Flags flags = Tracing::DefaultFlags) const;
			Tracing createTracing(uint32_t num_bounds, size_t bound_stride, Buffer bound_buffer = Buffer::null, size_t bound_offset = 0, Tracing::Flags flags = Tracing::DefaultFlags) const;
			
			/// create table
			TextureTable createTable() const;
			TextureTable createTable(uint32_t size) const;
			
			/// create shader
			Shader createShader() const;
			
			Shader loadShader(Shader::Type type, const char *name, const char *format, ...) const TS_PRINTF(4, 5);
			Shader loadShaderGLSL(Shader::Type type, const char *name, const char *format, ...) const TS_PRINTF(4, 5);
			Shader loadShader(Shader::Type type, const char *name, const String &macros = String::null) const;
			Shader loadShaderGLSL(Shader::Type type, const char *name, const String &macros = String::null) const;
			Shader loadShaderSPIRV(Shader::Type type, const char *name) const;
			
			Shader createShader(Shader::Type type, const char *src, const char *format, ...) const TS_PRINTF(4, 5);
			Shader createShaderGLSL(Shader::Type type, const char *src, const char *format, ...) const TS_PRINTF(4, 5);
			Shader createShader(Shader::Type type, const char *src, const String &macros = String::null) const;
			Shader createShaderGLSL(Shader::Type type, const char *src, const String &macros = String::null) const;
			Shader createShaderSPIRV(Shader::Type type, const Array<uint32_t> &data) const;
			
			/// create kernel
			Kernel createKernel() const;
			Kernel createKernel(const Kernel &kernel) const;
			
			/// release kernel
			void releaseKernel(Kernel &kernel) const;
			
			/// create pipeline
			Pipeline createPipeline() const;
			Pipeline createPipeline(const Pipeline &pipeline) const;
			
			/// release pipeline
			void releasePipeline(Pipeline &pipeline) const;
			
			/// create traversal
			Traversal createTraversal() const;
			Traversal createTraversal(const Traversal &traversal) const;
			
			/// release traversal
			void releaseTraversal(Traversal &traversal) const;
			
			/// create target
			Target createTarget() const;
			Target createTarget(Surface &surface) const;
			Target createTarget(Window &window) const;
			Target createTarget(const InitializerList<Texture> &textures, Target::Operation op = Target::OpDefault) const;
			
			/// create compute
			Compute createCompute() const;
			
			/// create command
			Command createCommand() const;
			Command createCommand(Target &target) const;
			
			/// set buffer data
			bool setBuffer(Buffer &buffer, size_t offset, const void *src, size_t size) const;
			bool setBuffer(Buffer &buffer, const void *src, size_t size) const;
			bool setBuffer(Buffer &buffer, const void *src) const;
			
			/// get buffer data
			bool getBuffer(Buffer &buffer, size_t offset, void *dest, size_t size) const;
			bool getBuffer(Buffer &buffer, void *dest, size_t size) const;
			bool getBuffer(Buffer &buffer, void *dest) const;
			
			/// map buffer data
			void *mapBuffer(Buffer &buffer, size_t offset, size_t size) const;
			void *mapBuffer(Buffer &buffer, size_t size) const;
			void *mapBuffer(Buffer &buffer) const;
			bool unmapBuffer(Buffer &buffer) const;
			
			/// copy buffer data
			bool copyBuffer(Buffer &buffer, size_t dest_offset, Buffer &src, size_t src_offset, size_t size) const;
			bool copyBuffer(Buffer &buffer, size_t dest_offset, Buffer &src, size_t size) const;
			bool copyBuffer(Buffer &buffer, Buffer &src, size_t size) const;
			bool copyBuffer(Buffer &buffer, Buffer &src) const;
			
			/// clear buffer data
			bool clearBuffer(Buffer &buffer, Format format, size_t offset, const void *src, size_t size) const;
			bool clearBuffer(Buffer &buffer, Format format, const void *src, size_t size) const;
			bool clearBuffer(Buffer &buffer, Format format, const void *src) const;
			bool clearBuffer(Buffer &buffer) const;
			
			/// flush buffer data
			bool flushBuffer(Buffer &buffer, Buffer::Flags flags = Buffer::FlagNone) const;
			bool flushBuffers(const Array<Buffer> &buffers, Buffer::Flags flags = Buffer::FlagNone) const;
			bool flushBuffers(const InitializerList<Buffer> &buffers, Buffer::Flags flags = Buffer::FlagNone) const;
			
			/// release buffer
			void releaseBuffer(Buffer &buffer) const;
			
			/// release sampler
			void releaseSampler(Sampler &sampler) const;
			
			/// set texture data
			bool setTexture(Texture &texture, const Origin &dest_origin, const Slice &dest_slice, const Image &image, const Slice &src_slice) const;
			bool setTexture(Texture &texture, const Origin &dest_origin, const Image &image) const;
			bool setTexture(Texture &texture, const Slice &dest_slice, const Image &image) const;
			bool setTexture(Texture &texture, const Image &image) const;
			
			/// get texture data
			bool getTexture(Texture &texture, const Slice &src_slice, Image &image, const Slice &dest_slice) const;
			bool getTexture(Texture &texture, Image &image, const Slice &dest_slice) const;
			bool getTexture(Texture &texture, Image &image) const;
			
			/// copy texture data
			bool copyTexture(Texture &texture, const Origin &dest_origin, const Slice &dest_slice, Texture &src, const Region &src_region, const Slice &src_slice) const;
			bool copyTexture(Texture &texture, const Origin &dest_origin, Texture &src, const Region &src_region) const;
			bool copyTexture(Texture &texture, const Slice &dest_slice, Texture &src, const Slice &src_slice) const;
			bool copyTexture(Texture &texture, Texture &src) const;
			
			/// clear texture data
			bool clearTexture(Texture &texture, const Region &region, const Slice &slice, const void *src) const;
			bool clearTexture(Texture &texture, const Region &region, const void *src) const;
			bool clearTexture(Texture &texture, const Slice &slice, const void *src) const;
			bool clearTexture(Texture &texture, const void *src) const;
			
			/// bind texture memory
			bool bindTexture(Texture &texture, const Region *regions, uint32_t num_regions, const Slice *slices, uint32_t num_slices, bool commit, Fence &fence) const;
			bool bindTexture(Texture &texture, const Region *regions, uint32_t num_regions, const Slice *slices, uint32_t num_slices, bool commit) const;
			bool bindTexture(Texture &texture, const Region &region, const Slice &slice, bool commit, Fence &fence) const;
			bool bindTexture(Texture &texture, const Region &region, const Slice &slice, bool commit) const;
			
			/// create texture mipmaps
			bool createMipmaps(Texture &texture, const Slice &slice) const;
			bool createMipmaps(Texture &texture) const;
			
			/// flush texture data
			bool flushTexture(Texture &texture, Texture::Flags flags = Texture::FlagNone) const;
			bool flushTexture(Texture &texture, const Slice &slice, Texture::Flags flags = Texture::FlagNone) const;
			bool flushTextures(const Array<Texture> &textures, Texture::Flags flags = Texture::FlagNone) const;
			bool flushTextures(const InitializerList<Texture> &textures, Texture::Flags flags = Texture::FlagNone) const;
			
			/// release texture
			void releaseTexture(Texture &texture) const;
			
			/// set tracing data
			virtual bool setTracing(Tracing &tracing, const Tracing::Instance *instances, uint32_t num_instances) const;
			
			/// build tracing
			bool buildTracing(Tracing &tracing, Buffer &buffer, Tracing::Flags flags = Tracing::FlagNone) const;
			bool buildTracing(Tracing &tracing, Buffer &buffer, size_t offset, Tracing::Flags flags = Tracing::FlagNone) const;
			bool buildTracings(const Array<Tracing> &tracings, Buffer &buffer, Tracing::Flags flags = Tracing::FlagNone) const;
			bool buildTracings(const Array<Tracing> &tracings, Buffer &buffer, size_t offset, Tracing::Flags flags = Tracing::FlagNone) const;
			
			/// copy tracing address
			bool copyTracing(Tracing &tracing, Buffer &buffer, size_t offset = 0) const;
			bool copyTracings(const Array<Tracing> &tracings, Buffer &buffer, size_t offset, size_t stride = 0) const;
			
			/// flush tracing
			bool flushTracing(Tracing &tracing) const;
			bool flushTracings(const Array<Tracing> &tracings) const;
			
			/// release tracing
			void releaseTracing(Tracing &tracing) const;
			
			/// set table texture
			bool setTable(TextureTable &table, uint32_t index, Texture &texture, bool owner = false) const;
			bool setTable(TextureTable &table, uint32_t index, const Array<Texture> &textures, bool owner = false) const;
			
			/// release table
			void releaseTable(TextureTable &table) const;
			
			/// begin/end query
			bool beginQuery(Query &query) const;
			void endQuery(Query &query) const;
			
			/// copy query data
			bool copyQuery(Query &query, Buffer &buffer, size_t offset = 0) const;
			bool copyQueries(const Array<Query> &queries, Buffer &buffer, size_t offset = 0, size_t stride = 0) const;
			bool copyQueries(const InitializerList<Query> &queries, Buffer &buffer, size_t offset = 0, size_t stride = 0) const;
			
			/// fence synchronization
			bool waitFence(Fence &fence) const;
			bool signalFence(Fence &fence) const;
			
			/// execute context
			bool execute(Device &device) const;
			
			/// flip context
			bool flip(Fence &fence) const;
			bool flip() const;
			
			/// flush context
			bool flush() const;
			
			/// finish context
			bool finish() const;
			
			/// check errors
			bool check() const;
	};
	
	/**
	 * D3D12Device
	 */
	class TS_API D3D12Device : public Device {
			
			TS_DECLARE_PTR_1(D3D12Device, Device, 0)
			
		public:
			
			D3D12Device();
			virtual ~D3D12Device();
			
			/// buffer state
			void setBufferState(Buffer &buffer, uint32_t state);
			
			/// texture state
			void setTextureState(Texture &texture, uint32_t state);
			
			/// command context
			ID3D12Device *getD3D12Device() const;
			ID3D12GraphicsCommandList *getCommand() const;
	};
	
	/**
	 * D3D11Device
	 */
	class TS_API D3D11Device : public Device {
			
			TS_DECLARE_PTR_1(D3D11Device, Device, 0)
			
		public:
			
			D3D11Device();
			virtual ~D3D11Device();
			
			/// command context
			ID3D11Device *getD3D11Device() const;
			ID3D11DeviceContext *getCommand() const;
	};
	
	/**
	 * MTLDevice
	 */
	class TS_API MTLDevice : public Device {
			
			TS_DECLARE_PTR_1(MTLDevice, Device, 0)
			
		public:
			
			MTLDevice();
			virtual ~MTLDevice();
			
			/// command context
			void *getMTLDevice() const;
			void *getQueue() const;
			void *getCommand() const;
	};
	
	/**
	 * VKDevice
	 */
	class TS_API VKDevice : public Device {
			
			TS_DECLARE_PTR_1(VKDevice, Device, 0)
			
		public:
			
			VKDevice();
			virtual ~VKDevice();
			
			/// buffer access
			void setBufferAccess(Buffer &buffer, uint32_t access);
			
			/// texture layout
			void setTextureLayout(Texture &texture, uint32_t layout);
			
			/// fence synchronization
			bool waitVKFence(void *fence, uint64_t timeout, bool reset) const;
			bool signalVKFence(void *fence) const;
			
			/// semaphore synchronization
			void waitSemaphore(void *semaphore, uint32_t mask) const;
			void signalSemaphore(void *semaphore) const;
			
			/// memory types
			bool hasMemoryType(uint32_t flags) const;
			uint32_t getMemoryIndex(uint32_t types, uint32_t flags) const;
			
			/// command context
			VkInstance getInstance() const;
			VkPhysicalDevice getAdapter() const;
			VkDevice getVKDevice() const;
			VkQueue getQueue() const;
			VkCommandBuffer getCommand() const;
			uint32_t getFamily() const;
	};
	
	/**
	 * FUDevice
	 */
	class TS_API FUDevice : public Device {
			
			TS_DECLARE_PTR_1(FUDevice, Device, 0)
			
		public:
			
			FUDevice();
			explicit FUDevice(const Array<Device> &devices, bool owner = false);
			virtual ~FUDevice();
			
			/// device mask
			void setMask(uint32_t mask);
			uint32_t getMask() const;
			
			/// Fusion devices
			uint32_t getNumDevices() const;
			const Device getDevice(uint32_t index) const;
			Device getDevice(uint32_t index);
	};
}

#endif /* __TELLUSIM_PLATFORM_DEVICE_H__ */
