#define HW_GPS_UBLOX_NEO6_C
#include "hw_gps_ublox_neo6.h"

#ifdef HW_GPS_UBLOX_NEO6_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "hw_gps_ublox_neo6_UBX.h"
#include "hw_gps_ublox_neo6_NMEA.h"
#include "../../../../hal/hal.h"
#include "../../../../lib/byteorder/lib_byteorder.h"
#include "../../../../drivers/gps/drv_gps.h"
#include "../../../../drivers/timer/drv_timer.h"
#include "../../../../drivers/sched/drv_sched.h"

/*
#if defined __has_attribute
	#if !(__has_attribute(packed))
		#error "'__attribute__((packed))' is unavailable."
	#endif
	#if !(__has_attribute(aligned))
		#error "'__attribute__((aligned))' is unavailable."
	#endif
#else
	#error "'__has_attribute()' is unavailable."
#endif
*/

//static uint8_t recv_buf[128];

static volatile lib_datetime_interval_t timestamp = 0;

static void job_getGpsMessage(void * arg) {
	
	hal_serial_write(hal_serial0, "job_getGpsMessage\n", sizeof("job_getGpsMessage\n"));
	//uint8_t tmp1 = sizeof(struct ubx_msg__NAV_TIMEUTC__TimeSolution_s);
	//hal_serial_write(hal_serial0, &tmp1, 1);
	
	int msg_byte = hal_serial_read(hal_serial1);;
	for (int i=0; i<128; i++) {
		if (msg_byte == ubx_msg_sync_s_default.syncChar1) {
			msg_byte = hal_serial_read(hal_serial1);
			if (msg_byte == ubx_msg_sync_s_default.syncChar2) goto MSG_SYNC_FOUND;
		} else {
			msg_byte = hal_serial_read(hal_serial1);
		}
	}
	
	hal_serial_write(hal_serial0, "no msg sync bytes found\n", sizeof("no msg sync bytes found\n"));
	return; //no msg sync bytes found
	
	struct ubx_msg_header_s msg_header;
	MSG_SYNC_FOUND:
	for (int i=0; i<UBX_MSG_HEADER_SIZE; i++) {
		msg_byte = hal_serial_read(hal_serial1);
		for (int cnt=0; cnt<10; cnt++) {
			if (msg_byte < 0) {
				hal_timer_delay(5);
				msg_byte = hal_serial_read(hal_serial1);
			} else {
				break;
			}
		}
		msg_header.raw[i] = msg_byte;
	}
	
	for (int i=0; i<UBX_MSG_HEADER_SIZE; i++) {
		if (msg_header.raw[i] != ubx_msg__NAV_TIMEUTC__TimeSolution_s_default.header.raw[i]) return;
	}
	
	hal_serial_write(hal_serial0, "header match\n", sizeof("header match\n"));
	
	struct ubx_msg__NAV_TIMEUTC__TimeSolution_s timeutc = ubx_msg__NAV_TIMEUTC__TimeSolution_s_default;
	for (int i=0; i<sizeof(ubx_msg__NAV_TIMEUTC__TimeSolution_s_default.payload); i++) {
		msg_byte = hal_serial_read(hal_serial1);
		for (int cnt=0; cnt<10; cnt++) {
			if (msg_byte < 0) {
				hal_timer_delay(5);
				msg_byte = hal_serial_read(hal_serial1);
			} else {
				break;
			}
		}
		((uint8_t*)(&(timeutc.payload)))[i] = msg_byte;
	}
	
	hal_serial_write(hal_serial0, "payload copied\n", sizeof("payload copied\n"));
	
	msg_byte = hal_serial_read(hal_serial1);
	for (int cnt=0; cnt<10; cnt++) {
		if (msg_byte < 0) {
			hal_timer_delay(5);
			msg_byte = hal_serial_read(hal_serial1);
		} else {
			break;
		}
	}
	uint8_t tmp_ck_a = msg_byte;
	msg_byte = hal_serial_read(hal_serial1);
	for (int cnt=0; cnt<10; cnt++) {
		if (msg_byte < 0) {
			hal_timer_delay(5);
			msg_byte = hal_serial_read(hal_serial1);
		} else {
			break;
		}
	}
	uint8_t tmp_ck_b = msg_byte;
	
	hal_serial_write(hal_serial0, "checksum copied\n", sizeof("checksum copied\n"));
	
	UBX_MSG_CHECKSUM(timeutc);
	
	hal_serial_write(hal_serial0, "checksum calculated\n", sizeof("checksum calculated\n"));
	
	//hal_serial_write(hal_serial0, ((uint8_t*)(&(timeutc))), sizeof(timeutc));
	
	if (!(timeutc.checksum.ck_a == tmp_ck_a && timeutc.checksum.ck_b == tmp_ck_b)) return;
	
	hal_serial_write(hal_serial0, "checksum validated\n", sizeof("checksum validated\n"));
	
	struct lib_datetime_s dt;
	dt.year = timeutc.payload.year;
	dt.month = timeutc.payload.month;
	dt.day = timeutc.payload.day;
	dt.hour = timeutc.payload.hour;
	dt.min = timeutc.payload.min;
	dt.sec = timeutc.payload.sec;
	dt.ms = drv_timer_getMonotonicTime() - timestamp;
	//ignores flags
	drv_timer_setAbsoluteDateTime(&dt);
	
	char tbuf[256];
	sprintf(&tbuf, "year:%u\nmonth:%u\nday:%u\nhour:%u\nmin:%u\nsec:%u\nms:%u\n",dt.year,dt.month,dt.day,dt.hour,dt.min,dt.sec,dt.ms);
	hal_serial_write(hal_serial0, tbuf, strlen(tbuf)+1);
	
	// uint8_t tmp[1] = {dt.ms};
	// hal_serial_write(hal_serial0, tmp, 1);

	// uint8_t buf[32];
	// size_t count = hal_serial_readBytes(hal_serial1, buf, sizeof(buf));
	// hal_serial_write(hal_serial0, buf, count);
}

