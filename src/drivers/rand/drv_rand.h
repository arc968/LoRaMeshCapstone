#ifndef DRV_RAND_H
#define DRV_RAND_H
#if defined (__cplusplus)
extern "C" {
#endif

#include <stdint.h>

// NOT SAFE TO USE DURING INTERRUPTS
void drv_rand_seedFromMisc(void);

// NOT SAFE TO USE DURING INTERRUPTS
void drv_rand_seedFromLoRa(struct drv_lora_s * handle);

// NOT SAFE TO USE DURING INTERRUPTS
void drv_rand_regenBuffer(void);

// NOT SAFE TO USE DURING INTERRUPTS
uint8_t drv_rand_getU8(void);
uint16_t drv_rand_getU16(void);
uint32_t drv_rand_getU32(void);
uint64_t drv_rand_getU64(void);

// NOT SAFE TO USE DURING INTERRUPTS
void drv_rand_fillBuf(uint8_t * buf, size_t size);

#if defined (__cplusplus)
}
#endif
#endif // DRV_RAND_H
