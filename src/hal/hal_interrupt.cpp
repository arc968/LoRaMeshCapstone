#define HAL_LIB
#include "hal_interrupt.h"

uint8_t globalinterruptsenabled = 1;

void hal_interrupt_enable(void) {
	#if defined(HW_ARDUINO)
		interrupts();
	#elif defined(HW_MKRWAN1300_H)
		
	#elif defined(HW_RAK4260_H)
		
	#elif defined(HW_RAK4600_H)
			
	#elif defined(HW_RAK11300_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
	
	globalinterruptsenabled = 1;
	
}

void hal_interrupt_disable(void) {
	#if defined(HW_ARDUINO)
		noInterrupts();
	#elif defined(HW_MKRWAN1300_H)
		
	#elif defined(HW_RAK4260_H)
		
	#elif defined(HW_RAK4600_H)
			
	#elif defined(HW_RAK11300_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
	
	globalinterruptsenabled = 0;
	
}

bool hal_interrupt_isEnabled(void) {
	
	return globalinterruptsenabled;
	
}

void hal_interrupt_attachPin(pin_t pin, void (*isr)(void), enum hal_interrupt_mode_e mode) {
	#if defined(HW_ARDUINO)
		#if defined(HW_MKRWAN1300_H)
			attachInterrupt(digitalPinToInterrupt(pin), isr, (PinStatus) mode);
		#else
			attachInterrupt(digitalPinToInterrupt(pin), isr, mode);
		#endif
	#elif defined(HW_MKRWAN1300_H)
		
	#elif defined(HW_RAK4260_H)
		
	#elif defined(HW_RAK4600_H)
			
	#elif defined(HW_RAK11300_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
}

void hal_interrupt_detachPin(pin_t pin) {
	#if defined(HW_ARDUINO)
		detachInterrupt(digitalPinToInterrupt(pin));
	#elif defined(HW_MKRWAN1300_H)
		
	#elif defined(HW_RAK4260_H)
		
	#elif defined(HW_RAK4600_H)
			
	#elif defined(HW_RAK11300_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
}

#ifndef HW_ARDUINO
void hal_interrupt_attach(enum hal_interrupt_type_e trigger, void (*isr)(void)) {
	#if defined(HW_RAK4260_H)
		
	#elif defined(HW_MKRWAN1300_H)
		
	#elif defined(HW_RAK4600_H)
			
	#elif defined(HW_RAK11300_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
}
#endif // HW_ARDUINO

#ifndef HW_ARDUINO
void hal_interrupt_detach(enum hal_interrupt_type_e trigger) {
	#if defined(HW_RAK4260_H)
		
	#elif defined(HW_MKRWAN1300_H)
		
	#elif defined(HW_RAK4600_H)
			
	#elif defined(HW_RAK11300_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
}
#endif // HW_ARDUINO