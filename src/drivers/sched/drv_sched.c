#include "../../hal/hal.h"
#include "drv_sched.h"

#include "../gps/drv_gps.h"

#define DRV_SCHED_MAX_JOBS 16 //must be >=1

enum job_type_e {
	JOB_TYPE__ONCE = 0,
	JOB_TYPE__REPEAT = 1,
	JOB_TYPE__AT = 2,
};

struct job_s {
	struct job_s * next;
	lib_datetime_interval_t interval;
	lib_datetime_time_t time;
	void (*fun_ptr)(void);
	enum drv_sched_pri_e priority;
	enum job_type_e type;
};

struct state_s {
	struct job_s * head_ready;
	struct job_s * head_empty;
	lib_datetime_time_t lastRunTime;;
	struct job_s jobs[DRV_SCHED_MAX_JOBS];
} state;

void drv_sched_init(void) {
	state.head_ready = NULL;
	state.head_empty = &(state.jobs[0]);
	state.lastRunTime = 0;
	for (int i=0; i<DRV_SCHED_MAX_JOBS; i++) {
		if (i == DRV_SCHED_MAX_JOBS-1) {
			state.jobs[i].next = NULL;
		} else {
			state.jobs[i].next = &(state.jobs[i+1]);
		}
		state.jobs[i].interval = 0;
		state.jobs[i].time = 0;
		state.jobs[i].fun_ptr = NULL;
		state.jobs[i].priority = DRV_SCHED_PRI__IDLE;
		state.jobs[i].type = JOB_TYPE__ONCE;
	}
}

static int schedule(void (*fun_ptr)(void), enum job_type_e type, enum drv_sched_pri_e priority, lib_datetime_interval_t interval, lib_datetime_time_t time, lib_datetime_time_t currentTime) {
	if (state.head_empty == NULL) return -1; //failed to schedule, no job slots remaining
	struct job_s * job = state.head_empty; //get empty job slot
	state.head_empty = job->next; //remove from linked list of empty jobs
	
	job->interval = interval;
	job->time = time;
	job->fun_ptr = fun_ptr;
	job->priority = priority;
	job->type = type;
	
	if (state.head_ready == NULL) {
		state.head_ready = job;
		state.lastRunTime = currentTime;
	} else {
		struct job_s * insertJobPtr = state.head_ready;
		while (insertJobPtr->time >= state.lastRunTime) insertJobPtr = insertJobPtr->next;
		while (insertJobPtr->next != NULL && insertJobPtr->next->time < job->time) insertJobPtr = insertJobPtr->next;
		job->next = insertJobPtr->next;
		insertJobPtr->next = job;
	}
	return 0;
}

int drv_sched_once(void (*fun_ptr)(void), enum drv_sched_pri_e priority, lib_datetime_interval_t delay_ms) {
	lib_datetime_time_t currentTime = drv_gps_getTime();
	if (delay_ms > LIB_DATETIME__MS_IN_DAY) return -1; //failed to schedule, interval is longer than one day
	return schedule(fun_ptr, JOB_TYPE__ONCE, priority, 0, lib_datetime_addIntervalToTime(currentTime, delay_ms), currentTime);
}

int drv_sched_repeating(void (*fun_ptr)(void), enum drv_sched_pri_e priority, lib_datetime_interval_t interval_ms) {
	lib_datetime_time_t currentTime = drv_gps_getTime();
	if (interval_ms > LIB_DATETIME__MS_IN_DAY) return -1; //failed to schedule, interval is longer than one day
	return schedule(fun_ptr, JOB_TYPE__REPEAT, priority, interval_ms, lib_datetime_addIntervalToTime(currentTime, interval_ms), currentTime);
}

int drv_sched_at(void (*fun_ptr)(void), enum drv_sched_pri_e priority, lib_datetime_time_t time) {
	lib_datetime_time_t currentTime = drv_gps_getTime();
	return schedule(fun_ptr, JOB_TYPE__AT, priority, 0, time, currentTime);
}

/*
Will attempt to sleep for as long as possible, only waking for scheduled jobs
*/
#ifdef __GNUC__
__attribute__((noreturn))
#endif
void drv_sched_start(void) {
	while (1) {
		
		
		//sleep
	}
}