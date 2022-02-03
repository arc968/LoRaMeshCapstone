#include "../../hal/hal.h"
#include "drv_sched.h"

#include "../timer/drv_timer.h"

enum job_type_e {
	JOB_TYPE__NONE = 0,
	JOB_TYPE__ONCE,
	JOB_TYPE__REPEAT,
	JOB_TYPE__ONCE_AT,
	JOB_TYPE__REPEAT_AT,
};

struct job_s {
	struct job_s * next;
	lib_datetime_interval_t interval;
	lib_datetime_interval_t time;
	void (*func_ptr)(void);
	enum drv_sched_pri_e priority;
	enum job_type_e type;
};

struct state_s {
	struct job_s * head_ready;
	struct job_s * head_empty;
	void (*func_onSleep_ptr)(void);
	void (*func_onWake_ptr)(void);
	lib_datetime_interval_t lastRunTime;
	struct job_s jobs[DRV_SCHED__MAX_JOBS];
} state;

static void stubFunc(void) {
	return; //do nothing
}

void drv_sched_init(void (*func_onSleep_ptr)(void), void (*func_onWake_ptr)(void)) {
	state.func_onSleep_ptr = (func_onSleep_ptr != NULL) ? func_onSleep_ptr : stubFunc;
	state.func_onWake_ptr = (func_onWake_ptr != NULL) ? func_onWake_ptr : stubFunc;
	state.head_ready = NULL;
	state.head_empty = &(state.jobs[0]);
	state.lastRunTime = 0;
	for (int i=0; i<DRV_SCHED__MAX_JOBS; i++) {
		if (i == DRV_SCHED__MAX_JOBS-1) {
			state.jobs[i].next = NULL;
		} else {
			state.jobs[i].next = &(state.jobs[i+1]);
		}
		state.jobs[i].interval = 0;
		state.jobs[i].time = 0;
		state.jobs[i].func_ptr = stubFunc;
		state.jobs[i].priority = DRV_SCHED_PRI__IDLE;
		state.jobs[i].type = JOB_TYPE__NONE;
	}
}

//TODO: not yet done
static enum drv_sched_err_e schedule(void (*func_ptr)(void), enum job_type_e type, enum drv_sched_pri_e priority, lib_datetime_interval_t delay_or_timeOfDay, lib_datetime_interval_t interval_ms) {
	lib_datetime_interval_t currentTime = drv_timer_getMonotonicTime();
	if (state.head_empty == NULL) return DRV_SCHED_ERR__NO_JOB_SLOTS; //failed to schedule, no job slots remaining
	struct job_s * job = state.head_empty; //get empty job slot
	state.head_empty = job->next; //remove from linked list of empty jobs
	
	job->next = NULL;
	job->interval = interval_ms;
	job->time = currentTime + delay_or_timeOfDay; //more logic needed
	job->func_ptr = func_ptr;
	job->priority = priority;
	job->type = type;
	
	if (state.head_ready == NULL) {
		state.head_ready = job;
		state.lastRunTime = currentTime;
	} else {
		struct job_s * insertJobPtr = state.head_ready;
		//while (insertJobPtr->time >= state.lastRunTime) insertJobPtr = insertJobPtr->next;
		while (insertJobPtr->next != NULL && insertJobPtr->next->time < job->time) insertJobPtr = insertJobPtr->next;
		job->next = insertJobPtr->next;
		insertJobPtr->next = job;
	}
	return 0;
}

//schedule once after specified delay
enum drv_sched_err_e drv_sched_once(void (*func_ptr)(void), enum drv_sched_pri_e priority, lib_datetime_interval_t delay_ms) {
	return schedule(func_ptr, JOB_TYPE__ONCE, priority, delay_ms, 0);
}

//schedule after specified delay, repeating at regular intervals afterward
enum drv_sched_err_e drv_sched_repeating(void (*func_ptr)(void), enum drv_sched_pri_e priority, lib_datetime_interval_t delay_ms, lib_datetime_interval_t interval_ms) {
	return schedule(func_ptr, JOB_TYPE__REPEAT, priority, delay_ms, interval_ms);
}

//schedule at particular time of day
enum drv_sched_err_e drv_sched_once_at(void (*func_ptr)(void), enum drv_sched_pri_e priority, lib_datetime_time_t time) {
	if (!drv_timer_absoluteTimeIsAvailable()) return DRV_SCHED_ERR__ABSOLUTE_SCHED_TMP_UNAVAILABLE;
	if (lib_datetime_validateTime(time) != LIB_DATETIME_ERR__NONE) return DRV_SCHED_ERR__INVALID_TIME;
	return schedule(func_ptr, JOB_TYPE__ONCE_AT, priority, (lib_datetime_interval_t) time, 0);
}

//schedule at particular time of day, repeating at regular intervals afterward
enum drv_sched_err_e drv_sched_repeating_at(void (*func_ptr)(void), enum drv_sched_pri_e priority, lib_datetime_time_t time, lib_datetime_interval_t interval_ms) {
	if (!drv_timer_absoluteTimeIsAvailable()) return DRV_SCHED_ERR__ABSOLUTE_SCHED_TMP_UNAVAILABLE;
	if (lib_datetime_validateTime(time) != LIB_DATETIME_ERR__NONE) return DRV_SCHED_ERR__INVALID_TIME;
	return schedule(func_ptr, JOB_TYPE__REPEAT_AT, priority, (lib_datetime_interval_t) time, interval_ms);
}

/*
Will attempt to sleep for as long as possible, only waking for scheduled jobs
*/
/*
#ifdef __GNUC__
__attribute__((noreturn))
#endif
*/
void drv_sched_start(void) {
	while (1) {
		struct job_s * job = state.head_ready; //check if NULL
		state.head_ready = job->next;
		job->next = NULL;
		
		(*(job->func_ptr))();
		
		struct job_s * insertJobPtr = state.head_empty;
		while (insertJobPtr->next != NULL) insertJobPtr = insertJobPtr->next;
		insertJobPtr->next = job;
		
		delay(job->interval);
		
		schedule(job->func_ptr, job->type, job->priority, job->time, job->interval);
		//sleep
	}
}