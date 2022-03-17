#include "../../hardware/hardware.h"

#if !defined(HW_GPS) || !defined(HW_LORA)
	#warning "HW_GPS and/or HW_LORA is undefined. Linking to drv_mesh.c will fail."
#else

/*
#if defined __has_attribute
	#if !(__has_attribute(packed))
		#error "'__attribute__((packed))' is unavailable."
	#endif
	#if !(__has_attribute(aligned))
		#error "'__attribute__((aligned))' is unavailable."
	#endif
#else
	#error "'__has_attribute()' is unavailable."
#endif
*/

#include "../../hal/hal.h"
#include "../gps/drv_gps.h"
#include "../lora/drv_lora.h"
#include "../sched/drv_sched.h"
#include "../timer/drv_timer.h"
#include "../../lib/misc/lib_misc.h"
#include "../../lib/datetime/lib_datetime.h"
#include "drv_mesh.h"
#include "drv_mesh_private.h"

#include "../../lib/monocypher/monocypher.h"

#define XXH_NO_STREAM
#define XXH_NO_LONG_LONG
#define XXH_CPU_LITTLE_ENDIAN
#define XXH_NO_STDLIB
#define XXH_NO_INLINE_HINTS
#define XXH_FORCE_ALIGN_CHECK
#include "../../lib/xxhash/xxhash.h"

#define PEER_COUNT_MAX 16
#define BUFFER_RELAY_SIZE 10
#define BUFFER_INBOUND_SIZE 3
#define BUFFER_OUTBOUND_SIZE 3
#define BUFFER_APPOINTMENTS_SIZE 16

#define FREQ_500kHz 500000
#define FREQ_250kHz 250000
#define FREQ_125kHz 125000
#define FREQ_62_5kHz 62500

#define LORA_US_FREQ 902000000
#define LORA_US_FREQ_MIN LORA_US_FREQ
#define LORA_US_FREQ_MAX 928000000
#define LORA_US_FREQ_WIDTH (LORA_US_FREQ_MAX - LORA_US_FREQ_MIN)
#define LORA_US_CHANNELCOUNT_500kHz 32
#define LORA_US_CHANNELCOUNT_250kHz 64
#define LORA_US_CHANNELCOUNT_125kHz 128
#define LORA_US_CHANNELCOUNT_62_5kHz 256
#define LORA_US_PADDING_500kHz ((uint64_t)(((LORA_US_FREQ_WIDTH - (LORA_US_CHANNELCOUNT_500kHz * FREQ_500kHz)) / LORA_US_CHANNELCOUNT_500kHz) / 2))
#define LORA_US_PADDING_250kHz ((uint64_t)(((LORA_US_FREQ_WIDTH - (LORA_US_CHANNELCOUNT_250kHz * FREQ_250kHz)) / LORA_US_CHANNELCOUNT_250kHz) / 2))
#define LORA_US_PADDING_125kHz ((uint64_t)(((LORA_US_FREQ_WIDTH - (LORA_US_CHANNELCOUNT_125kHz * FREQ_125kHz)) / LORA_US_CHANNELCOUNT_125kHz) / 2))
#define LORA_US_PADDING_62_5kHz ((uint64_t)(((LORA_US_FREQ_WIDTH - (LORA_US_CHANNELCOUNT_62_5kHz * FREQ_62_5kHz)) / LORA_US_CHANNELCOUNT_62_5kHz) / 2))

