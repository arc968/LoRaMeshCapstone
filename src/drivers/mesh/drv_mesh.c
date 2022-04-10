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

#include "../../deps/monocypher/monocypher.h"
#include "../../deps/siphash/siphash.h"
#include "../../deps/siphash/halfsiphash.h"

/*#define XXH_NO_STREAM
#define XXH_NO_LONG_LONG
#define XXH_CPU_LITTLE_ENDIAN
#define XXH_NO_STDLIB
#define XXH_NO_INLINE_HINTS
#define XXH_FORCE_ALIGN_CHECK
#include "../../deps/xxhash/xxhash.h"*/

#include "drv_mesh_config.h"
#include "drv_mesh.h"
#include "drv_mesh_private.h"
#include "drv_mesh_route.h"
#include "drv_mesh_send.h"
#include "drv_mesh_recv.h"

//small issue, starts backing off on boot not after initialization
//also needs to change bandwidth based on time, not seed
/* static struct appointment_s * getNextGlobalDiscoveryChannelAppointment(lib_datetime_realtime_t rt) {
	DEBUG_PRINT("\t"); DEBUG_PRINT_FUNCTION();

	
	//DEBUG_PRINT("\tbandwidth:%lu, frequency:%llu, spreadingFactor:%lu, codingRate:%lu\n", appt->radio_cfg.bandwidth, appt->radio_cfg.frequency, appt->radio_cfg.spreadingFactor, appt->radio_cfg.codingRate); 
	
	//DEBUG_PRINT("\ttmp:%lu, tmp2:%lu, tmp3:%lu\n", tmp, tmp2, tmp3); 
	//DEBUG_PRINT("post:\nmin:%u\nsec:%u\nms:%u\n",dt.min,dt.sec,dt.ms);
	//DEBUG_PRINT("year:%u\nmonth:%u\nday:%u\nhour:%u\nmin:%u\nsec:%u\nms:%u\n",dt.year,dt.month,dt.day,dt.hour,dt.min,dt.sec,dt.ms);
	return appt;
} */

void drv_mesh_getStats(struct drv_mesh_stats_s * stats) {
	memcpy(stats, &(state.stats), sizeof(struct drv_mesh_stats_s));
	stats->peer_count = 0;
	struct peer_s * peer = state.head_peer_ready;
	while (peer != NULL) {
		stats->peer_count++;
		peer = peer->next;
	}
}

static void printStats(struct drv_mesh_stats_s * stats) {
	DEBUG_PRINT("\t packets_dropped: %lu\n", stats->packets_dropped);
	DEBUG_PRINT("\t packets_forwarded: %lu\n", stats->packets_forwarded);
	DEBUG_PRINT("\t corrupt_packets: %lu\n", stats->corrupt_packets);
	DEBUG_PRINT("\t broadcasts_sent: %lu\n", stats->broadcasts_sent);
	DEBUG_PRINT("\t broadcasts_recv: %lu\n", stats->broadcasts_recv);

	DEBUG_PRINT("\t peer_count: %lu\n", stats->peer_count);
}

static void printPeerStats(struct peer_s * peer) {
	DEBUG_PRINT("[status=%s,last_packet_timestamp=%llu]\n", peer_status_string_arr[peer->status], peer->last_packet_timestamp);
}

