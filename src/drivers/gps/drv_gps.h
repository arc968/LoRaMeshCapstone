#ifndef DRV_GPS_H
#define DRV_GPS_H
#if defined (__cplusplus)
extern "C" {
#endif

#include <stdint.h>

#include "../../lib/datetime/lib_datetime.h"
#include "../../hardware/hardware.h"

enum drv_gps_error_e {
	DRV_GPS_ERR__NONE,
};

void drv_gps_init(void);

enum drv_gps_error_e drv_gps_sendCommand(const char * cmd);

enum drv_gps_error_e drv_gps_getTime(lib_datetime_realtime_t * rt);

#if defined (__cplusplus)
}
#endif
#endif // DRV_GPS_H