#ifndef DRV_GPS_H
#define DRV_GPS_H
#if defined (__cplusplus)
extern "C" {
#endif

#include "../../lib/datetime/lib_datetime.h"

#include <stdint.h>

typedef uint32_t drv_gps_baud_t;

void drv_gps_init(drv_gps_baud_t baud);

#if defined (__cplusplus)
}
#endif
#endif // DRV_GPS_H