#define HW_GPS_UBLOX_NEO6_C
#include "hw_gps_ublox_neo6.h"

#ifdef HW_GPS_UBLOX_NEO6_H

#include <stdlib.h>
#include <stdint.h>

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


static volatile lib_datetime_interval_t timestamp = 0;
static void isr_pps(void) {
	timestamp = drv_timer_getMonotonicTime();
}

void drv_gps_init(struct drv_gps_s * handle) {
	//initialize dependencies
		drv_sched_init();
		drv_timer_init();
	//initialize serial1 port for communicating with GPS
		hal_serial_begin(hal_serial1, 9600);
	//disable NMEA
		struct ubx_msg__CFG_PRT__SetPortConfigurationForUART_s ubx_cfg_prt = ubx_msg__CFG_PRT__SetPortConfigurationForUART_s_default;
		ubx_cfg_prt.payload.mode.charLen = 0b11;
		ubx_cfg_prt.payload.mode.parity = 0b100;
		ubx_cfg_prt.payload.baudRate = 9600;
		ubx_cfg_prt.payload.inProtoMask.ubx = 1;
		ubx_cfg_prt.payload.outProtoMask.ubx = 1;
		ubx_checksum(ubx_cfg_prt.body, sizeof(ubx_cfg_prt.body), &(ubx_cfg_prt.checksum));
		
		hal_serial_flush(hal_serial1);
		hal_serial_write(hal_serial1, (uint8_t *)&ubx_cfg_prt, sizeof(struct ubx_msg__CFG_PRT__SetPortConfigurationForUART_s));
		hal_serial_flush(hal_serial1);

		hal_timer_delay(250); //need to wait for it to finish
		//TODO: look for correct ACK

	//enable interrupts on GPS pulse GPIO pin
		hal_interrupt_attachPin(0, isr_pps, INTERRUPT_FALLING);
	//configure GPS for timepulse
		struct ubx_msg__CFG_TP5__SetTimePulse_s tp_ubx = ubx_msg__CFG_TP5__SetTimePulse_default;
		tp_ubx.payload.freqPeriod = LIB_BYTEORDER_HTOL_U32(1000000);
		tp_ubx.payload.pulseLenRatio = LIB_BYTEORDER_HTOL_U32(100000);
		tp_ubx.payload.Active = 1;
		tp_ubx.payload.LockGpsFreq = 1;
		tp_ubx.payload.isLength = 1;
		tp_ubx.payload.alignToTow = 1;
		tp_ubx.payload.polarity = 0;
		ubx_checksum(tp_ubx.body, sizeof(tp_ubx.body), &(tp_ubx.checksum));

		hal_serial_flush(hal_serial1);
		hal_serial_write(hal_serial1, (uint8_t *)&tp_ubx, sizeof(struct ubx_msg__CFG_TP5__SetTimePulse_s));
		hal_serial_flush(hal_serial1);

		hal_timer_delay(250); //need to wait for it to finish
		//TODO: look for correct ACK

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