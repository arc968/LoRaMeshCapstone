/**
 * \addtogroup RAK4260group RAK4260
 * @{
 *	 \ingroup hwlayer
 */
 
 /**
 * \file hw_rak4260.h
 * \brief This file is used to select The RAK4260 hardware for the library code to use for
 * compiling to work with. 
 * 
 * This file defines all the necissary defines the hardware.h file uses to set the library
 * code up properly to compile for the RAK4260 hardware should the user uncomment the 
 * define RAK4260 in the hw_config file. It also impliments necissary
 * define if else guards to prevent more than one hardware from being selected.
 */

#if defined(HW_H) && !defined(HW_RAK4260_H)
	#error "Multiple hardware definitions."
#elif !defined(HW_H) && !defined(HW_RAK4260_H)
#ifdef __cplusplus
extern "C" {
#endif

	#define HW_H
	#define HW_RAK4260_H
	#include "hw_rak4260_registers.h"
	
#ifdef __cplusplus
}
#endif

#endif // HW_H HW_RAK4260_H

/** @} */ // end of RAK4260group