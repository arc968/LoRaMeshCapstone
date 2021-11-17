#define HAL_LIB
#include "hal_serial.h"

#ifdef HW_ARDUINO
	#include <HardwareSerial.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

bool hal_serial_ready(void) {
	#if defined(HW_ARDUINO)
		return (Serial);
	#elif defined(HW_IBUG_H)
		return 0; //TODO
	#else
		#error "Hardware not yet implemented"
	#endif
}

void hal_serial_begin(uint16_t baud) {
	#if defined(HW_ARDUINO)
		Serial.begin(baud);
	#elif defined(HW_IBUG_H)
	
	#else
		#error "Hardware not yet implemented"
	#endif
}

void hal_serial_end(void) {
	#if defined(HW_ARDUINO)
		Serial.end();
	#elif defined(HW_IBUG_H)
	
	#else
		#error "Hardware not yet implemented"
	#endif
}

void hal_serial_write(uint8_t *buff, uint16_t length) {
	#if defined(HW_ARDUINO)
		Serial.write(buff, length);
	#elif defined(HW_IBUG_H)
	
	#else
		#error "Hardware not yet implemented"
	#endif
}

size_t hal_serial_readBytes(uint8_t *buf, uint16_t length) {
	#if defined(HW_ARDUINO)
		return Serial.readBytes(buf, length);
	#elif defined(HW_IBUG_H)
		return 0; //TODO
	#else
		#error "Hardware not yet implemented"
	#endif
}

void hal_serial_flush(void) {
	#if defined(HW_ARDUINO)
		Serial.flush();
	#elif defined(HW_IBUG_H)
	
	#else
		#error "Hardware not yet implemented"
	#endif
}

void hal_serial_setTimeout(uint32_t mstime) {
	#if defined(HW_ARDUINO)
		Serial.setTimeout(mstime);
	#elif defined(HW_IBUG_H)
	
	#else
		#error "Hardware not yet implemented"
	#endif
}



#ifdef __cplusplus
}
#endif//__cplusplus