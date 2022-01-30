#ifndef DRV_CO2_SENSOR_H
#define DRV_CO2_SENSOR_H

#include "../drv_i2c_abstract.h"

class drv_co2_sensor : drv_i2c_abstract {
	
	private:
		
		
		
	public:
		
		void setPowerMode(uint8_t mode);
		
};

#endif // DRV_CO2_SENSOR_H