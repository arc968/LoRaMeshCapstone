/**
 * \addtogroup RAK11300group RAK11300
 * @{
 *	 \ingroup hwlayer
 */
 
 /**
 * \file hw_rak11300.h
 * \brief This file is used to select The RAK11300 hardware for the library code to use for
 * compiling to work with. 
 * 
 * This file defines all the necissary defines the hardware.h file uses to set the library
 * code up properly to compile for the RAK11300 hardware should the user uncomment the 
 * define RAK11300 in the hw_config file. It also impliments necissary
 * define if else guards to prevent more than one hardware from being selected.
 */

#if defined(HW_H) && !defined(HW_RAK11300_H)
	#error "Multiple hardware definitions."
#elif !defined(HW_H) && !defined(HW_RAK11300_H)
#ifdef __cplusplus
extern "C" {
#endif

	#define HW_H
	#define HW_RAK11300_H
	#define HW_ARDUINO
	#include "hw_rak11300_registers.h"
	
#ifdef __cplusplus
}
#endif

#endif // HW_H HW_RAK11300_H

/** @} */ // end of RAK11300group