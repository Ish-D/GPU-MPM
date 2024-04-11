// Copyright (C) 2018-2024, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

/*
 */
#ifndef __TELLUSIM_SYSTEM_WINAPP_H__
#define __TELLUSIM_SYSTEM_WINAPP_H__

#include <core/TellusimString.h>

/*
 */
namespace Tellusim {
	
	/**
	 * WinApp application
	 */
	namespace WinApp {
		
		/// application instance
		TS_API void *getInstance();
		
		/// application show mode
		TS_API int32_t getShowMode();
		
		/// application window
		TS_API void *getWindow();
		
		/// WinApp main
		using Main = int32_t(int32_t argc, char **argv);
		TS_API void main(void *instance, void *prev_instance, wchar_t *command, int32_t show_mode, Main *main);
	}
}

/*
 */
#ifdef DECLARE_HANDLE
	#define TS_HINSTANCE
#else
	#define TS_HINSTANCE struct HINSTANCE__ { int32_t unused; }; typedef HINSTANCE__ *HINSTANCE;
#endif
#define TS_DECLARE_WINAPP_MAIN TS_HINSTANCE \
extern int32_t main(int32_t argc, char **argv); \
int32_t __stdcall wWinMain(HINSTANCE instance, HINSTANCE prev_instance, wchar_t *command, int32_t show_mode) { \
	Tellusim::WinApp::main((void*)instance, (void*)prev_instance, command, show_mode, ::main); \
}

#endif /* __TELLUSIM_SYSTEM_WINAPP_H__ */
