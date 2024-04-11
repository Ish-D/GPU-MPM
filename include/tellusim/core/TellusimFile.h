// Copyright (C) 2018-2024, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_CORE_FILE_H__
#define __TELLUSIM_CORE_FILE_H__

#include <core/TellusimStream.h>

/*
 */
namespace Tellusim {
	
	/**
	 * File class
	 */
	class TS_API File : public Stream {
			
			TS_DECLARE_PTR(File, 0)
			
		public:
			
			File();
			virtual ~File();
			
			/// open/close file
			bool open(const char *name, const char *mode);
			bool open(const String &name, const char *mode);
			bool open(int32_t fd, const char *name, const char *mode);
			bool popen(const char *command, const char *mode);
			bool popen(const String &command, const char *mode);
			void close();
			
			/// file utils
			static bool isFile(const char *name);
			static bool isFile(const String &name);
			static uint64_t getMTime(const char *name);
			static size_t getSize(const char *name);
			static bool remove(const char *name);
			
			using Stream::getSize;
	};
}

#endif /* __TELLUSIM_CORE_FILE_H__ */
