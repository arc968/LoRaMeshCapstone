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
	//PACKET_TYPE__DISC_HANDSHAKE = 4,
	PACKET_TYPE__ACK = 5,
	PACKET_TYPE__NACK = 6,
	PACKET_TYPE__ROUTE = 7,
};

enum nack_reason_e {
	NACK_REASON__NONE = 0,
	NACK_REASON__NO_ROUTE,
	NACK_REASON__BUFFER_FULL,
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
	uint8_t reserved;
} __attribute__((packed, aligned(1)));
#pragma scalar_storage_order default

/*
hash sent/received public key with pre-shared key, then calculate key exchange
*/
#pragma scalar_storage_order big-endian
static struct packet_type_disc_s {
	struct packet_header_s header;
	struct {
		uint8_t key_dh_pub[32];
		lib_datetime_realtime_t timestamp;
	} body;
	uint8_t nonce[24];
	uint8_t mac[16];
} __attribute__((packed, aligned(1))) const packet_type_disc_s_default = {
	.header.type = PACKET_TYPE__DISC,
};
#pragma scalar_storage_order default

#pragma scalar_storage_order big-endian
struct packet_type_discReply_s { //CAN WE JUST SEND THIS BACK AND FORTH? CAN ACK COMPLETE THE HANDSHAKE INSTEAD?
	struct packet_header_s header;
	uint8_t key_once_pub[32];
	struct {
		uint8_t key_ephemeral_pub[32];
		uint16_t index;
		uint8_t key_dh_pub[32];
		lib_datetime_realtime_t timestamp;
	} body; //encrypted with DH(recv.key_dh_pub, key_once_priv) as key
	uint8_t hmac[16]; //needs to include timestamp, DH(once,priv), DH(eph,priv), DH(pub,priv), AEAD MAC, and psk for auth
} __attribute__((packed, aligned(1))) const packet_type_discReply_s_default = {
	.header.type = PACKET_TYPE__DISC_REPLY,
};
#pragma scalar_storage_order default

/* #pragma scalar_storage_order big-endian
struct packet_type_discHandshake_s {
	struct packet_header_s header;
	uint8_t key_once_pub[32];
	struct {
		uint8_t key_ephemeral_pub[32];
		uint16_t index_send;
		uint16_t index_recv;
		lib_datetime_realtime_t timestamp;
	} body; //encrypted with DH(recv.key_dh_pub, key_once_priv) as key
	uint8_t hmac[16]; //needs to include timestamp, DH(once,priv), DH(eph,priv), DH(pub,priv), AEAD MAC, and psk for auth
} __attribute__((packed, aligned(1))) const packet_type_discHandshake_s_default = {
	.header.type = PACKET_TYPE__DISC_HANDSHAKE,
};
#pragma scalar_storage_order default */

#pragma scalar_storage_order big-endian
struct packet_linkHeader_s {
	struct packet_header_s header;
	uint16_t index_recv;
	uint32_t counter;
	uint8_t mac[16]; //poly1305
	uint8_t type; //actual type is encrypted
	uint8_t reserved;
} __attribute__((packed, aligned(1)));
#pragma scalar_storage_order default

#pragma scalar_storage_order big-endian
struct packet_type_ack_s {
	struct packet_linkHeader_s header;
	uint32_t counter_range_min;
	uint32_t counter_range_max;
} __attribute__((packed, aligned(1)));
#pragma scalar_storage_order default

#pragma scalar_storage_order big-endian
struct packet_type_nack_s {
	struct packet_linkHeader_s header;
	uint32_t counter_range_min;
	uint32_t counter_range_max;
} __attribute__((packed, aligned(1)));
#pragma scalar_storage_order default

#pragma scalar_storage_order big-endian
struct packet_type_data_s {
	struct packet_linkHeader_s header;
	//dynamic, "public"
	uint8_t ttl; //increments on each hop
	//uint32_t puid; //random on each hop for ACK purposes
	uint16_t index_send;
	uint16_t index_recv;
	//static, "public"
	ipv4_t ip_src;
	port_t port_src;
	ipv4_t ip_dst;
	port_t port_dst;
	//"private"
	//uint16_t seq_num;
	//uint16_t ack_num;
	uint32_t counter;
	uint8_t data[];
} __attribute__((packed, aligned(1)));
#pragma scalar_storage_order default

#pragma scalar_storage_order big-endian
struct packet_type_route_s {
	struct packet_linkHeader_s header;
	//dynamic, "public"
	uint8_t ttl; //increments on each hop
	//uint32_t puid; //random on each hop for ACK purposes
	uint16_t index_send;
	uint16_t index_recv;
	//static, "public"
	ipv4_t ip_src;
	ipv4_t ip_dst;
	uint32_t counter;
	uint8_t data[];
} __attribute__((packed, aligned(1)));
#pragma scalar_storage_order default

#if defined (__cplusplus)
}
#endif
#endif // DRV_MESH_AIR_H