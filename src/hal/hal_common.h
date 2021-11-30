#ifndef HAL_COMMON_H
#define HAL_COMMON_H

#include "../hardware/hardware.h"

#ifdef __cplusplus
	#include <cstdint>
	#include <cstdbool>
	#include <cstdlib>
#else
	#include <stdint.h>
	#include <stdbool.h>
	#include <stdlib.h>
#endif

typedef uint_fast16_t pin_t;

#endif // HAL_COMMON_H