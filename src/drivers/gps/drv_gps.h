#ifndef DRV_GPS_H
#define DRV_GPS_H

#include "../../lib/datetime/lib_datetime.h"

#include <stdint.h>

typedef uint32_t drv_gps_baud_t;

void drv_gps_init(drv_gps_baud_t baud);

lib_datetime_time_t drv_gps_getTime();

#endif // DRV_GPS_H