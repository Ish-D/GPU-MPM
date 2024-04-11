// Copyright (C) 2018-2024, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_CORE_TIME_H__
#define __TELLUSIM_CORE_TIME_H__

#include <core/TellusimString.h>

/*
 */
namespace Tellusim {
	
	/**
	 * Time utils
	 */
	namespace Time {
		
		enum {
			Seconds = 1000000u,
			MSeconds = 1000u,
			USeconds = 1u,
		};
		
		/// current system time in microseconds
		TS_API uint64_t current();
		
		/// current process time in seconds
		TS_API float64_t seconds();
		
		/// sleep process in microseconds
		TS_API void sleep(uint32_t usec);
	}
	
	/**
	 * Date class
	 */
	class TS_API Date {
			
			TS_DECLARE_PTR(Date, 0)
			
		public:
			
			Date();
			explicit Date(int64_t time, bool local = true);
			explicit Date(const char *str, const char *format = nullptr);
			~Date();
			
			/// clear date
			void clear();
			
			/// time in seconds since 1970-01-01 00:00:00
			void setTime(int64_t time, bool local = true);
			int64_t getTime(bool local = true) const;
			
			/// string time value
			/// \param format Default time format is yyyy-MM-dd HH:mm:ss
			bool setString(const char *str, const char *format = nullptr);
			String getString(const char *format = nullptr) const;
			
			/// current date
			void setYear(uint32_t year);
			void setMonth(uint32_t month);
			void setDate(uint32_t date);
			void setDay(uint32_t day);
			void setHours(uint32_t hours);
			void setMinutes(uint32_t minutes);
			void setSeconds(uint32_t seconds);
			
			uint32_t getYear() const;
			uint32_t getMonth() const;
			uint32_t getDate() const;
			uint32_t getDay() const;
			uint32_t getHours() const;
			uint32_t getMinutes() const;
			uint32_t getSeconds() const;
			
			/// local timezone in seconds
			static int32_t getTimeZone();
	};
}

#endif /* __TELLUSIM_CORE_TIME_H__ */
