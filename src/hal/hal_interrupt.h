#ifndef HAL_INTERRUPT_H
#define HAL_INTERRUPT_H

#include "hal_common.h"

#ifndef HW_ARDUINO
enum hal_interupt_mode_e {
	LOW = 0,
	HIGH = 1,
	CHANGE = 2,
	RISING = 3,
	FALLING = 4
};

enum hal_interupt_type_e {
	TODO = 0
};
#endif // HW_ARDUINO

void hal_interrupt_enable(void);

void hal_interrupt_disable(void);

void hal_interrupt_attachPin(pin_t pin, void (*isr)(void), uint8_t mode);

void hal_interrupt_detachPin(pin_t pin);

#ifndef HW_ARDUINO
void hal_interrupt_attach(enum HAL_INTERRUPT_TYPE trigger, void (*isr)(void));
#endif // HW_ARDUINO

#ifndef HW_ARDUINO
void hal_interrupt_detach(enum HAL_INTERRUPT_TYPE trigger);
#endif // HW_ARDUINO

#endif // HAL_INTERRUPT_H