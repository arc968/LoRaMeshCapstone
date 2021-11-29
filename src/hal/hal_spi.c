#define HAL_LIB
#include "hal_spi.h"

#ifdef HW_ARDUINO
	#include <SPI.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

void hal_spi_begin(void) {
	#if defined(HW_ARDUINO)
		SPI.begin();
	#elif defined(HW_IBUG_H)
		
	#else
		#error "Hardware not yet implemented"
	#endif
}

void hal_spi_end(void) {
	#if defined(HW_ARDUINO)
		SPI.end();
	#elif defined(HW_IBUG_H)
	
	#else
		#error "Hardware not yet implemented"
	#endif
}

void hal_spi_beginTransaction(uint32_t speedmax, uint8_t dataorder, uint8_t datamode) {
	#if defined(HW_ARDUINO)
		SPI.beginTransaction(SPISettings(speedmax, dataorder, datamode));
	#elif defined(HW_IBUG_H)
	
	#else
		#error "Hardware not yet implemented"
	#endif
}

void hal_spi_endTransaction(void) {
	#if defined(HW_ARDUINO)
		SPI.endTransaction();
	#elif defined(HW_IBUG_H)
	
	#else
		#error "Hardware not yet implemented"
	#endif
}
uint8_t hal_spi_transfer(uint8_t data, mosi) {
	#if defined(HW_ARDUINO)
		return SPI.transfer(data);
	#elif defined(HW_IBUG_H)
		return 0; //TODO
	#else
		#error "Hardware not yet implemented"
	#endif
}

void hal_spi_transferBuf(uint8_t* buf, uint16_t length, mosi) {
	#if defined(HW_ARDUINO)
		SPI.transfer(buff, length);
	#elif defined(HW_IBUG_H)
	
	#else
		#error "Hardware not yet implemented"
	#endif
}
void hal_spi_usingInterrupt(uint16_t interuptnum) {
	#if defined(HW_ARDUINO)
		SPI.usingInterrupt(interuptnum);
	#elif defined(HW_IBUG_H)
	
	#else
		#error "Hardware not yet implemented"
	#endif
}


#ifdef __cplusplus
}
#endif//__cplusplus