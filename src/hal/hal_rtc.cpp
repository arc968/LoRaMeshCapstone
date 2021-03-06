#define HAL_LIB
#include "hal_rtc.h"

#if defined(HW_MKRWAN1300_H)
	#if defined(HW_ARDUINO)
		#include <RTCZero.h>
		RTCZero rtc;
	#else
		
	#endif
#elif defined(HW_RAK4260_H)

	void RTC_Handler(void)                                  // Event System interrupt handler
	{
		RTC->MODE2.INTFLAG.reg = ~RTC_MODE2_INTFLAG_RESETVALUE;
	}

#elif defined(HW_RAK4600_H)
			
#elif defined(HW_RAK11300_H)
	
#else
	#error "Hardware not yet implemented"
#endif	

static uint8_t rtcIsInit = 0;

void hal_rtc_waitForSync(void) {
	
	#if defined(HW_MKRWAN1300_H)
		#if defined(HW_ARDUINO)
			//none
		#else
			
		#endif
	#elif defined(HW_RAK4260_H)
	
		while (RTC->MODE2.SYNCBUSY.reg != 0);
		
	#elif defined(HW_RAK4600_H)
		
	#elif defined(HW_RAK11300_H)
		//while (rtc_running());
	#else
		#error "Hardware not yet implemented"
	#endif
	
}



void hal_rtc_init(void) {
	
	
	#if defined(HW_MKRWAN1300_H)
		#if defined(HW_ARDUINO)
			rtc.begin();
		#else
			
		#endif
	#elif defined(HW_RAK4260_H)
	
		//disable rtc
		//sw reset and set up clk sorce and scaling
	
		hal_rtc_disable();
		
		//MCLK->APBAMASK.reg = MCLK_APBAMASK_OSC32KCTRL | MCLK_APBAMASK_RTC;
		
		//MCLK->BUPDIV.reg = MCLK_BUPDIV_BUPDIV_DIV32;
		
		//uses the internal ultra low power always on 32k occilator auto divided down to 1024Hz
		OSC32KCTRL->RTCCTRL.bit.RTCSEL = OSC32KCTRL_RTCCTRL_RTCSEL_ULP32K;
		OSC32KCTRL->OSCULP32K.bit.WRTLOCK = 0x1;
		
		RTC->MODE2.CTRLA.reg = RTC_MODE2_CTRLA_SWRST;

		hal_rtc_waitForSync();
		
		RTC->MODE2.CTRLA.reg = RTC_MODE2_CTRLA_RESETVALUE | RTC_MODE2_CTRLA_PRESCALER_DIV16 | RTC_MODE2_CTRLA_CLOCKSYNC | RTC_MODE2_CTRLA_MODE_CLOCK | RTC_MODE2_CTRLA_MATCHCLR | RTC_MODE2_CTRLA_CLKREP;
		RTC->MODE2.INTFLAG.reg = ~RTC_MODE2_INTFLAG_RESETVALUE;
		RTC->MODE2.Mode2Alarm[0].MASK.reg = RTC_MODE2_MASK_SEL_YYMMDDHHMMSS;
		RTC->MODE2.EVCTRL.reg = RTC_MODE2_EVCTRL_RESETVALUE;
		//RTC->MODE2.FREQCORR.reg &= ~RTC_FREQCORR_SIGN;
		//RTC->MODE2.FREQCORR.bit.VALUE = 0x00;
		
	#elif defined(HW_RAK4600_H)
		
	#elif defined(HW_RAK11300_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
	
	
	hal_rtc_clearClock();
	
	rtcIsInit = 1;
	
	hal_rtc_waitForSync();
	
	hal_rtc_enable();
	
}

void hal_rtc_deinit(void) {
	
	hal_rtc_disable();
	
	#if defined(HW_MKRWAN1300_H)
		#if defined(HW_ARDUINO)
			rtc.disableAlarm();
			rtc.detachInterrupt();
		#else
			
		#endif
	#elif defined(HW_RAK4260_H)
	
		RTC->MODE2.CTRLA.reg = RTC_MODE2_CTRLA_SWRST;
		
	#elif defined(HW_RAK4600_H)
		
	#elif defined(HW_RAK11300_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
	
	hal_rtc_waitForSync();
	
	rtcIsInit = 0;
	
}

bool hal_rtc_isInitialized(void) {
	
	return rtcIsInit;
	
}

void hal_rtc_enable(void) {
	
	#if defined(HW_MKRWAN1300_H)
		#if defined(HW_ARDUINO)
			rtc.enableAlarm(rtc.MATCH_YYMMDDHHMMSS);
		#else
			
		#endif
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
		
		#if defined(HW_ARDUINO)
			rtc.disableAlarm();
		#else
			
		#endif
	#elif defined(HW_RAK4260_H)
	
		RTC->MODE2.CTRLA.reg &= ~RTC_MODE2_CTRLA_ENABLE;
		
	#elif defined(HW_RAK4600_H)
		
	#elif defined(HW_RAK11300_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
	
	hal_rtc_waitForSync();
	
}

