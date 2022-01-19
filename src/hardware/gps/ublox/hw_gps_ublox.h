#if !defined(HW_GPS_UBLOX_SCOPE)
	#error "Do not directly include this header file, include hardware.h instead."
#elif !defined(HW_GPS_UBLOX_H)
	#define HW_GPS_SCOPE

	#ifndef HW_GPS_UBLOX
		#error "No ublox GPS hardware defined."
	#endif

	#define HW_GPS
	#define HW_GPS_UBLOX_H
	#include "../hw_gps.h"

	#undef HW_GPS_SCOPE
#endif // HW_GPS_UBLOX_H