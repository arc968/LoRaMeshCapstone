#ifndef DRV_I2C_SENSOR_ABSTRACT_H
#define DRV_I2C_SENSOR_ABSTRACT_H

#include "drv_sensor_abstract.h"

class drv_i2c_sensor_abstract : drv_sensor_abstract{
	
	private:
		
		uint8_t drv_address, drv_sda, drv_scl;
		static bool drv_i2c_begun;
		
	public:
	
	drv_i2c_sensor_abstract(address, sda, scl) {
			drv_address = address;
			drv_sda = sda;
			drv_scl = scl;
			drv_i2c_begun = false;
			drv_initalized = false; 
			drv_isEnabled = false;
	}
	
	~drv_i2c_sensor_abstract(void) {delete drv_address; delete drv_sda; delete drv_scl; delete drv_initalized; delete drv_enabled;}
	
	virtual void begin(void);
	virtual void end(void);
	
	void setAddress(uint8_t addr) {drv_address = addr;}
	uint8_t getAddress(void) {return drv_address;}
	
	void setSDAPin(uint8_t sda) {drv_sda = sda;}
	uint8_t getSDAPin(void) {return drv_sda;}
	
	void setSCLPin(uint8_t scl) {drv_scl = scl;}
	uint8_t getSCLPin(void) {return drv_scl;}
	
}


#endif //DRV_I2C_SENSOR_ABSTRACT_H