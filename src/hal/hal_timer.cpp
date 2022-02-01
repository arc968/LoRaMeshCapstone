#define HAL_LIB
#include "hal_timer.h"
#include "TimerInterrupt_Generic.h"

#if defined(HW_MKRWAN1300_H)
// Depending on the board, you can select SAMD21 Hardware Timer from TC3-TCC
// SAMD21 Hardware Timer from TC3 or TCC
// SAMD51 Hardware Timer only TC3
SAMDTimer ITimer0(TIMER_TC3);

// Init SAMD_ISR_Timer
// Each SAMD_ISR_Timer can service 16 different ISR-based timers
ISR_Timer SAMD_ISR_Timer;

void hal_timer_handler(void) {
  SAMD_ISR_Timer.run();
  //ITimer0.run();
}

#elif defined(HW_IBUG_H)

#else
	#error "Hardware not yet implemented"
#endif	

static bool timerIsInitialized = false;

void hal_timer_init(void){
	
	if (!timerIsInitialized) {
		
		ITimer0.attachInterruptInterval(1000 * 1000, hal_timer_handler);
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
	
	//SAMD_ISR_Timer.setInterval(interval, isr);
	ITimer0.setInterval(interval, isr);
	
}

