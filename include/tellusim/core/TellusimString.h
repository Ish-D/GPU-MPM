// Copyright (C) 2018-2024, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_CORE_STRING_H__
#define __TELLUSIM_CORE_STRING_H__

#include <TellusimBase.h>

/*
 */
namespace Tellusim {
	
	/**
	 * String class
	 */
	class TS_API String {
			
			TS_DECLARE_COPY(String, 4)
			
		public:
			
			String();
			explicit String(uint32_t size, char c = 0);
			explicit String(const char *str, uint32_t length = Maxu32);
			explicit String(const wchar_t *str, uint32_t length = Maxu32);
			explicit String(const uint32_t *str, uint32_t length = Maxu32);
			~String();
			
			/// resize string
			String &reserve(uint32_t size, bool discard = false);
			String &resize(uint32_t size, char c = 0, bool reserve = false);
			
			/// clear string
			void release();
			void clear();
			
			/// copy string
			void copy(const char *str, uint32_t length = Maxu32);
			void copy(const wchar_t *str, uint32_t length = Maxu32);
			void copy(const uint32_t *str, uint32_t length = Maxu32);
			void copy(const String &string, uint32_t length = Maxu32);
			
			String &operator=(const char *str);
			
			/// append string
			String &append(char c);
			String &append(const char *str, uint32_t length = Maxu32);
			String &append(const String &string, uint32_t length = Maxu32);
			
			String &operator+=(char c);
			String &operator+=(const char *str);
			String &operator+=(const String &string);
			
			/// insert string
			String &insert(uint32_t pos, const char *str, uint32_t length = Maxu32);
			String &insert(uint32_t pos, const String &string, uint32_t length = Maxu32);
			
			/// remove string
			String &removeBack(uint32_t length = 1);
			String &remove(uint32_t pos, uint32_t length = 1);
			
			/// reverse string
			String &reverse(uint32_t pos = 0, uint32_t length = Maxu32);
			
			/// string info
			uint32_t size() const;
			TS_INLINE bool empty() const { return (size() == 0); }
			explicit TS_INLINE operator bool() const { return (size() != 0); }
			
			/// string data
			char *get();
			const char *get() const;
			char &get(uint32_t index);
			char get(uint32_t index) const;
			TS_INLINE char &operator[](uint32_t index) { return get(index); }
			TS_INLINE char operator[](uint32_t index) const { return get(index); }
			
			/// find ascii character
			uint32_t find(char c, uint32_t pos = 0) const;
			uint32_t rfind(char c, uint32_t pos = Maxu32) const;
			uint32_t count(char c, uint32_t pos = 0) const;
			
			/// find part of the string
			uint32_t find(const char *str, uint32_t pos = 0) const;
			uint32_t rfind(const char *str, uint32_t pos = Maxu32) const;
			uint32_t count(const char *str, uint32_t pos = 0) const;
			
			/// compare begin of the string
			bool begins(const char *str, uint32_t length = Maxu32, uint32_t pos = 0) const;
			
			/// contains the string
			bool contains(const char *str, uint32_t length = Maxu32, uint32_t pos = 0) const;
			
			/// compare strings
			int32_t compare(const char *str, uint32_t pos = 0) const;
			
			/// distance between strings
			uint32_t distance(const char *str, bool scan = false, uint32_t pos = 0) const;
			
			/// string iterators
			const char *begin() const;
			const char *end() const;
			
			/// string elements
			char front(uint32_t index = 0) const;
			char back(uint32_t index = 0) const;
			char &front(uint32_t index = 0);
			char &back(uint32_t index = 0);
			
			/// return part of the string
			String substring(uint32_t pos, uint32_t length = Maxu32) const;
			
			/// replace part of the string
			String replace(char before, char after, uint32_t pos = 0) const;
			String replace(const char *before, const char *after, uint32_t pos = 0) const;
			
			/// file name utils
			String extension(const char *extension) const;
			String extension() const;
			String pathname() const;
			String basename() const;
			String dirname() const;
			
			/// relative file name
			static String relname(const char *path, const char *str);
			
			/// convert string case
			String capitalize(const char *delimiters = nullptr, const char *spaces = nullptr) const;
			String lower() const;
			String upper() const;
			
			/// string to unicode
			static uint32_t toUtf32(const char *str, uint32_t &code);
			uint32_t toUtf16(wchar_t *d, uint32_t length) const;
			uint32_t toUtf32(uint32_t *d, uint32_t length) const;
			
			/// unicode to string
			static uint32_t fromUtf32(String &d, uint32_t code);
			static String fromUtf16(const wchar_t *str, uint32_t length = Maxu32);
			static String fromUtf32(const uint32_t *str, uint32_t length = Maxu32);
			
			/// url to string
			static String fromUrl(const char *str, uint32_t length = Maxu32);
			
			/// string scan function
			uint32_t vscanf(const char *format, va_list args) const;
			uint32_t scanf(const char *format, ...) const TS_SCANF(2, 3);
			
			/// string printf function
			String &vprintf(const char *format, va_list args);
			String &printf(const char *format, ...) TS_PRINTF(2, 3);
			
