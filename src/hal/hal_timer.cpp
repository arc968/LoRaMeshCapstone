#define HAL_LIB
#include "hal_timer.h"

#include "TimerInterrupt_Generic.h"
#include "ISR_Timer_Generic.h"

#if defined(HW_MKRWAN1300_H)
	SAMDTimer ITimer(TIMER_TC3);
#elif defined(HW_IBUG_H)
	SAMDTimer ITimer(TIMER_TC3);
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
		//ITimer.attachInterruptInterval(1000, hal_timer_handler);
		#if defined(HW_MKRWAN1300_H)
			ITimer.attachInterruptInterval(interval_us, isr);
		#elif defined(HW_IBUG_H)
			ITimer.attachInterruptInterval(interval_us, isr);
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

