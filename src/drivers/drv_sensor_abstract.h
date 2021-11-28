#ifndef DRV_SENSOR_ABSTRACT_H
#define DRV_SENSOR_ABSTRACT_H

#include <stdint.h>
#include <stdlib.h>

class drv_sensor_abstract {
	
	private:
		bool drv_initalized;
		bool drv_enabled;
		
	public:
	
		virtual drv_sensor_abstract(void) {drv_initalized = false; drv_isEnabled = false;}
		virtual ~drv_sensor_abstract(void) {delete drv_initalized; delete drv_enabled;}
		
		virtual bool begin() = 0;
		virtual bool end() = 0;
		
		virtual void enable(void) {enabled = true;}
		virtual void disable(void) {enabled = false;}
		
		bool isInitialized(void) {return drv_initialized;}
		bool isEnabled(void) {
			if (isInitialized()){
				return drv_enabled;
			}
			return false;
		}
		
		virtual void read() = 0;
		virtual void write() = 0;
	
}


#endif //DRV_SENSOR_ABSTRACT_H