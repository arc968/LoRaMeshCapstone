#define HAL_LIB
#include "hal_gpio.h"

void hal_gpio_pinMode(pin_t pin, uint8_t mode) {
	#if defined(HW_ARDUINO)
		pinMode(pin, mode);	
	#elif defined(HW_IBUG_H)
	
	#else
		#error "Hardware not yet implemented"
	#endif
}

void hal_gpio_digitalWrite(pin_t pin, uint8_t val) {
	#if defined(HW_ARDUINO)
		digitalWrite(pin, val);
	#elif defined(HW_IBUG_H)
	
	#else
		#error "Hardware not yet implemented"
	#endif
}

uint8_t hal_gpio_digitalRead(pin_t pin) {
	#if defined(HW_ARDUINO)
		return digitalRead(pin);
	#elif defined(HW_IBUG_H)
		return 0; //TODO
	#else
		#error "Hardware not yet implemented"
	#endif
}

uint16_t hal_gpio_analogRead(pin_t pin) {
	#if defined(HW_ARDUINO)
		return analogRead(pin);
	#elif defined(HW_IBUG_H)
		return 0; //TODO
	#else
		#error "Hardware not yet implemented"
	#endif
}

