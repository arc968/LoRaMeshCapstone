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
 

//Base Addresses
#define REGFIFO		 	0x00	//!< FIFO read/write access
#define REGOPMODE	 	0x01	//Operating mode & LoRaTM / FSK selection
#define REGBITRATEMSB	0x02	//Bit Rate setting, Most Significant Bits
#define REGBITRATELSB	0x03	//Bit Rate setting, Least Significant Bits
#define REGFDEVMSB		0x04	//Frequency Deviation setting, Most Significant Bits
#define REGFDEVLSB		0x05	//Frequency Deviation setting, Least Significant Bits


//Mode Definitions




//Configuration Macros






/** @} */ // end of IBUGReggroup