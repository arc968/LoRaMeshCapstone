#define HAL_LIB
#include "../hardware/hardware.h"

#include "hal_gpio.h"

void hal_timer_delay(uint16_t msdelay) {
	
	#ifdef HW_ARDUINO
		delay(msdelay);	
	#elif HW_IBUG_H
	
	#else
		#error "Hardware not yet implemented"
	#endif
	
}

uint32_t hal_timer_millis(void) {
	
	#ifdef HW_ARDUINO
		return millis();	
	#elif HW_IBUG_H
	
	#else
		#error "Hardware not yet implemented"
	#endif
	
}