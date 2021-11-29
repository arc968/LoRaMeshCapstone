#ifndef DRV_SERIAL_SENSOR_ABSTRACT_H
#define DRV_SERIAL_SENSOR_ABSTRACT_H

#include "drv_sensor_abstract.h"

class drv_serial_sensor_abstract : drv_sensor_abstract{
	
	private:
		
		uint8_t drv_baud, drv_tx, drv_rx;
		static bool drv_serial_begun;
		
		
	public:
	
	drv_spi_sensor_abstract(baud, tx, rx) {			
			drv_baud = baud;
			drv_tx = tx;
			drv_rx = rx;
			drv_serial_begun = false;
			drv_initalized = false; 
			drv_isEnabled = false;
	}
	
	~drv_spi_sensor_abstract(void) {delete drv_baud; delete drv_initalized; delete drv_enabled;}
	
	virtual void begin(void);
	virtual void end(void);
	
	virtual bool isInitialized(void);
	
	uint8_t getBaud(void) {return drv_baud;}
	
	void setTXPin(uint8_t tx) {drv_tx = tx;}
	uint8_t getTXPin(void) {return drv_tx;}
	
	void setRXPin(uint8_t rx) {drv_rx = rx;}
	uint8_t getRXPin(void) {return drv_rx;}
}


#endif //DRV_SERIAL_SENSOR_ABSTRACT_H