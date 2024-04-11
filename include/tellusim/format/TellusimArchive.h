// Copyright (C) 2018-2024, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_FORMAT_ARCHIVE_H__
#define __TELLUSIM_FORMAT_ARCHIVE_H__

#include <core/TellusimStream.h>

/*
 */
namespace Tellusim {
	
	/**
	 * Archive
	 */
	class TS_API Archive {
			
			TS_DECLARE_NONCOPY(Archive, 4)
			
		public:
			
			Archive();
			~Archive();
			
			/// open/close archive
			bool open(const char *name, const char *type = nullptr);
			bool open(const String &name, const char *type = nullptr);
			bool open(Stream &stream, const char *type = nullptr);
			void close();
			
			/// archive status
			bool isOpened() const;
			String getName() const;
			
			/// files list
			uint32_t getNumFiles() const;
			String getFileName(uint32_t index) const;
			uint64_t getFileMTime(uint32_t index) const;
			size_t getFileSize(uint32_t index) const;
			
			/// find file
			uint32_t findFile(const char *name) const;
			uint32_t findFile(const String &name) const;
			bool isFile(const char *name) const;
			bool isFile(const String &name) const;
			
			/// open file
			Stream openFile(const char *name) const;
			Stream openFile(const String &name) const;
			Stream openFile(uint32_t index) const;
	};
	
	/**
	 * ArchiveStream class
	 */
	class TS_API ArchiveStream {
			
			TS_DECLARE_NONCOPY(ArchiveStream, 0)
			
		protected:
			
			ArchiveStream();
			ArchiveStream(const char *name);
			ArchiveStream(const InitializerList<const char*> &names);
			
		public:
			
			virtual ~ArchiveStream();
			
			/// create instance
			virtual ArchiveStream *instance() const = 0;
			virtual void destructor(ArchiveStream *instance) const = 0;
			
			/// open archive
			virtual bool open(Stream &stream) = 0;
			
			/// files list
			virtual uint32_t getNumFiles() const = 0;
			virtual const String &getFileName(uint32_t index) const = 0;
			virtual uint64_t getFileMTime(uint32_t index) const = 0;
			virtual size_t getFileSize(uint32_t index) const = 0;
			
			/// open file
			virtual Stream openFile(uint32_t index) = 0;
			
			/// archive stream formats
			static bool check(const String &name);
			
			/// list of supported formats
			static String getFormats();
	};
}

#endif /* __TELLUSIM_FORMAT_ARCHIVE_H__ */
