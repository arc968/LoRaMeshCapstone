/**
 * \addtogroup hallayer Hardware Abstraction Layer
 * @{
 */

/**
 * \file hal_interrupt.h
 * \brief This file provides interupt functionality for the library based on
 * the selected hardware in the hardware layer.
 * 
 * This file allows for the use of interupts for the defined hardware in the
 * hardware layer. It also creates the enums for user ease of use of the functions.
 */

#ifndef HAL_INTERRUPT_H
#define HAL_INTERRUPT_H

#include "hal_common.h"

#ifdef __cplusplus
extern "C" {
#endif

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
#else
enum hal_interrupt_mode_e {
	INTERRUPT_LOW = LOW,
	INTERRUPT_HIGH = HIGH,
	INTERRUPT_CHANGE = CHANGE,
	INTERRUPT_RISING = RISING,
	INTERRUPT_FALLING = FALLING
};

#endif // HW_ARDUINO



void hal_interrupt_enable(void);

void hal_interrupt_disable(void);

void hal_interrupt_attachPin(pin_t pin, void (*isr)(void), enum hal_interrupt_mode_e mode);

void hal_interrupt_detachPin(pin_t pin);

#ifndef HW_ARDUINO
void hal_interrupt_attach(enum hal_interrupt_type_e trigger, void (*isr)(void));
#endif // HW_ARDUINO

#ifndef HW_ARDUINO
void hal_interrupt_detach(enum hal_interrupt_type_e trigger);
#endif // HW_ARDUINO

#ifdef __cplusplus
}
#endif
#endif // HAL_INTERRUPT_H

/** @} */ // end of hallayer