#include "drv_spi_abstract.h"
#include "../../hal/hal.h"

void drv_spi_abstract :: begin(void) {
	
	hal_gpio_pinMode(drv_cs, GPIO_OUTPUT);
	hal_spi_begin();
	drv_initalized = true;
	drv_enabled = true;
	
}

void drv_spi_abstract :: end(void) {
	
	hal_spi_end();
	drv_initalized = false;
	drv_enabled = false;
	
}