static void drv_mesh_worker_scheduler(void * arg) {
	DEBUG_PRINT_REALTIME(); DEBUG_PRINT_FUNCTION();
	
	{ // debug output
		struct drv_mesh_stats_s stats;
		drv_mesh_getStats(&stats);
		printStats(&stats);
		for (uint32_t i=0; i<BUFFER_PEERS_SIZE; i++) {
			DEBUG_PRINT("\t peer %u: ", i);
			struct peer_s * peer = &(state.peers[i]);
			printPeerStats(peer);
		}
	}

	lib_datetime_realtime_t rt_disc;
	drv_timer_getRealtime(&rt_disc);
	rt_disc = (rt_disc / DISCOVERY_INTERVAL_MILLIS) * DISCOVERY_INTERVAL_MILLIS;
	rt_disc += DISCOVERY_INTERVAL_MILLIS;
	
	{ //schedule global discovery broadcast/receive
		struct appointment_s * appt = popEmptyAppt();
		if (appt == NULL) {
			DEBUG_PRINT("\tWARNING: Failed to get next global discovery appointment\n");
			return;
		}
		{
			uint32_t tmp = 0;//lib_misc_fastrange32(short_rt, 5*1000); //Will be in first 5 seconds of block
			appt->realtime = rt_disc + tmp;
			lib_datetime_interval_t curTime = drv_timer_getMonotonicTime();
			uint32_t tmp2 = (uint32_t)constrainU64(map(curTime, 0, LIB_DATETIME__MS_IN_DAY/24, 4, 20), 2, 20); // Ends at sending 1/n times
			uint32_t tmp3 = lib_misc_fastrange32(drv_rand_getU32(), tmp2);
			
			//appt->peer = NULL;

			uint32_t seed;
			crypto_blake2b_general((uint8_t *)&seed, sizeof(seed), state.psk, sizeof(state.psk), (uint8_t *)&(appt->realtime), sizeof(appt->realtime));
			seed = LIB_BYTEORDER_NTOH_U32(seed);
			
			enum drv_sched_err_e err;
			if (tmp3) { //TESTING
				DEBUG_PRINT("\tNext disc: RECV with odds: %lu/%lu\n", tmp2-1, tmp2);
				//appt->type = APPT_RECV;
				DEBUG_PRINT("\tINFO: Scheduling disc recv at t+%lu\n", appt->realtime - rt_disc);
				setRadioCfgAtTimeFromSeed(&(appt->radio_cfg), appt->realtime, seed, sizeof(struct packet_type_disc_s));
				err = drv_sched_once_at(drv_mesh_worker_recv, (void*)appt, DRV_SCHED_PRI__REALTIME, appt->realtime);
			} else {
				DEBUG_PRINT("\tNext disc: SEND with odds: 1/%lu\n", tmp2);
				//appt->type = APPT_SEND_DISC;
				appt->packet = popEmptyPacket();
				if (appt->packet == NULL) {
					DEBUG_PRINT("\tWARNING: Failed to schedule global disc appointment, no empty packets available\n");
					insertEmptyAppt(appt);
					return;
				}
				drv_mesh_buildPacket_disc(appt);
				DEBUG_PRINT("\tINFO: Scheduling disc send at t+%lu\n", appt->realtime - rt_disc);
				setRadioCfgAtTimeFromSeed(&(appt->radio_cfg), appt->realtime, seed, appt->packet->size);
				err = drv_sched_once_at(drv_mesh_worker_send, (void*)appt, DRV_SCHED_PRI__REALTIME, appt->realtime);
			}
			
			if (err != DRV_SCHED_ERR__NONE) {
				DEBUG_PRINT("\tWARNING: Failed to schedule next global discovery appointment\n");
				insertEmptyAppt(appt);
				return;
			}
		}
	}
	
	{ //schedule per-peer receive periods
		struct peer_s * peer = state.head_peer_ready;
		for (; peer != NULL; peer = peer->next) {
			struct appointment_s * appt = popEmptyAppt();
			if (appt == NULL) {
				DEBUG_PRINT("\tWARNING: Failed to schedule peer receive appointment, no empty appointments available\n");
				break; //the rest will fail anyway
			}
			
			uint32_t seed;
			crypto_blake2b_general((uint8_t *)&seed, sizeof(seed), peer->key_chan_recv, sizeof(peer->key_chan_recv), (uint8_t *)&(rt_disc), sizeof(rt_disc)); //doesn't handle byteorder correctly
			seed = LIB_BYTEORDER_HTON_U32(seed);
			
			uint32_t offset = lib_misc_fastrange32(seed, DISCOVERY_INTERVAL_MILLIS - 10000) + 5000; //use middle 5 seconds
			appt->realtime = rt_disc + offset;
			//appt->type = APPT_RECV;
			//appt->peer = NULL;
			appt->packet = NULL;
			setRadioCfgAtTimeFromSeed(&(appt->radio_cfg), appt->realtime, seed, 255);
			
			DEBUG_PRINT("\tINFO: Scheduling peer recv at t+%lu\n", offset);
			
			enum drv_sched_err_e err = drv_sched_once_at(drv_mesh_worker_recv, (void*)appt, DRV_SCHED_PRI__REALTIME, appt->realtime);
			if (err != DRV_SCHED_ERR__NONE) {
				DEBUG_PRINT("\tWARNING: Failed to schedule receive appointment\n");
				insertEmptyAppt(appt);
				break; //the rest will fail anyway
			}
		}
	}

	{ //schedule per-peer send periods
		struct peer_s * peer = state.head_peer_ready;
		for (; peer != NULL; peer = peer->next) {
			struct packet_s * packet = NULL;
			{ // decide which packet to send this period
				if (!RB_COUNT(peer->rb_packets)) {
					continue; //no packets queued
				}
				packet = *RB_GET(peer->rb_packets);
				if (peer->status == PEER_ACQUAINTANCE && packet->header.type == PACKET_TYPE__DISC_REPLY) {
					insertEmptyPacket(packet);
					if (!RB_COUNT(peer->rb_packets)) {
						continue; //no packets queued
					}
					packet = *RB_GET(peer->rb_packets);
				}
				if (!packet->once) {
					*RB_PUT(peer->rb_packets) = packet;
				}
			}
			if (packet != NULL) {
				struct appointment_s * appt = popEmptyAppt();
				if (appt == NULL) {
					DEBUG_PRINT("\tWARNING: Failed to schedule peer send appointment, no empty appointments available\n");
					if (packet->once) {
						*RB_PUT(peer->rb_packets) = packet; //requeue packet that would otherwise be leaking memory
					}
					break; //the rest will fail anyway
				}
				
				uint32_t seed;
				crypto_blake2b_general((uint8_t *)&seed, sizeof(seed), peer->key_chan_send, sizeof(peer->key_chan_send), (uint8_t *)&(rt_disc), sizeof(rt_disc)); //doesn't handle byteorder correctly
				seed = LIB_BYTEORDER_HTON_U32(seed);
				
				uint32_t offset = lib_misc_fastrange32(seed, DISCOVERY_INTERVAL_MILLIS - 10000) + 5000; //use middle 5 seconds
				appt->realtime = rt_disc + offset;
				setRadioCfgAtTimeFromSeed(&(appt->radio_cfg), appt->realtime, seed, packet->size);
				
				if (packet->once) {
					appt->packet = packet;
				} else {
					appt->packet = popEmptyPacket();
					if (appt->packet == NULL) {
						DEBUG_PRINT("\tWARNING: Failed to schedule peer send appointment, no empty packets available\n");
						insertEmptyAppt(appt);
						return; //the rest will fail anyway
					}
					memcpy(appt->packet, packet, sizeof(struct packet_s));
				}

				DEBUG_PRINT("\tINFO: Scheduling peer send at t+%lu\n", offset);
				
				enum drv_sched_err_e err = drv_sched_once_at(drv_mesh_worker_send, (void*)appt, DRV_SCHED_PRI__REALTIME, appt->realtime);
				if (err != DRV_SCHED_ERR__NONE) {
					DEBUG_PRINT("\tWARNING: Failed to schedule peer send appointment\n");
					insertEmptyAppt(appt);
					break; //the rest will fail anyway
				}
			}
		}
	}

}

