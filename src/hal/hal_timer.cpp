#define HAL_LIB
#include "hal_timer.h"
#include "TimerInterrupt_Generic.h"

#if defined(HW_MKRWAN1300_H)
// Depending on the board, you can select SAMD21 Hardware Timer from TC3-TCC
// SAMD21 Hardware Timer from TC3 or TCC
// SAMD51 Hardware Timer only TC3
SAMDTimer ITimer(TIMER_TC3);

#elif defined(HW_IBUG_H)

#else
	#error "Hardware not yet implemented"
#endif

ISR_Timer hal_ISR_Timer;

void isr_hal_timer_handler(void) {
  hal_ISR_Timer.run();
}	

static bool timerIsInitialized = false;

void hal_timer_init(void){
	
	if (!timerIsInitialized) {
		
		ITimer.attachInterruptInterval(1000 * 1000, isr_hal_timer_handler);
		timerIsInitialized = true;
	
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

void hal_timer_setInterruptInterval(void (*isr)(void), uint32_t interval) {
	
	hal_ISR_Timer.setInterval(interval, isr);
	
}

