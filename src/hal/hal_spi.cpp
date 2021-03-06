#define HAL_LIB
#include "hal_spi.h"

#ifdef HW_ARDUINO
	#include <SPI.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

bool hal_spi_begun = 0;

void hal_spi_begin(void) {
	if (!hal_spi_begun) {
	#if defined(HW_ARDUINO)
		SPI.begin();
		hal_spi_begun = 1;
	#elif defined(HW_MKRWAN1300_H)
		
	#elif defined(HW_RAK4260_H)
		
	#elif defined(HW_RAK4600_H)
			
	#elif defined(HW_RAK11300_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
	
	}
}

void hal_spi_end(void) {
	#if defined(HW_ARDUINO)
		SPI.end();
	#elif defined(HW_MKRWAN1300_H)
		
	#elif defined(HW_RAK4260_H)
		
	#elif defined(HW_RAK4600_H)
			
	#elif defined(HW_RAK11300_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
}

void hal_spi_beginTransaction(uint32_t speedmax, enum hal_spi_bit_order_e dataorder, uint8_t datamode) {
	#if defined(HW_ARDUINO)
		SPI.beginTransaction(SPISettings(speedmax, (BitOrder) dataorder, datamode));
	#elif defined(HW_MKRWAN1300_H)
		
	#elif defined(HW_RAK4260_H)
		
	#elif defined(HW_RAK4600_H)
			
	#elif defined(HW_RAK11300_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
}

void hal_spi_endTransaction(void) {
	#if defined(HW_ARDUINO)
		SPI.endTransaction();
	#elif defined(HW_MKRWAN1300_H)
		
	#elif defined(HW_RAK4260_H)
		
	#elif defined(HW_RAK4600_H)
			
	#elif defined(HW_RAK11300_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
}
uint8_t hal_spi_transfer(uint8_t data) {
	#if defined(HW_ARDUINO)
		return SPI.transfer(data);
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

void hal_spi_transferBuf(uint8_t* buf, uint16_t length) {
	#if defined(HW_ARDUINO)
		SPI.transfer(buf, length);
	#elif defined(HW_MKRWAN1300_H)
		
	#elif defined(HW_RAK4260_H)
		
	#elif defined(HW_RAK4600_H)
			
	#elif defined(HW_RAK11300_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
}
void hal_spi_usingInterrupt(uint16_t interuptnum) {
	#if defined(HW_ARDUINO)
		SPI.usingInterrupt(interuptnum);
	#elif defined(HW_MKRWAN1300_H)
		
	#elif defined(HW_RAK4260_H)
		
	#elif defined(HW_RAK4600_H)
			
	#elif defined(HW_RAK11300_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
}


#ifdef __cplusplus
}
#endif//__cplusplus