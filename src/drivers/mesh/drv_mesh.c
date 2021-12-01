#include "../../hal/hal.h"
#include "../gps/drv_gps.h"
#include "../lora/drv_lora.h"
#include "../sched/drv_sched.h"
#include "drv_mesh.h"

#define DRV_MESH_PEER_COUNT_MAX 16
#define DRV_MESH_BUFFER_RELAY_SIZE 10
#define DRV_MESH_BUFFER_INBOUND_SIZE 3
#define DRV_MESH_BUFFER_OUTBOUND_SIZE 3

#define DRV_MESH_UID_SIZE 4

enum packet_status_e {
	PACKET_FREE,
	PACKET_READY
};

struct peer_s {
	ip_t ip;
	uint8_t uid[DRV_MESH_UID_SIZE];
};

struct packet_ext_s {
	enum packet_status_e status;
	struct drv_mesh_packet_s packet;
};

static struct state_s {
	ip_t ip;
	struct peer_s peers[DRV_MESH_PEER_COUNT_MAX];
	
	uint8_t buf_relay_head;
	uint8_t buf_relay_tail;
	struct packet_ext_s buf_relay[DRV_MESH_BUFFER_RELAY_SIZE];
	
	uint8_t buf_inbound_head;
	uint8_t buf_inbound_tail;
	struct packet_ext_s buf_inbound[DRV_MESH_BUFFER_INBOUND_SIZE];
	
	uint8_t buf_outbound_head;
	uint8_t buf_outbound_tail;
	struct packet_ext_s buf_outbound[DRV_MESH_BUFFER_OUTBOUND_SIZE];
} state;

void drv_mesh_init(void) {
	//initialize datastructures
	
	//initialize GPS
	
	//configure GPS for timekeeping mode as appropriate
	
	//enable PPS interrupt handler (schedules mesh handler a few seconds before next run time
	
	//initialize LoRa radio
	
	//configure LoRa radio
}

static uint64_t getCenterFrequency(uint16_t channel, uint16_t bandwidth) {
	
}

static uint16_t getChannel() {
	
}