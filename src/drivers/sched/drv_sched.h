#ifndef DRV_SCHED_H
#define DRV_SCHED_H

#include "../../lib/datetime/lib_datetime.h"

#include <stdint.h>

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

void drv_sched_repeating(void (*fun_ptr)(void), enum drv_sched_pri_e priority, uint16_t interval_ms);

void drv_sched_once(void (*fun_ptr)(void), enum drv_sched_pri_e priority, uint16_t delay_ms);

void drv_sched_at(void (*fun_ptr)(void), enum drv_sched_pri_e priority, struct lib_datetime_s * dt);

#endif // DRV_SCHED_H