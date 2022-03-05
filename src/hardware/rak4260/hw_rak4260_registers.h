/**
 * \addtogroup RAK4260Reggroup RAK4260 registers
 * @{
 *	 \ingroup RAK4260group
 */
 
 /**
 * \file hw_rak4260_registers.h
 * \brief This file is used to define all the specific RAK4260 hardware register adresses and macros
 * for the library code to use for compiling to work with. 
 * 
 * This file defines all the necissary defines the hardware.h file uses to set the library
 * code up properly to compile for the RAK4260 hardware should the user uncomment the 
 * define RAK4260 in the hw_config file. It also impliments necissary
 * define if else guards to prevent more than one hardware from being selected.
 *
 * This file contains all the hardware specific adresses and macros the hardware abstraction layer uses
 * for the libraries functionality. All definitions in this file have specific names that need to be used
 * in order for the hardware abstraction layers functions to use propperly. Some definitions the hardware may
 * not have and can be ommitted if stated in the comments but names for those that are must follow the conventions used.
 *
 * The RAK4260 hardware uses the <a href="https://dl-docs.rakwireless.com/api/render/?emulateScreenMedia=false&pdf.format=legal&url=https%3A%2F%2Fdocs.rakwireless.com%2FProduct-Categories%2FWisDuo%2FRAK4260-Module%2FDatasheet%2F">RAK4260</a> processor. This processor is composed of two other processors, the <a href="https://www.mouser.com/datasheet/2/761/sx1276-1278113.pdf">SX1276-7-8</a>  and <a href="https://dl-docs.rakwireless.com/api/render/?emulateScreenMedia=false&pdf.format=legal&url=https%3A%2F%2Fdocs.rakwireless.com%2FProduct-Categories%2FWisDuo%2FRAK4260-Module%2FDatasheet%2F">ATSAMR34J18B</a> .
 */
 
/*****Power registers**********/

#define HW_POWER_BASEADDRESS			0x40000000


#define HW_POWER_AIRCR					(* (uint32_t *) 0xE000ED0C)


/*****Timer registers**********/

#define HW_TCC0						(* (uint32_t *) 0x42001400)
#define HW_TCC1						(* (uint32_t *) 0x42001800)
#define HW_TCC2						(* (uint32_t *) 0x42001C00)

#define HW_TC0						(* (uint32_t *) 0x42002000)
#define HW_TC1						(* (uint32_t *) 0x42002400)
#define HW_TC2						(* (uint32_t *) 0x42002800)
#define HW_TC3						(* (uint32_t *) 0x42002C00)

#define HW_TC0_CTRLA				(* (uint32_t *) HW_TC0 | 0x00)
#define HW_TC0_CTRLBCLR				(* (uint32_t *) HW_TC0 | 0x04)
#define HW_TC0_CTRLBSET				(* (uint32_t *) HW_TC0 | 0x05)
#define HW_TC0_EVCTRL				(* (uint32_t *) HW_TC0 | 0x06)
#define HW_TC0_INTENCLR				(* (uint32_t *) HW_TC0 | 0x08)
#define HW_TC0_INTENSET				(* (uint32_t *) HW_TC0 | 0x09)
#define HW_TC0_INTFLAG				(* (uint32_t *) HW_TC0 | 0x0A)
#define HW_TC0_STATUS				(* (uint32_t *) HW_TC0 | 0x0B)
#define HW_TC0_WAVE					(* (uint32_t *) HW_TC0 | 0x0C)
#define HW_TC0_DRVCTRL				(* (uint32_t *) HW_TC0 | 0x0D)
#define HW_TC0_DBGCTRL				(* (uint32_t *) HW_TC0 | 0x0F)
#define HW_TC0_SYNCBUSY				(* (uint32_t *) HW_TC0 | 0x10)
#define HW_TC0_COUNT				(* (uint32_t *) HW_TC0 | 0x14)
//#define HW_TC0_PER					(* (uint32_t *) HW_TC0 | 0x1B)
#define HW_TC0_CC0					(* (uint32_t *) HW_TC0 | 0x1C)
#define HW_TC0_CC1					(* (uint32_t *) HW_TC0 | 0x20) // Defined for 32 bit mode
//#define HW_TC0_PERBUF				(* (uint32_t *) HW_TC0 | 0x2F)
#define HW_TC0_CCBUF0				(* (uint32_t *) HW_TC0 | 0x30)
#define HW_TC0_CCBUF1				(* (uint32_t *) HW_TC0 | 0x34)

