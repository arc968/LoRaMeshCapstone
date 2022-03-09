#ifndef HW_RAK4260_OSC_H
#define HW_RAK4260_OSC_H


#define HW_OSC32KCTRL_U2246
#define REV_OSC32KCTRL              0x110

/* -------- HW_OSC32KCTRL_INTENCLR : (OSC32KCTRL Offset: 0x00) (R/W 32) Interrupt Enable Clear -------- */
typedef union {
  struct {
    uint32_t XOSC32KRDY:1;     /*!< bit:      0  XOSC32K Ready Interrupt Enable     */
    uint32_t OSC32KRDY:1;      /*!< bit:      1  OSC32K Ready Interrupt Enable      */
    uint32_t :30;              /*!< bit:  2..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} HW_OSC32KCTRL_INTENCLR_Type;

#define HW_OSC32KCTRL_INTENCLR_OFFSET  0x00         /**< \brief (HW_OSC32KCTRL_INTENCLR offset) Interrupt Enable Clear */
#define HW_OSC32KCTRL_INTENCLR_RESETVALUE _U_(0x00000000) /**< \brief (HW_OSC32KCTRL_INTENCLR reset_value) Interrupt Enable Clear */

#define HW_OSC32KCTRL_INTENCLR_XOSC32KRDY_Pos 0            /**< \brief (HW_OSC32KCTRL_INTENCLR) XOSC32K Ready Interrupt Enable */
#define HW_OSC32KCTRL_INTENCLR_XOSC32KRDY (_U_(0x1) << HW_OSC32KCTRL_INTENCLR_XOSC32KRDY_Pos)
#define HW_OSC32KCTRL_INTENCLR_OSC32KRDY_Pos 1            /**< \brief (HW_OSC32KCTRL_INTENCLR) OSC32K Ready Interrupt Enable */
#define HW_OSC32KCTRL_INTENCLR_OSC32KRDY (_U_(0x1) << HW_OSC32KCTRL_INTENCLR_OSC32KRDY_Pos)
#define HW_OSC32KCTRL_INTENCLR_MASK    _U_(0x00000003) /**< \brief (HW_OSC32KCTRL_INTENCLR) MASK Register */

/* -------- HW_OSC32KCTRL_INTENSET : (OSC32KCTRL Offset: 0x04) (R/W 32) Interrupt Enable Set -------- */
typedef union {
  struct {
    uint32_t XOSC32KRDY:1;     /*!< bit:      0  XOSC32K Ready Interrupt Enable     */
    uint32_t OSC32KRDY:1;      /*!< bit:      1  OSC32K Ready Interrupt Enable      */
    uint32_t :30;              /*!< bit:  2..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} HW_OSC32KCTRL_INTENSET_Type;

#define HW_OSC32KCTRL_INTENSET_OFFSET  0x04         /**< \brief (HW_OSC32KCTRL_INTENSET offset) Interrupt Enable Set */
#define HW_OSC32KCTRL_INTENSET_RESETVALUE _U_(0x00000000) /**< \brief (HW_OSC32KCTRL_INTENSET reset_value) Interrupt Enable Set */

#define HW_OSC32KCTRL_INTENSET_XOSC32KRDY_Pos 0            /**< \brief (HW_OSC32KCTRL_INTENSET) XOSC32K Ready Interrupt Enable */
#define HW_OSC32KCTRL_INTENSET_XOSC32KRDY (_U_(0x1) << HW_OSC32KCTRL_INTENSET_XOSC32KRDY_Pos)
#define HW_OSC32KCTRL_INTENSET_OSC32KRDY_Pos 1            /**< \brief (HW_OSC32KCTRL_INTENSET) OSC32K Ready Interrupt Enable */
#define HW_OSC32KCTRL_INTENSET_OSC32KRDY (_U_(0x1) << HW_OSC32KCTRL_INTENSET_OSC32KRDY_Pos)
#define HW_OSC32KCTRL_INTENSET_MASK    _U_(0x00000003) /**< \brief (HW_OSC32KCTRL_INTENSET) MASK Register */

/* -------- HW_OSC32KCTRL_INTFLAG : (OSC32KCTRL Offset: 0x08) (R/W 32) Interrupt Flag Status and Clear -------- */
typedef union { // __I to avoid read-modify-write on write-to-clear register
  struct {
    __I uint32_t XOSC32KRDY:1;     /*!< bit:      0  XOSC32K Ready                      */
    __I uint32_t OSC32KRDY:1;      /*!< bit:      1  OSC32K Ready                       */
    __I uint32_t :30;              /*!< bit:  2..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} HW_OSC32KCTRL_INTFLAG_Type;

#define HW_OSC32KCTRL_INTFLAG_OFFSET   0x08         /**< \brief (HW_OSC32KCTRL_INTFLAG offset) Interrupt Flag Status and Clear */
#define HW_OSC32KCTRL_INTFLAG_RESETVALUE _U_(0x00000000) /**< \brief (HW_OSC32KCTRL_INTFLAG reset_value) Interrupt Flag Status and Clear */

#define HW_OSC32KCTRL_INTFLAG_XOSC32KRDY_Pos 0            /**< \brief (HW_OSC32KCTRL_INTFLAG) XOSC32K Ready */
#define HW_OSC32KCTRL_INTFLAG_XOSC32KRDY (_U_(0x1) << HW_OSC32KCTRL_INTFLAG_XOSC32KRDY_Pos)
#define HW_OSC32KCTRL_INTFLAG_OSC32KRDY_Pos 1            /**< \brief (HW_OSC32KCTRL_INTFLAG) OSC32K Ready */
#define HW_OSC32KCTRL_INTFLAG_OSC32KRDY (_U_(0x1) << HW_OSC32KCTRL_INTFLAG_OSC32KRDY_Pos)
#define HW_OSC32KCTRL_INTFLAG_MASK     _U_(0x00000003) /**< \brief (HW_OSC32KCTRL_INTFLAG) MASK Register */

/* -------- HW_OSC32KCTRL_STATUS : (OSC32KCTRL Offset: 0x0C) (R/  32) Power and Clocks Status -------- */
typedef union {
  struct {
    uint32_t XOSC32KRDY:1;     /*!< bit:      0  XOSC32K Ready                      */
    uint32_t OSC32KRDY:1;      /*!< bit:      1  OSC32K Ready                       */
    uint32_t :30;              /*!< bit:  2..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} HW_OSC32KCTRL_STATUS_Type;

#define HW_OSC32KCTRL_STATUS_OFFSET    0x0C         /**< \brief (HW_OSC32KCTRL_STATUS offset) Power and Clocks Status */
#define HW_OSC32KCTRL_STATUS_RESETVALUE _U_(0x00000000) /**< \brief (HW_OSC32KCTRL_STATUS reset_value) Power and Clocks Status */

#define HW_OSC32KCTRL_STATUS_XOSC32KRDY_Pos 0            /**< \brief (HW_OSC32KCTRL_STATUS) XOSC32K Ready */
#define HW_OSC32KCTRL_STATUS_XOSC32KRDY (_U_(0x1) << HW_OSC32KCTRL_STATUS_XOSC32KRDY_Pos)
#define HW_OSC32KCTRL_STATUS_OSC32KRDY_Pos 1            /**< \brief (HW_OSC32KCTRL_STATUS) OSC32K Ready */
#define HW_OSC32KCTRL_STATUS_OSC32KRDY (_U_(0x1) << HW_OSC32KCTRL_STATUS_OSC32KRDY_Pos)
#define HW_OSC32KCTRL_STATUS_MASK      _U_(0x00000003) /**< \brief (HW_OSC32KCTRL_STATUS) MASK Register */

/* -------- HW_OSC32KCTRL_RTCCTRL : (OSC32KCTRL Offset: 0x10) (R/W 32) Clock selection -------- */
typedef union {
  struct {
    uint32_t RTCSEL:3;         /*!< bit:  0.. 2  RTC Clock Selection                */
    uint32_t :29;              /*!< bit:  3..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} HW_OSC32KCTRL_RTCCTRL_Type;

#define HW_OSC32KCTRL_RTCCTRL_OFFSET   0x10         /**< \brief (HW_OSC32KCTRL_RTCCTRL offset) Clock selection */
#define HW_OSC32KCTRL_RTCCTRL_RESETVALUE _U_(0x00000000) /**< \brief (HW_OSC32KCTRL_RTCCTRL reset_value) Clock selection */

#define HW_OSC32KCTRL_RTCCTRL_RTCSEL_Pos 0            /**< \brief (HW_OSC32KCTRL_RTCCTRL) RTC Clock Selection */
#define HW_OSC32KCTRL_RTCCTRL_RTCSEL_Msk (_U_(0x7) << HW_OSC32KCTRL_RTCCTRL_RTCSEL_Pos)
#define HW_OSC32KCTRL_RTCCTRL_RTCSEL(value) (HW_OSC32KCTRL_RTCCTRL_RTCSEL_Msk & ((value) << HW_OSC32KCTRL_RTCCTRL_RTCSEL_Pos))
#define   HW_OSC32KCTRL_RTCCTRL_RTCSEL_ULP1K_Val _U_(0x0)   /**< \brief (HW_OSC32KCTRL_RTCCTRL) 1.024kHz from 32kHz internal ULP oscillator */
#define   HW_OSC32KCTRL_RTCCTRL_RTCSEL_ULP32K_Val _U_(0x1)   /**< \brief (HW_OSC32KCTRL_RTCCTRL) 32.768kHz from 32kHz internal ULP oscillator */
#define   HW_OSC32KCTRL_RTCCTRL_RTCSEL_OSC1K_Val _U_(0x2)   /**< \brief (HW_OSC32KCTRL_RTCCTRL) 1.024kHz from 32.768kHz internal oscillator */
#define   HW_OSC32KCTRL_RTCCTRL_RTCSEL_OSC32K_Val _U_(0x3)   /**< \brief (HW_OSC32KCTRL_RTCCTRL) 32.768kHz from 32.768kHz internal oscillator */
#define   HW_OSC32KCTRL_RTCCTRL_RTCSEL_XOSC1K_Val _U_(0x4)   /**< \brief (HW_OSC32KCTRL_RTCCTRL) 1.024kHz from 32.768kHz internal oscillator */
#define   HW_OSC32KCTRL_RTCCTRL_RTCSEL_XOSC32K_Val _U_(0x5)   /**< \brief (HW_OSC32KCTRL_RTCCTRL) 32.768kHz from 32.768kHz external crystal oscillator */
#define HW_OSC32KCTRL_RTCCTRL_RTCSEL_ULP1K (HW_OSC32KCTRL_RTCCTRL_RTCSEL_ULP1K_Val << HW_OSC32KCTRL_RTCCTRL_RTCSEL_Pos)
#define HW_OSC32KCTRL_RTCCTRL_RTCSEL_ULP32K (HW_OSC32KCTRL_RTCCTRL_RTCSEL_ULP32K_Val << HW_OSC32KCTRL_RTCCTRL_RTCSEL_Pos)
#define HW_OSC32KCTRL_RTCCTRL_RTCSEL_OSC1K (HW_OSC32KCTRL_RTCCTRL_RTCSEL_OSC1K_Val << HW_OSC32KCTRL_RTCCTRL_RTCSEL_Pos)
#define HW_OSC32KCTRL_RTCCTRL_RTCSEL_OSC32K (HW_OSC32KCTRL_RTCCTRL_RTCSEL_OSC32K_Val << HW_OSC32KCTRL_RTCCTRL_RTCSEL_Pos)
#define HW_OSC32KCTRL_RTCCTRL_RTCSEL_XOSC1K (HW_OSC32KCTRL_RTCCTRL_RTCSEL_XOSC1K_Val << HW_OSC32KCTRL_RTCCTRL_RTCSEL_Pos)
#define HW_OSC32KCTRL_RTCCTRL_RTCSEL_XOSC32K (HW_OSC32KCTRL_RTCCTRL_RTCSEL_XOSC32K_Val << HW_OSC32KCTRL_RTCCTRL_RTCSEL_Pos)
#define HW_OSC32KCTRL_RTCCTRL_MASK     _U_(0x00000007) /**< \brief (HW_OSC32KCTRL_RTCCTRL) MASK Register */

/* -------- HW_OSC32KCTRL_XOSC32K : (OSC32KCTRL Offset: 0x14) (R/W 32) 32kHz External Crystal Oscillator (XOSC32K) Control -------- */
typedef union {
  struct {
    uint32_t :1;               /*!< bit:      0  Reserved                           */
    uint32_t ENABLE:1;         /*!< bit:      1  Oscillator Enable                  */
    uint32_t XTALEN:1;         /*!< bit:      2  Crystal Oscillator Enable          */
    uint32_t EN32K:1;          /*!< bit:      3  32kHz Output Enable                */
    uint32_t EN1K:1;           /*!< bit:      4  1kHz Output Enable                 */
    uint32_t :1;               /*!< bit:      5  Reserved                           */
    uint32_t RUNSTDBY:1;       /*!< bit:      6  Run in Standby                     */
    uint32_t ONDEMAND:1;       /*!< bit:      7  On Demand Control                  */
    uint32_t STARTUP:3;        /*!< bit:  8..10  Oscillator Start-Up Time           */
    uint32_t :1;               /*!< bit:     11  Reserved                           */
    uint32_t WRTLOCK:1;        /*!< bit:     12  Write Lock                         */
    uint32_t :19;              /*!< bit: 13..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} HW_OSC32KCTRL_XOSC32K_Type;

#define HW_OSC32KCTRL_XOSC32K_OFFSET   0x14         /**< \brief (HW_OSC32KCTRL_XOSC32K offset) 32kHz External Crystal Oscillator (XOSC32K) Control */
#define HW_OSC32KCTRL_XOSC32K_RESETVALUE _U_(0x00000080) /**< \brief (HW_OSC32KCTRL_XOSC32K reset_value) 32kHz External Crystal Oscillator (XOSC32K) Control */

#define HW_OSC32KCTRL_XOSC32K_ENABLE_Pos 1            /**< \brief (HW_OSC32KCTRL_XOSC32K) Oscillator Enable */
#define HW_OSC32KCTRL_XOSC32K_ENABLE   (_U_(0x1) << HW_OSC32KCTRL_XOSC32K_ENABLE_Pos)
#define HW_OSC32KCTRL_XOSC32K_XTALEN_Pos 2            /**< \brief (HW_OSC32KCTRL_XOSC32K) Crystal Oscillator Enable */
#define HW_OSC32KCTRL_XOSC32K_XTALEN   (_U_(0x1) << HW_OSC32KCTRL_XOSC32K_XTALEN_Pos)
#define HW_OSC32KCTRL_XOSC32K_EN32K_Pos 3            /**< \brief (HW_OSC32KCTRL_XOSC32K) 32kHz Output Enable */
#define HW_OSC32KCTRL_XOSC32K_EN32K    (_U_(0x1) << HW_OSC32KCTRL_XOSC32K_EN32K_Pos)
#define HW_OSC32KCTRL_XOSC32K_EN1K_Pos 4            /**< \brief (HW_OSC32KCTRL_XOSC32K) 1kHz Output Enable */
#define HW_OSC32KCTRL_XOSC32K_EN1K     (_U_(0x1) << HW_OSC32KCTRL_XOSC32K_EN1K_Pos)
#define HW_OSC32KCTRL_XOSC32K_RUNSTDBY_Pos 6            /**< \brief (HW_OSC32KCTRL_XOSC32K) Run in Standby */
#define HW_OSC32KCTRL_XOSC32K_RUNSTDBY (_U_(0x1) << HW_OSC32KCTRL_XOSC32K_RUNSTDBY_Pos)
#define HW_OSC32KCTRL_XOSC32K_ONDEMAND_Pos 7            /**< \brief (HW_OSC32KCTRL_XOSC32K) On Demand Control */
#define HW_OSC32KCTRL_XOSC32K_ONDEMAND (_U_(0x1) << HW_OSC32KCTRL_XOSC32K_ONDEMAND_Pos)
#define HW_OSC32KCTRL_XOSC32K_STARTUP_Pos 8            /**< \brief (HW_OSC32KCTRL_XOSC32K) Oscillator Start-Up Time */
#define HW_OSC32KCTRL_XOSC32K_STARTUP_Msk (_U_(0x7) << HW_OSC32KCTRL_XOSC32K_STARTUP_Pos)
#define HW_OSC32KCTRL_XOSC32K_STARTUP(value) (HW_OSC32KCTRL_XOSC32K_STARTUP_Msk & ((value) << HW_OSC32KCTRL_XOSC32K_STARTUP_Pos))
#define HW_OSC32KCTRL_XOSC32K_WRTLOCK_Pos 12           /**< \brief (HW_OSC32KCTRL_XOSC32K) Write Lock */
#define HW_OSC32KCTRL_XOSC32K_WRTLOCK  (_U_(0x1) << HW_OSC32KCTRL_XOSC32K_WRTLOCK_Pos)
#define HW_OSC32KCTRL_XOSC32K_MASK     _U_(0x000017DE) /**< \brief (HW_OSC32KCTRL_XOSC32K) MASK Register */

/* -------- HW_OSC32KCTRL_OSC32K : (OSC32KCTRL Offset: 0x18) (R/W 32) 32kHz Internal Oscillator (OSC32K) Control -------- */
typedef union {
  struct {
    uint32_t :1;               /*!< bit:      0  Reserved                           */
    uint32_t ENABLE:1;         /*!< bit:      1  Oscillator Enable                  */
    uint32_t EN32K:1;          /*!< bit:      2  32kHz Output Enable                */
    uint32_t EN1K:1;           /*!< bit:      3  1kHz Output Enable                 */
    uint32_t :2;               /*!< bit:  4.. 5  Reserved                           */
    uint32_t RUNSTDBY:1;       /*!< bit:      6  Run in Standby                     */
    uint32_t ONDEMAND:1;       /*!< bit:      7  On Demand Control                  */
    uint32_t STARTUP:3;        /*!< bit:  8..10  Oscillator Start-Up Time           */
    uint32_t :1;               /*!< bit:     11  Reserved                           */
    uint32_t WRTLOCK:1;        /*!< bit:     12  Write Lock                         */
    uint32_t :3;               /*!< bit: 13..15  Reserved                           */
    uint32_t CALIB:7;          /*!< bit: 16..22  Oscillator Calibration             */
    uint32_t :9;               /*!< bit: 23..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} HW_OSC32KCTRL_OSC32K_Type;

#define HW_OSC32KCTRL_OSC32K_OFFSET    0x18         /**< \brief (HW_OSC32KCTRL_OSC32K offset) 32kHz Internal Oscillator (OSC32K) Control */
#define HW_OSC32KCTRL_OSC32K_RESETVALUE _U_(0x003F0080) /**< \brief (HW_OSC32KCTRL_OSC32K reset_value) 32kHz Internal Oscillator (OSC32K) Control */

#define HW_OSC32KCTRL_OSC32K_ENABLE_Pos 1            /**< \brief (HW_OSC32KCTRL_OSC32K) Oscillator Enable */
#define HW_OSC32KCTRL_OSC32K_ENABLE    (_U_(0x1) << HW_OSC32KCTRL_OSC32K_ENABLE_Pos)
#define HW_OSC32KCTRL_OSC32K_EN32K_Pos 2            /**< \brief (HW_OSC32KCTRL_OSC32K) 32kHz Output Enable */
#define HW_OSC32KCTRL_OSC32K_EN32K     (_U_(0x1) << HW_OSC32KCTRL_OSC32K_EN32K_Pos)
#define HW_OSC32KCTRL_OSC32K_EN1K_Pos  3            /**< \brief (HW_OSC32KCTRL_OSC32K) 1kHz Output Enable */
#define HW_OSC32KCTRL_OSC32K_EN1K      (_U_(0x1) << HW_OSC32KCTRL_OSC32K_EN1K_Pos)
#define HW_OSC32KCTRL_OSC32K_RUNSTDBY_Pos 6            /**< \brief (HW_OSC32KCTRL_OSC32K) Run in Standby */
#define HW_OSC32KCTRL_OSC32K_RUNSTDBY  (_U_(0x1) << HW_OSC32KCTRL_OSC32K_RUNSTDBY_Pos)
#define HW_OSC32KCTRL_OSC32K_ONDEMAND_Pos 7            /**< \brief (HW_OSC32KCTRL_OSC32K) On Demand Control */
#define HW_OSC32KCTRL_OSC32K_ONDEMAND  (_U_(0x1) << HW_OSC32KCTRL_OSC32K_ONDEMAND_Pos)
#define HW_OSC32KCTRL_OSC32K_STARTUP_Pos 8            /**< \brief (HW_OSC32KCTRL_OSC32K) Oscillator Start-Up Time */
#define HW_OSC32KCTRL_OSC32K_STARTUP_Msk (_U_(0x7) << HW_OSC32KCTRL_OSC32K_STARTUP_Pos)
#define HW_OSC32KCTRL_OSC32K_STARTUP(value) (HW_OSC32KCTRL_OSC32K_STARTUP_Msk & ((value) << HW_OSC32KCTRL_OSC32K_STARTUP_Pos))
#define HW_OSC32KCTRL_OSC32K_WRTLOCK_Pos 12           /**< \brief (HW_OSC32KCTRL_OSC32K) Write Lock */
#define HW_OSC32KCTRL_OSC32K_WRTLOCK   (_U_(0x1) << HW_OSC32KCTRL_OSC32K_WRTLOCK_Pos)
#define HW_OSC32KCTRL_OSC32K_CALIB_Pos 16           /**< \brief (HW_OSC32KCTRL_OSC32K) Oscillator Calibration */
#define HW_OSC32KCTRL_OSC32K_CALIB_Msk (_U_(0x7F) << HW_OSC32KCTRL_OSC32K_CALIB_Pos)
#define HW_OSC32KCTRL_OSC32K_CALIB(value) (HW_OSC32KCTRL_OSC32K_CALIB_Msk & ((value) << HW_OSC32KCTRL_OSC32K_CALIB_Pos))
#define HW_OSC32KCTRL_OSC32K_MASK      _U_(0x007F17CE) /**< \brief (HW_OSC32KCTRL_OSC32K) MASK Register */

/* -------- HW_OSC32KCTRL_OSCULP32K : (OSC32KCTRL Offset: 0x1C) (R/W 32) 32kHz Ultra Low Power Internal Oscillator (OSCULP32K) Control -------- */
typedef union {
  struct {
    uint32_t :8;               /*!< bit:  0.. 7  Reserved                           */
    uint32_t CALIB:5;          /*!< bit:  8..12  Oscillator Calibration             */
    uint32_t :2;               /*!< bit: 13..14  Reserved                           */
    uint32_t WRTLOCK:1;        /*!< bit:     15  Write Lock                         */
    uint32_t :16;              /*!< bit: 16..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} HW_OSC32KCTRL_OSCULP32K_Type;

#define HW_OSC32KCTRL_OSCULP32K_OFFSET 0x1C         /**< \brief (HW_OSC32KCTRL_OSCULP32K offset) 32kHz Ultra Low Power Internal Oscillator (OSCULP32K) Control */

#define HW_OSC32KCTRL_OSCULP32K_CALIB_Pos 8            /**< \brief (HW_OSC32KCTRL_OSCULP32K) Oscillator Calibration */
#define HW_OSC32KCTRL_OSCULP32K_CALIB_Msk (_U_(0x1F) << HW_OSC32KCTRL_OSCULP32K_CALIB_Pos)
#define HW_OSC32KCTRL_OSCULP32K_CALIB(value) (HW_OSC32KCTRL_OSCULP32K_CALIB_Msk & ((value) << HW_OSC32KCTRL_OSCULP32K_CALIB_Pos))
#define HW_OSC32KCTRL_OSCULP32K_WRTLOCK_Pos 15           /**< \brief (HW_OSC32KCTRL_OSCULP32K) Write Lock */
#define HW_OSC32KCTRL_OSCULP32K_WRTLOCK (_U_(0x1) << HW_OSC32KCTRL_OSCULP32K_WRTLOCK_Pos)
#define HW_OSC32KCTRL_OSCULP32K_MASK   _U_(0x00009F00) /**< \brief (HW_OSC32KCTRL_OSCULP32K) MASK Register */

/** \brief OSC32KCTRL hardware registers */
typedef struct {
  __IO HW_OSC32KCTRL_INTENCLR_Type  INTENCLR;    /**< \brief Offset: 0x00 (R/W 32) Interrupt Enable Clear */
  __IO HW_OSC32KCTRL_INTENSET_Type  INTENSET;    /**< \brief Offset: 0x04 (R/W 32) Interrupt Enable Set */
  __IO HW_OSC32KCTRL_INTFLAG_Type   INTFLAG;     /**< \brief Offset: 0x08 (R/W 32) Interrupt Flag Status and Clear */
  __I  HW_OSC32KCTRL_STATUS_Type    STATUS;      /**< \brief Offset: 0x0C (R/  32) Power and Clocks Status */
  __IO HW_OSC32KCTRL_RTCCTRL_Type   RTCCTRL;     /**< \brief Offset: 0x10 (R/W 32) Clock selection */
  __IO HW_OSC32KCTRL_XOSC32K_Type   XOSC32K;     /**< \brief Offset: 0x14 (R/W 32) 32kHz External Crystal Oscillator (XOSC32K) Control */
  __IO HW_OSC32KCTRL_OSC32K_Type    OSC32K;      /**< \brief Offset: 0x18 (R/W 32) 32kHz Internal Oscillator (OSC32K) Control */
  __IO HW_OSC32KCTRL_OSCULP32K_Type OSCULP32K;   /**< \brief Offset: 0x1C (R/W 32) 32kHz Ultra Low Power Internal Oscillator (OSCULP32K) Control */
} Osc32kctrl;








#define HW_OSCCTRL_U2119
#define REV_OSCCTRL                 0x110

/* -------- HW_OSCCTRL_INTENCLR : (OSCCTRL Offset: 0x00) (R/W 32) Interrupt Enable Clear -------- */
typedef union {
  struct {
    uint32_t XOSCRDY:1;        /*!< bit:      0  XOSC Ready Interrupt Enable        */
    uint32_t :3;               /*!< bit:  1.. 3  Reserved                           */
    uint32_t OSC16MRDY:1;      /*!< bit:      4  OSC16M Ready Interrupt Enable      */
    uint32_t :3;               /*!< bit:  5.. 7  Reserved                           */
    uint32_t DFLLRDY:1;        /*!< bit:      8  DFLL Ready Interrupt Enable        */
    uint32_t DFLLOOB:1;        /*!< bit:      9  DFLL Out Of Bounds Interrupt Enable */
    uint32_t DFLLLCKF:1;       /*!< bit:     10  DFLL Lock Fine Interrupt Enable    */
    uint32_t DFLLLCKC:1;       /*!< bit:     11  DFLL Lock Coarse Interrupt Enable  */
    uint32_t DFLLRCS:1;        /*!< bit:     12  DFLL Reference Clock Stopped Interrupt Enable */
    uint32_t :3;               /*!< bit: 13..15  Reserved                           */
    uint32_t DPLLLCKR:1;       /*!< bit:     16  DPLL Lock Rise Interrupt Enable    */
    uint32_t DPLLLCKF:1;       /*!< bit:     17  DPLL Lock Fall Interrupt Enable    */
    uint32_t DPLLLTO:1;        /*!< bit:     18  DPLL Time Out Interrupt Enable     */
    uint32_t DPLLLDRTO:1;      /*!< bit:     19  DPLL Ratio Ready Interrupt Enable  */
    uint32_t :12;              /*!< bit: 20..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} HW_OSCCTRL_INTENCLR_Type;

#define HW_OSCCTRL_INTENCLR_OFFSET     0x00         /**< \brief (HW_OSCCTRL_INTENCLR offset) Interrupt Enable Clear */
#define HW_OSCCTRL_INTENCLR_RESETVALUE _U_(0x00000000) /**< \brief (HW_OSCCTRL_INTENCLR reset_value) Interrupt Enable Clear */

#define HW_OSCCTRL_INTENCLR_XOSCRDY_Pos 0            /**< \brief (HW_OSCCTRL_INTENCLR) XOSC Ready Interrupt Enable */
#define HW_OSCCTRL_INTENCLR_XOSCRDY    (_U_(0x1) << HW_OSCCTRL_INTENCLR_XOSCRDY_Pos)
#define HW_OSCCTRL_INTENCLR_OSC16MRDY_Pos 4            /**< \brief (HW_OSCCTRL_INTENCLR) OSC16M Ready Interrupt Enable */
#define HW_OSCCTRL_INTENCLR_OSC16MRDY  (_U_(0x1) << HW_OSCCTRL_INTENCLR_OSC16MRDY_Pos)
#define HW_OSCCTRL_INTENCLR_DFLLRDY_Pos 8            /**< \brief (HW_OSCCTRL_INTENCLR) DFLL Ready Interrupt Enable */
#define HW_OSCCTRL_INTENCLR_DFLLRDY    (_U_(0x1) << HW_OSCCTRL_INTENCLR_DFLLRDY_Pos)
#define HW_OSCCTRL_INTENCLR_DFLLOOB_Pos 9            /**< \brief (HW_OSCCTRL_INTENCLR) DFLL Out Of Bounds Interrupt Enable */
#define HW_OSCCTRL_INTENCLR_DFLLOOB    (_U_(0x1) << HW_OSCCTRL_INTENCLR_DFLLOOB_Pos)
#define HW_OSCCTRL_INTENCLR_DFLLLCKF_Pos 10           /**< \brief (HW_OSCCTRL_INTENCLR) DFLL Lock Fine Interrupt Enable */
#define HW_OSCCTRL_INTENCLR_DFLLLCKF   (_U_(0x1) << HW_OSCCTRL_INTENCLR_DFLLLCKF_Pos)
#define HW_OSCCTRL_INTENCLR_DFLLLCKC_Pos 11           /**< \brief (HW_OSCCTRL_INTENCLR) DFLL Lock Coarse Interrupt Enable */
#define HW_OSCCTRL_INTENCLR_DFLLLCKC   (_U_(0x1) << HW_OSCCTRL_INTENCLR_DFLLLCKC_Pos)
#define HW_OSCCTRL_INTENCLR_DFLLRCS_Pos 12           /**< \brief (HW_OSCCTRL_INTENCLR) DFLL Reference Clock Stopped Interrupt Enable */
#define HW_OSCCTRL_INTENCLR_DFLLRCS    (_U_(0x1) << HW_OSCCTRL_INTENCLR_DFLLRCS_Pos)
#define HW_OSCCTRL_INTENCLR_DPLLLCKR_Pos 16           /**< \brief (HW_OSCCTRL_INTENCLR) DPLL Lock Rise Interrupt Enable */
#define HW_OSCCTRL_INTENCLR_DPLLLCKR   (_U_(0x1) << HW_OSCCTRL_INTENCLR_DPLLLCKR_Pos)
#define HW_OSCCTRL_INTENCLR_DPLLLCKF_Pos 17           /**< \brief (HW_OSCCTRL_INTENCLR) DPLL Lock Fall Interrupt Enable */
#define HW_OSCCTRL_INTENCLR_DPLLLCKF   (_U_(0x1) << HW_OSCCTRL_INTENCLR_DPLLLCKF_Pos)
#define HW_OSCCTRL_INTENCLR_DPLLLTO_Pos 18           /**< \brief (HW_OSCCTRL_INTENCLR) DPLL Time Out Interrupt Enable */
#define HW_OSCCTRL_INTENCLR_DPLLLTO    (_U_(0x1) << HW_OSCCTRL_INTENCLR_DPLLLTO_Pos)
#define HW_OSCCTRL_INTENCLR_DPLLLDRTO_Pos 19           /**< \brief (HW_OSCCTRL_INTENCLR) DPLL Ratio Ready Interrupt Enable */
#define HW_OSCCTRL_INTENCLR_DPLLLDRTO  (_U_(0x1) << HW_OSCCTRL_INTENCLR_DPLLLDRTO_Pos)
#define HW_OSCCTRL_INTENCLR_MASK       _U_(0x000F1F11) /**< \brief (HW_OSCCTRL_INTENCLR) MASK Register */

/* -------- HW_OSCCTRL_INTENSET : (OSCCTRL Offset: 0x04) (R/W 32) Interrupt Enable Set -------- */
typedef union {
  struct {
    uint32_t XOSCRDY:1;        /*!< bit:      0  XOSC Ready Interrupt Enable        */
    uint32_t :3;               /*!< bit:  1.. 3  Reserved                           */
    uint32_t OSC16MRDY:1;      /*!< bit:      4  OSC16M Ready Interrupt Enable      */
    uint32_t :3;               /*!< bit:  5.. 7  Reserved                           */
    uint32_t DFLLRDY:1;        /*!< bit:      8  DFLL Ready Interrupt Enable        */
    uint32_t DFLLOOB:1;        /*!< bit:      9  DFLL Out Of Bounds Interrupt Enable */
    uint32_t DFLLLCKF:1;       /*!< bit:     10  DFLL Lock Fine Interrupt Enable    */
    uint32_t DFLLLCKC:1;       /*!< bit:     11  DFLL Lock Coarse Interrupt Enable  */
    uint32_t DFLLRCS:1;        /*!< bit:     12  DFLL Reference Clock Stopped Interrupt Enable */
    uint32_t :3;               /*!< bit: 13..15  Reserved                           */
    uint32_t DPLLLCKR:1;       /*!< bit:     16  DPLL Lock Rise Interrupt Enable    */
    uint32_t DPLLLCKF:1;       /*!< bit:     17  DPLL Lock Fall Interrupt Enable    */
    uint32_t DPLLLTO:1;        /*!< bit:     18  DPLL Time Out Interrupt Enable     */
    uint32_t DPLLLDRTO:1;      /*!< bit:     19  DPLL Ratio Ready Interrupt Enable  */
    uint32_t :12;              /*!< bit: 20..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} HW_OSCCTRL_INTENSET_Type;

#define HW_OSCCTRL_INTENSET_OFFSET     0x04         /**< \brief (HW_OSCCTRL_INTENSET offset) Interrupt Enable Set */
#define HW_OSCCTRL_INTENSET_RESETVALUE _U_(0x00000000) /**< \brief (HW_OSCCTRL_INTENSET reset_value) Interrupt Enable Set */

#define HW_OSCCTRL_INTENSET_XOSCRDY_Pos 0            /**< \brief (HW_OSCCTRL_INTENSET) XOSC Ready Interrupt Enable */
#define HW_OSCCTRL_INTENSET_XOSCRDY    (_U_(0x1) << HW_OSCCTRL_INTENSET_XOSCRDY_Pos)
#define HW_OSCCTRL_INTENSET_OSC16MRDY_Pos 4            /**< \brief (HW_OSCCTRL_INTENSET) OSC16M Ready Interrupt Enable */
#define HW_OSCCTRL_INTENSET_OSC16MRDY  (_U_(0x1) << HW_OSCCTRL_INTENSET_OSC16MRDY_Pos)
#define HW_OSCCTRL_INTENSET_DFLLRDY_Pos 8            /**< \brief (HW_OSCCTRL_INTENSET) DFLL Ready Interrupt Enable */
#define HW_OSCCTRL_INTENSET_DFLLRDY    (_U_(0x1) << HW_OSCCTRL_INTENSET_DFLLRDY_Pos)
#define HW_OSCCTRL_INTENSET_DFLLOOB_Pos 9            /**< \brief (HW_OSCCTRL_INTENSET) DFLL Out Of Bounds Interrupt Enable */
#define HW_OSCCTRL_INTENSET_DFLLOOB    (_U_(0x1) << HW_OSCCTRL_INTENSET_DFLLOOB_Pos)
#define HW_OSCCTRL_INTENSET_DFLLLCKF_Pos 10           /**< \brief (HW_OSCCTRL_INTENSET) DFLL Lock Fine Interrupt Enable */
#define HW_OSCCTRL_INTENSET_DFLLLCKF   (_U_(0x1) << HW_OSCCTRL_INTENSET_DFLLLCKF_Pos)
#define HW_OSCCTRL_INTENSET_DFLLLCKC_Pos 11           /**< \brief (HW_OSCCTRL_INTENSET) DFLL Lock Coarse Interrupt Enable */
#define HW_OSCCTRL_INTENSET_DFLLLCKC   (_U_(0x1) << HW_OSCCTRL_INTENSET_DFLLLCKC_Pos)
#define HW_OSCCTRL_INTENSET_DFLLRCS_Pos 12           /**< \brief (HW_OSCCTRL_INTENSET) DFLL Reference Clock Stopped Interrupt Enable */
#define HW_OSCCTRL_INTENSET_DFLLRCS    (_U_(0x1) << HW_OSCCTRL_INTENSET_DFLLRCS_Pos)
#define HW_OSCCTRL_INTENSET_DPLLLCKR_Pos 16           /**< \brief (HW_OSCCTRL_INTENSET) DPLL Lock Rise Interrupt Enable */
#define HW_OSCCTRL_INTENSET_DPLLLCKR   (_U_(0x1) << HW_OSCCTRL_INTENSET_DPLLLCKR_Pos)
#define HW_OSCCTRL_INTENSET_DPLLLCKF_Pos 17           /**< \brief (HW_OSCCTRL_INTENSET) DPLL Lock Fall Interrupt Enable */
#define HW_OSCCTRL_INTENSET_DPLLLCKF   (_U_(0x1) << HW_OSCCTRL_INTENSET_DPLLLCKF_Pos)
#define HW_OSCCTRL_INTENSET_DPLLLTO_Pos 18           /**< \brief (HW_OSCCTRL_INTENSET) DPLL Time Out Interrupt Enable */
#define HW_OSCCTRL_INTENSET_DPLLLTO    (_U_(0x1) << HW_OSCCTRL_INTENSET_DPLLLTO_Pos)
#define HW_OSCCTRL_INTENSET_DPLLLDRTO_Pos 19           /**< \brief (HW_OSCCTRL_INTENSET) DPLL Ratio Ready Interrupt Enable */
#define HW_OSCCTRL_INTENSET_DPLLLDRTO  (_U_(0x1) << HW_OSCCTRL_INTENSET_DPLLLDRTO_Pos)
#define HW_OSCCTRL_INTENSET_MASK       _U_(0x000F1F11) /**< \brief (HW_OSCCTRL_INTENSET) MASK Register */

/* -------- HW_OSCCTRL_INTFLAG : (OSCCTRL Offset: 0x08) (R/W 32) Interrupt Flag Status and Clear -------- */
typedef union { // __I to avoid read-modify-write on write-to-clear register
  struct {
    __I uint32_t XOSCRDY:1;        /*!< bit:      0  XOSC Ready                         */
    __I uint32_t :3;               /*!< bit:  1.. 3  Reserved                           */
    __I uint32_t OSC16MRDY:1;      /*!< bit:      4  OSC16M Ready                       */
    __I uint32_t :3;               /*!< bit:  5.. 7  Reserved                           */
    __I uint32_t DFLLRDY:1;        /*!< bit:      8  DFLL Ready                         */
    __I uint32_t DFLLOOB:1;        /*!< bit:      9  DFLL Out Of Bounds                 */
    __I uint32_t DFLLLCKF:1;       /*!< bit:     10  DFLL Lock Fine                     */
    __I uint32_t DFLLLCKC:1;       /*!< bit:     11  DFLL Lock Coarse                   */
    __I uint32_t DFLLRCS:1;        /*!< bit:     12  DFLL Reference Clock Stopped       */
    __I uint32_t :3;               /*!< bit: 13..15  Reserved                           */
    __I uint32_t DPLLLCKR:1;       /*!< bit:     16  DPLL Lock Rise                     */
    __I uint32_t DPLLLCKF:1;       /*!< bit:     17  DPLL Lock Fall                     */
    __I uint32_t DPLLLTO:1;        /*!< bit:     18  DPLL Timeout                       */
    __I uint32_t DPLLLDRTO:1;      /*!< bit:     19  DPLL Ratio Ready                   */
    __I uint32_t :12;              /*!< bit: 20..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} HW_OSCCTRL_INTFLAG_Type;

#define HW_OSCCTRL_INTFLAG_OFFSET      0x08         /**< \brief (HW_OSCCTRL_INTFLAG offset) Interrupt Flag Status and Clear */
#define HW_OSCCTRL_INTFLAG_RESETVALUE  _U_(0x00000000) /**< \brief (HW_OSCCTRL_INTFLAG reset_value) Interrupt Flag Status and Clear */

#define HW_OSCCTRL_INTFLAG_XOSCRDY_Pos 0            /**< \brief (HW_OSCCTRL_INTFLAG) XOSC Ready */
#define HW_OSCCTRL_INTFLAG_XOSCRDY     (_U_(0x1) << HW_OSCCTRL_INTFLAG_XOSCRDY_Pos)
#define HW_OSCCTRL_INTFLAG_OSC16MRDY_Pos 4            /**< \brief (HW_OSCCTRL_INTFLAG) OSC16M Ready */
#define HW_OSCCTRL_INTFLAG_OSC16MRDY   (_U_(0x1) << HW_OSCCTRL_INTFLAG_OSC16MRDY_Pos)
#define HW_OSCCTRL_INTFLAG_DFLLRDY_Pos 8            /**< \brief (HW_OSCCTRL_INTFLAG) DFLL Ready */
#define HW_OSCCTRL_INTFLAG_DFLLRDY     (_U_(0x1) << HW_OSCCTRL_INTFLAG_DFLLRDY_Pos)
#define HW_OSCCTRL_INTFLAG_DFLLOOB_Pos 9            /**< \brief (HW_OSCCTRL_INTFLAG) DFLL Out Of Bounds */
#define HW_OSCCTRL_INTFLAG_DFLLOOB     (_U_(0x1) << HW_OSCCTRL_INTFLAG_DFLLOOB_Pos)
#define HW_OSCCTRL_INTFLAG_DFLLLCKF_Pos 10           /**< \brief (HW_OSCCTRL_INTFLAG) DFLL Lock Fine */
#define HW_OSCCTRL_INTFLAG_DFLLLCKF    (_U_(0x1) << HW_OSCCTRL_INTFLAG_DFLLLCKF_Pos)
#define HW_OSCCTRL_INTFLAG_DFLLLCKC_Pos 11           /**< \brief (HW_OSCCTRL_INTFLAG) DFLL Lock Coarse */
#define HW_OSCCTRL_INTFLAG_DFLLLCKC    (_U_(0x1) << HW_OSCCTRL_INTFLAG_DFLLLCKC_Pos)
#define HW_OSCCTRL_INTFLAG_DFLLRCS_Pos 12           /**< \brief (HW_OSCCTRL_INTFLAG) DFLL Reference Clock Stopped */
#define HW_OSCCTRL_INTFLAG_DFLLRCS     (_U_(0x1) << HW_OSCCTRL_INTFLAG_DFLLRCS_Pos)
#define HW_OSCCTRL_INTFLAG_DPLLLCKR_Pos 16           /**< \brief (HW_OSCCTRL_INTFLAG) DPLL Lock Rise */
#define HW_OSCCTRL_INTFLAG_DPLLLCKR    (_U_(0x1) << HW_OSCCTRL_INTFLAG_DPLLLCKR_Pos)
#define HW_OSCCTRL_INTFLAG_DPLLLCKF_Pos 17           /**< \brief (HW_OSCCTRL_INTFLAG) DPLL Lock Fall */
#define HW_OSCCTRL_INTFLAG_DPLLLCKF    (_U_(0x1) << HW_OSCCTRL_INTFLAG_DPLLLCKF_Pos)
#define HW_OSCCTRL_INTFLAG_DPLLLTO_Pos 18           /**< \brief (HW_OSCCTRL_INTFLAG) DPLL Timeout */
#define HW_OSCCTRL_INTFLAG_DPLLLTO     (_U_(0x1) << HW_OSCCTRL_INTFLAG_DPLLLTO_Pos)
#define HW_OSCCTRL_INTFLAG_DPLLLDRTO_Pos 19           /**< \brief (HW_OSCCTRL_INTFLAG) DPLL Ratio Ready */
#define HW_OSCCTRL_INTFLAG_DPLLLDRTO   (_U_(0x1) << HW_OSCCTRL_INTFLAG_DPLLLDRTO_Pos)
#define HW_OSCCTRL_INTFLAG_MASK        _U_(0x000F1F11) /**< \brief (HW_OSCCTRL_INTFLAG) MASK Register */

/* -------- HW_OSCCTRL_STATUS : (OSCCTRL Offset: 0x0C) (R/  32) Power and Clocks Status -------- */
typedef union {
  struct {
    uint32_t XOSCRDY:1;        /*!< bit:      0  XOSC Ready                         */
    uint32_t :3;               /*!< bit:  1.. 3  Reserved                           */
    uint32_t OSC16MRDY:1;      /*!< bit:      4  OSC16M Ready                       */
    uint32_t :3;               /*!< bit:  5.. 7  Reserved                           */
    uint32_t DFLLRDY:1;        /*!< bit:      8  DFLL Ready                         */
    uint32_t DFLLOOB:1;        /*!< bit:      9  DFLL Out Of Bounds                 */
    uint32_t DFLLLCKF:1;       /*!< bit:     10  DFLL Lock Fine                     */
    uint32_t DFLLLCKC:1;       /*!< bit:     11  DFLL Lock Coarse                   */
    uint32_t DFLLRCS:1;        /*!< bit:     12  DFLL Reference Clock Stopped       */
    uint32_t :3;               /*!< bit: 13..15  Reserved                           */
    uint32_t DPLLLCKR:1;       /*!< bit:     16  DPLL Lock Rise                     */
    uint32_t DPLLLCKF:1;       /*!< bit:     17  DPLL Lock Fall                     */
    uint32_t DPLLTO:1;         /*!< bit:     18  DPLL Timeout                       */
    uint32_t DPLLLDRTO:1;      /*!< bit:     19  DPLL Ratio Ready                   */
    uint32_t :12;              /*!< bit: 20..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} HW_OSCCTRL_STATUS_Type;

#define HW_OSCCTRL_STATUS_OFFSET       0x0C         /**< \brief (HW_OSCCTRL_STATUS offset) Power and Clocks Status */
#define HW_OSCCTRL_STATUS_RESETVALUE   _U_(0x00000000) /**< \brief (HW_OSCCTRL_STATUS reset_value) Power and Clocks Status */

#define HW_OSCCTRL_STATUS_XOSCRDY_Pos  0            /**< \brief (HW_OSCCTRL_STATUS) XOSC Ready */
#define HW_OSCCTRL_STATUS_XOSCRDY      (_U_(0x1) << HW_OSCCTRL_STATUS_XOSCRDY_Pos)
#define HW_OSCCTRL_STATUS_OSC16MRDY_Pos 4            /**< \brief (HW_OSCCTRL_STATUS) OSC16M Ready */
#define HW_OSCCTRL_STATUS_OSC16MRDY    (_U_(0x1) << HW_OSCCTRL_STATUS_OSC16MRDY_Pos)
#define HW_OSCCTRL_STATUS_DFLLRDY_Pos  8            /**< \brief (HW_OSCCTRL_STATUS) DFLL Ready */
#define HW_OSCCTRL_STATUS_DFLLRDY      (_U_(0x1) << HW_OSCCTRL_STATUS_DFLLRDY_Pos)
#define HW_OSCCTRL_STATUS_DFLLOOB_Pos  9            /**< \brief (HW_OSCCTRL_STATUS) DFLL Out Of Bounds */
#define HW_OSCCTRL_STATUS_DFLLOOB      (_U_(0x1) << HW_OSCCTRL_STATUS_DFLLOOB_Pos)
#define HW_OSCCTRL_STATUS_DFLLLCKF_Pos 10           /**< \brief (HW_OSCCTRL_STATUS) DFLL Lock Fine */
#define HW_OSCCTRL_STATUS_DFLLLCKF     (_U_(0x1) << HW_OSCCTRL_STATUS_DFLLLCKF_Pos)
#define HW_OSCCTRL_STATUS_DFLLLCKC_Pos 11           /**< \brief (HW_OSCCTRL_STATUS) DFLL Lock Coarse */
#define HW_OSCCTRL_STATUS_DFLLLCKC     (_U_(0x1) << HW_OSCCTRL_STATUS_DFLLLCKC_Pos)
#define HW_OSCCTRL_STATUS_DFLLRCS_Pos  12           /**< \brief (HW_OSCCTRL_STATUS) DFLL Reference Clock Stopped */
#define HW_OSCCTRL_STATUS_DFLLRCS      (_U_(0x1) << HW_OSCCTRL_STATUS_DFLLRCS_Pos)
#define HW_OSCCTRL_STATUS_DPLLLCKR_Pos 16           /**< \brief (HW_OSCCTRL_STATUS) DPLL Lock Rise */
#define HW_OSCCTRL_STATUS_DPLLLCKR     (_U_(0x1) << HW_OSCCTRL_STATUS_DPLLLCKR_Pos)
#define HW_OSCCTRL_STATUS_DPLLLCKF_Pos 17           /**< \brief (HW_OSCCTRL_STATUS) DPLL Lock Fall */
#define HW_OSCCTRL_STATUS_DPLLLCKF     (_U_(0x1) << HW_OSCCTRL_STATUS_DPLLLCKF_Pos)
#define HW_OSCCTRL_STATUS_DPLLTO_Pos   18           /**< \brief (HW_OSCCTRL_STATUS) DPLL Timeout */
#define HW_OSCCTRL_STATUS_DPLLTO       (_U_(0x1) << HW_OSCCTRL_STATUS_DPLLTO_Pos)
#define HW_OSCCTRL_STATUS_DPLLLDRTO_Pos 19           /**< \brief (HW_OSCCTRL_STATUS) DPLL Ratio Ready */
#define HW_OSCCTRL_STATUS_DPLLLDRTO    (_U_(0x1) << HW_OSCCTRL_STATUS_DPLLLDRTO_Pos)
#define HW_OSCCTRL_STATUS_MASK         _U_(0x000F1F11) /**< \brief (HW_OSCCTRL_STATUS) MASK Register */

/* -------- HW_OSCCTRL_XOSCCTRL : (OSCCTRL Offset: 0x10) (R/W 16) External Multipurpose Crystal Oscillator (XOSC) Control -------- */
typedef union {
  struct {
    uint16_t :1;               /*!< bit:      0  Reserved                           */
    uint16_t ENABLE:1;         /*!< bit:      1  Oscillator Enable                  */
    uint16_t XTALEN:1;         /*!< bit:      2  Crystal Oscillator Enable          */
    uint16_t :3;               /*!< bit:  3.. 5  Reserved                           */
    uint16_t RUNSTDBY:1;       /*!< bit:      6  Run in Standby                     */
    uint16_t ONDEMAND:1;       /*!< bit:      7  On Demand Control                  */
    uint16_t GAIN:3;           /*!< bit:  8..10  Oscillator Gain                    */
    uint16_t AMPGC:1;          /*!< bit:     11  Automatic Amplitude Gain Control   */
    uint16_t STARTUP:4;        /*!< bit: 12..15  Start-Up Time                      */
  } bit;                       /*!< Structure used for bit  access                  */
  uint16_t reg;                /*!< Type      used for register access              */
} HW_OSCCTRL_XHW_OSCCTRL_Type;

#define HW_OSCCTRL_XHW_OSCCTRL_OFFSET     0x10         /**< \brief (HW_OSCCTRL_XOSCCTRL offset) External Multipurpose Crystal Oscillator (XOSC) Control */
#define HW_OSCCTRL_XHW_OSCCTRL_RESETVALUE _U_(0x0080)  /**< \brief (HW_OSCCTRL_XOSCCTRL reset_value) External Multipurpose Crystal Oscillator (XOSC) Control */

#define HW_OSCCTRL_XHW_OSCCTRL_ENABLE_Pos 1            /**< \brief (HW_OSCCTRL_XOSCCTRL) Oscillator Enable */
#define HW_OSCCTRL_XHW_OSCCTRL_ENABLE     (_U_(0x1) << HW_OSCCTRL_XHW_OSCCTRL_ENABLE_Pos)
#define HW_OSCCTRL_XHW_OSCCTRL_XTALEN_Pos 2            /**< \brief (HW_OSCCTRL_XOSCCTRL) Crystal Oscillator Enable */
#define HW_OSCCTRL_XHW_OSCCTRL_XTALEN     (_U_(0x1) << HW_OSCCTRL_XHW_OSCCTRL_XTALEN_Pos)
#define HW_OSCCTRL_XHW_OSCCTRL_RUNSTDBY_Pos 6            /**< \brief (HW_OSCCTRL_XOSCCTRL) Run in Standby */
#define HW_OSCCTRL_XHW_OSCCTRL_RUNSTDBY   (_U_(0x1) << HW_OSCCTRL_XHW_OSCCTRL_RUNSTDBY_Pos)
#define HW_OSCCTRL_XHW_OSCCTRL_ONDEMAND_Pos 7            /**< \brief (HW_OSCCTRL_XOSCCTRL) On Demand Control */
#define HW_OSCCTRL_XHW_OSCCTRL_ONDEMAND   (_U_(0x1) << HW_OSCCTRL_XHW_OSCCTRL_ONDEMAND_Pos)
#define HW_OSCCTRL_XHW_OSCCTRL_GAIN_Pos   8            /**< \brief (HW_OSCCTRL_XOSCCTRL) Oscillator Gain */
#define HW_OSCCTRL_XHW_OSCCTRL_GAIN_Msk   (_U_(0x7) << HW_OSCCTRL_XHW_OSCCTRL_GAIN_Pos)
#define HW_OSCCTRL_XHW_OSCCTRL_GAIN(value) (HW_OSCCTRL_XHW_OSCCTRL_GAIN_Msk & ((value) << HW_OSCCTRL_XHW_OSCCTRL_GAIN_Pos))
#define HW_OSCCTRL_XHW_OSCCTRL_AMPGC_Pos  11           /**< \brief (HW_OSCCTRL_XOSCCTRL) Automatic Amplitude Gain Control */
#define HW_OSCCTRL_XHW_OSCCTRL_AMPGC      (_U_(0x1) << HW_OSCCTRL_XHW_OSCCTRL_AMPGC_Pos)
#define HW_OSCCTRL_XHW_OSCCTRL_STARTUP_Pos 12           /**< \brief (HW_OSCCTRL_XOSCCTRL) Start-Up Time */
#define HW_OSCCTRL_XHW_OSCCTRL_STARTUP_Msk (_U_(0xF) << HW_OSCCTRL_XHW_OSCCTRL_STARTUP_Pos)
#define HW_OSCCTRL_XHW_OSCCTRL_STARTUP(value) (HW_OSCCTRL_XHW_OSCCTRL_STARTUP_Msk & ((value) << HW_OSCCTRL_XHW_OSCCTRL_STARTUP_Pos))
#define HW_OSCCTRL_XHW_OSCCTRL_MASK       _U_(0xFFC6)  /**< \brief (HW_OSCCTRL_XOSCCTRL) MASK Register */

/* -------- HW_OSCCTRL_OSC16MCTRL : (OSCCTRL Offset: 0x14) (R/W  8) 16MHz Internal Oscillator (OSC16M) Control -------- */
typedef union {
  struct {
    uint8_t  :1;               /*!< bit:      0  Reserved                           */
    uint8_t  ENABLE:1;         /*!< bit:      1  Oscillator Enable                  */
    uint8_t  FSEL:2;           /*!< bit:  2.. 3  Oscillator Frequency Select        */
    uint8_t  :2;               /*!< bit:  4.. 5  Reserved                           */
    uint8_t  RUNSTDBY:1;       /*!< bit:      6  Run in Standby                     */
    uint8_t  ONDEMAND:1;       /*!< bit:      7  On Demand Control                  */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} HW_OSCCTRL_OSC16MCTRL_Type;

#define HW_OSCCTRL_OSC16MCTRL_OFFSET   0x14         /**< \brief (HW_OSCCTRL_OSC16MCTRL offset) 16MHz Internal Oscillator (OSC16M) Control */
#define HW_OSCCTRL_OSC16MCTRL_RESETVALUE _U_(0x82)    /**< \brief (HW_OSCCTRL_OSC16MCTRL reset_value) 16MHz Internal Oscillator (OSC16M) Control */

#define HW_OSCCTRL_OSC16MCTRL_ENABLE_Pos 1            /**< \brief (HW_OSCCTRL_OSC16MCTRL) Oscillator Enable */
#define HW_OSCCTRL_OSC16MCTRL_ENABLE   (_U_(0x1) << HW_OSCCTRL_OSC16MCTRL_ENABLE_Pos)
#define HW_OSCCTRL_OSC16MCTRL_FSEL_Pos 2            /**< \brief (HW_OSCCTRL_OSC16MCTRL) Oscillator Frequency Select */
#define HW_OSCCTRL_OSC16MCTRL_FSEL_Msk (_U_(0x3) << HW_OSCCTRL_OSC16MCTRL_FSEL_Pos)
#define HW_OSCCTRL_OSC16MCTRL_FSEL(value) (HW_OSCCTRL_OSC16MCTRL_FSEL_Msk & ((value) << HW_OSCCTRL_OSC16MCTRL_FSEL_Pos))
#define   HW_OSCCTRL_OSC16MCTRL_FSEL_4_Val   _U_(0x0)   /**< \brief (HW_OSCCTRL_OSC16MCTRL) 4MHz */
#define   HW_OSCCTRL_OSC16MCTRL_FSEL_8_Val   _U_(0x1)   /**< \brief (HW_OSCCTRL_OSC16MCTRL) 8MHz */
#define   HW_OSCCTRL_OSC16MCTRL_FSEL_12_Val  _U_(0x2)   /**< \brief (HW_OSCCTRL_OSC16MCTRL) 12MHz */
#define   HW_OSCCTRL_OSC16MCTRL_FSEL_16_Val  _U_(0x3)   /**< \brief (HW_OSCCTRL_OSC16MCTRL) 16MHz */
#define HW_OSCCTRL_OSC16MCTRL_FSEL_4   (HW_OSCCTRL_OSC16MCTRL_FSEL_4_Val << HW_OSCCTRL_OSC16MCTRL_FSEL_Pos)
#define HW_OSCCTRL_OSC16MCTRL_FSEL_8   (HW_OSCCTRL_OSC16MCTRL_FSEL_8_Val << HW_OSCCTRL_OSC16MCTRL_FSEL_Pos)
#define HW_OSCCTRL_OSC16MCTRL_FSEL_12  (HW_OSCCTRL_OSC16MCTRL_FSEL_12_Val << HW_OSCCTRL_OSC16MCTRL_FSEL_Pos)
#define HW_OSCCTRL_OSC16MCTRL_FSEL_16  (HW_OSCCTRL_OSC16MCTRL_FSEL_16_Val << HW_OSCCTRL_OSC16MCTRL_FSEL_Pos)
#define HW_OSCCTRL_OSC16MCTRL_RUNSTDBY_Pos 6            /**< \brief (HW_OSCCTRL_OSC16MCTRL) Run in Standby */
#define HW_OSCCTRL_OSC16MCTRL_RUNSTDBY (_U_(0x1) << HW_OSCCTRL_OSC16MCTRL_RUNSTDBY_Pos)
#define HW_OSCCTRL_OSC16MCTRL_ONDEMAND_Pos 7            /**< \brief (HW_OSCCTRL_OSC16MCTRL) On Demand Control */
#define HW_OSCCTRL_OSC16MCTRL_ONDEMAND (_U_(0x1) << HW_OSCCTRL_OSC16MCTRL_ONDEMAND_Pos)
#define HW_OSCCTRL_OSC16MCTRL_MASK     _U_(0xCE)    /**< \brief (HW_OSCCTRL_OSC16MCTRL) MASK Register */

/* -------- HW_OSCCTRL_DFLLCTRL : (OSCCTRL Offset: 0x18) (R/W 16) DFLL48M Control -------- */
typedef union {
  struct {
    uint16_t :1;               /*!< bit:      0  Reserved                           */
    uint16_t ENABLE:1;         /*!< bit:      1  DFLL Enable                        */
    uint16_t MODE:1;           /*!< bit:      2  Operating Mode Selection           */
    uint16_t STABLE:1;         /*!< bit:      3  Stable DFLL Frequency              */
    uint16_t LLAW:1;           /*!< bit:      4  Lose Lock After Wake               */
    uint16_t USBCRM:1;         /*!< bit:      5  USB Clock Recovery Mode            */
    uint16_t RUNSTDBY:1;       /*!< bit:      6  Run in Standby                     */
    uint16_t ONDEMAND:1;       /*!< bit:      7  On Demand Control                  */
    uint16_t CCDIS:1;          /*!< bit:      8  Chill Cycle Disable                */
    uint16_t QLDIS:1;          /*!< bit:      9  Quick Lock Disable                 */
    uint16_t BPLCKC:1;         /*!< bit:     10  Bypass Coarse Lock                 */
    uint16_t WAITLOCK:1;       /*!< bit:     11  Wait Lock                          */
    uint16_t :4;               /*!< bit: 12..15  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint16_t reg;                /*!< Type      used for register access              */
} HW_OSCCTRL_DFLLCTRL_Type;

#define HW_OSCCTRL_DFLLCTRL_OFFSET     0x18         /**< \brief (HW_OSCCTRL_DFLLCTRL offset) DFLL48M Control */
#define HW_OSCCTRL_DFLLCTRL_RESETVALUE _U_(0x0080)  /**< \brief (HW_OSCCTRL_DFLLCTRL reset_value) DFLL48M Control */

#define HW_OSCCTRL_DFLLCTRL_ENABLE_Pos 1            /**< \brief (HW_OSCCTRL_DFLLCTRL) DFLL Enable */
#define HW_OSCCTRL_DFLLCTRL_ENABLE     (_U_(0x1) << HW_OSCCTRL_DFLLCTRL_ENABLE_Pos)
#define HW_OSCCTRL_DFLLCTRL_MODE_Pos   2            /**< \brief (HW_OSCCTRL_DFLLCTRL) Operating Mode Selection */
#define HW_OSCCTRL_DFLLCTRL_MODE       (_U_(0x1) << HW_OSCCTRL_DFLLCTRL_MODE_Pos)
#define HW_OSCCTRL_DFLLCTRL_STABLE_Pos 3            /**< \brief (HW_OSCCTRL_DFLLCTRL) Stable DFLL Frequency */
#define HW_OSCCTRL_DFLLCTRL_STABLE     (_U_(0x1) << HW_OSCCTRL_DFLLCTRL_STABLE_Pos)
#define HW_OSCCTRL_DFLLCTRL_LLAW_Pos   4            /**< \brief (HW_OSCCTRL_DFLLCTRL) Lose Lock After Wake */
#define HW_OSCCTRL_DFLLCTRL_LLAW       (_U_(0x1) << HW_OSCCTRL_DFLLCTRL_LLAW_Pos)
#define HW_OSCCTRL_DFLLCTRL_USBCRM_Pos 5            /**< \brief (HW_OSCCTRL_DFLLCTRL) USB Clock Recovery Mode */
#define HW_OSCCTRL_DFLLCTRL_USBCRM     (_U_(0x1) << HW_OSCCTRL_DFLLCTRL_USBCRM_Pos)
#define HW_OSCCTRL_DFLLCTRL_RUNSTDBY_Pos 6            /**< \brief (HW_OSCCTRL_DFLLCTRL) Run in Standby */
#define HW_OSCCTRL_DFLLCTRL_RUNSTDBY   (_U_(0x1) << HW_OSCCTRL_DFLLCTRL_RUNSTDBY_Pos)
#define HW_OSCCTRL_DFLLCTRL_ONDEMAND_Pos 7            /**< \brief (HW_OSCCTRL_DFLLCTRL) On Demand Control */
#define HW_OSCCTRL_DFLLCTRL_ONDEMAND   (_U_(0x1) << HW_OSCCTRL_DFLLCTRL_ONDEMAND_Pos)
#define HW_OSCCTRL_DFLLCTRL_CCDIS_Pos  8            /**< \brief (HW_OSCCTRL_DFLLCTRL) Chill Cycle Disable */
#define HW_OSCCTRL_DFLLCTRL_CCDIS      (_U_(0x1) << HW_OSCCTRL_DFLLCTRL_CCDIS_Pos)
#define HW_OSCCTRL_DFLLCTRL_QLDIS_Pos  9            /**< \brief (HW_OSCCTRL_DFLLCTRL) Quick Lock Disable */
#define HW_OSCCTRL_DFLLCTRL_QLDIS      (_U_(0x1) << HW_OSCCTRL_DFLLCTRL_QLDIS_Pos)
#define HW_OSCCTRL_DFLLCTRL_BPLCKC_Pos 10           /**< \brief (HW_OSCCTRL_DFLLCTRL) Bypass Coarse Lock */
#define HW_OSCCTRL_DFLLCTRL_BPLCKC     (_U_(0x1) << HW_OSCCTRL_DFLLCTRL_BPLCKC_Pos)
#define HW_OSCCTRL_DFLLCTRL_WAITLOCK_Pos 11           /**< \brief (HW_OSCCTRL_DFLLCTRL) Wait Lock */
#define HW_OSCCTRL_DFLLCTRL_WAITLOCK   (_U_(0x1) << HW_OSCCTRL_DFLLCTRL_WAITLOCK_Pos)
#define HW_OSCCTRL_DFLLCTRL_MASK       _U_(0x0FFE)  /**< \brief (HW_OSCCTRL_DFLLCTRL) MASK Register */

/* -------- HW_OSCCTRL_DFLLVAL : (OSCCTRL Offset: 0x1C) (R/W 32) DFLL48M Value -------- */
typedef union {
  struct {
    uint32_t FINE:10;          /*!< bit:  0.. 9  Fine Value                         */
    uint32_t COARSE:6;         /*!< bit: 10..15  Coarse Value                       */
    uint32_t DIFF:16;          /*!< bit: 16..31  Multiplication Ratio Difference    */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} HW_OSCCTRL_DFLLVAL_Type;

#define HW_OSCCTRL_DFLLVAL_OFFSET      0x1C         /**< \brief (HW_OSCCTRL_DFLLVAL offset) DFLL48M Value */
#define HW_OSCCTRL_DFLLVAL_RESETVALUE  _U_(0x00000000) /**< \brief (HW_OSCCTRL_DFLLVAL reset_value) DFLL48M Value */

#define HW_OSCCTRL_DFLLVAL_FINE_Pos    0            /**< \brief (HW_OSCCTRL_DFLLVAL) Fine Value */
#define HW_OSCCTRL_DFLLVAL_FINE_Msk    (_U_(0x3FF) << HW_OSCCTRL_DFLLVAL_FINE_Pos)
#define HW_OSCCTRL_DFLLVAL_FINE(value) (HW_OSCCTRL_DFLLVAL_FINE_Msk & ((value) << HW_OSCCTRL_DFLLVAL_FINE_Pos))
#define HW_OSCCTRL_DFLLVAL_COARSE_Pos  10           /**< \brief (HW_OSCCTRL_DFLLVAL) Coarse Value */
#define HW_OSCCTRL_DFLLVAL_COARSE_Msk  (_U_(0x3F) << HW_OSCCTRL_DFLLVAL_COARSE_Pos)
#define HW_OSCCTRL_DFLLVAL_COARSE(value) (HW_OSCCTRL_DFLLVAL_COARSE_Msk & ((value) << HW_OSCCTRL_DFLLVAL_COARSE_Pos))
#define HW_OSCCTRL_DFLLVAL_DIFF_Pos    16           /**< \brief (HW_OSCCTRL_DFLLVAL) Multiplication Ratio Difference */
#define HW_OSCCTRL_DFLLVAL_DIFF_Msk    (_U_(0xFFFF) << HW_OSCCTRL_DFLLVAL_DIFF_Pos)
#define HW_OSCCTRL_DFLLVAL_DIFF(value) (HW_OSCCTRL_DFLLVAL_DIFF_Msk & ((value) << HW_OSCCTRL_DFLLVAL_DIFF_Pos))
#define HW_OSCCTRL_DFLLVAL_MASK        _U_(0xFFFFFFFF) /**< \brief (HW_OSCCTRL_DFLLVAL) MASK Register */

/* -------- HW_OSCCTRL_DFLLMUL : (OSCCTRL Offset: 0x20) (R/W 32) DFLL48M Multiplier -------- */
typedef union {
  struct {
    uint32_t MUL:16;           /*!< bit:  0..15  DFLL Multiply Factor               */
    uint32_t FSTEP:10;         /*!< bit: 16..25  Fine Maximum Step                  */
    uint32_t CSTEP:6;          /*!< bit: 26..31  Coarse Maximum Step                */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} HW_OSCCTRL_DFLLMUL_Type;

#define HW_OSCCTRL_DFLLMUL_OFFSET      0x20         /**< \brief (HW_OSCCTRL_DFLLMUL offset) DFLL48M Multiplier */
#define HW_OSCCTRL_DFLLMUL_RESETVALUE  _U_(0x00000000) /**< \brief (HW_OSCCTRL_DFLLMUL reset_value) DFLL48M Multiplier */

#define HW_OSCCTRL_DFLLMUL_MUL_Pos     0            /**< \brief (HW_OSCCTRL_DFLLMUL) DFLL Multiply Factor */
#define HW_OSCCTRL_DFLLMUL_MUL_Msk     (_U_(0xFFFF) << HW_OSCCTRL_DFLLMUL_MUL_Pos)
#define HW_OSCCTRL_DFLLMUL_MUL(value)  (HW_OSCCTRL_DFLLMUL_MUL_Msk & ((value) << HW_OSCCTRL_DFLLMUL_MUL_Pos))
#define HW_OSCCTRL_DFLLMUL_FSTEP_Pos   16           /**< \brief (HW_OSCCTRL_DFLLMUL) Fine Maximum Step */
#define HW_OSCCTRL_DFLLMUL_FSTEP_Msk   (_U_(0x3FF) << HW_OSCCTRL_DFLLMUL_FSTEP_Pos)
#define HW_OSCCTRL_DFLLMUL_FSTEP(value) (HW_OSCCTRL_DFLLMUL_FSTEP_Msk & ((value) << HW_OSCCTRL_DFLLMUL_FSTEP_Pos))
#define HW_OSCCTRL_DFLLMUL_CSTEP_Pos   26           /**< \brief (HW_OSCCTRL_DFLLMUL) Coarse Maximum Step */
#define HW_OSCCTRL_DFLLMUL_CSTEP_Msk   (_U_(0x3F) << HW_OSCCTRL_DFLLMUL_CSTEP_Pos)
#define HW_OSCCTRL_DFLLMUL_CSTEP(value) (HW_OSCCTRL_DFLLMUL_CSTEP_Msk & ((value) << HW_OSCCTRL_DFLLMUL_CSTEP_Pos))
#define HW_OSCCTRL_DFLLMUL_MASK        _U_(0xFFFFFFFF) /**< \brief (HW_OSCCTRL_DFLLMUL) MASK Register */

/* -------- HW_OSCCTRL_DFLLSYNC : (OSCCTRL Offset: 0x24) (R/W  8) DFLL48M Synchronization -------- */
typedef union {
  struct {
    uint8_t  :7;               /*!< bit:  0.. 6  Reserved                           */
    uint8_t  READREQ:1;        /*!< bit:      7  Read Request                       */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} HW_OSCCTRL_DFLLSYNC_Type;

#define HW_OSCCTRL_DFLLSYNC_OFFSET     0x24         /**< \brief (HW_OSCCTRL_DFLLSYNC offset) DFLL48M Synchronization */
#define HW_OSCCTRL_DFLLSYNC_RESETVALUE _U_(0x00)    /**< \brief (HW_OSCCTRL_DFLLSYNC reset_value) DFLL48M Synchronization */

#define HW_OSCCTRL_DFLLSYNC_READREQ_Pos 7            /**< \brief (HW_OSCCTRL_DFLLSYNC) Read Request */
#define HW_OSCCTRL_DFLLSYNC_READREQ    (_U_(0x1) << HW_OSCCTRL_DFLLSYNC_READREQ_Pos)
#define HW_OSCCTRL_DFLLSYNC_MASK       _U_(0x80)    /**< \brief (HW_OSCCTRL_DFLLSYNC) MASK Register */

/* -------- HW_OSCCTRL_DPLLCTRLA : (OSCCTRL Offset: 0x28) (R/W  8) DPLL Control -------- */
typedef union {
  struct {
    uint8_t  :1;               /*!< bit:      0  Reserved                           */
    uint8_t  ENABLE:1;         /*!< bit:      1  Enable                             */
    uint8_t  :4;               /*!< bit:  2.. 5  Reserved                           */
    uint8_t  RUNSTDBY:1;       /*!< bit:      6  Run in Standby                     */
    uint8_t  ONDEMAND:1;       /*!< bit:      7  On Demand                          */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} HW_OSCCTRL_DPLLCTRLA_Type;

#define HW_OSCCTRL_DPLLCTRLA_OFFSET    0x28         /**< \brief (HW_OSCCTRL_DPLLCTRLA offset) DPLL Control */
#define HW_OSCCTRL_DPLLCTRLA_RESETVALUE _U_(0x80)    /**< \brief (HW_OSCCTRL_DPLLCTRLA reset_value) DPLL Control */

#define HW_OSCCTRL_DPLLCTRLA_ENABLE_Pos 1            /**< \brief (HW_OSCCTRL_DPLLCTRLA) Enable */
#define HW_OSCCTRL_DPLLCTRLA_ENABLE    (_U_(0x1) << HW_OSCCTRL_DPLLCTRLA_ENABLE_Pos)
#define HW_OSCCTRL_DPLLCTRLA_RUNSTDBY_Pos 6            /**< \brief (HW_OSCCTRL_DPLLCTRLA) Run in Standby */
#define HW_OSCCTRL_DPLLCTRLA_RUNSTDBY  (_U_(0x1) << HW_OSCCTRL_DPLLCTRLA_RUNSTDBY_Pos)
#define HW_OSCCTRL_DPLLCTRLA_ONDEMAND_Pos 7            /**< \brief (HW_OSCCTRL_DPLLCTRLA) On Demand */
#define HW_OSCCTRL_DPLLCTRLA_ONDEMAND  (_U_(0x1) << HW_OSCCTRL_DPLLCTRLA_ONDEMAND_Pos)
#define HW_OSCCTRL_DPLLCTRLA_MASK      _U_(0xC2)    /**< \brief (HW_OSCCTRL_DPLLCTRLA) MASK Register */

/* -------- HW_OSCCTRL_DPLLRATIO : (OSCCTRL Offset: 0x2C) (R/W 32) DPLL Ratio Control -------- */
typedef union {
  struct {
    uint32_t LDR:12;           /*!< bit:  0..11  Loop Divider Ratio                 */
    uint32_t :4;               /*!< bit: 12..15  Reserved                           */
    uint32_t LDRFRAC:4;        /*!< bit: 16..19  Loop Divider Ratio Fractional Part */
    uint32_t :12;              /*!< bit: 20..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} HW_OSCCTRL_DPLLRATIO_Type;

#define HW_OSCCTRL_DPLLRATIO_OFFSET    0x2C         /**< \brief (HW_OSCCTRL_DPLLRATIO offset) DPLL Ratio Control */
#define HW_OSCCTRL_DPLLRATIO_RESETVALUE _U_(0x00000000) /**< \brief (HW_OSCCTRL_DPLLRATIO reset_value) DPLL Ratio Control */

#define HW_OSCCTRL_DPLLRATIO_LDR_Pos   0            /**< \brief (HW_OSCCTRL_DPLLRATIO) Loop Divider Ratio */
#define HW_OSCCTRL_DPLLRATIO_LDR_Msk   (_U_(0xFFF) << HW_OSCCTRL_DPLLRATIO_LDR_Pos)
#define HW_OSCCTRL_DPLLRATIO_LDR(value) (HW_OSCCTRL_DPLLRATIO_LDR_Msk & ((value) << HW_OSCCTRL_DPLLRATIO_LDR_Pos))
#define HW_OSCCTRL_DPLLRATIO_LDRFRAC_Pos 16           /**< \brief (HW_OSCCTRL_DPLLRATIO) Loop Divider Ratio Fractional Part */
#define HW_OSCCTRL_DPLLRATIO_LDRFRAC_Msk (_U_(0xF) << HW_OSCCTRL_DPLLRATIO_LDRFRAC_Pos)
#define HW_OSCCTRL_DPLLRATIO_LDRFRAC(value) (HW_OSCCTRL_DPLLRATIO_LDRFRAC_Msk & ((value) << HW_OSCCTRL_DPLLRATIO_LDRFRAC_Pos))
#define HW_OSCCTRL_DPLLRATIO_MASK      _U_(0x000F0FFF) /**< \brief (HW_OSCCTRL_DPLLRATIO) MASK Register */

/* -------- HW_OSCCTRL_DPLLCTRLB : (OSCCTRL Offset: 0x30) (R/W 32) Digital Core Configuration -------- */
typedef union {
  struct {
    uint32_t FILTER:2;         /*!< bit:  0.. 1  Proportional Integral Filter Selection */
    uint32_t LPEN:1;           /*!< bit:      2  Low-Power Enable                   */
    uint32_t WUF:1;            /*!< bit:      3  Wake Up Fast                       */
    uint32_t REFCLK:2;         /*!< bit:  4.. 5  Reference Clock Selection          */
    uint32_t :2;               /*!< bit:  6.. 7  Reserved                           */
    uint32_t LTIME:3;          /*!< bit:  8..10  Lock Time                          */
    uint32_t :1;               /*!< bit:     11  Reserved                           */
    uint32_t LBYPASS:1;        /*!< bit:     12  Lock Bypass                        */
    uint32_t :3;               /*!< bit: 13..15  Reserved                           */
    uint32_t DIV:11;           /*!< bit: 16..26  Clock Divider                      */
    uint32_t :5;               /*!< bit: 27..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} HW_OSCCTRL_DPLLCTRLB_Type;

#define HW_OSCCTRL_DPLLCTRLB_OFFSET    0x30         /**< \brief (HW_OSCCTRL_DPLLCTRLB offset) Digital Core Configuration */
#define HW_OSCCTRL_DPLLCTRLB_RESETVALUE _U_(0x00000000) /**< \brief (HW_OSCCTRL_DPLLCTRLB reset_value) Digital Core Configuration */

#define HW_OSCCTRL_DPLLCTRLB_FILTER_Pos 0            /**< \brief (HW_OSCCTRL_DPLLCTRLB) Proportional Integral Filter Selection */
#define HW_OSCCTRL_DPLLCTRLB_FILTER_Msk (_U_(0x3) << HW_OSCCTRL_DPLLCTRLB_FILTER_Pos)
#define HW_OSCCTRL_DPLLCTRLB_FILTER(value) (HW_OSCCTRL_DPLLCTRLB_FILTER_Msk & ((value) << HW_OSCCTRL_DPLLCTRLB_FILTER_Pos))
#define HW_OSCCTRL_DPLLCTRLB_LPEN_Pos  2            /**< \brief (HW_OSCCTRL_DPLLCTRLB) Low-Power Enable */
#define HW_OSCCTRL_DPLLCTRLB_LPEN      (_U_(0x1) << HW_OSCCTRL_DPLLCTRLB_LPEN_Pos)
#define HW_OSCCTRL_DPLLCTRLB_WUF_Pos   3            /**< \brief (HW_OSCCTRL_DPLLCTRLB) Wake Up Fast */
#define HW_OSCCTRL_DPLLCTRLB_WUF       (_U_(0x1) << HW_OSCCTRL_DPLLCTRLB_WUF_Pos)
#define HW_OSCCTRL_DPLLCTRLB_REFCLK_Pos 4            /**< \brief (HW_OSCCTRL_DPLLCTRLB) Reference Clock Selection */
#define HW_OSCCTRL_DPLLCTRLB_REFCLK_Msk (_U_(0x3) << HW_OSCCTRL_DPLLCTRLB_REFCLK_Pos)
#define HW_OSCCTRL_DPLLCTRLB_REFCLK(value) (HW_OSCCTRL_DPLLCTRLB_REFCLK_Msk & ((value) << HW_OSCCTRL_DPLLCTRLB_REFCLK_Pos))
#define HW_OSCCTRL_DPLLCTRLB_LTIME_Pos 8            /**< \brief (HW_OSCCTRL_DPLLCTRLB) Lock Time */
#define HW_OSCCTRL_DPLLCTRLB_LTIME_Msk (_U_(0x7) << HW_OSCCTRL_DPLLCTRLB_LTIME_Pos)
#define HW_OSCCTRL_DPLLCTRLB_LTIME(value) (HW_OSCCTRL_DPLLCTRLB_LTIME_Msk & ((value) << HW_OSCCTRL_DPLLCTRLB_LTIME_Pos))
#define HW_OSCCTRL_DPLLCTRLB_LBYPASS_Pos 12           /**< \brief (HW_OSCCTRL_DPLLCTRLB) Lock Bypass */
#define HW_OSCCTRL_DPLLCTRLB_LBYPASS   (_U_(0x1) << HW_OSCCTRL_DPLLCTRLB_LBYPASS_Pos)
#define HW_OSCCTRL_DPLLCTRLB_DIV_Pos   16           /**< \brief (HW_OSCCTRL_DPLLCTRLB) Clock Divider */
#define HW_OSCCTRL_DPLLCTRLB_DIV_Msk   (_U_(0x7FF) << HW_OSCCTRL_DPLLCTRLB_DIV_Pos)
#define HW_OSCCTRL_DPLLCTRLB_DIV(value) (HW_OSCCTRL_DPLLCTRLB_DIV_Msk & ((value) << HW_OSCCTRL_DPLLCTRLB_DIV_Pos))
#define HW_OSCCTRL_DPLLCTRLB_MASK      _U_(0x07FF173F) /**< \brief (HW_OSCCTRL_DPLLCTRLB) MASK Register */

/* -------- HW_OSCCTRL_DPLLPRESC : (OSCCTRL Offset: 0x34) (R/W  8) DPLL Prescaler -------- */
typedef union {
  struct {
    uint8_t  PRESC:2;          /*!< bit:  0.. 1  Output Clock Prescaler             */
    uint8_t  :6;               /*!< bit:  2.. 7  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} HW_OSCCTRL_DPLLPRESC_Type;

#define HW_OSCCTRL_DPLLPRESC_OFFSET    0x34         /**< \brief (HW_OSCCTRL_DPLLPRESC offset) DPLL Prescaler */
#define HW_OSCCTRL_DPLLPRESC_RESETVALUE _U_(0x00)    /**< \brief (HW_OSCCTRL_DPLLPRESC reset_value) DPLL Prescaler */

#define HW_OSCCTRL_DPLLPRESC_PRESC_Pos 0            /**< \brief (HW_OSCCTRL_DPLLPRESC) Output Clock Prescaler */
#define HW_OSCCTRL_DPLLPRESC_PRESC_Msk (_U_(0x3) << HW_OSCCTRL_DPLLPRESC_PRESC_Pos)
#define HW_OSCCTRL_DPLLPRESC_PRESC(value) (HW_OSCCTRL_DPLLPRESC_PRESC_Msk & ((value) << HW_OSCCTRL_DPLLPRESC_PRESC_Pos))
#define   HW_OSCCTRL_DPLLPRESC_PRESC_DIV1_Val _U_(0x0)   /**< \brief (HW_OSCCTRL_DPLLPRESC) DPLL output is divided by 1 */
#define   HW_OSCCTRL_DPLLPRESC_PRESC_DIV2_Val _U_(0x1)   /**< \brief (HW_OSCCTRL_DPLLPRESC) DPLL output is divided by 2 */
#define   HW_OSCCTRL_DPLLPRESC_PRESC_DIV4_Val _U_(0x2)   /**< \brief (HW_OSCCTRL_DPLLPRESC) DPLL output is divided by 4 */
#define HW_OSCCTRL_DPLLPRESC_PRESC_DIV1 (HW_OSCCTRL_DPLLPRESC_PRESC_DIV1_Val << HW_OSCCTRL_DPLLPRESC_PRESC_Pos)
#define HW_OSCCTRL_DPLLPRESC_PRESC_DIV2 (HW_OSCCTRL_DPLLPRESC_PRESC_DIV2_Val << HW_OSCCTRL_DPLLPRESC_PRESC_Pos)
#define HW_OSCCTRL_DPLLPRESC_PRESC_DIV4 (HW_OSCCTRL_DPLLPRESC_PRESC_DIV4_Val << HW_OSCCTRL_DPLLPRESC_PRESC_Pos)
#define HW_OSCCTRL_DPLLPRESC_MASK      _U_(0x03)    /**< \brief (HW_OSCCTRL_DPLLPRESC) MASK Register */

/* -------- HW_OSCCTRL_DPLLSYNCBUSY : (OSCCTRL Offset: 0x38) (R/   8) DPLL Synchronization Busy -------- */
typedef union {
  struct {
    uint8_t  :1;               /*!< bit:      0  Reserved                           */
    uint8_t  ENABLE:1;         /*!< bit:      1  DPLL Enable Synchronization Status */
    uint8_t  DPLLRATIO:1;      /*!< bit:      2  DPLL Ratio Synchronization Status  */
    uint8_t  DPLLPRESC:1;      /*!< bit:      3  DPLL Prescaler Synchronization Status */
    uint8_t  :4;               /*!< bit:  4.. 7  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} HW_OSCCTRL_DPLLSYNCBUSY_Type;

#define HW_OSCCTRL_DPLLSYNCBUSY_OFFSET 0x38         /**< \brief (HW_OSCCTRL_DPLLSYNCBUSY offset) DPLL Synchronization Busy */
#define HW_OSCCTRL_DPLLSYNCBUSY_RESETVALUE _U_(0x00)    /**< \brief (HW_OSCCTRL_DPLLSYNCBUSY reset_value) DPLL Synchronization Busy */

#define HW_OSCCTRL_DPLLSYNCBUSY_ENABLE_Pos 1            /**< \brief (HW_OSCCTRL_DPLLSYNCBUSY) DPLL Enable Synchronization Status */
#define HW_OSCCTRL_DPLLSYNCBUSY_ENABLE (_U_(0x1) << HW_OSCCTRL_DPLLSYNCBUSY_ENABLE_Pos)
#define HW_OSCCTRL_DPLLSYNCBUSY_DPLLRATIO_Pos 2            /**< \brief (HW_OSCCTRL_DPLLSYNCBUSY) DPLL Ratio Synchronization Status */
#define HW_OSCCTRL_DPLLSYNCBUSY_DPLLRATIO (_U_(0x1) << HW_OSCCTRL_DPLLSYNCBUSY_DPLLRATIO_Pos)
#define HW_OSCCTRL_DPLLSYNCBUSY_DPLLPRESC_Pos 3            /**< \brief (HW_OSCCTRL_DPLLSYNCBUSY) DPLL Prescaler Synchronization Status */
#define HW_OSCCTRL_DPLLSYNCBUSY_DPLLPRESC (_U_(0x1) << HW_OSCCTRL_DPLLSYNCBUSY_DPLLPRESC_Pos)
#define HW_OSCCTRL_DPLLSYNCBUSY_MASK   _U_(0x0E)    /**< \brief (HW_OSCCTRL_DPLLSYNCBUSY) MASK Register */

/* -------- HW_OSCCTRL_DPLLSTATUS : (OSCCTRL Offset: 0x3C) (R/   8) DPLL Status -------- */
typedef union {
  struct {
    uint8_t  LOCK:1;           /*!< bit:      0  DPLL Lock Status                   */
    uint8_t  CLKRDY:1;         /*!< bit:      1  DPLL Clock Ready                   */
    uint8_t  :6;               /*!< bit:  2.. 7  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} HW_OSCCTRL_DPLLSTATUS_Type;

#define HW_OSCCTRL_DPLLSTATUS_OFFSET   0x3C         /**< \brief (HW_OSCCTRL_DPLLSTATUS offset) DPLL Status */
#define HW_OSCCTRL_DPLLSTATUS_RESETVALUE _U_(0x00)    /**< \brief (HW_OSCCTRL_DPLLSTATUS reset_value) DPLL Status */

#define HW_OSCCTRL_DPLLSTATUS_LOCK_Pos 0            /**< \brief (HW_OSCCTRL_DPLLSTATUS) DPLL Lock Status */
#define HW_OSCCTRL_DPLLSTATUS_LOCK     (_U_(0x1) << HW_OSCCTRL_DPLLSTATUS_LOCK_Pos)
#define HW_OSCCTRL_DPLLSTATUS_CLKRDY_Pos 1            /**< \brief (HW_OSCCTRL_DPLLSTATUS) DPLL Clock Ready */
#define HW_OSCCTRL_DPLLSTATUS_CLKRDY   (_U_(0x1) << HW_OSCCTRL_DPLLSTATUS_CLKRDY_Pos)
#define HW_OSCCTRL_DPLLSTATUS_MASK     _U_(0x03)    /**< \brief (HW_OSCCTRL_DPLLSTATUS) MASK Register */

/** \brief OSCCTRL hardware registers */
typedef struct {
  __IO HW_OSCCTRL_INTENCLR_Type     INTENCLR;    /**< \brief Offset: 0x00 (R/W 32) Interrupt Enable Clear */
  __IO HW_OSCCTRL_INTENSET_Type     INTENSET;    /**< \brief Offset: 0x04 (R/W 32) Interrupt Enable Set */
  __IO HW_OSCCTRL_INTFLAG_Type      INTFLAG;     /**< \brief Offset: 0x08 (R/W 32) Interrupt Flag Status and Clear */
  __I  HW_OSCCTRL_STATUS_Type       STATUS;      /**< \brief Offset: 0x0C (R/  32) Power and Clocks Status */
  __IO HW_OSCCTRL_XHW_OSCCTRL_Type     XOSCCTRL;    /**< \brief Offset: 0x10 (R/W 16) External Multipurpose Crystal Oscillator (XOSC) Control */
       RoReg8                    Reserved1[0x2];
  __IO HW_OSCCTRL_OSC16MCTRL_Type   OSC16MCTRL;  /**< \brief Offset: 0x14 (R/W  8) 16MHz Internal Oscillator (OSC16M) Control */
       RoReg8                    Reserved2[0x3];
  __IO HW_OSCCTRL_DFLLCTRL_Type     DFLLCTRL;    /**< \brief Offset: 0x18 (R/W 16) DFLL48M Control */
       RoReg8                    Reserved3[0x2];
  __IO HW_OSCCTRL_DFLLVAL_Type      DFLLVAL;     /**< \brief Offset: 0x1C (R/W 32) DFLL48M Value */
  __IO HW_OSCCTRL_DFLLMUL_Type      DFLLMUL;     /**< \brief Offset: 0x20 (R/W 32) DFLL48M Multiplier */
  __IO HW_OSCCTRL_DFLLSYNC_Type     DFLLSYNC;    /**< \brief Offset: 0x24 (R/W  8) DFLL48M Synchronization */
       RoReg8                    Reserved4[0x3];
  __IO HW_OSCCTRL_DPLLCTRLA_Type    DPLLCTRLA;   /**< \brief Offset: 0x28 (R/W  8) DPLL Control */
       RoReg8                    Reserved5[0x3];
  __IO HW_OSCCTRL_DPLLRATIO_Type    DPLLRATIO;   /**< \brief Offset: 0x2C (R/W 32) DPLL Ratio Control */
  __IO HW_OSCCTRL_DPLLCTRLB_Type    DPLLCTRLB;   /**< \brief Offset: 0x30 (R/W 32) Digital Core Configuration */
  __IO HW_OSCCTRL_DPLLPRESC_Type    DPLLPRESC;   /**< \brief Offset: 0x34 (R/W  8) DPLL Prescaler */
       RoReg8                    Reserved6[0x3];
  __I  HW_OSCCTRL_DPLLSYNCBUSY_Type DPLLSYNCBUSY; /**< \brief Offset: 0x38 (R/   8) DPLL Synchronization Busy */
       RoReg8                    Reserved7[0x3];
  __I  HW_OSCCTRL_DPLLSTATUS_Type   DPLLSTATUS;  /**< \brief Offset: 0x3C (R/   8) DPLL Status */
} Oscctrl;



/* ========== Register definition for OSC32KCTRL peripheral ========== */
#define HW_REG_OSC32KCTRL_INTENCLR    (*(RwReg  *)0x40001000UL) /**< \brief (OSC32KCTRL) Interrupt Enable Clear */
#define HW_REG_OSC32KCTRL_INTENSET    (*(RwReg  *)0x40001004UL) /**< \brief (OSC32KCTRL) Interrupt Enable Set */
#define HW_REG_OSC32KCTRL_INTFLAG     (*(RwReg  *)0x40001008UL) /**< \brief (OSC32KCTRL) Interrupt Flag Status and Clear */
#define HW_REG_OSC32KCTRL_STATUS      (*(RoReg  *)0x4000100CUL) /**< \brief (OSC32KCTRL) Power and Clocks Status */
#define HW_REG_OSC32KCTRL_RTCCTRL     (*(RwReg  *)0x40001010UL) /**< \brief (OSC32KCTRL) Clock selection */
#define HW_REG_OSC32KCTRL_XOSC32K     (*(RwReg  *)0x40001014UL) /**< \brief (OSC32KCTRL) 32kHz External Crystal Oscillator (XOSC32K) Control */
#define HW_REG_OSC32KCTRL_OSC32K      (*(RwReg  *)0x40001018UL) /**< \brief (OSC32KCTRL) 32kHz Internal Oscillator (OSC32K) Control */
#define HW_REG_OSC32KCTRL_OSCULP32K   (*(RwReg  *)0x4000101CUL) /**< \brief (OSC32KCTRL) 32kHz Ultra Low Power Internal Oscillator (OSCULP32K) Control */

/* ========== Instance parameters for OSC32KCTRL peripheral ========== */
#define HW_OSC32KCTRL_OSC32K_COARSE_CALIB_MSB 6       


/* ========== Register definition for OSCCTRL peripheral ========== */
#define HW_REG_OSCCTRL_INTENCLR       (*(RwReg  *)0x40000C00UL) /**< \brief (OSCCTRL) Interrupt Enable Clear */
#define HW_REG_OSCCTRL_INTENSET       (*(RwReg  *)0x40000C04UL) /**< \brief (OSCCTRL) Interrupt Enable Set */
#define HW_REG_OSCCTRL_INTFLAG        (*(RwReg  *)0x40000C08UL) /**< \brief (OSCCTRL) Interrupt Flag Status and Clear */
#define HW_REG_OSCCTRL_STATUS         (*(RoReg  *)0x40000C0CUL) /**< \brief (OSCCTRL) Power and Clocks Status */
#define HW_REG_OSCCTRL_XOSCCTRL       (*(RwReg16*)0x40000C10UL) /**< \brief (OSCCTRL) External Multipurpose Crystal Oscillator (XOSC) Control */
#define HW_REG_OSCCTRL_OSC16MCTRL     (*(RwReg8 *)0x40000C14UL) /**< \brief (OSCCTRL) 16MHz Internal Oscillator (OSC16M) Control */
#define HW_REG_OSCCTRL_DFLLCTRL       (*(RwReg16*)0x40000C18UL) /**< \brief (OSCCTRL) DFLL48M Control */
#define HW_REG_OSCCTRL_DFLLVAL        (*(RwReg  *)0x40000C1CUL) /**< \brief (OSCCTRL) DFLL48M Value */
#define HW_REG_OSCCTRL_DFLLMUL        (*(RwReg  *)0x40000C20UL) /**< \brief (OSCCTRL) DFLL48M Multiplier */
#define HW_REG_OSCCTRL_DFLLSYNC       (*(RwReg8 *)0x40000C24UL) /**< \brief (OSCCTRL) DFLL48M Synchronization */
#define HW_REG_OSCCTRL_DPLLCTRLA      (*(RwReg8 *)0x40000C28UL) /**< \brief (OSCCTRL) DPLL Control */
#define HW_REG_OSCCTRL_DPLLRATIO      (*(RwReg  *)0x40000C2CUL) /**< \brief (OSCCTRL) DPLL Ratio Control */
#define HW_REG_OSCCTRL_DPLLCTRLB      (*(RwReg  *)0x40000C30UL) /**< \brief (OSCCTRL) Digital Core Configuration */
#define HW_REG_OSCCTRL_DPLLPRESC      (*(RwReg8 *)0x40000C34UL) /**< \brief (OSCCTRL) DPLL Prescaler */
#define HW_REG_OSCCTRL_DPLLSYNCBUSY   (*(RoReg8 *)0x40000C38UL) /**< \brief (OSCCTRL) DPLL Synchronization Busy */
#define HW_REG_OSCCTRL_DPLLSTATUS     (*(RoReg8 *)0x40000C3CUL) /**< \brief (OSCCTRL) DPLL Status */

/* ========== Instance parameters for OSCCTRL peripheral ========== */
#define HW_OSCCTRL_DFLL48M_COARSE_MSB  5       
#define HW_OSCCTRL_DFLL48M_FINE_MSB    9       
#define HW_OSCCTRL_GCLK_ID_DFLL48      0        // Index of Generic Clock for DFLL48
#define HW_OSCCTRL_GCLK_ID_FDPLL       1        // Index of Generic Clock for DPLL
#define HW_OSCCTRL_GCLK_ID_FDPLL32K    2        // Index of Generic Clock for DPLL 32K
#define HW_OSCCTRL_DFLL48M_VERSION     0x320   
#define HW_OSCCTRL_FDPLL_VERSION       0x200   
#define HW_OSCCTRL_OSC16M_VERSION      0x100   
#define HW_OSCCTRL_XOSC_VERSION        0x120   


#endif //HW_RAK4260_OSC_H