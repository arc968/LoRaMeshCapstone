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
#include "../lib/datetime/lib_datetime.h"

#ifdef __cplusplus
extern "C" {
#endif

void hal_rtc_init(void);

void hal_rtc_deinit(void);

bool hal_rtc_isInitialized(void);

void hal_rtc_enable(void);

void hal_rtc_disable(void);

void hal_rtc_setClock(uint32_t val);

void hal_rtc_clearClock(void);

void hal_rtc_getClock(struct lib_datetime_s * val);

void hal_rtc_setAlarm(struct lib_datetime_s * dt);

void hal_rtc_getAlarm(struct lib_datetime_s * val);

bool hal_rtc_compareClockToAlarm(void);

void hal_rtc_enableAlarmInterrupt(void);

void hal_rtc_disableAlarmInterrupt(void);

void hal_rtc_enableOverflowInterrupt(void);

void hal_rtc_disableOverflowInterrupt(void);

void hal_rtc_clearAlarmInterrupt(void);

void hal_rtc_clearOverflowInterrupt(void);


#ifdef __cplusplus
}
#endif
#endif // HAL_RTC_H

/** @} */ // end of hallayer