// Copyright (C) 2018-2024, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_PLATFORM_BUFFER_H__
#define __TELLUSIM_PLATFORM_BUFFER_H__

#include <TellusimFormat.h>
#include <core/TellusimArray.h>
#include <platform/TellusimPlatform.h>

/*
 */
namespace Tellusim {
	
	/* Prototypes
	 */
	class String;
	
	/**
	 * Buffer class
	 */
	class TS_API Buffer {
			
			TS_DECLARE_PTR(Buffer, 0)
			
		public:
			
			/// Buffer flags
			enum Flags {
				FlagNone = 0,
				FlagRead			= (1 << 0),		// read buffer
				FlagWrite			= (1 << 1),		// write buffer
				FlagSource			= (1 << 2),		// source buffer
				FlagSparse			= (1 << 3),		// sparse buffer
				FlagShared			= (1 << 4),		// shared buffer
				FlagMapped			= (1 << 5),		// mapped buffer
				FlagExtern			= (1 << 6),		// extern buffer
				FlagInterop			= (1 << 7),		// interop buffer
				FlagDynamic			= (1 << 8),		// dynamic buffer
				FlagUniform			= (1 << 9),		// uniform buffer
				FlagStorage			= (1 << 10),	// storage buffer
				FlagAddress			= (1 << 11),	// address buffer
				FlagTracing			= (1 << 12),	// tracing buffer
				FlagScratch			= (1 << 13),	// scratch buffer
				FlagBinding			= (1 << 14),	// binding buffer
				FlagIndirect		= (1 << 15),	// indirect buffer
				FlagConditional		= (1 << 16),	// conditional buffer
				FlagVertex			= (1 << 17),	// vertex buffer
				FlagIndex			= (1 << 18),	// index buffer
				FlagTexel			= (1 << 19),	// texel buffer
				FlagAccel			= (1 << 20),	// accel buffer
				DefaultFlags		= FlagNone,
				NumFlags = 21,
			};
			
			Buffer();
			virtual ~Buffer();
			
			/// buffer platform
			Platform getPlatform() const;
			
			TS_INLINE const char *getPlatformName() const { return Tellusim::getPlatformName(getPlatform()); }
			
			/// buffer device index
			uint32_t getIndex() const;
			
			/// clear buffer
			void clear();
			
			/// check buffer
			bool isCreated() const;
			
			/// buffer name
			void setName(const char *name);
			String getName() const;
			
			/// create buffer
			bool create(Flags flags, size_t size, Format format = FormatUnknown);
			
			bool isMapped() const;
			
			/// buffer flags
			Flags getFlags() const;
			
			TS_INLINE bool hasFlag(Flags flags) const { return ((getFlags() & flags) != FlagNone); }
			TS_INLINE bool hasFlags(Flags flags) const { return ((getFlags() & flags) == flags); }
			
			String getFlagsName() const;
			
			/// buffer format
			Format getFormat() const;
			
			TS_INLINE const char *getFormatName() const { return Tellusim::getFormatName(getFormat()); }
			
			TS_INLINE uint32_t getComponents() const { return getFormatComponents(getFormat()); }
			TS_INLINE uint32_t getPixelSize() const { return getFormatPixelSize(getFormat()); }
			
			/// buffer size
			size_t getSize();
			
			/// sparse buffer page size
			size_t getPageSize();
			
			/// buffer description
			String getDescription() const;
	};
	
	/**
	 * D3D12Buffer
	 */
	class TS_API D3D12Buffer : public Buffer {
			
			TS_DECLARE_PTR_1(D3D12Buffer, Buffer, 0)
			
		public:
			
			D3D12Buffer();
			virtual ~D3D12Buffer();
			
			/// create external buffer
			bool create(Flags flags, ID3D12Resource *buffer, uint32_t state);
			
			ID3D12Resource *getD3D12Buffer() const;
			size_t getUnorderedAccessView() const;
			size_t getShaderResourceView() const;
			uint64_t getBufferAddress() const;
			
			void setBufferState(uint32_t state);
			uint32_t getBufferState() const;
			
			void *getSharedHandle() const;
			void *getInteropHandle() const;
			
			using Buffer::create;
	};
	
	/**
	 * D3D11Buffer
	 */
	class TS_API D3D11Buffer : public Buffer {
			
			TS_DECLARE_PTR_1(D3D11Buffer, Buffer, 0)
			
		public:
			
			D3D11Buffer();
			virtual ~D3D11Buffer();
			
