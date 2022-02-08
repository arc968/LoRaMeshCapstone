#ifndef DRV_I2C_ABSTRACT_H
#define DRV_I2C_ABSTRACT_H

#include "drv_sensor_abstract.h"

class drv_i2c_abstract : public drv_sensor_abstract{
	
	protected:
		
		uint8_t drv_address, drv_sda, drv_scl;
		
	public:
	
	drv_i2c_abstract(uint8_t address, uint8_t sda, uint8_t scl)/* : drv_sensor_abstract()*/{
			drv_address = address;
			drv_sda = sda;
			drv_scl = scl;
			//drv_initalized = false; 
			//drv_enabled = false;
	}
	
	~drv_i2c_abstract(void) {}
	
	virtual void begin(void);
	virtual void end(void);
	
	virtual void write(uint8_t * buf, uint16_t byteLength);
	virtual bool read(uint8_t* buf, uint16_t buflength);
	
	void setAddress(uint8_t addr) {drv_address = addr;}
	uint8_t getAddress(void) {return drv_address;}
	
	void setSDAPin(uint8_t sda) {drv_sda = sda;}
	uint8_t getSDAPin(void) {return drv_sda;}
	
	void setSCLPin(uint8_t scl) {drv_scl = scl;}
	uint8_t getSCLPin(void) {return drv_scl;}
	
};


#endif //DRV_I2C_ABSTRACT_H