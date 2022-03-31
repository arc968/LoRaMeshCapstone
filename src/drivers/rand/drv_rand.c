#include "../../hal/hal.h"

#include <stdbool.h>

#include "../timer/drv_timer.h"
#include "../lora/drv_lora.h"

#include "../../lib/misc/lib_misc.h"
#include "../../deps/monocypher/monocypher.h"

#include "drv_rand.h"


/*
//#include "../../lib/printf/printf.h"
int  snprintf_(char* buffer, size_t count, const char* format, ...);

#define DEBUG_PRINT_FUNCTION() {char tbuf[256]; snprintf_(tbuf, sizeof(tbuf), "%s()\n",__func__); hal_serial_write(hal_serial0, (uint8_t *)&(tbuf[0]), strlen(tbuf));}

#define DEBUG_PRINT(...) {char tbuf[256]; snprintf_(tbuf, sizeof(tbuf), __VA_ARGS__); hal_serial_write(hal_serial0, (uint8_t *)&(tbuf[0]), strlen(tbuf));}

#define DEBUG_PRINT_TIMESTAMP() {char tbuf[256]; snprintf_(tbuf, sizeof(tbuf), "[%lu] ", (uint32_t)drv_timer_getMonotonicTime()); hal_serial_write(hal_serial0, (uint8_t *)&(tbuf[0]), strlen(tbuf));}

#define DEBUG_PRINT_REALTIME() {char tbuf[256]; lib_datetime_realtime_t trt; drv_timer_getRealtime(&trt); snprintf_(tbuf, sizeof(tbuf), "[rt:%lu] ", (uint32_t)trt); hal_serial_write(hal_serial0, (uint8_t *)&(tbuf[0]), strlen(tbuf));}
*/

#define MISC_MIN_SEED_ROUNDS 128
#define MISC_MIN_DURATION_MS 1000
#define LORA_MIN_SEED_ROUNDS 128
#define LORA_MIN_DURATION_MS 1000

static struct state_s {
	bool initialized;
	uint64_t nonce;
	uint8_t key[32];
	uint8_t bufferedBytes[32];
	uint32_t availableBytes;
} state;


#ifndef HW_ARDUINO
	#define NUM_ANALOG_INPUTS 0
#endif
/*
Pulls from several random-ish sources of noise in an attempt to seed the RNG
*/
void drv_rand_seedFromMisc(void) {
	crypto_blake2b_ctx ctx;
	crypto_blake2b_general_init(&ctx, sizeof(state.key), state.key, sizeof(state.key));
	
	lib_datetime_realtime_t start = drv_timer_getMonotonicTime();
	for (uint32_t i=0; i<MISC_MIN_SEED_ROUNDS || drv_timer_getMonotonicTime()-start < MISC_MIN_DURATION_MS; i++) {
		for (uint32_t aPins=0; aPins<NUM_ANALOG_INPUTS; aPins++) crypto_blake2b_update(&ctx, (uint8_t *)&(uint16_t){hal_gpio_analogRead(aPins)}, sizeof(uint16_t));
		crypto_blake2b_update(&ctx, (uint8_t *)&(uint64_t){drv_timer_getMonotonicTime()}, sizeof(uint64_t));
		crypto_blake2b_update(&ctx, (uint8_t *)&(uint16_t){hal_serial_available(hal_serial0)}, sizeof(uint16_t));
		crypto_blake2b_update(&ctx, (uint8_t *)&(uint16_t){hal_serial_available(hal_serial1)}, sizeof(uint16_t));
		{lib_datetime_realtime_t rt = 0; drv_timer_getRealtime(&rt); //don't care if unavailable
			crypto_blake2b_update(&ctx, (uint8_t *)&(uint64_t){rt}, sizeof(uint64_t));}
	}
	
	crypto_blake2b_final(&ctx, state.key);
	//crypto_blake2b_final(&ctx, &(state.key[0]));
	state.initialized = true;
}

