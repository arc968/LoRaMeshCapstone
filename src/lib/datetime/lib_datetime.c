#include "lib_datetime.h"

//NOT YET DONE
lib_datetime_time_t lib_datetime_addIntervalToTime(lib_datetime_time_t time, lib_datetime_interval_t interval) {
	return time + interval; //NOT YET DONE
}

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