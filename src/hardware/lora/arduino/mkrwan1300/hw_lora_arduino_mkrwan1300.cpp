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
	// registers
	#define REG_FIFO                 0x00
	#define REG_OP_MODE              0x01
	#define REG_FRF_MSB              0x06
	#define REG_FRF_MID              0x07
	#define REG_FRF_LSB              0x08
	#define REG_PA_CONFIG            0x09
	#define REG_OCP                  0x0b
	#define REG_LNA                  0x0c
	#define REG_FIFO_ADDR_PTR        0x0d
	#define REG_FIFO_TX_BASE_ADDR    0x0e
	#define REG_FIFO_RX_BASE_ADDR    0x0f
	#define REG_FIFO_RX_CURRENT_ADDR 0x10
	#define REG_IRQ_FLAGS            0x12
	#define REG_RX_NB_BYTES          0x13
	#define REG_MODEM_STATUS         0x18
	#define REG_PKT_SNR_VALUE        0x19
	#define REG_PKT_RSSI_VALUE       0x1a
	#define REG_RSSI_VALUE           0x1b
	#define REG_MODEM_CONFIG_1       0x1d
	#define REG_MODEM_CONFIG_2       0x1e
	#define REG_PREAMBLE_MSB         0x20
	#define REG_PREAMBLE_LSB         0x21
	#define REG_PAYLOAD_LENGTH       0x22
	#define REG_MODEM_CONFIG_3       0x26
	#define REG_FREQ_ERROR_MSB       0x28
	#define REG_FREQ_ERROR_MID       0x29
	#define REG_FREQ_ERROR_LSB       0x2a
	#define REG_RSSI_WIDEBAND        0x2c
	#define REG_DETECTION_OPTIMIZE   0x31
	#define REG_INVERTIQ             0x33
	#define REG_DETECTION_THRESHOLD  0x37
	#define REG_SYNC_WORD            0x39
	#define REG_INVERTIQ2            0x3b
	#define REG_DIO_MAPPING_1        0x40
	#define REG_VERSION              0x42
	#define REG_PA_DAC               0x4d

	// modes
	#define MODE_LONG_RANGE_MODE     0x80
	#define MODE_SLEEP               0x00
	#define MODE_STDBY               0x01
	#define MODE_TX                  0x03
	#define MODE_RX_CONTINUOUS       0x05
	#define MODE_RX_SINGLE           0x06

	// PA config
	#define PA_BOOST                 0x80

	// IRQ masks
	#define IRQ_TX_DONE_MASK           0x08
	#define IRQ_PAYLOAD_CRC_ERROR_MASK 0x20
	#define IRQ_RX_DONE_MASK           0x40

	#define RF_MID_BAND_THRESHOLD    525E6
	#define RSSI_OFFSET_HF_PORT      157
	#define RSSI_OFFSET_LF_PORT      164

	#define MAX_PKT_LENGTH           255
#else
	
#endif //HW_ARDUINO


void drv_lora_init(struct drv_lora_s * handle, uint64_t freq) {
	
	#ifdef HW_ARDUINO
		while (!LoRa.begin(freq));
		//LoRa.enableCrc();
	#else
		
	#endif //HW_ARDUINO
	/*handle->pin = 2`;
	handle->frequency = freq;
	handle->bandwidth = DRV_LORA_BW__125kHz;
	handle->spreadingFactor = DRV_LORA_SF__7;
	handle->codingRate = DRV_LORA_CR__4_5;
	handle->txpower = 7;
	handle->preamblelen = 8;*/
	
}

/*pin_t drv_lora_getPin(struct drv_lora_s * handle) {
	
	return handle->pin;
	
}*/

