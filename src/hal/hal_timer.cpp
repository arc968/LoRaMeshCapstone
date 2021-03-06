#define HAL_LIB
#include "hal_timer.h"

#if defined(HW_MKRWAN1300_H)
	
	#if defined(HW_ARDUINO)	
		#include "TimerInterrupt_Generic.h"
		#include "ISR_Timer_Generic.h"
		SAMDTimer ITimer(TIMER_TC3);
		//ISR_Timer hal_ISR_Timer;

		//void hal_timer_handler(void) {
		//	hal_ISR_Timer.run();
		//}
	#else
		
		
		
	#endif
	
#elif defined(HW_RAK4260_H)

	static volatile uint64_t currentMillisRunTime = 0;

	static void (* isrfunc)(void);

	void TC2_Handler(void) {
		
		TC2->COUNT16.INTFLAG.reg = ~TC_INTFLAG_RESETVALUE;
		isrfunc();
		
	}
		
	void TC0_Handler(void) {
		
		currentMillisRunTime++;
		//RTC->MODE2.GP[0].reg++;
		TC0->COUNT32.INTFLAG.reg = ~TC_INTFLAG_RESETVALUE;
		
	}
	
#elif defined(HW_RAK4600_H)
	
#elif defined(HW_RAK11300_H)
	
#else
	#error "Hardware not yet implemented"
#endif


static uint8_t timerIsInitialized = 1, gclksetup = 1, millisisinitialized = 1;


void hal_timer_init(void (*isr)(void), uint16_t interval_us) {
	
	if (timerIsInitialized == 1) {
		timerIsInitialized = 0;
		#if defined(HW_MKRWAN1300_H)
		
			#if defined(HW_ARDUINO)	
				ITimer.attachInterruptInterval(interval_us, isr);
			#else
				
				
				
			#endif
			
		#elif defined(HW_RAK4260_H)
			
			TC2->COUNT16.CTRLA.reg &= ~TC_CTRLA_ENABLE;
			
			TC2->COUNT16.CTRLA.reg &= TC_CTRLA_SWRST;
			
			if (gclksetup != 0) {
				//need to use the 48MHz clk set that up with GCLK
				
				GCLK->GENCTRL[1].reg = GCLK_GENCTRL_SRC_DFLL48M | GCLK_GENCTRL_RUNSTDBY;
				
				GCLK->GENCTRL[1].reg |= GCLK_GENCTRL_GENEN;
				
				GCLK->PCHCTRL[28].reg = GCLK_PCHCTRL_GEN_GCLK1_Val;
				
				while(GCLK->SYNCBUSY.reg != 0x0);
				
				gclksetup = 0;
			}
			
			GCLK->PCHCTRL[28].reg |= GCLK_PCHCTRL_CHEN;
			
			while(TC2->COUNT16.SYNCBUSY.reg != 0x0);
			
			TC2->COUNT16.CTRLA.reg |= TC_CTRLA_MODE_COUNT16 | TC_CTRLA_PRESCALER_DIV64;
			
			TC2->COUNT16.CTRLBSET.reg |= TC_CTRLBSET_DIR;
			
			TC2->COUNT16.INTFLAG.reg = ~TC_INTFLAG_RESETVALUE;
			
			TC2->COUNT16.INTENSET.reg = TC_INTENSET_MC0;
			TC2->COUNT16.EVCTRL.reg = TC_EVCTRL_MCEO0;
			
			TC2->COUNT16.CC[0].reg = interval_us;	//0.001sec = (max-count + 1) * (1/(48 * 10^6)Hz/64) , count = 749 -> 1ms interval
			
			
			//set interrupt to the isr
			isrfunc = isr;
			
			TC2->COUNT16.COUNT.reg = 0x0000;
			
			while(TC2->COUNT16.SYNCBUSY.reg != 0);
			TC2->COUNT16.CTRLA.reg |= TC_CTRLA_ENABLE;
			
			
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
	#elif defined(HW_MKRWAN1300_H)
		
	#elif defined(HW_RAK4260_H)
		
	#elif defined(HW_RAK4600_H)
			
	#elif defined(HW_RAK11300_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
	
}

uint64_t hal_timer_millis(void) {
	
	#if defined(HW_ARDUINO)
		return millis();
	#elif defined(HW_MKRWAN1300_H)
		return 0; //TODO
	#elif defined(HW_RAK4260_H)
		
		if (millisisinitialized != 0) {
			
			TC0->COUNT16.CTRLA.reg &= ~TC_CTRLA_ENABLE;
				
			TC0->COUNT16.CTRLA.reg &= TC_CTRLA_SWRST;
			
			if (gclksetup != 0) {
				//need to use the 48MHz clk set that up with GCLK
				
				GCLK->GENCTRL[1].reg = GCLK_GENCTRL_SRC_DFLL48M | GCLK_GENCTRL_RUNSTDBY;
				
				GCLK->GENCTRL[1].reg |= GCLK_GENCTRL_GENEN;
				
				gclksetup = 0;
			}
			
			
			GCLK->PCHCTRL[27].reg = GCLK_PCHCTRL_GEN_GCLK1_Val;
				
			while(GCLK->SYNCBUSY.reg != 0x0);
			
			GCLK->PCHCTRL[27].reg |= GCLK_PCHCTRL_CHEN;
			
			while(TC0->COUNT32.SYNCBUSY.reg != 0x0);
			
			TC0->COUNT32.CTRLA.reg |= TC_CTRLA_MODE_COUNT32 | TC_CTRLA_PRESCALER_DIV2_Val;
			
			TC0->COUNT32.CTRLBSET.reg |= TC_CTRLBSET_DIR;
			
			TC0->COUNT32.INTFLAG.reg = TC_INTFLAG_RESETVALUE;
			
			TC0->COUNT32.INTENSET.reg = TC_INTENSET_MC0;
			TC0->COUNT32.EVCTRL.reg = TC_EVCTRL_MCEO0;
			
			TC0->COUNT32.CC[0].reg = 23999;	//(48MHz / 2) / 1000 = 1msec , count = 23999
			
			TC0->COUNT32.COUNT.reg = 0x00000000;
			
			//RTC->MODE2.GP[0].reg = 0x00000000;
			
			while(TC0->COUNT32.SYNCBUSY.reg != 0);
			TC0->COUNT32.CTRLA.reg |= TC_CTRLA_ENABLE;
			
			millisisinitialized = 0;
		}
		
		return currentMillisRunTime;
		
	#elif defined(HW_RAK4600_H)
		return 0; //TODO
	#elif defined(HW_RAK11300_H)
		return 0; //TODO
	#else
		#error "Hardware not yet implemented"
	#endif
	
}


#if defined(HW_MKRWAN1300_H)
	#if defined(HW_ARDUINO)	
		/*
		void hal_timer_setInterruptInterval(void (*isr)(void), uint32_t interval) {
			
			hal_ISR_Timer.setInterval(interval, isr);
			
		}
		*/
	#else
		
		
		
	#endif
#endif //HW_MKRWAN1300_H





