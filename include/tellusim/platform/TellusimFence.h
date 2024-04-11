// Copyright (C) 2018-2024, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_PLATFORM_FENCE_H__
#define __TELLUSIM_PLATFORM_FENCE_H__

#include <core/TellusimArray.h>
#include <platform/TellusimPlatform.h>

/*
 */
namespace Tellusim {
	
	/* Prototypes
	 */
	class String;
	
	/**
	 * Fence class
	 */
	class TS_API Fence {
			
			TS_DECLARE_PTR(Fence, 0)
			
		public:
			
			/// Fence flags
			enum Flags {
				FlagNone = 0,
				FlagSemaphore	= (1 << 0),		// semaphore fence
				FlagSignaled	= (1 << 1),		// signaled state
				FlagShared		= (1 << 2),		// shared fence
				FlagExtern		= (1 << 3),		// extern fence
				DefaultFlags	= FlagNone,
				NumFlags = 4,
			};
			
			Fence();
			virtual ~Fence();
			
			/// fence platform
			Platform getPlatform() const;
			
			TS_INLINE const char *getPlatformName() const { return Tellusim::getPlatformName(getPlatform()); }
			
			/// fence device index
			uint32_t getIndex() const;
			
			/// clear fence
			void clear();
			
			/// check fence
			bool isCreated() const;
			
			/// create fence
			bool create(Flags flags = DefaultFlags);
			
			/// fence flags
			Flags getFlags() const;
			
			TS_INLINE bool hasFlag(Flags flags) const { return ((getFlags() & flags) != FlagNone); }
			TS_INLINE bool hasFlags(Flags flags) const { return ((getFlags() & flags) == flags); }
			
			String getFlagsName() const;
			
			/// fence description
			String getDescription() const;
	};
	
	/**
	 * VKFence
	 */
	class TS_API VKFence : public Fence {
			
			TS_DECLARE_PTR_1(VKFence, Fence, 0)
			
		public:
			
			VKFence();
			virtual ~VKFence();
			
			VkFence getVKFence() const;
			VkSemaphore getSemaphore() const;
			
			void *getSharedHandle() const;
	};
	
	/**
	 * FUFence
	 */
	class TS_API FUFence : public Fence {
			
			TS_DECLARE_PTR_1(FUFence, Fence, 0)
			
		public:
			
			FUFence();
			explicit FUFence(const Array<Fence> &fences, bool owner = false);
			virtual ~FUFence();
			
			/// device mask
			void setMask(uint32_t mask);
			uint32_t getMask() const;
			
			/// Fusion fences
			uint32_t getNumFences() const;
			const Fence getFence(uint32_t index) const;
			Fence getFence(uint32_t index);
	};
	
	/*
	 */
	TS_DECLARE_ENUM_OP(Fence::Flags)
}

#endif /* __TELLUSIM_PLATFORM_FENCE_H__ */
