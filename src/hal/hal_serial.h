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

#include <stdio.h>
#include <string.h>

int  snprintf_(char* buffer, size_t count, const char* format, ...);
#define DEBUG_PRINT_FUNCTION() {char tbuf[256]; snprintf_(tbuf, sizeof(tbuf), "%s()\n",__func__); hal_serial_write(hal_serial0, (uint8_t *)&(tbuf[0]), strlen(tbuf));}

#define DEBUG_PRINT(...) {char tbuf[256]; snprintf_(tbuf, sizeof(tbuf), __VA_ARGS__); hal_serial_write(hal_serial0, (uint8_t *)&(tbuf[0]), strlen(tbuf));}

#define DEBUG_PRINT_TIMESTAMP() {char tbuf[256]; snprintf_(tbuf, sizeof(tbuf), "[%lu] ", (uint32_t)drv_timer_getMonotonicTime()); hal_serial_write(hal_serial0, (uint8_t *)&(tbuf[0]), strlen(tbuf));}

#define DEBUG_PRINT_REALTIME() {char tbuf[256]; lib_datetime_realtime_t trt; drv_timer_getRealtime(&trt); snprintf_(tbuf, sizeof(tbuf), "[rt:%lu] ", (uint32_t)trt); hal_serial_write(hal_serial0, (uint8_t *)&(tbuf[0]), strlen(tbuf));}

extern void * const hal_serial0;
extern void * const hal_serial1;
//extern const void * hal_serial2;
//extern const void * hal_serial3;

bool hal_serial_ready(void * const handle);
void hal_serial_begin(void * const handle, uint16_t baud);
void hal_serial_end(void * const handle);
void hal_serial_write(void * const handle, uint8_t *buf, uint16_t length);
int hal_serial_read(void * const handle);
size_t hal_serial_readBytes(void * const handle, uint8_t *buf, uint16_t length);
void hal_serial_flush(void * const handle);
void hal_serial_setTimeout(void * const handle, uint32_t mstime);
uint16_t hal_serial_available(void * const handle);

#ifdef __cplusplus
}
#endif
#endif // HAL_SERIAL_H

/** @} */ // end of hallayer