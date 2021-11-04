#include "hal_config.h"
#ifndef HW_H
	#error "Hardware not defined"
#endif // HW_H

#include "hal_gpio.h"

void hal_gpio_pinMode(pin_t pin, uint8_t mode) {
	
	#ifdef HW_ARDUINO
		pinMode(pin, HAL_GPIO_PINMODE);	
	#elif HW_IBUG_H
	
	#else
		#error "Hardware not yet implemented"
	#endif
	
}

void hal_gpio_digitalWrite(pin_t pin, uint8_t val) {
	
	#ifdef HW_ARDUINO
		digitalWrite(pin, val);
	#elif HW_IBUG_H
	
	#else
		#error "Hardware not yet implemented"
	#endif
	
}

uint8_t hal_gpio_digitalRead(pin_t pin) {
	
	#ifdef HW_ARDUINO
		return digitalRead(pin);
	#elif HW_IBUG_H
	
	#else
		#error "Hardware not yet implemented"
	#endif
	
}

uint16_t hal_gpio_analogRead(pin_t pin) {
	
	#ifdef HW_ARDUINO
		return analogRead(pin);
	#elif HW_IBUG_H
	
	#else
		#error "Hardware not yet implemented"
	#endif
	
}

