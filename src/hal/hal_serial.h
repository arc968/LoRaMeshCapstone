/**
 * \addtogroup hallayer Hardware Abstraction Layer
 * @{
 */

/**
 * \file hal_serial.h
 * \brief This file provides the underlying functionality for serial communications for the library
 * based on the selected hardware in the Hardware layer.
 * 
 * Based on the selected hardware defined in the hardware layer, this file sets up serial communications
 * for the library.
 */

#ifndef HAL_SERIAL_H
#define HAL_SERIAL_H

#include "hal_common.h"

#ifdef __cplusplus
extern "C" {
#endif

extern const void * hal_serial0;
extern const void * hal_serial1;
//extern const void * hal_serial2;
//extern const void * hal_serial3;

bool hal_serial_ready(void *handle);
void hal_serial_begin(void *handle, uint16_t baud);
void hal_serial_end(void *handle);
void hal_serial_write(void *handle, uint8_t *buf, uint16_t length);
size_t hal_serial_readBytes(void *handle, uint8_t *buf, uint16_t length);
void hal_serial_flush(void *handle);
void hal_serial_setTimeout(void *handle, uint32_t mstime);
uint16_t hal_serial_available(void *handle);

#ifdef __cplusplus
}
#endif
#endif // HAL_SERIAL_H

/** @} */ // end of hallayer