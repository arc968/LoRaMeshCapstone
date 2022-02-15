/**
 * \addtogroup RAK4600group RAK4600
 * @{
 *	 \ingroup hwlayer
 */
 
 /**
 * \file hw_rak4600.h
 * \brief This file is used to select The RAK4600 hardware for the library code to use for
 * compiling to work with. 
 * 
 * This file defines all the necissary defines the hardware.h file uses to set the library
 * code up properly to compile for the RAK4600 hardware should the user uncomment the 
 * define RAK4600 in the hw_config file. It also impliments necissary
 * define if else guards to prevent more than one hardware from being selected.
 */

#if defined(HW_H) && !defined(HW_RAK4600_H)
	#error "Multiple hardware definitions."
#elif !defined(HW_H) && !defined(HW_RAK4600_H)
#ifdef __cplusplus
extern "C" {
#endif

	#define HW_H
	#define HW_RAK4600_H
	#define HW_ARDUINO
	#include "hw_rak4600_registers.h"
	
#ifdef __cplusplus
}
#endif

#endif // HW_H HW_RAK4600_H

/** @} */ // end of IBUGgroup