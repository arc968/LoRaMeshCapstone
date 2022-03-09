#ifndef HW_RAK4260_GCLK_H
#define HW_RAK4260_GCLK_H


#define HW_GCLK_U2122
#define REV_GCLK                    0x111

/* -------- HW_GCLK_CTRLA : (GCLK Offset: 0x00) (R/W  8) Control -------- */
typedef union {
  struct {
    uint8_t  SWRST:1;          /*!< bit:      0  Software Reset                     */
    uint8_t  :7;               /*!< bit:  1.. 7  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} HW_GCLK_CTRLA_Type;

#define HW_GCLK_CTRLA_OFFSET           0x00         /**< \brief (HW_GCLK_CTRLA offset) Control */
#define HW_GCLK_CTRLA_RESETVALUE       _U_(0x00)    /**< \brief (HW_GCLK_CTRLA reset_value) Control */

#define HW_GCLK_CTRLA_SWRST_Pos        0            /**< \brief (HW_GCLK_CTRLA) Software Reset */
#define HW_GCLK_CTRLA_SWRST            (_U_(0x1) << HW_GCLK_CTRLA_SWRST_Pos)
#define HW_GCLK_CTRLA_MASK             _U_(0x01)    /**< \brief (HW_GCLK_CTRLA) MASK Register */

/* -------- HW_GCLK_SYNCBUSY : (GCLK Offset: 0x04) (R/  32) Synchronization Busy -------- */
typedef union {
  struct {
    uint32_t SWRST:1;          /*!< bit:      0  Software Reset Synchroniation Busy bit */
    uint32_t :1;               /*!< bit:      1  Reserved                           */
    uint32_t GENCTRL0:1;       /*!< bit:      2  Generic Clock Generator Control 0 Synchronization Busy bits */
    uint32_t GENCTRL1:1;       /*!< bit:      3  Generic Clock Generator Control 1 Synchronization Busy bits */
    uint32_t GENCTRL2:1;       /*!< bit:      4  Generic Clock Generator Control 2 Synchronization Busy bits */
    uint32_t GENCTRL3:1;       /*!< bit:      5  Generic Clock Generator Control 3 Synchronization Busy bits */
    uint32_t GENCTRL4:1;       /*!< bit:      6  Generic Clock Generator Control 4 Synchronization Busy bits */
    uint32_t GENCTRL5:1;       /*!< bit:      7  Generic Clock Generator Control 5 Synchronization Busy bits */
    uint32_t GENCTRL6:1;       /*!< bit:      8  Generic Clock Generator Control 6 Synchronization Busy bits */
    uint32_t GENCTRL7:1;       /*!< bit:      9  Generic Clock Generator Control 7 Synchronization Busy bits */
    uint32_t GENCTRL8:1;       /*!< bit:     10  Generic Clock Generator Control 8 Synchronization Busy bits */
    uint32_t :21;              /*!< bit: 11..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  struct {
    uint32_t :2;               /*!< bit:  0.. 1  Reserved                           */
    uint32_t GENCTRL:9;        /*!< bit:  2..10  Generic Clock Generator Control x Synchronization Busy bits */
    uint32_t :21;              /*!< bit: 11..31  Reserved                           */
  } vec;                       /*!< Structure used for vec  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} HW_GCLK_SYNCBUSY_Type;

#define HW_GCLK_SYNCBUSY_OFFSET        0x04         /**< \brief (HW_GCLK_SYNCBUSY offset) Synchronization Busy */
#define HW_GCLK_SYNCBUSY_RESETVALUE    _U_(0x00000000) /**< \brief (HW_GCLK_SYNCBUSY reset_value) Synchronization Busy */

#define HW_GCLK_SYNCBUSY_SWRST_Pos     0            /**< \brief (HW_GCLK_SYNCBUSY) Software Reset Synchroniation Busy bit */
#define HW_GCLK_SYNCBUSY_SWRST         (_U_(0x1) << HW_GCLK_SYNCBUSY_SWRST_Pos)
#define HW_GCLK_SYNCBUSY_GENCTRL0_Pos  2            /**< \brief (HW_GCLK_SYNCBUSY) Generic Clock Generator Control 0 Synchronization Busy bits */
#define HW_GCLK_SYNCBUSY_GENCTRL0      (_U_(1) << HW_GCLK_SYNCBUSY_GENCTRL0_Pos)
#define HW_GCLK_SYNCBUSY_GENCTRL1_Pos  3            /**< \brief (HW_GCLK_SYNCBUSY) Generic Clock Generator Control 1 Synchronization Busy bits */
#define HW_GCLK_SYNCBUSY_GENCTRL1      (_U_(1) << HW_GCLK_SYNCBUSY_GENCTRL1_Pos)
#define HW_GCLK_SYNCBUSY_GENCTRL2_Pos  4            /**< \brief (HW_GCLK_SYNCBUSY) Generic Clock Generator Control 2 Synchronization Busy bits */
#define HW_GCLK_SYNCBUSY_GENCTRL2      (_U_(1) << HW_GCLK_SYNCBUSY_GENCTRL2_Pos)
#define HW_GCLK_SYNCBUSY_GENCTRL3_Pos  5            /**< \brief (HW_GCLK_SYNCBUSY) Generic Clock Generator Control 3 Synchronization Busy bits */
#define HW_GCLK_SYNCBUSY_GENCTRL3      (_U_(1) << HW_GCLK_SYNCBUSY_GENCTRL3_Pos)
#define HW_GCLK_SYNCBUSY_GENCTRL4_Pos  6            /**< \brief (HW_GCLK_SYNCBUSY) Generic Clock Generator Control 4 Synchronization Busy bits */
#define HW_GCLK_SYNCBUSY_GENCTRL4      (_U_(1) << HW_GCLK_SYNCBUSY_GENCTRL4_Pos)
#define HW_GCLK_SYNCBUSY_GENCTRL5_Pos  7            /**< \brief (HW_GCLK_SYNCBUSY) Generic Clock Generator Control 5 Synchronization Busy bits */
#define HW_GCLK_SYNCBUSY_GENCTRL5      (_U_(1) << HW_GCLK_SYNCBUSY_GENCTRL5_Pos)
#define HW_GCLK_SYNCBUSY_GENCTRL6_Pos  8            /**< \brief (HW_GCLK_SYNCBUSY) Generic Clock Generator Control 6 Synchronization Busy bits */
#define HW_GCLK_SYNCBUSY_GENCTRL6      (_U_(1) << HW_GCLK_SYNCBUSY_GENCTRL6_Pos)
#define HW_GCLK_SYNCBUSY_GENCTRL7_Pos  9            /**< \brief (HW_GCLK_SYNCBUSY) Generic Clock Generator Control 7 Synchronization Busy bits */
#define HW_GCLK_SYNCBUSY_GENCTRL7      (_U_(1) << HW_GCLK_SYNCBUSY_GENCTRL7_Pos)
#define HW_GCLK_SYNCBUSY_GENCTRL8_Pos  10           /**< \brief (HW_GCLK_SYNCBUSY) Generic Clock Generator Control 8 Synchronization Busy bits */
#define HW_GCLK_SYNCBUSY_GENCTRL8      (_U_(1) << HW_GCLK_SYNCBUSY_GENCTRL8_Pos)
#define HW_GCLK_SYNCBUSY_GENCTRL_Pos   2            /**< \brief (HW_GCLK_SYNCBUSY) Generic Clock Generator Control x Synchronization Busy bits */
#define HW_GCLK_SYNCBUSY_GENCTRL_Msk   (_U_(0x1FF) << HW_GCLK_SYNCBUSY_GENCTRL_Pos)
#define HW_GCLK_SYNCBUSY_GENCTRL(value) (HW_GCLK_SYNCBUSY_GENCTRL_Msk & ((value) << HW_GCLK_SYNCBUSY_GENCTRL_Pos))
#define   HW_GCLK_SYNCBUSY_GENCTRL_GCLK0_Val _U_(0x1)   /**< \brief (HW_GCLK_SYNCBUSY) Generic clock generator 0 */
#define   HW_GCLK_SYNCBUSY_GENCTRL_GCLK1_Val _U_(0x2)   /**< \brief (HW_GCLK_SYNCBUSY) Generic clock generator 1 */
#define   HW_GCLK_SYNCBUSY_GENCTRL_GCLK2_Val _U_(0x4)   /**< \brief (HW_GCLK_SYNCBUSY) Generic clock generator 2 */
#define   HW_GCLK_SYNCBUSY_GENCTRL_GCLK3_Val _U_(0x8)   /**< \brief (HW_GCLK_SYNCBUSY) Generic clock generator 3 */
#define   HW_GCLK_SYNCBUSY_GENCTRL_GCLK4_Val _U_(0x10)   /**< \brief (HW_GCLK_SYNCBUSY) Generic clock generator 4 */
#define   HW_GCLK_SYNCBUSY_GENCTRL_GCLK5_Val _U_(0x20)   /**< \brief (HW_GCLK_SYNCBUSY) Generic clock generator 5 */
#define   HW_GCLK_SYNCBUSY_GENCTRL_GCLK6_Val _U_(0x40)   /**< \brief (HW_GCLK_SYNCBUSY) Generic clock generator 6 */
#define   HW_GCLK_SYNCBUSY_GENCTRL_GCLK7_Val _U_(0x80)   /**< \brief (HW_GCLK_SYNCBUSY) Generic clock generator 7 */
#define   HW_GCLK_SYNCBUSY_GENCTRL_GCLK8_Val _U_(0x100)   /**< \brief (HW_GCLK_SYNCBUSY) Generic clock generator 8 */
#define HW_GCLK_SYNCBUSY_GENCTRL_GCLK0 (HW_GCLK_SYNCBUSY_GENCTRL_GCLK0_Val << HW_GCLK_SYNCBUSY_GENCTRL_Pos)
#define HW_GCLK_SYNCBUSY_GENCTRL_GCLK1 (HW_GCLK_SYNCBUSY_GENCTRL_GCLK1_Val << HW_GCLK_SYNCBUSY_GENCTRL_Pos)
#define HW_GCLK_SYNCBUSY_GENCTRL_GCLK2 (HW_GCLK_SYNCBUSY_GENCTRL_GCLK2_Val << HW_GCLK_SYNCBUSY_GENCTRL_Pos)
#define HW_GCLK_SYNCBUSY_GENCTRL_GCLK3 (HW_GCLK_SYNCBUSY_GENCTRL_GCLK3_Val << HW_GCLK_SYNCBUSY_GENCTRL_Pos)
#define HW_GCLK_SYNCBUSY_GENCTRL_GCLK4 (HW_GCLK_SYNCBUSY_GENCTRL_GCLK4_Val << HW_GCLK_SYNCBUSY_GENCTRL_Pos)
#define HW_GCLK_SYNCBUSY_GENCTRL_GCLK5 (HW_GCLK_SYNCBUSY_GENCTRL_GCLK5_Val << HW_GCLK_SYNCBUSY_GENCTRL_Pos)
#define HW_GCLK_SYNCBUSY_GENCTRL_GCLK6 (HW_GCLK_SYNCBUSY_GENCTRL_GCLK6_Val << HW_GCLK_SYNCBUSY_GENCTRL_Pos)
#define HW_GCLK_SYNCBUSY_GENCTRL_GCLK7 (HW_GCLK_SYNCBUSY_GENCTRL_GCLK7_Val << HW_GCLK_SYNCBUSY_GENCTRL_Pos)
#define HW_GCLK_SYNCBUSY_GENCTRL_GCLK8 (HW_GCLK_SYNCBUSY_GENCTRL_GCLK8_Val << HW_GCLK_SYNCBUSY_GENCTRL_Pos)
#define HW_GCLK_SYNCBUSY_MASK          _U_(0x000007FD) /**< \brief (HW_GCLK_SYNCBUSY) MASK Register */

/* -------- HW_GCLK_GENCTRL : (GCLK Offset: 0x20) (R/W 32) Generic Clock Generator Control -------- */
typedef union {
  struct {
    uint32_t SRC:4;            /*!< bit:  0.. 3  Source Select                      */
    uint32_t :4;               /*!< bit:  4.. 7  Reserved                           */
    uint32_t GENEN:1;          /*!< bit:      8  Generic Clock Generator Enable     */
    uint32_t IDC:1;            /*!< bit:      9  Improve Duty Cycle                 */
    uint32_t OOV:1;            /*!< bit:     10  Output Off Value                   */
    uint32_t OE:1;             /*!< bit:     11  Output Enable                      */
    uint32_t DIVSEL:1;         /*!< bit:     12  Divide Selection                   */
    uint32_t RUNSTDBY:1;       /*!< bit:     13  Run in Standby                     */
    uint32_t :2;               /*!< bit: 14..15  Reserved                           */
    uint32_t DIV:16;           /*!< bit: 16..31  Division Factor                    */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} HW_GCLK_GENCTRL_Type;

#define HW_GCLK_GENCTRL_OFFSET         0x20         /**< \brief (HW_GCLK_GENCTRL offset) Generic Clock Generator Control */
#define HW_GCLK_GENCTRL_RESETVALUE     _U_(0x00000000) /**< \brief (HW_GCLK_GENCTRL reset_value) Generic Clock Generator Control */

#define HW_GCLK_GENCTRL_SRC_Pos        0            /**< \brief (HW_GCLK_GENCTRL) Source Select */
#define HW_GCLK_GENCTRL_SRC_Msk        (_U_(0xF) << HW_GCLK_GENCTRL_SRC_Pos)
#define HW_GCLK_GENCTRL_SRC(value)     (HW_GCLK_GENCTRL_SRC_Msk & ((value) << HW_GCLK_GENCTRL_SRC_Pos))
#define   HW_GCLK_GENCTRL_SRC_XOSC_Val       _U_(0x0)   /**< \brief (HW_GCLK_GENCTRL) XOSC oscillator output */
#define   HW_GCLK_GENCTRL_SRC_GCLKIN_Val     _U_(0x1)   /**< \brief (HW_GCLK_GENCTRL) Generator input pad */
#define   HW_GCLK_GENCTRL_SRC_GCLKGEN1_Val   _U_(0x2)   /**< \brief (HW_GCLK_GENCTRL) Generic clock generator 1 output */
#define   HW_GCLK_GENCTRL_SRC_OSCULP32K_Val  _U_(0x3)   /**< \brief (HW_GCLK_GENCTRL) OSCULP32K oscillator output */
#define   HW_GCLK_GENCTRL_SRC_OSC32K_Val     _U_(0x4)   /**< \brief (HW_GCLK_GENCTRL) OSC32K oscillator output */
#define   HW_GCLK_GENCTRL_SRC_XOSC32K_Val    _U_(0x5)   /**< \brief (HW_GCLK_GENCTRL) XOSC32K oscillator output */
#define   HW_GCLK_GENCTRL_SRC_OSC16M_Val     _U_(0x6)   /**< \brief (HW_GCLK_GENCTRL) OSC16M oscillator output */
#define   HW_GCLK_GENCTRL_SRC_DFLL48M_Val    _U_(0x7)   /**< \brief (HW_GCLK_GENCTRL) DFLL48M output */
#define   HW_GCLK_GENCTRL_SRC_DPLL96M_Val    _U_(0x8)   /**< \brief (HW_GCLK_GENCTRL) DPLL96M output */
#define HW_GCLK_GENCTRL_SRC_XOSC       (HW_GCLK_GENCTRL_SRC_XOSC_Val     << HW_GCLK_GENCTRL_SRC_Pos)
#define HW_GCLK_GENCTRL_SRC_GCLKIN     (HW_GCLK_GENCTRL_SRC_GCLKIN_Val   << HW_GCLK_GENCTRL_SRC_Pos)
#define HW_GCLK_GENCTRL_SRC_GCLKGEN1   (HW_GCLK_GENCTRL_SRC_GCLKGEN1_Val << HW_GCLK_GENCTRL_SRC_Pos)
#define HW_GCLK_GENCTRL_SRC_OSCULP32K  (HW_GCLK_GENCTRL_SRC_OSCULP32K_Val << HW_GCLK_GENCTRL_SRC_Pos)
#define HW_GCLK_GENCTRL_SRC_OSC32K     (HW_GCLK_GENCTRL_SRC_OSC32K_Val   << HW_GCLK_GENCTRL_SRC_Pos)
#define HW_GCLK_GENCTRL_SRC_XOSC32K    (HW_GCLK_GENCTRL_SRC_XOSC32K_Val  << HW_GCLK_GENCTRL_SRC_Pos)
#define HW_GCLK_GENCTRL_SRC_OSC16M     (HW_GCLK_GENCTRL_SRC_OSC16M_Val   << HW_GCLK_GENCTRL_SRC_Pos)
#define HW_GCLK_GENCTRL_SRC_DFLL48M    (HW_GCLK_GENCTRL_SRC_DFLL48M_Val  << HW_GCLK_GENCTRL_SRC_Pos)
#define HW_GCLK_GENCTRL_SRC_DPLL96M    (HW_GCLK_GENCTRL_SRC_DPLL96M_Val  << HW_GCLK_GENCTRL_SRC_Pos)
#define HW_GCLK_GENCTRL_GENEN_Pos      8            /**< \brief (HW_GCLK_GENCTRL) Generic Clock Generator Enable */
#define HW_GCLK_GENCTRL_GENEN          (_U_(0x1) << HW_GCLK_GENCTRL_GENEN_Pos)
#define HW_GCLK_GENCTRL_IDC_Pos        9            /**< \brief (HW_GCLK_GENCTRL) Improve Duty Cycle */
#define HW_GCLK_GENCTRL_IDC            (_U_(0x1) << HW_GCLK_GENCTRL_IDC_Pos)
#define HW_GCLK_GENCTRL_OOV_Pos        10           /**< \brief (HW_GCLK_GENCTRL) Output Off Value */
#define HW_GCLK_GENCTRL_OOV            (_U_(0x1) << HW_GCLK_GENCTRL_OOV_Pos)
#define HW_GCLK_GENCTRL_OE_Pos         11           /**< \brief (HW_GCLK_GENCTRL) Output Enable */
#define HW_GCLK_GENCTRL_OE             (_U_(0x1) << HW_GCLK_GENCTRL_OE_Pos)
#define HW_GCLK_GENCTRL_DIVSEL_Pos     12           /**< \brief (HW_GCLK_GENCTRL) Divide Selection */
#define HW_GCLK_GENCTRL_DIVSEL         (_U_(0x1) << HW_GCLK_GENCTRL_DIVSEL_Pos)
#define HW_GCLK_GENCTRL_RUNSTDBY_Pos   13           /**< \brief (HW_GCLK_GENCTRL) Run in Standby */
#define HW_GCLK_GENCTRL_RUNSTDBY       (_U_(0x1) << HW_GCLK_GENCTRL_RUNSTDBY_Pos)
#define HW_GCLK_GENCTRL_DIV_Pos        16           /**< \brief (HW_GCLK_GENCTRL) Division Factor */
#define HW_GCLK_GENCTRL_DIV_Msk        (_U_(0xFFFF) << HW_GCLK_GENCTRL_DIV_Pos)
#define HW_GCLK_GENCTRL_DIV(value)     (HW_GCLK_GENCTRL_DIV_Msk & ((value) << HW_GCLK_GENCTRL_DIV_Pos))
#define HW_GCLK_GENCTRL_MASK           _U_(0xFFFF3F0F) /**< \brief (HW_GCLK_GENCTRL) MASK Register */

/* -------- HW_GCLK_PCHCTRL : (GCLK Offset: 0x80) (R/W 32) Peripheral Clock Control -------- */
typedef union {
  struct {
    uint32_t GEN:4;            /*!< bit:  0.. 3  Generic Clock Generator            */
    uint32_t :2;               /*!< bit:  4.. 5  Reserved                           */
    uint32_t CHEN:1;           /*!< bit:      6  Channel Enable                     */
    uint32_t WRTLOCK:1;        /*!< bit:      7  Write Lock                         */
    uint32_t :24;              /*!< bit:  8..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} HW_GCLK_PCHCTRL_Type;

#define HW_GCLK_PCHCTRL_OFFSET         0x80         /**< \brief (HW_GCLK_PCHCTRL offset) Peripheral Clock Control */
#define HW_GCLK_PCHCTRL_RESETVALUE     _U_(0x00000000) /**< \brief (HW_GCLK_PCHCTRL reset_value) Peripheral Clock Control */

#define HW_GCLK_PCHCTRL_GEN_Pos        0            /**< \brief (HW_GCLK_PCHCTRL) Generic Clock Generator */
#define HW_GCLK_PCHCTRL_GEN_Msk        (_U_(0xF) << HW_GCLK_PCHCTRL_GEN_Pos)
#define HW_GCLK_PCHCTRL_GEN(value)     (HW_GCLK_PCHCTRL_GEN_Msk & ((value) << HW_GCLK_PCHCTRL_GEN_Pos))
#define   HW_GCLK_PCHCTRL_GEN_GCLK0_Val      _U_(0x0)   /**< \brief (HW_GCLK_PCHCTRL) Generic clock generator 0 */
#define   HW_GCLK_PCHCTRL_GEN_GCLK1_Val      _U_(0x1)   /**< \brief (HW_GCLK_PCHCTRL) Generic clock generator 1 */
#define   HW_GCLK_PCHCTRL_GEN_GCLK2_Val      _U_(0x2)   /**< \brief (HW_GCLK_PCHCTRL) Generic clock generator 2 */
#define   HW_GCLK_PCHCTRL_GEN_GCLK3_Val      _U_(0x3)   /**< \brief (HW_GCLK_PCHCTRL) Generic clock generator 3 */
#define   HW_GCLK_PCHCTRL_GEN_GCLK4_Val      _U_(0x4)   /**< \brief (HW_GCLK_PCHCTRL) Generic clock generator 4 */
#define   HW_GCLK_PCHCTRL_GEN_GCLK5_Val      _U_(0x5)   /**< \brief (HW_GCLK_PCHCTRL) Generic clock generator 5 */
#define   HW_GCLK_PCHCTRL_GEN_GCLK6_Val      _U_(0x6)   /**< \brief (HW_GCLK_PCHCTRL) Generic clock generator 6 */
#define   HW_GCLK_PCHCTRL_GEN_GCLK7_Val      _U_(0x7)   /**< \brief (HW_GCLK_PCHCTRL) Generic clock generator 7 */
#define   HW_GCLK_PCHCTRL_GEN_GCLK8_Val      _U_(0x8)   /**< \brief (HW_GCLK_PCHCTRL) Generic clock generator 8 */
#define HW_GCLK_PCHCTRL_GEN_GCLK0      (HW_GCLK_PCHCTRL_GEN_GCLK0_Val    << HW_GCLK_PCHCTRL_GEN_Pos)
#define HW_GCLK_PCHCTRL_GEN_GCLK1      (HW_GCLK_PCHCTRL_GEN_GCLK1_Val    << HW_GCLK_PCHCTRL_GEN_Pos)
#define HW_GCLK_PCHCTRL_GEN_GCLK2      (HW_GCLK_PCHCTRL_GEN_GCLK2_Val    << HW_GCLK_PCHCTRL_GEN_Pos)
#define HW_GCLK_PCHCTRL_GEN_GCLK3      (HW_GCLK_PCHCTRL_GEN_GCLK3_Val    << HW_GCLK_PCHCTRL_GEN_Pos)
#define HW_GCLK_PCHCTRL_GEN_GCLK4      (HW_GCLK_PCHCTRL_GEN_GCLK4_Val    << HW_GCLK_PCHCTRL_GEN_Pos)
#define HW_GCLK_PCHCTRL_GEN_GCLK5      (HW_GCLK_PCHCTRL_GEN_GCLK5_Val    << HW_GCLK_PCHCTRL_GEN_Pos)
#define HW_GCLK_PCHCTRL_GEN_GCLK6      (HW_GCLK_PCHCTRL_GEN_GCLK6_Val    << HW_GCLK_PCHCTRL_GEN_Pos)
#define HW_GCLK_PCHCTRL_GEN_GCLK7      (HW_GCLK_PCHCTRL_GEN_GCLK7_Val    << HW_GCLK_PCHCTRL_GEN_Pos)
#define HW_GCLK_PCHCTRL_GEN_GCLK8      (HW_GCLK_PCHCTRL_GEN_GCLK8_Val    << HW_GCLK_PCHCTRL_GEN_Pos)
#define HW_GCLK_PCHCTRL_CHEN_Pos       6            /**< \brief (HW_GCLK_PCHCTRL) Channel Enable */
#define HW_GCLK_PCHCTRL_CHEN           (_U_(0x1) << HW_GCLK_PCHCTRL_CHEN_Pos)
#define HW_GCLK_PCHCTRL_WRTLOCK_Pos    7            /**< \brief (HW_GCLK_PCHCTRL) Write Lock */
#define HW_GCLK_PCHCTRL_WRTLOCK        (_U_(0x1) << HW_GCLK_PCHCTRL_WRTLOCK_Pos)
#define HW_GCLK_PCHCTRL_MASK           _U_(0x000000CF) /**< \brief (HW_GCLK_PCHCTRL) MASK Register */

/** \brief GCLK hardware registers */
typedef struct {
  __IO HW_GCLK_CTRLA_Type           CTRLA;       /**< \brief Offset: 0x00 (R/W  8) Control */
       RoReg8                    Reserved1[0x3];
  __I  HW_GCLK_SYNCBUSY_Type        SYNCBUSY;    /**< \brief Offset: 0x04 (R/  32) Synchronization Busy */
       RoReg8                    Reserved2[0x18];
  __IO HW_GCLK_GENCTRL_Type         GENCTRL[9];  /**< \brief Offset: 0x20 (R/W 32) Generic Clock Generator Control */
       RoReg8                    Reserved3[0x3C];
  __IO HW_GCLK_PCHCTRL_Type         PCHCTRL[36]; /**< \brief Offset: 0x80 (R/W 32) Peripheral Clock Control */
} Gclk;


/* ========== Register definition for GCLK peripheral ========== */
#define HW_REG_GCLK_CTRLA             (*(RwReg8 *)0x40001800UL) /**< \brief (GCLK) Control */
#define HW_REG_GCLK_SYNCBUSY          (*(RoReg  *)0x40001804UL) /**< \brief (GCLK) Synchronization Busy */
#define HW_REG_GCLK_GENCTRL0          (*(RwReg  *)0x40001820UL) /**< \brief (GCLK) Generic Clock Generator Control 0 */
#define HW_REG_GCLK_GENCTRL1          (*(RwReg  *)0x40001824UL) /**< \brief (GCLK) Generic Clock Generator Control 1 */
#define HW_REG_GCLK_GENCTRL2          (*(RwReg  *)0x40001828UL) /**< \brief (GCLK) Generic Clock Generator Control 2 */
#define HW_REG_GCLK_GENCTRL3          (*(RwReg  *)0x4000182CUL) /**< \brief (GCLK) Generic Clock Generator Control 3 */
#define HW_REG_GCLK_GENCTRL4          (*(RwReg  *)0x40001830UL) /**< \brief (GCLK) Generic Clock Generator Control 4 */
#define HW_REG_GCLK_GENCTRL5          (*(RwReg  *)0x40001834UL) /**< \brief (GCLK) Generic Clock Generator Control 5 */
#define HW_REG_GCLK_GENCTRL6          (*(RwReg  *)0x40001838UL) /**< \brief (GCLK) Generic Clock Generator Control 6 */
#define HW_REG_GCLK_GENCTRL7          (*(RwReg  *)0x4000183CUL) /**< \brief (GCLK) Generic Clock Generator Control 7 */
#define HW_REG_GCLK_GENCTRL8          (*(RwReg  *)0x40001840UL) /**< \brief (GCLK) Generic Clock Generator Control 8 */
#define HW_REG_GCLK_PCHCTRL0          (*(RwReg  *)0x40001880UL) /**< \brief (GCLK) Peripheral Clock Control 0 */
#define HW_REG_GCLK_PCHCTRL1          (*(RwReg  *)0x40001884UL) /**< \brief (GCLK) Peripheral Clock Control 1 */
#define HW_REG_GCLK_PCHCTRL2          (*(RwReg  *)0x40001888UL) /**< \brief (GCLK) Peripheral Clock Control 2 */
#define HW_REG_GCLK_PCHCTRL3          (*(RwReg  *)0x4000188CUL) /**< \brief (GCLK) Peripheral Clock Control 3 */
#define HW_REG_GCLK_PCHCTRL4          (*(RwReg  *)0x40001890UL) /**< \brief (GCLK) Peripheral Clock Control 4 */
#define HW_REG_GCLK_PCHCTRL5          (*(RwReg  *)0x40001894UL) /**< \brief (GCLK) Peripheral Clock Control 5 */
#define HW_REG_GCLK_PCHCTRL6          (*(RwReg  *)0x40001898UL) /**< \brief (GCLK) Peripheral Clock Control 6 */
#define HW_REG_GCLK_PCHCTRL7          (*(RwReg  *)0x4000189CUL) /**< \brief (GCLK) Peripheral Clock Control 7 */
#define HW_REG_GCLK_PCHCTRL8          (*(RwReg  *)0x400018A0UL) /**< \brief (GCLK) Peripheral Clock Control 8 */
#define HW_REG_GCLK_PCHCTRL9          (*(RwReg  *)0x400018A4UL) /**< \brief (GCLK) Peripheral Clock Control 9 */
#define HW_REG_GCLK_PCHCTRL10         (*(RwReg  *)0x400018A8UL) /**< \brief (GCLK) Peripheral Clock Control 10 */
#define HW_REG_GCLK_PCHCTRL11         (*(RwReg  *)0x400018ACUL) /**< \brief (GCLK) Peripheral Clock Control 11 */
#define HW_REG_GCLK_PCHCTRL12         (*(RwReg  *)0x400018B0UL) /**< \brief (GCLK) Peripheral Clock Control 12 */
#define HW_REG_GCLK_PCHCTRL13         (*(RwReg  *)0x400018B4UL) /**< \brief (GCLK) Peripheral Clock Control 13 */
#define HW_REG_GCLK_PCHCTRL14         (*(RwReg  *)0x400018B8UL) /**< \brief (GCLK) Peripheral Clock Control 14 */
#define HW_REG_GCLK_PCHCTRL15         (*(RwReg  *)0x400018BCUL) /**< \brief (GCLK) Peripheral Clock Control 15 */
#define HW_REG_GCLK_PCHCTRL16         (*(RwReg  *)0x400018C0UL) /**< \brief (GCLK) Peripheral Clock Control 16 */
#define HW_REG_GCLK_PCHCTRL17         (*(RwReg  *)0x400018C4UL) /**< \brief (GCLK) Peripheral Clock Control 17 */
#define HW_REG_GCLK_PCHCTRL18         (*(RwReg  *)0x400018C8UL) /**< \brief (GCLK) Peripheral Clock Control 18 */
#define HW_REG_GCLK_PCHCTRL19         (*(RwReg  *)0x400018CCUL) /**< \brief (GCLK) Peripheral Clock Control 19 */
#define HW_REG_GCLK_PCHCTRL20         (*(RwReg  *)0x400018D0UL) /**< \brief (GCLK) Peripheral Clock Control 20 */
#define HW_REG_GCLK_PCHCTRL21         (*(RwReg  *)0x400018D4UL) /**< \brief (GCLK) Peripheral Clock Control 21 */
#define HW_REG_GCLK_PCHCTRL22         (*(RwReg  *)0x400018D8UL) /**< \brief (GCLK) Peripheral Clock Control 22 */
#define HW_REG_GCLK_PCHCTRL23         (*(RwReg  *)0x400018DCUL) /**< \brief (GCLK) Peripheral Clock Control 23 */
#define HW_REG_GCLK_PCHCTRL24         (*(RwReg  *)0x400018E0UL) /**< \brief (GCLK) Peripheral Clock Control 24 */
#define HW_REG_GCLK_PCHCTRL25         (*(RwReg  *)0x400018E4UL) /**< \brief (GCLK) Peripheral Clock Control 25 */
#define HW_REG_GCLK_PCHCTRL26         (*(RwReg  *)0x400018E8UL) /**< \brief (GCLK) Peripheral Clock Control 26 */
#define HW_REG_GCLK_PCHCTRL27         (*(RwReg  *)0x400018ECUL) /**< \brief (GCLK) Peripheral Clock Control 27 */
#define HW_REG_GCLK_PCHCTRL28         (*(RwReg  *)0x400018F0UL) /**< \brief (GCLK) Peripheral Clock Control 28 */
#define HW_REG_GCLK_PCHCTRL29         (*(RwReg  *)0x400018F4UL) /**< \brief (GCLK) Peripheral Clock Control 29 */
#define HW_REG_GCLK_PCHCTRL30         (*(RwReg  *)0x400018F8UL) /**< \brief (GCLK) Peripheral Clock Control 30 */
#define HW_REG_GCLK_PCHCTRL31         (*(RwReg  *)0x400018FCUL) /**< \brief (GCLK) Peripheral Clock Control 31 */
#define HW_REG_GCLK_PCHCTRL32         (*(RwReg  *)0x40001900UL) /**< \brief (GCLK) Peripheral Clock Control 32 */
#define HW_REG_GCLK_PCHCTRL33         (*(RwReg  *)0x40001904UL) /**< \brief (GCLK) Peripheral Clock Control 33 */
#define HW_REG_GCLK_PCHCTRL34         (*(RwReg  *)0x40001908UL) /**< \brief (GCLK) Peripheral Clock Control 34 */
#define HW_REG_GCLK_PCHCTRL35         (*(RwReg  *)0x4000190CUL) /**< \brief (GCLK) Peripheral Clock Control 35 */

/* ========== Instance parameters for GCLK peripheral ========== */
#define HW_GCLK_GENDIV_BITS            16      
#define HW_GCLK_GEN_BITS               4       
#define HW_GCLK_GEN_NUM                9        // Number of Generic Clock Generators
#define HW_GCLK_GEN_NUM_MSB            8        // Number of Generic Clock Generators - 1
#define HW_GCLK_GEN_SOURCE_NUM_MSB     8        // Number of Generic Clock Sources - 1
#define HW_GCLK_NUM                    36       // Number of Generic Clock Users
#define HW_GCLK_SOURCE_BITS            4       
#define HW_GCLK_SOURCE_DFLL48M         7       
#define HW_GCLK_SOURCE_DPLL96M         8       
#define HW_GCLK_SOURCE_GCLKGEN1        2       
#define HW_GCLK_SOURCE_GCLKIN          1       
#define HW_GCLK_SOURCE_NUM             9        // Number of Generic Clock Sources
#define HW_GCLK_SOURCE_OSCULP32K       3       
#define HW_GCLK_SOURCE_OSC16M          6       
#define HW_GCLK_SOURCE_OSC32K          4       
#define HW_GCLK_SOURCE_XOSC            0       
#define HW_GCLK_SOURCE_XOSC32K         5       


#endif //HW_RAK4260_GCLK_H