#ifndef DRV_SCHED_H
#define DRV_SCHED_H

#include "../../lib/datetime/lib_datetime.h"

void drv_sched_init(void);

#ifdef __GNUC__
__attribute__((noreturn))
#endif
void drv_sched_start(void);

void drv_sched_repeating(void (*fun_ptr)(void), uint16_t interval_ms);

void drv_sched_once(void (*fun_ptr)(void), uint16_t delay_ms);

void drv_sched_at(void (*fun_ptr)(void), struct lib_datetime_s * dt);

#endif // DRV_SCHED_H