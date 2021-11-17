#ifndef HAL_SPI_H
#define HAL_SPI_H

#include "hal_common.h"

#ifndef HW_ARDUINO
enum hal_spi_mode_e {
	SPI_MODE0 = 0,
	SPI_MODE1 = 1,
	SPI_MODE2 = 2,
	SPI_MODE3 = 3
};

enum hal_spi_bit_order_e {
	LSBFIRST = 0,
	MSBFIRST = 1
};
#endif // HW_ARDUINO

void hal_spi_begin(void);
void hal_spi_end(void);
void hal_spi_beginTransaction(uint32_t speedmax, uint8_t dataorder, uint8_t datamode);
void hal_spi_endTransaction(void);
uint8_t hal_spi_transfer(uint8_t data);
void hal_spi_transferBuf(uint8_t* buf, uint16_t length);
void hal_spi_usingInterrupt(uint16_t interuptnum);

#endif // HAL_SPI_H