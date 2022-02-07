#ifndef DRV_RTC_RV8803C7_H
#define DRV_RTC_RV8803C7_H

#include "../drv_i2c_abstract.h"

class drv_rtc_RV8803C7 : drv_i2c_abstract {
	
	private:
		
		uint8_t drv_nint, drv_evi, drv_clkout, drv_clkoe;
		
	public:
		
		drv_rtc_RV8803C7(uint16_t address, uint8_t sda, uint8_t scl, uint8_t nint, uint8_t evi, uint8_t clkout, uint8_t clkoe) {
			
			drv_address = address;
			drv_sda = sda;
			drv_scl = scl;
			drv_nint = nint;
			drv_evi = evi;
			drv_clkout = clkout;
			drv_clkoe = clkoe;	
			drv_enabled = true;
			
			hal_gpio_pinMode(drv_nint, GPIO_INPUT);
			hal_gpio_pinMode(drv_evi, GPIO_OUTPUT);
			hal_gpio_digitalWrite(drv_evi, GPIO_LOW);
			hal_gpio_pinMode(drv_clkoe, GPIO_OUTPUT);
			hal_gpio_digitalWrite(drv_clkoe, GPIO_LOW);
			hal_gpio_pinMode(drv_clkout, GPIO_INPUT);			
		}
		~drv_rtc_RV8803C7(void){}
		
		
		
		
};

#endif // DRV_RTC_RV8803C7_H