#include "lib_misc.h"

void shuffleArrU8(uint8_t * arr, uint16_t len, uint32_t seed) {
  for (uint16_t i=len-1; i>0; i--) {
    seed = lib_misc_XORshiftLFSR32(seed);
    uint16_t j = lib_misc_fastrange16((uint16_t)(seed), i+1);
    uint8_t tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
  }
}
