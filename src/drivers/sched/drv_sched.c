#include "../hal/hal.h"
#include "drv_sched.h"

#define DRV_SCHED_MAX_JOBS 16

void drv_sched_init(void) {
	
}

/*
Will attempt to sleep for as long as possible, only waking for scheduled jobs
*/
#ifdef __GNUC__
__attribute__((noreturn))
#endif
void drv_sched_start(void) {
	while (1) {
		
	}
}