#ifndef DRV_MESH_PRIVATE_H
#define DRV_MESH_PRIVATE_H
#if defined (__cplusplus)
extern "C" {
#endif

typedef uint16_t channel_t;

typedef uint64_t peer_uid_t;

#include "drv_mesh_air.h"

/* enum peer_status_e {
	PEER_EMPTY = 0,
	PEER_PASSERBY, //only heard their broadcast
	PEER_STRANGER, //they heard our broadcast, but we did not hear theirs
	PEER_ACQUAINTANCE, //handshake complete
	PEER_FRIEND, //PSK handshake complete
}; */

/* enum peer_status_e {
	PEER_EMPTY = 0,
	PEER_PASSERBY, //have heard broadcast, will send discReply
	PEER_STRANGER, //have received discReply, will send discHandshake
	PEER_ACQUAINTANCE, //have received discHandshake, will send ACK for each discHandshake received
	//PEER_FRIEND, 
}; */

enum peer_status_e {
	PEER_EMPTY = 0,
	PEER_PASSERBY = 1, //have heard broadcast, will send discReply
	PEER_STRANGER = 2, //have received discReply, will send discReply, will send ACK for each discReply received
	PEER_ACQUAINTANCE = 3, //have received ACK, will send ACK for each discReply received
};

char * peer_status_string_arr[] = {
	[PEER_EMPTY] = "PEER_EMPTY",
	[PEER_PASSERBY] = "PEER_PASSERBY",
	[PEER_STRANGER] = "PEER_STRANGER",
	[PEER_ACQUAINTANCE] = "PEER_ACQUAINTANCE",
};

struct peer_s {
	struct peer_s * next;
	enum peer_status_e status;
	
	uint8_t key_dh_pub[32];
	uint8_t key_chan_send[8];
	uint8_t key_chan_recv[8];

	uint16_t index;
	uint32_t counter_send;
	uint32_t counter_recv;
	uint32_t counter_ack;

	uint8_t key_send[32];
	//union {
		uint8_t key_recv[32];
		uint8_t key_ephemeral_priv[32]; // of this peer
	//};

	lib_datetime_realtime_t last_packet_timestamp;
	
	struct {
		uint16_t count;
		uint16_t head;
		uint16_t tail;
		struct packet_s * buf[BUFFER_PER_PEER_PACKETS_SIZE];
	} rb_packets;
};

struct radio_cfg_s {
	uint16_t preambleSymbols;
	uint64_t frequency;
	enum drv_lora_bandwidth_e bandwidth;
	enum drv_lora_spreadingFactor_e spreadingFactor;
	enum drv_lora_codingRate_e codingRate;
	uint32_t toaEstimate;
};

struct appointment_s {
	struct appointment_s * next;
	
	lib_datetime_realtime_t realtime;

	struct radio_cfg_s radio_cfg;
	
	struct packet_s * packet;	
}; //__attribute__((packed)); //PACKED CAUSES HARD LOCKUP

struct packet_s {
	struct packet_s * next;
	bool once;
	uint32_t counter;
	uint8_t size;
	union {
		struct packet_header_s header;
		struct packet_type_disc_s asDisc;
		struct packet_type_auth_s asAuth;
		struct packet_type_link_s asLink;
		uint8_t raw[DRV_MESH__PACKET_SIZE_MAX];
	};
} __attribute__((packed, aligned(1)));

struct route_s {
	struct route_s * next;
	ipv4_t ip_src;
	lib_datetime_realtime_t last_usage;
	uint8_t count;
	struct {
		uint8_t ttl;
		uint16_t index_peer;
	} peers[ROUTE_PEER_COUNT];
};

static struct state_s {
	ipv4_t ip;
	uint8_t key_dh_pub[32];
	uint8_t key_dh_priv[32];
	uint8_t psk[32];
	uint8_t key_hashtable[8];

	lib_datetime_realtime_t scheduleBy;

	void (*func_onRecv_ptr)(struct drv_mesh_packet_s *);
	
	struct {
		uint16_t head;
		uint16_t tail;
		uint16_t count;
		struct {
			uint8_t hash[4];
			uint8_t ttl;
		} buf[BUFFER_RECENT_PAYLOADS_SIZE];
	} rb_recentPayloads;
	
	struct route_s route_gateway;
	struct route_s * head_route_empty;
	struct route_s routes[BUFFER_ROUTES_SIZE];
	struct route_s * hm_route_buckets[HASHMAP_ROUTES_BUCKET_COUNT];

	struct peer_s * head_peer_empty;
	struct peer_s * head_peer_ready;
	struct peer_s peers[BUFFER_PEERS_SIZE];

	struct packet_s * head_packet_empty;
	struct packet_s packets[BUFFER_PACKETS_SIZE];
	
	struct {
		uint16_t count;
		uint16_t head;
		uint16_t tail;
		struct packet_s * buf[BUFFER_OUTBOUND_PACKETS_SIZE];
	} rb_outboundPackets;
	uint32_t counter_outbound;

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