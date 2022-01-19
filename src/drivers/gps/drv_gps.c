#include "../../hal/hal.h"
#include "../../hardware/hardware.h"

#ifdef GPS_NONE
	#warning "GPS_NONE is defined. Linking to any drv_gps.h functions to drv_gps.c will fail."
#else
	#define HW_GPS_IMPLEMENTATION
	#include "drv_gps.h"
#endif // GPS_NONE