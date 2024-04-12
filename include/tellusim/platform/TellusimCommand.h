// Copyright (C) 2018-2024, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_PLATFORM_COMMAND_H__
#define __TELLUSIM_PLATFORM_COMMAND_H__

#include <TellusimTypes.h>
#include <TellusimFormat.h>
#include <core/TellusimArray.h>
#include <platform/TellusimPlatform.h>

/*
 */
namespace Tellusim {
	
	/* Prototypes
	 */
	struct Color;
	class Query;
	class Buffer;
	class Sampler;
	class Texture;
	class Tracing;
	class TextureTable;
	class Pipeline;
	
	/**
	 * Command class
	 */
	class TS_API Command {
			
			TS_DECLARE_PTR(Command, 0)
			
		public:
			
			Command();
			virtual ~Command();
			
			/// command platform
			Platform getPlatform() const;
			
			TS_INLINE const char *getPlatformName() const { return Tellusim::getPlatformName(getPlatform()); }
			
			/// command device index
			uint32_t getIndex() const;
			
			/// set pipeline
			void setPipeline(Pipeline &pipeline);
			Pipeline getPipeline() const;
			
			/// set viewport parameters
			void setViewport(uint32_t index, const Viewport &viewport);
			void setViewports(const Viewport *viewports, uint32_t num_viewports);
			
			/// set scissor parameters
			void setScissor(uint32_t index, const Scissor &scissor);
			void setScissors(const Scissor *scissors, uint32_t num_scissors);
			
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
			
			/// set vertices
			void *getVertexData(uint32_t index, size_t size);
			void setVertexData(uint32_t index, const void *src, size_t size);
			void setVertexBuffer(uint32_t index, Buffer &buffer, size_t offset = 0);
			void setVertexOffset(uint32_t index, size_t offset, bool relative = false);
			void setVertexBuffers(uint32_t index, const InitializerList<Buffer> &buffers);
			void setVertexBuffers(uint32_t index, const InitializerList<Buffer> &buffers, const InitializerList<size_t> &offsets);
			
			template <class Type, size_t Size> void setVertices(uint32_t index, const Type (&vertices)[Size]) { setVertexData(index, vertices, sizeof(Type) * Size); }
			template <class Type> void setVertices(uint32_t index, const InitializerList<Type> &vertices) { setVertexData(index, vertices.begin(), sizeof(Type) * vertices.size()); }
			
			/// set indices
			void *getIndexData(Format format, size_t size);
			void setIndexData(Format format, const void *src, size_t size);
			void setIndexBuffer(Format format, Buffer &buffer, size_t offset = 0);
			void setIndexOffset(size_t offset, bool relative = false);
			
			template <class Type, size_t Size> void setIndices(Format format, const Type (&indices)[Size]) { setIndexData(format, indices, sizeof(Type) * Size); }
			void setIndices(const InitializerList<uint16_t> &indices) { setIndexData(FormatRu16, indices.begin(), sizeof(uint16_t) * indices.size()); }
			
			/// set indirect
			void *getIndirectData(size_t size);
			void setIndirectData(const void *src, size_t size);
			void setIndirectBuffer(Buffer &buffer, size_t offset = 0);
			void setIndirectOffset(size_t offset, bool relative = false);
			
			template <class Type> void setIndirect(const Type &data) { setIndirectData(&data, sizeof(Type)); }
			
			/// blending parameters
			void setBlendColor(const Color &color);
			void setBlendColor(float32_t r, float32_t g, float32_t b, float32_t a);
			
			/// stencil parameters
			void setStencilRef(uint32_t ref);
			
			/// draw arrays
			void drawArrays(uint32_t num_vertices, uint32_t base_vertex = 0);
			void drawArraysInstanced(uint32_t num_vertices, uint32_t base_vertex, uint32_t num_instances, uint32_t base_instance = 0);
			
			/// draw arrays indirect
			struct DrawArraysIndirect;
			void drawArraysIndirect(uint32_t num_draws, size_t stride = sizeof(DrawArraysIndirect));
			void drawArraysIndirect(Buffer &buffer, size_t offset, uint32_t num_draws, size_t stride = sizeof(DrawArraysIndirect));
			
