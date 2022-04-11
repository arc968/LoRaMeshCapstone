#ifndef DRV_MESH_AIR_H
#define DRV_MESH_AIR_H
#if defined (__cplusplus)
extern "C" {
#endif

enum packet_type_e {
	PACKET_TYPE__NONE = 0,
	PACKET_TYPE__DISC,
	PACKET_TYPE__AUTH,
	PACKET_TYPE__LINK,
};
	//layer 2 (Data Link)
/* 	//layer 3 (Network) (Relayable)
	PACKET_TYPE__DATA,
	PACKET_TYPE__ACK,
	PACKET_TYPE__NACK,
	PACKET_TYPE__ROUTE, */


/* enum nack_reason_e {
	NACK_REASON__NONE = 0,
	NACK_REASON__NO_ROUTE,
	NACK_REASON__BUFFER_FULL,
}; */

#pragma scalar_storage_order big-endian
struct packet_header_s {
	uint8_t type;
	uint8_t reserved;
} __attribute__((packed, aligned(1)));
#pragma scalar_storage_order default

#pragma scalar_storage_order big-endian
static struct packet_type_disc_s {
	struct {
		struct packet_header_s header;
	} auth;
	struct {
		uint8_t key_dh_pub[32];
		lib_datetime_realtime_t timestamp;
	} lock;
	uint8_t nonce[24];
	uint8_t mac[16];
} __attribute__((packed, aligned(1))) const packet_type_disc_s_default = {
	.auth.header.type = PACKET_TYPE__DISC,
};
#pragma scalar_storage_order default

#pragma scalar_storage_order big-endian
struct packet_type_auth_s {
	struct {
		struct packet_header_s header;
		uint8_t key_once_pub[32];
	} auth;
	struct {
		uint8_t key_ephemeral_pub[32];
		uint16_t index;
		uint8_t key_dh_pub[32];
		lib_datetime_realtime_t timestamp;
	} lock; //encrypted with DH(recv.key_dh_pub, key_once_priv) as key
	uint8_t hmac[16]; //needs to include timestamp, DH(once,priv), DH(eph,priv), DH(pub,priv), AEAD MAC, and psk for auth
} __attribute__((packed, aligned(1))) const packet_type_auth_s_default = {
	.auth.header.type = PACKET_TYPE__AUTH,
};
#pragma scalar_storage_order default

#pragma scalar_storage_order big-endian
struct packet_type_link_s {
	struct {
		struct packet_header_s header;
		uint16_t index;
		uint32_t counter;
	} auth;
	struct {
		uint32_t ack;
	} lock;
	uint8_t mac[16]; //poly1305
	uint8_t data[];
} __attribute__((packed, aligned(1))) const packet_type_link_s_default = {
	.auth.header.type = PACKET_TYPE__LINK,
};
#pragma scalar_storage_order default

/* #pragma scalar_storage_order big-endian
struct packet_type_data_s {
	struct packet_link_s link;
	//dynamic, "public"
	uint8_t ttl; //increments on each hop
	//static, "public"
	ipv4_t ip_src;
	ipv4_t ip_dst;
	port_t port_src;
	port_t port_dst;
	uint32_t num_seq;
	uint32_t num_ack;
	//"private"
	uint8_t data[];
} __attribute__((packed, aligned(1))) const packet_type_data_s_default = {
	.link.header.type = PACKET_TYPE__DATA,
};
#pragma scalar_storage_order default */

/* #pragma scalar_storage_order big-endian
struct packet_type_ack_s {
	struct packet_linkHeader_s header;
	uint32_t puid;
} __attribute__((packed, aligned(1))) const packet_type_ack_s_default = {
	.header.body.type = PACKET_TYPE__ACK,
};
#pragma scalar_storage_order default */

/* #pragma scalar_storage_order big-endian
struct packet_type_nack_s {
	struct packet_linkHeader_s header;
	uint32_t puid;
} __attribute__((packed, aligned(1)));
#pragma scalar_storage_order default */

/* #pragma scalar_storage_order big-endian
struct packet_type_route_s {
	struct packet_linkHeader_s header;
	//dynamic, "public"
	uint8_t ttl; //increments on each hop
	//static, "public"
	ipv4_t ip_src;
	ipv4_t ip_dst;
	uint32_t puid;
	uint8_t pttl;
} __attribute__((packed, aligned(1)));
#pragma scalar_storage_order default */

#if defined (__cplusplus)
}
#endif
#endif // DRV_MESH_AIR_H