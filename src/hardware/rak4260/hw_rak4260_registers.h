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
 
 #ifndef HW_RAK4260_REGISTERS_H
 #define HW_RAK4260_REGISTERS_H
 
 #ifndef HW_ARDUINO

#ifdef __cplusplus
 extern "C" {
#endif

#ifdef __cplusplus
  #define   __I     volatile             /*!< Defines 'read only' permissions */
#else
  #define   __I     volatile const       /*!< Defines 'read only' permissions */
#endif
#define     __O     volatile             /*!< Defines 'write only' permissions */
#define     __IO    volatile             /*!< Defines 'read / write' permissions */

/* following defines should be used for structure members */
#define     __IM     volatile const      /*! Defines 'read only' structure member permissions */
#define     __OM     volatile            /*! Defines 'write only' structure member permissions */
#define     __IOM    volatile            /*! Defines 'read / write' structure member permissions */

#include <stdint.h>
#ifndef __cplusplus
typedef volatile const uint32_t RoReg;   /**< Read only 32-bit register (volatile const unsigned int) */
typedef volatile const uint16_t RoReg16; /**< Read only 16-bit register (volatile const unsigned int) */
typedef volatile const uint8_t  RoReg8;  /**< Read only  8-bit register (volatile const unsigned int) */
#else
typedef volatile       uint32_t RoReg;   /**< Read only 32-bit register (volatile const unsigned int) */
typedef volatile       uint16_t RoReg16; /**< Read only 16-bit register (volatile const unsigned int) */
typedef volatile       uint8_t  RoReg8;  /**< Read only  8-bit register (volatile const unsigned int) */
#endif
typedef volatile       uint32_t WoReg;   /**< Write only 32-bit register (volatile unsigned int) */
typedef volatile       uint16_t WoReg16; /**< Write only 16-bit register (volatile unsigned int) */
typedef volatile       uint8_t  WoReg8;  /**< Write only  8-bit register (volatile unsigned int) */
typedef volatile       uint32_t RwReg;   /**< Read-Write 32-bit register (volatile unsigned int) */
typedef volatile       uint16_t RwReg16; /**< Read-Write 16-bit register (volatile unsigned int) */
typedef volatile       uint8_t  RwReg8;  /**< Read-Write  8-bit register (volatile unsigned int) */


#if !defined(SKIP_INTEGER_LITERALS)
#if defined(_U_) || defined(_L_) || defined(_UL_)
  #error "Integer Literals macros already defined elsewhere"
#endif
/* Macros that deal with adding suffixes to integer literal constants for C/C++ */
#define _U_(x)         x ## U            /**< C code: Unsigned integer literal constant value */
#define _L_(x)         x ## L            /**< C code: Long integer literal constant value */
#define _UL_(x)        x ## UL           /**< C code: Unsigned Long integer literal constant value */
#else /* Assembler */
#define _U_(x)         x                 /**< Assembler: Unsigned integer literal constant value */
#define _L_(x)         x                 /**< Assembler: Long integer literal constant value */
#define _UL_(x)        x                 /**< Assembler: Unsigned Long integer literal constant value */
#endif /* SKIP_INTEGER_LITERALS */


/** Interrupt Number Definition */
typedef enum IRQn
{
  /******  Cortex-M0+ Processor Exceptions Numbers *******************/
  NonMaskableInt_IRQn      = -14,/**<  2 Non Maskable Interrupt      */
  HardFault_IRQn           = -13,/**<  3 Hard Fault Interrupt        */
  SVCall_IRQn              = -5, /**< 11 SV Call Interrupt           */
  PendSV_IRQn              = -2, /**< 14 Pend SV Interrupt           */
  SysTick_IRQn             = -1, /**< 15 System Tick Interrupt       */
  /******  ATSAMR34J18B-specific Interrupt Numbers *********************/
  SYSTEM_IRQn              =  0, /**<  0 SAML21J18B System Interrupts */
  WDT_IRQn                 =  1, /**<  1 SAML21J18B Watchdog Timer (WDT) */
  RTC_IRQn                 =  2, /**<  2 SAML21J18B Real-Time Counter (RTC) */
  EIC_IRQn                 =  3, /**<  3 SAML21J18B External Interrupt Controller (EIC) */
  NVMCTRL_IRQn             =  4, /**<  4 SAML21J18B Non-Volatile Memory Controller (NVMCTRL) */
  DMAC_IRQn                =  5, /**<  5 SAML21J18B Direct Memory Access Controller (DMAC) */
  USB_IRQn                 =  6, /**<  6 SAML21J18B Universal Serial Bus (USB) */
  EVSYS_IRQn               =  7, /**<  7 SAML21J18B Event System Interface (EVSYS) */
  SERCOM0_IRQn             =  8, /**<  8 SAML21J18B Serial Communication Interface 0 (SERCOM0) */
  SERCOM1_IRQn             =  9, /**<  9 SAML21J18B Serial Communication Interface 1 (SERCOM1) */
  SERCOM2_IRQn             = 10, /**< 10 SAML21J18B Serial Communication Interface 2 (SERCOM2) */
  SERCOM3_IRQn             = 11, /**< 11 SAML21J18B Serial Communication Interface 3 (SERCOM3) */
  SERCOM4_IRQn             = 12, /**< 12 SAML21J18B Serial Communication Interface 4 (SERCOM4) */
  SERCOM5_IRQn             = 13, /**< 13 SAML21J18B Serial Communication Interface 5 (SERCOM5) */
  TCC0_IRQn                = 14, /**< 14 SAML21J18B Timer Counter Control 0 (TCC0) */
  TCC1_IRQn                = 15, /**< 15 SAML21J18B Timer Counter Control 1 (TCC1) */
  TCC2_IRQn                = 16, /**< 16 SAML21J18B Timer Counter Control 2 (TCC2) */
  TC0_IRQn                 = 17, /**< 17 SAML21J18B Basic Timer Counter 0 (TC0) */
  TC1_IRQn                 = 18, /**< 18 SAML21J18B Basic Timer Counter 1 (TC1) */
  TC2_IRQn                 = 19, /**< 19 SAML21J18B Basic Timer Counter 2 (TC2) */
  TC3_IRQn                 = 20, /**< 20 SAML21J18B Basic Timer Counter 3 (TC3) */
  TC4_IRQn                 = 21, /**< 21 SAML21J18B Basic Timer Counter 4 (TC4) */
  ADC_IRQn                 = 22, /**< 22 SAML21J18B Analog Digital Converter (ADC) */
  AC_IRQn                  = 23, /**< 23 SAML21J18B Analog Comparators (AC) */
  DAC_IRQn                 = 24, /**< 24 SAML21J18B Digital-to-Analog Converter (DAC) */
  PTC_IRQn                 = 25, /**< 25 SAML21J18B Peripheral Touch Controller (PTC) */
  AES_IRQn                 = 26, /**< 26 SAML21J18B Advanced Encryption Standard (AES) */
  TRNG_IRQn                = 27, /**< 27 SAML21J18B True Random Generator (TRNG) */

  PERIPH_COUNT_IRQn        = 29  /**< Number of peripheral IDs */
} IRQn_Type;

typedef struct _DeviceVectors
{
  /* Stack pointer */
  void* pvStack;

  /* Cortex-M handlers */
  void* pfnReset_Handler;
  void* pfnNonMaskableInt_Handler;
  void* pfnHardFault_Handler;
  void* pvReservedM12;
  void* pvReservedM11;
  void* pvReservedM10;
  void* pvReservedM9;
  void* pvReservedM8;
  void* pvReservedM7;
  void* pvReservedM6;
  void* pfnSVCall_Handler;
  void* pvReservedM4;
  void* pvReservedM3;
  void* pfnPendSV_Handler;
  void* pfnSysTick_Handler;

  /* Peripheral handlers */
  void* pfnSYSTEM_Handler;                /*  0 Main Clock, 32k Oscillators Control, Oscillators Control, Peripheral Access Controller, Power Manager, Supply Controller, Trigger Allocator */
  void* pfnWDT_Handler;                   /*  1 Watchdog Timer */
  void* pfnRTC_Handler;                   /*  2 Real-Time Counter */
  void* pfnEIC_Handler;                   /*  3 External Interrupt Controller */
  void* pfnNVMCTRL_Handler;               /*  4 Non-Volatile Memory Controller */
  void* pfnDMAC_Handler;                  /*  5 Direct Memory Access Controller */
  void* pfnUSB_Handler;                   /*  6 Universal Serial Bus */
  void* pfnEVSYS_Handler;                 /*  7 Event System Interface */
  void* pfnSERCOM0_Handler;               /*  8 Serial Communication Interface 0 */
  void* pfnSERCOM1_Handler;               /*  9 Serial Communication Interface 1 */
  void* pfnSERCOM2_Handler;               /* 10 Serial Communication Interface 2 */
  void* pfnSERCOM3_Handler;               /* 11 Serial Communication Interface 3 */
  void* pfnSERCOM4_Handler;               /* 12 Serial Communication Interface 4 */
  void* pfnSERCOM5_Handler;               /* 13 Serial Communication Interface 5 */
  void* pfnTCC0_Handler;                  /* 14 Timer Counter Control 0 */
  void* pfnTCC1_Handler;                  /* 15 Timer Counter Control 1 */
  void* pfnTCC2_Handler;                  /* 16 Timer Counter Control 2 */
  void* pfnTC0_Handler;                   /* 17 Basic Timer Counter 0 */
  void* pfnTC1_Handler;                   /* 18 Basic Timer Counter 1 */
  void* pfnTC2_Handler;                   /* 19 Basic Timer Counter 2 */
  void* pfnTC3_Handler;                   /* 20 Basic Timer Counter 3 */
  void* pfnTC4_Handler;                   /* 21 Basic Timer Counter 4 */
  void* pfnADC_Handler;                   /* 22 Analog Digital Converter */
  void* pfnAC_Handler;                    /* 23 Analog Comparators */
  void* pfnDAC_Handler;                   /* 24 Digital-to-Analog Converter */
  void* pfnPTC_Handler;                   /* 25 Peripheral Touch Controller */
  void* pfnAES_Handler;                   /* 26 Advanced Encryption Standard */
  void* pfnTRNG_Handler;                  /* 27 True Random Generator */
  void* pvReserved28;
} DeviceVectors;

/* Cortex-M0+ processor handlers */
void Reset_Handler               ( void );
void NonMaskableInt_Handler      ( void );
void HardFault_Handler           ( void );
void SVCall_Handler              ( void );
void PendSV_Handler              ( void );
void SysTick_Handler             ( void );

/* Peripherals handlers */
void SYSTEM_Handler              ( void );
void WDT_Handler                 ( void );
void RTC_Handler                 ( void );
void EIC_Handler                 ( void );
void NVMCTRL_Handler             ( void );
void DMAC_Handler                ( void );
void USB_Handler                 ( void );
void EVSYS_Handler               ( void );
void SERCOM0_Handler             ( void );
void SERCOM1_Handler             ( void );
void SERCOM2_Handler             ( void );
void SERCOM3_Handler             ( void );
void SERCOM4_Handler             ( void );
void SERCOM5_Handler             ( void );
void TCC0_Handler                ( void );
void TCC1_Handler                ( void );
void TCC2_Handler                ( void );
void TC0_Handler                 ( void );
void TC1_Handler                 ( void );
void TC2_Handler                 ( void );
void TC3_Handler                 ( void );
void TC4_Handler                 ( void );
void ADC_Handler                 ( void );
void AC_Handler                  ( void );
void DAC_Handler                 ( void );
void PTC_Handler                 ( void );
void AES_Handler                 ( void );
void TRNG_Handler                ( void );


/* Default empty handler */
void Dummy_Handler(void)
{
  for (;;) { }
}

/* Cortex-M0+ core handlers */
void HardFault_Handler(void) __attribute__ ((weak, alias("Dummy_Handler")));
void Reset_Handler    (void);
void NMI_Handler      (void) __attribute__ ((weak, alias("Dummy_Handler")));
void SVC_Handler      (void) __attribute__ ((weak, alias("Dummy_Handler")));
void PendSV_Handler   (void) __attribute__ ((weak, alias("Dummy_Handler")));
void SysTick_Handler  (void);

/* Peripherals handlers */
void PM_Handler       (void) __attribute__ ((weak, alias("Dummy_Handler")));
void SYSCTRL_Handler  (void) __attribute__ ((weak, alias("Dummy_Handler")));
void WDT_Handler      (void) __attribute__ ((weak, alias("Dummy_Handler")));
void RTC_Handler      (void) __attribute__ ((weak, alias("Dummy_Handler")));
void EIC_Handler      (void) __attribute__ ((weak, alias("Dummy_Handler")));
void NVMCTRL_Handler  (void) __attribute__ ((weak, alias("Dummy_Handler")));
void DMAC_Handler     (void) __attribute__ ((weak, alias("Dummy_Handler")));
void USB_Handler      (void) __attribute__ ((weak));
void EVSYS_Handler    (void) __attribute__ ((weak, alias("Dummy_Handler")));
void SERCOM0_Handler  (void) __attribute__ ((weak, alias("Dummy_Handler")));
void SERCOM1_Handler  (void) __attribute__ ((weak, alias("Dummy_Handler")));
void SERCOM2_Handler  (void) __attribute__ ((weak, alias("Dummy_Handler")));
void SERCOM3_Handler  (void) __attribute__ ((weak, alias("Dummy_Handler")));
void SERCOM4_Handler  (void) __attribute__ ((weak, alias("Dummy_Handler")));
void SERCOM5_Handler  (void) __attribute__ ((weak, alias("Dummy_Handler")));
void TCC0_Handler     (void) __attribute__ ((weak, alias("Dummy_Handler")));
void TCC1_Handler     (void) __attribute__ ((weak, alias("Dummy_Handler")));
void TCC2_Handler     (void) __attribute__ ((weak, alias("Dummy_Handler")));
void TC3_Handler      (void) __attribute__ ((weak, alias("Dummy_Handler")));
void TC4_Handler      (void) __attribute__ ((weak, alias("Dummy_Handler")));
void TC5_Handler      (void) __attribute__ ((weak)); // Used in Tone.cpp
void TC6_Handler      (void) __attribute__ ((weak, alias("Dummy_Handler")));
void TC7_Handler      (void) __attribute__ ((weak, alias("Dummy_Handler")));
void ADC_Handler      (void) __attribute__ ((weak, alias("Dummy_Handler")));
void AC_Handler       (void) __attribute__ ((weak, alias("Dummy_Handler")));
void DAC_Handler      (void) __attribute__ ((weak, alias("Dummy_Handler")));
void PTC_Handler      (void) __attribute__ ((weak, alias("Dummy_Handler")));
void I2S_Handler      (void) __attribute__ ((weak, alias("Dummy_Handler")));

/* Initialize segments */
extern uint32_t __etext;
extern uint32_t __data_start__;
extern uint32_t __data_end__;
extern uint32_t __bss_start__;
extern uint32_t __bss_end__;
extern uint32_t __StackTop;

/* Exception Table */
__attribute__ ((section(".isr_vector"))) const DeviceVectors exception_table =
{
  /* Configure Initial Stack Pointer, using linker-generated symbols */
  (void*) (&__StackTop),

  (void*) Reset_Handler,
  (void*) NMI_Handler,
  (void*) HardFault_Handler,
  (void*) (0UL), /* Reserved */
  (void*) (0UL), /* Reserved */
  (void*) (0UL), /* Reserved */
  (void*) (0UL), /* Reserved */
  (void*) (0UL), /* Reserved */
  (void*) (0UL), /* Reserved */
  (void*) (0UL), /* Reserved */
  (void*) SVC_Handler,
  (void*) (0UL), /* Reserved */
  (void*) (0UL), /* Reserved */
  (void*) PendSV_Handler,
  (void*) SysTick_Handler,

  /* Configurable interrupts */
  (void*) PM_Handler,             /*  0 Power Manager */
  (void*) SYSCTRL_Handler,        /*  1 System Control */
  (void*) WDT_Handler,            /*  2 Watchdog Timer */
  (void*) RTC_Handler,            /*  3 Real-Time Counter */
  (void*) EIC_Handler,            /*  4 External Interrupt Controller */
  (void*) NVMCTRL_Handler,        /*  5 Non-Volatile Memory Controller */
  (void*) DMAC_Handler,           /*  6 Direct Memory Access Controller */
  (void*) USB_Handler,            /*  7 Universal Serial Bus */
  (void*) EVSYS_Handler,          /*  8 Event System Interface */
  (void*) SERCOM0_Handler,        /*  9 Serial Communication Interface 0 */
  (void*) SERCOM1_Handler,        /* 10 Serial Communication Interface 1 */
  (void*) SERCOM2_Handler,        /* 11 Serial Communication Interface 2 */
  (void*) SERCOM3_Handler,        /* 12 Serial Communication Interface 3 */
  (void*) SERCOM4_Handler,        /* 13 Serial Communication Interface 4 */
  (void*) SERCOM5_Handler,        /* 14 Serial Communication Interface 5 */
  (void*) TCC0_Handler,           /* 15 Timer Counter Control 0 */
  (void*) TCC1_Handler,           /* 16 Timer Counter Control 1 */
  (void*) TCC2_Handler,           /* 17 Timer Counter Control 2 */
  (void*) TC3_Handler,            /* 18 Basic Timer Counter 0 */
  (void*) TC4_Handler,            /* 19 Basic Timer Counter 1 */
  (void*) TC5_Handler,            /* 20 Basic Timer Counter 2 */
  (void*) TC6_Handler,            /* 21 Basic Timer Counter 3 */
  (void*) TC7_Handler,            /* 22 Basic Timer Counter 4 */
  (void*) ADC_Handler,            /* 23 Analog Digital Converter */
  (void*) AC_Handler,             /* 24 Analog Comparators */
  (void*) DAC_Handler,            /* 25 Digital Analog Converter */
  (void*) PTC_Handler,            /* 26 Peripheral Touch Controller */
  (void*) I2S_Handler,            /* 27 Inter-IC Sound Interface */
  (void*) (0UL),                  /* Reserved */
};



/*
 * \brief Configuration of the Cortex-M0+ Processor and Core Peripherals
 */

#define __CM0PLUS_REV          1         /*!< Core revision r0p1 */
#define __MPU_PRESENT          0         /*!< MPU present or not */
#define __NVIC_PRIO_BITS       2         /*!< Number of bits used for Priority Levels */
#define __VTOR_PRESENT         1         /*!< VTOR present or not */
#define __Vendor_SysTickConfig 0         /*!< Set to 1 if different SysTick Config is used */



//struct peripheral includes
#include "hw_rak4260_power.h"
#include "hw_rak4260_mclk.h"
#include "hw_rak4260_tc.h"
#include "hw_rak4260_rtc.h"
#include "hw_rak4260_gclk.h"
#include "hw_rak4260_scs.h"


//#define AC                ((Ac       *)0x43001000UL) /**< \brief (AC) APB Base Address */
//#define AC_INST_NUM       1                          /**< \brief (AC) Number of instances */
//#define AC_INSTS          { AC }                     /**< \brief (AC) Instances List */

//#define ADC               ((Adc      *)0x43000C00UL) /**< \brief (ADC) APB Base Address */
//#define ADC_INST_NUM      1                          /**< \brief (ADC) Number of instances */
//#define ADC_INSTS         { ADC }                    /**< \brief (ADC) Instances List */

//#define AES               ((Aes      *)0x42003400UL) /**< \brief (AES) APB Base Address */
//#define AES_INST_NUM      1                          /**< \brief (AES) Number of instances */
//#define AES_INSTS         { AES }                    /**< \brief (AES) Instances List */

//#define CCL               ((Ccl      *)0x43001C00UL) /**< \brief (CCL) APB Base Address */
//#define CCL_INST_NUM      1                          /**< \brief (CCL) Number of instances */
//#define CCL_INSTS         { CCL }                    /**< \brief (CCL) Instances List */

//#define DAC               ((Dac      *)0x42003000UL) /**< \brief (DAC) APB Base Address */
//#define DAC_INST_NUM      1                          /**< \brief (DAC) Number of instances */
//#define DAC_INSTS         { DAC }                    /**< \brief (DAC) Instances List */

//#define DMAC              ((Dmac     *)0x44000400UL) /**< \brief (DMAC) APB Base Address */
//#define DMAC_INST_NUM     1                          /**< \brief (DMAC) Number of instances */
//#define DMAC_INSTS        { DMAC }                   /**< \brief (DMAC) Instances List */

//#define DSU               ((Dsu      *)0x41002000UL) /**< \brief (DSU) APB Base Address */
//#define DSU_INST_NUM      1                          /**< \brief (DSU) Number of instances */
//#define DSU_INSTS         { DSU }                    /**< \brief (DSU) Instances List */

//#define EIC               ((Eic      *)0x40002400UL) /**< \brief (EIC) APB Base Address */
//#define EIC_INST_NUM      1                          /**< \brief (EIC) Number of instances */
//#define EIC_INSTS         { EIC }                    /**< \brief (EIC) Instances List */

//#define EVSYS             ((Evsys    *)0x43000000UL) /**< \brief (EVSYS) APB Base Address */
//#define EVSYS_INST_NUM    1                          /**< \brief (EVSYS) Number of instances */
//#define EVSYS_INSTS       { EVSYS }                  /**< \brief (EVSYS) Instances List */

#define GCLK              ((Gclk     *)0x40001800UL) /**< \brief (GCLK) APB Base Address */
#define GCLK_INST_NUM     1                          /**< \brief (GCLK) Number of instances */
#define GCLK_INSTS        { GCLK }                   /**< \brief (GCLK) Instances List */

#define MCLK              ((Mclk     *)0x40000400UL) /**< \brief (MCLK) APB Base Address */
#define MCLK_INST_NUM     1                          /**< \brief (MCLK) Number of instances */
#define MCLK_INSTS        { MCLK }                   /**< \brief (MCLK) Instances List */

//#define MTB               ((Mtb      *)0x41006000UL) /**< \brief (MTB) APB Base Address */
//#define MTB_INST_NUM      1                          /**< \brief (MTB) Number of instances */
//#define MTB_INSTS         { MTB }                    /**< \brief (MTB) Instances List */

//#define NVMCTRL           ((Nvmctrl  *)0x41004000UL) /**< \brief (NVMCTRL) APB Base Address */
//#define NVMCTRL_CAL                   (0x00800000UL) /**< \brief (NVMCTRL) CAL Base Address */
//#define NVMCTRL_LOCKBIT               (0x00802000UL) /**< \brief (NVMCTRL) LOCKBIT Base Address */
//#define NVMCTRL_OTP1                  (0x00806000UL) /**< \brief (NVMCTRL) OTP1 Base Address */
//#define NVMCTRL_OTP2                  (0x00806008UL) /**< \brief (NVMCTRL) OTP2 Base Address */
//#define NVMCTRL_OTP3                  (0x00806010UL) /**< \brief (NVMCTRL) OTP3 Base Address */
//#define NVMCTRL_OTP4                  (0x00806018UL) /**< \brief (NVMCTRL) OTP4 Base Address */
//#define NVMCTRL_OTP5                  (0x00806020UL) /**< \brief (NVMCTRL) OTP5 Base Address */
//#define NVMCTRL_TEMP_LOG              (0x00806030UL) /**< \brief (NVMCTRL) TEMP_LOG Base Address */
//#define NVMCTRL_USER                  (0x00804000UL) /**< \brief (NVMCTRL) USER Base Address */
//#define NVMCTRL_INST_NUM  1                          /**< \brief (NVMCTRL) Number of instances */
//#define NVMCTRL_INSTS     { NVMCTRL }                /**< \brief (NVMCTRL) Instances List */

//#define OPAMP             ((Opamp    *)0x43001800UL) /**< \brief (OPAMP) APB Base Address */
//#define OPAMP_INST_NUM    1                          /**< \brief (OPAMP) Number of instances */
//#define OPAMP_INSTS       { OPAMP }                  /**< \brief (OPAMP) Instances List */

#define OSCCTRL           ((Oscctrl  *)0x40000C00UL) /**< \brief (OSCCTRL) APB Base Address */
#define OSCCTRL_INST_NUM  1                          /**< \brief (OSCCTRL) Number of instances */
#define OSCCTRL_INSTS     { OSCCTRL }                /**< \brief (OSCCTRL) Instances List */

#define OSC32KCTRL        ((Osc32kctrl *)0x40001000UL) /**< \brief (OSC32KCTRL) APB Base Address */
#define OSC32KCTRL_INST_NUM 1                          /**< \brief (OSC32KCTRL) Number of instances */
#define OSC32KCTRL_INSTS  { OSC32KCTRL }             /**< \brief (OSC32KCTRL) Instances List */

//#define PAC               ((Pac      *)0x44000000UL) /**< \brief (PAC) APB Base Address */
//#define PAC_INST_NUM      1                          /**< \brief (PAC) Number of instances */
//#define PAC_INSTS         { PAC }                    /**< \brief (PAC) Instances List */

#define PM                ((Pm       *)0x40000000UL) /**< \brief (PM) APB Base Address */
#define PM_INST_NUM       1                          /**< \brief (PM) Number of instances */
#define PM_INSTS          { PM }                     /**< \brief (PM) Instances List */

//#define PORT              ((Port     *)0x40002800UL) /**< \brief (PORT) APB Base Address */
//#define PORT_IOBUS        ((Port     *)0x60000000UL) /**< \brief (PORT) IOBUS Base Address */
//#define PORT_INST_NUM     1                          /**< \brief (PORT) Number of instances */
//#define PORT_INSTS        { PORT }                   /**< \brief (PORT) Instances List */
//#define PORT_IOBUS_INST_NUM 1                          /**< \brief (PORT) Number of instances */
//#define PORT_IOBUS_INSTS  { PORT_IOBUS }             /**< \brief (PORT) Instances List */

//#define PTC               ((void     *)0x43001400UL) /**< \brief (PTC) APB Base Address */
//#define PTC_GCLK_ID       33
//#define PTC_INST_NUM      1                          /**< \brief (PTC) Number of instances */
//#define PTC_INSTS         { PTC }                    /**< \brief (PTC) Instances List */

//#define RSTC              ((Rstc     *)0x40000800UL) /**< \brief (RSTC) APB Base Address */
//#define RSTC_INST_NUM     1                          /**< \brief (RSTC) Number of instances */
//#define RSTC_INSTS        { RSTC }                   /**< \brief (RSTC) Instances List */

#define RTC               ((Rtc      *)0x40002000UL) /**< \brief (RTC) APB Base Address */
#define RTC_INST_NUM      1                          /**< \brief (RTC) Number of instances */
#define RTC_INSTS         { RTC }                    /**< \brief (RTC) Instances List */

//#define SERCOM0           ((Sercom   *)0x42000000UL) /**< \brief (SERCOM0) APB Base Address */
//#define SERCOM1           ((Sercom   *)0x42000400UL) /**< \brief (SERCOM1) APB Base Address */
//#define SERCOM2           ((Sercom   *)0x42000800UL) /**< \brief (SERCOM2) APB Base Address */
//#define SERCOM3           ((Sercom   *)0x42000C00UL) /**< \brief (SERCOM3) APB Base Address */
//#define SERCOM4           ((Sercom   *)0x42001000UL) /**< \brief (SERCOM4) APB Base Address */
//#define SERCOM5           ((Sercom   *)0x43000400UL) /**< \brief (SERCOM5) APB Base Address */
//#define SERCOM_INST_NUM   6                          /**< \brief (SERCOM) Number of instances */
//#define SERCOM_INSTS      { SERCOM0, SERCOM1, SERCOM2, SERCOM3, SERCOM4, SERCOM5 } /**< \brief (SERCOM) Instances List */

//#define SUPC              ((Supc     *)0x40001400UL) /**< \brief (SUPC) APB Base Address */
//#define SUPC_INST_NUM     1                          /**< \brief (SUPC) Number of instances */
//#define SUPC_INSTS        { SUPC }                   /**< \brief (SUPC) Instances List */

#define TC0               ((Tc       *)0x42002000UL) /**< \brief (TC0) APB Base Address */
#define TC1               ((Tc       *)0x42002400UL) /**< \brief (TC1) APB Base Address */
#define TC2               ((Tc       *)0x42002800UL) /**< \brief (TC2) APB Base Address */
#define TC3               ((Tc       *)0x42002C00UL) /**< \brief (TC3) APB Base Address */
#define TC4               ((Tc       *)0x43000800UL) /**< \brief (TC4) APB Base Address */
#define TC_INST_NUM       5                          /**< \brief (TC) Number of instances */
#define TC_INSTS          { TC0, TC1, TC2, TC3, TC4 } /**< \brief (TC) Instances List */

//#define TCC0              ((Tcc      *)0x42001400UL) /**< \brief (TCC0) APB Base Address */
//#define TCC1              ((Tcc      *)0x42001800UL) /**< \brief (TCC1) APB Base Address */
//#define TCC2              ((Tcc      *)0x42001C00UL) /**< \brief (TCC2) APB Base Address */
//#define TCC_INST_NUM      3                          /**< \brief (TCC) Number of instances */
//#define TCC_INSTS         { TCC0, TCC1, TCC2 }       /**< \brief (TCC) Instances List */

//#define TRNG              ((Trng     *)0x42003800UL) /**< \brief (TRNG) APB Base Address */
//#define TRNG_INST_NUM     1                          /**< \brief (TRNG) Number of instances */
//#define TRNG_INSTS        { TRNG }                   /**< \brief (TRNG) Instances List */

//#define USB               ((Usb      *)0x41000000UL) /**< \brief (USB) APB Base Address */
//#define USB_INST_NUM      1                          /**< \brief (USB) Number of instances */
//#define USB_INSTS         { USB }                    /**< \brief (USB) Instances List */

//define WDT               ((Wdt      *)0x40001C00UL) /**< \brief (WDT) APB Base Address */
//#define WDT_INST_NUM      1                          /**< \brief (WDT) Number of instances */
//#define WDT_INSTS         { WDT }                    /**< \brief (WDT) Instances List */


#ifdef __cplusplus
}
#endif


 

#endif //HW_ARDUINO

#ifdef __cplusplus
 extern "C" {
#endif
#define SYSCTRL_AIRCR	  ((SCS_AIRCR_Type *) 0xE000ED0C)
#ifdef __cplusplus
}
#endif

#endif //HW_RAK4260_REGISTERS_H

/** @} */ // end of RAK4260Reggroup




/*
#define HW_POWER_BASEADDRESS			0x40000000


#define HW_POWER_AIRCR					(* (uint32_t *) 0xE000ED0C)


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

*/

