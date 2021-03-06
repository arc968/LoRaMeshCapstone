/**
 * \addtogroup hallayer Hardware Abstraction Layer
 * @{
 */

/**
 * \file hal_timer.h
 * \brief This file provides the underlying timer functionalies and delays for the library
 * based on the defined hardware in the hardware layer.
 *
 * Based on the selected hardware in the hardware layer this file sets up the timers for this
 * library. Aditionally this file provides the time of opperation in milliseconds, and a delay 
 * function for the library.
 */

#ifndef HAL_TIMER_H
#define HAL_TIMER_H

#include "hal_common.h"

#ifdef __cplusplus
extern "C" {
#endif

void hal_timer_init(void (*isr)(void), uint16_t interval_us);

void hal_timer_delay(uint16_t msdelay);

uint64_t hal_timer_millis(void);

//void hal_timer_setInterruptInterval(void (*isr)(void), uint32_t interval);

#ifdef __cplusplus
}
#endif
#endif // HAL_TIMER_H

/** @} */ // end of hallayer