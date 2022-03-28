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

#include <stdint.h>
#include <stdbool.h>

#include "../../hal/hal.h"
#include "../gps/drv_gps.h"
#include "../lora/drv_lora.h"
#include "../sched/drv_sched.h"
#include "../timer/drv_timer.h"
#include "../rand/drv_rand.h"
#include "../../lib/misc/lib_misc.h"
#include "../../lib/ip/lib_ip.h"
#include "../../lib/datetime/lib_datetime.h"
#include "../../lib/byteorder/lib_byteorder.h"

#include "../../lib/monocypher/monocypher.h"

#define XXH_NO_STREAM
#define XXH_NO_LONG_LONG
#define XXH_CPU_LITTLE_ENDIAN
#define XXH_NO_STDLIB
#define XXH_NO_INLINE_HINTS
#define XXH_FORCE_ALIGN_CHECK
#include "../../lib/xxhash/xxhash.h"

#include "drv_mesh_config.h"
#include "drv_mesh.h"
#include "drv_mesh_private.h"

#include "drv_mesh_send.h"
#include "drv_mesh_recv.h"

//small issue, starts backing off on boot not after initialization
//also needs to change bandwidth based on time, not seed
static struct appointment_s * getNextGlobalDiscoveryChannelAppointment(lib_datetime_realtime_t rt) {
	DEBUG_PRINT_REALTIME(); DEBUG_PRINT_FUNCTION();
	struct appointment_s * appt = popEmptyAppt();
	if (appt == NULL) return NULL;
	
	/*
	struct lib_datetime_s dt;
	drv_timer_getAbsoluteDateTime(&dt); //safe to ignore error
	//DEBUG_PRINT("pre:\nmin:%u\nsec:%u\nms:%u\n",dt.min,dt.sec,dt.ms);
	dt.sec = (dt.sec / 15) * 15;
	dt.ms = 0;
	lib_datetime_realtime_t rt;
	lib_datetime_convertDatetimeToRealtime(&dt, &rt);
	rt += 1000*15;
	*/

	
	//uint32_t short_rt = lib_misc_XORshiftLFSR32((uint32_t)lib_misc_mix64(rt));
	uint32_t tmp = 0;//lib_misc_fastrange32(short_rt, 5*1000); //Will be in first 5 seconds of block
	appt->realtime = rt + tmp;
	lib_datetime_interval_t curTime = drv_timer_getMonotonicTime();
	uint32_t tmp2 = (uint32_t)constrainU64(map(curTime, 0, LIB_DATETIME__MS_IN_DAY/24, 2, 20), 2, 20); // Ends at sending 1/n times
	uint32_t tmp3 = lib_misc_fastrange32(drv_rand_getU32(), tmp2);
	if (tmp3) { //TESTING
		appt->type = APPT_RECV;
	} else {
		appt->type = APPT_SEND_DISC;
	}

	//setApptValsFromSeed(appt, short_rt);
	//appt->radio_cfg.bandwidth = drv_lora_bandwidth_e_arr[lib_misc_fastrange32(short_rt, sizeof(drv_lora_bandwidth_e_arr)/sizeof(drv_lora_bandwidth_e_arr[0]))];
	setRadioCfgAtTimeFromSeed(&(appt->radio_cfg), rt, 0); //0 for global
	
	DEBUG_PRINT("\tbandwidth:%lu, frequency:%llu, spreadingFactor:%lu, codingRate:%lu\n", appt->radio_cfg.bandwidth, appt->radio_cfg.frequency, appt->radio_cfg.spreadingFactor, appt->radio_cfg.codingRate); 
	
	DEBUG_PRINT("\ttmp:%lu, tmp2:%lu, tmp3:%lu\n", tmp, tmp2, tmp3); 
	//DEBUG_PRINT("post:\nmin:%u\nsec:%u\nms:%u\n",dt.min,dt.sec,dt.ms);
	//DEBUG_PRINT("year:%u\nmonth:%u\nday:%u\nhour:%u\nmin:%u\nsec:%u\nms:%u\n",dt.year,dt.month,dt.day,dt.hour,dt.min,dt.sec,dt.ms);
	return appt;
}

