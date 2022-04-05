#if !defined(HARDWARE_H_SCOPE) && !defined(HW_GPS_RTC_DS3231_C)
	#error "Do not directly include this header file, include hardware.h instead."
#elif defined(HW_GPS_H) && !defined(HW_GPS_RTC_DS3231_H)
	#error "Multiple GPS hardware definitions."
#elif !defined(HW_GPS_RTC_DS3231_H)
#ifdef __cplusplus
extern "C" {
#endif

	#define HW_GPS_RTC_SCOPE

	#define HW_GPS_RTC
	#define HW_GPS_RTC_DS3231_H
	#include "../hw_gps_rtc.h"

	#undef HW_GPS_RTC_SCOPE
	
#ifdef __cplusplus
}
#endif

#endif // HW_GPS_RTC_DS3231_H