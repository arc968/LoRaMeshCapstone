#if !defined(HARDWARE_H_SCOPE)
	#error "Do not directly include this header file, include hardware.h instead."
#elif !defined(HW_GPS_UBLOX_H)

	#ifndef HW_GPS_UBLOX
		#error "No ublox GPS hardware defined. Do not include hw_gps_ublox.h directly."
	#endif

	#define HW_GPS
	#define HW_GPS_UBLOX_H
	#include "../hw_gps.h"

#endif // HW_GPS_UBLOX_H