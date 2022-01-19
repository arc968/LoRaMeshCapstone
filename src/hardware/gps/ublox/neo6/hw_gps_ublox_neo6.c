#define HW_GPS_UBLOX_NEO6_C
#include "hw_gps_ublox_neo6.h"

#include "../../../../drivers/gps/drv_gps.h"

#ifdef HW_GPS_UBLOX_NEO6_H

void drv_gps_init(void) {
	//initialize serial1 port for communicating with GPS
	
	//add ISR to vector table
	
	//enable interrupts on GPS pulse GPIO pin
}

#endif // HW_GPS_UBLOX_NEO6_H

#undef HW_GPS_UBLOX_NEO6_C