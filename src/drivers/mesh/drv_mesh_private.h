#ifndef DRV_MESH_PRIVATE_H
#define DRV_MESH_PRIVATE_H
#if defined (__cplusplus)
extern "C" {
#endif

typedef uint16_t channel_t;

typedef uint64_t peer_uid_t;

#include "drv_mesh_air.h"

enum peer_status_e {
	PEER_EMPTY = 0,
	PEER_PASSERBY, //only heard their broadcast
	PEER_STRANGER, //they heard our broadcast, but we did not hear theirs
	PEER_ACQUAINTANCE, //handshake complete
	PEER_FRIEND, //PSK handshake complete
};

struct peer_s {
	struct peer_s * next;
	enum peer_status_e status;
	peer_uid_t uid;
	//uint8_t key[32];
};

struct radio_cfg_s {
	uint16_t preambleSymbols;
	uint64_t frequency;
	enum drv_lora_bandwidth_e bandwidth;
	enum drv_lora_spreadingFactor_e spreadingFactor;
	enum drv_lora_codingRate_e codingRate;
};

enum appointment_type_e {
	APPT_RECV,
	APPT_SEND_DISC,
	APPT_SEND_DISC_REPLY,
	APPT_SEND_DISC_HANDSHAKE,
	APPT_SEND_DATA,
	APPT_SEND_ROUTE,
/* 	APPT_DISC_RECV,
	APPT_DISC_REPLY_SEND,
	APPT_DISC_REPLY_RECV,
	APPT_DATA_SEND, */
};

struct appointment_s {
	struct appointment_s * next;
	
	lib_datetime_realtime_t realtime;
	
	enum appointment_type_e type;
	
	struct peer_s * peer;
	
	struct packet_s * packet;
	
	struct radio_cfg_s radio_cfg;
}; //__attribute__((packed)); //PACKED CAUSES HARD LOCKUP

struct packet_s {
	struct packet_s * next;
	uint8_t size;
	union {
		struct packet_header_s header;
		struct packet_type_data_s asData;
		struct packet_type_disc_s asDisc;
		struct packet_type_discReply_s asDiscReply;
		struct packet_type_discHandshake_s asDiscHandshake;
		struct packet_type_ack_s asAck;
		struct packet_type_nack_s asNack;
		struct packet_type_route_s asRoute;
		uint8_t raw[DRV_MESH__PACKET_SIZE_MAX];
	};
} __attribute__((packed, aligned(1)));

struct route_s {
	struct route_s * next;
	ipv4_t ip_src;
	lib_datetime_realtime_t last_usage;
	struct {
		uint8_t ttl;
		uint16_t index_peer;
	} peers[ROUTE_PEER_COUNT];
};

static struct state_s {
	ipv4_t ip;
	peer_uid_t uid;
	//uint8_t pubkey[32];
	//uint8_t privkey[32];
	uint8_t psk[32];
	uint8_t key_hashtable[8];
	
	struct {
		uint16_t head;
		uint16_t tail;
		uint16_t count;
		struct {
			uint8_t hash[4];
			uint8_t ttl;
		} buf[BUFFER_RECENT_PACKETS_SIZE];
	} rb_recentPackets;
	
	struct route_s route_gateway;
	struct route_s * head_route_empty;
	struct route_s routes[BUFFER_ROUTES_SIZE];
	struct route_s * hm_route_buckets[HASHMAP_ROUTES_BUCKET_COUNT];

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

#include "drv_mesh_private_util.h"

#if defined (__cplusplus)
}
#endif
#endif // DRV_MESH_PRIVATE_H