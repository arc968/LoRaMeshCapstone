#ifndef DRV_MESH_CONFIG_H
#define DRV_MESH_CONFIG_H
#if defined (__cplusplus)
extern "C" {
#endif

#define BUFFER_PEERS_SIZE 8
#define BUFFER_ROUTES_SIZE 16
#define BUFFER_RECENT_PAYLOADS_SIZE 16
#define HASHMAP_ROUTES_BUCKET_COUNT 16
#define ROUTE_PEER_COUNT 4
//#define BUFFER_RELAY_SIZE 10
//#define BUFFER_INBOUND_SIZE 3
//#define BUFFER_OUTBOUND_SIZE 3
#define BUFFER_PACKETS_SIZE 40
#define BUFFER_OUTBOUND_PACKETS_SIZE 4
#define BUFFER_PER_PEER_PACKETS_SIZE 8
#define BUFFER_PER_PEER_PACKETS_MIN_SPACE 2
#define BUFFER_APPOINTMENTS_SIZE (BUFFER_PEERS_SIZE*2 + 2)

#define FREQ_500kHz 500000
#define FREQ_250kHz 250000
#define FREQ_125kHz 125000
#define FREQ_62_5kHz 62500

#define DISC_FRAC_START 4
#define DISC_FRAC_END 20

#define MAX_RECV_BAILOUT_TIME 5000

#define PACKET_DROP_TTL 5

//#define PREAMBLE_LENGTH 8192
#define PREAMBLE_MS 150
#define PADDING_MS PREAMBLE_MS
#define PACKET_TOA_MAX_GENERATE 2000
#define PACKET_TOA_MAX_SEND PACKET_TOA_MAX_GENERATE

#define SCHEDULER_PRE_DISCOVERY_INTERVAL_MS 2500 //2500
#define SCHEDULER_PRE_DISCOVERY_WINDOW_MS 500 //500
#define DISCOVERY_INTERVAL_SECONDS 15
#define DISCOVERY_INTERVAL_MILLIS (DISCOVERY_INTERVAL_SECONDS*1000)
#define DISCOVERY_PADDING PACKET_TOA_MAX_GENERATE //(PREAMBLE_MS + (2*PADDING_MS)) + 500
//(DISCOVERY_INTERVAL_MILLIS - DISCOVERY_PADDING) must be greater than PACKET_TOA_MAX_GENERATE

#define LORA_US_FREQ 902000000
#define LORA_US_FREQ_MIN LORA_US_FREQ
#define LORA_US_FREQ_MAX 928000000
#define LORA_US_FREQ_WIDTH (LORA_US_FREQ_MAX - LORA_US_FREQ_MIN)
#define LORA_US_CHANNELCOUNT_500kHz 32
#define LORA_US_CHANNELCOUNT_250kHz 64
#define LORA_US_CHANNELCOUNT_125kHz 128
#define LORA_US_CHANNELCOUNT_62_5kHz 256
#define LORA_US_PADDING_500kHz ((uint64_t)(((LORA_US_FREQ_WIDTH - (LORA_US_CHANNELCOUNT_500kHz * FREQ_500kHz)) / LORA_US_CHANNELCOUNT_500kHz) / 2))
#define LORA_US_PADDING_250kHz ((uint64_t)(((LORA_US_FREQ_WIDTH - (LORA_US_CHANNELCOUNT_250kHz * FREQ_250kHz)) / LORA_US_CHANNELCOUNT_250kHz) / 2))
#define LORA_US_PADDING_125kHz ((uint64_t)(((LORA_US_FREQ_WIDTH - (LORA_US_CHANNELCOUNT_125kHz * FREQ_125kHz)) / LORA_US_CHANNELCOUNT_125kHz) / 2))
#define LORA_US_PADDING_62_5kHz ((uint64_t)(((LORA_US_FREQ_WIDTH - (LORA_US_CHANNELCOUNT_62_5kHz * FREQ_62_5kHz)) / LORA_US_CHANNELCOUNT_62_5kHz) / 2))

#define DRV_MESH__PACKET_SIZE_MAX 255
#define DRV_MESH__PAYLOAD_SIZE_MAX 192
#define DRV_MESH__MESSAGE_SIZE_MAX 128

const uint8_t DRV_MESH__MAX_MESSAGE_SIZE = DRV_MESH__MESSAGE_SIZE_MAX;

const ipv4_t GATEWAY_IP = {10, 0, 0, 1};

static enum drv_lora_bandwidth_e drv_lora_bandwidth_e_arr[] = {
	DRV_LORA_BW__500kHz,
	DRV_LORA_BW__250kHz,
	DRV_LORA_BW__125kHz,
	DRV_LORA_BW__62_5kHz,
};
static enum drv_lora_spreadingFactor_e drv_lora_spreadingFactor_e_arr[] = {
	//DRV_LORA_SF__6, //do not use
	DRV_LORA_SF__7,
	DRV_LORA_SF__8,
	DRV_LORA_SF__9,
	DRV_LORA_SF__10,
	DRV_LORA_SF__11,
	DRV_LORA_SF__12,
};
static enum drv_lora_codingRate_e drv_lora_codingRate_e_arr[] = {
	DRV_LORA_CR__4_5,
	DRV_LORA_CR__4_6,
	DRV_LORA_CR__4_7,
	DRV_LORA_CR__4_8,
};

#if defined (__cplusplus)
}
#endif
#endif // DRV_MESH_CONFIG_H