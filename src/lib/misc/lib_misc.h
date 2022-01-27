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
inline uint32_t lib_misc_fastrange32(uint32_t word, uint32_t p) {
	return (uint32_t)(((uint64_t)word * (uint64_t)p) >> 32);
}

inline uint32_t lib_misc_XORshiftLFSR32(uint32_t seed) {
  if (seed == 0) seed = 0xFFFFFFFF;
  seed ^= seed << 13;
  seed ^= seed >> 17;
  seed ^= seed << 5;
  return seed;
}

inline uint16_t lib_misc_XORshiftLFSR16(uint16_t seed) {
  if (seed == 0) seed = 0xFFFF;
  seed ^= seed << 7;
  seed ^= seed >> 9;
  seed ^= seed << 8;
  return seed;
}

void shuffleArrU8(uint8_t * arr, uint16_t len, uint32_t seed);

#endif // LIB_MISC_H