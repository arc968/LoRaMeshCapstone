#ifndef DRV_SENSOR_ABSTRACT_H
#define DRV_SENSOR_ABSTRACT_H

#include <stdint.h>
#include <stdlib.h>

class drv_sensor_abstract {
	
	private:
		bool drv_initalized;
		bool drv_enabled;
		
	public:
	
		virtual drv_sensor_abstract(void) {drv_initalized = false; drv_enabled = false;}
		virtual ~drv_sensor_abstract(void) {}
		
		virtual bool begin() = 0;
		virtual bool end() = 0;
		
		virtual void enable(void) {drv_enabled = true;}
		virtual void disable(void) {drv_enabled = false;}
		
		virtual bool isInitialized(void) {return drv_initialized;}
		bool isEnabled(void);
		
		virtual uint8_t read() = 0;
		virtual void write() = 0;
	
}


#endif //DRV_SENSOR_ABSTRACT_H