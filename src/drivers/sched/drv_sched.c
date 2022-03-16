#include "../../hal/hal.h"
#include "drv_sched.h"

#include <stdbool.h>
#include <stdio.h>
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
	void (*func_ptr)(void*);
	void * func_arg;
	enum drv_sched_pri_e priority;
	enum job_type_e type;
};

struct state_s {
	struct job_s * head_ready;
	struct job_s * head_timed;
	struct job_s * head_later;
	struct job_s * head_empty;
	struct job_s * head_onAbsoluteAvailable;
	void (*func_onSleep_ptr)(void);
	void (*func_onWake_ptr)(void);
	lib_datetime_time_t lastRunTime;
	struct job_s jobs[DRV_SCHED__MAX_JOBS];
} state;

static volatile bool initialized = false;

static void worker_onAbsoluteAvailable(void);
void drv_sched_init(void) {
	if (!initialized) {
		drv_timer_init();
		state.func_onSleep_ptr = NULL;
		state.func_onWake_ptr = NULL;
		state.head_ready = NULL;
		state.head_timed = NULL;
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
			state.jobs[i].func_ptr = NULL;
			state.jobs[i].priority = DRV_SCHED_PRI__IDLE;
			state.jobs[i].type = JOB_TYPE__NONE;
		}
		drv_timer_setCallbackOnAbsoluteTimeAvailable(worker_onAbsoluteAvailable);
		initialized = true;
	}
}

void drv_sched_setOnSleepCallback(void (*func_onSleep_ptr)(void)) {
	state.func_onSleep_ptr = func_onSleep_ptr;
}

void drv_sched_setOnWakeCallback(void (*func_onWake_ptr)(void)) {
	state.func_onWake_ptr = func_onWake_ptr;
}

static struct job_s * popEmptyJob(void) {
	struct job_s * job = state.head_empty; //get empty job slot
	if (job != NULL) {
		state.head_empty = job->next; //remove from linked list of empty jobs
	}
	return job;
}

static void insertEmptyJob(struct job_s * job) {
	job->next = state.head_empty;
	state.head_empty = job;
}

static void insertLaterJob(struct job_s * job) {
	job->next = state.head_later;
	state.head_later = job;
}

static void insertOnAbsoluteAvailableJob(struct job_s * job) {
	job->next = state.head_onAbsoluteAvailable;
	state.head_onAbsoluteAvailable = job;
}

static void insertNormalJob(struct job_s * job) {
	if (state.head_ready == NULL) {
		state.head_ready = job;
	} else {
		if (state.head_ready->time >= job->time) {
			job->next = state.head_ready;
			state.head_ready = job;
		} else {
			struct job_s * insertJobPtr = state.head_ready;
			while (insertJobPtr->next != NULL && insertJobPtr->next->time < job->time) insertJobPtr = insertJobPtr->next;
			job->next = insertJobPtr->next;
			insertJobPtr->next = job;
		}
	}
}

static void insertTimedJob(struct job_s * job) {
	if (state.head_timed == NULL) {
		state.head_timed = job;
	} else {
		if (state.head_timed->time >= job->time) {
			job->next = state.head_timed;
			state.head_timed = job;
		} else {
			struct job_s * insertJobPtr = state.head_timed;
			while (insertJobPtr->next != NULL && insertJobPtr->next->time < job->time) insertJobPtr = insertJobPtr->next;
			job->next = insertJobPtr->next;
			insertJobPtr->next = job;
		}
	}
}

static void worker_onAbsoluteAvailable(void) {
	struct job_s * job = state.head_onAbsoluteAvailable;
	while (job != NULL) {
		state.head_onAbsoluteAvailable = job->next;
		job->next = NULL;
		if (job->func_ptr != NULL) (*(job->func_ptr))(job->func_arg); //run job
		insertEmptyJob(job);
	}
}

//TODO: not yet done
static enum drv_sched_err_e schedule(void (*func_ptr)(void*), void * func_arg, enum job_type_e type, enum drv_sched_pri_e priority, lib_datetime_interval_t delay_or_timeOfDay, lib_datetime_interval_t interval_ms) {
	bool interruptsEnabled = hal_interrupt_isEnabled();
	hal_interrupt_disable();
	
