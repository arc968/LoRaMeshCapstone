#ifndef HAL_SPI_H
#define HAL_SPI_H

#include "hal_common.h"

#ifndef HW_ARDUINO
enum HAL_SPI_MODE {
	SPI_MODE0 = 0,
	SPI_MODE1 = 1,
	SPI_MODE2 = 2,
	SPI_MODE3 = 3
};

enum HAL_SPI_BIT_ORDER {
	LSBFIRST = 0,
	MSBFIRST = 1
};
#endif // HW_ARDUINO

void hal_spi_begin(void);
void hal_spi_end(void);
void hal_spi_begin_transaction(uint32_t speedmax, uint8_t dataorder, uint8_t datamode);
void hal_spi_end_transaction(void);
void hal_spi_transfer(uint8_t data);
void hal_spi_transfer_buf(uint8_t* buf, uint16_t length);
void hal_spi_using_interrupt(uint16_t interuptnum);

#endif // HAL_SPI_H