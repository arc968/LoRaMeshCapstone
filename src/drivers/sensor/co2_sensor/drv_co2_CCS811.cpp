#include "drv_co2_CCS811.h"

void drv_co2_CCS811 :: setPowerMode(uint8_t mode) {
	
	
	
}

void drv_co2_CCS811 :: reset(void) {
	
	hal_gpio_digitalWrite(drv_nreset, GPIO_LOW);
	hal_gpio_digitalWrite(drv_nreset, GPIO_HIGH);
	
}

bool drv_co2_CCS811 :: read(uint8_t* buf, uint16_t buflength) {
	
	uint16_t readlength = 0;
	
	if (drv_enabled && drv_initalized) {
		
		hal_gpio_digitalWrite(drv_nreset, GPIO_LOW);

	
		hal_i2c_requestFrom(drv_address, buflength, true);
		
		while(hal_i2c_available() && buflength > readlength) {
			
			buf[readlength] = hal_i2c_read();
			readlength++;
			
		}
		
		if (readlength == buflength - 1) {
			
			hal_gpio_digitalWrite(drv_nreset, GPIO_HIGH);
			return true;
			
		}
		
	}
	
	hal_gpio_digitalWrite(drv_nreset, GPIO_HIGH);
	return false;
	
}

void drv_co2_CCS811 :: write(uint8_t * buf, uint16_t byteLength) {
	
	if (drv_enabled && drv_initalized) {
		
		hal_gpio_digitalWrite(drv_nreset, GPIO_LOW);
		hal_i2c_beginTransmission(drv_address);
		hal_i2c_write(buf, byteLength);
		hal_i2c_endTransmission(true);
		hal_gpio_digitalWrite(drv_nreset, GPIO_HIGH);
		
	}
	
}