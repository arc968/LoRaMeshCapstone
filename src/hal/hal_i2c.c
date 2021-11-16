#define HAL_LIB
#include "hal_i2c.h"

#ifdef HW_ARDUINO
	#include <Wire.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif


/*
	void func() {
		#ifdef HW_ARDUINO
			Wire.begin();
		#elif HW_IBUG_H
			
		#else
			#error "Hardware not yet implemented"
		#endif
	}
*/


#ifdef __cplusplus
}
#endif