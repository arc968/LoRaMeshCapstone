#ifndef DRV_TIMER_H
#define DRV_TIMER_H
#if defined (__cplusplus)
extern "C" {
#endif

#include <stdbool.h>
#include "../../lib/datetime/lib_datetime.h"

enum drv_timer_err_e {
	DRV_TIMER_ERR__NONE = 0, //no error, operation was successful
	DRV_TIMER_ERR__ABSOLUTE_TIME_TMP_UNAVAILABLE, //absolute time source (such as GPS) is not yet synchronized
	DRV_TIMER_ERR__ABSOLUTE_DATE_TMP_UNAVAILABLE, //absolute time source (such as GPS) is not yet synchronized
};

void drv_timer_init(void);

lib_datetime_interval_t drv_timer_getMonotonicTime(void); //cannot fail, ms since drv_timer was initialized

bool drv_timer_absoluteDateIsAvailable(void);

bool drv_timer_absoluteTimeIsAvailable(void);

void drv_timer_setAbsoluteDateTime(struct lib_datetime_s * dt);

void drv_timer_setAbsoluteDate(struct lib_datetime_s * dt);

void drv_timer_setAbsoluteTime(lib_datetime_time_t time);

enum drv_timer_err_e drv_timer_getAbsoluteDateTime(struct lib_datetime_s * dt);

enum drv_timer_err_e drv_timer_getAbsoluteDate(struct lib_datetime_s * dt);

enum drv_timer_err_e drv_timer_getAbsoluteTime(lib_datetime_time_t * time);

enum drv_timer_err_e drv_timer_getRealtime(lib_datetime_realtime_t * realtime);

#if defined (__cplusplus)
}
#endif
#endif // DRV_TIMER_H
