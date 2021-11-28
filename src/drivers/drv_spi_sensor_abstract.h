#ifndef DRV_SPI_SENSOR_ABSTRACT_H
#define DRV_SPI_SENSOR_ABSTRACT_H

#include "drv_sensor_abstract.h"

class drv_spi_sensor_abstract : drv_sensor_abstract{
	
	private:
		
		uint8_t drv_cs, drv_mosi, drv_miso, drv_clk;
		
	public:
	
	virtual drv_spi_sensor_abstract(cs, mosi, miso, clk) {
			drv_cs = cs;
			drv_mosi = mosi;
			drv_miso = miso;
			drv_clk = clk;
	}
	
	virtual ~drv_spi_sensor_abstract(void) {delete drv_cs; delete drv_mosi; delete drv_miso; delete drv_clk;}
	
	virtual void setCSPin(uint8_t cs) {drv_cs = cs;}
	virtual uint8_t getCSPin(void) {return drv_cs;}
	
	virtual void setMOSIPin(uint8_t mosi) {drv_mosi = mosi;}
	virtual uint8_t getMOSIPin(void) {return drv_mosi;}
	
	virtual void setMISOPin(uint8_t miso) {drv_miso = miso;}
	virtual uint8_t getMISOPin(void) {return drv_miso;}
	
	virtual void setClkPin(uint8_t clk) {drv_clk = clk;}
	virtual uint8_t getCLKPin(void) {return drv_clk;}
}


#endif //DRV_SPI_SENSOR_ABSTRACT_H