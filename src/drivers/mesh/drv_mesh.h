#ifndef DRV_MESH_H
#define DRV_MESH_H
#if defined (__cplusplus)
extern "C" {
#endif

#include <stdint.h>

#include "../../lib/ip/lib_ip.h"

#define DRV_MESH_PACKET_SIZE_MAX 256

struct drv_mesh_packet_s {
	ip_t ip;
	uint16_t len;
	uint8_t buf[DRV_MESH_PACKET_SIZE_MAX];
};

enum drv_mesh_error_e {
	OK = 0,
	NONE = 0,
	ERR_MESSAGE_TOO_LARGE,
	ERR_BUFFER_FULL,
};

void drv_mesh_init(void);

void drv_mesh_setRecvHandler(void (*fun_ptr)(ip_t *));

enum drv_mesh_error_e drv_mesh_send(uint32_t ip, uint16_t len, uint8_t * buf);

#if defined (__cplusplus)
}
#endif
#endif // DRV_MESH_H