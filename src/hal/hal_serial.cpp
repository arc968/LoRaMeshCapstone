#define HAL_LIB
#include "hal_serial.h"

#ifdef HW_ARDUINO
	#include <HardwareSerial.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if defined(HW_ARDUINO)
const void * hal_serial0 = &Serial;
const void * hal_serial1 = &Serial1;
//const void * hal_serial2 = &Serial2;
//const void * hal_serial3 = &Serial3;
#endif

bool hal_serial_ready(void *handle) {
	#if defined(HW_ARDUINO)
		return static_cast<HardwareSerial*>(handle);
	#elif defined(HW_IBUG_H)
		return 0; //TODO
	#else
		#error "Hardware not yet implemented"
	#endif
}

void hal_serial_begin(void *handle, uint16_t baud) {
	#if defined(HW_ARDUINO)
		static_cast<HardwareSerial*>(handle)->begin(baud);
	#elif defined(HW_IBUG_H)
	
	#else
		#error "Hardware not yet implemented"
	#endif
}

void hal_serial_end(void *handle) {
	#if defined(HW_ARDUINO)
		static_cast<HardwareSerial*>(handle)->end();
	#elif defined(HW_IBUG_H)
	
	#else
		#error "Hardware not yet implemented"
	#endif
}

void hal_serial_write(void *handle,uint8_t *buf, uint16_t length) {
	#if defined(HW_ARDUINO)
		static_cast<HardwareSerial*>(handle)->write(buf, length);
	#elif defined(HW_IBUG_H)
	
	#else
		#error "Hardware not yet implemented"
	#endif
}

size_t hal_serial_readBytes(void *handle, uint8_t *buf, uint16_t length) {
	#if defined(HW_ARDUINO)
		return static_cast<HardwareSerial*>(handle)->readBytes((char*)buf, length);
	#elif defined(HW_IBUG_H)
		return 0; //TODO
	#else
		#error "Hardware not yet implemented"
	#endif
}

void hal_serial_flush(void *handle) {
	#if defined(HW_ARDUINO)
		static_cast<HardwareSerial*>(handle)->flush();
	#elif defined(HW_IBUG_H)
	
	#else
		#error "Hardware not yet implemented"
	#endif
}

void hal_serial_setTimeout(void *handle, uint32_t mstime) {
	#if defined(HW_ARDUINO)
		static_cast<HardwareSerial*>(handle)->setTimeout(mstime);
	#elif defined(HW_IBUG_H)
	
	#else
		#error "Hardware not yet implemented"
	#endif
}

uint16_t hal_serial_available(void *handle) {
	#if defined(HW_ARDUINO)
		static_cast<HardwareSerial*>(handle)->available();
	#elif defined(HW_IBUG_H)
		return 0 //TODO
	#else
		#error "Hardware not yet implemented"
	#endif
}



#ifdef __cplusplus
}
#endif//__cplusplus