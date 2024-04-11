// Copyright (C) 2018-2024, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_CORE_SYSTEM_H__
#define __TELLUSIM_CORE_SYSTEM_H__

#include <core/TellusimString.h>

/*
 */
namespace Tellusim {
	
	/**
	 * System utils
	 */
	namespace System {
		
		/**
		 * Thread identifier
		 */
		TS_API uint32_t getThreadID();
		
		/**
		 * Environment variables
		 */
		TS_API bool setEnvironment(const char *name, const char *value);
		TS_API bool setEnvironment(const String &name, const char *value);
		TS_API String getEnvironment(const char *name);
		TS_API String getEnvironment(const String &name);
		
		/**
		 * Dynamic libraries
		 */
		TS_API void *loadLibrary(const char *name);
		TS_API void *loadLibrary(const String &name);
		TS_API void *getFunction(void *handle, const char *name);
		TS_API void *getFunction(void *handle, const String &name);
		TS_API void closeLibrary(void *handle);
		
		/**
		 * Execute command
		 */
		TS_API bool exec(const char *command, bool wait = false);
		TS_API bool exec(const String &command, bool wait = false);
		
		/**
		 * Open resource
		 */
		TS_API bool open(const char *command);
		TS_API bool open(const String &command);
	}
	
	/**
	 * System Info
	 */
	class TS_API Info {
			
			TS_DECLARE_PTR(Info, 0)
			
		public:
			
			Info();
			~Info();
			
			/// System info
			size_t getSystemMemory() const;
			uint64_t getSystemUptime() const;
			String getSystemName() const;
			String getSystemVersion() const;
			String getKernelVersion() const;
			
			/// CPU info
			uint32_t getCPUCount() const;
			String getCPUName(uint32_t index) const;
			String getCPUVendor(uint32_t index) const;
			uint32_t getCPUCores(uint32_t index) const;
			uint32_t getCPUThreads(uint32_t index) const;
			uint64_t getCPUFrequency(uint32_t index) const;
			uint32_t getCPUTemperature(uint32_t index) const;
			uint32_t getCPUUtilization(uint32_t index) const;
			uint32_t getCPUFanSpeed(uint32_t index) const;
			uint32_t getCPUPower(uint32_t index) const;
			
			/// GPU info
			uint32_t getGPUCount() const;
			String getGPUName(uint32_t index) const;
			String getGPUVendor(uint32_t index) const;
			String getGPUSerial(uint32_t index) const;
			String getGPUDevice(uint32_t index) const;
			String getGPUVersion(uint32_t index) const;
			size_t getGPUMemory(uint32_t index) const;
			uint32_t getGPUScreens(uint32_t index) const;
			uint64_t getGPUFrequency(uint32_t index) const;
			uint32_t getGPUTemperature(uint32_t index) const;
			uint32_t getGPUUtilization(uint32_t index) const;
			uint32_t getGPUFanSpeed(uint32_t index) const;
			uint32_t getGPUPower(uint32_t index) const;
			bool isGPUThrottling(uint32_t index) const;
	};
}

#endif /* __TELLUSIM_CORE_SYSTEM_H__ */
