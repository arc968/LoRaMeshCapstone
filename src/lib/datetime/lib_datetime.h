#ifndef LIB_DATETIME_H
#define LIB_DATETIME_H
#if defined (__cplusplus)
extern "C" {
#endif

#include <stdint.h>

enum lib_datetime_err_e {
	LIB_DATETIME_ERR__NONE = 0, //no error, operation was successful
	LIB_DATETIME_ERR__TIME_OUT_OF_RANGE,
	LIB_DATETIME_ERR__DATETIME_OUT_OF_RANGE,
};

typedef uint32_t lib_datetime_time_t; //time of day in ms, there are 24h*60m*60s*1000ms = 86,400,000ms in a day

typedef uint64_t lib_datetime_realtime_t; //time since epoch in ms

typedef uint64_t lib_datetime_interval_t; //time interval in ms

#define LIB_DATETIME__MS_IN_DAY 86400000 //(24*60*60*1000)

#define PACK_STRUCTS
#define USE_BITFIELDS
#if defined(USE_BITFIELDS)
//bitfields are used to reduce the struct down to 6 bytes
//this will increase binary size by quite a bit, but saves a lot of memory
#pragma scalar_storage_order big-endian
struct lib_datetime_s {
	union {
		struct {
			uint8_t :8;
			uint16_t year:12, //yyyy 00..4095
					 month:4; //mm 01..12
			uint32_t day:5,   //dd  01..31
					 hour:5,  //hh  00..23
					 min:6,   //mm  00..59
					 sec:6,   //ss  00..59
					 ms:10;   //sss 00..999
		};
		uint64_t raw;
	};
}
//packed attribute is used to remove 2 byte padding (6->8 bytes)
#if defined(PACK_STRUCTS)
	__attribute__((packed, aligned(1))) //__attribute__((scalar_storage_order("big-endian"))) ????????
#endif
;
#pragma scalar_storage_order default
#else
struct lib_datetime_s {
	uint16_t year; //yyyy
	uint8_t month; //mm  01..12
	uint8_t day;   //dd  01..31
	uint8_t hour;  //hh  00..23
	uint8_t min;   //mm  00..59
	uint8_t sec;   //ss  00..59
	uint16_t ms;   //sss 00..999
}
#if defined(PACK_STRUCTS)
	__attribute__((packed))
#endif
;
#endif

void lib_datetime_copy(struct lib_datetime_s * src, struct lib_datetime_s * dst);

void lib_datetime_copyDate(struct lib_datetime_s * src, struct lib_datetime_s * dst);

void lib_datetime_copyTime(struct lib_datetime_s * src, struct lib_datetime_s * dst);

void lib_datetime_clearDate(struct lib_datetime_s * dt);

void lib_datetime_clearTime(struct lib_datetime_s * dt);

enum lib_datetime_err_e lib_datetime_validateTime(lib_datetime_time_t time);

enum lib_datetime_err_e lib_datetime_validateDatetime(struct lib_datetime_s * dt);

int lib_datetime_cmp(struct lib_datetime_s * a, struct lib_datetime_s * b);

void lib_datetime_convertTimeToDatetime(lib_datetime_time_t time, struct lib_datetime_s * dt);

void lib_datetime_convertDatetimeToTime(struct lib_datetime_s * dt, lib_datetime_time_t * time);

void lib_datetime_convertRealtimeToDatetime(lib_datetime_realtime_t realtime, struct lib_datetime_s * dt);

void lib_datetime_convertDatetimeToRealtime(struct lib_datetime_s * dt, lib_datetime_realtime_t * realtime);

lib_datetime_time_t lib_datetime_convertRealtimeToTime(lib_datetime_realtime_t realtime);

//adds an interval to a time, wrapping around as necessary
lib_datetime_time_t lib_datetime_addIntervalToTime(lib_datetime_time_t time, lib_datetime_interval_t interval);

//adds an interval to a datetime
void lib_datetime_addIntervalToDatetime(struct lib_datetime_s * dt, lib_datetime_interval_t interval);

#if defined (__cplusplus)
}
#endif
#endif // LIB_DATETIME_H
