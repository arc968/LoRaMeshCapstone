#ifndef DRV_LORA_H
#define DRV_LORA_H
#if defined (__cplusplus)
extern "C" {
#endif

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "../../hal/hal_common.h"
#include "../../hardware/hardware.h"

enum drv_lora_region_e {
	DRV_LORA_REGION_US915,
	DRV_LORA_REGION_EU868,
	DRV_LORA_REGION_433,
};

enum drv_lora_bandwidth_e {
	DRV_LORA_BW__62_5kHz,
	DRV_LORA_BW__125kHz,
	DRV_LORA_BW__250kHz,
	DRV_LORA_BW__500kHz,
};

enum drv_lora_spreadingFactor_e {
	DRV_LORA_SF__6 = 6,
	DRV_LORA_SF__7 = 7,
	DRV_LORA_SF__8 = 8,
	DRV_LORA_SF__9 = 9,
	DRV_LORA_SF__10 = 10,
	DRV_LORA_SF__11 = 11,
	DRV_LORA_SF__12 = 12,
};

enum drv_lora_codingRate_e {
	DRV_LORA_CR__4_5 = 1, // 4/5
	DRV_LORA_CR__4_6 = 2, // 4/6
	DRV_LORA_CR__4_7 = 3, // 4/7
	DRV_LORA_CR__4_8 = 4, // 4/8
};

enum drv_lora_mode_e {
	DRV_LORA_MODE__IDLE,
	DRV_LORA_MODE__SLEEP,
	DRV_LORA_MODE__RECV,
	DRV_LORA_MODE__SEND,
};

struct drv_lora_packet_s {
	uint8_t size;
	uint8_t buf[255];
};

struct drv_lora_s {
	pin_t pin;
	enum drv_lora_mode_e mode;
	enum drv_lora_region_e region;
	enum drv_lora_bandwidth_e bandwidth;
	enum drv_lora_spreadingFactor_e spreadingFactor;
	enum drv_lora_codingRate_e codingRate;
	uint16_t txpower;
	uint16_t preamblelen;
};

void drv_lora_init(struct drv_lora_s * handle, enum drv_lora_region_e region, pin_t pin);

void drv_lora_setMode(struct drv_lora_s * handle, enum drv_lora_mode_e mode);
enum drv_lora_mode_e drv_lora_getMode(struct drv_lora_s * handle);

void drv_lora_setTxPower(struct drv_lora_s * handle, uint16_t dB);
uint16_t drv_lora_getTxPower(struct drv_lora_s * handle);

void drv_lora_setPreamble(struct drv_lora_s * handle, uint16_t ms);
uint16_t drv_lora_getPreamble(struct drv_lora_s * handle);

void drv_lora_setBandwidth(struct drv_lora_s * handle, enum drv_lora_bandwidth_e);
enum drv_lora_bandwidth_e drv_lora_getBandwidth(struct drv_lora_s * handle);

void drv_lora_setSpreadingFactor(struct drv_lora_s * handle, enum drv_lora_spreadingFactor_e);
enum drv_lora_spreadingFactor_e drv_lora_getSpreadingFactor(struct drv_lora_s * handle);

void drv_lora_setCodingRate(struct drv_lora_s * handle, enum drv_lora_codingRate_e);
enum drv_lora_codingRate_e drv_lora_getCodingRate(struct drv_lora_s * handle);

uint16_t drv_lora_recvPacketCount(struct drv_lora_s * handle);
void drv_lora_getRecvPacket(struct drv_lora_s * handle, struct drv_lora_packet_s * packet);

void drv_lora_queuePacket(struct drv_lora_s * handle, struct drv_lora_packet_s * packet);

#if defined (__cplusplus)
}
#endif
#endif // DRV_LORA_H
