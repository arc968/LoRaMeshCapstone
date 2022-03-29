#ifndef DRV_MESH_AIR_H
#define DRV_MESH_AIR_H
#if defined (__cplusplus)
extern "C" {
#endif

enum packet_type_e {
	PACKET_TYPE__NONE = 0,
	//layer 3 (Network) (Relayable)
	PACKET_TYPE__DATA = 1,
	//layer 2 (Data Link)
	PACKET_TYPE__DISC = 2,
	PACKET_TYPE__DISC_REPLY = 3,
	PACKET_TYPE__DISC_HANDSHAKE = 4,
	PACKET_TYPE__ACK = 5,
	PACKET_TYPE__NACK = 6,
	PACKET_TYPE__ROUTE = 7,
};

/*enum ciphermask_e {
	CIPHER__NONE = (0x1 << 0),
	CIPHER__AES = (0x1 << 1),
	CIPHER__PSK_AES = (0x1 << 2),
	CIPHER__XCHACHA20 = (0x1 << 3),
	CIPHER__PSK_XCHACHA20 = (0x1 << 4),
};

#pragma scalar_storage_order big-endian
struct ciphermask_s {
	union {
		uint16_t none:1,
				aes:1,
				psk_aes:1,
				xchacha20:1,
				psk_xchacha20:1,
				:0;
		uint16_t mask;
	};
} __attribute__((packed, aligned(1)));
#pragma scalar_storage_order default*/

#pragma scalar_storage_order big-endian
struct packet_header_s {
	uint8_t type;
	uint8_t reserved[3];
} __attribute__((packed, aligned(1)));
#pragma scalar_storage_order default

/*
hash sent/received public key with pre-shared key, then calculate key exchange
*/
#pragma scalar_storage_order big-endian
static struct packet_type_disc_s {
	struct packet_header_s header;
	peer_uid_t broadcast_peer_uid;
	//struct ciphermask_s ciphermask; //all capable/allowed bits are set
	//uint8_t key_ephemeral[32];
	//uint8_t hmac[8];
} __attribute__((packed, aligned(1))) const packet_type_disc_s_default = {
	.header.type = PACKET_TYPE__DISC,
};
#pragma scalar_storage_order default

#pragma scalar_storage_order big-endian
struct packet_type_discReply_s {
	struct packet_header_s header;
	peer_uid_t broadcast_peer_uid;
	peer_uid_t reply_peer_uid;
	//struct ciphermask_s ciphermask; //only a single bit set for selected mode
	//uint8_t key_ephemeral[32];
	//uint8_t hmac[8];
} __attribute__((packed, aligned(1))) const packet_type_discReply_s_default = {
	.header.type = PACKET_TYPE__DISC_REPLY,
};
#pragma scalar_storage_order default

#pragma scalar_storage_order big-endian
struct packet_type_discHandshake_s {
	struct packet_header_s header;
	peer_uid_t sender_peer_uid;
	
} __attribute__((packed, aligned(1))) const packet_type_discHandshake_s_default = {
	.header.type = PACKET_TYPE__DISC_HANDSHAKE,
};
#pragma scalar_storage_order default

#pragma scalar_storage_order big-endian
struct packet_type_ack_s {
	struct packet_header_s header;
	uint32_t puid;
} __attribute__((packed, aligned(1)));
#pragma scalar_storage_order default

#pragma scalar_storage_order big-endian
struct packet_type_nack_s {
	struct packet_header_s header;
	uint32_t puid;
} __attribute__((packed, aligned(1)));
#pragma scalar_storage_order default

#pragma scalar_storage_order big-endian
struct packet_type_data_s {
	struct packet_header_s header;
	//dynamic, "public"
	uint8_t ttl; //increments on each hop
	//uint32_t puid; //random on each hop for ACK purposes
	uint16_t index_send;
	uint16_t index_recv;
	//static, "public"
	ip_t ip_src;
	ip_t ip_dst;
	//"private"
	//uint16_t seq_num;
	//uint16_t ack_num;
	uint32_t counter;
	uint8_t data[];
} __attribute__((packed, aligned(1)));
#pragma scalar_storage_order default

#pragma scalar_storage_order big-endian
struct packet_type_route_s {
	struct packet_header_s header;
	//dynamic, "public"
	uint8_t ttl; //increments on each hop
	//uint32_t puid; //random on each hop for ACK purposes
	uint16_t index_send;
	uint16_t index_recv;
	//static, "public"
	ip_t ip_src;
	ip_t ip_dst;
} __attribute__((packed, aligned(1)));
#pragma scalar_storage_order default

#if defined (__cplusplus)
}
#endif
#endif // DRV_MESH_AIR_H