#define HW_TC1_CTRLA				(* (uint32_t *) HW_TC1 | 0x00)
#define HW_TC1_CTRLBCLR				(* (uint32_t *) HW_TC1 | 0x04)
#define HW_TC1_CTRLBSET				(* (uint32_t *) HW_TC1 | 0x05)
#define HW_TC1_EVCTRL				(* (uint32_t *) HW_TC1 | 0x06)
#define HW_TC1_INTENCLR				(* (uint32_t *) HW_TC1 | 0x08)
#define HW_TC1_INTENSET				(* (uint32_t *) HW_TC1 | 0x09)
#define HW_TC1_INTFLAG				(* (uint32_t *) HW_TC1 | 0x0A)
#define HW_TC1_STATUS				(* (uint32_t *) HW_TC1 | 0x0B)
#define HW_TC1_WAVE					(* (uint32_t *) HW_TC1 | 0x0C)
#define HW_TC1_DRVCTRL				(* (uint32_t *) HW_TC1 | 0x0D)
#define HW_TC1_DBGCTRL				(* (uint32_t *) HW_TC1 | 0x0F)
#define HW_TC1_SYNCBUSY				(* (uint32_t *) HW_TC1 | 0x10)
#define HW_TC1_COUNT				(* (uint32_t *) HW_TC1 | 0x14)
//#define HW_TC1_PER					(* (uint32_t *) HW_TC1 | 0x1B)
#define HW_TC1_CC0					(* (uint32_t *) HW_TC1 | 0x1C)
//#define HW_TC1_CC1					(* (uint32_t *) HW_TC1 | 0x1D)
//#define HW_TC1_PERBUF				(* (uint32_t *) HW_TC1 | 0x2F)
#define HW_TC1_CCBUF0				(* (uint32_t *) HW_TC1 | 0x30)
#define HW_TC1_CCBUF1				(* (uint32_t *) HW_TC1 | 0x34)

#define HW_TC2_CTRLA				(* (uint32_t *) HW_TC2 | 0x00)
#define HW_TC2_CTRLBCLR				(* (uint32_t *) HW_TC2 | 0x04)
#define HW_TC2_CTRLBSET				(* (uint32_t *) HW_TC2 | 0x05)
#define HW_TC2_EVCTRL				(* (uint32_t *) HW_TC2 | 0x06)
#define HW_TC2_INTENCLR				(* (uint32_t *) HW_TC2 | 0x08)
#define HW_TC2_INTENSET				(* (uint32_t *) HW_TC2 | 0x09)
#define HW_TC2_INTFLAG				(* (uint32_t *) HW_TC2 | 0x0A)
#define HW_TC2_STATUS				(* (uint32_t *) HW_TC2 | 0x0B)
#define HW_TC2_WAVE					(* (uint32_t *) HW_TC2 | 0x0C)
#define HW_TC2_DRVCTRL				(* (uint32_t *) HW_TC2 | 0x0D)
#define HW_TC2_DBGCTRL				(* (uint32_t *) HW_TC2 | 0x0F)
#define HW_TC2_SYNCBUSY				(* (uint32_t *) HW_TC2 | 0x10)
#define HW_TC2_COUNT				(* (uint32_t *) HW_TC2 | 0x14)
//#define HW_TC2_PER					(* (uint32_t *) HW_TC2 | 0x1B)
#define HW_TC2_CC0					(* (uint32_t *) HW_TC2 | 0x1C)
#define HW_TC2_CC1					(* (uint32_t *) HW_TC2 | 0x1E) // Defined for 16 bit mode
//#define HW_TC2_PERBUF				(* (uint32_t *) HW_TC2 | 0x2F)
#define HW_TC2_CCBUF0				(* (uint32_t *) HW_TC2 | 0x30)
#define HW_TC2_CCBUF1				(* (uint32_t *) HW_TC2 | 0x34)


