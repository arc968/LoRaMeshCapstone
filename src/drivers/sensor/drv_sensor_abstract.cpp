#include "drv_sensor_abstract.h"
#include "../../hal/hal.h"

bool drv_sensor_abstract :: isEnabled(void) {
	if (isInitialized()){
		return drv_enabled;
	}
	return false;
}
