#define HAL_LIB
#include "hal_power.h"

#if defined(HW_MKRWAN1300_H)
	#include "ArduinoLowPower.h"
#elif defined(HW_IBUG_H)

#else
	#error "Hardware not yet implemented"
#endif	



void hal_power_mode(enum hw_power_pwrmodes_e pwrmode, uint16_t millis) {

#if defined(HW_ARDUINO)
	
	if (pwrmode == PWR_FULL) {
		hal_power_wake();
	}
	else if (pwrmode == PWR_IDLE) {
		LowPower.idle(millis);
	}
	else if (pwrmode == PWR_LOW_POWER) {
		LowPower.sleep(millis);
	}
	else if (pwrmode == PWR_ULTRA_LOW_POWER) {
		LowPower.deepSleep(millis);
	}
	else {
		LowPower.deepSleep(millis);
	}
	
#elif defined(HW_IBUG_H)

#else
	#error "Hardware not yet implemented"
#endif	

}

void hal_power_wake(void) {
	
	
	
}


#if defined(HW_MKRWAN1300_H)
void hal_power_attachInterruptWakeup(uint8_t pin) {
	LowPower.attachInterruptWakeup(pin, hal_power_wake, RISING);
}
#endif