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
#include "../rand/drv_rand.h"
#include "../../lib/misc/lib_misc.h"
#include "../../lib/datetime/lib_datetime.h"
#include "drv_mesh.h"
#include "drv_mesh_private.h"

//#include "../../lib/printf/printf.h"
int  snprintf_(char* buffer, size_t count, const char* format, ...);

#include "../../lib/monocypher/monocypher.h"

#define XXH_NO_STREAM
#define XXH_NO_LONG_LONG
#define XXH_CPU_LITTLE_ENDIAN
#define XXH_NO_STDLIB
#define XXH_NO_INLINE_HINTS
#define XXH_FORCE_ALIGN_CHECK
#include "../../lib/xxhash/xxhash.h"

#define BUFFER_PEERS_SIZE 16
//#define BUFFER_RELAY_SIZE 10
//#define BUFFER_INBOUND_SIZE 3
//#define BUFFER_OUTBOUND_SIZE 3
#define BUFFER_PACKETS_SIZE 16
#define BUFFER_APPOINTMENTS_SIZE 16

#define FREQ_500kHz 500000
#define FREQ_250kHz 250000
#define FREQ_125kHz 125000
#define FREQ_62_5kHz 62500

#define PREAMBLE_LENGTH 32

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

#define DEBUG_PRINT_FUNCTION() {char tbuf[256]; snprintf_(tbuf, sizeof(tbuf), "%s()\n",__func__); hal_serial_write(hal_serial0, (uint8_t *)&(tbuf[0]), strlen(tbuf));}

#define DEBUG_PRINT(...) {char tbuf[256]; snprintf_(tbuf, sizeof(tbuf), __VA_ARGS__); hal_serial_write(hal_serial0, (uint8_t *)&(tbuf[0]), strlen(tbuf));}

#define DEBUG_PRINT_TIMESTAMP() {char tbuf[256]; snprintf_(tbuf, sizeof(tbuf), "[%lu] ", (uint32_t)drv_timer_getMonotonicTime()); hal_serial_write(hal_serial0, (uint8_t *)&(tbuf[0]), strlen(tbuf));}

#define DEBUG_PRINT_REALTIME() {char tbuf[256]; lib_datetime_realtime_t trt; drv_timer_getRealtime(&trt); snprintf_(tbuf, sizeof(tbuf), "[rt:%lu] ", (uint32_t)trt); hal_serial_write(hal_serial0, (uint8_t *)&(tbuf[0]), strlen(tbuf));}

static struct state_s {
	ip_t ip;
	peer_uid_t uid;
	uint8_t pubkey[32];
	uint8_t privkey[32];
	uint8_t psk[32];

	struct peer_s * head_peer_empty;
	struct peer_s * head_peer_ready;
	struct peer_s peers[BUFFER_PEERS_SIZE];

	struct packet_s * head_packet_empty;
	struct packet_s packets[BUFFER_PACKETS_SIZE];

	struct appointment_s * head_appt_empty;
	struct appointment_s appointments[BUFFER_APPOINTMENTS_SIZE];

	volatile bool radio_mutex;
	struct drv_lora_s radio;
	
	struct drv_mesh_stats_s stats;
} state;

static struct peer_s * popEmptyPeer(void) {
	struct peer_s * peer = state.head_peer_empty;
	if (peer != NULL) {
		state.head_peer_empty = peer->next;
	}
	peer->next = NULL;
	return peer;
}

static void insertEmptyPeer(struct peer_s * peer) {
	peer->next = state.head_peer_empty;
	state.head_peer_empty = peer;
}

static void removeReadyPeer(struct peer_s * peer) {
	if (state.head_peer_ready == peer) {
		state.head_peer_ready = NULL;
	} else {
		struct peer_s * prev_peer = state.head_peer_ready;
		while (prev_peer->next != peer) prev_peer = prev_peer->next;
		prev_peer->next = peer->next;
		peer->next = NULL;
	}
}

static struct peer_s * getPeerByUID(peer_uid_t uid) {
	struct peer_s * peer = state.head_peer_ready;
	while (peer != NULL && peer->uid != uid) peer = peer->next;
	return peer;
}

static void insertReadyPeer(struct peer_s * peer) {
	peer->next = state.head_peer_ready;
	state.head_peer_ready = peer;
}

static struct packet_s * popEmptyPacket(void) {
	struct packet_s * packet = state.head_packet_empty;
	if (packet != NULL) {
		state.head_packet_empty = packet->next;
	}
	packet->next = NULL;
	return packet;
}

