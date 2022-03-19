#ifndef DRV_MESH_AIR_H
#define DRV_MESH_AIR_H
#if defined (__cplusplus)
extern "C" {
#endif

enum packet_type_e {
	//layer 3 (Network) (Relayable)
	PACKET_TYPE__DATA,
	//layer 2 (Data Link)
	PACKET_TYPE__DISC,
	PACKET_TYPE__DISC_REPLY,
	PACKET_TYPE__DISC_HANDSHAKE,
	PACKET_TYPE__ACK,
	PACKET_TYPE__NACK,
	PACKET_TYPE__REKEY,
	PACKET_TYPE__REKEY_REPLY,
};

enum ciphermask_e {
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
#pragma scalar_storage_order default

#pragma scalar_storage_order big-endian
struct packet_header_s {
	enum packet_type_e type;
} __attribute__((packed, aligned(1)));
#pragma scalar_storage_order default

/*
hash sent/received public key with pre-shared key, then calculate key exchange
*/
#pragma scalar_storage_order big-endian
static struct packet_type_disc_s {
	struct packet_header_s header;
	peer_uid_t broadcast_peer_uid;
	struct ciphermask_s ciphermask; //all capable/allowed bits are set
	uint8_t key_ephemeral[32];
} __attribute__((packed, aligned(1))) const packet_type_disc_s_default = {
	.header.type = PACKET_TYPE__DISC,
};
#pragma scalar_storage_order default

#pragma scalar_storage_order big-endian
struct packet_type_discReply_s {
	struct packet_header_s header;
	peer_uid_t broadcast_peer_uid;
	peer_uid_t reply_peer_uid;
	struct ciphermask_s ciphermask; //only a single bit set for selected mode
	uint8_t key_ephemeral[32]; //optional, only if common cipher is found
} __attribute__((packed, aligned(1))) const packet_type_disc_s_default = {
	.header.type = PACKET_TYPE__DISC,
};
#pragma scalar_storage_order default

#pragma scalar_storage_order big-endian
struct packet_type_discHandshake_s {
	struct packet_header_s header;
	peer_uid_t sender_peer_uid;
	
} __attribute__((packed, aligned(1)));
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
	uint8_t ttl; //decrements on each hop
	uint32_t puid; //random on each hop for ACK purposes
	//static, "public"
	ip_t src;
	ip_t dst;
	//"private"
	uint16_t seq_num;
	uint16_t ack_num;
	uint8_t data[];
} __attribute__((packed, aligned(1)));
#pragma scalar_storage_order default

#if defined (__cplusplus)
}
#endif
#endif // DRV_MESH_AIR_H