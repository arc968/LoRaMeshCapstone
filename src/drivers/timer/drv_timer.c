#include "../../hal/hal.h"
#include "drv_timer.h"

volatile lib_datetime_interval_t monotonic_time = 0;

void isr_incrementMonotonic(void) {
	monotonic_time++;
}

void drv_timer_init(void) {
	hal_timer_init();
	hal_timer_setInterruptInterval(isr_incrementMonotonic, 1000); //once every ms
}

lib_datetime_interval_t drv_timer_getMonotonicTime(void) {
	return monotonic_time;
}