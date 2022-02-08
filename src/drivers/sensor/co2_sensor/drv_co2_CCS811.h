#ifndef DRV_CO2_CCS811_H
#define DRV_CO2_CCS811_H

#include "../drv_i2c_abstract.h"

class drv_co2_CCS811 : protected drv_i2c_abstract {
	
	private:
		
		const uint8_t drv_address_low = 0x5A, drv_address_high = 0x5B; 
		uint8_t drv_nreset, drv_nwake, drv_addr, drv_nint, drv_pwmsense, drv_aux;
		
		
	public:
	
		drv_co2_CCS811(uint8_t sda, uint8_t scl, uint8_t nreset, uint8_t nwake, uint8_t addrselect, uint8_t nint, uint8_t pwmsense, uint8_t aux);
		~drv_co2_CCS811(void) {}
		
		void setPowerMode(uint8_t mode);
		
		void reset(void);
		
		bool read(uint8_t* buf, uint16_t buflength);
		void write(uint8_t * buf, uint16_t byteLength);
		
};

#endif // DRV_CO2_CCS811_H