static void insertEmptyPacket(struct packet_s * packet) {
	packet->next = state.head_packet_empty;
	state.head_packet_empty = packet;
}

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

static uint64_t constrainU64(uint64_t x, uint64_t a, uint64_t b) {
	if(x < a) {
		return a;
	} else if(b < x) {
		return b;
	} else {
		return x;
	}
}

static uint64_t map(uint64_t x, uint64_t in_min, uint64_t in_max, uint64_t out_min, uint64_t out_max) {
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

static uint32_t getChannelCount(enum drv_lora_bandwidth_e bw) {
	if (bw == DRV_LORA_BW__500kHz) return LORA_US_CHANNELCOUNT_500kHz;
	if (bw == DRV_LORA_BW__250kHz) return LORA_US_CHANNELCOUNT_250kHz;
	if (bw == DRV_LORA_BW__125kHz) return LORA_US_CHANNELCOUNT_125kHz;
	if (bw == DRV_LORA_BW__62_5kHz) return LORA_US_CHANNELCOUNT_62_5kHz;
	return LORA_US_CHANNELCOUNT_500kHz;
}

/*
DRV_LORA_BW__62_5kHz DRV_LORA_SF__8 DRV_LORA_CR__4_6
DRV_LORA_BW__500kHz DRV_LORA_SF__12 DRV_LORA_CR__4_5
*/
static void setApptValsFromSeed(struct appointment_s * appt, uint32_t seed) {
	appt->radio_cfg.bandwidth = drv_lora_bandwidth_e_arr[lib_misc_fastrange32(seed, sizeof(drv_lora_bandwidth_e_arr)/sizeof(drv_lora_bandwidth_e_arr[0]))];
	appt->radio_cfg.frequency = getCenterFrequency(lib_misc_fastrange32(seed, getChannelCount(appt->radio_cfg.bandwidth)), appt->radio_cfg.bandwidth);
	appt->radio_cfg.spreadingFactor = drv_lora_spreadingFactor_e_arr[lib_misc_fastrange32(seed, sizeof(drv_lora_spreadingFactor_e_arr)/sizeof(drv_lora_spreadingFactor_e_arr[0]))];
	appt->radio_cfg.codingRate = drv_lora_codingRate_e_arr[lib_misc_fastrange32(seed, sizeof(drv_lora_codingRate_e_arr)/sizeof(drv_lora_codingRate_e_arr[0]))];
}

//small issue, starts backing off on boot not after initialization
//also needs to change bandwidth based on time, not seed
static struct appointment_s * getNextGlobalDiscoveryChannelAppointment(void) {
	DEBUG_PRINT_REALTIME(); DEBUG_PRINT_FUNCTION();
	struct appointment_s * appt = popEmptyAppt();
	if (appt == NULL) return NULL;
	
	struct lib_datetime_s dt;
	drv_timer_getAbsoluteDateTime(&dt); //safe to ignore error
	//DEBUG_PRINT("pre:\nmin:%u\nsec:%u\nms:%u\n",dt.min,dt.sec,dt.ms);
	dt.sec = (dt.sec / 15) * 15;
	dt.ms = 0;
	lib_datetime_realtime_t rt;
	lib_datetime_convertDatetimeToRealtime(&dt, &rt);
	rt += 1000*15;
	
	uint32_t short_rt = lib_misc_XORshiftLFSR32((uint32_t)lib_misc_mix64(rt));
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

	setApptValsFromSeed(appt, short_rt);
	DEBUG_PRINT("\tbandwidth:%lu, frequency:%llu, spreadingFactor:%lu, codingRate:%lu\n", appt->radio_cfg.bandwidth, appt->radio_cfg.frequency, appt->radio_cfg.spreadingFactor, appt->radio_cfg.codingRate); 
	
	DEBUG_PRINT("\ttmp:%lu, tmp2:%lu, tmp3:%lu\n", tmp, tmp2, tmp3); 
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

static void drv_mesh_worker_send_finish(void * arg) {
	DEBUG_PRINT_REALTIME(); DEBUG_PRINT_FUNCTION();
	DEBUG_PRINT_REALTIME(); DEBUG_PRINT("Packet sent.\n");
	struct appointment_s * appt = (struct appointment_s *) arg;
	
	drv_lora_setMode(&state.radio, DRV_LORA_MODE__SLEEP);
	state.radio_mutex = 0;
	
	if (appt->type == APPT_SEND_DISC) {
		state.stats.broadcasts_sent++;
	}
	
	insertEmptyAppt(appt);
}

static void drv_mesh_worker_send(void * arg) {
	DEBUG_PRINT_REALTIME(); DEBUG_PRINT_FUNCTION();
	struct appointment_s * appt = (struct appointment_s *) arg;
	
	if (appt->type == APPT_RECV) {
		DEBUG_PRINT_REALTIME(); DEBUG_PRINT("ERROR: Unexpected appointment type in drv_mesh_worker_send()\n");
		insertEmptyAppt(appt);
		return;
	}
	
	if (!state.radio_mutex) {
		
		struct packet_s raw_packet = {0};
		
		if (appt->type == APPT_SEND_DISC) {
			raw_packet.asDisc = packet_type_disc_s_default;
			raw_packet.asDisc.broadcast_peer_uid = state.uid;
			raw_packet.asDisc.ciphermask.mask = CIPHER__PSK_XCHACHA20;
			memcpy(state.pubkey, raw_packet.asDisc.key_ephemeral, sizeof(state.pubkey));
			crypto_blake2b_general(raw_packet.asDisc.hmac, sizeof(raw_packet.asDisc.hmac), state.psk, sizeof(state.psk), &(raw_packet.asDisc), sizeof(raw_packet.asDisc)-sizeof(raw_packet.asDisc.hmac));
			
			raw_packet.size = sizeof(struct packet_type_disc_s);
			
			DEBUG_PRINT_REALTIME(); DEBUG_PRINT("Sending discovery packet as [%llX]...\n", raw_packet.asDisc.broadcast_peer_uid);
		} else if (appt->type == APPT_SEND_DISC_REPLY) {
			raw_packet.asDiscReply = packet_type_discReply_s_default;
			raw_packet.asDiscReply.reply_peer_uid = state.uid;
			raw_packet.asDiscReply.broadcast_peer_uid = appt->peer->uid;
			raw_packet.asDiscReply.ciphermask.mask = CIPHER__PSK_XCHACHA20;
			
			memcpy(state.pubkey, raw_packet.asDiscReply.key_ephemeral, sizeof(state.pubkey));
			crypto_blake2b_general(raw_packet.asDiscReply.hmac, sizeof(raw_packet.asDiscReply.hmac), state.psk, sizeof(state.psk), &(raw_packet.asDiscReply), sizeof(raw_packet.asDiscReply)-sizeof(raw_packet.asDiscReply.hmac));
			
			raw_packet.size = sizeof(struct packet_type_discReply_s);
			
			DEBUG_PRINT_REALTIME(); DEBUG_PRINT("Sending discovery reply packet as [%llX] to [%llX]...\n", raw_packet.asDiscReply.reply_peer_uid, raw_packet.asDiscReply.broadcast_peer_uid);
		} else {
			DEBUG_PRINT_REALTIME(); DEBUG_PRINT("WARNING: Unexpected appointment type in drv_mesh_worker_disc_send(), unable to send.\n");
		}
		
		state.radio_mutex = 1;
		drv_lora_setMode(&state.radio, DRV_LORA_MODE__IDLE);
		
		drv_lora_setPreamble(&state.radio, PREAMBLE_LENGTH);
		drv_lora_setBandwidth(&state.radio, appt->radio_cfg.bandwidth);
		drv_lora_setSpreadingFactor(&state.radio, appt->radio_cfg.spreadingFactor);
		drv_lora_setCodingRate(&state.radio, appt->radio_cfg.codingRate);
		drv_lora_setFrequency(&state.radio, appt->radio_cfg.frequency);
		
		drv_lora_sendRawPacket_async(&state.radio, raw_packet.raw, raw_packet.size);
		
		enum drv_sched_err_e err = drv_sched_once(drv_mesh_worker_send_finish, arg, DRV_SCHED_PRI__REALTIME, 5000);
		if (err != DRV_SCHED_ERR__NONE) {
			DEBUG_PRINT_REALTIME(); DEBUG_PRINT("WARNING: Failed to schedule drv_mesh_worker_disc_send_finish()\n");
			drv_lora_setMode(&state.radio, DRV_LORA_MODE__SLEEP);
			state.radio_mutex = 0;
		}
	} else {
		DEBUG_PRINT_REALTIME(); DEBUG_PRINT("WARNING: Radio locked, unable to send discovery packet.\n");
	}
	insertEmptyAppt(appt);
}

static void drv_mesh_worker_recv_finish(void * arg) {
	DEBUG_PRINT_REALTIME(); DEBUG_PRINT_FUNCTION();
	struct appointment_s * appt = (struct appointment_s *) arg;
	
	struct packet_s raw_packet = {0};
	raw_packet.size = drv_lora_getRawPacket(&state.radio, raw_packet.raw);
	
	drv_lora_setMode(&state.radio, DRV_LORA_MODE__SLEEP);
	state.radio_mutex = 0;
	
	if (raw_packet.size > 0) {
		if (raw_packet.header.type == PACKET_TYPE__DISC) {
			DEBUG_PRINT_REALTIME(); DEBUG_PRINT("Discovery packet received from [%llX] (%lu bytes).\n", raw_packet.asDisc.broadcast_peer_uid, raw_packet.size);
			if (raw_packet.size != sizeof(struct packet_type_disc_s)) {
				DEBUG_PRINT_REALTIME(); DEBUG_PRINT("WARNING: Packet size does not match type.\n");
				insertEmptyAppt(appt);
				return;
			};
			
			state.stats.broadcasts_recv++;
			
			struct peer_s * peer = getPeerByUID(raw_packet.asDisc.broadcast_peer_uid);
			if (peer == NULL) {
				DEBUG_PRINT_REALTIME(); DEBUG_PRINT("Discovery packet from unknown peer (new peer found).\n");
				peer = popEmptyPeer();
				if (peer == NULL) {
					DEBUG_PRINT_REALTIME(); DEBUG_PRINT("WARNING: Unable to save new peer, no peer slots remaining.\n");
					insertEmptyAppt(appt);
					return;
				}
				peer->status = PEER_PASSERBY;
				peer->uid = raw_packet.asDisc.broadcast_peer_uid;
				//memcpy(raw_packet.asDisc.key_ephemeral, peer->key, sizeof(peer->key));
				crypto_x25519(peer->key, state.privkey, raw_packet.asDisc.key_ephemeral);
				crypto_blake2b_general(peer->key, sizeof(peer->key), state.psk, sizeof(state.psk), peer->key, sizeof(peer->key));
				
				uint8_t tmp_hmac[sizeof(raw_packet.asDisc.hmac)];
				crypto_blake2b_general(tmp_hmac, sizeof(tmp_hmac), state.psk, sizeof(state.psk), &(raw_packet.asDisc), sizeof(raw_packet.asDisc)-sizeof(tmp_hmac));
				if (memcmp(tmp_hmac, raw_packet.asDisc.hmac, sizeof(tmp_hmac)) != 0) {
					DEBUG_PRINT_REALTIME(); DEBUG_PRINT("HMAC mismatch.\n");
					state.stats.mac_failures++;
					insertEmptyPeer(peer);
				} else {
					insertReadyPeer(peer);
				}
			} else {
				DEBUG_PRINT_REALTIME(); DEBUG_PRINT("Discovery packet from known peer.\n");
				//peer already known
				if (peer->status == PEER_PASSERBY) {
					//heard their broadcast again, check if key is the same
				} else if (peer->status == PEER_ACQUAINTANCE) {
					//can't check if peer's key has changed since we wiped it... oops.
				} else if (peer->status == PEER_FRIEND) {
					//can't check if peer's key has changed since we wiped it... oops.
				} else {
					//shouldn't be possible
				}
			}
		} else if (raw_packet.header.type == PACKET_TYPE__DISC_REPLY) {
			DEBUG_PRINT_REALTIME(); DEBUG_PRINT("Discovery reply packet received from [%llX] (%lu bytes).\n", raw_packet.asDiscReply.reply_peer_uid, raw_packet.size);
			if (raw_packet.size != sizeof(struct packet_type_discReply_s)) {
				DEBUG_PRINT_REALTIME(); DEBUG_PRINT("WARNING: Packet size does not match type.\n");
				insertEmptyAppt(appt);
				return;
			};
			
			if (raw_packet.asDiscReply.broadcast_peer_uid != state.uid) {
				DEBUG_PRINT_REALTIME(); DEBUG_PRINT("Discovery reply packet intended for different broadcaster.\n");
				insertEmptyAppt(appt);
				return;
			}
			
			struct peer_s * peer = getPeerByUID(raw_packet.asDiscReply.reply_peer_uid);
			if (peer == NULL) { //PEER_STRANGER
				DEBUG_PRINT_REALTIME(); DEBUG_PRINT("Discovery reply packet received from unknown peer.\n");
				peer = popEmptyPeer();
				if (peer == NULL) {
					DEBUG_PRINT_REALTIME(); DEBUG_PRINT("WARNING: Unable to save new peer, no peer slots remaining.\n");
					insertEmptyAppt(appt);
					return;
				}
				peer->status = PEER_ACQUAINTANCE;
				peer->uid = raw_packet.asDiscReply.reply_peer_uid;
				crypto_x25519(peer->key, state.privkey, raw_packet.asDiscReply.key_ephemeral);
				crypto_blake2b_general(peer->key, sizeof(peer->key), state.psk, sizeof(state.psk), peer->key, sizeof(peer->key));
				
				uint8_t tmp_hmac[sizeof(raw_packet.asDiscReply.hmac)];
				crypto_blake2b_general(tmp_hmac, sizeof(tmp_hmac), state.psk, sizeof(state.psk), &(raw_packet.asDiscReply), sizeof(raw_packet.asDiscReply)-sizeof(tmp_hmac));
				if (memcmp(tmp_hmac, raw_packet.asDiscReply.hmac, sizeof(tmp_hmac)) != 0) {
					DEBUG_PRINT_REALTIME(); DEBUG_PRINT("HMAC mismatch.\n");
					state.stats.mac_failures++;
					insertEmptyPeer(peer);
				} else {
					insertReadyPeer(peer);
				}
			} else {
				if (peer->status == PEER_PASSERBY) {
					//do basically the same as above?
				} else if (peer->status == PEER_ACQUAINTANCE) {
					
				} else if (peer->status == PEER_FRIEND) {
					
				} else {
					//shouldn't be possible
				}
			}
		} else {
			DEBUG_PRINT_REALTIME(); DEBUG_PRINT("Unknown packet received.\n");
		}
	} else {
		DEBUG_PRINT_REALTIME(); DEBUG_PRINT("No packet received.\n");
	}
	insertEmptyAppt(appt);
}

static void drv_mesh_worker_recv(void * arg) {
	DEBUG_PRINT_REALTIME(); DEBUG_PRINT_FUNCTION();
	struct appointment_s * appt = (struct appointment_s *) arg;
	
	if (appt->type != APPT_RECV) {
		DEBUG_PRINT_REALTIME(); DEBUG_PRINT("ERROR: Unexpected appointment type in drv_mesh_worker_recv()\n");
		insertEmptyAppt(appt);
		return;
	}
	
	if (!state.radio_mutex) {
		DEBUG_PRINT_REALTIME(); DEBUG_PRINT("Listening for packet...\n");
		state.radio_mutex = 1;
		
		drv_lora_setMode(&state.radio, DRV_LORA_MODE__IDLE);
		
		drv_lora_setPreamble(&state.radio, PREAMBLE_LENGTH);
		drv_lora_setBandwidth(&state.radio, appt->radio_cfg.bandwidth);
		drv_lora_setSpreadingFactor(&state.radio, appt->radio_cfg.spreadingFactor);
		drv_lora_setCodingRate(&state.radio, appt->radio_cfg.codingRate);
		drv_lora_setFrequency(&state.radio, appt->radio_cfg.frequency);
		
		drv_lora_setMode(&state.radio, DRV_LORA_MODE__RECV_ONCE);
		
		enum drv_sched_err_e err = drv_sched_once(drv_mesh_worker_recv_finish, arg, DRV_SCHED_PRI__REALTIME, 5000);
		if (err != DRV_SCHED_ERR__NONE) {
			DEBUG_PRINT_REALTIME(); DEBUG_PRINT("WARNING: Failed to schedule drv_mesh_worker_disc_recv_finish()\n");
			drv_lora_setMode(&state.radio, DRV_LORA_MODE__SLEEP);
			state.radio_mutex = 0;
			insertEmptyAppt(appt);
		}
	} else {
		DEBUG_PRINT_REALTIME(); DEBUG_PRINT("WARNING: Radio locked, unable to listen for packet.\n");
		insertEmptyAppt(appt);
	}
}

static void drv_mesh_worker_scheduler(void * arg) {
	DEBUG_PRINT_REALTIME(); DEBUG_PRINT_FUNCTION();
	
	{ //schedule global discovery broadcast/receive
		struct appointment_s * appt = getNextGlobalDiscoveryChannelAppointment();
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
	
	{ //schedule own receive periods
		
	}
	
	{ //schedule per-peer sends
		
	}
}

//runs once absolute scheduling is available
static void drv_mesh_start(void * arg __attribute__((unused))) {
	DEBUG_PRINT_REALTIME(); DEBUG_PRINT_FUNCTION();

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
		drv_lora_init(&state.radio, getCenterFrequency(0, DRV_LORA_BW__125kHz), 0); //TESTING
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