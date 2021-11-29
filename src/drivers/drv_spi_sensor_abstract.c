#include "drv_spi_sensor_abstract.h"
#include "hal.h"

void begin(void) {
	
	hal_gpio_pinMode(drv_cs, OUTPUT);
	if (drv_spi_begun == false) {
		hal_spi_begin();
		drv_spi_begun = true;
	}
	drv_initialized = true;
	drv_enabled = true;
	
}

void end(void) {
	
	hal_spi_end();
	drv_initialized = false;
	drv_enabled = false;
	
}