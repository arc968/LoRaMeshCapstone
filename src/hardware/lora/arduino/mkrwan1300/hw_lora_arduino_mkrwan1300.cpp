#define HW_LORA_ARDUINO_MKRWAN1300_CPP
//#include "hw_lora_arduino_mkrwan1300.h"
#include "../../../hardware.h"

#ifdef HW_LORA_ARDUINO_MKRWAN1300_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "../../../../hal/hal.h"
#include "../../../../lib/byteorder/lib_byteorder.h"
#include "../../../../drivers/lora/drv_lora.h"
#include "../../../../drivers/timer/drv_timer.h"
#include "../../../../drivers/sched/drv_sched.h"

#if defined (__cplusplus)
extern "C" {
#endif

#include <LoRa.h>


void drv_lora_init(struct drv_lora_s * handle, enum drv_lora_region_e region, pin_t pin) {
	
	while (!LoRa.begin(region));
	handle->pin = pin;
	/*handle->region = region;
	handle->bandwidth = DRV_LORA_BW__125kHz;
	handle->spreadingFactor = DRV_LORA_SF__7;
	handle->codingRate = DRV_LORA_CR__4_5;
	handle->txpower = 7;
	handle->preamblelen = 8;*/
	
}

void drv_lora_setMode(struct drv_lora_s * handle, enum drv_lora_mode_e mode) {
	
	switch (mode) {
		case DRV_LORA_MODE__IDLE:
			LoRa.idle();
			break;
		case DRV_LORA_MODE__SLEEP:
			LoRa.sleep();
			break;
		case DRV_LORA_MODE__RECV:
			
			break;
		case DRV_LORA_MODE__SEND:
			
			break;
		default:
			LoRa.idle();
			//mode = DRV_LORA_MODE__IDLE;
	}
	
	//handle->mode = mode;
	
}
/*enum drv_lora_mode_e drv_lora_getMode(struct drv_lora_s * handle) {
	
	return handle->mode;
	
}*/

void drv_lora_setTxPower(struct drv_lora_s * handle, uint16_t dB) {
	
	LoRa.setTxPower(dB);
	//handle->txpower = dB;
	
}
/*uint16_t drv_lora_getTxPower(struct drv_lora_s * handle) {
	
	return handle->txpower;
	
}*/

void drv_lora_setPreamble(struct drv_lora_s * handle, uint16_t ms) {
	
	if (ms > 6 && ms < 65535) {
		LoRa.setPreambleLength(ms);
		//handle->preamblelen = ms;
	}
	
}
/*uint16_t drv_lora_getPreamble(struct drv_lora_s * handle) {
	
	return handle->preamblelen;
	
}*/

void drv_lora_setBandwidth(struct drv_lora_s * handle, enum drv_lora_bandwidth_e bw) {
	
	LoRa.setSignalBandwidth(bw);
	//handle->bandwidth = bw;
	
}
/*enum drv_lora_bandwidth_e drv_lora_getBandwidth(struct drv_lora_s * handle) {
	
	return handle->bandwidth;
	
}*/

void drv_lora_setSpreadingFactor(struct drv_lora_s * handle, enum drv_lora_spreadingFactor_e sf) {
	
	LoRa.setSpreadingFactor(sf);
	//handle->spreadingFactor = sf;
	
}
/*enum drv_lora_spreadingFactor_e drv_lora_getSpreadingFactor(struct drv_lora_s * handle) {
	
	return handle->spreadingFactor;
	
}*/

void drv_lora_setCodingRate(struct drv_lora_s * handle, enum drv_lora_codingRate_e cr) {
	
	LoRa.setCodingRate4(cr);
	//handle->codingRate = cr;
	
}
/*enum drv_lora_codingRate_e drv_lora_getCodingRate(struct drv_lora_s * handle) {
	
	return handle->codingRate;
	
}*/

void drv_lora_recvPacket(struct drv_lora_s * handle, struct drv_lora_packet_s * packet) {
	
	uint8_t indx = 0;
	
	if (LoRa.parsePacket(packet->size)) {
		while (LoRa.available() && indx < packet->size) {
			
			packet->buf[indx] = LoRa.read();
			
		}
		
		packet->rssi = LoRa.packetRssi();
		packet->snr = LoRa.packetSnr();
		packet->freqerr = LoRa.packetFrequencyError();
		
		indx++;
		
	}
	
	if (indx == 0) {
		packet->size = 0;
	}
	else if (indx < packet->size-1) {
		packet->size = indx + 1;
	}
	
}

void drv_lora_sendPacket(struct drv_lora_s * handle, struct drv_lora_packet_s * packet) {
	
	while (LoRa.beginPacket());
	
	LoRa.write(packet->buf, packet->size);
	
	LoRa.endPacket();
	
}

#if defined (__cplusplus)
}
#endif

#endif // HW_LORA_ARDUINO_MKRWAN1300_H

#undef HW_LORA_ARDUINO_MKRWAN1300_CPP