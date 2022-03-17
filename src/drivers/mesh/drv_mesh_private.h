#ifndef DRV_MESH_PRIVATE_H
#define DRV_MESH_PRIVATE_H
#if defined (__cplusplus)
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include "../../lib/ip/lib_ip.h"
#include "drv_mesh.h"
#include "../lora/drv_lora.h"

#define DRV_MESH__PACKET_SIZE_MAX 255

typedef uint16_t channel_t;

typedef uint32_t peer_uid_t;

enum appointment_type_e {
	APPT_DISC_SEND,
	APPT_DISC_RECV,
	APPT_DATA_SEND,
	APPT_DATA_RECV,
};

/*
enum drv_mesh_bandwidth_e {
	BW__500kHz,
	BW__250kHz,
	BW__125kHz,
	BW__62_5kHz,
};
*/

struct peer_s {
	ip_t ip;
	peer_uid_t uid;
};

struct appointment_s {
	struct appointment_s * next;
	
	lib_datetime_realtime_t realtime;
	
	enum appointment_type_e type;
	
	struct peer_s * peer;
	
	channel_t channel;
	enum drv_lora_bandwidth_e bandwidth;
	enum drv_lora_spreadingFactor_e spreadingFactor;
	enum drv_lora_codingRate_e codingRate;
} __attribute__((packed));

enum packet_status_e {
	PACKET_FREE,
	PACKET_READY
};

enum packet_type_e {
	//layer 3 (Network) (Relayable)
	PACKET_TYPE__DATA,
	//layer 2 (Data Link)
	PACKET_TYPE__DISC,
	PACKET_TYPE__DISC_REPLY,
	PACKET_TYPE__DISC_HANDSHAKE,
	PACKET_TYPE__ACK,
	PACKET_TYPE__NACK,
};

enum ciphermask_e {
	CIPHER__NONE = 0,
	CIPHER__AES = (0x1 << 0),
	CIPHER__PSK_AES = (0x1 << 1),
	CIPHER__XCHACHA20 = (0x1 << 2),
	CIPHER__PSK_XCHACHA20 = (0x1 << 3),
};

#pragma scalar_storage_order big-endian
struct ciphermask_s {
	union {
		uint8_t none:1,
				aes:1,
				psk_aes:1,
				xchacha20:1,
				psk_xchacha20:1,
				:0;
		uint8_t mask;
	};
} __attribute__((packed, aligned(1)));
#pragma scalar_storage_order default

struct packet_header_s {
	enum packet_type_e type;
} __attribute__((packed));

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
} __attribute__((packed));

/*
hash sent/received public key with pre-shared key, then calculate key exchange
*/
struct packet_type_disc_s {
	struct packet_header_s header;
	struct peer_s peer;
	struct ciphermask_s ciphermask; //all capable/allowed bits are set
} __attribute__((packed));

struct packet_type_discReply_s {
	struct packet_header_s header;
	struct peer_s peer;
	struct ciphermask_s ciphermask; //only a single bit set for selected mode
	uint8_t key_ephemeral[32]; //optional, only if common cipher is found
} __attribute__((packed));

struct packet_type_discHandshake_s {
	struct packet_header_s header;
	struct peer_s peer;
	uint8_t key_ephemeral[32]; //optional, only if common cipher is found
} __attribute__((packed));

struct packet_type_ack_s {
	struct packet_header_s header;
	uint32_t puid;
} __attribute__((packed));

struct packet_type_nack_s {
	struct packet_header_s header;
	uint32_t puid;
} __attribute__((packed));

struct packet_int_s {
	union {
		struct packet_header_s header;
		struct packet_type_data_s asData;
		struct packet_type_disc_s asDisc;
		struct packet_type_discReply_s asDiscReply;
		struct packet_type_discHandshake_s asDiscHandshake;
		struct packet_type_ack_s asAck;
		struct packet_type_nack_s asNack;
		uint8_t raw[DRV_MESH__PACKET_SIZE_MAX];
	};
} __attribute__((packed));

struct packet_s {
	uint16_t totalLen;
	uint16_t dataLen;
	bool crcEnabled;
	struct packet_int_s payload;
};

/* static struct packet_data_s {
	uint16_t len;
	uint8_t buf[DRV_MESH__PACKET_SIZE_MAX];
}; */

struct packet_ext_s {
	ip_t ip;
	enum packet_status_e status;
	enum drv_lora_codingRate_e codingRate;
	struct packet_s packet;
};

#if defined (__cplusplus)
}
#endif
#endif // DRV_MESH_PRIVATE_H