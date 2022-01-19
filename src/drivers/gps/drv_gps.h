#ifndef DRV_GPS_H
#define DRV_GPS_H
#if defined (__cplusplus)
extern "C" {
#endif

#include "../../hardware/hardware.h"

#ifdef GPS_NONE
	#error "GPS_NONE is defined. This header file should not be included."
#endif

#ifndef HW_GPS_H
	#error "No GPS hardware defined."
#endif

#include "../../lib/datetime/lib_datetime.h"

#include <stdint.h>

typedef uint32_t drv_gps_baud_t;

typedef uint16_t drv_gps_millihertz_t;

enum drv_gps_error_e {
	DRV_GPS_ERR__NONE,
};

enum drv_gps_baud_e {
	DRV_GPS_BAUD__115200,
	DRV_GPS_BAUD__57600,
	DRV_GPS_BAUD__9600,
};

void drv_gps_init(void);

enum drv_gps_error_e drv_gps_setBaud(drv_gps_baud_t baud);

enum drv_gps_error_e drv_gps_setUpdateRate(drv_gps_millihertz_t rate);

#if defined (__cplusplus)
}
#endif
#endif // DRV_GPS_H