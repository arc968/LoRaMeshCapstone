#if !defined(HARDWARE_H_SCOPE)
	#error "Do not directly include this header file, include hardware.h instead."
#elif defined(HW_GPS_H) && !defined(HW_GPS_UBLOX_NEO6_H)
	#error "Multiple GPS hardware definitions."
#elif !defined(HW_GPS_H) && !defined(HW_GPS_UBLOX_NEO6_H)

	#define HW_GPS_UBLOX
	#define HW_GPS_UBLOX_NEO6_H
	#include "../hw_gps_ublox.h"

	#ifdef HW_GPS_IMPLEMENTATION

	void drv_gps_init(drv_gps_baud_t baud) {
		//initialize serial1 port for communicating with GPS
		
		//add ISR to vector table
		
		//enable interrupts on GPS pulse GPIO pin
	}

	#endif // HW_GPS_UBLOX_NEO6_IMPLEMENTATION
#endif // HW_GPS_UBLOX_NEO6_H