#ifndef DRV_SCHED_H
#define DRV_SCHED_H
#if defined (__cplusplus)
extern "C" {
#endif

#include "../../lib/datetime/lib_datetime.h"

#define DRV_SCHED__MAX_JOBS 16
#if (!((DRV_SCHED__MAX_JOBS) >= 1))
	#error DRV_SCHED__MAX_JOBS must be >= 1
#endif

enum drv_sched_pri_e {
	DRV_SCHED_PRI__IDLE = 0,
	DRV_SCHED_PRI__LOW = 63,
	DRV_SCHED_PRI__NORMAL = 127,
	DRV_SCHED_PRI__HIGH = 191,
	DRV_SCHED_PRI__REALTIME = 255
};

enum drv_sched_err_e {
	DRV_SCHED_ERR__NONE = 0, //no error, operation was successful
	DRV_SCHED_ERR__NO_JOB_SLOTS, //no empty jobs slots left
	DRV_SCHED_ERR__ABSOLUTE_SCHED_TMP_UNAVAILABLE, //absolute time source (such as GPS) is not yet synchronized
	DRV_SCHED_ERR__INVALID_TIME, //invalid time of day
};

void drv_sched_init(void);

#ifdef __GNUC__
__attribute__((noreturn))
#endif
void drv_sched_start(void);

void drv_sched_setOnSleepCallback(void (*func_onSleep_ptr)(void));

void drv_sched_setOnWakeCallback(void (*func_onWake_ptr)(void));

enum drv_sched_err_e drv_sched_once(void (*func_ptr)(void*), void * func_arg, enum drv_sched_pri_e priority, lib_datetime_interval_t delay_ms);

enum drv_sched_err_e drv_sched_repeating(void (*func_ptr)(void*), void * func_arg, enum drv_sched_pri_e priority, lib_datetime_interval_t delay_ms, lib_datetime_interval_t interval_ms);

enum drv_sched_err_e drv_sched_once_at(void (*func_ptr)(void*), void * func_arg, enum drv_sched_pri_e priority, lib_datetime_realtime_t time);

enum drv_sched_err_e drv_sched_repeating_at(void (*func_ptr)(void*), void * func_arg, enum drv_sched_pri_e priority, lib_datetime_realtime_t time, lib_datetime_interval_t interval_ms);

enum drv_sched_err_e drv_sched_onAbsoluteAvailable(void (*func_ptr)(void*), void * func_arg);

#if defined (__cplusplus)
}
#endif
#endif // DRV_SCHED_H