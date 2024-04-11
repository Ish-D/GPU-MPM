// Copyright (C) 2018-2024, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

/*
 */
#ifndef __TELLUSIM_APP_H__
#define __TELLUSIM_APP_H__

#include <core/TellusimArray.h>
#include <core/TellusimString.h>
#include <platform/TellusimPlatform.h>

/*
 */
namespace Tellusim {
	
	/**
	 * Application
	 */
	class TS_API App {
			
			TS_DECLARE_NONCOPY(App, 8)
			
		public:
			
			/// Release version
			enum {
				Version_19 = 20221010,
				Version_20 = 20221109,
				Version_21 = 20221122,
				Version_22 = 20221222,
				Version_23 = 20230117,
				Version_24 = 20230217,
				Version_25 = 20230402,
				Version_26 = 20230509,
				Version_27 = 20230612,
				Version_28 = 20230718,
				Version_29 = 20230824,
				Version_30 = 20231029,
				Version_31 = 20231113,
				Version_32 = 20231212,
				Version_33 = 20240116,
				Version_34 = 20240216,
				Version_35 = 20240320,
				Version = Version_35,
			};
			
			App(int32_t argc, char **argv);
			virtual ~App();
			
			/// clear application
			void clear();
			
			/// command line parameters
			Platform getPlatform() const;
			uint32_t getDevice() const;
			uint32_t getWidth() const;
			uint32_t getHeight() const;
			uint32_t getMultisample() const;
			
			/// command line arguments
			uint32_t getNumArguments() const;
			const String &getArgument(uint32_t num) const;
			const Array<String> &getArguments() const;
			
			bool isArgument(const char *name) const;
			const String &getArgument(const char *name) const;
			
			/// create application
			bool create(Platform platform = PlatformUnknown, uint32_t version = Version);
			
			/// default parameters
			static void setPlatform(Platform platform, uint32_t device = Maxu32);
			static void setSize(uint32_t width, uint32_t height, uint32_t multisample = 0);
			
			/// binary info
			static bool isBuildDebug();
			static bool isBuildFloat64();
			static String getBuildDate();
			static String getBuildInfo();
			static uint32_t getVersion();
			static uint64_t getAPIHash();
	};
}

#endif /* __TELLUSIM_APP_H__ */