			/// string format function
			static String vformat(const char *format, va_list args);
			static String format(const char *format, ...) TS_PRINTF(1, 2);
			
			/// value to string
			static String &fromi32(String &d, int32_t value, uint32_t radix = 10);
			static String &fromi64(String &d, int64_t value, uint32_t radix = 10);
			static String &fromu32(String &d, uint32_t value, uint32_t radix = 10);
			static String &fromu64(String &d, uint64_t value, uint32_t radix = 10);
			static String &fromf32(String &d, float32_t value, uint32_t digits = 6, bool compact = false, bool exponent = false);
			static String &fromf64(String &d, float64_t value, uint32_t digits = 12, bool compact = false, bool exponent = false);
			
			static String fromi32(int32_t value, uint32_t radix = 10);
			static String fromi64(int64_t value, uint32_t radix = 10);
			static String fromu32(uint32_t value, uint32_t radix = 10);
			static String fromu64(uint64_t value, uint32_t radix = 10);
			static String fromf32(float32_t value, uint32_t digits = 6, bool compact = false, bool exponent = false);
			static String fromf64(float64_t value, uint32_t digits = 12, bool compact = false, bool exponent = false);
			
			/// string to value
			static int32_t toi32(const char *str, uint32_t radix = 10, uint32_t *size = nullptr);
			static int64_t toi64(const char *str, uint32_t radix = 10, uint32_t *size = nullptr);
			static uint32_t tou32(const char *str, uint32_t radix = 10, uint32_t *size = nullptr);
			static uint64_t tou64(const char *str, uint32_t radix = 10, uint32_t *size = nullptr);
			static TS_INLINE int32_t toi32(const char *str, uint32_t *size) { return toi32(str, 10, size); }
			static TS_INLINE int64_t toi64(const char *str, uint32_t *size) { return toi64(str, 10, size); }
			static TS_INLINE uint32_t tou32(const char *str, uint32_t *size) { return tou32(str, 10, size); }
			static TS_INLINE uint64_t tou64(const char *str, uint32_t *size) { return tou64(str, 10, size); }
			static float32_t tof32(const char *str, uint32_t *size = nullptr);
			static float64_t tof64(const char *str, uint32_t *size = nullptr);
			
			int32_t toi32(uint32_t radix = 10, uint32_t pos = 0) const;
			int64_t toi64(uint32_t radix = 10, uint32_t pos = 0) const;
			uint32_t tou32(uint32_t radix = 10, uint32_t pos = 0) const;
			uint64_t tou64(uint32_t radix = 10, uint32_t pos = 0) const;
			float32_t tof32(uint32_t pos = 0) const;
			float64_t tof64(uint32_t pos = 0) const;
			
			/// string to hash value
			uint32_t toHashu32(uint32_t pos = 0) const;
			uint64_t toHashu64(uint32_t pos = 0) const;
			
			/// string to color value
			uint32_t toRGBAu8(uint32_t pos = 0) const;
			
			/// value convertors
			static String fromTime(uint64_t usec, uint32_t digits = 2);
			static String fromBytes(uint64_t bytes, uint32_t digits = 2);
			static String fromNumber(uint64_t value, uint32_t digits = 2);
			static String fromFrequency(uint64_t hz, uint32_t digits = 2);
			static String fromLength(float64_t distance, uint32_t digits = 2);
			static String fromAngle(float64_t angle, uint32_t digits = 2);
			
			static uint64_t toBytes(const char *str, uint32_t *size = nullptr);
			static uint64_t toNumber(const char *str, uint32_t *size = nullptr);
			static uint64_t toFrequency(const char *str, uint32_t *size = nullptr);
			static float64_t toLength(const char *str, uint32_t *size = nullptr);
			
			uint64_t toBytes(uint32_t pos = 0, uint32_t *size = nullptr) const;
			uint64_t toNumber(uint32_t pos = 0, uint32_t *size = nullptr) const;
			uint64_t toFrequency(uint32_t pos = 0, uint32_t *size = nullptr) const;
			float64_t toLength(uint32_t pos = 0, uint32_t *size = nullptr) const;
			
			/// empty string
			static const String null;
	};
	
	/**
	 * String operators
	 */
	TS_API String operator+(const String &s0, const char *s1);
	TS_API String operator+(const char *s0, const String &s1);
	TS_API String operator+(const String &s0, const String &s1);
	
	TS_API bool operator==(const String &s0, const char *s1);
	TS_API bool operator==(const char *s0, const String &s1);
	TS_API bool operator==(const String &s0, const String &s1);
	
	TS_API bool operator!=(const String &s0, const char *s1);
	TS_API bool operator!=(const char *s0, const String &s1);
	TS_API bool operator!=(const String &s0, const String &s1);
	
	TS_API bool operator<(const String &s0, const char *s1);
	TS_API bool operator<(const char *s0, const String &s1);
	TS_API bool operator<(const String &s0, const String &s1);
	
	TS_API bool operator>(const String &s0, const char *s1);
	TS_API bool operator>(const char *s0, const String &s1);
	TS_API bool operator>(const String &s0, const String &s1);
}

#endif /* __TELLUSIM_CORE_STRING_H__ */
