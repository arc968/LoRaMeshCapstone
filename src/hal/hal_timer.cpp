#define HAL_LIB
#include "hal_timer.h"

#if defined(HW_MKRWAN1300_H)
	//#include "TimerInterrupt_Generic.h"
	//#include "ISR_Timer_Generic.h"
	//SAMDTimer ITimer(TIMER_TC3);
#elif defined(HW_IBUG_H)
	
#else
	#error "Hardware not yet implemented"
#endif	

//ISR_Timer hal_ISR_Timer;

#if defined(HW_MKRWAN1300_H)
void hal_timer_handler(void) {
	hal_ISR_Timer.run();
}
#endif


static bool timerIsInitialized = false;

void hal_timer_init(void (*isr)(void), uint32_t interval_us) {
	
	if (!timerIsInitialized) {
		timerIsInitialized = true;
		#if defined(HW_MKRWAN1300_H)
			//ITimer.attachInterruptInterval(interval_us, isr);
		#elif defined(HW_IBUG_H)
			
		#else
			#error "Hardware not yet implemented"
		#endif	
	}
	
}

void hal_timer_delay(uint16_t msdelay) {
	
	#if defined(HW_ARDUINO)
		delay(msdelay);	
	#elif defined(HW_IBUG_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
	
}

uint32_t hal_timer_millis(void) {
	
	#if defined(HW_ARDUINO)
		return millis();	
	#elif defined(HW_IBUG_H)
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

