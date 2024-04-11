// Copyright (C) 2018-2024, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_PLATFORM_SURFACE_H__
#define __TELLUSIM_PLATFORM_SURFACE_H__

#include <TellusimFormat.h>
#include <platform/TellusimPlatform.h>

/*
 */
namespace Tellusim {
	
	/* Prototypes
	 */
	class Context;
	class D3D12Context;
	class D3D11Context;
	class MTLContext;
	class VKContext;
	class GLContext;
	class GLESContext;
	
	/**
	 * Surface
	 */
	class TS_API Surface {
			
		protected:
			
			TS_DECLARE_PTR(Surface, 2)
			
		public:
			
			Surface();
			explicit Surface(Context &context);
			explicit Surface(Platform platform);
			virtual ~Surface();
			
			/// context platform
			Platform getPlatform() const;
			
			TS_INLINE const char *getPlatformName() const { return Tellusim::getPlatformName(getPlatform()); }
			
			/// surface device index
			uint32_t getIndex() const;
			
			/// surface size
			void setSize(uint32_t width, uint32_t height);
			uint32_t getWidth() const;
			uint32_t getHeight() const;
			
			/// surface multisample
			void setMultisample(uint32_t multisample);
			uint32_t getMultisample() const;
			bool hasMultisample() const;
			
			/// surface layers
			void setColorLayer(uint32_t layer, uint32_t layers);
			void setDepthLayer(uint32_t layer, uint32_t layers);
			uint32_t getColorLayer() const;
			uint32_t getDepthLayer() const;
			uint32_t getColorLayers() const;
			uint32_t getDepthLayers() const;
			bool hasColorLayers() const;
			bool hasDepthLayers() const;
			
			/// surface formats
			void setColorFormat(Format format);
			void setDepthFormat(Format format);
			Format getColorFormat() const;
			Format getDepthFormat() const;
	};
	
	/**
	 * D3D12Surface
	 */
	class TS_API D3D12Surface : public Surface {
			
			TS_DECLARE_PTR_1(D3D12Surface, Surface, 0)
			
		public:
			
			D3D12Surface();
			explicit D3D12Surface(D3D12Context &context);
			virtual ~D3D12Surface();
			
			/// current device
			IDXGIFactory4 *getFactory() const;
			ID3D12Device *getDevice() const;
			ID3D12CommandQueue *getQueue() const;
			ID3D12GraphicsCommandList *getCommand() const;
			
			/// render targets
			void setRenderTarget(ID3D12Resource *render_target);
			void setDepthStencil(ID3D12Resource *depth_stencil);
			ID3D12Resource *getRenderTarget() const;
			ID3D12Resource *getDepthStencil() const;
			
			/// render target views
			void setRenderTargetView(size_t render_target_view);
			void setDepthStencilView(size_t depth_stencil_view);
			size_t getRenderTargetView() const;
			size_t getDepthStencilView() const;
	};
	
	/**
	 * D3D11Surface
	 */
	class TS_API D3D11Surface : public Surface {
			
			TS_DECLARE_PTR_1(D3D11Surface, Surface, 0)
			
		public:
			
			D3D11Surface();
			explicit D3D11Surface(D3D11Context &context);
			virtual ~D3D11Surface();
			
			/// current device
			IDXGIFactory *getFactory() const;
			ID3D11Device *getDevice() const;
			ID3D11DeviceContext *getContext() const;
			
			/// render targets
			void setRenderTarget(ID3D11Texture2D *render_target);
			void setDepthStencil(ID3D11Texture2D *depth_stencil);
			ID3D11Texture2D *getRenderTarget() const;
			ID3D11Texture2D *getDepthStencil() const;
			
			/// render target views
			void setRenderTargetView(ID3D11RenderTargetView *render_target_view);
			void setDepthStencilView(ID3D11DepthStencilView *depth_stencil_view);
			ID3D11RenderTargetView *getRenderTargetView() const;
			ID3D11DepthStencilView *getDepthStencilView() const;
	};
	
	/**
	 * MTLSurface
	 */
	class TS_API MTLSurface : public Surface {
			
			TS_DECLARE_PTR_1(MTLSurface, Surface, 0)
			
		public:
			
			MTLSurface();
			explicit MTLSurface(MTLContext &context);
			virtual ~MTLSurface();
			
			/// current device
			void *getDevice() const;
			void *getQueue() const;
			void *getCommand() const;
			
			/// render pass descriptor
			void setDescriptor(void *descriptor);
			void *getDescriptor() const;
	};
	
	/**
	 * VKSurface
	 */
	class TS_API VKSurface : public Surface {
			
			TS_DECLARE_PTR_1(VKSurface, Surface, 0)
			
		public:
			
			VKSurface();
			explicit VKSurface(VKContext &context);
			virtual ~VKSurface();
			
			/// current device
			VkInstance getInstance() const;
			VkPhysicalDevice getAdapter() const;
			VkDevice getDevice() const;
			VkQueue getQueue() const;
			VkCommandBuffer getCommand() const;
			uint32_t getFamily() const;
			
			/// image handles
			void setColorImage(VkImage image);
			void setDepthImage(VkImage image);
			VkImage getColorImage() const;
			VkImage getDepthImage() const;
			
			/// image view handles
			void setColorImageView(VkImageView image_view);
			void setDepthImageView(VkImageView image_view);
			VkImageView getColorImageView() const;
			VkImageView getDepthImageView() const;
			
			/// framebuffer handle
			void setRenderPass(VkRenderPass render_pass);
			void setFramebuffer(VkFramebuffer framebuffer);
			VkRenderPass getRenderPass() const;
			VkFramebuffer getFramebuffer() const;
	};
	
	/**
	 * GLSurface
	 */
	class TS_API GLSurface : public Surface {
			
			TS_DECLARE_PTR_1(GLSurface, Surface, 0)
			
		public:
			
			GLSurface();
			explicit GLSurface(GLContext &context);
			virtual ~GLSurface();
			
			/// current context
			void *getContext() const;
			
			/// texture identifiers
			void setColorTextureID(uint32_t texture_id);
			void setDepthTextureID(uint32_t texture_id);
			uint32_t getColorTextureID() const;
			uint32_t getDepthTextureID() const;
			
			/// framebuffer identifier
			void setFramebufferID(uint32_t framebuffer_id);
			uint32_t getFramebufferID() const;
	};
	
	/**
	 * GLESSurface
	 */
	class TS_API GLESSurface : public Surface {
			
			TS_DECLARE_PTR_1(GLESSurface, Surface, 0)
			
		public:
			
			GLESSurface();
			explicit GLESSurface(GLESContext &context);
			virtual ~GLESSurface();
			
			/// current context
			void *getContext() const;
			
			/// texture identifiers
			void setColorTextureID(uint32_t texture_id);
			void setDepthTextureID(uint32_t texture_id);
			uint32_t getColorTextureID() const;
			uint32_t getDepthTextureID() const;
			
			/// framebuffer identifier
			void setFramebufferID(uint32_t framebuffer_id);
			uint32_t getFramebufferID() const;
	};
}

#endif /* __TELLUSIM_PLATFORM_SURFACE_H__ */
