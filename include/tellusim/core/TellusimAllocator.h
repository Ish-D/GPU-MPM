// Copyright (C) 2018-2024, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_CORE_ALLOCATOR_H__
#define __TELLUSIM_CORE_ALLOCATOR_H__

#include <new>

#include <TellusimBase.h>

/*
 */
namespace Tellusim {
	
	/**
	 * Memory allocator
	 */
	namespace Allocator {
		
		/// raw allocation
		TS_API void *allocate(size_t size);
		TS_API void *reallocate(void *ptr, size_t old_size, size_t new_size);
		TS_API void free(const void *ptr, size_t size);
		
		/// object allocation
		template <class Type> static Type *allocate() {
			Type *ptr = (Type*)allocate(sizeof(Type));
			if(ptr == nullptr) return nullptr;
			return new(ptr) Type();
		}
		template <class Type> static void freeObject(Type *ptr) {
			if(ptr == nullptr) return;
			ptr->~Type();
			free(ptr, sizeof(Type));
		}
		
		/// array allocation
		template <class Type> static Type *allocate(size_t size) {
			if(size == 0) return nullptr;
			Type *ptr = (Type*)allocate(sizeof(Type) * size);
			if(ptr == nullptr) return nullptr;
			if(!IsPod<Type>::Result) {
				#if _WIN32
					for(size_t i = 0; i < size; i++) {
						new(ptr + i) Type();
					}
					return ptr;
				#else
					return new(ptr) Type[size];
				#endif
			}
			return ptr;
		}
		template <class Type> static void freeArray(Type *ptr, size_t size) {
			if(ptr == nullptr) return;
			if(!IsPod<Type>::Result) {
				for(size_t i = 0; i < size; i++) {
					ptr[i].~Type();
				}
			}
			free(ptr, sizeof(Type) * size);
		}
		
		/// memory statistics
		TS_API size_t getMemory();
		TS_API size_t getAllocations();
	}
}

#endif /* __TELLUSIM_CORE_ALLOCATOR_H__ */
