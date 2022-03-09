#define HAL_LIB
#include "hal_rtc.h"


void hal_rtc_waitForSync(void) {
	
	#if defined(HW_MKRWAN1300_H)
		
	#elif defined(HW_RAK4260_H)
	
		//while (RTC->MODE1.SYNCBUSY.ENABLE != 0);
		
	#elif defined(HW_RAK4600_H)
		
	#elif defined(HW_RAK11300_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
	
}



bool hal_rtc_init(enum hw_rtc_modes_e mode, uint8_t clkdiv) {
	
	hal_rtc_disable();
	
	//sw reset and set up clk sorce and scaling
	
	#if defined(HW_MKRWAN1300_H)
		
	#elif defined(HW_RAK4260_H)
		
		/*MCLK.APBAMASK.reg = MCLK_APBAMASK_OSC32KCTRL | MCLK_APBAMASK_RTC;
		
		MCLK.BUPDIV.reg = MCLK_BUPDIV_BUPDIV_DIV1;
		
		RTC->MODE1.CTRLA.reg = RTC_MODE1_CTRLA_SWRST

		RTC->MODE1.CTRLA.reg = RTC_MODE1_CTRLA_COUNTSYNC;
		
		hal_rtc_waitForSync();
		
		RTC->MODE1.CTRLA.reg = RTC_MODE1_CTRLA_COUNTSYNC;
		RTC->MODE1.INTENCLR.reg = ~RTC_MODE1_INTENCLR_RESETVALUE;
		RTC->MODE1.EVCTRL.reg = RTC_MODE1_EVCTRL_RESETVALUE;*/
		
	#elif defined(HW_RAK4600_H)
		
	#elif defined(HW_RAK11300_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
	
	
	hal_rtc_setCount(0x00000000);
	
	hal_rtc_enable();
	
}

bool hal_rtc_deinit(void) {
	
	hal_rtc_disable();
	
	#if defined(HW_MKRWAN1300_H)
		
	#elif defined(HW_RAK4260_H)
	
		//RTC->MODE1.CTRLA.reg = RTC_MODE1_CTRLA_SWRST;
		
	#elif defined(HW_RAK4600_H)
		
	#elif defined(HW_RAK11300_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
	
	hal_rtc_waitForSync();
	
}

void hal_rtc_enable(void) {
	
	#if defined(HW_MKRWAN1300_H)
		
	#elif defined(HW_RAK4260_H)
	
		RTC->MODE1.CTRLA.reg |= RTC_MODE1_CTRLA_ENABLE;
		
	#elif defined(HW_RAK4600_H)
		
	#elif defined(HW_RAK11300_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
	
	hal_rtc_waitForSync();
	
}

void hal_rtc_disable(void) {
	
	#if defined(HW_MKRWAN1300_H)
		
	#elif defined(HW_RAK4260_H)
	
		//RTC->MODE1.CTRLA.reg &= ~RTC_MODE1_CTRLA_ENABLE;
		
	#elif defined(HW_RAK4600_H)
		
	#elif defined(HW_RAK11300_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
	
	hal_rtc_waitForSync();
	
}

void hal_rtc_setCount(uint32_t val) {
	
	#if defined(HW_MKRWAN1300_H)
		
	#elif defined(HW_RAK4260_H)
	
		//RTC->MODE1.COUNT.reg = val;
		hal_rtc_waitForSync();
		
	#elif defined(HW_RAK4600_H)
		
	#elif defined(HW_RAK11300_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
	
}

uint32_t hal_rtc_getCount(void) {
	
	hal_rtc_waitForSync();
	
	#if defined(HW_MKRWAN1300_H)
		
	#elif defined(HW_RAK4260_H)
	
		return 0;//RTC->MODE1.COUNT.reg;
		
	#elif defined(HW_RAK4600_H)
		
	#elif defined(HW_RAK11300_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
	
}

void hal_rtc_setCompare(uint32_t val) {
	
	#if defined(HW_MKRWAN1300_H)
		
	#elif defined(HW_RAK4260_H)
	
		//RTC->MODE1.COMP.reg = val;
		
	#elif defined(HW_RAK4600_H)
		
	#elif defined(HW_RAK11300_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
	
	hal_rtc_waitForSync();
	
}

uint32_t hal_rtc_getCompare(void) {
	
	hal_rtc_waitForSync();
	
	#if defined(HW_MKRWAN1300_H)
		
	#elif defined(HW_RAK4260_H)
		
		return 0;//RTC->MODE1.COMP.reg;
		
	#elif defined(HW_RAK4600_H)
		
	#elif defined(HW_RAK11300_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
	
}
/*
void hal_rtc_enableCompareInterrupt(void) {
	
	#if defined(HW_MKRWAN1300_H)
		
	#elif defined(HW_RAK4260_H)
	
		RTC->MODE1.INTENSET.reg |= RTC_MODE1_INTENSET_CMP0;
		hal_rtc_waitForSync();
		
	#elif defined(HW_RAK4600_H)
		
	#elif defined(HW_RAK11300_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
	
}

void hal_rtc_disableCompareInterrupt(void) {
	
	#if defined(HW_MKRWAN1300_H)
		
	#elif defined(HW_RAK4260_H)
	
		RTC->MODE1.INTENCLR.reg |= RTC_MODE1_INTENSET_CMP0;
		hal_rtc_waitForSync();
		
	#elif defined(HW_RAK4600_H)
		
	#elif defined(HW_RAK11300_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
	
}
*/
void hal_rtc_enableOverflowInterrupt(void) {
	
	#if defined(HW_MKRWAN1300_H)
		
	#elif defined(HW_RAK4260_H)
	
		//RTC->MODE1.INTENSET.reg |= RTC_MODE1_INTENSET_OVF;
		
	#elif defined(HW_RAK4600_H)
		
	#elif defined(HW_RAK11300_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
	
	hal_rtc_waitForSync();
	
}

void hal_rtc_disableOverflowInterrupt(void) {
	
	#if defined(HW_MKRWAN1300_H)
		
	#elif defined(HW_RAK4260_H)
	
		//RTC->MODE1.INTENCLR.reg |= RTC_MODE1_INTENSET_OVF;
		
	#elif defined(HW_RAK4600_H)
		
	#elif defined(HW_RAK11300_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
	
	hal_rtc_waitForSync();
	
}


void hal_rtc_clearCompareInterrupt(void) {
	
	#if defined(HW_MKRWAN1300_H)
		
	#elif defined(HW_RAK4260_H)
	
		//RTC->MODE1.INTFLAG.reg &= ~RTC_MODE1_INTENSET_CMP0;
		
	#elif defined(HW_RAK4600_H)
		
	#elif defined(HW_RAK11300_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
	
	hal_rtc_waitForSync();
	
}

void hal_rtc_clearOverflowInterrupt(void) {
	
	#if defined(HW_MKRWAN1300_H)
		
	#elif defined(HW_RAK4260_H)
		
		//RTC->MODE1.INTFLAG.reg &= ~RTC_MODE1_INTENSET_OVF;
		
	#elif defined(HW_RAK4600_H)
		
	#elif defined(HW_RAK11300_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
	
	hal_rtc_waitForSync();
	
}