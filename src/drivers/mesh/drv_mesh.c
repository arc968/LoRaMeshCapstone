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
#include "drv_mesh_send.h"
#include "drv_mesh_route.h"
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

	lib_datetime_realtime_t rt_disc;
	drv_timer_getRealtime(&rt_disc);
	if (rt_disc >= state.scheduleBy - SCHEDULER_PRE_DISCOVERY_WINDOW_MS) {
		DEBUG_PRINT("\tWARNING: drv_mesh_worker_scheduler() late, skipping.\n");
		state.scheduleBy += DISCOVERY_INTERVAL_MILLIS;
		return;
	} else {
		state.scheduleBy += DISCOVERY_INTERVAL_MILLIS;
	}
	rt_disc = (rt_disc / DISCOVERY_INTERVAL_MILLIS) * DISCOVERY_INTERVAL_MILLIS;
	rt_disc += DISCOVERY_INTERVAL_MILLIS;
	//rt_disc is the start of the upcoming period

	{ // debug output
		struct drv_mesh_stats_s stats;
		drv_mesh_getStats(&stats);
		printStats(&stats);
		for (uint32_t i=0; i<BUFFER_PEERS_SIZE; i++) {
			DEBUG_PRINT("\t peer %u: ", i);
			struct peer_s * peer = &(state.peers[i]);
			printPeerStats(peer);
		}
		DEBUG_PRINT_ARRAY(state.ip);
	}
	
	{ //schedule global discovery broadcast/receive
		struct appointment_s * appt = popEmptyAppt();
		if (appt == NULL) {
			DEBUG_PRINT("\tWARNING: Failed to get next global discovery appointment\n");
			return;
		}
		{
			uint32_t seed;

			// uint64_t rt_disc_tmp = LIB_BYTEORDER_HTON_U64(rt_disc);
			// crypto_blake2b_general((uint8_t *)&seed, sizeof(seed), state.psk, sizeof(state.psk), (uint8_t *)&(rt_disc_tmp), sizeof(rt_disc_tmp));
			// seed = LIB_BYTEORDER_NTOH_U32(seed);

			uint32_t tmp = 0; //lib_misc_fastrange32(seed, DISCOVERY_INTERVAL_MILLIS);
			appt->realtime = rt_disc + tmp;
			lib_datetime_interval_t curTime = drv_timer_getMonotonicTime();
			uint32_t tmp2 = (uint32_t)constrainU64(map(curTime, 0, LIB_DATETIME__MS_IN_DAY/24, 8, 20), 8, 20); // Ends at sending 1/n times
			uint32_t tmp3 = lib_misc_fastrange32(drv_rand_getU32(), tmp2);
			
			//appt->peer = NULL;

			//uint32_t seed;
			uint64_t appt_rt_tmp = LIB_BYTEORDER_HTON_U64(appt->realtime);
			crypto_blake2b_general((uint8_t *)&seed, sizeof(seed), state.psk, sizeof(state.psk), (uint8_t *)&(appt_rt_tmp), sizeof(appt_rt_tmp));
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
				drv_mesh_buildPacket_disc(appt->packet);
				DEBUG_PRINT("\tINFO: Scheduling disc send at t+%lu\n", appt->realtime - rt_disc);
				setRadioCfgAtTimeFromSeed(&(appt->radio_cfg), appt->realtime, seed, appt->packet->size);
				//estimateTimeOnAirInMsFromRadioCfg(&(appt->radio_cfg), appt->packet->size);
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
			
			uint32_t offset = lib_misc_fastrange32(seed, (DISCOVERY_INTERVAL_MILLIS - DISCOVERY_PADDING) - PACKET_TOA_MAX_GENERATE) + DISCOVERY_PADDING;
			appt->realtime = rt_disc + offset;

			DEBUG_PRINT("\tINFO: Scheduling peer recv at t+%lu\n", offset);
			//appt->type = APPT_RECV;
			//appt->peer = NULL;
			appt->packet = NULL;
			setRadioCfgAtTimeFromSeed(&(appt->radio_cfg), appt->realtime, seed, 255);
			
			enum drv_sched_err_e err = drv_sched_once_at(drv_mesh_worker_recv, (void*)appt, DRV_SCHED_PRI__REALTIME, appt->realtime);
			if (err != DRV_SCHED_ERR__NONE) {
				DEBUG_PRINT("\tWARNING: Failed to schedule receive appointment\n");
				insertEmptyAppt(appt);
				break; //the rest will fail anyway
			}
		}
	}

	{ //queue payloads
		/* uint16_t count = RB_COUNT(state.rb_outboundPackets);
		for (uint16_t i=0; i<count; i++) {
			struct packet_s * packet = *RB_GET(state.rb_outboundPackets);
			
			*RB_PUT(state.rb_outboundPackets) = packet;
		} */
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
				/* if (peer->status == PEER_ACQUAINTANCE && packet->header.type == PACKET_TYPE__DISC_REPLY) {
					insertEmptyPacket(packet);
					if (!RB_COUNT(peer->rb_packets)) {
						continue; //no packets queued
					}
					packet = *RB_GET(peer->rb_packets);
				} */
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
				
				uint32_t offset = lib_misc_fastrange32(seed, (DISCOVERY_INTERVAL_MILLIS - DISCOVERY_PADDING) - PACKET_TOA_MAX_GENERATE) + DISCOVERY_PADDING;
				appt->realtime = rt_disc + offset;

				DEBUG_PRINT("\tINFO: Scheduling peer send at t+%lu\n", offset);

				setRadioCfgAtTimeFromSeed(&(appt->radio_cfg), appt->realtime, seed, packet->size);
				//estimateTimeOnAirInMsFromRadioCfg(&(appt->radio_cfg), packet->size);
				
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

				enum drv_sched_err_e err = drv_sched_once_at(drv_mesh_worker_send, (void*)appt, DRV_SCHED_PRI__REALTIME, appt->realtime);
				if (err != DRV_SCHED_ERR__NONE) {
					DEBUG_PRINT("\tWARNING: Failed to schedule peer send appointment\n");
					insertEmptyAppt(appt);
					break; //the rest will fail anyway
				}
			}
		}
	}
	DEBUG_PRINT_REALTIME(); DEBUG_PRINT("drv_mesh_worker_scheduler() return\n");
}

