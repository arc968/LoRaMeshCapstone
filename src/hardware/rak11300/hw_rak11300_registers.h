/**
 * \addtogroup RAK4260Reggroup RAK11300 registers
 * @{
 *	 \ingroup RAK11300group
 */
 
 /**
 * \file hw_rak11300_registers.h
 * \brief This file is used to define all the specific RAK11300 hardware register adresses and macros
 * for the library code to use for compiling to work with. 
 * 
 * This file defines all the necissary defines the hardware.h file uses to set the library
 * code up properly to compile for the RAK11300 hardware should the user uncomment the 
 * define RAK11300 in the hw_config file. It also impliments necissary
 * define if else guards to prevent more than one hardware from being selected.
 *
 * This file contains all the hardware specific adresses and macros the hardware abstraction layer uses
 * for the libraries functionality. All definitions in this file have specific names that need to be used
 * in order for the hardware abstraction layers functions to use propperly. Some definitions the hardware may
 * not have and can be ommitted if stated in the comments but names for those that are must follow the conventions used.
 *
 * The RAK11300 hardware uses the <a href="https://dl-docs.rakwireless.com/api/render/?emulateScreenMedia=false&pdf.format=legal&url=https%3A%2F%2Fdocs.rakwireless.com%2FProduct-Categories%2FWisDuo%2FRAK11300-Module%2FDatasheet%2F">RAK11300</a> processor. This processor is composed of two other processors, the <a href="https://semtech.my.salesforce.com/sfc/p/#E0000000JelG/a/2R000000Un7F/yT.fKdAr9ZAo3cJLc4F2cBdUsMftpT2vsOICP7NmvMo">SX1262</a>  and <a href="https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf">RP2040</a> .
 */
 
 #ifndef HW_RAK11300_REGISTERS_H
#define HW_RAK11300_REGISTERS_H

 
/*****Power registers**********/
#define HW_POWER_AIRCR					(* (uint32_t *) 0xE000ED0C)


/*****Timer registers**********/


#endif HW_RAK11300_REGISTERS_H

/** @} */ // end of RAK11300Reggroup