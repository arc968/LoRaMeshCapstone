#ifndef HAL_TIMER_H
#define HAL_TIMER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "hal_common.h"

void hal_timer_delay(uint16_t msdelay);

uint32_t hal_timer_millis(void);

#ifdef __cplusplus
}
#endif
#endif // HAL_TIMER_H