void drv_lora_setMode(struct drv_lora_s * handle, enum drv_lora_mode_e mode) {
	
	switch (mode) {
		case DRV_LORA_MODE__IDLE:
			#ifdef HW_ARDUINO
				LoRa.idle();
			#else
				
			#endif //HW_ARDUINO
			break;
		case DRV_LORA_MODE__IDLE_CLEAR:
			#ifdef HW_ARDUINO
				{
					// clear IRQ's
					int tirqFlags = drv_lora_readRegister(REG_IRQ_FLAGS);
					drv_lora_writeRegister(REG_IRQ_FLAGS, tirqFlags);
					LoRa.idle();
				}
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
		case DRV_LORA_MODE__RECV_ONCE:
			#ifdef HW_ARDUINO
				{
					// clear IRQ's
					int tirqFlags = drv_lora_readRegister(REG_IRQ_FLAGS);
					drv_lora_writeRegister(REG_IRQ_FLAGS, tirqFlags);
					// reset FIFO address
					drv_lora_writeRegister(REG_FIFO_ADDR_PTR, 0);
					// put in single RX mode
					drv_lora_writeRegister(REG_OP_MODE, MODE_LONG_RANGE_MODE | MODE_RX_SINGLE);
				}
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

/* uint16_t drv_lora_available(struct drv_lora_s * handle) {
	
	#ifdef HW_ARDUINO
		return LoRa.available();
	#else
	
	#endif //HW_ARDUINO
	
} */

/* uint16_t drv_lora_parsePacket(struct drv_lora_s * handle) {
	
	#ifdef HW_ARDUINO
		return LoRa.parsePacket();
	#else
	
	#endif //HW_ARDUINO
	
} */

uint8_t drv_lora_getRawPacket(struct drv_lora_s * handle, uint8_t * buf) {
	
	#ifdef HW_ARDUINO
		uint8_t sizeOut = 0;
		uint8_t size = LoRa.parsePacket();
		if (size > 0) {
			for (uint16_t i=0; LoRa.available() && i < size; i++) {
				buf[i] = LoRa.read();
				sizeOut++;
			}
		}
		return sizeOut;
	#else
		
	#endif //HW_ARDUINO
	
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

void drv_lora_sendRawPacket_async(struct drv_lora_s * handle, uint8_t * buf, size_t size) {
	#ifdef HW_ARDUINO
		//while (LoRa.beginPacket());
		if (LoRa.beginPacket()) {
			LoRa.write(buf, size);
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

bool drv_lora_isSignalDetected(struct drv_lora_s * handle) { 
	return drv_lora_readRegister(REG_MODEM_STATUS) & (0x1 << 0);
}

bool drv_lora_isSignalSynchronized(struct drv_lora_s * handle) { 
	return drv_lora_readRegister(REG_MODEM_STATUS) & (0x1 << 1);
}

bool drv_lora_isHeaderValid(struct drv_lora_s * handle) {
	return drv_lora_readRegister(REG_MODEM_STATUS) & (0x1 << 3);
}

uint8_t drv_lora_getStatusReg(struct drv_lora_s * handle) {
	return drv_lora_readRegister(REG_MODEM_STATUS);
}

bool drv_lora_isRecvTimeout(struct drv_lora_s * handle) {
	//return drv_lora_readRegister(REG_MODEM_STATUS) & (0x1 << 3);
	uint8_t tirqFlags = drv_lora_readRegister(REG_IRQ_FLAGS);
	//drv_lora_writeRegister(REG_IRQ_FLAGS, tirqFlags);
	return tirqFlags & (0x1 << 7);
}


uint8_t drv_lora_singleTransfer(uint8_t address, uint8_t value) {
	
	#ifdef HW_ARDUINO
		uint8_t response;

		digitalWrite(LORA_DEFAULT_SS_PIN, LOW);

		(&LORA_DEFAULT_SPI)->beginTransaction(SPISettings(LORA_DEFAULT_SPI_FREQUENCY, MSBFIRST, SPI_MODE0));
		(&LORA_DEFAULT_SPI)->transfer(address);
		response = (&LORA_DEFAULT_SPI)->transfer(value);
		(&LORA_DEFAULT_SPI)->endTransaction();

		digitalWrite(LORA_DEFAULT_SS_PIN, HIGH);

		return response;
	#else
		
	#endif //HW_ARDUINO
	
}

uint8_t drv_lora_readRegister(uint8_t address) {
	return drv_lora_singleTransfer(address & 0x7f, 0x00);
}

void drv_lora_writeRegister(uint8_t address, uint8_t value) {
	drv_lora_singleTransfer(address | 0x80, value);
}


#if defined (__cplusplus)
}
#endif

#endif // HW_LORA_ARDUINO_MKRWAN1300_H

#undef HW_LORA_ARDUINO_MKRWAN1300_CPP