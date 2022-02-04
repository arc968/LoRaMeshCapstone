/**
 * \addtogroup IBUGReggroup IBUG registers
 * @{
 *	 \ingroup IBUGgroup
 */
 
 /**
 * \file hw_ibug_registers.h
 * \brief This file is used to define all the specific IBUG hardware register adresses and macros
 * for the library code to use for compiling to work with. 
 * 
 * This file defines all the necissary defines the hardware.h file uses to set the library
 * code up properly to compile for the IBUG hardware should the user uncomment the 
 * define IBUG in the hw_config file. It also impliments necissary
 * define if else guards to prevent more than one hardware from being selected.
 *
 * This file contains all the hardware specific adresses and macros the hardware abstraction layer uses
 * for the libraries functionality. All definitions in this file have specific names that need to be used
 * in order for the hardware abstraction layers functions to use propperly. Some definitions the hardware may
 * not have and can be ommitted if stated in the comments but names for those that are must follow the conventions used.
 *
 * The IBUG hardware uses the <a href="https://dl-docs.rakwireless.com/api/render/?emulateScreenMedia=false&pdf.format=legal&url=https%3A%2F%2Fdocs.rakwireless.com%2FProduct-Categories%2FWisDuo%2FRAK4600-Module%2FDatasheet%2F">RAK4600</a> processor. This processor is composed of two other processors, the <a href="https://www.mouser.com/datasheet/2/761/sx1276-1278113.pdf">SX1276-7-8</a>  and <a href="https://infocenter.nordicsemi.com/pdf/nRF52832_PS_v1.0.pdf">nRF52832</a> .
 */
 
/*****Power registers**********/
#define HW_POWER 						(* (uint32_t *) 0x40000000)

#define HW_POWER_TASKS_CONSTLAT			(* (uint32_t *) (HW_POWER | 0x078))
#define HW_POWER_TASKS_LOWPWR			(* (uint32_t *) (HW_POWER | 0x07C))
#define HW_POWER_TASKS_SLEEPENTER		(* (uint32_t *) (HW_POWER | 0x114))
#define HW_POWER_TASKS_SLEEPEXIT		(* (uint32_t *) (HW_POWER | 0x118))
#define HW_POWER_INTENSET				(* (uint32_t *) (HW_POWER | 0x304))
#define HW_POWER_INTENCLR				(* (uint32_t *) (HW_POWER | 0x308))
#define HW_POWER_SYSTEMOFF				(* (uint32_t *) (HW_POWER | 0x500))
#define HW_POWER_RAM0_POWER 			(* (uint32_t *) (HW_POWER | 0x900))
#define HW_POWER_RAM0_POWERSET 			(* (uint32_t *) (HW_POWER | 0x904))
#define HW_POWER_RAM0_POWERCLR 			(* (uint32_t *) (HW_POWER | 0x908))
#define HW_POWER_RAM1_POWER 			(* (uint32_t *) (HW_POWER | 0x910))
#define HW_POWER_RAM1_POWERSET 			(* (uint32_t *) (HW_POWER | 0x914))
#define HW_POWER_RAM1_POWERCLR 			(* (uint32_t *) (HW_POWER | 0x918))
#define HW_POWER_RAM2_POWER 			(* (uint32_t *) (HW_POWER | 0x920))
#define HW_POWER_RAM2_POWERSET 			(* (uint32_t *) (HW_POWER | 0x924))
#define HW_POWER_RAM2_POWERCLR 			(* (uint32_t *) (HW_POWER | 0x928))
#define HW_POWER_RAM3_POWER 			(* (uint32_t *) (HW_POWER | 0x930))
#define HW_POWER_RAM3_POWERSET 			(* (uint32_t *) (HW_POWER | 0x934))
#define HW_POWER_RAM3_POWERCLR 			(* (uint32_t *) (HW_POWER | 0x938))
#define HW_POWER_RAM4_POWER 			(* (uint32_t *) (HW_POWER | 0x940))
#define HW_POWER_RAM4_POWERSET 			(* (uint32_t *) (HW_POWER | 0x944))
#define HW_POWER_RAM4_POWERCLR 			(* (uint32_t *) (HW_POWER | 0x948))
#define HW_POWER_RAM5_POWER 			(* (uint32_t *) (HW_POWER | 0x950))
#define HW_POWER_RAM5_POWERSET 			(* (uint32_t *) (HW_POWER | 0x954))
#define HW_POWER_RAM5_POWERCLR 			(* (uint32_t *) (HW_POWER | 0x958))
#define HW_POWER_RAM6_POWER 			(* (uint32_t *) (HW_POWER | 0x960))
#define HW_POWER_RAM6_POWERSET 			(* (uint32_t *) (HW_POWER | 0x964))
#define HW_POWER_RAM6_POWERCLR 			(* (uint32_t *) (HW_POWER | 0x968))
#define HW_POWER_RAM7_POWER 			(* (uint32_t *) (HW_POWER | 0x970))
#define HW_POWER_RAM7_POWERSET 			(* (uint32_t *) (HW_POWER | 0x974))
#define HW_POWER_RAM7_POWERCLR 			(* (uint32_t *) (HW_POWER | 0x978))







/** @} */ // end of IBUGReggroup