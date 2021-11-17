#define HAL_LIB
#include "hal_i2c.h"

#ifdef HW_ARDUINO
	#include <Wire.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

void hal_i2c_begin(uint16_t address) {
	#if defined(HW_ARDUINO)
		Wire.begin(address);
	#elif defined(HW_IBUG_H)
	
	#else
		#error "Hardware not yet implemented"
	#endif
}

void hal_i2c_request_from(uint16_t address, uint16_t quantity, bool stop) {
	#if defined(HW_ARDUINO)
		Wire.requestFrom(address, quantity, stop);
	#elif defined(HW_IBUG_H)
	
	#else
		#error "Hardware not yet implemented"
	#endif
}

void hal_i2c_begin_Transmission(uint16_t address) {
	#if defined(HW_ARDUINO)
		Wire.beginTransmission(address);
	#elif defined(HW_IBUG_H)
	
	#else
		#error "Hardware not yet implemented"
	#endif
}

uint8_t hal_i2c_end_transmission(bool stop) {
	#if defined(HW_ARDUINO)
		return Wire.endTransmission(stop);
	#elif defined(HW_IBUG_H)
	
	#else
		#error "Hardware not yet implemented"
	#endif
}

void hal_i2c_write(uint8_t *data, uint16_t length) {
	#if defined(HW_ARDUINO)
		Wire.write(data, length);
	#elif defined(HW_IBUG_H)
	
	#else
		#error "Hardware not yet implemented"
	#endif
}

uint16_t hal_i2c_available(void) {
	#if defined(HW_ARDUINO)
		return Wire.available();
	#elif defined(HW_IBUG_H)
	
	#else
		#error "Hardware not yet implemented"
	#endif
}

uint8_t hal_i2c_read(void) {
	#if defined(HW_ARDUINO)
		return Wire.read();
	#elif defined(HW_IBUG_H)
	
	#else
		#error "Hardware not yet implemented"
	#endif
}

void hal_i2c_set_clock(uint32_t freq) {
	#if defined(HW_ARDUINO)
		Wire.SetClock(freq);
	#elif defined(HW_IBUG_H)
	
	#else
		#error "Hardware not yet implemented"
	#endif
}

void hal_i2c_on_receive(uint32_t numBytes) {
	#if defined(HW_ARDUINO)
		Wire.onReceive(numBytes);
	#elif defined(HW_IBUG_H)
	
	#else
		#error "Hardware not yet implemented"
	#endif
}

void hal_i2c_on_request(void (*handler)(void)) {
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