#include "../../hal/hal.h"
#include "drv_timer.h"

static volatile lib_datetime_interval_t monotonic_ms = 0;

static volatile lib_datetime_interval_t timestamp = 0;

static volatile bool absoluteDateInitialized = false;
static volatile bool absoluteTimeInitialized = false;
static volatile bool initialized = false;

struct lib_datetime_s absoluteTime = {0};

void isr_incrementMonotonic(void) {
	monotonic_ms++;
}

void drv_timer_init(void) {
	if (!initialized) {
		hal_timer_init();
		hal_timer_setInterruptInterval(isr_incrementMonotonic, 1000); //once every ms
	}
}

lib_datetime_interval_t drv_timer_getMonotonicTime(void) {
	return monotonic_ms;
}

bool drv_timer_absoluteDateIsAvailable(void) {
	return absoluteDateInitialized;
}

bool drv_timer_absoluteTimeIsAvailable(void) {
	return absoluteTimeInitialized;
}

void drv_timer_setAbsoluteDateTime(struct lib_datetime_s * dt) {
	timestamp = monotonic_ms;
	lib_datetime_copy(dt, &absoluteTime);
	absoluteDateInitialized = true;
	absoluteTimeInitialized = true;
}

void drv_timer_setAbsoluteDate(struct lib_datetime_s * dt) {
	timestamp = monotonic_ms;
	lib_datetime_copyDate(dt, &absoluteTime);
	absoluteDateInitialized = true;
}

void drv_timer_setAbsoluteTime(lib_datetime_time_t time) {
	timestamp = monotonic_ms;
	struct lib_datetime_s dt;
	lib_datetime_convertTimeToDatetime(time, &dt); //TODO error checking
	lib_datetime_copyTime(&dt, &absoluteTime);
	absoluteTimeInitialized = true;
}

enum drv_timer_err_e drv_timer_getAbsoluteDateTime(struct lib_datetime_s * dt) {
	lib_datetime_interval_t offset = monotonic_ms - timestamp;
	if (!absoluteTimeInitialized) return DRV_TIMER_ERR__ABSOLUTE_TIME_TMP_UNAVAILABLE;
	if (!absoluteDateInitialized) return DRV_TIMER_ERR__ABSOLUTE_DATE_TMP_UNAVAILABLE;
	*dt = absoluteTime;
	lib_datetime_addIntervalToDateTime(dt, offset);
	
}

enum drv_timer_err_e drv_timer_getAbsoluteDate(struct lib_datetime_s * dt) {
	lib_datetime_interval_t offset = monotonic_ms - timestamp;
	if (!absoluteDateInitialized) return DRV_TIMER_ERR__ABSOLUTE_DATE_TMP_UNAVAILABLE;
	*dt = absoluteTime;
	lib_datetime_addIntervalToDateTime(dt, offset);
	lib_datetime_clearTime(dt);
}

enum drv_timer_err_e drv_timer_getAbsoluteTime(lib_datetime_time_t * time) {
	lib_datetime_interval_t offset = monotonic_ms - timestamp;
	if (!absoluteTimeInitialized) return DRV_TIMER_ERR__ABSOLUTE_TIME_TMP_UNAVAILABLE;
	lib_datetime_convertDateTimeToTime(&absoluteTime, time);
	lib_datetime_addIntervalToTime(time, offset);
}