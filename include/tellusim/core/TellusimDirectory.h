// Copyright (C) 2018-2024, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_CORE_DIRECTORY_H__
#define __TELLUSIM_CORE_DIRECTORY_H__

#include <core/TellusimArray.h>
#include <core/TellusimString.h>

/*
 */
namespace Tellusim {
	
	/**
	 * Directory class
	 */
	class TS_API Directory {
			
			TS_DECLARE_PTR(Directory, 0)
			
		public:
			
			Directory();
			~Directory();
			
			/// open/close directory
			bool open(const char *name, bool children = false);
			bool open(const String &name, bool children = false);
			void close();
			
			/// directory status
			bool isOpened() const;
			String getName() const;
			
			/// attributes
			enum Attributes {
				AttributeNone = 0,
				AttributeRead		= (1 << 0),		// read access
				AttributeWrite		= (1 << 1),		// write access
				AttributeHidden		= (1 << 2),		// hidden flag
				AttributeExecute	= (1 << 3),		// execute flag
				AttributeTemporary	= (1 << 4),		// temporary flag
				NumAttributes = 5,
			};
			
			/// files
			uint32_t getNumFiles() const;
			String getFileName(uint32_t index) const;
			Attributes getFileAttributes(uint32_t index) const;
			uint64_t getFileMTime(uint32_t index) const;
			uint64_t getFileATime(uint32_t index) const;
			uint64_t getFileCTime(uint32_t index) const;
			size_t getFileSize(uint32_t index) const;
			const Array<String> getFiles() const;
			
			/// directories
			uint32_t getNumDirectories() const;
			String getDirectoryName(uint32_t index) const;
			Attributes getDirectoryAttributes(uint32_t index) const;
			uint64_t getDirectoryCTime(uint32_t index) const;
			uint32_t getDirectorySize(uint32_t index) const;
			const Array<String> getDirectories() const;
			
			/// file utils
			static bool isFile(const char *name);
			static bool isFile(const String &name);
			static bool setFileAttributes(const char *name, Attributes attributes);
			static Attributes getFileAttributes(const char *name);
			static bool setFileMTime(const char *name, uint64_t time);
			static uint64_t getFileMTime(const char *name);
			static uint64_t getFileATime(const char *name);
			static uint64_t getFileCTime(const char *name);
			static size_t getFileSize(const char *name);
			static bool removeFile(const char *name);
			
			/// directory utils
			static bool isDirectory(const char *name);
			static bool isDirectory(const String &name);
			static bool changeDirectory(const char *name);
			static bool changeDirectory(const String &name);
			static bool createDirectory(const char *name, bool children = false);
			static bool createDirectory(const String &name, bool children = false);
			static bool removeDirectory(const char *name, bool children = false);
			static bool removeDirectory(const String &name, bool children = false);
			static bool rename(const char *name, const char *new_name);
			
			/// common directories
			static String getCurrentDirectory();
			static String getHomeDirectory();
			static String getTempDirectory();
			static String getConfigDirectory();
			static String getDocumentsDirectory();
			
			/// drive utils
			static const Array<String> getDriveNames();
	};
	
	/*
	 */
	TS_DECLARE_ENUM_OP(Directory::Attributes)
}

#endif /* __TELLUSIM_CORE_DIRECTORY_H__ */