static void drv_mesh_worker_scheduler(void * arg) {
	DEBUG_PRINT_REALTIME(); DEBUG_PRINT_FUNCTION();
	
	lib_datetime_realtime_t rt_disc;
	drv_timer_getRealtime(&rt_disc);
	rt_disc = (rt_disc / DISCOVERY_INTERVAL_MILLIS) * DISCOVERY_INTERVAL_MILLIS;
	rt_disc += DISCOVERY_INTERVAL_MILLIS;
	
	{ //schedule global discovery broadcast/receive
		struct appointment_s * appt = getNextGlobalDiscoveryChannelAppointment(rt_disc);
		if (appt == NULL) {
			DEBUG_PRINT_REALTIME(); DEBUG_PRINT("WARNING: Failed to get next global discovery appointment\n");
			return;
		}
		enum drv_sched_err_e err;
		if (appt->type == APPT_RECV) {
			err = drv_sched_once_at(drv_mesh_worker_recv, (void*)appt, DRV_SCHED_PRI__REALTIME, appt->realtime);
		} else {
			err = drv_sched_once_at(drv_mesh_worker_send, (void*)appt, DRV_SCHED_PRI__REALTIME, appt->realtime);
		}
		if (err != DRV_SCHED_ERR__NONE) {
			DEBUG_PRINT_REALTIME(); DEBUG_PRINT("WARNING: Failed to schedule next global discovery appointment\n");
			insertEmptyAppt(appt);
			return;
		}
	}
	
	{ //schedule per-peer sends
		struct peer_s * peer = state.head_peer_ready;
		for (; peer != NULL; peer = peer->next) {
			if ((peer->status != PEER_ACQUAINTANCE) && (peer->status != PEER_FRIEND)) {
				struct appointment_s * appt = popEmptyAppt();
				if (appt == NULL) {
					DEBUG_PRINT_REALTIME(); DEBUG_PRINT("WARNING: Failed to schedule peer send discReply appointment, no empty appointments available\n");
					continue;
				}
				
				uint32_t tmp;
				crypto_blake2b_general((uint8_t *)&tmp, sizeof(tmp), state.psk, sizeof(state.psk), (uint8_t *)&(peer->uid), sizeof(peer->uid)); //doesn't handle byteorder correctly
				tmp = LIB_BYTEORDER_HTON_U32(tmp);
				
				uint32_t offset = lib_misc_fastrange32(tmp, DISCOVERY_INTERVAL_MILLIS - 5000) + 5000;
				appt->realtime = rt_disc + offset;
				appt->type = APPT_SEND_DISC_REPLY;
				appt->peer = peer;
				appt->packet = popEmptyPacket();
				if (appt->packet == NULL) {
					DEBUG_PRINT_REALTIME(); DEBUG_PRINT("WARNING: Failed to schedule peer send discReply appointment, no empty packets available\n");
					insertEmptyAppt(appt);
					continue;
				}
				setRadioCfgAtTimeFromSeed(&(appt->radio_cfg), appt->realtime, tmp);
				
				drv_mesh_buildPacket(appt, appt->packet);
				
				DEBUG_PRINT_REALTIME(); DEBUG_PRINT("INFO: Scheduling discReply send at t+%lu\n", offset);
				
				enum drv_sched_err_e err = drv_sched_once_at(drv_mesh_worker_send, (void*)appt, DRV_SCHED_PRI__REALTIME, appt->realtime);
				if (err != DRV_SCHED_ERR__NONE) {
					DEBUG_PRINT_REALTIME(); DEBUG_PRINT("WARNING: Failed to schedule peer send discReply appointment\n");
					insertEmptyAppt(appt);
					continue;
				}
			} else {
				DEBUG_PRINT_REALTIME(); DEBUG_PRINT("INFO: Skipping discReply for peer [%llX], handshake already complete.\n", peer->uid);
			}
		}
	}
	
	{ //schedule own receive periods
		{ //discovery reply periods
			struct appointment_s * appt = popEmptyAppt();
			if (appt == NULL) {
				DEBUG_PRINT_REALTIME(); DEBUG_PRINT("WARNING: Failed to schedule receive appointment, no empty appointments available\n");
				return;
			}
			
			uint32_t tmp;
			crypto_blake2b_general((uint8_t *)&tmp, sizeof(tmp), state.psk, sizeof(state.psk), (uint8_t *)&(state.uid), sizeof(state.uid)); //doesn't handle byteorder correctly
			tmp = LIB_BYTEORDER_HTON_U32(tmp);
			
			uint32_t offset = lib_misc_fastrange32(tmp, DISCOVERY_INTERVAL_MILLIS - 5000) + 5000;
			appt->realtime = rt_disc + offset;
			appt->type = APPT_RECV;
			appt->peer = NULL;
			appt->packet = NULL;
			setRadioCfgAtTimeFromSeed(&(appt->radio_cfg), appt->realtime, tmp);
			
			DEBUG_PRINT_REALTIME(); DEBUG_PRINT("INFO: Scheduling discReply listen at t+%lu\n", offset);
			
			enum drv_sched_err_e err = drv_sched_once_at(drv_mesh_worker_recv, (void*)appt, DRV_SCHED_PRI__REALTIME, appt->realtime);
			if (err != DRV_SCHED_ERR__NONE) {
				DEBUG_PRINT_REALTIME(); DEBUG_PRINT("WARNING: Failed to schedule receive appointment\n");
				insertEmptyAppt(appt);
				return;
			}
		}
		/*{ //per-peer receive periods
			struct peer_s * peer = state.head_peer_ready;
			for (; peer != NULL; peer = peer->next) {
				struct appointment_s * appt = popEmptyAppt();
				if (appt == NULL) {
					DEBUG_PRINT_REALTIME(); DEBUG_PRINT("WARNING: Failed to schedule peer receive appointment, no empty appointments available\n");
					return;
				}
				
				appt->
				
				enum drv_sched_err_e err = drv_sched_once_at(drv_mesh_worker_recv, (void*)appt, DRV_SCHED_PRI__REALTIME, appt->realtime);
				if (err != DRV_SCHED_ERR__NONE) {
					DEBUG_PRINT_REALTIME(); DEBUG_PRINT("WARNING: Failed to schedule peer receive appointment\n");
					insertEmptyAppt(appt);
					return;
				}
			}
		}*/
	}
}

