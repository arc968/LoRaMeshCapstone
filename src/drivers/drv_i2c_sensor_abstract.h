#ifndef DRV_I2C_SENSOR_ABSTRACT_H
#define DRV_I2C_SENSOR_ABSTRACT_H

#include "drv_sensor_abstract.h"

class drv_i2c_sensor_abstract : drv_sensor_abstract{
	
	private:
		
		uint8_t drv_address, drv_sda, drv_acl;
		
	public:
	
	virtual drv_i2c_sensor_abstract(address, sda, scl) {
			drv_address = address;
			drv_sda = sda;
			drv_scl = scl;
	}
	
	virtual ~drv_spi_sensor_abstract(void) {delete drv_address; delete drv_sda; delete drv_scl;}
	
	virtual void setAddress(uint8_t addr) {drv_address = addr;}
	virtual uint8_t getAddress(void) {return drv_address;}
	
	virtual void setSDAPin(uint8_t sda) {drv_sda = sda;}
	virtual uint8_t getSDAPin(void) {return drv_sda;}
	
	virtual void setSCLPin(uint8_t scl) {drv_scl = scl;}
	virtual uint8_t getSCLPin(void) {return drv_scl;}
	
}


#endif //DRV_I2C_SENSOR_ABSTRACT_H