	lib_datetime_interval_t currentTime = drv_timer_getMonotonicTime();
	lib_datetime_time_t curTime; drv_timer_getAbsoluteTime(&curTime);
	struct job_s * job = popEmptyJob();
	if (job == NULL) {
		if (interruptsEnabled) hal_interrupt_enable();
		return DRV_SCHED_ERR__NO_JOB_SLOTS; //failed to schedule, no job slots remaining
	}
	
	job->next = NULL;
	job->interval = interval_ms;
	job->func_ptr = func_ptr;
	job->func_arg = func_arg;
	job->priority = priority;
	job->type = type;
	
	if (type == JOB_TYPE__ONCE || type == JOB_TYPE__REPEAT) {
		job->time = currentTime + delay_or_timeOfDay;
		insertNormalJob(job);
	} else if (type == JOB_TYPE__ONCE_AT || type == JOB_TYPE__REPEAT_AT) {
		job->time = delay_or_timeOfDay;
		
		if (curTime < job->time) {
			insertTimedJob(job);
		} else {
			insertLaterJob(job);
		}
	} else {
		//shouldn't be possible
	}
	
	if (interruptsEnabled) hal_interrupt_enable();
	
	return DRV_SCHED_ERR__NONE;
}

//schedule once after specified delay
enum drv_sched_err_e drv_sched_once(void (*func_ptr)(void*), void * func_arg, enum drv_sched_pri_e priority, lib_datetime_interval_t delay_ms) {
	return schedule(func_ptr, func_arg, JOB_TYPE__ONCE, priority, delay_ms, 0);
}

//schedule after specified delay, repeating at regular intervals afterward
enum drv_sched_err_e drv_sched_repeating(void (*func_ptr)(void*), void * func_arg, enum drv_sched_pri_e priority, lib_datetime_interval_t delay_ms, lib_datetime_interval_t interval_ms) {
	return schedule(func_ptr, func_arg, JOB_TYPE__REPEAT, priority, delay_ms, interval_ms);
}

//schedule at particular time of day
enum drv_sched_err_e drv_sched_once_at(void (*func_ptr)(void*), void * func_arg, enum drv_sched_pri_e priority, lib_datetime_time_t time) {
	if (!drv_timer_absoluteTimeIsAvailable()) return DRV_SCHED_ERR__ABSOLUTE_SCHED_TMP_UNAVAILABLE;
	if (lib_datetime_validateTime(time) != LIB_DATETIME_ERR__NONE) return DRV_SCHED_ERR__INVALID_TIME;
	return schedule(func_ptr, func_arg, JOB_TYPE__ONCE_AT, priority, (lib_datetime_interval_t) time, 0);
}

//schedule at particular time of day, repeating at regular intervals afterward
enum drv_sched_err_e drv_sched_repeating_at(void (*func_ptr)(void*), void * func_arg, enum drv_sched_pri_e priority, lib_datetime_time_t time, lib_datetime_interval_t interval_ms) {
	if (!drv_timer_absoluteTimeIsAvailable()) return DRV_SCHED_ERR__ABSOLUTE_SCHED_TMP_UNAVAILABLE;
	if (lib_datetime_validateTime(time) != LIB_DATETIME_ERR__NONE) return DRV_SCHED_ERR__INVALID_TIME;
	return schedule(func_ptr, func_arg, JOB_TYPE__REPEAT_AT, priority, (lib_datetime_interval_t) time, interval_ms);
}

enum drv_sched_err_e drv_sched_onAbsoluteAvailable(void (*func_ptr)(void*), void * func_arg) {
	bool interruptsEnabled = hal_interrupt_isEnabled();
	hal_interrupt_disable();
	struct job_s * job = popEmptyJob();
	if (job == NULL) {
		if (interruptsEnabled) hal_interrupt_enable();
		return DRV_SCHED_ERR__NO_JOB_SLOTS;
	}
	job->func_ptr = func_ptr;
	job->func_arg = func_arg;
	job->type = JOB_TYPE__ONCE;
	insertOnAbsoluteAvailableJob(job);
	if (interruptsEnabled) hal_interrupt_enable();
	return DRV_SCHED_ERR__NONE;
}

static enum power_state_e {
	STATE_AWAKE,
	STATE_SLEEP,
} powerState = STATE_AWAKE;


