#define HAL_LIB
#include "hal_serial.h"

#ifdef HW_ARDUINO
	#include <HardwareSerial.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if defined(HW_ARDUINO)

	void * const hal_serial0 = &Serial;
	void * const hal_serial1 = &Serial1;
	//const void * hal_serial2 = &Serial2;
	//const void * hal_serial3 = &Serial3;

#elif defined(HW_MKRWAN1300_H)
	
#elif defined(HW_RAK4260_H)
	
#elif defined(HW_RAK4600_H)
		
#elif defined(HW_RAK11300_H)
	
#else
	#error "Hardware not yet implemented"
#endif

bool hal_serial_ready(void * const handle) {
	#if defined(HW_ARDUINO)
		return (*(static_cast<Serial_*>(handle)));
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

void hal_serial_begin(void * const handle, uint16_t baud) {
	#if defined(HW_ARDUINO)
		static_cast<HardwareSerial*>(handle)->begin(baud);
	#elif defined(HW_MKRWAN1300_H)
		
	#elif defined(HW_RAK4260_H)
		
	#elif defined(HW_RAK4600_H)
			
	#elif defined(HW_RAK11300_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
}

void hal_serial_end(void * const handle) {
	#if defined(HW_ARDUINO)
		static_cast<HardwareSerial*>(handle)->end();
	#elif defined(HW_MKRWAN1300_H)
		
	#elif defined(HW_RAK4260_H)
		
	#elif defined(HW_RAK4600_H)
			
	#elif defined(HW_RAK11300_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
}

void hal_serial_write(void * const handle,uint8_t *buf, uint16_t length) {
	#if defined(HW_ARDUINO)
		static_cast<HardwareSerial*>(handle)->write(buf, length);
	#elif defined(HW_MKRWAN1300_H)
		
	#elif defined(HW_RAK4260_H)
		
	#elif defined(HW_RAK4600_H)
			
	#elif defined(HW_RAK11300_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
}

int hal_serial_read(void * const handle) {
	#if defined(HW_ARDUINO)
		return static_cast<HardwareSerial*>(handle)->read();
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

size_t hal_serial_readBytes(void * const handle, uint8_t *buf, uint16_t length) {
	#if defined(HW_ARDUINO)
		uint16_t count = 0;
		while(static_cast<HardwareSerial*>(handle)->available() > 0 && count < length) {
			buf[count++] = static_cast<HardwareSerial*>(handle)->read();
		}
		return count;
	#elif defined(HW_MKRWAN1300_H)
		
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

void hal_serial_flush(void * const handle) {
	#if defined(HW_ARDUINO)
		static_cast<HardwareSerial*>(handle)->flush();
	#elif defined(HW_MKRWAN1300_H)
		
	#elif defined(HW_RAK4260_H)
		
	#elif defined(HW_RAK4600_H)
			
	#elif defined(HW_RAK11300_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
}

void hal_serial_setTimeout(void * const handle, uint32_t mstime) {
	#if defined(HW_ARDUINO)
		static_cast<HardwareSerial*>(handle)->setTimeout(mstime);
	#elif defined(HW_MKRWAN1300_H)
		
	#elif defined(HW_RAK4260_H)
		
	#elif defined(HW_RAK4600_H)
			
	#elif defined(HW_RAK11300_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
}

uint16_t hal_serial_available(void * const handle) {
	#if defined(HW_ARDUINO)
		return static_cast<HardwareSerial*>(handle)->available();
	#elif defined(HW_MKRWAN1300_H)
		
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



#ifdef __cplusplus
}
#endif//__cplusplus