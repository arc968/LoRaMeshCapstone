#ifndef DRV_MESH_H
#define DRV_MESH_H
#if defined (__cplusplus)
extern "C" {
#endif

#include "../../lib/ip/lib_ip.h"

#include <stdint.h>

#define DRV_MESH__MESSAGE_SIZE_MAX 128

enum drv_mesh_error_e {
	DRV_MESH_ERR__NONE = 0,
	DRV_MESH_ERR__MESSAGE_TOO_LARGE,
	DRV_MESH_ERR__BUFFER_FULL,
	DRV_MESH_ERR__NO_PEERS,
	DRV_MESH_ERR__NO_GATEWAY,
	DRV_MESH_ERR__NO_ROUTE,
};

struct drv_mesh_packet_s {
	ipv4_t ip;
	uint16_t port;
	uint8_t len;
	uint8_t buf[DRV_MESH__MESSAGE_SIZE_MAX];
};

struct drv_mesh_stats_s {
	uint32_t packets_dropped;
	uint32_t packets_forwarded;
	uint32_t corrupt_packets;
	uint32_t broadcasts_sent;
	uint32_t broadcasts_recv;
	
	lib_datetime_realtime_t last_packet_send;
	lib_datetime_realtime_t last_packet_recv;
	lib_datetime_realtime_t last_packet_disc_send;
	lib_datetime_realtime_t last_packet_disc_recv;
	lib_datetime_realtime_t last_packet_discReply_send;
	lib_datetime_realtime_t last_packet_discReply_recv;
	lib_datetime_realtime_t last_packet_link_send;
	lib_datetime_realtime_t last_packet_link_recv;

	uint32_t peer_count;
};

void drv_mesh_init(void (*func_onRecv_ptr)(struct drv_mesh_packet_s *));

enum drv_mesh_error_e drv_mesh_send(ipv4_t ip, uint16_t port,
	uint8_t * buf, uint8_t len);

void drv_mesh_getStats(struct drv_mesh_stats_s *);

//uint8_t drv_mesh_getMaxMessageSize(void);

#if defined (__cplusplus)
}
#endif
#endif // DRV_MESH_H