#define UBX_MSG_SERIAL_WRITE(serial_port, message) hal_serial_write(serial_port, (uint8_t *)(&(message)), sizeof(typeof(message)));

#define UBX_CFG_MSG_SERIAL_WRITE(serial_port, message) ubx_cfg_write(serial_port, (uint8_t *)(&(message)), sizeof(typeof(message)));


static void isr_pps(void) {
	timestamp = drv_timer_getMonotonicTime();
	// if (hal_gpio_digitalRead(6) == 1) {
		// hal_gpio_digitalWrite(6, LOW);
	// } else {
		// hal_gpio_digitalWrite(6, HIGH);
	// }
	drv_sched_once(job_getGpsMessage, NULL, DRV_SCHED_PRI__NORMAL, 250);
}




/*
enum ubx_cfg_reply_e {
	UBX_CFG_REPLY_ACK,
	UBX_CFG_REPLY_NAK,
	UBX_CFG_REPLY_TIMEOUT,
};
*/

//TODO: look for correct ACK
#define UBX_CFG_WRITE_TIMEOUT 200
static void ubx_cfg_write(void * const handle, uint8_t *msg, uint16_t length) {
	hal_serial_write(handle, msg, length);
	hal_serial_flush(handle);
	hal_timer_delay(250); //need to wait for it to finish
	/*
	lib_datetime_interval_t startTime = drv_timer_getMonotonicTime();
	uint8_t index_sync = 0;
	while(drv_timer_getMonotonicTime() < (startTime+UBX_CFG_WRITE_TIMEOUT)) {
		if (hal_serial_available(handle) > 0) {
			uint8_t buf[64];
			uint16_t count = hal_serial_readBytes(handle, buf, sizeof(buf));
			for (uint16_t i=0; i<count; i++) {
				 if (index_sync == UBX_MSG_SYNC_SIZE) {
					memmove(&(buf[0]), &(buf[i]), count-i);
					count -= i;
				} else if (buf[i] == ubx_msg_sync_s_default.syncChars[index_sync]) {
					index_sync++;
				} else {
					index_sync = 0;
				}
			}
		}
	}
	return UBX_CFG_REPLY_TIMEOUT;
	*/
}

void drv_gps_init(struct drv_gps_s * handle) {
	//initialize dependencies
		drv_timer_init();
		drv_sched_init();
	//initialize serial1 port for communicating with GPS
		hal_serial_begin(hal_serial1, 9600);
	//disable NMEA
		struct ubx_msg__CFG_PRT__SetPortConfigurationForUART_s ubx_cfg_prt = ubx_msg__CFG_PRT__SetPortConfigurationForUART_s_default;
		ubx_cfg_prt.payload = (typeof(ubx_cfg_prt.payload)) {
			.portID = 1,
			.mode.reserved1 = 1,
			.mode.charLen = 0b11,
			.mode.parity = 0b100,
			.baudRate = 9600,
			.inProtoMask.ubx = 1,
			.outProtoMask.ubx = 1
		};
		UBX_MSG_CHECKSUM(ubx_cfg_prt);
		
		//enum ubx_cfg_reply_e err = 
		UBX_CFG_MSG_SERIAL_WRITE(hal_serial1, ubx_cfg_prt);
		//while (err != UBX_CFG_REPLY_ACK);
		hal_timer_delay(250);

	//configure GPS for timepulse
		struct ubx_msg__CFG_TP5__SetTimePulse_s tp_ubx = ubx_msg__CFG_TP5__SetTimePulse_s_default;
		tp_ubx.payload = (typeof(tp_ubx.payload)) {
			.freqPeriod = 1000000,
			.pulseLenRatio = 100000,
			.Active = 1,
			.LockGpsFreq = 1,
			.isLength = 1,
			.alignToTow = 1,
			.polarity = 0,
		};
		UBX_MSG_CHECKSUM(tp_ubx);
		
		//err = 
		UBX_CFG_MSG_SERIAL_WRITE(hal_serial1, tp_ubx);
		//while (err != UBX_CFG_REPLY_ACK);
		hal_timer_delay(250);
	
	//configure GPS for NAVUTC
		struct ubx_msg__CFG_MSG__SetMessageRate_s nav_ubx = ubx_msg__CFG_MSG__SetMessageRate_s_default;
		nav_ubx.payload = (typeof(nav_ubx.payload)) {
			.msg = UBX_MSG_ID__NAV_TIMEUTC,
			.rate = 1,
		};
		UBX_MSG_CHECKSUM(nav_ubx);
		
		//err = 
		UBX_CFG_MSG_SERIAL_WRITE(hal_serial1, nav_ubx);
		//while (err != UBX_CFG_REPLY_ACK);
		
	hal_timer_delay(250);
	hal_serial_flush(hal_serial1);
		
	//enable interrupts on GPS pulse GPIO pin
	hal_interrupt_attachPin(0, isr_pps, INTERRUPT_FALLING);

	// while(true) { //check GPS reply
		// if (hal_serial_available(hal_serial1) > 0) {
			// uint8_t buf[32];
			// size_t count = hal_serial_readBytes(hal_serial1, buf, sizeof(buf));
			// hal_serial_write(hal_serial0, buf, count);
		// }
	// }
}

#endif // HW_GPS_UBLOX_NEO6_H

#undef HW_GPS_UBLOX_NEO6_C