//runs once absolute scheduling is available
//TODO error handling
static void drv_mesh_start(void * arg __attribute__((unused))) {
	DEBUG_PRINT_REALTIME(); DEBUG_PRINT_FUNCTION();
	//drv_sched_once_at(drv_mesh_worker_disc_listener, appt, DRV_SCHED_PRI__REALTIME, lib_datetime_convertRealtimeToTime(appt->realtime));
	/*
	struct lib_datetime_s dt;
	drv_timer_getAbsoluteDateTime(&dt); //safe to ignore error
	dt.sec = (dt.sec / 15) * 15;
	dt.ms = 0;
	lib_datetime_realtime_t rt;
	//drv_timer_getRealtime(&rt);
	lib_datetime_convertDatetimeToRealtime(&dt, &rt);
	*/
	
	lib_datetime_realtime_t rt;
	drv_timer_getRealtime(&rt);
	rt = (rt / DISCOVERY_INTERVAL_MILLIS) * DISCOVERY_INTERVAL_MILLIS;
	rt += DISCOVERY_INTERVAL_MILLIS;
	
	//enum drv_sched_err_e err = drv_sched_once_at(drv_mesh_worker_disc_listener, NULL, DRV_SCHED_PRI__REALTIME, rt+1000);
	enum drv_sched_err_e err = drv_sched_repeating_at(drv_mesh_worker_scheduler, NULL, DRV_SCHED_PRI__REALTIME, rt-1000, DISCOVERY_INTERVAL_MILLIS);
	if (err != DRV_SCHED_ERR__NONE) { //error checking
		DEBUG_PRINT_REALTIME(); DEBUG_PRINT("WARNING: Failed to schedule drv_mesh_worker_scheduler()\n");
		return;
	}
}

//add runonce guard
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
		
		state.head_peer_empty = &(state.peers[0]);
		for (int i=0; i<BUFFER_PEERS_SIZE; i++) {
			if (i == BUFFER_PEERS_SIZE-1) {
				state.peers[i].next = NULL;
			} else {
				state.peers[i].next = &(state.peers[i+1]);
			}
		}
		
		state.head_packet_empty = &(state.packets[0]);
		for (int i=0; i<BUFFER_PACKETS_SIZE; i++) {
			if (i == BUFFER_PACKETS_SIZE-1) {
				state.packets[i].next = NULL;
			} else {
				state.packets[i].next = &(state.packets[i+1]);
			}
		}
	//initialize scheduler
		drv_sched_init();
		drv_sched_onAbsoluteAvailable(drv_mesh_start, NULL);
	//initialize GPS 
		drv_gps_init(NULL);
	//configure GPS for timekeeping mode as appropriate
	
	//initialize LoRa radio
		drv_lora_init(&state.radio, getCenterFrequency(0, DRV_LORA_BW__125kHz)); //TESTING
	//configure LoRa radio
		drv_lora_setMode(&state.radio, DRV_LORA_MODE__SLEEP);
	//seed RNG
		DEBUG_PRINT_TIMESTAMP(); DEBUG_PRINT("SEEDING RNG...\n");
		drv_rand_seedFromLoRa(&state.radio);
		DEBUG_PRINT_TIMESTAMP(); DEBUG_PRINT("DONE SEEDING RNG.\n");
		state.uid = drv_rand_getU64();
		drv_rand_fillBuf(state.privkey, sizeof(state.privkey));
		crypto_x25519_public_key(state.pubkey, state.privkey);
		//DEBUG_PRINT("UID: [%llu]\n", state.uid);
		DEBUG_PRINT("UID: [%llX]\n", state.uid);
}

enum drv_mesh_error_e drv_mesh_send(struct drv_mesh_packet_s * packet) {
	return 0;
}

void drv_mesh_getStats(struct drv_mesh_stats_s * stats) {
	memcpy(&(state.stats), stats, sizeof(struct drv_mesh_stats_s));
	stats->peer_count = 0;
	struct peer_s * peer = state.head_peer_ready;
	while(peer != NULL) {
		stats->peer_count++;
		peer = peer->next;
	}
}

#endif