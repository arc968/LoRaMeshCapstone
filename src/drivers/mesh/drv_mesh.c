#include "../../hardware/hardware.h"

#if !defined(HW_GPS) || !defined(HW_LORA)
	#warning "HW_GPS and/or HW_LORA is undefined. Linking to drv_mesh.c will fail."
#else

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

void drv_mesh_getStats(struct drv_mesh_stats_s * stats) {
	memcpy(stats, &(state.stats), sizeof(struct drv_mesh_stats_s));
	stats->peer_count = 0;
	stats->peer_count_passerby = 0;
	stats->peer_count_stranger = 0;
	stats->peer_count_acquaintance = 0;
	struct peer_s * peer = state.head_peer_ready;
	while (peer != NULL) {
		stats->peer_count++;
		if (peer->status == PEER_PASSERBY) stats->peer_count_passerby++;
		if (peer->status == PEER_STRANGER) stats->peer_count_stranger++;
		if (peer->status == PEER_ACQUAINTANCE) stats->peer_count_acquaintance++;
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
	DEBUG_PRINT("\t peer_count_passerby: %lu\n", stats->peer_count_passerby);
	DEBUG_PRINT("\t peer_count_stranger: %lu\n", stats->peer_count_stranger);
	DEBUG_PRINT("\t peer_count_acquaintance: %lu\n", stats->peer_count_acquaintance);
}

static void printPeerStats(struct peer_s * peer) {
	DEBUG_PRINT("[status=%s,last_packet_timestamp=%llu]\n", peer_status_string_arr[peer->status], peer->last_packet_timestamp);
	//DEBUG_PRINT("[status=%s,ip=[%hhu.%hhu.%hhu.%hhu],last_packet_timestamp=%llu]\n", peer_status_string_arr[peer->status], peer->ip[0], peer->ip[1], peer->ip[2], peer->ip[3], peer->last_packet_timestamp);
}

//small issue, starts backing off on boot not after initialization
//also needs to change bandwidth based on time, not seed
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
			uint32_t tmp2 = (uint32_t)constrainU64(map(curTime, 0, DISC_BACKOFF_DURATION_MS, DISC_FRAC_START, DISC_FRAC_END), DISC_FRAC_START, DISC_FRAC_END); // Ends at sending 1/n times
			uint32_t tmp3 = lib_misc_fastrange32(drv_rand_getU32(), tmp2);
			
			//appt->peer = NULL;

			//uint32_t seed;
			uint64_t appt_rt_tmp = LIB_BYTEORDER_HTON_U64(appt->realtime);
			crypto_blake2b_general((uint8_t *)&seed, sizeof(seed), state.psk, sizeof(state.psk), (uint8_t *)&(appt_rt_tmp), sizeof(appt_rt_tmp));
			seed = LIB_BYTEORDER_NTOH_U32(seed);
			
			enum drv_sched_err_e err;

			// TEMP DEBUG
			// hal_gpio_pinMode(7, INPUT_PULLUP);
			// if (hal_gpio_digitalRead(7)) {
			// 	tmp3 = 1;
			// } else {
			// 	tmp3 = 0;
			// }

			// END TEMP DEBUG

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
	
	{ //queue outbound packet
		if (RB_COUNT(state.rb_outboundPackets)) {
			struct packet_s * packet = *RB_GET(state.rb_outboundPackets);
			struct payload_type_data_s * payload = (struct payload_type_data_s *)&(packet->asLink.payload[0]);
			lib_datetime_realtime_t rt;
			drv_timer_getRealtime(&rt);	
			drv_mesh_routePayload((struct payload_s *)payload, packet->size, rt, NULL);
			*RB_PUT(state.rb_outboundPackets) = packet;
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

static void fn_stub(struct drv_mesh_packet_s * packet) {
	return;
}

extern uint8_t TESTING_DEMO_ISGATEWAY_FLAG_THING;

//add runonce guard
void drv_mesh_init(uint8_t key_psk[32], uint8_t key_dh_priv[32], void (*func_onRecv_ptr)(struct drv_mesh_packet_s *)) {
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
		//configure GPS for timekeeping mode as appropriate
			drv_gps_init(NULL);
	//initialize LoRa radio
		drv_lora_init(&state.radio, getCenterFrequency(0, DRV_LORA_BW__125kHz)); //TESTING
	//configure LoRa radio
		drv_lora_setMode(&state.radio, DRV_LORA_MODE__SLEEP);
	//seed RNG
		DEBUG_PRINT_TIMESTAMP(); DEBUG_PRINT("SEEDING RNG...\n");
		drv_rand_seedFromLoRa(&state.radio);
		DEBUG_PRINT_TIMESTAMP(); DEBUG_PRINT("DONE SEEDING RNG.\n");
	//set variables
		if (func_onRecv_ptr != NULL) {
			state.func_onRecv_ptr = func_onRecv_ptr;
		} else {
			state.func_onRecv_ptr = fn_stub;
		}
		if (key_psk != NULL) {
			memcpy(state.psk, key_psk, sizeof(state.psk));
		} else {
			crypto_wipe(state.psk, sizeof(state.psk));
		}
		if (key_dh_priv != NULL) {
			memcpy(state.key_dh_priv, key_dh_priv, sizeof(state.key_dh_priv));
		} else {
			drv_rand_fillBuf(state.key_dh_priv, sizeof(state.key_dh_priv));
		}
		crypto_x25519_public_key(state.key_dh_pub, state.key_dh_priv);

		if (TESTING_DEMO_ISGATEWAY_FLAG_THING) {
			//memset(state.ip, 8, sizeof(ipv4_t));
			memcpy(state.ip, GATEWAY_IP, sizeof(ipv4_t));
		} else {			//drv_rand_fillBuf(state.ip, sizeof(state.ip));
			
			// state.ip[0] = 10;
			// state.ip[1] = 0;
			// state.ip[2] = 0;
			// state.ip[3] = DEMO_IP;

			crypto_blake2b_general(state.ip, sizeof(ipv4_t), NULL, 0, state.key_dh_priv, sizeof(state.key_dh_priv));
			state.ip[0] = 10;
			state.ip[1] = 0;
			state.ip[2] = 0;
		}
		DEBUG_PRINT_ARRAY(state.ip);
}

void drv_mesh_getIP(ipv4_t * ip) {
	memcpy(ip, state.ip, sizeof(ipv4_t));
}

enum drv_mesh_error_e drv_mesh_send(struct drv_mesh_packet_s * packet) {

	struct drv_mesh_stats_s stats;
	drv_mesh_getStats(&stats);
	if (stats.peer_count_acquaintance == 0) {
		DEBUG_PRINT("\tWARNING: Failed to send mesh packet, no peers available\n");
		return DRV_MESH_ERR__NO_PEERS;
	}

/* 	struct route_s * route = findRoute(packet->ip, 0);
	if (route == NULL) {
		DEBUG_PRINT("\tWARNING: Failed to send mesh packet, no route available\n");
		return DRV_MESH_ERR__NO_ROUTE;
	} */

	if (packet->len > DRV_MESH__MESSAGE_SIZE_MAX) {
		DEBUG_PRINT("\tWARNING: Failed to send mesh packet, payload too large\n");
		return DRV_MESH_ERR__MESSAGE_TOO_LARGE;
	}

	if (packet->len == 0) {
		DEBUG_PRINT("\tWARNING: Failed to send mesh packet, payload too small\n");
		return DRV_MESH_ERR__MESSAGE_TOO_SMALL;
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
	payload->header.ttl = 0;
	memcpy(payload->header.ip_src, state.ip, sizeof(ipv4_t));
	payload->header.port_src = LIB_BYTEORDER_HTON_U16(0);
	memcpy(payload->header.ip_dst, packet->ip, sizeof(ipv4_t));
	payload->header.port_dst = LIB_BYTEORDER_HTON_U16(packet->port);
	memcpy(payload->data, packet->buf, packet->len);

	//TODO can only send unique payload once
	//???
	payload->auth.num_seq = ++state.counter_outbound;
	payload->auth.num_ack = 0;

	raw_packet->counter = payload->auth.num_seq;
	raw_packet->size = sizeof(struct payload_type_data_s) + packet->len;
	*RB_PUT(state.rb_outboundPackets) = raw_packet;

	DEBUG_PRINT("\tINFO: Sending serial message (seq: %u) (%hhu bytes) in payload (%hhu bytes) in packet (%hhu bytes) \n", payload->auth.num_seq, packet->len, sizeof(struct payload_type_data_s) + packet->len, sizeof(struct packet_type_link_s) + sizeof(struct payload_type_data_s) + packet->len);

	insertRecentPayload((struct payload_s *)payload, raw_packet->size);

	//lib_datetime_realtime_t rt;
	//drv_timer_getRealtime(&rt);	
	//drv_mesh_routePayload((struct payload_s *)payload, sizeof(struct payload_type_data_s) + packet->len, rt);

	/* struct peer_s * peer = state.head_peer_ready;
	for (; peer != NULL; peer = peer->next) {
		if (peer->status == PEER_ACQUAINTANCE) {
			if (RB_SPACE(peer->rb_packets)) {
				struct packet_s * tmp_packet = popEmptyPacket();
				if (tmp_packet == NULL) {
					DEBUG_PRINT("\tWARNING: Failed to send mesh packet, no empty packets available\n");
					break; //rest will fail anyway
				}
				drv_mesh_buildPacket_link(peer, tmp_packet, (uint8_t *)payload, sizeof(struct payload_type_data_s) + packet->len);
				*RB_PUT(peer->rb_packets) = tmp_packet;
			}
		}
	} */

	return DRV_MESH_ERR__NONE;
}

#endif