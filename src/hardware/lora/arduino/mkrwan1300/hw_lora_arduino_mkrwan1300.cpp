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

#ifdef HW_ARDUINO
	#include <LoRa.h>
#else
	
#endif //HW_ARDUINO


void drv_lora_init(struct drv_lora_s * handle, uint64_t freq, pin_t pin) {
	
	#ifdef HW_ARDUINO
		while (!LoRa.begin(freq));
	#else
		
	#endif //HW_ARDUINO
	handle->pin = pin;
	/*handle->frequency = freq;
	handle->bandwidth = DRV_LORA_BW__125kHz;
	handle->spreadingFactor = DRV_LORA_SF__7;
	handle->codingRate = DRV_LORA_CR__4_5;
	handle->txpower = 7;
	handle->preamblelen = 8;*/
	
}

void drv_lora_setMode(struct drv_lora_s * handle, enum drv_lora_mode_e mode) {
	
	switch (mode) {
		case DRV_LORA_MODE__IDLE:
			#ifdef HW_ARDUINO
				LoRa.idle();
			#else
				
			#endif //HW_ARDUINO
			break;
		case DRV_LORA_MODE__SLEEP:
			#ifdef HW_ARDUINO
				LoRa.sleep();
			#else
				
			#endif //HW_ARDUINO
			break;
		case DRV_LORA_MODE__RECV:
			#ifdef HW_ARDUINO
				
			#else
				
			#endif //HW_ARDUINO
			break;
		case DRV_LORA_MODE__SEND:
			#ifdef HW_ARDUINO
				
			#else
				
			#endif //HW_ARDUINO
			break;
		default:
			#ifdef HW_ARDUINO
				LoRa.idle();
			#else
				
			#endif //HW_ARDUINO
			//mode = DRV_LORA_MODE__IDLE;
	}
	
	//handle->mode = mode;
	
}
/*enum drv_lora_mode_e drv_lora_getMode(struct drv_lora_s * handle) {
	
	return handle->mode;
	
}*/

void drv_lora_setTxPower(struct drv_lora_s * handle, uint16_t dB) {
	
	#ifdef HW_ARDUINO
		LoRa.setTxPower(dB);
	#else
		
	#endif //HW_ARDUINO
	
	//handle->txpower = dB;
	
}
/*uint16_t drv_lora_getTxPower(struct drv_lora_s * handle) {
	
	return handle->txpower;
	
}*/

void drv_lora_setPreamble(struct drv_lora_s * handle, uint16_t symbols) {
	
	if (symbols >= 6 && symbols <= 65535) {
		#ifdef HW_ARDUINO
			LoRa.setPreambleLength(symbols);
		#else
			
		#endif //HW_ARDUINO
		
		//handle->preamblelen = ms;
	}
	
}
/*uint16_t drv_lora_getPreamble(struct drv_lora_s * handle) {
	
	return handle->preamblelen;
	
}*/

void drv_lora_setBandwidth(struct drv_lora_s * handle, enum drv_lora_bandwidth_e bw) {
	
	#ifdef HW_ARDUINO
		LoRa.setSignalBandwidth(bw);
	#else
		
	#endif //HW_ARDUINO
	
	//handle->bandwidth = bw;
	
}
/*enum drv_lora_bandwidth_e drv_lora_getBandwidth(struct drv_lora_s * handle) {
	
	return handle->bandwidth;
	
}*/

void drv_lora_setSpreadingFactor(struct drv_lora_s * handle, enum drv_lora_spreadingFactor_e sf) {
	
	#ifdef HW_ARDUINO
		LoRa.setSpreadingFactor(sf);
	#else
		
	#endif //HW_ARDUINO
	
	//handle->spreadingFactor = sf;
	
}
/*enum drv_lora_spreadingFactor_e drv_lora_getSpreadingFactor(struct drv_lora_s * handle) {
	
	return handle->spreadingFactor;
	
}*/

void drv_lora_setCodingRate(struct drv_lora_s * handle, enum drv_lora_codingRate_e cr) {
	
	#ifdef HW_ARDUINO
		LoRa.setCodingRate4(cr);
	#else
		
	#endif //HW_ARDUINO
	
	//handle->codingRate = cr;
	
}
/*enum drv_lora_codingRate_e drv_lora_getCodingRate(struct drv_lora_s * handle) {
	
	return handle->codingRate;
	
}*/

void drv_lora_setFrequency(struct drv_lora_s * handle, uint64_t freq) {
	
	#ifdef HW_ARDUINO
		LoRa.setFrequency(freq);
	#else
		
	#endif //HW_ARDUINO
	
	//handle->frequency = freq;
	
}
/*uint64_t drv_lora_getFrequency(struct drv_lora_s * handle) {
	
	return handle->frequency;
	
}*/

uint16_t drv_lora_available(struct drv_lora_s * handle) {
	#ifdef HW_ARDUINO
		return LoRa.available();
	#else
	
	#endif //HW_ARDUINO
}

uint16_t drv_lora_parsePacket(struct drv_lora_s * handle) {
	#ifdef HW_ARDUINO
		return LoRa.parsePacket();
	#else
	
	#endif //HW_ARDUINO
}

void drv_lora_getPacket(struct drv_lora_s * handle, struct drv_lora_packet_s * packet) {
	packet->size = 0;
	for (int i=0; LoRa.available() && i < 255; i++) {
		packet->buf[i] = LoRa.read();
		packet->size++;
	}
	packet->rssi = LoRa.packetRssi();
	packet->snr = LoRa.packetSnr();
	packet->freqerr = LoRa.packetFrequencyError();
}

void drv_lora_recvPacket(struct drv_lora_s * handle, struct drv_lora_packet_s * packet) {
	
	#ifdef HW_ARDUINO
		packet->size = 0;
		int size = LoRa.parsePacket();
		if (size > 0) {
			for (int i=0; LoRa.available() && i < size; i++) {
				packet->buf[i] = LoRa.read();
				packet->size++;
			}
			
			packet->rssi = LoRa.packetRssi();
			packet->snr = LoRa.packetSnr();
			packet->freqerr = LoRa.packetFrequencyError();
		}
	#else
		
	#endif //HW_ARDUINO
	
	
}

void drv_lora_sendPacket(struct drv_lora_s * handle, struct drv_lora_packet_s * packet) {
	
	#ifdef HW_ARDUINO
	//while (LoRa.beginPacket());
	if (LoRa.beginPacket()) {
		LoRa.write(packet->buf, packet->size);
		LoRa.endPacket();
	}
	#else
		
	#endif //HW_ARDUINO
	
}

void drv_lora_sendPacket_async(struct drv_lora_s * handle, struct drv_lora_packet_s * packet) {
	
	#ifdef HW_ARDUINO
	//while (LoRa.beginPacket());
	if (LoRa.beginPacket()) {
		LoRa.write(packet->buf, packet->size);
		LoRa.endPacket(true);
	}
	#else
		
	#endif //HW_ARDUINO
	
}

uint8_t drv_lora_random(struct drv_lora_s * handle) {
	
	#ifdef HW_ARDUINO
		return LoRa.random();
	#else
		
	#endif //HW_ARDUINO
	
}

#if defined (__cplusplus)
}
#endif

#endif // HW_LORA_ARDUINO_MKRWAN1300_H

#undef HW_LORA_ARDUINO_MKRWAN1300_CPP