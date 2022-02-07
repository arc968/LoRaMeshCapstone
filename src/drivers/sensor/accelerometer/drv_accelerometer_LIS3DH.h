#ifndef DRV_ACCELEROMETER_LIS3DH_H
#define DRV_ACCELEROMETER_LIS3DH_H

#include "../drv_i2c_abstract.h"

class drv_accelerometer_LIS3DH : drv_i2c_abstract {
	
	private:
		
		
		
	public:
		
		void setPowerMode(uint8_t mode);
		
};

#endif // DRV_ACCELEROMETER_H