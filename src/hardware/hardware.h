/**
 * \addtogroup hwlayer [Hardware Layer]
 * @{
 */

/**
 *
 * \file hardware.h
 * \brief This file uses the selected hardware from hw_config.h to include the selected
 * hardwares setup files.
 * 
 * The included setup file of the selected hardware is included into the library's
 * compiling to allow the code in the hardware abstraction layer to work on the selected
 * hardware.
 *
 * \author Josh Lariviere
 * \author Andrew Courtemanche
 */

#ifndef HARDWARE_H
#define HARDWARE_H
#define HARDWARE_H_SCOPE

#include "hw_config.h"

#if defined(MKRWAN1300)
	#include "mkrwan1300/hw_mkrwan1300.h"
#elif defined(IBUG)
	#include "ibug/hw_ibug.h"
#else
	#error "No hardware defined."
#endif

#if defined(GPS_UBLOX_NEO6)
	#include "gps/ublox/neo6/hw_gps_ublox_neo6.h"
#elif defined(GPS_NONE)
	#include "gps/hw_gps.h"
#else
	#error "No GPS hardware defined. Explicitly define GPS_NONE if no GPS module is used."
#endif

#undef HARDWARE_H_SCOPE
#endif // HARDWARE_H

/** @} */ // end of hwlayer group