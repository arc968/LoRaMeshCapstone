/**
 * \addtogroup hwlayer Hardware Layer
 * @{
 */

/**
 * \file hardware.h
 * \brief This file uses the selected hardware from hw_config.h to include the selected
 * hardwares setup files.
 * 
 * The included setup file of the selected hardware is included into the library's
 * compiling to allow the code in the hardware abstraction layer to work on the selected
 * hardware.
 */

#ifndef HARDWARE_H
#define HARDWARE_H

#include "hw_config.h"

#if defined(MKRWAN1300)
	#include "mkrwan1300/hw_mkrwan1300.h"
#elif defined(IBUG)
	#include "ibug/hw_ibug.h"
#else
	#error "No hardware defined"
#endif

#endif // HARDWARE_H

/** @} */ // end of hwlayer group