// Copyright (C) 2018-2024, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_PLATFORM_COMPUTE_H__
#define __TELLUSIM_PLATFORM_COMPUTE_H__

#include <TellusimTypes.h>
#include <TellusimFormat.h>
#include <core/TellusimArray.h>
#include <platform/TellusimPlatform.h>

/*
 */
namespace Tellusim {
	
	/* Prototypes
	 */
	class Image;
	class Query;
	class Buffer;
	class Sampler;
	class Texture;
	class Tracing;
	class TextureTable;
	class Kernel;
	class Traversal;
	
	/**
	 * Compute class
	 */
	class TS_API Compute {
			
			TS_DECLARE_PTR(Compute, 0)
			
		public:
			
			Compute();
			virtual ~Compute();
			
			/// compute platform
			Platform getPlatform() const;
			
			TS_INLINE const char *getPlatformName() const { return Tellusim::getPlatformName(getPlatform()); }
			
			/// compute device index
			uint32_t getIndex() const;
			
			/// set kernel
			void setKernel(Kernel &kernel);
			Kernel getKernel() const;
			
			/// set traversal
			void setTraversal(Traversal &traversal);
			Traversal getTraversal() const;
			
			/// set samplers
			void setSampler(uint32_t index, Sampler &sampler);
			void setSamplers(uint32_t index, const InitializerList<Sampler> &samplers);
			
			/// set textures
			void setTexture(uint32_t index, Texture &texture);
			void setTexture(uint32_t index, Texture &texture, const Slice &slice);
			void setTextures(uint32_t index, const InitializerList<Texture> &textures);
			
			/// set surfaces
			void setSurfaceTexture(uint32_t index, Texture &texture);
			void setSurfaceTexture(uint32_t index, Texture &texture, const Slice &slice, Format format = FormatUnknown);
			void setSurfaceTextures(uint32_t index, const InitializerList<Texture> &textures);
			
			/// set uniforms
			void *getUniformData(uint32_t index, size_t size);
			void setUniformData(uint32_t index, const void *src, size_t size);
			void setUniformBuffer(uint32_t index, Buffer &buffer, size_t offset = 0, size_t size = 0);
			void setUniformOffset(uint32_t index, size_t offset, bool relative = false);
			void setUniformBuffers(uint32_t index, const InitializerList<Buffer> &buffers);
			void setUniformBuffers(uint32_t index, const InitializerList<Buffer> &buffers, const InitializerList<size_t> &offsets);
			
			template <class Type> void setUniform(uint32_t index, const Type &data) { setUniformData(index, &data, sizeof(Type)); }
			
			/// set storages
			void *getStorageData(uint32_t index, size_t size);
			void setStorageData(uint32_t index, const void *src, size_t size);
			void setStorageBuffer(uint32_t index, Buffer &buffer, size_t offset = 0, size_t size = 0);
			void setStorageOffset(uint32_t index, size_t offset, bool relative = false);
			void setStorageBuffers(uint32_t index, const InitializerList<Buffer> &buffers);
			void setStorageBuffers(uint32_t index, const InitializerList<Buffer> &buffers, const InitializerList<size_t> &offsets);
			
			template <class Type> void setStorage(uint32_t index, const Type &data) { setStorageData(index, &data, sizeof(Type)); }
			
			/// set tracings
			void setTracing(uint32_t index, Tracing &tracing);
			void setTracings(uint32_t index, const InitializerList<Tracing> &tracings);
			
			/// set texels
			void setTexelBuffer(uint32_t index, Buffer &buffer);
			void setTexelBuffers(uint32_t index, const InitializerList<Buffer> &buffers);
			
			/// set tables
			void setTextureTable(uint32_t index, TextureTable &table);
			void setTextureTables(uint32_t index, const InitializerList<TextureTable> &tables);
			
			/// set indirect
			void *getIndirectData(size_t size);
			void setIndirectData(const void *src, size_t size);
			void setIndirectBuffer(Buffer &buffer, size_t offset = 0);
			void setIndirectOffset(size_t offset, bool relative = false);
			
			template <class Type> void setIndirect(const Type &data) { setIndirectData(&data, sizeof(Type)); }
			
			/// dispatch kernel
			void dispatch(uint32_t width, uint32_t height = 1, uint32_t depth = 1);
			void dispatch(const Texture &texture);
			void dispatch(const Size &size);
			
			/// dispatch kernel indirect
			void dispatchIndirect();
			
			/// set buffer data
			bool setBuffer(Buffer &buffer, size_t offset, const void *src, size_t size);
			bool setBuffer(Buffer &buffer, const void *src, size_t size);
			bool setBuffer(Buffer &buffer, const void *src);
			
