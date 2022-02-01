#include "../../hal/hal.h"
#include "drv_timer.h"

volatile lib_datetime_interval_t monotonic_time = 0;

void drv_timer_init(void) {
	
}

void isr_incrementMonotonic(void) {
	monotonic_time++;
}

lib_datetime_interval_t drv_timer_getMonotonicTime(void) {
	return monotonic_time;
}