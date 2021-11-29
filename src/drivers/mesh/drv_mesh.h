#ifndef DRV_MESH_H
#define DRV_MESH_H

#include <stdint.h>

#include "../../lib/ip/lib_ip.h"

#define DRV_MESH_PACKET_BUF_SIZE 256

struct drv_mesh_packet_s {
	ip_t ip;
	uint16_t len;
	uint8_t buf[DRV_MESH_PACKET_BUF_SIZE];
};

void drv_mesh_init(void);

void drv_mesh_setRecvHandler(void (*fun_ptr)(struct ip_t *));

int drv_mesh_send(uint32_t ip, uint16_t len, uint8_t * buf);

#endif // DRV_MESH_H