			/// copy buffer data
			bool copyBuffer(Buffer &buffer, size_t dest_offset, Buffer &src, size_t src_offset, size_t size);
			bool copyBuffer(Buffer &buffer, size_t dest_offset, Buffer &src, size_t size);
			bool copyBuffer(Buffer &buffer, Buffer &src, size_t size);
			bool copyBuffer(Buffer &buffer, Buffer &src);
			
			/// clear buffer data
			bool clearBuffer(Buffer &buffer, Format format, size_t offset, const void *src, size_t size);
			bool clearBuffer(Buffer &buffer, Format format, const void *src, size_t size);
			bool clearBuffer(Buffer &buffer, Format format, const void *src);
			bool clearBuffer(Buffer &buffer);
			
			/// set texture data
			bool setTexture(Texture &texture, const Origin &dest_origin, const Slice &dest_slice, const Image &image, const Slice &src_slice);
			bool setTexture(Texture &texture, const Origin &dest_origin, const Image &image);
			bool setTexture(Texture &texture, const Slice &dest_slice, const Image &image);
			bool setTexture(Texture &texture, const Image &image);
			
			/// copy texture data
			bool copyTexture(Texture &texture, const Origin &dest_origin, const Slice &dest_slice, Texture &src, const Region &src_region, const Slice &src_slice);
			bool copyTexture(Texture &texture, const Origin &dest_origin, Texture &src, const Region &src_region);
			bool copyTexture(Texture &texture, const Slice &dest_slice, Texture &src, const Slice &src_slice);
			bool copyTexture(Texture &texture, Texture &src);
			
			/// clear texture data
			bool clearTexture(Texture &texture, const Region &region, const Slice &slice, const void *src);
			bool clearTexture(Texture &texture, const Region &region, const void *src);
			bool clearTexture(Texture &texture, const Slice &slice, const void *src);
			bool clearTexture(Texture &texture, const void *src);
			
			/// resource barriers
			void barrier(Texture &texture);
			void barrier(Buffer &buffer);
			
			void barrier(const InitializerList<Texture> &textures);
			void barrier(const InitializerList<Buffer> &buffers);
			
			/// begin/end conditional
			void beginConditional(Buffer &buffer, size_t offset);
			void endConditional();
			
			/// begin/end query
			bool beginQuery(Query &query);
			void endQuery(Query &query);
			
			/// dispatch indirect parameters
			struct DispatchIndirect {
				uint32_t group_width;
				uint32_t group_height;
				uint32_t group_depth;
				uint32_t padding;
			};
	};
	
	/**
	 * D3D12Compute
	 */
	class TS_API D3D12Compute : public Compute {
			
			TS_DECLARE_PTR_1(D3D12Compute, Compute, 0)
			
		public:
			
			D3D12Compute();
			virtual ~D3D12Compute();
			
			/// command context
			ID3D12GraphicsCommandList *getCommand() const;
			
			/// update resources
			void update();
	};
	
	/**
	 * MTLCompute
	 */
	class TS_API MTLCompute : public Compute {
			
			TS_DECLARE_PTR_1(MTLCompute, Compute, 0)
			
		public:
			
			MTLCompute();
			virtual ~MTLCompute();
			
			/// command context
			void *getEncoder() const;
			
			/// end encoding
			void flush(void *encoder, bool enqueue = false);
			void flush(bool create = false, bool enqueue = false);
			
			/// update resources
			void update();
	};
	
	/**
	 * VKCompute
	 */
	class TS_API VKCompute : public Compute {
			
			TS_DECLARE_PTR_1(VKCompute, Compute, 0)
			
		public:
			
			VKCompute();
			virtual ~VKCompute();
			
			/// command context
			VkCommandBuffer getCommand() const;
			
			/// compute descriptors
			VkDescriptorSet getSamplerDescriptor() const;
			VkDescriptorSet getImageDescriptor() const;
			VkDescriptorSet getBufferDescriptor() const;
			VkDescriptorSet getTracingDescriptor() const;
			VkDescriptorSet getTexelDescriptor() const;
			
			/// update resources
			void update();
	};
	
	/**
	 * FUCompute
	 */
	class TS_API FUCompute : public Compute {
			
			TS_DECLARE_PTR_1(FUCompute, Compute, 0)
			
		public:
			
			FUCompute();
			explicit FUCompute(const Array<Compute> &computes, bool owner = false);
			virtual ~FUCompute();
			
			/// device mask
			void setMask(uint32_t mask);
			uint32_t getMask() const;
			
			/// Fusion computes
			uint32_t getNumComputes() const;
			const Compute getCompute(uint32_t index) const;
			Compute getCompute(uint32_t index);
	};
}

#endif /* __TELLUSIM_PLATFORM_COMPUTE_H__ */
