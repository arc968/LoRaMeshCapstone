#include "lib_datetime.h"

void lib_datetime_copy(struct lib_datetime_s * src, struct lib_datetime_s * dst) {
	lib_datetime_copyDate(src, dst);
	lib_datetime_copyTime(src, dst);
}

void lib_datetime_copyDate(struct lib_datetime_s * src, struct lib_datetime_s * dst) {
	dst->year = src->year;
	dst->month = src->month;
	dst->day = src->day;
}

void lib_datetime_copyTime(struct lib_datetime_s * src, struct lib_datetime_s * dst) {
	dst->hour = src->hour;
	dst->min = src->min;
	dst->sec = src->sec;
	dst->ms = src->ms;
}

void lib_datetime_clearDate(struct lib_datetime_s * dt) {
	dt->year = 0;
	dt->month = 0;
	dt->day = 0;
}

void lib_datetime_clearTime(struct lib_datetime_s * dt) {
	dt->hour = 0;
	dt->min = 0;
	dt->sec = 0;
	dt->ms = 0;
}

enum lib_datetime_err_e lib_datetime_validateTime(lib_datetime_time_t time) {
	return LIB_DATETIME_ERR__NONE; //TODO
}

int lib_datetime_cmp(struct lib_datetime_s * a, struct lib_datetime_s * b) {
	return 0; //TODO
}

enum lib_datetime_err_e lib_datetime_convertTimeToDatetime(lib_datetime_time_t time, struct lib_datetime_s * dt) {
	return LIB_DATETIME_ERR__NONE; //TODO
}

enum lib_datetime_err_e lib_datetime_convertDatetimeToTime(struct lib_datetime_s * dt, lib_datetime_time_t * time) {
	return LIB_DATETIME_ERR__NONE; //TODO
}

enum lib_datetime_err_e lib_datetime_convertRealtimeToDatetime(lib_datetime_realtime_t realtime, struct lib_datetime_s * dt) {
	return LIB_DATETIME_ERR__NONE; //TODO
}

enum lib_datetime_err_e lib_datetime_convertDatetimeToRealtime(struct lib_datetime_s * dt, lib_datetime_realtime_t * realtime) {
	return LIB_DATETIME_ERR__NONE; //TODO
}

//adds an interval to a time, wrapping around as necessary
lib_datetime_time_t lib_datetime_addIntervalToTime(lib_datetime_time_t time, lib_datetime_interval_t interval) {
	return time + interval; //TODO
}

//adds an interval to a datetime
void lib_datetime_addIntervalToDatetime(struct lib_datetime_s * dt, lib_datetime_interval_t interval) {
	
}