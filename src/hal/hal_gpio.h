#ifndef HAL_GPIO_H
#define HAL_GPIO_H

#include "hal_common.h"

#ifndef HW_ARDUINO
enum hal_gpio_pinmode_e {
	INPUT = 0,
	OUTPUT = 1,
	INPUT_PULLUP = 2,
	INPUT_PULLDOWN = 3
};

enum hal_gpio_output_e {
	LOW = 0,
	HIGH = 1
};
#endif // HW_ARDUINO

void hal_gpio_pinMode(pin_t pin, uint8_t mode);

void hal_gpio_digitalWrite(pin_t pin, uint8_t mode);

uint8_t hal_gpio_digitalRead(pin_t pin);

uint16_t hal_gpio_analogRead(pin_t pin);

#endif // HAL_GPIO_H