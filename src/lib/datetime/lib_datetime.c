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

void lib_datetime_clearDateTime(struct lib_datetime_s * dt) {
	lib_datetime_clearDate(dt);
	lib_datetime_clearTime(dt);
}

enum lib_datetime_err_e lib_datetime_validateTime(lib_datetime_time_t time) {
	if (time > LIB_DATETIME__MS_IN_DAY) return LIB_DATETIME_ERR__TIME_OUT_OF_RANGE;
	return LIB_DATETIME_ERR__NONE;
}

//TODO: validate days in different months
enum lib_datetime_err_e lib_datetime_validateDatetime(struct lib_datetime_s * dt) {
	if (dt->month < 1 || dt->month > 12) return LIB_DATETIME_ERR__DATETIME_OUT_OF_RANGE;
	if (dt->day < 1 || dt->day > 31) return LIB_DATETIME_ERR__DATETIME_OUT_OF_RANGE;
	if (dt->hour > 23) return LIB_DATETIME_ERR__DATETIME_OUT_OF_RANGE;
	if (dt->min > 59) return LIB_DATETIME_ERR__DATETIME_OUT_OF_RANGE;
	if (dt->sec > 59) return LIB_DATETIME_ERR__DATETIME_OUT_OF_RANGE;
	if (dt->ms > 999) return LIB_DATETIME_ERR__DATETIME_OUT_OF_RANGE;
	return LIB_DATETIME_ERR__NONE;
}

int lib_datetime_cmp(struct lib_datetime_s * a, struct lib_datetime_s * b) {
	#if defined(USE_BITFIELDS)
	if (a->raw > b->raw) return 1;
	if (a->raw < b->raw) return -1;
	return 0;
	#else
	if (a->year > b->year) return 1;
	if (a->year < b->year) return -1;
	if (a->month > b->month) return 1;
	if (a->month < b->month) return -1;
	if (a->day > b->day) return 1;
	if (a->day < b->day) return -1;
	if (a->hour > b->hour) return 1;
	if (a->hour < b->hour) return -1;
	if (a->min > b->min) return 1;
	if (a->min < b->min) return -1;
	if (a->sec > b->sec) return 1;
	if (a->sec < b->sec) return -1;
	if (a->ms > b->ms) return 1;
	if (a->ms < b->ms) return -1;
	return 0;
	#endif
}

void lib_datetime_convertTimeToDatetime(lib_datetime_time_t time, struct lib_datetime_s * dt) {
	lib_datetime_convertRealtimeToDatetime((lib_datetime_realtime_t)time, dt);
}

void lib_datetime_convertDatetimeToTime(struct lib_datetime_s * dt, lib_datetime_time_t * time) {
	*time = (3600000*dt->hour) + (60000*dt->min) + (1000*dt->sec) + dt->ms;
}

//adapted from https://www.oryx-embedded.com/doc/date__time_8c_source.html
void lib_datetime_convertRealtimeToDatetime(lib_datetime_realtime_t realtime, struct lib_datetime_s * dt) {
	lib_datetime_realtime_t rt = realtime;
	
	dt->ms = rt % 1000;
	rt /= 1000;
	dt->sec = rt % 60;
	rt /= 60;
	dt->min = rt % 60;
	rt /= 60;
	dt->hour = rt % 24;
	rt /= 24;
	
	uint64_t a = (uint64_t) ((4*rt + 102032)/146097 + 15);
	uint64_t b = (uint64_t) (rt + 2442113 + a - (a/4));
	uint64_t c = (20*b - 2442) / 7305;
	uint64_t d = b - 365*c - (c/4);
	uint64_t e = d*1000/30601;
	uint64_t f = d - e*30 - e*601/1000;
	
	//January and February are counted as months 13 and 14 of the previous year
	if(e <= 13) {
		c -= 4716;
		e -= 1;
	} else {
		c -= 4715;
		e -= 13;
	}
	
	dt->year = c;
	dt->month = e;
	dt->day = f;
}

//adapted from https://www.oryx-embedded.com/doc/date__time_8c_source.html
void lib_datetime_convertDatetimeToRealtime(struct lib_datetime_s * dt, lib_datetime_realtime_t * realtime) {
	lib_datetime_realtime_t t;
	
	//Year
	uint64_t y = dt->year;
	//Month of year
	uint64_t m = dt->month;
	//Day of month
	uint64_t d = dt->day;
	
	//January and February are counted as months 13 and 14 of the previous year
	if(m <= 2) {
		m += 12;
		y -= 1;
	}
	
	//Convert years to days
	t = (365*y) + (y/4) - (y/100) + (y/400);
	//Convert months to days
	t += (30*m) + (3*(m + 1)/5) + d;
	//Unix time starts on January 1st, 1970
	t -= 719561;
	//Convert days to seconds
	t *= 86400;
	//Add hours, minutes and seconds
	t += (3600*dt->hour) + (60*dt->min) + dt->sec;
	//Convert seconds to milliseconds
	t *= 1000;
	//Add milliseconds
	t += dt->ms;
	
	*realtime = t;
}

lib_datetime_time_t lib_datetime_convertRealtimeToTime(lib_datetime_realtime_t realtime) {
	struct lib_datetime_s dt;
	lib_datetime_time_t out;
	lib_datetime_convertRealtimeToDatetime(realtime, &dt);
	lib_datetime_convertDatetimeToTime(&dt, &out);
	return out;
}

//adds an interval to a time, wrapping around as necessary
//should probably just be a macro
lib_datetime_time_t lib_datetime_addIntervalToTime(lib_datetime_time_t time, lib_datetime_interval_t interval) {
	return (((uint64_t)time) + interval) % LIB_DATETIME__MS_IN_DAY;
}

//adds an interval to a datetime
void lib_datetime_addIntervalToDatetime(struct lib_datetime_s * dt, lib_datetime_interval_t interval) {
	lib_datetime_realtime_t rt = 0;
	lib_datetime_convertDatetimeToRealtime(dt, &rt);
	rt += interval;
	lib_datetime_convertRealtimeToDatetime(rt, dt);
}