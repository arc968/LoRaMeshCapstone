#define HAL_LIB
#include "hal_power.h"
#include "hal_rtc.h"

#if defined(HW_MKRWAN1300_H)
	#include "ArduinoLowPower.h"
#elif defined(HW_RAK4260_H)

#elif defined(HW_RAK4600_H)
			
#elif defined(HW_RAK11300_H)
	
#else
	#error "Hardware not yet implemented"
#endif	

void hal_power_wake(void) {	
#if defined(HW_MKRWAN1300_H)
	
#elif defined(HW_RAK4260_H)
	
#elif defined(HW_RAK4600_H)
	
#elif defined(HW_RAK11300_H)
	
#else
	#error "Hardware not yet implemented"
#endif
}

void hal_power_idle(uint16_t seconds) {
#if defined(HW_MKRWAN1300_H)
	LowPower.idle(seconds);
#elif defined(HW_RAK4260_H)
	
	//set the sleep mode power reg
	
	//turn on the clk for the rtc to run
	hal_rtc_enable();
	
	//__wfi();
	//WFI();
	//__asm("WFI()");					the WFI thing is one of these 4 options whichever compiles
	//__attribute__((naked)) WFI();

	//clear interupt flag to use again

	
#elif defined(HW_RAK4600_H)
	
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
	
	//TODO impliment timer interrupt wake control
	
#elif defined(HW_RAK11300_H)
	
	
	//__wfi();
	
#else
	#error "Hardware not yet implemented"
#endif
}

void hal_power_sleep(uint16_t seconds) {
#if defined(HW_MKRWAN1300_H)
	LowPower.sleep(seconds);
#elif defined(HW_RAK4260_H)
	
	//set the sleep mode power reg
	//need standby mode 3
	
	//turn on the clk for the rtc to run
	hal_rtc_enable();
	
	//__wfi();
	//WFI();
	//__asm("WFI()");					the WFI thing is one of these 4 options whichever compiles
	//__attribute__((naked)) WFI();
	
	//clear interupt flag to use again

	
#elif defined(HW_RAK4600_H)
	
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
	
	//TODO impliment timer interrupt wake control
	
#elif defined(HW_RAK11300_H)
	
	
	//__wfi();
	
#else
	#error "Hardware not yet implemented"
#endif
}

void hal_power_deepSleep(uint16_t seconds) {
#if defined(HW_MKRWAN1300_H)
	LowPower.deepSleep(seconds);
#elif defined(HW_RAK4260_H)
	
	//set the sleep mode power reg
	
	//turn on the clk for the rtc to run
	hal_rtc_enable();
	
	//__wfi();
	//WFI();
	//__asm("WFI()");					the WFI thing is one of these 4 options whichever compiles
	//__attribute__((naked)) WFI();
	
	//clear interupt flag to use again
	
#elif defined(HW_RAK4600_H)
	
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
	
	//TODO impliment timer interrupt wake control

#elif defined(HW_RAK11300_H)
	
	
	//__wfi();
	
#else
	#error "Hardware not yet implemented"
#endif
}

void hal_power_mode(enum hw_power_pwrmodes_e pwrmode, uint16_t seconds) {
	
	static uint8_t powertimersetup = 1;
	
	if (powertimersetup != 0) {
		
		#if defined(HW_MKRWAN1300_H)
			
		#elif defined(HW_RAK4260_H)
			
			//have to use rtc cant use tc in deep sleep
			
			hal_rtc_init();
			
			hal_rtc_disable();
			
			//hal_rtc_setCount(0x00000000);
			
			//hal_rtc_setCompare(/*set to 1ms * milis val*/);
			
			//hal_rtc_enableCompareInterrupt();
			
			//set gclk to run in deep sleep for the rtc
			
		#elif defined(HW_RAK4600_H)
				
		#elif defined(HW_RAK11300_H)
			
		#else
			#error "Hardware not yet implemented"
		#endif
				
		powertimersetup = 0;
	}

	if (pwrmode == PWR_FULL) {
		hal_power_wake();
	}
	else if (pwrmode == PWR_IDLE) {
		hal_power_idle(seconds);
	}
	else if (pwrmode == PWR_SLEEP) {
		hal_power_sleep(seconds);
	}
	else if (pwrmode == PWR_DEEP_SLEEP) {
		hal_power_deepSleep(seconds);
	}
	else {
		hal_power_deepSleep(seconds);
	}

}

void hal_power_softReset(void) {
#if defined(HW_MKRWAN1300_H)
	HW_POWER_AIRCR = 0x05FA0004;
	while(1) {/* wait until reset */}
#elif defined(HW_RAK4260_H)
	SYSCTRL_AIRCR->reg = 0x05FA0004;
	while(1) {/* wait until reset */}
#elif defined(HW_RAK4600_H)
	HW_POWER_AIRCR = 0x05FA0004;
	while(1) {/* wait until reset */}
#elif defined(HW_RAK11300_H)
	HW_POWER_AIRCR = 0x05FA0004;
	while(1) {/* wait until reset */}
#else
	#error "Hardware not yet implemented"
#endif
}


#if defined(HW_MKRWAN1300_H)
void hal_power_attachInterruptWakeup(uint8_t pin) {
	LowPower.attachInterruptWakeup(pin, hal_power_wake, RISING);
}
#endif