// Copyright (C) 2018-2024, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

/*
 */
#ifndef __TELLUSIM_PLATFORM_H__
#define __TELLUSIM_PLATFORM_H__

#include <TellusimBase.h>

/*
 */
namespace Tellusim {
	
	/**
	 * Vendor PCI ID
	 */
	enum Vendor {
		VendorARM = 0x13b5,
		VendorAMD = 0x1002,
		VendorApple = 0x106b,
		VendorIntel = 0x8086,
		VendorNvidia = 0x10de,
		VendorQualcomm = 0x5143,
	};
	
	/**
	 * Platform types
	 */
	enum Platform {
		PlatformUnknown = 0,
		PlatformFusion,
		PlatformD3D12,
		PlatformD3D11,
		PlatformMTL,
		PlatformVK,
		PlatformGL,
		PlatformGLES,
		PlatformWG,
		PlatformCU,
		PlatformHIP,
		PlatformAny,
		NumPlatforms,
	};
	
	/**
	 * Platform name
	 */
	TS_API const char *getPlatformName(Platform platform);
	TS_API Platform findPlatformName(const char *name);
	
	/**
	 * Check platform
	 */
	TS_API bool isPlatformAvailable(Platform platform);
}

/**
 * Direct3D12 prototypes
 */
typedef struct IDXGIFactory4 IDXGIFactory4;
typedef struct ID3D12Device ID3D12Device;
typedef struct ID3D12CommandQueue ID3D12CommandQueue;
typedef struct ID3D12GraphicsCommandList ID3D12GraphicsCommandList;
typedef struct ID3D12Resource ID3D12Resource;

/**
 * Direct3D11 prototypes
 */
typedef struct IDXGIFactory IDXGIFactory;
typedef struct ID3D11Device ID3D11Device;
typedef struct ID3D11DeviceContext ID3D11DeviceContext;
typedef struct ID3D11Buffer ID3D11Buffer;
typedef struct ID3D11Texture2D ID3D11Texture2D;
typedef struct ID3D11RenderTargetView ID3D11RenderTargetView;
typedef struct ID3D11DepthStencilView ID3D11DepthStencilView;
typedef struct ID3D11ShaderResourceView ID3D11ShaderResourceView;
typedef struct ID3D11UnorderedAccessView ID3D11UnorderedAccessView;

/**
 * Vulkan prototypes
 */
typedef struct VkInstance_T *VkInstance;
typedef struct VkPhysicalDevice_T *VkPhysicalDevice;
typedef struct VkDevice_T *VkDevice;
typedef struct VkQueue_T *VkQueue;
typedef struct VkCommandBuffer_T *VkCommandBuffer;

#if TS_X64 || TS_ARM64
	typedef struct VkShaderModule_T *VkShaderModule;
	typedef struct VkDescriptorSet_T *VkDescriptorSet;
	typedef struct VkRenderPass_T *VkRenderPass;
	typedef struct VkFramebuffer_T *VkFramebuffer;
	typedef struct VkFence_T *VkFence;
	typedef struct VkSemaphore_T *VkSemaphore;
	typedef struct VkImage_T *VkImage;
	typedef struct VkImageView_T *VkImageView;
	typedef struct VkBuffer_T *VkBuffer;
	typedef struct VkBufferView_T *VkBufferView;
	typedef struct VkAccelerationStructureKHR_T *VkAccelerationStructureKHR;
#else
	typedef uint64_t VkShaderModule;
	typedef uint64_t VkDescriptorSet;
	typedef uint64_t VkRenderPass;
	typedef uint64_t VkFramebuffer;
	typedef uint64_t VkFence;
	typedef uint64_t VkSemaphore;
	typedef uint64_t VkImage;
	typedef uint64_t VkImageView;
	typedef uint64_t VkBuffer;
	typedef uint64_t VkBufferView;
	typedef uint64_t VkAccelerationStructureKHR;
#endif

#if _WIN32
	#define TS_VKAPI __stdcall
#else
	#define TS_VKAPI
#endif
typedef void (TS_VKAPI *PFN_vkVoidFunction)(void);
typedef PFN_vkVoidFunction (TS_VKAPI *PFN_vkGetInstanceProcAddr)(VkInstance instance, const char *name);
typedef PFN_vkVoidFunction (TS_VKAPI *PFN_vkGetDeviceProcAddr)(VkDevice device, const char *name);

/**
 * Cuda prototypes
 */
typedef struct CUctx_st *CUcontext;
typedef struct CUmod_st *CUmodule;
typedef struct CUfunc_st *CUfunction;
typedef struct CUevent_st *CUevent;
typedef struct CUstream_st *CUstream;
typedef struct CUarray_st *CUarray;
typedef struct CUmipmappedArray_st *CUmipmappedArray;
typedef struct CUextMemory_st *CUexternalMemory;

#endif /* __TELLUSIM_PLATFORM_H__ */
