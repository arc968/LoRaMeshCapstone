#ifndef DRV_GPS_H
#define DRV_GPS_H
#if defined (__cplusplus)
extern "C" {
#endif

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "../../lib/datetime/lib_datetime.h"
#include "../../hardware/hardware.h"

enum drv_gps_error_e {
	DRV_GPS_ERR__NONE,
};

struct drv_gps_s {
	
};

void drv_gps_init(struct drv_gps_s * handle);

enum drv_gps_error_e drv_gps_sendCommand(const char * cmd);

#if defined (__cplusplus)
}
#endif
#endif // DRV_GPS_H
