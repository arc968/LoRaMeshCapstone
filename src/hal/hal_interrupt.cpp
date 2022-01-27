#define HAL_LIB
#include "hal_interrupt.h"

void hal_interrupt_enable(void) {
	#if defined(HW_ARDUINO)
		interrupts();
	#elif defined(HW_IBUG_H)
	
	#else
		#error "Hardware not yet implemented"
	#endif
}

void hal_interrupt_disable(void) {
	#if defined(HW_ARDUINO)
		noInterrupts();
	#elif defined(HW_IBUG_H)
	
	#else
		#error "Hardware not yet implemented"
	#endif
}

void hal_interrupt_attachPin(pin_t pin, void (isr)(void), enum hal_interrupt_mode_e mode) {
	#if defined(HW_ARDUINO)
		attachInterrupt(digitalPinToInterrupt(pin), isr, (PinStatus) mode);
	#elif defined(HW_IBUG_H)
	
	#else
		#error "Hardware not yet implemented"
	#endif
}

void hal_interrupt_detachPin(pin_t pin) {
	#if defined(HW_ARDUINO)
		detachInterrupt(digitalPinToInterrupt(pin));
	#elif defined(HW_IBUG_H)
	
	#else
		#error "Hardware not yet implemented"
	#endif
}

#ifndef HW_ARDUINO
void hal_interrupt_attach(enum hal_interrupt_type_e trigger, void (*isr)(void)) {
	#if defined(HW_IBUG_H)
	
	#else
		#error "Hardware not yet implemented"
	#endif
}
#endif // HW_ARDUINO

#ifndef HW_ARDUINO
void hal_interrupt_detach(enum hal_interrupt_type_e trigger) {
	#if defined(HW_IBUG_H)
	
	#else
		#error "Hardware not yet implemented"
	#endif
}
#endif // HW_ARDUINO