#include <stdint.h>
#define RB_CAPACITY(rb) ((uint16_t)(sizeof(rb.buf)/sizeof(__typeof__(rb.buf[0]))))
#define RB_COUNT(rb) ((uint16_t)rb.count)
#define RB_GET(rb) ((__typeof__(rb.buf[0]) *)(\
    (rb.count == 0) ? NULL : \
        (rb.tail = ((rb.tail+1)%RB_CAPACITY(rb)),\
        rb.count--,\
        &(rb.buf[(rb.tail == 0) ? RB_CAPACITY(rb)-1 : rb.tail-1]))\
))
#define RB_PEEK(rb) ((__typeof__(rb.buf[0]) *)(\
    (rb.count == 0) ? NULL : \
        &(rb.buf[rb.tail])\
))
#define RB_PUT(rb) ((__typeof__(rb.buf[0]) *)(\
    (rb.count == RB_CAPACITY(rb)) ? NULL : \
        (rb.head = ((rb.head+1)%RB_CAPACITY(rb)),\
        rb.count++,\
        &(rb.buf[(rb.head == 0) ? RB_CAPACITY(rb)-1 : rb.head-1]))\
))

#define DEBUG_PRINT_FUNCTION() {char tbuf[256]; sprintf(tbuf, "%s()\n",__func__); hal_serial_write(hal_serial0, tbuf, strlen(tbuf)+1);}

#define DEBUG_PRINT(...) {char tbuf[256]; sprintf(tbuf, __VA_ARGS__); hal_serial_write(hal_serial0, tbuf, strlen(tbuf)+1);}

#define DEBUG_PRINT_TIMESTAMP() {char tbuf[256]; sprintf(tbuf, "[%lu] ", drv_timer_getMonotonicTime()); hal_serial_write(hal_serial0, tbuf, strlen(tbuf)+1);}

static struct state_s {
	ip_t ip;
	struct peer_s peers[PEER_COUNT_MAX];
	
	struct {
		uint8_t head;
		uint8_t tail;
		uint16_t count;
		struct packet_ext_s buf[BUFFER_RELAY_SIZE];
	} rb_relay;
	
	struct {
		uint8_t head;
		uint8_t tail;
		uint16_t count;
		struct packet_ext_s buf[BUFFER_INBOUND_SIZE];
	} rb_inbound;
	
	struct {
		uint8_t head;
		uint8_t tail;
		uint16_t count;
		struct packet_ext_s buf[BUFFER_OUTBOUND_SIZE];
	} rb_outbound;

	struct appointment_s * head_appt_empty;
	struct appointment_s appointments[BUFFER_APPOINTMENTS_SIZE];
	
	struct drv_lora_s radio;
} state;

static struct appointment_s * popEmptyAppt(void) {
	struct appointment_s * appt = state.head_appt_empty;
	if (appt != NULL) {
		state.head_appt_empty = appt->next;
	}
	appt->next = NULL;
	return appt;
}

static void insertEmptyAppt(struct appointment_s * appt) {
	appt->next = state.head_appt_empty;
	state.head_appt_empty = appt;
}

//TODO: only works in US, no error handling
static uint64_t getCenterFrequency(channel_t channel, enum drv_lora_bandwidth_e bandwidth) {
	if (bandwidth == DRV_LORA_BW__500kHz) return LORA_US_FREQ_MIN + LORA_US_PADDING_500kHz + (channel * FREQ_500kHz) + (channel * LORA_US_PADDING_500kHz) + (FREQ_500kHz / 2);
	if (bandwidth == DRV_LORA_BW__250kHz) return LORA_US_FREQ_MIN + LORA_US_PADDING_250kHz + (channel * FREQ_250kHz) + (channel * LORA_US_PADDING_250kHz) + (FREQ_250kHz / 2);
	if (bandwidth == DRV_LORA_BW__125kHz) return LORA_US_FREQ_MIN + LORA_US_PADDING_125kHz + (channel * FREQ_125kHz) + (channel * LORA_US_PADDING_125kHz) + (FREQ_125kHz / 2);
	if (bandwidth == DRV_LORA_BW__62_5kHz) return LORA_US_FREQ_MIN + LORA_US_PADDING_62_5kHz + (channel * FREQ_62_5kHz) + (channel * LORA_US_PADDING_62_5kHz) + (FREQ_62_5kHz / 2);
	return 0;
}