void drv_rand_seedFromLoRa(struct drv_lora_s * handle) {
	crypto_blake2b_ctx ctx;
	crypto_blake2b_general_init(&ctx, sizeof(state.key), state.key, sizeof(state.key));
	
	uint8_t prev = 0;
	uint8_t randByte = 0;
	drv_rand_seedFromMisc();
	lib_datetime_realtime_t start = drv_timer_getMonotonicTime();
	for (uint32_t i=0; i<LORA_MIN_SEED_ROUNDS || drv_timer_getMonotonicTime()-start < LORA_MIN_DURATION_MS; i++) {
		drv_lora_setMode(handle, DRV_LORA_MODE__RECV_ONCE);
		while (randByte == prev) randByte = drv_lora_random(handle);
		drv_lora_setMode(handle, DRV_LORA_MODE__IDLE_CLEAR);
		crypto_blake2b_update(&ctx, &(uint8_t){randByte}, sizeof(uint8_t));
		prev = randByte;
	}
	drv_lora_setMode(handle, DRV_LORA_MODE__SLEEP);
	
	crypto_blake2b_final(&ctx, state.key);
	state.initialized = true;
/* 	uint8_t tempKey[32];
	uint8_t prev = 0;
	uint8_t randByte = 0;
	fillBufFromMisc(&(tempKey[0]), sizeof(tempKey));
	for (uint_fast8_t i=0; i<sizeof(state.key); i++) {
		drv_lora_setMode(handle, DRV_LORA_MODE__RECV_ONCE);
		while (randByte == prev) randByte = drv_lora_random(handle);
		drv_lora_setMode(handle, DRV_LORA_MODE__IDLE_CLEAR);
		state.key[i] = randByte;
		prev = randByte;
	}
	drv_lora_setMode(handle, DRV_LORA_MODE__SLEEP);
	crypto_blake2b_general(&(state.key[0]), sizeof(state.key), &(tempKey[0]), sizeof(tempKey), &(state.key[0]), sizeof(state.key));
	crypto_wipe(&(tempKey[0]), sizeof(tempKey));
	state.initialized = true; */
}

void drv_rand_fillBuf(uint8_t * buf, size_t size) {
	if (!state.initialized) drv_rand_seedFromMisc();
	crypto_chacha20(buf, NULL, size, state.key, (uint8_t *)&(state.nonce));
	state.nonce++;
}

void drv_rand_regenBuffer(void) {
	drv_rand_fillBuf(&(state.bufferedBytes[0]), sizeof(state.bufferedBytes));
	state.availableBytes = sizeof(state.bufferedBytes);
}

uint8_t drv_rand_getU8(void) {
	if (!state.initialized) drv_rand_seedFromMisc();
	if (state.availableBytes < sizeof(uint8_t)) drv_rand_regenBuffer();
	state.availableBytes -= sizeof(uint8_t);
	return *((uint8_t*)&(state.bufferedBytes[state.availableBytes]));
}

uint16_t drv_rand_getU16(void) {
	if (!state.initialized) drv_rand_seedFromMisc();
	if (state.availableBytes < sizeof(uint16_t)) drv_rand_regenBuffer();
	state.availableBytes -= sizeof(uint16_t);
	return *((uint16_t*)&(state.bufferedBytes[state.availableBytes]));
}

uint32_t drv_rand_getU32(void) {
	if (!state.initialized) drv_rand_seedFromMisc();
	if (state.availableBytes < sizeof(uint32_t)) drv_rand_regenBuffer();
	state.availableBytes -= sizeof(uint32_t);
	return *((uint32_t*)&(state.bufferedBytes[state.availableBytes]));
}

uint64_t drv_rand_getU64(void) {
	if (!state.initialized) drv_rand_seedFromMisc();
	if (state.availableBytes < sizeof(uint64_t)) drv_rand_regenBuffer();
	state.availableBytes -= sizeof(uint64_t);
	/*
	uint64_t out = 0;
	for (uint32_t i=0; i<sizeof(uint64_t); i++) {
		//DEBUG_PRINT("%X", state.bufferedBytes[state.availableBytes+i]);
		out <<= 8;
		out |= state.bufferedBytes[state.availableBytes+i] & 0xFF;
	}
	//DEBUG_PRINT("\n");
	hal_serial_flush(hal_serial0);
	return out;
	*/
	//return *((uint64_t*)&(state.bufferedBytes[state.availableBytes]));
	return ((uint64_t)*((uint32_t*)&(state.bufferedBytes[state.availableBytes]))) * 4294967296 + (uint64_t)*((uint32_t*)&(state.bufferedBytes[state.availableBytes+4]));
}

