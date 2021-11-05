#ifndef HAL_TIMER_H
#define HAL_TIMER_H

#include "../hardware/hardware.h"

#include "hal_common.h"

void hal_timer_delay(uint16_t msdelay);

uint32_t hal_timer_millis(void);

#endif // HAL_TIMER_H