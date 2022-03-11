#define HAL_LIB
#include "hal_i2c.h"

#ifdef HW_ARDUINO
	#include <Wire.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

bool hal_i2c_begun = 0;

void hal_i2c_begin(void) {
	if(!hal_i2c_begun) {
	#if defined(HW_ARDUINO)
		Wire.begin();
		hal_i2c_begun = 1;
	#elif defined(HW_MKRWAN1300_H)
		
	#elif defined(HW_RAK4260_H)
		
	#elif defined(HW_RAK4600_H)
			
	#elif defined(HW_RAK11300_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
	}
}

void hal_i2c_requestFrom(uint16_t address, uint16_t quantity, bool stop) {
	#if defined(HW_ARDUINO)
		Wire.requestFrom(address, quantity, stop);
	#elif defined(HW_MKRWAN1300_H)
		
	#elif defined(HW_RAK4260_H)
	
	#elif defined(HW_RAK4600_H)
			
	#elif defined(HW_RAK11300_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
}

void hal_i2c_beginTransmission(uint8_t address) {
	#if defined(HW_ARDUINO)
		Wire.beginTransmission(address);
	#elif defined(HW_MKRWAN1300_H)
		
	#elif defined(HW_RAK4260_H)
	
	#elif defined(HW_RAK4600_H)
			
	#elif defined(HW_RAK11300_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
}

uint8_t hal_i2c_endTransmission(bool stop) {
	#if defined(HW_ARDUINO)
		return Wire.endTransmission(stop);
	#elif defined(HW_MKRWAN1300_H)
		return 0; //TODO
	#elif defined(HW_RAK4260_H)
		return 0; //TODO
	#elif defined(HW_RAK4600_H)
		return 0; //TODO
	#elif defined(HW_RAK11300_H)
		return 0; //TODO
	#else
		#error "Hardware not yet implemented"
	#endif
}

void hal_i2c_write(uint8_t *buf, uint16_t length) {
	#if defined(HW_ARDUINO)
		Wire.write(buf, length);
	#elif defined(HW_MKRWAN1300_H)
		
	#elif defined(HW_RAK4260_H)
	
	#elif defined(HW_RAK4600_H)
			
	#elif defined(HW_RAK11300_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
}

uint16_t hal_i2c_available(void) {
	#if defined(HW_ARDUINO)
		return Wire.available();
	#elif defined(HW_MKRWAN1300_H)
		return 0; //TODO
	#elif defined(HW_RAK4260_H)
		return 0; //TODO
	#elif defined(HW_RAK4600_H)
		return 0; //TODO
	#elif defined(HW_RAK11300_H)
		return 0; //TODO
	#else
		#error "Hardware not yet implemented"
	#endif
}

uint8_t hal_i2c_read(void) {
	#if defined(HW_ARDUINO)
		return Wire.read();
	#elif defined(HW_MKRWAN1300_H)
		return 0; //TODO
	#elif defined(HW_RAK4260_H)
		return 0; //TODO
	#elif defined(HW_RAK4600_H)
		return 0; //TODO
	#elif defined(HW_RAK11300_H)
		return 0; //TODO
	#else
		#error "Hardware not yet implemented"
	#endif
}

void hal_i2c_setClock(uint32_t freq) {
	#if defined(HW_ARDUINO)
		Wire.setClock(freq);
	#elif defined(HW_MKRWAN1300_H)
		
	#elif defined(HW_RAK4260_H)
		
	#elif defined(HW_RAK4600_H)
			
	#elif defined(HW_RAK11300_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
}

void hal_i2c_onReceive() {
	#if defined(HW_ARDUINO)
		Wire.onReceive(hal_i2c_received);
	#elif defined(HW_MKRWAN1300_H)
		
	#elif defined(HW_RAK4260_H)
	
	#elif defined(HW_RAK4600_H)
			
	#elif defined(HW_RAK11300_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
}

void hal_i2c_onRequest(void (*handler)(void)) {
	#if defined(HW_ARDUINO)
		Wire.onRequest(handler);
	#elif defined(HW_MKRWAN1300_H)
		
	#elif defined(HW_RAK4260_H)
	
	#elif defined(HW_RAK4600_H)
			
	#elif defined(HW_RAK11300_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
}

void hal_i2c_received(int numBytes) {
	//TODO
}

#ifdef __cplusplus
}
#endif //__cplusplus