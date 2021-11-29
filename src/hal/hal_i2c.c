#define HAL_LIB
#include "hal_i2c.h"

#ifdef HW_ARDUINO
	#include <Wire.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

void hal_i2c_begin(void) {
	#if defined(HW_ARDUINO)
		Wire.begin();
	#elif defined(HW_IBUG_H)
	
	#else
		#error "Hardware not yet implemented"
	#endif
}

void hal_i2c_requestFrom(uint16_t address, uint16_t quantity, bool stop) {
	#if defined(HW_ARDUINO)
		Wire.requestFrom(address, quantity, stop);
	#elif defined(HW_IBUG_H)
	
	#else
		#error "Hardware not yet implemented"
	#endif
}

void hal_i2c_beginTransmission(uint16_t address) {
	#if defined(HW_ARDUINO)
		Wire.beginTransmission(address);
	#elif defined(HW_IBUG_H)
	
	#else
		#error "Hardware not yet implemented"
	#endif
}

uint8_t hal_i2c_endTransmission(bool stop) {
	#if defined(HW_ARDUINO)
		return Wire.endTransmission(stop);
	#elif defined(HW_IBUG_H)
		return 0; //TODO
	#else
		#error "Hardware not yet implemented"
	#endif
}

void hal_i2c_write(uint8_t *buf, uint16_t length) {
	#if defined(HW_ARDUINO)
		Wire.write(buf, length);
	#elif defined(HW_IBUG_H)
	
	#else
		#error "Hardware not yet implemented"
	#endif
}

uint16_t hal_i2c_available(void) {
	#if defined(HW_ARDUINO)
		return Wire.available();
	#elif defined(HW_IBUG_H)
		return 0; //TODO
	#else
		#error "Hardware not yet implemented"
	#endif
}

uint8_t hal_i2c_read(void) {
	#if defined(HW_ARDUINO)
		return Wire.read();
	#elif defined(HW_IBUG_H)
		return 0; //TODO
	#else
		#error "Hardware not yet implemented"
	#endif
}

void hal_i2c_setClock(uint32_t freq) {
	#if defined(HW_ARDUINO)
		Wire.SetClock(freq);
	#elif defined(HW_IBUG_H)
	
	#else
		#error "Hardware not yet implemented"
	#endif
}

void hal_i2c_onReceive(uint32_t numBytes) {
	#if defined(HW_ARDUINO)
		Wire.onReceive(numBytes);
	#elif defined(HW_IBUG_H)
	
	#else
		#error "Hardware not yet implemented"
	#endif
}

void hal_i2c_onRequest(void (*handler)(void)) {
	#if defined(HW_ARDUINO)
		Wire.onRequest(handler);
	#elif defined(HW_IBUG_H)
	
	#else
		#error "Hardware not yet implemented"
	#endif
}


#ifdef __cplusplus
}
#endif //__cplusplus