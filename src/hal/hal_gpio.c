#include "hal_config.h"
#ifndef HW_H
	#error "Hardware not defined"
#endif // HW_H

#include "hal_gpio.h"

void hal_gpio_pinMode(pin_t pin, enum HAL_GPIO_PINMODE) {
	
	#ifdef HW_ARDUINO
		pinMode(pin, HAL_GPIO_PINMODE);	
	#elif HW_IBUG_H
	
	#else
		#error "Hardware not yet implemented"
	#endif
	
}

void hal_gpio_digitalWrite(pin_t pin, enum HAL_GPIO_OUTPUT);

uint8_t hal_gpio_digitalRead(pin_t pin);

uint16_t hal_gpio_analogRead(pin_t pin);

