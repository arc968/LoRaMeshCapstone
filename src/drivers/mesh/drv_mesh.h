#ifndef DRV_MESH_H
#define DRV_MESH_H
#if defined (__cplusplus)
extern "C" {
#endif

#include "../../lib/ip/lib_ip.h"

#include <stdint.h>

#define DRV_MESH__PACKET_SIZE_MAX 256

enum drv_mesh_error_e {
	DRV_MESH_ERR__NONE = 0,
	DRV_MESH_ERR__MESSAGE_TOO_LARGE,
	DRV_MESH_ERR__BUFFER_FULL,
};

struct drv_mesh_packet_s {
	ip_t ip;
	uint16_t len;
	uint8_t buf[DRV_MESH__PACKET_SIZE_MAX];
};

void drv_mesh_init(void (*func_onRecv_ptr)(ip_t *));

enum drv_mesh_error_e drv_mesh_send(uint32_t ip, uint16_t len, uint8_t * buf);

#if defined (__cplusplus)
}
#endif
#endif // DRV_MESH_H