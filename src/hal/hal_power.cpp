#define HAL_LIB
#include "hal_power.h"

#if defined(HW_MKRWAN1300_H)
	#include "ArduinoLowPower.h"
#elif defined(HW_IBUG_H)

#else
	#error "Hardware not yet implemented"
#endif	

void hal_power_wake(void) {	
#if defined(HW_ARDUINO)
	
#elif defined(HW_IBUG_H)
	
	
	
#else
	#error "Hardware not yet implemented"
#endif
}

void hal_power_idle(uint16_t millis) {
#if defined(HW_ARDUINO)
	LowPower.idle(millis);
#elif defined(HW_IBUG_H)
	
	HW_POWER_SYSTEMOFF = 0x00000000;
	
	HW_POWER_RAM0_POWERSET = 0x0003FFFF;
	HW_POWER_RAM1_POWERSET = 0x0003FFFF;
	HW_POWER_RAM2_POWERSET = 0x0003FFFF;
	HW_POWER_RAM3_POWERSET = 0x0003FFFF;
	HW_POWER_RAM4_POWERSET = 0x0003FFFF;
	HW_POWER_RAM5_POWERSET = 0x0003FFFF;
	HW_POWER_RAM6_POWERSET = 0x0003FFFF;
	HW_POWER_RAM7_POWERSET = 0x0003FFFF;
	
	HW_POWER_TASKS_LOWPWR = 0x00000000;
	HW_POWER_TASKS_CONSTLAT = 0x00000001;
	
#else
	#error "Hardware not yet implemented"
#endif
}

void hal_power_sleep(uint16_t millis) {
#if defined(HW_ARDUINO)
	LowPower.sleep(millis);
#elif defined(HW_IBUG_H)
	
	HW_POWER_SYSTEMOFF = 0x00000000;
	
	HW_POWER_RAM0_POWERSET = 0x0003FFFF;
	HW_POWER_RAM1_POWERSET = 0x0003FFFF;
	HW_POWER_RAM2_POWERSET = 0x0003FFFF;
	HW_POWER_RAM3_POWERSET = 0x0003FFFF;
	HW_POWER_RAM4_POWERSET = 0x0003FFFF;
	HW_POWER_RAM5_POWERSET = 0x0003FFFF;
	HW_POWER_RAM6_POWERSET = 0x0003FFFF;
	HW_POWER_RAM7_POWERSET = 0x0003FFFF;
	
	HW_POWER_TASKS_CONSTLAT = 0x00000000;
	HW_POWER_TASKS_LOWPWR 	= 0x00000001;	
	
#else
	#error "Hardware not yet implemented"
#endif
}

void hal_power_deepSleep(uint16_t millis) {
#if defined(HW_ARDUINO)
	LowPower.deepSleep(millis);
#elif defined(HW_IBUG_H)
	
	HW_POWER_SYSTEMOFF = 0x00000000;
	
	HW_POWER_RAM0_POWERSET = 0x0003FFFF;
	HW_POWER_RAM1_POWERSET = 0x0003FFFF;
	HW_POWER_RAM2_POWERSET = 0x0003FFFF;
	HW_POWER_RAM3_POWERSET = 0x0003FFFF;
	HW_POWER_RAM4_POWERSET = 0x0003FFFF;
	HW_POWER_RAM5_POWERSET = 0x0003FFFF;
	HW_POWER_RAM6_POWERSET = 0x0003FFFF;
	HW_POWER_RAM7_POWERSET = 0x0003FFFF;
	
	HW_POWER_TASKS_CONSTLAT = 0x00000000;
	HW_POWER_TASKS_LOWPWR 	= 0x00000001;	
	
#else
	#error "Hardware not yet implemented"
#endif
}

void hal_power_mode(enum hw_power_pwrmodes_e pwrmode, uint16_t millis) {

	if (pwrmode == PWR_FULL) {
		hal_power_wake();
	}
	else if (pwrmode == PWR_IDLE) {
		hal_power_idle(millis);
	}
	else if (pwrmode == PWR_LOW_POWER) {
		hal_power_sleep(millis);
	}
	else if (pwrmode == PWR_ULTRA_LOW_POWER) {
		hal_power_deepSleep(millis);
	}
	else {
		hal_power_deepSleep(millis);
	}

}


#if defined(HW_MKRWAN1300_H)
void hal_power_attachInterruptWakeup(uint8_t pin) {
	LowPower.attachInterruptWakeup(pin, hal_power_wake, RISING);
}
#endif