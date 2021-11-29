#include "drv_serial_sensor_abstract.h"
#include "hal.h"

void begin(void) {
	
	if (drv_serial_begun == false) {
		hal_serial_begin();
	
		if (hal_serial_ready()) {
			drv_serial_begun = true;
			drv_initialized = true;
			drv_enabled = true;
		}
		else {
			drv_initialized = false;
			drv_enabled = false;
		}
	
	}
	
}

void end(void) {
	
	hal_serial_end();
	drv_initialized = false;
	drv_enabled = false;
	
}

bool isInitialized(void) {
	
	if (hal_serial_ready()) {
		return drv_initialized;
	}
	
	return false;
	
}