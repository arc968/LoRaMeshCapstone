#if !defined(HW_GPS_UBLOX_NEO6_C)
	#error "Do not directly include this header file, include hardware.h instead."
#elif !defined(HW_GPS_UBLOX_NEO6_UBX_H)
	#define HW_GPS_UBLOX_NEO6_UBX_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "../../../../lib/byteorder/lib_byteorder.h"

#define UBX_SYNC_CHARS {0xB5, 0x62}

//ACK
#define UBX_MSG_ID__ACK_ACK {0x05, 0x01}
	#define UBX_MSG__ACK_ACK {UBX_MSG_ID__ACK_ACK, 2}
#define UBX_MSG_ID__ACK_NAK {0x05, 0x00}
	#define UBX_MSG__ACK_NAK {UBX_MSG_ID__ACK_NAK, 2}
//CFG
#define UBX_MSG_ID__CFG_PRT {0x06, 0x00}
	#define UBX_MSG__CFG_PRT__SetPortConfigurationForUART {UBX_MSG_ID__CFG_PRT, 20}
#define UBX_MSG_ID__CFG_MSG {0x06, 0x01}
	#define UBX_MSG__CFG_MSG__SetMessageRate {UBX_MSG_ID__CFG_MSG, 3}
#define UBX_MSG_ID__CFG_TP {0x06, 0x07}
#define UBX_MSG_ID__CFG_TP5 {0x06, 0x31}
	#define UBX_MSG__CFG_TP5__SetTimePulse {UBX_MSG_ID__CFG_TP5, 32}
//NAV
#define UBX_MSG_ID__NAV_TIMEUTC {0x01, 0x21}
#define UBX_MSG__NAV_TIMEUTC__TimeSolution {UBX_MSG_ID__NAV_TIMEUTC, 20}
//NMEA
#define UBX_MSG_ID__NMEA_GPGGA {0xF0, 0x00}
#define UBX_MSG_ID__NMEA_GPGLL {0xF0, 0x01}
#define UBX_MSG_ID__NMEA_GPGSA {0xF0, 0x02}
#define UBX_MSG_ID__NMEA_GPRMC {0xF0, 0x04}
#define UBX_MSG_ID__NMEA_GPVTG {0xF0, 0x05}

typedef uint8_t U1;
typedef int8_t I1;
typedef uint8_t X1;
typedef uint16_t U2;
typedef int16_t I2;
typedef uint8_t X2[2];
typedef uint32_t U4;
typedef int32_t I4;
typedef uint8_t X4[4];
typedef float R4;
typedef double R8;
typedef uint8_t CH;

struct ubx_msg_sync_s {
	union {
		const uint8_t syncChars[2];
		struct {
			const uint8_t syncChar1;
			const uint8_t syncChar2;
		};
	};
} __attribute__((packed, aligned(1))) const ubx_msg_sync_s_default = {
	.syncChars = UBX_SYNC_CHARS,
};

#define UBX_MSG_HEADER_SIZE 4
struct ubx_msg_header_s {
	union {
		const uint8_t ID[2];
		struct {
			const uint8_t msgClass;
			const uint8_t msgID;
		};
	};
	struct {
		const uint16_t length;
	} __attribute__((scalar_storage_order("little-endian")));
} __attribute__((packed, aligned(1)));

struct ubx_msg_checksum_s {
	uint8_t ck_a;
	uint8_t ck_b;
} __attribute__((packed, aligned(1)));

static void ubx_checksum(uint8_t * raw, size_t size, struct ubx_msg_checksum_s * checksum) {
	checksum->ck_a = 0;
	checksum->ck_b = 0;
	for (size_t i=0; i<size; i++) {
		checksum->ck_a += raw[i];
		checksum->ck_b += checksum->ck_a;
	}
}

#define UBX_CHECKSUM(ubx_msg) ubx_checksum(&((ubx_msg).header), offsetof(typeof((ubx_msg)), checksum) - offsetof(typeof((ubx_msg)), header), &((ubx_msg).checksum));

// BEGIN PACKET STRUCTS

struct ubx_msg_stripped_s {
	struct ubx_msg_header_s header;
	uint8_t payload[];
};

struct ubx_msg__ACK_ACK_s {
	struct ubx_msg_sync_s sync;
	struct ubx_msg_header_s header;
	struct {
		union {
			struct {
				U1 msgClass;
				U1 msgID;
			};
			uint8_t msg[2];
		};
	} payload;
	struct ubx_msg_checksum_s checksum;
} __attribute__((packed, aligned(1))) const ubx_msg__ACK_ACK_s_default = {
	.sync = UBX_SYNC_CHARS,
	.header = UBX_MSG__ACK_ACK,
};

