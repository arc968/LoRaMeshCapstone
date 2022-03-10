/**
 * \addtogroup hallayer Hardware Abstraction Layer
 * @{
 */

/**
 * \file hal_power.h
 * \brief 
 * 
 * 
 */

#ifndef HAL_POWER_H
#define HAL_POWER_H

#include "hal_common.h"
#include "../lib/datetime/lib_datetime.h"

#ifdef __cplusplus
extern "C" {
#endif

enum hw_power_pwrmodes_e {
	
	PWR_FULL = 0,
	PWR_IDLE = 1,
	PWR_SLEEP = 2,
	PWR_DEEP_SLEEP = 3,
	
};

void hal_power_mode(enum hw_power_pwrmodes_e pwrmode, struct lib_datetime_s * alarm);

void hal_power_softReset(void);

#if defined(HW_MKRWAN1300_H)
void hal_power_attachInterruptWakeup(uint8_t pin, void (*isr)(void));
#endif

#ifdef __cplusplus
}
#endif
#endif // HAL_POWER_H

/** @} */ // end of hallayer