#ifndef DRV_SCHED_H
#define DRV_SCHED_H
#if defined (__cplusplus)
extern "C" {
#endif

#include "../../lib/datetime/lib_datetime.h"

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
	DRV_SCHED_ERR__INTERVAL_TOO_LONG, //interval is longer than one day
	DRV_SCHED_ERR__ABSOLUTE_SCHED_TMP_UNAVAILABLE, //absolute time source (such as GPS) is not yet synchronized
};

void drv_sched_init(void (*fun_ptr_)(void), void (*fun_ptr)(void));

#ifdef __GNUC__
__attribute__((noreturn))
#endif
void drv_sched_start(void);

enum drv_sched_err_e drv_sched_once(void (*fun_ptr)(void), enum drv_sched_pri_e priority, lib_datetime_interval_t delay_ms);

enum drv_sched_err_e drv_sched_repeating(void (*fun_ptr)(void), enum drv_sched_pri_e priority, lib_datetime_interval_t interval_ms);

enum drv_sched_err_e drv_sched_once_at(void (*fun_ptr)(void), enum drv_sched_pri_e priority, lib_datetime_time_t time);

enum drv_sched_err_e drv_sched_repeating_at(void (*fun_ptr)(void), enum drv_sched_pri_e priority, lib_datetime_time_t time, lib_datetime_interval_t interval_ms);

#if defined (__cplusplus)
}
#endif
#endif // DRV_SCHED_H