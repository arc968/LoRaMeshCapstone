#include "drv_i2c_abstract.h"
#include "../../hal/hal.h"

void begin(void) {
	
	hal_i2c_begin();
	drv_initialized = true;
	drv_enabled = true;
	
}

void end(void) {
	
	drv_initialized = false;
	drv_enabled = false;
	
}