#define HW_TC3_CTRLA				(* (uint32_t *) HW_TC3 | 0x00)
#define HW_TC3_CTRLBCLR				(* (uint32_t *) HW_TC3 | 0x04)
#define HW_TC3_CTRLBSET				(* (uint32_t *) HW_TC3 | 0x05)
#define HW_TC3_EVCTRL				(* (uint32_t *) HW_TC3 | 0x06)
#define HW_TC3_INTENCLR				(* (uint32_t *) HW_TC3 | 0x08)
#define HW_TC3_INTENSET				(* (uint32_t *) HW_TC3 | 0x09)
#define HW_TC3_INTFLAG				(* (uint32_t *) HW_TC3 | 0x0A)
#define HW_TC3_STATUS				(* (uint32_t *) HW_TC3 | 0x0B)
#define HW_TC3_WAVE					(* (uint32_t *) HW_TC3 | 0x0C)
#define HW_TC3_DRVCTRL				(* (uint32_t *) HW_TC3 | 0x0D)
#define HW_TC3_DBGCTRL				(* (uint32_t *) HW_TC3 | 0x0F)
#define HW_TC3_SYNCBUSY				(* (uint32_t *) HW_TC3 | 0x10)
#define HW_TC3_COUNT				(* (uint32_t *) HW_TC3 | 0x14)
//#define HW_TC3_PER					(* (uint32_t *) HW_TC3 | 0x1B)
#define HW_TC3_CC0					(* (uint32_t *) HW_TC3 | 0x1C)
//#define HW_TC3_CC1					(* (uint32_t *) HW_TC3 | 0x1D)
//#define HW_TC3_PERBUF				(* (uint32_t *) HW_TC3 | 0x2F)
#define HW_TC3_CCBUF0				(* (uint32_t *) HW_TC3 | 0x30)
#define HW_TC3_CCBUF1				(* (uint32_t *) HW_TC3 | 0x34)

//timer masks//////////

#define HW_TCxCTRLA_ENABLE				0x00000002
#define HW_TCxCTRLA_DISABLE				0x00000000

#define HW_TCxCTRLA_COUNT16MODE			0x00000000
#define HW_TCxCTRLA_COUNT8MODE			0x00000004
#define HW_TCxCTRLA_COUNT32MODE			0x00000008

#define HW_TCxCTRLA_PRESCALER_DIV1		0x00000000
#define HW_TCxCTRLA_PRESCALER_DIV2		0x00000100
#define HW_TCxCTRLA_PRESCALER_DIV4		0x00000200
#define HW_TCxCTRLA_PRESCALER_DIV8		0x00000300
#define HW_TCxCTRLA_PRESCALER_DIV16		0x00000400
#define HW_TCxCTRLA_PRESCALER_DIV64		0x00000500
#define HW_TCxCTRLA_PRESCALER_DIV256	0x00000600
#define HW_TCxCTRLA_PRESCALER_DIV1024	0x00000700

#define HW_TCxCTRLBSET_COUNTUP			0x01
#define HW_TCxCTRLBSET_COUNTDOWN		0x00
#define HW_TCxCTRLBSET_RETRIGGER		0x20
#define HW_TCxCTRLBSET_STOP				0x40
#define HW_TCxCTRLBSET_UPDATA			0x60
#define HW_TCxCTRLBSET_READSYNC			0x80



/** @} */ // end of RAK4260Reggroup