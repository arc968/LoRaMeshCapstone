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

#ifdef DEBUG_MESH
	int  snprintf_(char* buffer, size_t count, const char* format, ...);
	#define DEBUG_PRINT_FUNCTION() {char tbuf[256]; snprintf_(tbuf, sizeof(tbuf), "%s()\n",__func__); hal_serial_write(hal_serial0, (uint8_t *)&(tbuf[0]), strlen(tbuf));}

	#define DEBUG_PRINT(...) {char tbuf[256]; snprintf_(tbuf, sizeof(tbuf), __VA_ARGS__); hal_serial_write(hal_serial0, (uint8_t *)&(tbuf[0]), strlen(tbuf));}

	#define DEBUG_PRINT_TIMESTAMP() {char tbuf[256]; snprintf_(tbuf, sizeof(tbuf), "[%lu] ", (uint32_t)drv_timer_getMonotonicTime()); hal_serial_write(hal_serial0, (uint8_t *)&(tbuf[0]), strlen(tbuf));}

	#define DEBUG_PRINT_REALTIME() {char tbuf[256]; lib_datetime_realtime_t trt; drv_timer_getRealtime(&trt); snprintf_(tbuf, sizeof(tbuf), "[rt:%lu] ", (uint32_t)trt); hal_serial_write(hal_serial0, (uint8_t *)&(tbuf[0]), strlen(tbuf));}\

	#define DEBUG_PRINT_BUF(tarr,tsize) { DEBUG_PRINT(#tarr" [%hhu]: [", tsize); \
			for (uint32_t i=0; i<tsize; i++) DEBUG_PRINT(((i+1==tsize) ? "%hhu" : "%hhu,"), ((uint8_t *)(tarr))[i]); \
			DEBUG_PRINT("]\n"); }

	#define DEBUG_PRINT_BUF_HEX(tarr,tsize) { DEBUG_PRINT(#tarr" [%hhX]: [",tsize); \
			for (uint32_t i=0; i<tsize; i++) DEBUG_PRINT(((i+1==tsize) ? "%hhX" : "%hhX,"), ((uint8_t *)(tarr))[i]); \
			DEBUG_PRINT("]\n"); }

	#define DEBUG_PRINT_ARRAY(tarr) { DEBUG_PRINT(#tarr" [%hhu]: [", sizeof(tarr)); \
			for (uint32_t i=0; i<sizeof(tarr); i++) DEBUG_PRINT(((i+1==sizeof(tarr)) ? "%hhu" : "%hhu,"), (tarr)[i]); \
			DEBUG_PRINT("]\n"); }

	#define DEBUG_PRINT_ARRAY_HEX(tarr) { DEBUG_PRINT(#tarr" [%hhX]: [", sizeof(tarr)); \
			for (uint32_t i=0; i<sizeof(tarr); i++) DEBUG_PRINT(((i+1==sizeof(tarr)) ? "%hhX" : "%hhX,"), (tarr)[i]); \
			DEBUG_PRINT("]\n"); }
#else 
	#define DEBUG_PRINT_FUNCTION() 
	#define DEBUG_PRINT(...) 
	#define DEBUG_PRINT_TIMESTAMP() 
	#define DEBUG_PRINT_REALTIME() 
	#define DEBUG_PRINT_BUF(tarr,tsize) 
	#define DEBUG_PRINT_BUF_HEX(tarr,tsize) 
	#define DEBUG_PRINT_ARRAY(tarr) 
	#define DEBUG_PRINT_ARRAY_HEX(tarr) 
#endif

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