/**
 * \addtogroup hallayer Hardware Abstraction Layer
 * @{
 */

/**
 * \file hal_i2c.h
 * \brief 
 * 
 * 
 */

#ifndef HAL_I2C_H
#define HAL_I2C_H
#ifdef __cplusplus
extern "C" {
#endif

#include "hal_common.h"

void hal_i2c_begin(void);
void hal_i2c_requestFrom(uint16_t address, uint16_t quantity, bool stop);
void hal_i2c_beginTransmission(uint16_t address);
uint8_t hal_i2c_endTransmission(bool stop);
void hal_i2c_write(uint8_t *buf, uint16_t length);
uint16_t hal_i2c_available(void);
uint8_t hal_i2c_read(void);
void hal_i2c_setClock(uint32_t freq);
void hal_i2c_onReceive(uint32_t numBytes);
void hal_i2c_onRequest(void (*handler)(void));

#ifdef __cplusplus
}
#endif
#endif // HAL_I2C_H

/** @} */ // end of hallayer