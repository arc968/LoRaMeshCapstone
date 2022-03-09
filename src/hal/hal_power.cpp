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

void hal_power_idle(uint16_t millis) {
#if defined(HW_MKRWAN1300_H)
	LowPower.idle(millis);
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

void hal_power_sleep(uint16_t millis) {
#if defined(HW_MKRWAN1300_H)
	LowPower.sleep(millis);
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

void hal_power_deepSleep(uint16_t millis) {
#if defined(HW_MKRWAN1300_H)
	LowPower.deepSleep(millis);
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

void hal_power_mode(enum hw_power_pwrmodes_e pwrmode, uint16_t millis) {
	
	static uint8_t powertimersetup = 1;
	
	if (powertimersetup != 0) {
		
		#if defined(HW_MKRWAN1300_H)
			
		#elif defined(HW_RAK4260_H)
			/*//setup milisecond timer interval on tc0 with 16 percision
			HW_TC0_CTRLA &= HW_TCxCTRLA_DISABLE;
			
			//setup milisecond timer interval on tc0 with 16 percision
			//GCLK has to use the 48MHz clk then we divide by 2
				
			HW_TC0_CTRLA |= HW_TCxCTRLA_COUNT16MODE | HW_TCxCTRLA_PRESCALER_DIV2;
			
			HW_TC0_CTRLBSET |= HW_TCxCTRLBSET_COUNTUP | HW_TCxCTRLBSET_STOP;
			
			HW_TC0_INTFLAG = 0x00;
			HW_TC0_INTSET = 0x10;
			
			HW_TC0_CC0 = 0x5DBF; 	// (48MHz/2) / 1000 = 1ms = 23999 = 0x5DBF
			
			//connect TC_CC0 interrupt on compare equal to the wake event
			
			//sleep functions MUST request that GCLK keeps the 48MHz clk on durring low power modes
			
			HW_TC0_CTRLA |= HW_TCx_ENABLE;*/
			
			//have to use rtc cant use tc in deep sleep
			
			hal_rtc_init(RTC_32COUNT, 0x1/* fix this */);
			
			hal_rtc_disable();
			
			hal_rtc_setCount(0x00000000);
			
			hal_rtc_setCompare(/*set to 1ms * milis val*/);
			
			hal_rtc_enableCompareInterrupt(void);
			
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
		hal_power_idle(millis);
	}
	else if (pwrmode == PWR_SLEEP) {
		hal_power_sleep(millis);
	}
	else if (pwrmode == PWR_DEEP_SLEEP) {
		hal_power_deepSleep(millis);
	}
	else {
		hal_power_deepSleep(millis);
	}

}

void hal_power_softReset(void) {
#if defined(HW_MKRWAN1300_H)
	HW_POWER_AIRCR = 0x05FA0004;
	while(1) {/* wait until reset */}
#elif defined(HW_RAK4260_H)
	HW_SCS_AIRCR.reg = 0x05FA0004;
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