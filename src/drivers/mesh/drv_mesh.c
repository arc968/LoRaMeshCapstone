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

static struct state_s {
	ip_t ip;
	struct peer_s peers[PEER_COUNT_MAX];
	
	uint8_t buf_relay_head;
	uint8_t buf_relay_tail;
	struct packet_ext_s buf_relay[BUFFER_RELAY_SIZE];
	
	uint8_t buf_inbound_head;
	uint8_t buf_inbound_tail;
	struct packet_ext_s buf_inbound[BUFFER_INBOUND_SIZE];
	
	uint8_t buf_outbound_head;
	uint8_t buf_outbound_tail;
	struct packet_ext_s buf_outbound[BUFFER_OUTBOUND_SIZE];

	struct appointment_s appointments[BUFFER_APPOINTMENTS_SIZE];
} state;

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

static struct appointment_s * getNextDiscoveryChannelAppointment(void) {
	return NULL;
}

static void drv_mesh_worker_disc_listener(void * arg) {
	
}

static void drv_mesh_worker_disc_broadcaster(void * arg) {
	
}

static void drv_mesh_worker_data_recv(void * arg) {
	
}

static void drv_mesh_worker_data_send(void * arg) {
	
}

//runs once absolute scheduling is available
static void drv_mesh_start(void * arg __attribute__((unused))) {
	struct appointment_s * appt = getNextDiscoveryChannelAppointment();
	drv_sched_once_at(drv_mesh_worker_disc_listener, appt, DRV_SCHED_PRI__REALTIME, lib_datetime_convertRealtimeToTime(appt->realtime));
}

void drv_mesh_init(void (*func_onRecv_ptr)(struct drv_mesh_packet_s *)) {
	//initialize datastructures
	
	//initialize GPS
	
	//configure GPS for timekeeping mode as appropriate
	
	//initialize LoRa radio
	
	//configure LoRa radio
	
	drv_sched_onAbsoluteAvailable(drv_mesh_start, NULL);
}

enum drv_mesh_error_e drv_mesh_send(struct drv_mesh_packet_s * packet) {
	return 0;
}

#endif