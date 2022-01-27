/**
 * \addtogroup hallayer Hardware Abstraction Layer
 * @{
 */

/**
 * \file hal_spi.h
 * \brief 
 * 
 * 
 */

#ifndef HAL_SPI_H
#define HAL_SPI_H

#include "hal_common.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HW_ARDUINO
enum hal_spi_mode_e {
	SPI_MODE0 = 0,
	SPI_MODE1 = 1,
	SPI_MODE2 = 2,
	SPI_MODE3 = 3
};

enum hal_spi_bit_order_e {
	SPI_LSBFIRST = 0,
	SPI_MSBFIRST = 1
};
#else 
enum hal_spi_bit_order_e {
	SPI_LSBFIRST = LSBFIRST ,
	SPI_MSBFIRST = MSBFIRST
};
#endif // HW_ARDUINO

void hal_spi_begin(void);
void hal_spi_end(void);
void hal_spi_beginTransaction(uint32_t speedmax, enum hal_spi_bit_order_e dataorder, uint8_t datamode);
void hal_spi_endTransaction(void);
uint8_t hal_spi_transfer(uint8_t data);
void hal_spi_transferBuf(uint8_t* buf, uint16_t length);
void hal_spi_usingInterrupt(uint16_t interuptnum);

#ifdef __cplusplus
}
#endif
#endif // HAL_SPI_H

/** @} */ // end of hallayer