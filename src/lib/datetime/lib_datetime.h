#ifndef LIB_DATETIME_H
#define LIB_DATETIME_H
#if defined (__cplusplus)
extern "C" {
#endif

#include <stdint.h>

typedef uint32_t lib_datetime_time_t; //time of day in ms, there are 24h*60m*60s*1000ms = 86,400,000ms in a day

typedef uint32_t lib_datetime_interval_t; //time interval in ms

#define LIB_DATETIME_MS_IN_DAY (24*60*60*1000)

struct lib_datetime_s {
	uint16_t year; //yyyy
	uint8_t month; //mm  01..12
	uint8_t day;   //dd  01..31
	uint8_t hour;  //hh  00..23
	uint8_t min;   //mm  00..59
	uint8_t sec;   //ss  00..59
	uint16_t ms;   //sss 00..999
};

int lib_datetime_cmp(struct lib_datetime_s * a, struct lib_datetime_s * b);

//returns -1 if conversion failed
int lib_datetime_timeToDatetime(lib_datetime_time_t time, struct lib_datetime_s * dt);

//returns -1 if conversion failed
int lib_datetime_datetimeToTime(struct lib_datetime_s * dt, lib_datetime_time_t * time);

//adds an interval to a time, wrapping around as necessary
lib_datetime_time_t lib_datetime_addIntervalToTime(lib_datetime_time_t time, lib_datetime_interval_t interval);

#if defined (__cplusplus)
}
#endif
#endif // LIB_DATETIME_H