struct ubx_msg__ACK_NAK_s {
	struct ubx_msg_sync_s sync;
	struct ubx_msg_header_s header;
	struct {
		union {
			struct {
				U1 msgClass;
				U1 msgID;
			};
			uint8_t msg[2];
		};
	} payload;
	struct ubx_msg_checksum_s checksum;
} __attribute__((packed, aligned(1))) const ubx_msg__ACK_NAK_s_default = {
	.sync = UBX_SYNC_CHARS,
	.header = UBX_MSG__ACK_NAK,
};

struct ubx_msg__CFG_PRT__SetPortConfigurationForUART_s {
	struct ubx_msg_sync_s sync;
	struct ubx_msg_header_s header;
	struct {
		U1 portID;
		U1 reserved0;
		X2 txReady; //set to 0
		struct {
			X1 charLen:2,:1,reserved1:1,:0;
			X1 :2,nStopBits:2,parity:3,:0;
			X1 :8; X1 :8; //2 byte padding
		} __attribute__((scalar_storage_order("big-endian"))) mode;
		struct {
			U4 baudRate;
		} __attribute__((scalar_storage_order("little-endian")));
		struct {
			X1 :6,nmea:1,ubx:1;
			X1 :8;
		} __attribute__((scalar_storage_order("big-endian"))) inProtoMask;
		struct {
			X1 :6,nmea:1,ubx:1;
			X1 :8;
		} __attribute__((scalar_storage_order("big-endian"))) outProtoMask;
		U2 reserved4;
		U2 reserved5;
	} payload;
	struct ubx_msg_checksum_s checksum;
} __attribute__((packed, aligned(1))) const ubx_msg__CFG_PRT__SetPortConfigurationForUART_s_default = {
	.sync = UBX_SYNC_CHARS,
	.header = UBX_MSG__CFG_PRT__SetPortConfigurationForUART,
	.payload.portID = 1,
	.payload.mode.reserved1 = 1,
};

struct ubx_msg__CFG_MSG__SetMessageRate_s {
	struct ubx_msg_sync_s sync;
	struct ubx_msg_header_s header;
	struct {
		union {
			struct {
				U1 msgClass;
				U1 msgID;
			};
			uint8_t msg[2];
		};
		U1 rate;
	} payload;
	struct ubx_msg_checksum_s checksum;
} __attribute__((packed, aligned(1))) const ubx_msg__CFG_MSG__SetMessageRate_s_default = {
	.sync = UBX_SYNC_CHARS,
	.header = UBX_MSG__CFG_MSG__SetMessageRate,
};

struct ubx_msg__NAV_TIMEUTC__TimeSolution_s {
	struct ubx_msg_sync_s sync;
	struct ubx_msg_header_s header;
	struct {
		struct {
			U4 iTOW;
			U4 tAcc;
			I4 nano;
			U2 year;
			U1 month;
			U1 day;
			U1 hour;
			U1 min;
			U1 sec;
		} __attribute__((scalar_storage_order("little-endian")));
		struct {
			X1  :5,validTOW:1,validWKN:1,validUTC:1;
		} __attribute__((scalar_storage_order("big-endian")));
	} payload;
	struct ubx_msg_checksum_s checksum;
} __attribute__((packed, aligned(1))) const ubx_msg__NAV_TIMEUTC__TimeSolution_s_default = {
	.sync = UBX_SYNC_CHARS,
	.header = UBX_MSG__NAV_TIMEUTC__TimeSolution,
};

struct ubx_msg__CFG_TP5__SetTimePulse_s {
	struct ubx_msg_sync_s sync;
	struct ubx_msg_header_s header;
	struct {
		struct {
			U1 tpIdx;
			U1 reserved0;
			U2 reserved1;
			I2 antCableDelay_ns;
			I2 rfGroupDelay_ns;
			U4 freqPeriod;
			U4 freqPeriodLock;
			U4 pulseLenRatio;
			U4 pulseLenRatioLock;
			I4 userConfigDelay;
		} __attribute__((scalar_storage_order("little-endian")));
		struct {
			X1  gridUtcGps:1,
				polarity:1,
				alignToTow:1,
				isLength:1,
				isFreq:1,
				lockedOtherSet:1,
				LockGpsFreq:1,
				Active:1;
			X1 :8; X1 :8; X1 :8; //3 byte padding
		} __attribute__((scalar_storage_order("big-endian")));
	} payload;
	struct ubx_msg_checksum_s checksum;
} __attribute__((packed, aligned(1))) const ubx_msg__CFG_TP5__SetTimePulse_s_default = {
	.sync = UBX_SYNC_CHARS,
	.header = UBX_MSG__CFG_TP5__SetTimePulse,
};

#ifdef __cplusplus
}
#endif

#endif // HW_GPS_UBLOX_NEO6_UBX_H