/*
 *  Global discovery channel - determined by time
 *  Private discovery channel - determined by time and private key
 *  Peer-specific discovery channel - determined by discovery broadcast, DISC contains list of settings that peer will listen on
 *  Peer receive channel(s) - determined by time and UID. A node tells each of it's peers when it can be reached. It does not need to tell all of them the same time.
 */
/*
static void getChannelConfiguration(struct channel_settings_s * settings, struct lib_datetime_s dt, uid_t uid) {
	
	lib_datetime_realtime_t realtime = 0;
	dt.sec = 0;
	dt.ms = 0;
	lib_datetime_convertDatetimeToRealtime(&dt, &realtime); //TODO: error handling
	realtime = lib_misc_mix64(realtime);
	
	
	
	
	return 0;
}
*/

static struct appointment_s * getNextGlobalDiscoveryChannelAppointment(void) {
	DEBUG_PRINT_TIMESTAMP(); DEBUG_PRINT_FUNCTION();
	struct appointment_s * appt = popEmptyAppt();
	if (appt == NULL) return NULL;
	struct lib_datetime_s dt;
	drv_timer_getAbsoluteDateTime(&dt); //safe to ignore error
	//DEBUG_PRINT("pre:\nmin:%u\nsec:%u\nms:%u\n",dt.min,dt.sec,dt.ms);
	dt.sec = (dt.sec / 15) * 15;
	if (dt.sec == 45) {
		lib_datetime_addIntervalToDatetime(&dt, 1000*60);
		dt.sec = 0;
	} else {
		dt.sec += 15;
	}
	dt.ms = 0;
	
	lib_datetime_realtime_t rt;
	lib_datetime_convertDatetimeToRealtime(&dt, &rt);
	
	uint32_t tmp = lib_misc_fastrange32(lib_misc_XORshiftLFSR32((uint32_t)lib_misc_mix64(rt)), 15*1000);
	appt->realtime = rt + tmp;
	appt->type = APPT_DISC_SEND;
	appt->peer = NULL;
	appt->channel = 0;
	appt->bandwidth = DRV_LORA_BW__125kHz;
	appt->spreadingFactor = DRV_LORA_SF__9;
	appt->codingRate = DRV_LORA_CR__4_6;
	
	DEBUG_PRINT("tmp:%u\n", tmp); 
	//DEBUG_PRINT("post:\nmin:%u\nsec:%u\nms:%u\n",dt.min,dt.sec,dt.ms);
	//DEBUG_PRINT("year:%u\nmonth:%u\nday:%u\nhour:%u\nmin:%u\nsec:%u\nms:%u\n",dt.year,dt.month,dt.day,dt.hour,dt.min,dt.sec,dt.ms);
	return appt;
}

/*static struct appointment_s * getNextPrivateDiscoveryChannelAppointment(void) {
	struct appointment_s * appt = popEmptyAppt();
	struct datetime_s dt; drv_timer_getAbsoluteDateTime(&dt); //safe to ignore error
	dt.min++;
	dt.sec = 0;
	dt.ms = 0;

	return appt;
}*/

static void drv_mesh_worker_disc_send(void * arg) {
	DEBUG_PRINT_TIMESTAMP(); DEBUG_PRINT_FUNCTION();
	struct appointment_s * appt = (struct appointment_s *) arg;
	insertEmptyAppt(appt);
}

static void drv_mesh_worker_disc_recv(void * arg) {
	DEBUG_PRINT_TIMESTAMP(); DEBUG_PRINT_FUNCTION();
	struct appointment_s * appt = (struct appointment_s *) arg;
	insertEmptyAppt(appt);
}

static void drv_mesh_worker_data_send(void * arg) {
	DEBUG_PRINT_TIMESTAMP(); DEBUG_PRINT_FUNCTION();
	struct appointment_s * appt = (struct appointment_s *) arg;
	insertEmptyAppt(appt);
}

