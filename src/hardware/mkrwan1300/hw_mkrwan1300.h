/**
 * \addtogroup MKRWAN1300group MKRWAN1300
 * @{
 *	 \ingroup hwlayer
 */
 
 /**
 * \file hw_mkrwan1300.h
 * \brief This file is used to select The mkrwan1300 hardware for the library code to use for
 * compiling to work with. 
 * 
 * This file defines all the necissary defines the hardware.h file uses to set the library
 * code up properly to compile for the mkrwan1300 hardware should the user uncomment the 
 * define MKRWAN1300 in the hw_config file. It also impliments necissary
 * define if else guards to prevent more than one hardware from being selected.
 */
 
#if defined(HW_H) && !defined(HW_MKRWAN1300_H)
	#error "Multiple hardware definitions."
#elif !defined(HW_H) && !defined(HW_MKRWAN1300_H)
#ifdef __cplusplus
extern "C" {
#endif

	#define HW_H
	#define HW_MKRWAN1300_H
	#include "hw_mkrwan1300_registers.h"

#ifdef __cplusplus
}
#endif
#endif // HW_H HW_MKRWAN1300_H



/** @} */ // end of MKRWAN1300group