#include "drv_i2c_abstract.h"
#include "../../hal/hal.h"

void drv_i2c_abstract :: begin(void) {
	
	hal_i2c_begin();
	drv_initalized = true;
	drv_enabled = true;
	
}

void drv_i2c_abstract :: end(void) {
	
	drv_initalized = false;
	drv_enabled = false;
	
}