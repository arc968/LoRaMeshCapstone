#ifndef DRV_RTC_RV8803C7_H
#define DRV_RTC_RV8803C7_H

#include "../drv_i2c_abstract.h"

class drv_rtc_RV8803C7 : drv_i2c_abstract {
	
	private:
		
		uint8_t drv_nint, drv_evi, drv_clkout, drv_clkoe;
		
	public:
		
		drv_rtc_RV8803C7(uint8_t address, uint8_t sda, uint8_t scl, uint8_t nint, uint8_t evi, uint8_t clkout, uint8_t clkoe);
		~drv_rtc_RV8803C7(void){}
		
		
		
		
};

#endif // DRV_RTC_RV8803C7_H