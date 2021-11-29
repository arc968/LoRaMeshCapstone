#include "drv_spi_abstract.h"
#include "../hal/hal.h"

void begin(void) {
	
	hal_gpio_pinMode(drv_cs, OUTPUT);
	hal_spi_begin();
	drv_spi_begun = true;
	drv_initialized = true;
	drv_enabled = true;
	
}

void end(void) {
	
	hal_spi_end();
	drv_initialized = false;
	drv_enabled = false;
	
}