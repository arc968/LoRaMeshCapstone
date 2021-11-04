#ifndef HAL_INTERRUPT_H
#define HAL_INTERRUPT_H

#include "hal_defines.h"

enum HAL_INTERRUPT_MODE {
	LOW = 0,
	HIGH = 1,
	CHANGE = 2,
	RISING = 3,
	FALLING = 4
};

hal_interrupt_enable();

hal_interrupt_disable();

hal_interrupt_attach(pin_t pin, void (*isr)(void), enum HAL_INTERRUPT_MODE);

hal_interrupt_detach(pin_t pin);

#endif // HAL_INTERRUPT_H