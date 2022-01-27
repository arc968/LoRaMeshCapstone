#ifndef LIB_MISC_H
#define LIB_MISC_H

#include <stdint.h>

/**
* Given a value "word", produces an integer in [0,p) without division.
* The function is as fair as possible in the sense that if you iterate
* through all possible values of "word", then you will generate all
* possible outputs as uniformly as possible.
*/
// Adapted from: https://github.com/lemire/fastrange
inline uint16_t lib_misc_fastrange16(uint16_t w, uint16_t p) {
  return (uint16_t)(((uint32_t)w * (uint32_t)p) >> 16);
}

/**
* Given a value "word", produces an integer in [0,p) without division.
* The function is as fair as possible in the sense that if you iterate
* through all possible values of "word", then you will generate all
* possible outputs as uniformly as possible.
*/
// Adapted from: https://github.com/lemire/fastrange
inline uint32_t lib_misc_fastrange32(uint32_t word, uint32_t p) {
	return (uint32_t)(((uint64_t)word * (uint64_t)p) >> 32);
}

inline uint16_t lib_misc_XORshiftLFSR16(uint16_t seed) {
	seed ^= seed << 7;
	seed ^= seed >> 9;
	seed ^= seed << 8;
	return seed;
}

inline uint32_t lib_misc_XORshiftLFSR32(uint32_t seed) {
	seed ^= seed << 13;
	seed ^= seed >> 17;
	seed ^= seed << 5;
	return seed;
}

inline uint64_t lib_misc_XORshiftLFSR64(uint64_t seed) {
	seed ^= seed << 12;
	seed ^= seed >> 25;
	seed ^= seed << 27;
	return seed;
}

//THESE CONSTANTS ARE NOT VALIDATED
uint16_t lib_misc_mix16(uint16_t val) {
	if (val == 0) val = 0xFFFF;
	val ^= val >> 7;
	val *= 0x37f4;
	val ^= val >> 5;
	val *= 0xe91c;
	val ^= val >> 8;
	return val;
}

uint32_t lib_misc_mix32(uint32_t val) {
	if (val == 0) val = 0xFFFFFFFF;
	val ^= val >> 16;
	val *= 0x85ebca6b;
	val ^= val >> 13;
	val *= 0xc2b2ae35;
	val ^= val >> 16;
	return val;
}

uint64_t lib_misc_mix64(uint64_t val) {
	if (val == 0) val = 0xFFFFFFFFFFFFFFFF;
	val ^= val >> 30;
	val *= 0xbf58476d1ce4e5b9;
	val ^= val >> 27;
	val *= 0x94d049bb133111eb;
	val ^= val >> 31;
	return val;
}

void shuffleArrU8(uint8_t * arr, uint16_t len, uint32_t seed);

#endif // LIB_MISC_H