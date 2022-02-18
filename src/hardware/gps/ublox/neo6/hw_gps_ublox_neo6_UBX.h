#if !defined(HW_GPS_UBLOX_NEO6_C)
	#error "Do not directly include this header file, include hardware.h instead."
#elif !defined(HW_GPS_UBLOX_NEO6_UBX_H)
	#define HW_GPS_UBLOX_NEO6_UBX_H

#define UBX_SYNC_CHARS {0xB5, 0x62}
#define UBX_MSG_ID__CFG_MSG {0x06, 0x01}
#define UBX_MSG_ID__CFG_TP {0x06, 0x07}

#endif // HW_GPS_UBLOX_NEO6_UBX_H