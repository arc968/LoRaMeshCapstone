#ifndef HAL_INTERRUPT_H
#define HAL_INTERRUPT_H

#include "hal_common.h"

#ifndef HW_ARDUINO
enum hal_interrupt_mode_e {
	INTERRUPT_LOW = 0,
	INTERRUPT_HIGH = 1,
	INTERRUPT_CHANGE = 2,
	INTERRUPT_RISING = 3,
	INTERRUPT_FALLING = 4
};

enum hal_interrupt_type_e {
	TODO = 0
};
#endif // HW_ARDUINO

void hal_interrupt_enable(void);

void hal_interrupt_disable(void);

void hal_interrupt_attachPin(pin_t pin, void (*isr)(void), uint8_t mode);

void hal_interrupt_detachPin(pin_t pin);

#ifndef HW_ARDUINO
void hal_interrupt_attach(enum hal_interrupt_type_e trigger, void (*isr)(void));
#endif // HW_ARDUINO

#ifndef HW_ARDUINO
void hal_interrupt_detach(enum hal_interrupt_type_e trigger);
#endif // HW_ARDUINO

#endif // HAL_INTERRUPT_H