#define HAL_LIB
#include "hal_rtc.h"
#include "../lib/datetime/lib_datetime.h"


void hal_rtc_waitForSync(void) {
	
	#if defined(HW_MKRWAN1300_H)
		
	#elif defined(HW_RAK4260_H)
	
		while (RTC->MODE2.SYNCBUSY.reg != 0);
		
	#elif defined(HW_RAK4600_H)
		
	#elif defined(HW_RAK11300_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
	
}



bool hal_rtc_init(void) {
	
	hal_rtc_disable();
	
	//sw reset and set up clk sorce and scaling
	
	#if defined(HW_MKRWAN1300_H)
		
	#elif defined(HW_RAK4260_H)
		
		MCLK->APBAMASK.reg = MCLK_APBAMASK_OSC32KCTRL | MCLK_APBAMASK_RTC;
		
		MCLK->BUPDIV.reg = MCLK_BUPDIV_BUPDIV_DIV32;
		
		RTC->MODE2.CTRLA.reg = RTC_MODE2_CTRLA_SWRST;

		hal_rtc_waitForSync();
		
		RTC->MODE2.CTRLA.reg = RTC_MODE2_CTRLA_CLOCKSYNC | RTC_MODE2_CTRLA_MODE_CLOCK | RTC_MODE2_CTRLA_MATCHCLR;
		RTC->MODE2.INTFLAG.reg = ~RTC_MODE2_INTFLAG_RESETVALUE;
		RTC->MODE2.EVCTRL.reg = RTC_MODE2_EVCTRL_RESETVALUE;
		RTC->MODE2.FREQCORR.reg &= ~RTC_FREQCORR_SIGN;
		//RTC->MODE2.FREQCORR.bit.VALUE = 
		
	#elif defined(HW_RAK4600_H)
		
	#elif defined(HW_RAK11300_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
	
	
	//hal_rtc_setCount(0x00000000);
	
	hal_rtc_waitForSync();
	
	hal_rtc_enable();
	
}

bool hal_rtc_deinit(void) {
	
	hal_rtc_disable();
	
	#if defined(HW_MKRWAN1300_H)
		
	#elif defined(HW_RAK4260_H)
	
		RTC->MODE2.CTRLA.reg = RTC_MODE2_CTRLA_SWRST;
		
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
	
		RTC->MODE2.CTRLA.reg |= RTC_MODE2_CTRLA_ENABLE;
		
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
	
		RTC->MODE2.CTRLA.reg &= ~RTC_MODE2_CTRLA_ENABLE;
		
	#elif defined(HW_RAK4600_H)
		
	#elif defined(HW_RAK11300_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
	
	hal_rtc_waitForSync();
	
}

void hal_rtc_setClock(struct lib_datetime_s dt) {
	
	hal_rtc_waitForSync();
	
	#if defined(HW_MKRWAN1300_H)
		
	#elif defined(HW_RAK4260_H)
	
		RTC->MODE2.CLOCK.bit.YEAR = dt.year;
		RTC->MODE2.CLOCK.bit.MONTH = dt.month;
		RTC->MODE2.CLOCK.bit.DAY = dt.day;
		RTC->MODE2.CLOCK.bit.HOUR = dt.hour;
		RTC->MODE2.CLOCK.bit.MINUTE = dt.min;
		RTC->MODE2.CLOCK.bit.SECOND = dt.sec;
		
	#elif defined(HW_RAK4600_H)
		
	#elif defined(HW_RAK11300_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
	
	hal_rtc_waitForSync();
	
}

struct lib_datetime_s hal_rtc_getClock(void) {
	
	lib_datetime_s val;
	
	hal_rtc_waitForSync();
	
	#if defined(HW_MKRWAN1300_H)
		
	#elif defined(HW_RAK4260_H)
	
		val.year = RTC->MODE2.CLOCK.bit.YEAR;
		val.month = RTC->MODE2.CLOCK.bit.MONTH;
		val.day = RTC->MODE2.CLOCK.bit.DAY;
		val.hour = RTC->MODE2.CLOCK.bit.HOUR;
		val.min = RTC->MODE2.CLOCK.bit.MINUTE;
		val.sec = RTC->MODE2.CLOCK.bit.SECOND;
		
		return val;
		
	#elif defined(HW_RAK4600_H)
		
	#elif defined(HW_RAK11300_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
	
}

void hal_rtc_setAlarm(uint32_t val) {
	
	#if defined(HW_MKRWAN1300_H)
		
	#elif defined(HW_RAK4260_H)
	
		//RTC->MODE2.COMP.reg = val;
		
	#elif defined(HW_RAK4600_H)
		
	#elif defined(HW_RAK11300_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
	
	hal_rtc_waitForSync();
	
}

uint32_t hal_rtc_getAlarm(void) {
	
	hal_rtc_waitForSync();
	
	#if defined(HW_MKRWAN1300_H)
		
	#elif defined(HW_RAK4260_H)
		
		return 0;//RTC->MODE2.COMP.reg;
		
	#elif defined(HW_RAK4600_H)
		
	#elif defined(HW_RAK11300_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
	
}

void hal_rtc_enableAlarmInterrupt(void) {
	
	#if defined(HW_MKRWAN1300_H)
		
	#elif defined(HW_RAK4260_H)
	
		RTC->MODE2.INTENSET.reg |= RTC_MODE2_INTENSET_ALARM0;
		
	#elif defined(HW_RAK4600_H)
		
	#elif defined(HW_RAK11300_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
	
	hal_rtc_waitForSync();
	
}

void hal_rtc_disableAlarmInterrupt(void) {
	
	#if defined(HW_MKRWAN1300_H)
		
	#elif defined(HW_RAK4260_H)
	
		RTC->MODE2.INTENCLR.reg |= RTC_MODE2_INTENCLR_ALARM0;
		
	#elif defined(HW_RAK4600_H)
		
	#elif defined(HW_RAK11300_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
	
	hal_rtc_waitForSync();
	
}

void hal_rtc_enableOverflowInterrupt(void) {
	
	#if defined(HW_MKRWAN1300_H)
		
	#elif defined(HW_RAK4260_H)
	
		RTC->MODE2.INTENSET.reg |= RTC_MODE2_INTENSET_OVF;
		
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
	
		RTC->MODE2.INTENCLR.reg |= RTC_MODE2_INTENCLR_OVF;
		
	#elif defined(HW_RAK4600_H)
		
	#elif defined(HW_RAK11300_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
	
	hal_rtc_waitForSync();
	
}


void hal_rtc_clearAlarmInterrupt(void) {
	
	#if defined(HW_MKRWAN1300_H)
		
	#elif defined(HW_RAK4260_H)
	
		RTC->MODE2.INTFLAG.reg |= RTC_MODE2_INTFLAG_ALARM0;
		
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
		
		RTC->MODE2.INTFLAG.reg |= RTC_MODE2_INTFLAG_OVF;
		
	#elif defined(HW_RAK4600_H)
		
	#elif defined(HW_RAK11300_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
	
	hal_rtc_waitForSync();
	
}