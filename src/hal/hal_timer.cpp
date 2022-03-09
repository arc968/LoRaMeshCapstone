#define HAL_LIB
#include "hal_timer.h"

#if defined(HW_MKRWAN1300_H)
	#include "TimerInterrupt_Generic.h"
	#include "ISR_Timer_Generic.h"
	SAMDTimer ITimer(TIMER_TC3);
	//ISR_Timer hal_ISR_Timer;
#elif defined(HW_RAK4260_H)
	
#else
	#error "Hardware not yet implemented"
#endif	


#if defined(HW_MKRWAN1300_H)
//void hal_timer_handler(void) {
//	hal_ISR_Timer.run();
//}
#endif

#if defined(HW_MKRWAN1300_H)
	
#elif defined(HW_RAK4260_H)
	
#elif defined(HW_RAK4600_H)
	
#elif defined(HW_RAK11300_H)
	
#else
	#error "Hardware not yet implemented"
#endif




static uint8_t timerIsInitialized = 1;

void hal_timer_init(void (*isr)(void), uint16_t interval_us) {
	
	if (timerIsInitialized == 1) {
		timerIsInitialized = 0;
		#if defined(HW_MKRWAN1300_H)
			ITimer.attachInterruptInterval(interval_us, isr);
		#elif defined(HW_RAK4260_H)
			
			HW_TC2.COUNT16.CTRLA.ENABLE &= ~HW_TC_CTRLA_ENABLE;
			
			HW_TC2.COUNT16.CTRLA.SWRST &= HW_TC_CTRLA_SWRST;
			
			//need to use the 48MHz clk set that up with GCLK
			
			HW_GCLK.GENCTRL[1].reg = HW_GCLK_GENCTRL_SRC_DFLL48M | HW_GCLK_GENCTRL_RUNSTDBY;
			
			HW_GCLK.GENCTRL[1].reg |= HW_GCLK_GENCTRL_GENEN;
			
			HW_GCLK.PCHCTRL[28].reg = HW_GCLK_PCHCTRL_GEN_GCLK1_Val;
			
			while(HW_GCLK.SYNCBUSY != 0x0):
			
			HW_GCLK.PCHCTRL[28].reg |= HW_GCLK_PCHCTRL_CHEN;
			
			while(HW_TC2.COUNT16.SYNCBUSY.reg != 0x0);
			
			HW_TC2.COUNT16.CTRLA.reg |= HW_TC_CTRLA_MODE_COUNT16 | HW_TC_CTRLA_PRESCALER_DIV2_Val;
			
			HW_TC2.COUNT16.CTRLBSET.reg |= HW_TC_CTRLBSET_DIR;
			
			HW_TC2.COUNT16.INTFLAG.reg = HW_TC_INTFLAG_RESETVALUE;
			
			HW_TC2.COUNT16.INTSET.reg = HW_TC_INTENSET_MC0;
			
			
			HW_TC2.COUNT16.CC[0].reg = interval_us;	//(48MHz / 2) / 1000 = 1msec , count = 23999
			
			
			//set interrupt to the isr
			TC2_Handler = isr; //I think this works not sure	(void*) TC2_Handler => (void) (*isr)(void)
			
			HW_TC2.COUNT16.COUNT.reg = 0x0000;
			
			while(HW_TC2.COUNT16.SYNCBUSY.reg != 0);
			HW_TC2.COUNT16.CTRLA.ENABLE &= HW_TC_CTRLA_ENABLE;
			
			
		#elif defined(HW_RAK4600_H)
			
		#elif defined(HW_RAK11300_H)
			
		#else
			#error "Hardware not yet implemented"
		#endif	
	}
	
}

void hal_timer_delay(uint16_t msdelay) {
	
	#if defined(HW_ARDUINO)
		delay(msdelay);	
	#elif defined(HW_RAK4260_H)
		
	#elif defined(HW_RAK4600_H)
			
	#elif defined(HW_RAK11300_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
	
}

uint32_t hal_timer_millis(void) {
	
	#if defined(HW_ARDUINO)
		return millis();	
	#elif defined(HW_RAK4260_H)
		return 0; //TODO
	#elif defined(HW_RAK4600_H)
		return 0; //TODO
	#elif defined(HW_RAK11300_H)
		return 0; //TODO
	#else
		#error "Hardware not yet implemented"
	#endif
	
}

/*
void hal_timer_setInterruptInterval(void (*isr)(void), uint32_t interval) {
	
	hal_ISR_Timer.setInterval(interval, isr);
	
}
*/