static uint16_t num = 0;
/*
Will attempt to sleep for as long as possible, only waking for scheduled jobs
*/
#ifdef __GNUC__
__attribute__((noreturn))
#endif
void drv_sched_start(void) { //TODO: needs work. It is ugly and doesn't handle edge cases well, such as GPS time going back slightly. Also priority does nothing.
	while (1) {
		{ //schedule relative jobs
			bool interruptsEnabled = hal_interrupt_isEnabled();
			hal_interrupt_disable();
			lib_datetime_interval_t curTime = drv_timer_getMonotonicTime();
			struct job_s * job = state.head_ready;
			if (job != NULL && job->time <= curTime) {
				state.head_ready = job->next;
				job->next = NULL;
				
				if (job->func_ptr != NULL) {
					if (interruptsEnabled) hal_interrupt_enable();
					(*(job->func_ptr))(job->func_arg); //run job
					hal_interrupt_disable();
				}
				
				if (job->type == JOB_TYPE__ONCE) {
					insertEmptyJob(job);
				} else if (job->type == JOB_TYPE__REPEAT) {
					job->time += job->interval;
					insertNormalJob(job);
				} else {
					//shouldn't get here
					insertEmptyJob(job);
				}
			}
			if (interruptsEnabled) hal_interrupt_enable();
		}
		
		{ //schedule absolute jobs
			bool interruptsEnabled = hal_interrupt_isEnabled();
			hal_interrupt_disable();
			lib_datetime_time_t curTime;
			if (drv_timer_getAbsoluteTime(&curTime) == DRV_TIMER_ERR__NONE) { //if absolute time is available
				if (curTime < state.lastRunTime) { //time rollover (new day), handle accordingly
					struct job_s * old_later = state.head_later;
					state.head_later = NULL;
					//flush timed jobs
					{
						struct job_s * job = state.head_timed;
						while (job != NULL) {
							state.head_timed = job->next;
							job->next = NULL;
							
							if (job->time >= state.lastRunTime) { //if job was missed at end of day
								if (job->func_ptr != NULL) {
									if (interruptsEnabled) hal_interrupt_enable();
									(*(job->func_ptr))(job->func_arg); //run job
									hal_interrupt_disable();
								}
								
								if (job->type == JOB_TYPE__ONCE_AT) {
									insertEmptyJob(job);
								} else if (job->type == JOB_TYPE__REPEAT_AT) {
									insertLaterJob(job);
								} else {
									//shouldn't get here
								}
							} else { //probably won't happen because this is duplicate logic from schedule()
								insertLaterJob(job);
							}
						}
					}
					
					//queue all "later" jobs
					while (state.head_later != NULL) {
						struct job_s * job = old_later; //get empty job slot
						old_later = job->next; //remove from linked list of empty jobs
						job->next = NULL;
						insertTimedJob(job);
					}
					state.lastRunTime = curTime;
				}
				
				struct job_s * job = state.head_timed;
				if (job != NULL && job->time <= curTime) { //normal operation
					state.head_timed = job->next;
					job->next = NULL;
					
					if (job->func_ptr != NULL) {
						if (interruptsEnabled) hal_interrupt_enable();
						(*(job->func_ptr))(job->func_arg); //run job
						hal_interrupt_disable();
					}
					
					if (job->type == JOB_TYPE__ONCE_AT) {
						insertEmptyJob(job);
					} else if (job->type == JOB_TYPE__REPEAT_AT) {
						insertLaterJob(job);
					} else {
						//shouldn't get here
					}
					state.lastRunTime = curTime;
				}
			}
			if (interruptsEnabled) hal_interrupt_enable();
		}
		hal_power_setMode(PWR_IDLE, NULL);
		/*
		#define TIME_SLEEP 1500
		#define TIME_IDLE 1
		char abuf[256];
		sprintf(abuf, "t");
		hal_serial_write(hal_serial0, abuf, strlen(abuf)+1);
		hal_serial_flush(hal_serial0);
		{ //power //TODO manage powerState
		char tbuf[256];
			struct lib_datetime_s dt = {0};
			lib_datetime_interval_t curMonoTime = drv_timer_getMonotonicTime();
			if (state.head_ready != NULL) {
				lib_datetime_interval_t timeUntilMono = state.head_ready->time - curMonoTime;
				if (timeUntilMono > TIME_SLEEP) {
					lib_datetime_time_t curAbsoluteTime;
					if (drv_timer_getAbsoluteTime(&curAbsoluteTime) == DRV_TIMER_ERR__NONE && state.head_timed != NULL) {
						lib_datetime_interval_t timeUntilAbsolute = state.head_timed->time - curAbsoluteTime;
						if (timeUntilAbsolute > TIME_SLEEP) {
							//SLEEP
							dt.sec = (timeUntilAbsolute < timeUntilMono) ? timeUntilAbsolute/1000 : timeUntilMono/1000;
							if (state.func_onSleep_ptr != NULL) (*(state.func_onSleep_ptr))();
							sprintf(tbuf, "s1\n");
							hal_serial_write(hal_serial0, tbuf, strlen(tbuf)+1);
							hal_serial_flush(hal_serial0);
							//hal_power_setMode(PWR_SLEEP, &dt);
							if (state.func_onWake_ptr != NULL) (*(state.func_onWake_ptr))();
						}
					} else {
						//SLEEP
						dt.sec = timeUntilMono/1000;
						if (state.func_onSleep_ptr != NULL) (*(state.func_onSleep_ptr))();
						sprintf(tbuf, "s2\n");
						hal_serial_write(hal_serial0, tbuf, strlen(tbuf)+1);
						hal_serial_flush(hal_serial0);
						//hal_power_setMode(PWR_SLEEP, &dt);
						if (state.func_onWake_ptr != NULL) (*(state.func_onWake_ptr))();
					}
				} else if (timeUntilMono > TIME_IDLE) {
					lib_datetime_time_t curAbsoluteTime;
					if (drv_timer_getAbsoluteTime(&curAbsoluteTime) == DRV_TIMER_ERR__NONE && state.head_timed != NULL) {
						lib_datetime_interval_t timeUntilAbsolute = state.head_timed->time - curAbsoluteTime;
						if (timeUntilAbsolute > TIME_IDLE) {
							//IDLE
							sprintf(tbuf, "i1\n");
							hal_serial_write(hal_serial0, tbuf, strlen(tbuf)+1);
							hal_serial_flush(hal_serial0);
							hal_power_setMode(PWR_IDLE, NULL);
						}
					} else {
						//IDLE
						sprintf(tbuf, "i2\n");
						hal_serial_write(hal_serial0, tbuf, strlen(tbuf)+1);
						hal_serial_flush(hal_serial0);
						hal_power_setMode(PWR_IDLE, NULL);
					}
				}
			} else {
				lib_datetime_time_t curAbsoluteTime;
				if (drv_timer_getAbsoluteTime(&curAbsoluteTime) == DRV_TIMER_ERR__NONE && state.head_timed != NULL) {
					lib_datetime_interval_t timeUntilAbsolute = state.head_timed->time - curAbsoluteTime;
					if (timeUntilAbsolute > TIME_SLEEP) {
						//SLEEP
						dt.sec = timeUntilAbsolute/1000;
						if (state.func_onSleep_ptr != NULL) (*(state.func_onSleep_ptr))();
						sprintf(tbuf, "s3\n");
						hal_serial_write(hal_serial0, tbuf, strlen(tbuf)+1);
						hal_serial_flush(hal_serial0);
						//hal_power_setMode(PWR_SLEEP, &dt);
						if (state.func_onWake_ptr != NULL) (*(state.func_onWake_ptr))();
					} else if (timeUntilAbsolute > TIME_IDLE) {
						//IDLE
						sprintf(tbuf, "i3\n");
						hal_serial_write(hal_serial0, tbuf, strlen(tbuf)+1);
						hal_serial_flush(hal_serial0);
						hal_power_setMode(PWR_IDLE, NULL);
					}
				} else {
					//SLEEP
					dt.year = 3000;
					if (state.func_onSleep_ptr != NULL) (*(state.func_onSleep_ptr))();
					sprintf(tbuf, "s4\n");
					hal_serial_write(hal_serial0, tbuf, strlen(tbuf)+1);
					hal_serial_flush(hal_serial0);
					//hal_power_setMode(PWR_SLEEP, &dt);
					if (state.func_onWake_ptr != NULL) (*(state.func_onWake_ptr))();
				}
			}
		}
		*/
	}
}