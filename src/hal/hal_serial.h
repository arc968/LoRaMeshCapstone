#ifndef HAL_SERIAL_H
#define HAL_SERIAL_H

#include "../hardware/hardware.h"

#include "hal_common.h"

void hal_serial_begin(uint16_t baud);

void hal_serial_end(void);

void hal_serial_write(uint8_t *buff, uint16_t len);

size_t hal_serial_read_bytes(uint8_t *buff, uint16_t len);

size_t hal_serial_print(uint8_t *val, uint8_t format);

size_t hal_serial_print(uint8_t *val, uint8_t format);

#endif // HAL_SERIAL_H