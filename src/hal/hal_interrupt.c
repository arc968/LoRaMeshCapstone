#define HAL_LIB
#include "hal_interrupt.h"

void hal_interrupt_enable(void) {
	#ifdef HW_ARDUINO
		interrupts();
	#elif HW_IBUG_H
	
	#else
		#error "Hardware not yet implemented"
	#endif
}

void hal_interrupt_disable(void) {
	#ifdef HW_ARDUINO
		noInterrupts();
	#elif HW_IBUG_H
	
	#else
		#error "Hardware not yet implemented"
	#endif
}

void hal_interrupt_attachPin(pin_t pin, void (*isr)(void), uint8_t mode) {
	#ifdef HW_ARDUINO
		attachInterrupt(digitalPinToInterrupt(pin), isr, mode);
	#elif HW_IBUG_H
	
	#else
		#error "Hardware not yet implemented"
	#endif
}

void hal_interrupt_detachPin(pin_t pin) {
	#ifdef HW_ARDUINO
		detachInterrupt(digitalPinToInterrupt(pin));
	#elif HW_IBUG_H
	
	#else
		#error "Hardware not yet implemented"
	#endif
}

#ifndef HW_ARDUINO
void hal_interrupt_attach(enum HAL_INTERRUPT_TYPE trigger, void (*isr)(void)) {
	#ifdef HW_IBUG_H
	
	#else
		#error "Hardware not yet implemented"
	#endif
}
#endif // HW_ARDUINO

#ifndef HW_ARDUINO
void hal_interrupt_detach(enum HAL_INTERRUPT_TYPE trigger) {
	#ifdef HW_IBUG_H
	
	#else
		#error "Hardware not yet implemented"
	#endif
}
#endif // HW_ARDUINO