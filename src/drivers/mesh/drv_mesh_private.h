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

typedef uint64_t peer_uid_t;

#include "drv_mesh_air.h"

enum appointment_type_e {
	APPT_DISC_SEND,
	APPT_DISC_RECV,
	APPT_DISC_REPLY_SEND,
	APPT_DISC_REPLY_RECV,
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
	peer_uid_t uid;
	uint8_t key[32];
};

struct appointment_s {
	struct appointment_s * next;
	
	lib_datetime_realtime_t realtime;
	
	enum appointment_type_e type;
	
	struct peer_s peer;
	
	//channel_t channel;
	uint16_t preamble;
	uint64_t frequency;
	enum drv_lora_bandwidth_e bandwidth;
	enum drv_lora_spreadingFactor_e spreadingFactor;
	enum drv_lora_codingRate_e codingRate;
} __attribute__((packed));

enum packet_status_e {
	PACKET_FREE,
	PACKET_READY
};

struct packet_type_raw_s {
	uint8_t size;
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

/* struct packet_s {
	uint16_t totalLen;
	uint16_t dataLen;
	bool crcEnabled;
	struct packet_raw_s payload;
}; */

/* static struct packet_data_s {
	uint16_t len;
	uint8_t buf[DRV_MESH__PACKET_SIZE_MAX];
}; */

struct packet_internal_s {
	enum packet_status_e status;
	struct packet_type_raw_s packet;
};

#if defined (__cplusplus)
}
#endif
#endif // DRV_MESH_PRIVATE_H