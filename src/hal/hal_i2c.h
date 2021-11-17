#ifndef HAL_I2C_H
#define HAL_I2C_H

#include "hal_common.h"

void hal_i2c_begin(uint16_t address);
void hal_i2c_request_from(uint16_t address, uint16_t quantity, bool stop);
void hal_i2c_begin_transmission(uint16_t address);
uint8_t hal_i2c_end_transmission(bool stop);
void hal_i2c_write(uint8_t *data, uint16_t length);
uint16_t hal_i2c_available(void);
uint8_t hal_i2c_read(void);
void hal_i2c_set_clock(uint32_t freq);
void hal_i2c_on_receive(uint32_t numBytes);
void hal_i2c_on_request(void (*handler)(void));

#endif // HAL_I2C_H