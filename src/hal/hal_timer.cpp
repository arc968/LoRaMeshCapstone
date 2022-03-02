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


static uint8_t timerIsInitialized = 0;

void hal_timer_init(void (*isr)(void), uint32_t interval_us) {
	
	if (timerIsInitialized == 0) {
		timerIsInitialized = 1;
		#if defined(HW_MKRWAN1300_H)
			ITimer.attachInterruptInterval(interval_us, isr);
		#elif defined(HW_RAK4260_H)
			//disable TC to write to setup registers CTRLA->ENABLE bit = 0
			
			//enable tc bus clk
			
			//select tc size, desired 16 or 32 bit CTRLA -> Mode Bits default is 16 bit counter
			
			//set count direction to up CTRLBSET ->DIR bit 
			
			
			
			
			//reenable TC
			
			HW_TC2_CTRLA &= HW_TCxCTRLA_DISABLE;
			
			HW_TC2_CTRLA |= HW_TCxCTRLA_COUNT32MODE | HW_TCxCTRLA_PRESCALER_DIV1;
			
			HW_TC2_CTRLBSET |= HW_TCxCTRLBSET_COUNTUP;
			
			HW_TC2_INTFLAG = 0x00;
			
			TW_TC2_INTSET = 0x10;
			
			
			
			
			
			HW_TC0_CTRLA |= HW_TCx_ENABLE;
			
			
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

