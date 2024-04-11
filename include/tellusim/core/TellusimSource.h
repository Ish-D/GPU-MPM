// Copyright (C) 2018-2024, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_CORE_SOURCE_H__
#define __TELLUSIM_CORE_SOURCE_H__

#include <core/TellusimStream.h>

/*
 */
namespace Tellusim {
	
	/**
	 * Source class
	 */
	class TS_API Source : public Stream {
			
			TS_DECLARE_PTR(Source, 0)
			
		public:
			
			Source();
			Source(const uint8_t *data, size_t size, const char *name = nullptr);
			virtual ~Source();
			
			/// open/close source
			bool open(const char *name, bool callback = true, bool write = false);
			bool open(const String &name, bool callback = true, bool write = false);
			void close();
			
			/// source name
			void setName(const char *name, size_t offset, size_t size);
			void setName(const String &name, size_t offset, size_t size);
			
			/// source data
			void setData(const uint8_t *data, size_t size, const char *name = nullptr);
			
			/// source utils
			static bool isSource(const char *name);
			static bool isSource(const String &name);
			static uint64_t getMTime(const char *name);
			static size_t getSize(const char *name);
			
			/// source callback
			using IsCallback = bool(const char *name, void *data);
			using OpenCallback = Stream(const char *name, void *data);
			static void setCallback(OpenCallback *open_func, void *data = nullptr);
			static void setCallback(OpenCallback *open_func, IsCallback *is_func, void *data = nullptr);
			static OpenCallback *getOpenCallback();
			static IsCallback *getIsCallback();
			static void *getCallbackData();
			
			using Stream::getSize;
	};
}

#endif /* __TELLUSIM_CORE_SOURCE_H__ */
