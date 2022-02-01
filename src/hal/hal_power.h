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

#ifdef __cplusplus
extern "C" {
#endif

enum hw_power_pwrmodes_e {
	
	PWR_FULL = 0,
	PWR_IDLE = 1,
	PWR_LOW_POWER = 2,
	PWR_ULTRA_LOW_POWER = 3,
	
}

void hal_power_mode(hw_power_pwrmodes_e pwrmode, uint16_t millis);

void hal_power_wake(void);

#if defined(HW_MKRWAN1300_H)
void hal_power_attachInterruptWakeup(uint8_t pin, void (*isr)(void));
#endif

#ifdef __cplusplus
}
#endif
#endif // HAL_POWER_H

/** @} */ // end of hallayer