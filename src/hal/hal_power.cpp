#define HAL_LIB
#include "hal_power.h"
#include "hal_rtc.h"
#include "hal_timer.h"
#include "hal_interrupt.h"

#if defined(HW_MKRWAN1300_H)
	#if defined(HW_ARDUINO)
		#include "ArduinoLowPower.h"
	#endif
#elif defined(HW_RAK4260_H)

#elif defined(HW_RAK4600_H)
			
#elif defined(HW_RAK11300_H)
	
#else
	#error "Hardware not yet implemented"
#endif	

static uint8_t rtcenable = 1, interruptwasdisabled = 0;;
static uint64_t currentmillis;
static lib_datetime_s * wakeAlarm;

void hal_power_wake(void) {	
	#if defined(HW_MKRWAN1300_H)
		
	#elif defined(HW_RAK4260_H)
		
	#elif defined(HW_RAK4600_H)
		
	#elif defined(HW_RAK11300_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
}

void hal_power_idle() {
	
	#if defined(HW_MKRWAN1300_H)
		#if defined(HW_ARDUINO)
				do {
					//LowPower.idle();
					SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
					PM->SLEEP.reg = 0;
					__DSB();
					__WFI();
				} while (rtcenable ? (!hal_rtc_compareClockToAlarm()) : 0);
		#else
			
		#endif
	#elif defined(HW_RAK4260_H)
		
		//set the sleep mode power reg
		PM->SLEEPCFG.bit.SLEEPMODE = 0x2;
		
		if (rtcenable) {
			//turn on the clk for the rtc to run
			hal_rtc_enable();
		}
		
		do {
			//wait for interrupt compiler command
			__asm("WFI");
		} while (rtcenable ? (!hal_rtc_compareClockToAlarm()) : 0);
		
		
		currentmillis = hal_timer_millis();
		
		/*do {
			//wait for interrupt compiler command
			__asm("WFI");
		} while (wakeAlarm->ms < hal_timer_millis() - currentmillis);*/
		
		
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
	
	//clear interupt flag to use again
	hal_rtc_clearAlarmInterrupt();
	hal_rtc_disable();

}

void hal_power_sleep() {
	
	#if defined(HW_MKRWAN1300_H)
		#if defined(HW_ARDUINO)
			do {
				LowPower.sleep();
			} while (rtcenable ? (!hal_rtc_compareClockToAlarm()) : 0);
		#else
			
		#endif
	#elif defined(HW_RAK4260_H)
		
		//set the sleep mode power reg
		PM->SLEEPCFG.bit.SLEEPMODE = 0x4;
		
		if (rtcenable) {
			//turn on the clk for the rtc to run
			hal_rtc_enable();
		}
		
		do {
			//wait for interrupt compiler command
			__asm("WFI");
		} while (rtcenable ? (!hal_rtc_compareClockToAlarm()) : 0);
		
		
		/*currentmillis = hal_timer_millis();
		
		do {
			//wait for interrupt compiler command
			__asm("WFI");
		} while (wakeAlarm->ms < hal_timer_millis() - currentmillis);*/

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
	
	//clear interupt flag to use again
	hal_rtc_clearAlarmInterrupt();
	hal_rtc_disable();
	
}

void hal_power_deepSleep() {
	
	#if defined(HW_MKRWAN1300_H)
		#if defined(HW_ARDUINO)
			while (rtcenable ? (!hal_rtc_compareClockToAlarm()) : 0) {
				LowPower.deepSleep();
			}
		#else
			
		#endif
	#elif defined(HW_RAK4260_H)
		
		//set the sleep mode power reg
		PM->SLEEPCFG.bit.SLEEPMODE = 0x5;
		
		if (rtcenable) {
			//turn on the clk for the rtc to run
			hal_rtc_enable();
		}
		
		//deep sleep resets millis() count so deep sleep cannot support millisecond preceicion
		do {
			//wait for interrupt compiler command
			__asm("WFI");
		} while (rtcenable ? (!hal_rtc_compareClockToAlarm()) : 0);
		
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
	
	//clear interupt flag to use again
	hal_rtc_clearAlarmInterrupt();
	hal_rtc_disable();

}

void hal_power_setMode(enum hw_power_pwrmodes_e pwrmode, struct lib_datetime_s * alarm) {
	
	static uint8_t powertimersetup = 0;
	
	wakeAlarm = alarm;
	
	if (!powertimersetup || !hal_rtc_isInitialized()) {
		
		#if defined(HW_MKRWAN1300_H)
			#if defined(HW_ARDUINO)	
				//none
			#else
				
				
				
			#endif
		#elif defined(HW_RAK4260_H)
			
			//have to use rtc cant use tc in deep sleep
			//warning any running peripheral in sleep mode or idle mode that triggers an interrupt triggers a wake event as well
			
			hal_rtc_init();
			
			hal_rtc_disable();
			
			hal_rtc_enableAlarmInterrupt();
			
			PM->STDBYCFG.reg = PM_STDBYCFG_RESETVALUE;
			
			WDT->CTRLA.reg = WDT_CTRLA_RESETVALUE;
			
		#elif defined(HW_RAK4600_H)
				
		#elif defined(HW_RAK11300_H)
			
		#else
			#error "Hardware not yet implemented"
		#endif
				
		powertimersetup = 1;
	}
	
	rtcenable = 1;
	hal_rtc_clearAlarmInterrupt();
	
	if (wakeAlarm != NULL) {
		hal_rtc_setAlarm(wakeAlarm);
	}
	else {
		rtcenable = 0;
	}
	
	hal_rtc_clearClock();
	
	//must ensure that global interrups are enabled to be able to trigger a wake event interrupt
	/*interruptwasdisabled = 0;
	if (!hal_interrupt_isEnabled()) {
		hal_interrupt_enable();
		interruptwasdisabled = 1;
	}*/

	if (pwrmode == PWR_FULL) {
		hal_power_wake();
	}
	else if (pwrmode == PWR_IDLE) {
		hal_power_idle();
	}
	else if (pwrmode == PWR_SLEEP) {
		hal_power_sleep();
	}
	else if (pwrmode == PWR_DEEP_SLEEP) {
		hal_power_deepSleep();
	}
	else {
		//hal_power_idle();
	}
	
	/*if (interruptwasdisabled) {
		hal_interrupt_disable();
	}*/

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