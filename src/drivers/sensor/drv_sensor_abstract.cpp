#include "drv_spi_sensor_abstract.h"
#include "../hal/hal.h"

bool isEnabled(void) {
	if (isInitialized()){
		return drv_enabled;
	}
	return false;
}
