#include "../../hal/hal.h"
#include "drv_timer.h"

//static volatile lib_datetime_interval_t monotonic_ms = 0;

static volatile lib_datetime_interval_t timestamp = 0;

static volatile bool absoluteDateInitialized = false;
static volatile bool absoluteTimeInitialized = false;
static volatile bool initialized = false;

static struct lib_datetime_s absoluteTime = {0}; //does not handle volatile properly

static void (* volatile cb_onAbsoluteTimeAvailable)(void) = NULL;
static void (* volatile cb_onAbsoluteDateAvailable)(void) = NULL;

/*
void isr_incrementMonotonic(void) {
	monotonic_ms++;
}
*/

void drv_timer_init(void) {
	if (!initialized) {
		//hal_timer_init(isr_incrementMonotonic, 1000);
		//hal_timer_setInterruptInterval(isr_incrementMonotonic, 1000); //once every ms
		initialized = true;
	}
}

lib_datetime_interval_t drv_timer_getMonotonicTime(void) {
	return hal_timer_millis();
	//return monotonic_ms;
}

bool drv_timer_absoluteDateIsAvailable(void) {
	return absoluteDateInitialized;
}

bool drv_timer_absoluteTimeIsAvailable(void) {
	return absoluteTimeInitialized;
}

void drv_timer_setCallbackOnAbsoluteTimeAvailable(void (*func_ptr)(void)) {
	cb_onAbsoluteTimeAvailable = func_ptr;
}

void drv_timer_setCallbackOnAbsoluteDateAvailable(void (*func_ptr)(void)) {
	cb_onAbsoluteDateAvailable = func_ptr;
}

void drv_timer_setAbsoluteDateTime(struct lib_datetime_s * dt) {
	//timestamp = monotonic_ms;
	timestamp = hal_timer_millis();
	lib_datetime_copy(dt, &absoluteTime);
	if (!absoluteTimeInitialized) {
		absoluteTimeInitialized = true;
		if (cb_onAbsoluteTimeAvailable != NULL) (*cb_onAbsoluteTimeAvailable)();
	}
	if (!absoluteDateInitialized) {
		absoluteDateInitialized = true;
		if (cb_onAbsoluteDateAvailable != NULL) (*cb_onAbsoluteDateAvailable)();
	}
}

void drv_timer_setAbsoluteDate(struct lib_datetime_s * dt) {
	//timestamp = monotonic_ms;
	timestamp = hal_timer_millis();
	lib_datetime_copyDate(dt, &absoluteTime);
	if (!absoluteDateInitialized) {
		absoluteDateInitialized = true;
		if (cb_onAbsoluteDateAvailable != NULL) (*cb_onAbsoluteDateAvailable)();
	}
}

void drv_timer_setAbsoluteTime(lib_datetime_time_t time) {
	//timestamp = monotonic_ms;
	timestamp = hal_timer_millis();
	struct lib_datetime_s dt;
	lib_datetime_convertTimeToDatetime(time, &dt); //TODO error checking
	lib_datetime_copyTime(&dt, &absoluteTime);
	if (!absoluteTimeInitialized) {
		absoluteTimeInitialized = true;
		if (cb_onAbsoluteTimeAvailable != NULL) (*cb_onAbsoluteTimeAvailable)();
	}
}

enum drv_timer_err_e drv_timer_getAbsoluteDateTime(struct lib_datetime_s * dt) {
	//lib_datetime_interval_t offset = monotonic_ms - timestamp;
	lib_datetime_interval_t offset = hal_timer_millis() - timestamp;
	if (!absoluteTimeInitialized) return DRV_TIMER_ERR__ABSOLUTE_TIME_TMP_UNAVAILABLE;
	if (!absoluteDateInitialized) return DRV_TIMER_ERR__ABSOLUTE_DATE_TMP_UNAVAILABLE;
	*dt = absoluteTime;
	lib_datetime_addIntervalToDatetime(dt, offset);
	return DRV_TIMER_ERR__NONE;
}

enum drv_timer_err_e drv_timer_getAbsoluteDate(struct lib_datetime_s * dt) {
	//lib_datetime_interval_t offset = monotonic_ms - timestamp;
	lib_datetime_interval_t offset = hal_timer_millis() - timestamp;
	if (!absoluteDateInitialized) return DRV_TIMER_ERR__ABSOLUTE_DATE_TMP_UNAVAILABLE;
	*dt = absoluteTime;
	lib_datetime_addIntervalToDatetime(dt, offset);
	lib_datetime_clearTime(dt);
	return DRV_TIMER_ERR__NONE;
}

enum drv_timer_err_e drv_timer_getAbsoluteTime(lib_datetime_time_t * time) {
	//lib_datetime_interval_t offset = monotonic_ms - timestamp;
	lib_datetime_interval_t offset = hal_timer_millis() - timestamp;
	if (!absoluteTimeInitialized) return DRV_TIMER_ERR__ABSOLUTE_TIME_TMP_UNAVAILABLE;
	lib_datetime_convertDatetimeToTime(&absoluteTime, time);
	*time = lib_datetime_addIntervalToTime(*time, offset);
	return DRV_TIMER_ERR__NONE;
}

enum drv_timer_err_e drv_timer_getRealtime(lib_datetime_realtime_t * realtime) {
	struct lib_datetime_s dt;
	enum drv_timer_err_e err = drv_timer_getAbsoluteDateTime(&dt);
	if (err != DRV_TIMER_ERR__NONE) return err;
	lib_datetime_convertDatetimeToRealtime(&dt, realtime);
	return DRV_TIMER_ERR__NONE;
}

