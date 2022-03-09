#ifndef HW_RAK4260_POWER_H
#define HW_RAK4260_POWER_H


#define HW_POWER_U2240
#define REV_PM                      0x102

/* -------- HW_POWER_CTRLA : (HW_POWER Offset: 0x00) (R/W  8) Control A -------- */
typedef union {
  struct {
    uint8_t  :2;               /*!< bit:  0.. 1  Reserved                           */
    uint8_t  IORET:1;          /*!< bit:      2  I/O Retention                      */
    uint8_t  :5;               /*!< bit:  3.. 7  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} HW_POWER_CTRLA_Type;

#define HW_POWER_CTRLA_OFFSET             0x00         /**< \brief (HW_POWER_CTRLA offset) Control A */
#define HW_POWER_CTRLA_RESETVALUE         _U_(0x00)    /**< \brief (HW_POWER_CTRLA reset_value) Control A */

#define HW_POWER_CTRLA_IORET_Pos          2            /**< \brief (HW_POWER_CTRLA) I/O Retention */
#define HW_POWER_CTRLA_IORET              (_U_(0x1) << HW_POWER_CTRLA_IORET_Pos)
#define HW_POWER_CTRLA_MASK               _U_(0x04)    /**< \brief (HW_POWER_CTRLA) MASK Register */

/* -------- HW_POWER_SLEEPCFG : (HW_POWER Offset: 0x01) (R/W  8) Sleep Configuration -------- */
typedef union {
  struct {
    uint8_t  SLEEPMODE:3;      /*!< bit:  0.. 2  Sleep Mode                         */
    uint8_t  :5;               /*!< bit:  3.. 7  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} HW_POWER_SLEEPCFG_Type;

#define HW_POWER_SLEEPCFG_OFFSET          0x01         /**< \brief (HW_POWER_SLEEPCFG offset) Sleep Configuration */
#define HW_POWER_SLEEPCFG_RESETVALUE      _U_(0x02)    /**< \brief (HW_POWER_SLEEPCFG reset_value) Sleep Configuration */

#define HW_POWER_SLEEPCFG_SLEEPMODE_Pos   0            /**< \brief (HW_POWER_SLEEPCFG) Sleep Mode */
#define HW_POWER_SLEEPCFG_SLEEPMODE_Msk   (_U_(0x7) << HW_POWER_SLEEPCFG_SLEEPMODE_Pos)
#define HW_POWER_SLEEPCFG_SLEEPMODE(value) (HW_POWER_SLEEPCFG_SLEEPMODE_Msk & ((value) << HW_POWER_SLEEPCFG_SLEEPMODE_Pos))
#define   HW_POWER_SLEEPCFG_SLEEPMODE_IDLE_Val  _U_(0x2)   /**< \brief (HW_POWER_SLEEPCFG) CPU, AHBx, and APBx clocks are OFF */
#define   HW_POWER_SLEEPCFG_SLEEPMODE_STANDBY_Val _U_(0x4)   /**< \brief (HW_POWER_SLEEPCFG) All Clocks are OFF */
#define   HW_POWER_SLEEPCFG_SLEEPMODE_BACKUP_Val _U_(0x5)   /**< \brief (HW_POWER_SLEEPCFG) Only Backup domain is powered ON */
#define   HW_POWER_SLEEPCFG_SLEEPMODE_OFF_Val   _U_(0x6)   /**< \brief (HW_POWER_SLEEPCFG) All power domains are powered OFF */
#define HW_POWER_SLEEPCFG_SLEEPMODE_IDLE  (HW_POWER_SLEEPCFG_SLEEPMODE_IDLE_Val << HW_POWER_SLEEPCFG_SLEEPMODE_Pos)
#define HW_POWER_SLEEPCFG_SLEEPMODE_STANDBY (HW_POWER_SLEEPCFG_SLEEPMODE_STANDBY_Val << HW_POWER_SLEEPCFG_SLEEPMODE_Pos)
#define HW_POWER_SLEEPCFG_SLEEPMODE_BACKUP (HW_POWER_SLEEPCFG_SLEEPMODE_BACKUP_Val << HW_POWER_SLEEPCFG_SLEEPMODE_Pos)
#define HW_POWER_SLEEPCFG_SLEEPMODE_OFF   (HW_POWER_SLEEPCFG_SLEEPMODE_OFF_Val << HW_POWER_SLEEPCFG_SLEEPMODE_Pos)
#define HW_POWER_SLEEPCFG_MASK            _U_(0x07)    /**< \brief (HW_POWER_SLEEPCFG) MASK Register */

/* -------- HW_POWER_PLCFG : (HW_POWER Offset: 0x02) (R/W  8) Performance Level Configuration -------- */
typedef union {
  struct {
    uint8_t  PLSEL:2;          /*!< bit:  0.. 1  Performance Level Select           */
    uint8_t  :5;               /*!< bit:  2.. 6  Reserved                           */
    uint8_t  PLDIS:1;          /*!< bit:      7  Performance Level Disable          */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} HW_POWER_PLCFG_Type;

#define HW_POWER_PLCFG_OFFSET             0x02         /**< \brief (HW_POWER_PLCFG offset) Performance Level Configuration */
#define HW_POWER_PLCFG_RESETVALUE         _U_(0x00)    /**< \brief (HW_POWER_PLCFG reset_value) Performance Level Configuration */

#define HW_POWER_PLCFG_PLSEL_Pos          0            /**< \brief (HW_POWER_PLCFG) Performance Level Select */
#define HW_POWER_PLCFG_PLSEL_Msk          (_U_(0x3) << HW_POWER_PLCFG_PLSEL_Pos)
#define HW_POWER_PLCFG_PLSEL(value)       (HW_POWER_PLCFG_PLSEL_Msk & ((value) << HW_POWER_PLCFG_PLSEL_Pos))
#define   HW_POWER_PLCFG_PLSEL_PL0_Val          _U_(0x0)   /**< \brief (HW_POWER_PLCFG) Performance Level 0 */
#define   HW_POWER_PLCFG_PLSEL_PL1_Val          _U_(0x1)   /**< \brief (HW_POWER_PLCFG) Performance Level 1 */
#define   HW_POWER_PLCFG_PLSEL_PL2_Val          _U_(0x2)   /**< \brief (HW_POWER_PLCFG) Performance Level 2 */
#define HW_POWER_PLCFG_PLSEL_PL0          (HW_POWER_PLCFG_PLSEL_PL0_Val        << HW_POWER_PLCFG_PLSEL_Pos)
#define HW_POWER_PLCFG_PLSEL_PL1          (HW_POWER_PLCFG_PLSEL_PL1_Val        << HW_POWER_PLCFG_PLSEL_Pos)
#define HW_POWER_PLCFG_PLSEL_PL2          (HW_POWER_PLCFG_PLSEL_PL2_Val        << HW_POWER_PLCFG_PLSEL_Pos)
#define HW_POWER_PLCFG_PLDIS_Pos          7            /**< \brief (HW_POWER_PLCFG) Performance Level Disable */
#define HW_POWER_PLCFG_PLDIS              (_U_(0x1) << HW_POWER_PLCFG_PLDIS_Pos)
#define HW_POWER_PLCFG_MASK               _U_(0x83)    /**< \brief (HW_POWER_PLCFG) MASK Register */

/* -------- HW_POWER_INTENCLR : (HW_POWER Offset: 0x04) (R/W  8) Interrupt Enable Clear -------- */
typedef union {
  struct {
    uint8_t  PLRDY:1;          /*!< bit:      0  Performance Level Interrupt Enable */
    uint8_t  :7;               /*!< bit:  1.. 7  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} HW_POWER_INTENCLR_Type;

#define HW_POWER_INTENCLR_OFFSET          0x04         /**< \brief (HW_POWER_INTENCLR offset) Interrupt Enable Clear */
#define HW_POWER_INTENCLR_RESETVALUE      _U_(0x00)    /**< \brief (HW_POWER_INTENCLR reset_value) Interrupt Enable Clear */

#define HW_POWER_INTENCLR_PLRDY_Pos       0            /**< \brief (HW_POWER_INTENCLR) Performance Level Interrupt Enable */
#define HW_POWER_INTENCLR_PLRDY           (_U_(0x1) << HW_POWER_INTENCLR_PLRDY_Pos)
#define HW_POWER_INTENCLR_MASK            _U_(0x01)    /**< \brief (HW_POWER_INTENCLR) MASK Register */

/* -------- HW_POWER_INTENSET : (HW_POWER Offset: 0x05) (R/W  8) Interrupt Enable Set -------- */
typedef union {
  struct {
    uint8_t  PLRDY:1;          /*!< bit:      0  Performance Level Ready interrupt Enable */
    uint8_t  :7;               /*!< bit:  1.. 7  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} HW_POWER_INTENSET_Type;

#define HW_POWER_INTENSET_OFFSET          0x05         /**< \brief (HW_POWER_INTENSET offset) Interrupt Enable Set */
#define HW_POWER_INTENSET_RESETVALUE      _U_(0x00)    /**< \brief (HW_POWER_INTENSET reset_value) Interrupt Enable Set */

#define HW_POWER_INTENSET_PLRDY_Pos       0            /**< \brief (HW_POWER_INTENSET) Performance Level Ready interrupt Enable */
#define HW_POWER_INTENSET_PLRDY           (_U_(0x1) << HW_POWER_INTENSET_PLRDY_Pos)
#define HW_POWER_INTENSET_MASK            _U_(0x01)    /**< \brief (HW_POWER_INTENSET) MASK Register */

/* -------- HW_POWER_INTFLAG : (HW_POWER Offset: 0x06) (R/W  8) Interrupt Flag Status and Clear -------- */
typedef union { // __I to avoid read-modify-write on write-to-clear register
  struct {
    __I uint8_t  PLRDY:1;          /*!< bit:      0  Performance Level Ready            */
    __I uint8_t  :7;               /*!< bit:  1.. 7  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} HW_POWER_INTFLAG_Type;

#define HW_POWER_INTFLAG_OFFSET           0x06         /**< \brief (HW_POWER_INTFLAG offset) Interrupt Flag Status and Clear */
#define HW_POWER_INTFLAG_RESETVALUE       _U_(0x00)    /**< \brief (HW_POWER_INTFLAG reset_value) Interrupt Flag Status and Clear */

#define HW_POWER_INTFLAG_PLRDY_Pos        0            /**< \brief (HW_POWER_INTFLAG) Performance Level Ready */
#define HW_POWER_INTFLAG_PLRDY            (_U_(0x1) << HW_POWER_INTFLAG_PLRDY_Pos)
#define HW_POWER_INTFLAG_MASK             _U_(0x01)    /**< \brief (HW_POWER_INTFLAG) MASK Register */

/* -------- HW_POWER_STDBYCFG : (HW_POWER Offset: 0x08) (R/W 16) Standby Configuration -------- */
typedef union {
  struct {
    uint16_t PDCFG:2;          /*!< bit:  0.. 1  Power Domain Configuration         */
    uint16_t :2;               /*!< bit:  2.. 3  Reserved                           */
    uint16_t DPGPD0:1;         /*!< bit:      4  Dynamic Power Gating for PD0       */
    uint16_t DPGPD1:1;         /*!< bit:      5  Dynamic Power Gating for PD1       */
    uint16_t VREGSMOD:2;       /*!< bit:  6.. 7  Voltage Regulator Standby mode     */
    uint16_t LINKPD:2;         /*!< bit:  8.. 9  Linked Power Domain                */
    uint16_t BBIASHS:2;        /*!< bit: 10..11  Back Bias for HMCRAMCHS            */
    uint16_t BBIASLP:2;        /*!< bit: 12..13  Back Bias for HMCRAMCLP            */
    uint16_t BBIASPP:2;        /*!< bit: 14..15  Back Bias for PicoPram             */
  } bit;                       /*!< Structure used for bit  access                  */
  uint16_t reg;                /*!< Type      used for register access              */
} HW_POWER_STDBYCFG_Type;

#define HW_POWER_STDBYCFG_OFFSET          0x08         /**< \brief (HW_POWER_STDBYCFG offset) Standby Configuration */
#define HW_POWER_STDBYCFG_RESETVALUE      _U_(0x0000)  /**< \brief (HW_POWER_STDBYCFG reset_value) Standby Configuration */

#define HW_POWER_STDBYCFG_PDCFG_Pos       0            /**< \brief (HW_POWER_STDBYCFG) Power Domain Configuration */
#define HW_POWER_STDBYCFG_PDCFG_Msk       (_U_(0x3) << HW_POWER_STDBYCFG_PDCFG_Pos)
#define HW_POWER_STDBYCFG_PDCFG(value)    (HW_POWER_STDBYCFG_PDCFG_Msk & ((value) << HW_POWER_STDBYCFG_PDCFG_Pos))
#define   HW_POWER_STDBYCFG_PDCFG_DEFAULT_Val   _U_(0x0)   /**< \brief (HW_POWER_STDBYCFG) All power domains switching is handled by hardware. */
#define   HW_POWER_STDBYCFG_PDCFG_PD0_Val       _U_(0x1)   /**< \brief (HW_POWER_STDBYCFG) PD0 is forced ACTIVE. PD1 and PD2 power domains switching is handled by hardware. */
#define   HW_POWER_STDBYCFG_PDCFG_PD01_Val      _U_(0x2)   /**< \brief (HW_POWER_STDBYCFG) PD0 and PD1 are forced ACTIVE. PD2 power domain switching is handled by hardware. */
#define   HW_POWER_STDBYCFG_PDCFG_PD012_Val     _U_(0x3)   /**< \brief (HW_POWER_STDBYCFG) All power domains are forced ACTIVE. */
#define HW_POWER_STDBYCFG_PDCFG_DEFAULT   (HW_POWER_STDBYCFG_PDCFG_DEFAULT_Val << HW_POWER_STDBYCFG_PDCFG_Pos)
#define HW_POWER_STDBYCFG_PDCFG_PD0       (HW_POWER_STDBYCFG_PDCFG_PD0_Val     << HW_POWER_STDBYCFG_PDCFG_Pos)
#define HW_POWER_STDBYCFG_PDCFG_PD01      (HW_POWER_STDBYCFG_PDCFG_PD01_Val    << HW_POWER_STDBYCFG_PDCFG_Pos)
#define HW_POWER_STDBYCFG_PDCFG_PD012     (HW_POWER_STDBYCFG_PDCFG_PD012_Val   << HW_POWER_STDBYCFG_PDCFG_Pos)
#define HW_POWER_STDBYCFG_DPGPD0_Pos      4            /**< \brief (HW_POWER_STDBYCFG) Dynamic Power Gating for PD0 */
#define HW_POWER_STDBYCFG_DPGPD0          (_U_(0x1) << HW_POWER_STDBYCFG_DPGPD0_Pos)
#define HW_POWER_STDBYCFG_DPGPD1_Pos      5            /**< \brief (HW_POWER_STDBYCFG) Dynamic Power Gating for PD1 */
#define HW_POWER_STDBYCFG_DPGPD1          (_U_(0x1) << HW_POWER_STDBYCFG_DPGPD1_Pos)
#define HW_POWER_STDBYCFG_VREGSMOD_Pos    6            /**< \brief (HW_POWER_STDBYCFG) Voltage Regulator Standby mode */
#define HW_POWER_STDBYCFG_VREGSMOD_Msk    (_U_(0x3) << HW_POWER_STDBYCFG_VREGSMOD_Pos)
#define HW_POWER_STDBYCFG_VREGSMOD(value) (HW_POWER_STDBYCFG_VREGSMOD_Msk & ((value) << HW_POWER_STDBYCFG_VREGSMOD_Pos))
#define   HW_POWER_STDBYCFG_VREGSMOD_AUTO_Val   _U_(0x0)   /**< \brief (HW_POWER_STDBYCFG) Automatic mode */
#define   HW_POWER_STDBYCFG_VREGSMOD_PERFORMANCE_Val _U_(0x1)   /**< \brief (HW_POWER_STDBYCFG) Performance oriented */
#define   HW_POWER_STDBYCFG_VREGSMOD_LP_Val     _U_(0x2)   /**< \brief (HW_POWER_STDBYCFG) Low Power oriented */
#define HW_POWER_STDBYCFG_VREGSMOD_AUTO   (HW_POWER_STDBYCFG_VREGSMOD_AUTO_Val << HW_POWER_STDBYCFG_VREGSMOD_Pos)
#define HW_POWER_STDBYCFG_VREGSMOD_PERFORMANCE (HW_POWER_STDBYCFG_VREGSMOD_PERFORMANCE_Val << HW_POWER_STDBYCFG_VREGSMOD_Pos)
#define HW_POWER_STDBYCFG_VREGSMOD_LP     (HW_POWER_STDBYCFG_VREGSMOD_LP_Val   << HW_POWER_STDBYCFG_VREGSMOD_Pos)
#define HW_POWER_STDBYCFG_LINKPD_Pos      8            /**< \brief (HW_POWER_STDBYCFG) Linked Power Domain */
#define HW_POWER_STDBYCFG_LINKPD_Msk      (_U_(0x3) << HW_POWER_STDBYCFG_LINKPD_Pos)
#define HW_POWER_STDBYCFG_LINKPD(value)   (HW_POWER_STDBYCFG_LINKPD_Msk & ((value) << HW_POWER_STDBYCFG_LINKPD_Pos))
#define   HW_POWER_STDBYCFG_LINKPD_DEFAULT_Val  _U_(0x0)   /**< \brief (HW_POWER_STDBYCFG) Power domains are not linked */
#define   HW_POWER_STDBYCFG_LINKPD_PD01_Val     _U_(0x1)   /**< \brief (HW_POWER_STDBYCFG) PD0 and PD1 power domains are linked */
#define   HW_POWER_STDBYCFG_LINKPD_PD12_Val     _U_(0x2)   /**< \brief (HW_POWER_STDBYCFG) PD1 and PD2 power domains are linked */
#define   HW_POWER_STDBYCFG_LINKPD_PD012_Val    _U_(0x3)   /**< \brief (HW_POWER_STDBYCFG) All power domains are linked */
#define HW_POWER_STDBYCFG_LINKPD_DEFAULT  (HW_POWER_STDBYCFG_LINKPD_DEFAULT_Val << HW_POWER_STDBYCFG_LINKPD_Pos)
#define HW_POWER_STDBYCFG_LINKPD_PD01     (HW_POWER_STDBYCFG_LINKPD_PD01_Val   << HW_POWER_STDBYCFG_LINKPD_Pos)
#define HW_POWER_STDBYCFG_LINKPD_PD12     (HW_POWER_STDBYCFG_LINKPD_PD12_Val   << HW_POWER_STDBYCFG_LINKPD_Pos)
#define HW_POWER_STDBYCFG_LINKPD_PD012    (HW_POWER_STDBYCFG_LINKPD_PD012_Val  << HW_POWER_STDBYCFG_LINKPD_Pos)
#define HW_POWER_STDBYCFG_BBIASHS_Pos     10           /**< \brief (HW_POWER_STDBYCFG) Back Bias for HMCRAMCHS */
#define HW_POWER_STDBYCFG_BBIASHS_Msk     (_U_(0x3) << HW_POWER_STDBYCFG_BBIASHS_Pos)
#define HW_POWER_STDBYCFG_BBIASHS(value)  (HW_POWER_STDBYCFG_BBIASHS_Msk & ((value) << HW_POWER_STDBYCFG_BBIASHS_Pos))
#define HW_POWER_STDBYCFG_BBIASLP_Pos     12           /**< \brief (HW_POWER_STDBYCFG) Back Bias for HMCRAMCLP */
#define HW_POWER_STDBYCFG_BBIASLP_Msk     (_U_(0x3) << HW_POWER_STDBYCFG_BBIASLP_Pos)
#define HW_POWER_STDBYCFG_BBIASLP(value)  (HW_POWER_STDBYCFG_BBIASLP_Msk & ((value) << HW_POWER_STDBYCFG_BBIASLP_Pos))
#define HW_POWER_STDBYCFG_BBIASPP_Pos     14           /**< \brief (HW_POWER_STDBYCFG) Back Bias for PicoPram */
#define HW_POWER_STDBYCFG_BBIASPP_Msk     (_U_(0x3) << HW_POWER_STDBYCFG_BBIASPP_Pos)
#define HW_POWER_STDBYCFG_BBIASPP(value)  (HW_POWER_STDBYCFG_BBIASPP_Msk & ((value) << HW_POWER_STDBYCFG_BBIASPP_Pos))
#define HW_POWER_STDBYCFG_MASK            _U_(0xFFF3)  /**< \brief (HW_POWER_STDBYCFG) MASK Register */

/* -------- HW_POWER_PWSAKDLY : (PM Offset: 0x0C) (R/W  8) Power Switch Acknowledge Delay -------- */
typedef union {
  struct {
    uint8_t  DLYVAL:7;         /*!< bit:  0.. 6  Delay Value                        */
    uint8_t  IGNACK:1;         /*!< bit:      7  Ignore Acknowledge                 */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} HW_POWER_PWSAKDLY_Type;

#define HW_POWER_PWSAKDLY_OFFSET          0x0C         /**< \brief (HW_POWER_PWSAKDLY offset) Power Switch Acknowledge Delay */
#define HW_POWER_PWSAKDLY_RESETVALUE      _U_(0x00)    /**< \brief (HW_POWER_PWSAKDLY reset_value) Power Switch Acknowledge Delay */

#define HW_POWER_PWSAKDLY_DLYVAL_Pos      0            /**< \brief (HW_POWER_PWSAKDLY) Delay Value */
#define HW_POWER_PWSAKDLY_DLYVAL_Msk      (_U_(0x7F) << HW_POWER_PWSAKDLY_DLYVAL_Pos)
#define HW_POWER_PWSAKDLY_DLYVAL(value)   (HW_POWER_PWSAKDLY_DLYVAL_Msk & ((value) << HW_POWER_PWSAKDLY_DLYVAL_Pos))
#define HW_POWER_PWSAKDLY_IGNACK_Pos      7            /**< \brief (HW_POWER_PWSAKDLY) Ignore Acknowledge */
#define HW_POWER_PWSAKDLY_IGNACK          (_U_(0x1) << HW_POWER_PWSAKDLY_IGNACK_Pos)
#define HW_POWER_PWSAKDLY_MASK            _U_(0xFF)    /**< \brief (HW_POWER_PWSAKDLY) MASK Register */

/** \brief HW_POWER hardware registers */
typedef struct {
  __IO HW_POWER_CTRLA_Type             CTRLA;       /**< \brief Offset: 0x00 (R/W  8) Control A */
  __IO HW_POWER_SLEEPCFG_Type          SLEEPCFG;    /**< \brief Offset: 0x01 (R/W  8) Sleep Configuration */
  __IO HW_POWER_PLCFG_Type             PLCFG;       /**< \brief Offset: 0x02 (R/W  8) Performance Level Configuration */
       RoReg8                    Reserved1[0x1];
  __IO HW_POWER_INTENCLR_Type          INTENCLR;    /**< \brief Offset: 0x04 (R/W  8) Interrupt Enable Clear */
  __IO HW_POWER_INTENSET_Type          INTENSET;    /**< \brief Offset: 0x05 (R/W  8) Interrupt Enable Set */
  __IO HW_POWER_INTFLAG_Type           INTFLAG;     /**< \brief Offset: 0x06 (R/W  8) Interrupt Flag Status and Clear */
       RoReg8                    Reserved2[0x1];
  __IO HW_POWER_STDBYCFG_Type          STDBYCFG;    /**< \brief Offset: 0x08 (R/W 16) Standby Configuration */
       RoReg8                    Reserved3[0x2];
  __IO HW_POWER_PWSAKDLY_Type          PWSAKDLY;    /**< \brief Offset: 0x0C (R/W  8) Power Switch Acknowledge Delay */
} Pm;

/*@}*/

/* ========== Register definition for PM peripheral ========== */
#define HW_REG_POWER__CTRLA              (*(RwReg8 *)0x40000000UL) /**< \brief (PM) Control A */
#define HW_REG_POWER_SLEEPCFG            (*(RwReg8 *)0x40000001UL) /**< \brief (PM) Sleep Configuration */
#define HW_REG_POWER_PLCFG               (*(RwReg8 *)0x40000002UL) /**< \brief (PM) Performance Level Configuration */
#define HW_REG_POWER_INTENCLR            (*(RwReg8 *)0x40000004UL) /**< \brief (PM) Interrupt Enable Clear */
#define HW_REG_POWER_INTENSET            (*(RwReg8 *)0x40000005UL) /**< \brief (PM) Interrupt Enable Set */
#define HW_REG_POWER_INTFLAG             (*(RwReg8 *)0x40000006UL) /**< \brief (PM) Interrupt Flag Status and Clear */
#define HW_REG_POWER_STDBYCFG            (*(RwReg16*)0x40000008UL) /**< \brief (PM) Standby Configuration */
#define HW_REG_POWER_PWSAKDLY            (*(RwReg8 *)0x4000000CUL) /**< \brief (PM) Power Switch Acknowledge Delay */

/* ========== Instance parameters for PM peripheral ========== */
#define HW_POWER_PD_NUM                   3        // Number of switchable Power Domain


#endif //HW_RAK4260_POWER_H