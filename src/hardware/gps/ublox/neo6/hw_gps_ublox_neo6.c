#define HW_GPS_UBLOX_NEO6_C
#include "hw_gps_ublox_neo6.h"

#ifdef HW_GPS_UBLOX_NEO6_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

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

#define UBX_MSG_SERIAL_WRITE(serial_port, message) hal_serial_write(serial_port, (uint8_t *)(&(message)), sizeof(typeof(message)));

#define UBX_CFG_MSG_SERIAL_WRITE(serial_port, message) ubx_cfg_write(serial_port, (uint8_t *)(&(message)), sizeof(typeof(message)));

static volatile lib_datetime_interval_t timestamp = 0;
static void isr_pps(void) {
	timestamp = drv_timer_getMonotonicTime();
	if (hal_gpio_digitalRead(6) == 1) {
		hal_gpio_digitalWrite(6, LOW);
	} else {
		hal_gpio_digitalWrite(6, HIGH);
	}
}


static uint8_t recv_buf[128];

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
		drv_sched_init();
		drv_timer_init();
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
		
	//enable interrupts on GPS pulse GPIO pin
	hal_interrupt_attachPin(0, isr_pps, INTERRUPT_FALLING);

	while(true) { //check GPS reply
		if (hal_serial_available(hal_serial1) > 0) {
			uint8_t buf[128];
			size_t count = hal_serial_readBytes(hal_serial1, buf, sizeof(buf));
			hal_serial_write(hal_serial0, buf, count);
		}
	}
}

#endif // HW_GPS_UBLOX_NEO6_H

#undef HW_GPS_UBLOX_NEO6_C