			/// draw elements
			void drawElements(uint32_t num_indices, uint32_t base_index = 0, int32_t base_vertex = 0);
			void drawElementsInstanced(uint32_t num_indices, uint32_t base_index, uint32_t num_instances);
			void drawElementsInstanced(uint32_t num_indices, uint32_t base_index, int32_t base_vertex, uint32_t num_instances, uint32_t base_instance = 0);
			
			/// draw elements indirect
			struct DrawElementsIndirect;
			void drawElementsIndirect(uint32_t num_draws, size_t stride = sizeof(DrawElementsIndirect));
			void drawElementsIndirect(Buffer &buffer, size_t offset, uint32_t num_draws, size_t stride = sizeof(DrawElementsIndirect));
			
			/// draw mesh
			void drawMesh(uint32_t width, uint32_t height = 1, uint32_t depth = 1);
			
			/// draw mesh indirect
			struct DrawMeshIndirect;
			void drawMeshIndirect(uint32_t num_draws, size_t stride = sizeof(DrawMeshIndirect));
			void drawMeshIndirect(Buffer &buffer, size_t offset, uint32_t num_draws, size_t stride = sizeof(DrawMeshIndirect));
			
			/// begin/end conditional
			void beginConditional(Buffer &buffer, size_t offset);
			void endConditional();
			
			/// begin/end query
			bool beginQuery(Query &query);
			void endQuery(Query &query);
			
			/// draw arrays indirect parameters
			struct DrawArraysIndirect {
				uint32_t num_vertices;
				uint32_t num_instances;
				uint32_t base_vertex;
				uint32_t base_instance;
			};
			
			/// draw elements indirect parameters
			struct DrawElementsIndirect {
				uint32_t num_indices;
				uint32_t num_instances;
				uint32_t base_index;
				int32_t base_vertex;
				uint32_t base_instance;
			};
			
			/// draw mesh indirect parameters
			struct DrawMeshIndirect {
				uint32_t group_width;
				uint32_t group_height;
				uint32_t group_depth;
				uint32_t padding;
			};
	};
	
	/**
	 * D3D12Command
	 */
	class TS_API D3D12Command : public Command {
			
			TS_DECLARE_PTR_1(D3D12Command, Command, 0)
			
		public:
			
			D3D12Command();
			virtual ~D3D12Command();
			
			/// command context
			ID3D12GraphicsCommandList *getD3D12Command() const;
			
			/// update resources
			void update();
	};
	
	/**
	 * MTLCommand
	 */
	class TS_API MTLCommand : public Command {
			
			TS_DECLARE_PTR_1(MTLCommand, Command, 0)
			
		public:
			
			MTLCommand();
			virtual ~MTLCommand();
			
			/// command context
			void *getEncoder() const;
			
			/// end encoding
			void flush(void *encoder, bool enqueue = false);
			void flush(bool create = false, bool enqueue = false);
			
			/// update resources
			void update();
	};
	
	/**
	 * VKCommand
	 */
	class TS_API VKCommand : public Command {
			
			TS_DECLARE_PTR_1(VKCommand, Command, 0)
			
		public:
			
			VKCommand();
			virtual ~VKCommand();
			
			/// command context
			VkCommandBuffer getVKCommand() const;
			
			/// command descriptors
			VkDescriptorSet getSamplerDescriptor() const;
			VkDescriptorSet getImageDescriptor() const;
			VkDescriptorSet getBufferDescriptor() const;
			VkDescriptorSet getTracingDescriptor() const;
			VkDescriptorSet getTexelDescriptor() const;
			
			/// update resources
			void update();
	};
	
	/**
	 * FUCommand
	 */
	class TS_API FUCommand : public Command {
			
			TS_DECLARE_PTR_1(FUCommand, Command, 0)
			
		public:
			
			FUCommand();
			explicit FUCommand(const Array<Command> &commands, bool owner = false);
			virtual ~FUCommand();
			
			/// device mask
			void setMask(uint32_t mask);
			uint32_t getMask() const;
			
			/// Fusion commands
			uint32_t getNumCommands() const;
			const Command getCommand(uint32_t index) const;
			Command getCommand(uint32_t index);
	};
}

#endif /* __TELLUSIM_PLATFORM_COMMAND_H__ */
