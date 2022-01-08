#include "../../hal/hal.h"
#include "drv_gps.h"

void drv_gps_init(drv_gps_baud_t baud) {
	//initialize serial1 port for communicating with GPS
	
	//add ISR to vector table
	
	//enable interrupts on GPS pulse GPIO pin
}

lib_datetime_time_t drv_gps_getTime() {
	return 0;
}