#include "drv_co2_CCS811.h"
#include "../src/hal/hal_gpio.h"
#include "../src/hal/hal_i2c.h"
#include "../src/hal/hal_interrupt.h"


drv_co2_CCS811 :: drv_co2_CCS811(uint8_t sda, uint8_t scl, uint8_t nreset, uint8_t nwake, uint8_t addrselect, uint8_t nint, uint8_t pwmsense, uint8_t aux) : drv_i2c_abstract(drv_address_low, sda, scl) {
	//drv_address = drv_address_low;
	//drv_sda = sda;
	//drv_scl = scl;
	//drv_initalized = false; 
	//drv_enabled = false;
	drv_nreset = nreset;
	drv_nwake = nwake;
	drv_addr = addrselect;
	drv_nint = nint;
	drv_pwmsense = pwmsense;
	drv_aux = aux;
	
	hal_gpio_pinMode(drv_nreset, GPIO_OUTPUT);
	hal_gpio_digitalWrite(drv_nreset, GPIO_HIGH);
	hal_gpio_pinMode(drv_nwake, GPIO_OUTPUT);
	hal_gpio_digitalWrite(drv_nwake, GPIO_HIGH);
	hal_gpio_pinMode(drv_nint, GPIO_INPUT);
	hal_gpio_pinMode(drv_addr, GPIO_OUTPUT);
	hal_gpio_digitalWrite(drv_addr, GPIO_LOW);
	hal_gpio_pinMode(drv_pwmsense, GPIO_INPUT);
	
	if (drv_aux != NULL) {
		
		
	}
	
}

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