			/// create external buffer
			bool create(Flags flags, ID3D11Buffer *buffer);
			
			ID3D11Buffer *getD3D11Buffer() const;
			ID3D11UnorderedAccessView *getUnorderedAccessView() const;
			ID3D11ShaderResourceView *getShaderResourceView() const;
			
			void *getInteropHandle() const;
			
			using Buffer::create;
	};
	
	/**
	 * MTLBuffer
	 */
	class TS_API MTLBuffer : public Buffer {
			
			TS_DECLARE_PTR_1(MTLBuffer, Buffer, 0)
			
		public:
			
			MTLBuffer();
			virtual ~MTLBuffer();
			
			/// create external buffer
			bool create(Flags flags, void *buffer);
			
			void *getMTLBuffer() const;
			
			void *getSharedPtr() const;
			
			using Buffer::create;
	};
	
	/**
	 * VKBuffer
	 */
	class TS_API VKBuffer : public Buffer {
			
			TS_DECLARE_PTR_1(VKBuffer, Buffer, 0)
			
		public:
			
			VKBuffer();
			virtual ~VKBuffer();
			
			/// create external buffer
			bool create(Flags flags, size_t size, VkBuffer buffer, uint32_t access);
			
			VkBuffer getVKBuffer() const;
			VkBufferView getBufferView() const;
			uint64_t getBufferAddress() const;
			
			void setBufferAccess(uint32_t access);
			uint32_t getBufferAccess() const;
			
			void *getSharedPtr() const;
			void *getInteropHandle() const;
			
			using Buffer::create;
	};
	
	/**
	 * GLBuffer
	 */
	class TS_API GLBuffer : public Buffer {
			
			TS_DECLARE_PTR_1(GLBuffer, Buffer, 0)
			
		public:
			
			GLBuffer();
			virtual ~GLBuffer();
			
			/// create external buffer
			bool create(Flags flags, uint32_t target, uint32_t buffer_id);
			
			uint32_t getTarget() const;
			uint32_t getBufferID() const;
			
			using Buffer::create;
	};
	
	/**
	 * GLESBuffer
	 */
	class TS_API GLESBuffer : public Buffer {
			
			TS_DECLARE_PTR_1(GLESBuffer, Buffer, 0)
			
		public:
			
			GLESBuffer();
			virtual ~GLESBuffer();
			
			/// create external buffer
			bool create(Flags flags, uint32_t target, uint32_t buffer_id);
			
			uint32_t getTarget() const;
			uint32_t getBufferID() const;
			
			using Buffer::create;
	};
	
	/**
	 * CUBuffer
	 */
	class TS_API CUBuffer : public Buffer {
			
			TS_DECLARE_PTR_1(CUBuffer, Buffer, 0)
			
		public:
			
			CUBuffer();
			virtual ~CUBuffer();
			
			size_t getBufferPtr() const;
			uint8_t *getBufferData() const;
			CUevent getBufferEvent() const;
			uint32_t getArrayFormat() const;
			uint32_t getArrayChannels() const;
			CUexternalMemory getSharedMemory() const;
	};
	
	/**
	 * HIPBuffer
	 */
	class TS_API HIPBuffer : public Buffer {
			
			TS_DECLARE_PTR_1(HIPBuffer, Buffer, 0)
			
		public:
			
			HIPBuffer();
			virtual ~HIPBuffer();
			
			void *getBufferPtr() const;
			uint8_t *getBufferData() const;
			void *getBufferEvent() const;
			uint32_t getArrayFormat() const;
			uint32_t getArrayChannels() const;
			void *getSharedMemory() const;
	};
	
	/**
	 * FUBuffer
	 */
	class TS_API FUBuffer : public Buffer {
			
			TS_DECLARE_PTR_1(FUBuffer, Buffer, 0)
			
		public:
			
			FUBuffer();
			explicit FUBuffer(const Array<Buffer> &buffers, bool owner = false);
			virtual ~FUBuffer();
			
			/// device mask
			void setMask(uint32_t mask);
			uint32_t getMask() const;
			
			/// Fusion buffers
			uint32_t getNumBuffers() const;
			const Buffer getBuffer(uint32_t index) const;
			Buffer getBuffer(uint32_t index);
	};
	
	/*
	 */
	TS_DECLARE_ENUM_OP(Buffer::Flags)
}

#endif /* __TELLUSIM_PLATFORM_BUFFER_H__ */