static void drv_mesh_worker_data_recv(void * arg) {
	DEBUG_PRINT_TIMESTAMP(); DEBUG_PRINT_FUNCTION();
	struct appointment_s * appt = (struct appointment_s *) arg;
	insertEmptyAppt(appt);
}

static void drv_mesh_worker_scheduler(void * arg) {
	DEBUG_PRINT_TIMESTAMP(); DEBUG_PRINT_FUNCTION();
	struct appointment_s * appt = getNextGlobalDiscoveryChannelAppointment();
	if (appt == NULL) return;
	if (appt->type = APPT_DISC_SEND) {
		enum drv_sched_err_e err = drv_sched_once_at(drv_mesh_worker_disc_send, (void*)appt, DRV_SCHED_PRI__REALTIME, appt->realtime);
	} else if (appt->type = APPT_DISC_RECV) {
		enum drv_sched_err_e err = drv_sched_once_at(drv_mesh_worker_disc_recv, (void*)appt, DRV_SCHED_PRI__REALTIME, appt->realtime);
	} else if (appt->type = APPT_DATA_SEND) {
		enum drv_sched_err_e err = drv_sched_once_at(drv_mesh_worker_data_send, (void*)appt, DRV_SCHED_PRI__REALTIME, appt->realtime);
	} else if (appt->type = APPT_DATA_RECV) {
		enum drv_sched_err_e err = drv_sched_once_at(drv_mesh_worker_data_recv, (void*)appt, DRV_SCHED_PRI__REALTIME, appt->realtime);
	}
}

//runs once absolute scheduling is available
static void drv_mesh_start(void * arg __attribute__((unused))) {
	DEBUG_PRINT_TIMESTAMP(); DEBUG_PRINT_FUNCTION();

	//drv_sched_once_at(drv_mesh_worker_disc_listener, appt, DRV_SCHED_PRI__REALTIME, lib_datetime_convertRealtimeToTime(appt->realtime));
	struct lib_datetime_s dt;
	drv_timer_getAbsoluteDateTime(&dt); //safe to ignore error
	dt.sec = (dt.sec / 15) * 15;
	dt.ms = 0;
	lib_datetime_realtime_t rt;
	//drv_timer_getRealtime(&rt);
	lib_datetime_convertDatetimeToRealtime(&dt, &rt);
	//enum drv_sched_err_e err = drv_sched_once_at(drv_mesh_worker_disc_listener, NULL, DRV_SCHED_PRI__REALTIME, rt+1000);
	enum drv_sched_err_e err = drv_sched_repeating_at(drv_mesh_worker_scheduler, NULL, DRV_SCHED_PRI__REALTIME, rt+14000, 1000*15); //run 1 second before each 15 second block
}

void drv_mesh_init(void (*func_onRecv_ptr)(struct drv_mesh_packet_s *)) {
	DEBUG_PRINT_TIMESTAMP(); DEBUG_PRINT_FUNCTION();
	//initialize datastructures
	state.head_appt_empty = &(state.appointments[0]);
	for (int i=0; i<BUFFER_APPOINTMENTS_SIZE; i++) {
		if (i == BUFFER_APPOINTMENTS_SIZE-1) {
			state.appointments[i].next = NULL;
		} else {
			state.appointments[i].next = &(state.appointments[i+1]);
		}
	}
	//initialize scheduler
	drv_sched_init();
	drv_sched_onAbsoluteAvailable(drv_mesh_start, NULL);
	//initialize GPS 
	drv_gps_init(NULL);
	//configure GPS for timekeeping mode as appropriate
	
	//initialize LoRa radio
	//drv_lora_init(&state.radio, DRV_LORA_REGION_US915, 0);
	//configure LoRa radio
	
	
}

enum drv_mesh_error_e drv_mesh_send(struct drv_mesh_packet_s * packet) {
	return 0;
}

#endif