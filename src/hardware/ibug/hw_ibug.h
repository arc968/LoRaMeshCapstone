/**
 * \addtogroup IBUGgroup IBUG
 * @{
 *	 \ingroup hwlayer
 */
 
 /**
 * \file hw_ibug.h
 * \brief This file is used to select The IBUG hardware for the library code to use for
 * compiling to work with. 
 * 
 * This file defines all the necissary defines the hardware.h file uses to set the library
 * code up properly to compile for the IBUG hardware should the user uncomment the 
 * define IBUG in the hw_config file. It also impliments necissary
 * define if else guards to prevent more than one hardware from being selected.
 */

#if defined(HW_H) && !defined(HW_IBUG_H)
	#error "Multiple hardware definitions"
#elif !defined(HW_H) && !defined(HW_IBUG_H)

	#define HW_H
	#define HW_IBUG_H
	#include "hw_ibug_registers.h"

#endif // HW_H IBUG_H

/** @} */ // end of IBUGgroup