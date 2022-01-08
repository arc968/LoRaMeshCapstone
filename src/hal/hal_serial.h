#ifndef HAL_SERIAL_H
#define HAL_SERIAL_H
#ifdef __cplusplus
extern "C" {
#endif

#include "hal_common.h"

bool hal_serial_ready(void);
void hal_serial_begin(uint16_t baud);
void hal_serial_end(void);
void hal_serial_write(uint8_t *buff, uint16_t length);
size_t hal_serial_readBytes(uint8_t *buf, uint16_t length);
void hal_serial_flush(void);
void hal_serial_setTimeout(uint32_t mstime);

#ifdef __cplusplus
}
#endif
#endif // HAL_SERIAL_H