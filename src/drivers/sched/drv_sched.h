#ifndef DRV_SCHED_H
#define DRV_SCHED_H

#include "../../lib/datetime/lib_datetime.h"

enum drv_sched_pri_e {
	PRI_IDLE = 0,
	PRI_LOW = 63,
	PRI_NORMAL = 127,
	PRI_HIGH = 191,
	PRI_REALTIME = 255
}
#ifdef __GNUC__
__attribute__ ((__packed__))
#endif
;

void drv_sched_init(void);

#ifdef __GNUC__
__attribute__((noreturn))
#endif
void drv_sched_start(void);

//0 if successful, -1 if failed
int drv_sched_once(void (*fun_ptr)(void), enum drv_sched_pri_e priority, lib_datetime_interval_t delay_ms);

//0 if successful, -1 if failed
int drv_sched_repeating(void (*fun_ptr)(void), enum drv_sched_pri_e priority, lib_datetime_interval_t interval_ms);

//0 if successful, -1 if failed
int drv_sched_at(void (*fun_ptr)(void), enum drv_sched_pri_e priority, lib_datetime_time_t time);

#endif // DRV_SCHED_H