//runs once absolute scheduling is available
//TODO error handling
static void drv_mesh_start(void * arg __attribute__((unused))) {
	DEBUG_PRINT_REALTIME(); DEBUG_PRINT_FUNCTION();
	
	lib_datetime_realtime_t rt;
	drv_timer_getRealtime(&rt);
	rt = (rt / DISCOVERY_INTERVAL_MILLIS) * DISCOVERY_INTERVAL_MILLIS;
	rt += DISCOVERY_INTERVAL_MILLIS;
	
	enum drv_sched_err_e err = drv_sched_repeating_at(drv_mesh_worker_scheduler, NULL, DRV_SCHED_PRI__REALTIME, rt-5000, DISCOVERY_INTERVAL_MILLIS);
	if (err != DRV_SCHED_ERR__NONE) { //error checking
		DEBUG_PRINT("\tWARNING: Failed to schedule drv_mesh_worker_scheduler()\n");
		return;
	}
}

//add runonce guard
void drv_mesh_init(void (*func_onRecv_ptr)(struct drv_mesh_packet_s *)) {
	DEBUG_PRINT_TIMESTAMP(); DEBUG_PRINT_FUNCTION();
	//initialize datastructures
		state.head_route_empty = &(state.routes[0]);
		for (int i=0; i<BUFFER_ROUTES_SIZE; i++) {
			if (i == BUFFER_ROUTES_SIZE-1) {
				state.routes[i].next = NULL;
			} else {
				state.routes[i].next = &(state.routes[i+1]);
			}
		}
	
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
		//state.uid = drv_rand_getU64();
		drv_rand_fillBuf(state.key_dh_priv, sizeof(state.key_dh_priv));
		crypto_x25519_public_key(state.key_dh_pub, state.key_dh_priv);
		//DEBUG_PRINT("UID: [%llu]\n", state.uid);
		//DEBUG_PRINT("UID: [%llX]\n", state.uid);
}

enum drv_mesh_error_e drv_mesh_send(struct drv_mesh_packet_s * packet) {
	return 0;
}

#endif