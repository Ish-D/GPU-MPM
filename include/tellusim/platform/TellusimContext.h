// Copyright (C) 2018-2024, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_PLATFORM_CONTEXT_H__
#define __TELLUSIM_PLATFORM_CONTEXT_H__

#include <platform/TellusimPlatform.h>

/*
 */
namespace Tellusim {
	
	/**
	 * Context
	 */
	class TS_API Context {
			
			TS_DECLARE_PTR(Context, 2)
			
		public:
			
			/// context constructor
			Context();
			explicit Context(Platform platform, uint32_t index = Maxu32);
			virtual ~Context();
			
			/// context platform
			Platform getPlatform() const;
			
			TS_INLINE const char *getPlatformName() const { return Tellusim::getPlatformName(getPlatform()); }
			
			/// context device index
			uint32_t getIndex() const;
			
			/// check context
			bool isCreated() const;
			
			/// create context
			bool create();
			
			/// flush context
			bool flush();
			bool finish();
	};
	
	/**
	 * D3D12Context
	 */
	class TS_API D3D12Context : public Context {
			
			TS_DECLARE_PTR_1(D3D12Context, Context, 0)
			
		public:
			
			D3D12Context();
			virtual ~D3D12Context();
			
			/// create context
			bool create(ID3D12Device *device, ID3D12CommandQueue *queue);
			
			/// current device
			IDXGIFactory4 *getFactory() const;
			ID3D12Device *getDevice() const;
			ID3D12CommandQueue *getQueue() const;
			ID3D12GraphicsCommandList *getCommand() const;
			
			/// check Direct3D12 errors
			static bool error(uint32_t result);
			
			using Context::create;
	};
	
	/**
	 * D3D11Context
	 */
	class TS_API D3D11Context : public Context {
			
			TS_DECLARE_PTR_1(D3D11Context, Context, 0)
			
		public:
			
			D3D11Context();
			virtual ~D3D11Context();
			
			/// create context
			bool create(ID3D11Device *device);
			
			/// current device
			IDXGIFactory *getFactory() const;
			ID3D11Device *getDevice() const;
			ID3D11DeviceContext *getD3D11Context() const;
			
			/// check Direct3D11 errors
			static bool error(uint32_t result);
			
			using Context::create;
	};
	
	/**
	 * MTLContext
	 */
	class TS_API MTLContext : public Context {
			
			TS_DECLARE_PTR_1(MTLContext, Context, 0)
			
		public:
			
			MTLContext();
			virtual ~MTLContext();
			
			/// create context
			bool create(void *device, void *queue);
			
			/// current device
			void *getDevice() const;
			void *getQueue() const;
			void *getCommand() const;
			
			using Context::create;
	};
	
	/**
	 * VKContext
	 */
	class TS_API VKContext : public Context {
			
			TS_DECLARE_PTR_1(VKContext, Context, 0)
			
		public:
			
			VKContext();
			virtual ~VKContext();
			
			/// create context
			bool create(VkInstance instance, PFN_vkGetInstanceProcAddr func, VkPhysicalDevice adapter, VkDevice device, uint32_t family, uint32_t index);
			
			/// current device
			VkInstance getInstance() const;
			VkPhysicalDevice getAdapter() const;
			VkDevice getDevice() const;
			
			/// current context
			VkQueue getQueue() const;
			VkCommandBuffer getCommand() const;
			uint32_t getFamily() const;
			
			/// device queues
			uint32_t getNumQueues();
			uint32_t getQueueFlags(uint32_t index);
			uint32_t getQueueFamily(uint32_t index);
			
			/// additional extensions
			static void addContextExtension(const char *name);
			static void addAdapterExtension(const char *name);
			
			/// get proc address functions
			static PFN_vkGetInstanceProcAddr getInstanceProcAddress();
			static PFN_vkGetDeviceProcAddr getDeviceProcAddress();
			
			/// Vulkan functions
			static void *getProcAddress(const char *name);
			
			/// check Vulkan errors
			static bool error(uint32_t result);
			
			using Context::create;
	};
	
	/**
	 * GLContext
	 */
	class TS_API GLContext : public Context {
			
			TS_DECLARE_PTR_1(GLContext, Context, 0)
			
		public:
			
			GLContext();
			virtual ~GLContext();
			
			/// create context
			bool create(void *context);
			
			/// current context
			void *getGLDisplay() const;
			void *getGLVisual() const;
			void *getGLConfig() const;
			void *getGLSurface() const;
			void *getGLContext() const;
			
			/// OpenGL functions
			static void *getProcAddress(const char *name);
			
			/// check OpenGL errors
			static bool error(uint32_t result);
			static bool check();
			
			using Context::create;
	};
	
	/**
	 * GLESContext
	 */
	class TS_API GLESContext : public Context {
			
			TS_DECLARE_PTR_1(GLESContext, Context, 0)
			
		public:
			
			GLESContext();
			virtual ~GLESContext();
			
			/// create context
			bool create(void *context);
			
			/// current context
			void *getGLESDisplay() const;
			void *getGLESConfig() const;
			void *getGLESContext() const;
			
			/// OpenGLES functions
			static void *getProcAddress(const char *name);
			
			/// check OpenGLES errors
			static bool error(uint32_t result);
			static bool check();
			
			using Context::create;
	};
	
	/**
	 * CUContext
	 */
	class TS_API CUContext : public Context {
			
			TS_DECLARE_PTR_1(CUContext, Context, 0)
			
		public:
			
			CUContext();
			virtual ~CUContext();
			
			/// current device
			int32_t getDevice() const;
			CUcontext getCUContext() const;
			CUstream getStream() const;
			
			/// Cuda functions
			static void *getProcAddress(const char *name);
			
			/// check Cuda errors
			static bool error(uint32_t result);
	};
	
	/**
	 * HIPContext
	 */
	class TS_API HIPContext : public Context {
			
			TS_DECLARE_PTR_1(HIPContext, Context, 0)
			
		public:
			
			HIPContext();
			virtual ~HIPContext();
			
			/// current device
			int32_t getDevice() const;
			void *getHIPContext() const;
			void *getStream() const;
			
			/// Hip functions
			static void *getProcAddress(const char *name);
			
			/// check Hip errors
			static bool error(uint32_t result);
	};
}

#endif /* __TELLUSIM_PLATFORM_CONTEXT_H__ */
