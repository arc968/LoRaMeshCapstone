/**
 * \addtogroup hallayer Hardware Abstraction Layer
 * @{
 */

/**
 * \file hal_gpio.h
 * \brief This file sets up the pins on the selected hardware in the hardware layer for input and output.
 * 
 * Based on the selected hardware in the hardware layer this file sets up the functionality of the gpio pins
 * of the hard ware to configure them and read and write digital and analog signals on appropriate pins.
 * This file aditionaly sets up enums to provide ease of use when using the functions for the user.
 */

#ifndef HAL_GPIO_H
#define HAL_GPIO_H
#ifdef __cplusplus
extern "C" {
#endif

#include "hal_common.h"

#ifndef HW_ARDUINO
enum hal_gpio_pinmode_e {
	GPIO_INPUT = 0,
	GPIO_OUTPUT = 1,
	GPIO_INPUT_PULLUP = 2,
	GPIO_INPUT_PULLDOWN = 3
};

enum hal_gpio_output_e {
	GPIO_LOW = 0,
	GPIO_HIGH = 1
};

#else
enum hal_gpio_pinmode_e {
	GPIO_INPUT = INPUT,
	GPIO_OUTPUT = OUTPUT,
	GPIO_INPUT_PULLUP = PULLUP,
	GPIO_INPUT_PULLDOWN = PULLDOWN
};

enum hal_gpio_output_e {
	GPIO_LOW = LOW,
	GPIO_HIGH = HIGH
};

#endif // HW_ARDUINO

void hal_gpio_pinMode(pin_t pin, uint8_t mode);

void hal_gpio_digitalWrite(pin_t pin, uint8_t mode);

uint8_t hal_gpio_digitalRead(pin_t pin);

uint16_t hal_gpio_analogRead(pin_t pin);

#ifdef __cplusplus
}
#endif
#endif // HAL_GPIO_H

/** @} */ // end of hallayer