/**
 * \addtogroup hallayer Hardware Abstraction Layer
 * @{
 */

/**
 * \file hal_common.h
 * \brief This file is used as a ease of use to include all the common includes for all the
 * hardware abstraction layer files in one line of includes. 
 * 
 * This file has the includes needed by all the files in the hardware abstraction layer along
 * with any universal typedefs shared by the hardware abstraction layer files. The hardware.h
 * file is included to have in all the hardware abstraction layer files to propperly compile the
 * layer to work with the selected hardware and associated needed defines.
 */

#ifndef HAL_COMMON_H
#define HAL_COMMON_H

#include "../hardware/hardware.h"

#ifdef __cplusplus
extern "C" {
#endif



#ifdef __cplusplus
	//#include <cstdint>
	//#include <cstdbool>
	//#include <cstdlib>
	#include <stdint.h>
	#include <stdbool.h>
	#include <stdlib.h>
#else
	#include <stdint.h>
	#include <stdbool.h>
	#include <stdlib.h>
#endif

typedef uint_fast16_t pin_t;

#ifdef __cplusplus
}
#endif
#endif // HAL_COMMON_H

/** @} */ // end of hallayer