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

#include "hal_common.h"

#ifdef __cplusplus
extern "C" {
#endif

void hal_i2c_begin(void);
void hal_i2c_requestFrom(uint16_t address, uint16_t quantity, bool stop);
void hal_i2c_beginTransmission(uint8_t address);
uint8_t hal_i2c_endTransmission(bool stop);
void hal_i2c_write(uint8_t *buf, uint16_t length);
uint16_t hal_i2c_available(void);
uint8_t hal_i2c_read(void);
void hal_i2c_setClock(uint32_t freq);
void hal_i2c_onReceive();
void hal_i2c_onRequest(void (*handler)(void));

void hal_i2c_received(int numBytes);

#ifdef __cplusplus
}
#endif
#endif // HAL_I2C_H

/** @} */ // end of hallayer