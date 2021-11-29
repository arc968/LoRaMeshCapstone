#include "drv_i2c_sensor_abstract.h"
#include "hal.h"

void begin(void) {
	
	if (drv_i2c_begun == false) {
		hal_i2c_begin();
		drv_i2c_begun = true;
	}
	drv_initialized = true;
	drv_enabled = true;
	
}

void end(void) {
	
	drv_initialized = false;
	drv_enabled = false;
	
}