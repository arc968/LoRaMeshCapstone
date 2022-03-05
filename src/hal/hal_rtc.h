/**
 * \addtogroup hallayer Hardware Abstraction Layer
 * @{
 */

/**
 * \file hal_rtc.h
 * \brief This file provides the underlying mcu real time counter (rtc) functionalies for the library
 * based on the defined hardware in the hardware layer.
 *
 * Based on the selected hardware in the hardware layer this file sets up the RTC for this
 * library. Aditionally this file provides the hal_power.h with a always on acurate timer count
 * to serve as an internal wake up interrupt after a certain time interval.
 */

#ifndef HAL_RTC_H
#define HAL_RTC_H

#include "hal_common.h"

#ifdef __cplusplus
extern "C" {
#endif

bool hal_rtc_init(uint8_t mode, uint8_t clkdiv);

bool hal_rtc_deinit(void);

void hal_rtc_enable(void);

void hal_rtc_disable(void);

void hal_rtc_setCount(void);

uint32_t hal_rtc_getCount(void);

void hal_rtc_setCompare(uint32_t val);

uint32_t hal_rtc_getCompare(void);

void hal_rtc_enableCompareInterrupt(void);

void hal_rtc_disableCompareInterrupt(void);

void hal_rtc_enableOverflowInterrupt(void);

void hal_rtc_disableOverflowInterrupt(void);

void hal_rtc_enableCompareInterrupt(void);

void hal_rtc_disableCompareInterrupt(void);

void hal_rtc_clearCompareInterrupt(void);

void hal_rtc_clearOverflowInterrupt(void);


#ifdef __cplusplus
}
#endif
#endif // HAL_RTC_H

/** @} */ // end of hallayer