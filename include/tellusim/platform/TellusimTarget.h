// Copyright (C) 2018-2024, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_PLATFORM_TARGET_H__
#define __TELLUSIM_PLATFORM_TARGET_H__

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
	class Fence;
	class Surface;
	class Texture;
	
	/**
	 * Target class
	 */
	class TS_API Target {
			
			TS_DECLARE_PTR(Target, 0)
			
		public:
			
			/// Target operations
			enum Operation {
				
				BeginLoad		= (1 << 0),		// load targets
				BeginClear		= (1 << 1),		// clear targets
				BeginDiscard	= (1 << 2),		// discard targets
				BeginMask		= (BeginLoad | BeginClear | BeginDiscard),
				
				EndStore		= (1 << 3),		// store targets
				EndResolve		= (1 << 4),		// resolve targets
				EndDiscard		= (1 << 5),		// discard targets
				EndMask			= (EndStore | EndResolve | EndDiscard),
				
				OpNone			= 0,
				OpLoad			= BeginLoad,
				OpLoadStore		= (BeginLoad | EndStore),
				OpClearStore	= (BeginClear | EndStore),
				OpClearDiscard	= (BeginClear | EndDiscard),
				OpDefault		= OpClearStore,
			};
			
			Target();
			virtual ~Target();
			
			/// target platform
			Platform getPlatform() const;
			
			TS_INLINE const char *getPlatformName() const { return Tellusim::getPlatformName(getPlatform()); }
			
			/// target device index
			uint32_t getIndex() const;
			
			/// begin target
			bool begin(Fence &fence);
			bool begin();
			
			/// end target
			void end(Fence &fence);
			void end();
			
			/// swap target
			void swap(Surface &surface);
			
			/// check target
			bool isEnabled() const;
			
			/// target format
			Format getColorFormat(uint32_t index = 0) const;
			Format getDepthFormat() const;
			uint32_t getMultisample() const;
			bool hasMultisample() const;
			bool isFlipped() const;
			bool isAtomic() const;
			
			/// target dimension
			uint32_t getWidth() const;
			uint32_t getHeight() const;
			uint32_t getDepth() const;
			uint32_t getFaces() const;
			uint32_t getLayers() const;
			uint32_t getMipmaps() const;
			
			/// color target
			void setClearColor(const Color &color);
			void setClearColor(uint32_t index, const Color &color);
			void setClearColor(float32_t r, float32_t g, float32_t b, float32_t a);
			void setClearColor(uint32_t index, float32_t r, float32_t g, float32_t b, float32_t a);
			void setColorTexture(Texture &texture, Operation op = OpDefault, const Slice &slice = Slice());
			void setColorTexture(uint32_t index, Texture &texture, Operation op = OpDefault, const Slice &slice = Slice());
			void setColorResolve(Texture &texture, const Slice &slice = Slice());
			void setColorResolve(uint32_t index, Texture &texture, const Slice &slice = Slice());
			
			uint32_t getNumTargets() const;
			const Color &getClearColor(uint32_t index = 0) const;
			Operation getColorOp(uint32_t index = 0) const;
			Texture getColorTexture(uint32_t index) const;
			Texture getColorResolve(uint32_t index) const;
			const Slice &getColorTextureSlice(uint32_t index) const;
			const Slice &getColorResolveSlice(uint32_t index) const;
			
			/// depth target
			void setClearDepth(float32_t depth, uint32_t stencil = 0);
			void setDepthTexture(Texture &texture, Operation op = OpDefault, const Slice &slice = Slice());
			void setDepthResolve(Texture &texture, const Slice &slice = Slice());
			
			float32_t getClearDepth() const;
			uint32_t getClearStencil() const;
			Operation getDepthOp() const;
			Texture getDepthTexture() const;
			Texture getDepthResolve() const;
			const Slice &getDepthTextureSlice() const;
			const Slice &getDepthResolveSlice() const;
	};
	
	/**
	 * D3D12Target
	 */
	class TS_API D3D12Target : public Target {
			
			TS_DECLARE_PTR_1(D3D12Target, Target, 0)
			
		public:
			
			D3D12Target();
			virtual ~D3D12Target();
			
			size_t *getRenderTargetViews() const;
			size_t getDepthStencilView() const;
	};
	
	/**
	 * D3D11Target
	 */
	class TS_API D3D11Target : public Target {
			
			TS_DECLARE_PTR_1(D3D11Target, Target, 0)
			
		public:
			
			D3D11Target();
			virtual ~D3D11Target();
			
			ID3D11RenderTargetView **getRenderTargetViews() const;
			ID3D11DepthStencilView *getDepthStencilView() const;
	};
	
	/**
	 * MTLTarget
	 */
	class TS_API MTLTarget : public Target {
			
			TS_DECLARE_PTR_1(MTLTarget, Target, 0)
			
		public:
			
			MTLTarget();
			virtual ~MTLTarget();
			
			void *getDescriptor() const;
	};
	
	/**
	 * VKTarget
	 */
	class TS_API VKTarget : public Target {
			
			TS_DECLARE_PTR_1(VKTarget, Target, 0)
			
		public:
			
			VKTarget();
			virtual ~VKTarget();
			
			VkRenderPass getRenderPass() const;
			VkFramebuffer getFramebuffer() const;
	};
	
	/**
	 * GLTarget
	 */
	class TS_API GLTarget : public Target {
			
			TS_DECLARE_PTR_1(GLTarget, Target, 0)
			
		public:
			
			GLTarget();
			virtual ~GLTarget();
			
			uint32_t getFramebufferID() const;
	};
	
	/**
	 * GLESTarget
	 */
	class TS_API GLESTarget : public Target {
			
			TS_DECLARE_PTR_1(GLESTarget, Target, 0)
			
		public:
			
			GLESTarget();
			virtual ~GLESTarget();
			
			uint32_t getFramebufferID() const;
	};
	
	/**
	 * FUTarget
	 */
	class TS_API FUTarget : public Target {
			
			TS_DECLARE_PTR_1(FUTarget, Target, 0)
			
		public:
			
			FUTarget();
			explicit FUTarget(const Array<Target> &targets, bool owner = false);
			virtual ~FUTarget();
			
			/// device mask
			void setMask(uint32_t mask);
			uint32_t getMask() const;
			
			/// Fusion targets
			uint32_t getNumTargets() const;
			const Target getTarget(uint32_t index) const;
			Target getTarget(uint32_t index);
	};
	
	/*
	 */
	TS_DECLARE_ENUM_OP(Target::Operation)
}

#endif /* __TELLUSIM_PLATFORM_TARGET_H__ */