//runs once absolute scheduling is available
//TODO error handling
static void drv_mesh_start(void * arg __attribute__((unused))) {
	DEBUG_PRINT_REALTIME(); DEBUG_PRINT_FUNCTION();
	
	lib_datetime_realtime_t rt;
	drv_timer_getRealtime(&rt);
	rt = (rt / DISCOVERY_INTERVAL_MILLIS) * DISCOVERY_INTERVAL_MILLIS;
	rt += DISCOVERY_INTERVAL_MILLIS;
	
	state.scheduleBy = rt;
	enum drv_sched_err_e err = drv_sched_repeating_at(drv_mesh_worker_scheduler, NULL, DRV_SCHED_PRI__REALTIME, rt-SCHEDULER_PRE_DISCOVERY_INTERVAL_MS, DISCOVERY_INTERVAL_MILLIS);
	if (err != DRV_SCHED_ERR__NONE) { //error checking
		DEBUG_PRINT("\tWARNING: Failed to schedule drv_mesh_worker_scheduler()\n");
		return;
	}
}

//add runonce guard
void drv_mesh_init(void (*func_onRecv_ptr)(struct drv_mesh_packet_s *)) {
	DEBUG_PRINT_TIMESTAMP(); DEBUG_PRINT_FUNCTION();
	//initialize datastructures
		state.func_onRecv_ptr = func_onRecv_ptr;

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
		drv_rand_fillBuf(state.ip, sizeof(state.ip));
		state.ip[0] = 10;
		DEBUG_PRINT_ARRAY(state.ip);
}

enum drv_mesh_error_e drv_mesh_send(ipv4_t ip, uint16_t port, uint8_t * buf, uint8_t len) {

	struct drv_mesh_stats_s stats;
	drv_mesh_getStats(&stats);
	if (stats.peer_count == 0) {
		DEBUG_PRINT("\tWARNING: Failed to send mesh packet, no peers available\n");
		return DRV_MESH_ERR__NO_PEERS;
	}

/* 	struct route_s * route = findRoute(packet->ip, 0);
	if (route == NULL) {
		DEBUG_PRINT("\tWARNING: Failed to send mesh packet, no route available\n");
		return DRV_MESH_ERR__NO_ROUTE;
	} */

	if (len > DRV_MESH__MESSAGE_SIZE_MAX) {
		DEBUG_PRINT("\tWARNING: Failed to send mesh packet, payload too large\n");
		return DRV_MESH_ERR__MESSAGE_TOO_LARGE;
	}

	if (!RB_SPACE(state.rb_outboundPackets)) {
		DEBUG_PRINT("\tWARNING: Failed to send mesh packet, outbound packet buffer full\n");
		return DRV_MESH_ERR__BUFFER_FULL;
	}

	struct packet_s * raw_packet = popEmptyPacket();
	if (raw_packet == NULL) {
		DEBUG_PRINT("\tWARNING: Failed to send mesh packet, no empty packets available\n");
		return DRV_MESH_ERR__BUFFER_FULL;
	}

	struct payload_type_data_s * payload = (struct payload_type_data_s *)&(raw_packet->asLink.payload[0]);
	payload->header.type = PAYLOAD_TYPE__DATA;
	memcpy(payload->ip_dst, &ip, sizeof(ipv4_t));
	payload->port_dst = LIB_BYTEORDER_HTON_U16(port);
	memcpy(payload->data, buf, len);

	*RB_PUT(state.rb_outboundPackets) = raw_packet;

	DEBUG_PRINT("\tINFO: Sending serial message (%hhu bytes) in payload (%hhu bytes) in packet (%hhu bytes) \n", len, sizeof(struct payload_type_data_s) + len, sizeof(struct packet_type_link_s) + sizeof(struct payload_type_data_s) + len);

	struct peer_s * peer = state.head_peer_ready;
	for (; peer != NULL; peer = peer->next) {
		if (peer->status == PEER_ACQUAINTANCE) {
			if (RB_SPACE(peer->rb_packets)) {
				struct packet_s * tmp_packet = popEmptyPacket();
				if (tmp_packet == NULL) {
					DEBUG_PRINT("\tWARNING: Failed to send mesh packet, no empty packets available\n");
					break; //rest will fail anyway
				}
				drv_mesh_buildPacket_link(peer, tmp_packet, (uint8_t *)payload, sizeof(struct payload_type_data_s) + len);
				*RB_PUT(peer->rb_packets) = tmp_packet;
			}
		}
	}

	return DRV_MESH_ERR__NONE;
}

#endif