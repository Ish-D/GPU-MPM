// Copyright (C) 2018-2024, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_SAMPLE_COMMON_H__
#define __TELLUSIM_SAMPLE_COMMON_H__

#include <TellusimApp.h>
#include <core/TellusimLog.h>
#include <core/TellusimTime.h>
#include <format/TellusimImage.h>
#include <platform/TellusimWindow.h>

#if _WINAPP
	#include <system/TellusimWinApp.h>
	TS_DECLARE_WINAPP_MAIN
#endif
#if _ANDROID
	#include <system/TellusimAndroid.h>
	TS_DECLARE_ANDROID_NATIVE_ACTIVITY
#endif

/*
 */
#if _WIN32
	#define DECLARE_WINDOW_KEYBOARD_PRESSED \
		window.setKeyboardPressedCallback([&](uint32_t key, uint32_t code) { if(key == Window::KeyEsc || (key == Window::KeyF4 && window.getKeyboardKey(Window::KeyAlt))) window.stop(); });
#else
	#define DECLARE_WINDOW_KEYBOARD_PRESSED \
		window.setKeyboardPressedCallback([&](uint32_t key, uint32_t code) { if(key == Window::KeyEsc) window.stop(); });
#endif

#define DECLARE_WINDOW \
	App app(argc, argv); \
	if(!app.create()) return 1; \
	Window window(app.getPlatform(), app.getDevice()); \
	if(!window) return 1; \
	window.setSize(app.getWidth(), app.getHeight()); \
	window.setCloseClickedCallback([&]() { window.stop(); }); \
	DECLARE_WINDOW_KEYBOARD_PRESSED

#define DECLARE_GLOBAL \
	Image window_image; \
	float32_t old_time = 0.0f; \
	float32_t fps_time = 0.0f; \
	float32_t frame_time = 0.0f; \
	uint32_t frame_counter = 0u; \
	uint32_t fps_counter = 0u; \
	TS_UNUSED(old_time);

#define DECLARE_COMMON \
	fps_counter++; \
	frame_counter++; \
	old_time = frame_time; \
	frame_time = (float32_t)Time::seconds(); \
	bool pause = false; \
	bool simulate = true; \
	float32_t fps = 0.0f; \
	float32_t time = frame_time; \
	if(frame_time - fps_time > 1.0f) { \
		fps = fps_counter / (frame_time - fps_time); \
		fps_time = frame_time; \
		fps_counter = 0; \
	} \
	if(!window.getKeyboardKey(Window::KeyCtrl) && !window.getKeyboardKey(Window::KeyAlt) && window.getKeyboardKey(Window::KeyF12, true) && window.grab(window_image)) { \
		String name = window.getTitle().replace(" ", "_").replace("::", "_"); \
		window_image.save(String::format("%s_%u.png", name.get(), frame_counter)); \
	} \
	for(int32_t i = 1; i < argc; i++) { \
		if(!strcmp(argv[i], "-fps") && fps > 0.0f) { \
			TS_LOGF(Message, "%s FPS: %.1f\n", window.getTitle().get(), fps); \
		} \
		else if(!strcmp(argv[i], "-pause")) { \
			old_time = 0.0f; \
			time = 0.0f; \
			pause = true; \
		} \
		else if(i + 1 < argc) { \
			bool done = false; \
			if(!strcmp(argv[i], "-frames") && frame_counter + 60 >= String::tou32(argv[i + 1])) { \
				done |= (frame_counter >= String::tou32(argv[i + 1])); \
				simulate = false; \
				window.finish(); \
			} \
			if(!strcmp(argv[i], "-time") && frame_time + 0.5f >= String::tof32(argv[i + 1])) { \
				done |= (frame_time >= String::tof32(argv[i + 1])); \
				simulate = false; \
				window.finish(); \
			} \
			if(done) { \
				TS_LOGF(Message, "%s Done (Frames: %u FPS: %.1f)\n", window.getTitle().get(), frame_counter, frame_counter / frame_time); \
				for(int32_t j = 1; j < argc; j++) { \
					if(!strcmp(argv[j], "-image") && j + 1 < argc) { \
						if(window.grab(window_image)) window_image.save(argv[j + 1]); \
					} \
				} \
				window.stop(); \
			} \
		} \
	} \
	TS_UNUSED(simulate); \
	TS_UNUSED(pause); \
	TS_UNUSED(time); \
	TS_UNUSED(fps);

#endif /* __TELLUSIM_SAMPLE_COMMON_H__ */
