#ifndef DRV_SENSOR_ABSTRACT_H
#define DRV_SENSOR_ABSTRACT_H

#include <stdint.h>
#include <stdlib.h>

class drv_sensor_abstract {
	
	private:
		bool initalized;
		bool enabled;
		
	public:
	
		virtual drv_sensor_abstract() {initalized = false; isEnabled = false;}
		virtual ~drv_sensor_abstract() {delete initalized; delete enabled;}
		
		virtual bool begin() = 0;
		virtual bool end() = 0;
		
		bool isInitialized() {return initialized;}
		bool isEnabled() {
			if (isInitialized()){
				return enabled;
			}
			return false;
		}
		
		virtual void read() = 0;
		virtual void write() = 0;
	
}


#endif //DRV_SENSOR_ABSTRACT_H