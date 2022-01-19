#if !defined(HARDWARE_H_SCOPE) && !defined(HW_GPS_UBLOX_NEO6_C)
	#error "Do not directly include this header file, include hardware.h instead."
#elif defined(HW_GPS_H) && !defined(HW_GPS_UBLOX_NEO6_H)
	#error "Multiple GPS hardware definitions."
#elif !defined(HW_GPS_UBLOX_NEO6_H)
	#define HW_GPS_UBLOX_SCOPE

	#define HW_GPS_UBLOX
	#define HW_GPS_UBLOX_NEO6_H
	#include "../hw_gps_ublox.h"

	#undef HW_GPS_UBLOX_SCOPE
#endif // HW_GPS_UBLOX_NEO6_H