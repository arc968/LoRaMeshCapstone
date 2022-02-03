#define HW_GPS_UBLOX_NEO6_C
#include "hw_gps_ublox_neo6.h"

#ifdef HW_GPS_UBLOX_NEO6_H

#include <stdlib.h>
#include <stdint.h>

#include "hw_gps_ublox_neo6_UBX.h"
#include "hw_gps_ublox_neo6_NMEA.h"
#include "../../../../lib/byteorder/lib_byteorder.h"
#include "../../../../drivers/gps/drv_gps.h"

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

struct ubx_msg_sync_s {
	const union {
		uint8_t syncChars[2];
		struct {
			uint8_t syncChar1;
			uint8_t syncChar2;
		};
	};
} __attribute__((packed, aligned(1))) const ubx_msg_sync_s_default = {
	.syncChars = UBX_SYNC_CHARS,
};

struct ubx_msg_header_s {
	const union {
		uint8_t ID[2];
		struct {
			uint8_t msgClass;
			uint8_t msgID;
		};
	};
	const union {
		uint16_t length; //must be little-endian
		uint8_t len[2];
		struct {
			uint8_t lenLSB;
			uint8_t lenMSB;
		};
	};
} __attribute__((packed, aligned(1)));

struct ubx_msg_footer_s {
	uint8_t ck_a;
	uint8_t ck_b;
} __attribute__((packed, aligned(1)));

struct ubx_msg__CFG_MSG__SetMessageRates_s {
	struct ubx_msg_sync_s sync;
	struct ubx_msg_header_s header;
	struct {
		uint8_t msgClass;
		uint8_t msgID;
		union {
			uint8_t rate[6];
			struct {
				uint8_t if_DDC:1; // 1=enable, 0=disable
				uint8_t if_SerialPort1:1; // 1=enable, 0=disable
				uint8_t if_SerialPort2:1; // 1=enable, 0=disable
				uint8_t if_USB:1; // 1=enable, 0=disable
				uint8_t if_SPI:1; // 1=enable, 0=disable
				uint8_t if_reserved:1; // 1=enable, 0=disable
			};
		};
	} payload;
	struct ubx_msg_footer_s footer;
} __attribute__((packed, aligned(1))) const ubx_msg__CFG_MSG__SetMessageRates_s_default = {
	.sync = {
		.syncChars = UBX_SYNC_CHARS,
	},
	.header = {
		.ID = UBX_MSG_ID__CFG_MSG,
		.length = LIB_BYTEORDER_HTON_U16(8),
		//.length = LIB_BYTEORDER_HTON_U16(sizeof(((struct ubx_msg__CFG_MSG__SetMessageRates_s*)NULL)->payload)),
	},
	.payload = {0},
	.footer = {0},
};

static void ubx_checksum(struct ubx_msg_header_s * header, struct ubx_msg_footer_s * footer) {
	footer->ck_a = 0;
	footer->ck_b = 0;
	for (size_t i=0; i<(size_t)(((void *)footer)-((void *)header)); i++) { //TODO fix this, signed/unsigned integer comparison warning
		footer->ck_a += ((uint8_t *)header)[i];
		footer->ck_b += footer->ck_a;
	}
}

void drv_gps_init(void) {
	
	//initialize serial1 port for communicating with GPS
	
	//add ISR to vector table
	
	//enable interrupts on GPS pulse GPIO pin
}

#endif // HW_GPS_UBLOX_NEO6_H

#undef HW_GPS_UBLOX_NEO6_C