#define HW_GPS_RTC_DS3231_C
#include "../../../hardware.h"

#ifdef HW_GPS_RTC_DS3231_H

#ifdef __cplusplus
extern "C" {
#endif

#include "RTClib.h"

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "../../../../hal/hal.h"
#include "../../../../lib/byteorder/lib_byteorder.h"
#include "../../../../drivers/gps/drv_gps.h"
#include "../../../../drivers/timer/drv_timer.h"
#include "../../../../drivers/sched/drv_sched.h"

RTC_DS3231 myRTC;

static volatile lib_datetime_interval_t timestamp = 0;

static volatile bool runonce = false;

static void job_getGpsMessage(void * arg) {
	DEBUG_PRINT_TIMESTAMP(); DEBUG_PRINT_FUNCTION();
	
	if (myRTC.alarmFired(1)) {
	
		myRTC.clearAlarm(1);
		DateTime current = myRTC.now();
	
		struct lib_datetime_s dt;
		dt.year = current.year();
		dt.month = current.month();
		dt.day = current.day();
		dt.hour = current.hour();
		dt.min = current.minute();
		dt.sec = current.second();
		dt.ms = 0;
		//ignores flags
		//drv_timer_setAbsoluteDateTime(&dt);
		drv_timer_setAbsoluteDateTimeWithTimestamp(&dt, timestamp);
		
		DEBUG_PRINT("\tyear:%u,month:%u,day:%u,hour:%u,min:%u,sec:%u,ms:%u\n",dt.year,dt.month,dt.day,dt.hour,dt.min,dt.sec,dt.ms);
	} else {
		DEBUG_PRINT("\tNo RTC GPS message found\n");
	}
	

}

static void isr_pps(void) {
	timestamp = drv_timer_getMonotonicTime();
	
	drv_sched_once(job_getGpsMessage, NULL, DRV_SCHED_PRI__NORMAL, 100);
}

void drv_gps_init(struct drv_gps_s * handle) {
	//initialize dependencies
		drv_timer_init();
		drv_sched_init();
	
	//initialize RTC
		myRTC.begin();
	
	//enable interrupts on GPS pulse GPIO pin
	#if defined(HW_MKRWAN1300_H)
		hal_interrupt_attachPin(0, isr_pps, INTERRUPT_FALLING);
	#elif defined(HW_RAK4260_H)
		hal_interrupt_attachPin(5, isr_pps, INTERRUPT_FALLING);
	#elif defined(HW_RAK4600_H)
			
	#elif defined(HW_RAK11300_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
}

#ifdef __cplusplus
}
#endif//__cplusplus

#endif // HW_GPS_RTC_DS3231_H

#undef HW_GPS_RTC_DS3231_C