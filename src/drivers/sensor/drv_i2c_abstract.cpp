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

void drv_i2c_abstract :: write(uint8_t * buf, uint16_t byteLength) {
	
	if (drv_enabled && drv_initalized) {
		
		hal_i2c_beginTransmission(drv_address);
		hal_i2c_write(buf, byteLength);
		hal_i2c_endTransmission(true);
		
	}
	
}

bool drv_i2c_abstract :: read(uint8_t* buf, uint16_t buflength) {
	
	uint16_t readlength = 0;
	
	if (drv_enabled && drv_initalized) {
	
		hal_i2c_requestFrom(drv_address, buflength, true);
		
		while(hal_i2c_available() && buflength > readlength) {
			
			buf[readlength] = hal_i2c_read();
			readlength++;
			
		}
		
		if (readlength == buflength - 1) {
			
			return true;
			
		}
		
	}
	
	return false;
	
}

