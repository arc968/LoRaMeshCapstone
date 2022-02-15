#include "drv_rtc_RV8803C7.h"
#include "../src/hal/hal.h"

drv_rtc_RV8803C7 :: drv_rtc_RV8803C7(uint8_t address, uint8_t sda, uint8_t scl, uint8_t nint, uint8_t evi, uint8_t clkout, uint8_t clkoe) : drv_i2c_abstract(address, sda, scl)  {
	
	//drv_address = address;
	//drv_sda = sda;
	//drv_scl = scl;
	//drv_initalized = false;		
	//drv_enabled = true;
	drv_nint = nint;
	drv_evi = evi;
	drv_clkout = clkout;
	drv_clkoe = clkoe;	

	
	hal_gpio_pinMode(drv_nint, GPIO_INPUT);
	hal_gpio_pinMode(drv_evi, GPIO_OUTPUT);
	hal_gpio_digitalWrite(drv_evi, GPIO_LOW);
	hal_gpio_pinMode(drv_clkoe, GPIO_OUTPUT);
	hal_gpio_digitalWrite(drv_clkoe, GPIO_LOW);
	hal_gpio_pinMode(drv_clkout, GPIO_INPUT);			
}