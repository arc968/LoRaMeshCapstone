#ifndef HAL_INTERRUPT_H
#define HAL_INTERRUPT_H

#include "hal_common.h"

enum HAL_INTERRUPT_MODE {
	LOW = 0,
	HIGH = 1,
	CHANGE = 2,
	RISING = 3,
	FALLING = 4
};

enum HAL_INTERRUPT_TYPE {
	
};

void hal_interrupt_enable(void);

void hal_interrupt_disable(void);

void hal_interrupt_attachPin(pin_t pin, void (*isr)(void), uint8_t mode);

void hal_interrupt_detachPin(pin_t pin);

void hal_interrupt_attach(enum HAL_INTERRUPT_TYPE trigger, void (*isr)(void));

void hal_interrupt_detach(enum HAL_INTERRUPT_TYPE trigger);

#endif // HAL_INTERRUPT_H