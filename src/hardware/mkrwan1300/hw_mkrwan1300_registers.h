/**
 * \addtogroup MKRWAN1300Reggroup IBUG registers
 * @{
 *	 \ingroup MKRWAN1300group
 */
 
 /**
 * \file hw_mkrwan1300_registers.h
 * \brief This file is used to select The mkrwan1300 hardware for the library code to use for
 * compiling to work with. 
 * 
 * This file defines all the necissary defines the hardware.h file uses to set the library
 * code up properly to compile for the mkrwan1300 hardware should the user uncomment the 
 * define MKRWAN1300 in the hw_config file. It also impliments necissary
 * define if else guards to prevent more than one hardware from being selected.
 *
 * This file contains all the hardware specific adresses and macros the hardware abstraction layer uses
 * for the libraries functionality. All definitions in this file have specific names that need to be used
 * in order for the hardware abstraction layers functions to use propperly. Some definitions the hardware may
 * not have and can be ommitted if stated in the comments but names for those that are must follow the conventions used.
 *
 * The mkrwan1300 hardware uses the <a href="http://ww1.microchip.com/downloads/en/DeviceDoc/40001884A.pdf">SAMD21 Cortex-M0+ 32bit low power ARM MCU</a> processor.
 */
 
#ifdef __cplusplus
extern "C" {
#endif


 
#ifdef __cplusplus
}
#endif

 /** @} */ // end of MKRWAN1300Reggroup