void hal_rtc_setClock(struct lib_datetime_s * dt) {
	
	hal_rtc_waitForSync();
	
	#if defined(HW_MKRWAN1300_H)
		#if defined(HW_ARDUINO)
				
			rtc.setYear(dt->year);
			rtc.setMonth(dt->month);
			rtc.setDay(dt->day);
			rtc.setHours(dt->hour);
			rtc.setMinutes(dt->min);
			rtc.setSeconds(dt->sec);
			
		#else
			
		#endif
	#elif defined(HW_RAK4260_H)
	
		RTC->MODE2.CLOCK.bit.YEAR = dt->year;
		RTC->MODE2.CLOCK.bit.MONTH = dt->month;
		RTC->MODE2.CLOCK.bit.DAY = dt->day;
		RTC->MODE2.CLOCK.bit.HOUR = dt->hour;
		RTC->MODE2.CLOCK.bit.MINUTE = dt->min;
		RTC->MODE2.CLOCK.bit.SECOND = dt->sec;
		
	#elif defined(HW_RAK4600_H)
		
	#elif defined(HW_RAK11300_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
	
	hal_rtc_waitForSync();
	
}

void hal_rtc_clearClock(void) {
	
	hal_rtc_waitForSync();
	
	#if defined(HW_MKRWAN1300_H)
		#if defined(HW_ARDUINO)
			rtc.setDate(0x00, 0x00, 0x00);
			rtc.setTime(0x00, 0x00, 0x00);
		#else
			
		#endif
	#elif defined(HW_RAK4260_H)
	
		RTC->MODE2.CLOCK.reg = RTC_MODE2_CLOCK_RESETVALUE;
		
	#elif defined(HW_RAK4600_H)
		
	#elif defined(HW_RAK11300_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
	
	hal_rtc_waitForSync();
	
}

void hal_rtc_getClock(struct lib_datetime_s * val) {
	
	hal_rtc_waitForSync();
	
	#if defined(HW_MKRWAN1300_H)
		#if defined(HW_ARDUINO)
			val->year = rtc.getYear();
			val->month = rtc.getMonth();
			val->day = rtc.getDay();
			val->hour = rtc.getHours();
			val->min = rtc.getMinutes();
			val->sec = rtc.getSeconds();
		#else
			
		#endif
	#elif defined(HW_RAK4260_H)
	
		val->year = RTC->MODE2.CLOCK.bit.YEAR;
		val->month = RTC->MODE2.CLOCK.bit.MONTH;
		val->day = RTC->MODE2.CLOCK.bit.DAY;
		val->hour = RTC->MODE2.CLOCK.bit.HOUR;
		val->min = RTC->MODE2.CLOCK.bit.MINUTE;
		val->sec = RTC->MODE2.CLOCK.bit.SECOND;
		
	#elif defined(HW_RAK4600_H)
		
	#elif defined(HW_RAK11300_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
	
}

void hal_rtc_setAlarm(struct lib_datetime_s * dt) {
	
	hal_rtc_waitForSync();
	
	#if defined(HW_MKRWAN1300_H)
		#if defined(HW_ARDUINO)
			rtc.setAlarmDate(dt->year, dt->month, dt->day);
			rtc.setAlarmTime(dt->hour, dt->min, dt->sec);
		#else
			
		#endif
	#elif defined(HW_RAK4260_H)
	
		RTC->MODE2.Mode2Alarm[0].ALARM.bit.YEAR = dt->year;
		RTC->MODE2.Mode2Alarm[0].ALARM.bit.MONTH = dt->month;
		RTC->MODE2.Mode2Alarm[0].ALARM.bit.DAY = dt->day;
		RTC->MODE2.Mode2Alarm[0].ALARM.bit.HOUR = dt->hour;
		RTC->MODE2.Mode2Alarm[0].ALARM.bit.MINUTE = dt->min;
		RTC->MODE2.Mode2Alarm[0].ALARM.bit.SECOND = dt->sec;
		
	#elif defined(HW_RAK4600_H)
		
	#elif defined(HW_RAK11300_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
	
	hal_rtc_waitForSync();
	
}

void hal_rtc_getAlarm(struct lib_datetime_s * val) {
	
	hal_rtc_waitForSync();
	
	#if defined(HW_MKRWAN1300_H)
		#if defined(HW_ARDUINO)
			val->year = rtc.getAlarmYear();
			val->month = rtc.getAlarmMonth();
			val->day = rtc.getAlarmDay();
			val->hour = rtc.getAlarmHours();
			val->min = rtc.getAlarmMinutes();
			val->sec = rtc.getAlarmSeconds();
		#else
			
		#endif
	#elif defined(HW_RAK4260_H)
	
		val->year = RTC->MODE2.CLOCK.bit.YEAR;
		val->month = RTC->MODE2.CLOCK.bit.MONTH;
		val->day = RTC->MODE2.CLOCK.bit.DAY;
		val->hour = RTC->MODE2.CLOCK.bit.HOUR;
		val->min = RTC->MODE2.CLOCK.bit.MINUTE;
		val->sec = RTC->MODE2.CLOCK.bit.SECOND;
		
	#elif defined(HW_RAK4600_H)
		
	#elif defined(HW_RAK11300_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
	
}

void hal_rtc_clearAlarm(void) {
	
	hal_rtc_waitForSync();
	
	#if defined(HW_MKRWAN1300_H)
		#if defined(HW_ARDUINO)
			rtc.setAlarmDate(0, 0, 0);
			rtc.setAlarmTime(0, 0, 0);
		#else
			
		#endif
	#elif defined(HW_RAK4260_H)
	
		RTC->MODE2.Mode2Alarm[0].ALARM.reg = 0x00000000;
		
	#elif defined(HW_RAK4600_H)
		
	#elif defined(HW_RAK11300_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
	
	hal_rtc_waitForSync();
	
}

bool hal_rtc_compareClockToAlarm(void) {
	
	hal_rtc_waitForSync();
	
	#if defined(HW_MKRWAN1300_H)
		#if defined(HW_ARDUINO)
			/*lib_datetime_s * clk, alarm;
			
			hal_rtc_getClock(clk);
			hals_rtc_getAlarm(alarm);
			
			if (lib_datetime_cmp(clk, alarm) >= 0) {
				return true;
			}
			else {
				return false;
			}*/
			
			
			return (rtc.getYear() >= rtc.getAlarmYear() &&
					rtc.getMonth() >= rtc.getAlarmMonth() &&
					rtc.getDay() >= rtc.getAlarmDay() &&
					rtc.getHours() >= rtc.getAlarmHours() &&
					rtc.getMinutes() >= rtc.getAlarmMinutes() &&
					rtc.getSeconds() >= rtc.getAlarmSeconds());
		#else
			
		#endif
		
				
	#elif defined(HW_RAK4260_H)
	
		return RTC->MODE2.CLOCK.reg >= RTC->MODE2.Mode2Alarm[0].ALARM.reg;
				
	#elif defined(HW_RAK4600_H)
		
	#elif defined(HW_RAK11300_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
	
}

void hal_rtc_enableAlarmInterrupt(void) {
	
	#if defined(HW_MKRWAN1300_H)
		#if defined(HW_ARDUINO)
			rtc.enableAlarm(rtc.MATCH_YYMMDDHHMMSS);
		#else
			
		#endif
	#elif defined(HW_RAK4260_H)
	
		RTC->MODE2.INTENSET.reg |= RTC_MODE2_INTENSET_ALARM0;
		RTC->MODE2.EVCTRL.reg |= RTC_MODE2_EVCTRL_ALARMEO0;
		
	#elif defined(HW_RAK4600_H)
		
	#elif defined(HW_RAK11300_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
	
	hal_rtc_waitForSync();
	
}

void hal_rtc_disableAlarmInterrupt(void) {
	
	#if defined(HW_MKRWAN1300_H)
		#if defined(HW_ARDUINO)
			rtc.disableAlarm();
		#else
			
		#endif
	#elif defined(HW_RAK4260_H)
	
		RTC->MODE2.INTENCLR.reg |= RTC_MODE2_INTENCLR_ALARM0;
		RTC->MODE2.EVCTRL.reg &= ~RTC_MODE2_EVCTRL_ALARMEO0;
		
	#elif defined(HW_RAK4600_H)
		
	#elif defined(HW_RAK11300_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
	
	hal_rtc_waitForSync();
	
}

void hal_rtc_enableOverflowInterrupt(void) {
	
	#if defined(HW_MKRWAN1300_H)
		#if defined(HW_ARDUINO)
			//none
		#else
			
		#endif		
	#elif defined(HW_RAK4260_H)
	
		RTC->MODE2.INTENSET.reg |= RTC_MODE2_INTENSET_OVF;
		RTC->MODE2.EVCTRL.reg |= RTC_MODE2_EVCTRL_OVFEO;
		
	#elif defined(HW_RAK4600_H)
		
	#elif defined(HW_RAK11300_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
	
	hal_rtc_waitForSync();
	
}

void hal_rtc_disableOverflowInterrupt(void) {
	
	#if defined(HW_MKRWAN1300_H)
		#if defined(HW_ARDUINO)
			//none
		#else
			
		#endif
	#elif defined(HW_RAK4260_H)
	
		RTC->MODE2.INTENCLR.reg |= RTC_MODE2_INTENCLR_OVF;
		RTC->MODE2.EVCTRL.reg &= ~RTC_MODE2_EVCTRL_OVFEO;
		
	#elif defined(HW_RAK4600_H)
		
	#elif defined(HW_RAK11300_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
	
	hal_rtc_waitForSync();
	
}


void hal_rtc_clearAlarmInterrupt(void) {
	
	#if defined(HW_MKRWAN1300_H)
		#if defined(HW_ARDUINO)
			//none
		#else
			
		#endif
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
		#if defined(HW_ARDUINO)
			//none
		#else
			
		#endif
	#elif defined(HW_RAK4260_H)
		
		RTC->MODE2.INTFLAG.reg |= RTC_MODE2_INTFLAG_OVF;
		
	#elif defined(HW_RAK4600_H)
		
	#elif defined(HW_RAK11300_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
	
	hal_rtc_waitForSync();
	
}