#ifndef HW_RAK4260_RTC_H
#define HW_RAK4260_RTC_H


#define HW_RTC_U2250
#define REV_RTC                     0x110

/* -------- HW_RTC_MODE0_CTRLA : (RTC Offset: 0x00) (R/W 16) MODE0 MODE0 Control A -------- */
typedef union {
  struct {
    uint16_t SWRST:1;          /*!< bit:      0  Software Reset                     */
    uint16_t ENABLE:1;         /*!< bit:      1  Enable                             */
    uint16_t MODE:2;           /*!< bit:  2.. 3  Operating Mode                     */
    uint16_t :3;               /*!< bit:  4.. 6  Reserved                           */
    uint16_t MATCHCLR:1;       /*!< bit:      7  Clear on Match                     */
    uint16_t PRESCALER:4;      /*!< bit:  8..11  Prescaler                          */
    uint16_t :3;               /*!< bit: 12..14  Reserved                           */
    uint16_t COUNTSYNC:1;      /*!< bit:     15  Count Read Synchronization Enable  */
  } bit;                       /*!< Structure used for bit  access                  */
  uint16_t reg;                /*!< Type      used for register access              */
} HW_RTC_MODE0_CTRLA_Type;

#define HW_RTC_MODE0_CTRLA_OFFSET      0x00         /**< \brief (HW_RTC_MODE0_CTRLA offset) MODE0 Control A */
#define HW_RTC_MODE0_CTRLA_RESETVALUE  _U_(0x0000)  /**< \brief (HW_RTC_MODE0_CTRLA reset_value) MODE0 Control A */

#define HW_RTC_MODE0_CTRLA_SWRST_Pos   0            /**< \brief (HW_RTC_MODE0_CTRLA) Software Reset */
#define HW_RTC_MODE0_CTRLA_SWRST       (_U_(0x1) << HW_RTC_MODE0_CTRLA_SWRST_Pos)
#define HW_RTC_MODE0_CTRLA_ENABLE_Pos  1            /**< \brief (HW_RTC_MODE0_CTRLA) Enable */
#define HW_RTC_MODE0_CTRLA_ENABLE      (_U_(0x1) << HW_RTC_MODE0_CTRLA_ENABLE_Pos)
#define HW_RTC_MODE0_CTRLA_MODE_Pos    2            /**< \brief (HW_RTC_MODE0_CTRLA) Operating Mode */
#define HW_RTC_MODE0_CTRLA_MODE_Msk    (_U_(0x3) << HW_RTC_MODE0_CTRLA_MODE_Pos)
#define HW_RTC_MODE0_CTRLA_MODE(value) (HW_RTC_MODE0_CTRLA_MODE_Msk & ((value) << HW_RTC_MODE0_CTRLA_MODE_Pos))
#define   HW_RTC_MODE0_CTRLA_MODE_COUNT32_Val _U_(0x0)   /**< \brief (HW_RTC_MODE0_CTRLA) Mode 0: 32-bit Counter */
#define   HW_RTC_MODE0_CTRLA_MODE_COUNT16_Val _U_(0x1)   /**< \brief (HW_RTC_MODE0_CTRLA) Mode 1: 16-bit Counter */
#define   HW_RTC_MODE0_CTRLA_MODE_CLOCK_Val  _U_(0x2)   /**< \brief (HW_RTC_MODE0_CTRLA) Mode 2: Clock/Calendar */
#define HW_RTC_MODE0_CTRLA_MODE_COUNT32 (HW_RTC_MODE0_CTRLA_MODE_COUNT32_Val << HW_RTC_MODE0_CTRLA_MODE_Pos)
#define HW_RTC_MODE0_CTRLA_MODE_COUNT16 (HW_RTC_MODE0_CTRLA_MODE_COUNT16_Val << HW_RTC_MODE0_CTRLA_MODE_Pos)
#define HW_RTC_MODE0_CTRLA_MODE_CLOCK  (HW_RTC_MODE0_CTRLA_MODE_CLOCK_Val << HW_RTC_MODE0_CTRLA_MODE_Pos)
#define HW_RTC_MODE0_CTRLA_MATCHCLR_Pos 7            /**< \brief (HW_RTC_MODE0_CTRLA) Clear on Match */
#define HW_RTC_MODE0_CTRLA_MATCHCLR    (_U_(0x1) << HW_RTC_MODE0_CTRLA_MATCHCLR_Pos)
#define HW_RTC_MODE0_CTRLA_PRESCALER_Pos 8            /**< \brief (HW_RTC_MODE0_CTRLA) Prescaler */
#define HW_RTC_MODE0_CTRLA_PRESCALER_Msk (_U_(0xF) << HW_RTC_MODE0_CTRLA_PRESCALER_Pos)
#define HW_RTC_MODE0_CTRLA_PRESCALER(value) (HW_RTC_MODE0_CTRLA_PRESCALER_Msk & ((value) << HW_RTC_MODE0_CTRLA_PRESCALER_Pos))
#define   HW_RTC_MODE0_CTRLA_PRESCALER_OFF_Val _U_(0x0)   /**< \brief (HW_RTC_MODE0_CTRLA) CLK_HW_RTC_CNT = GCLK_RTC/1 */
#define   HW_RTC_MODE0_CTRLA_PRESCALER_DIV1_Val _U_(0x1)   /**< \brief (HW_RTC_MODE0_CTRLA) CLK_HW_RTC_CNT = GCLK_RTC/1 */
#define   HW_RTC_MODE0_CTRLA_PRESCALER_DIV2_Val _U_(0x2)   /**< \brief (HW_RTC_MODE0_CTRLA) CLK_HW_RTC_CNT = GCLK_RTC/2 */
#define   HW_RTC_MODE0_CTRLA_PRESCALER_DIV4_Val _U_(0x3)   /**< \brief (HW_RTC_MODE0_CTRLA) CLK_HW_RTC_CNT = GCLK_RTC/4 */
#define   HW_RTC_MODE0_CTRLA_PRESCALER_DIV8_Val _U_(0x4)   /**< \brief (HW_RTC_MODE0_CTRLA) CLK_HW_RTC_CNT = GCLK_RTC/8 */
#define   HW_RTC_MODE0_CTRLA_PRESCALER_DIV16_Val _U_(0x5)   /**< \brief (HW_RTC_MODE0_CTRLA) CLK_HW_RTC_CNT = GCLK_RTC/16 */
#define   HW_RTC_MODE0_CTRLA_PRESCALER_DIV32_Val _U_(0x6)   /**< \brief (HW_RTC_MODE0_CTRLA) CLK_HW_RTC_CNT = GCLK_RTC/32 */
#define   HW_RTC_MODE0_CTRLA_PRESCALER_DIV64_Val _U_(0x7)   /**< \brief (HW_RTC_MODE0_CTRLA) CLK_HW_RTC_CNT = GCLK_RTC/64 */
#define   HW_RTC_MODE0_CTRLA_PRESCALER_DIV128_Val _U_(0x8)   /**< \brief (HW_RTC_MODE0_CTRLA) CLK_HW_RTC_CNT = GCLK_RTC/128 */
#define   HW_RTC_MODE0_CTRLA_PRESCALER_DIV256_Val _U_(0x9)   /**< \brief (HW_RTC_MODE0_CTRLA) CLK_HW_RTC_CNT = GCLK_RTC/256 */
#define   HW_RTC_MODE0_CTRLA_PRESCALER_DIV512_Val _U_(0xA)   /**< \brief (HW_RTC_MODE0_CTRLA) CLK_HW_RTC_CNT = GCLK_RTC/512 */
#define   HW_RTC_MODE0_CTRLA_PRESCALER_DIV1024_Val _U_(0xB)   /**< \brief (HW_RTC_MODE0_CTRLA) CLK_HW_RTC_CNT = GCLK_RTC/1024 */
#define HW_RTC_MODE0_CTRLA_PRESCALER_OFF (HW_RTC_MODE0_CTRLA_PRESCALER_OFF_Val << HW_RTC_MODE0_CTRLA_PRESCALER_Pos)
#define HW_RTC_MODE0_CTRLA_PRESCALER_DIV1 (HW_RTC_MODE0_CTRLA_PRESCALER_DIV1_Val << HW_RTC_MODE0_CTRLA_PRESCALER_Pos)
#define HW_RTC_MODE0_CTRLA_PRESCALER_DIV2 (HW_RTC_MODE0_CTRLA_PRESCALER_DIV2_Val << HW_RTC_MODE0_CTRLA_PRESCALER_Pos)
#define HW_RTC_MODE0_CTRLA_PRESCALER_DIV4 (HW_RTC_MODE0_CTRLA_PRESCALER_DIV4_Val << HW_RTC_MODE0_CTRLA_PRESCALER_Pos)
#define HW_RTC_MODE0_CTRLA_PRESCALER_DIV8 (HW_RTC_MODE0_CTRLA_PRESCALER_DIV8_Val << HW_RTC_MODE0_CTRLA_PRESCALER_Pos)
#define HW_RTC_MODE0_CTRLA_PRESCALER_DIV16 (HW_RTC_MODE0_CTRLA_PRESCALER_DIV16_Val << HW_RTC_MODE0_CTRLA_PRESCALER_Pos)
#define HW_RTC_MODE0_CTRLA_PRESCALER_DIV32 (HW_RTC_MODE0_CTRLA_PRESCALER_DIV32_Val << HW_RTC_MODE0_CTRLA_PRESCALER_Pos)
#define HW_RTC_MODE0_CTRLA_PRESCALER_DIV64 (HW_RTC_MODE0_CTRLA_PRESCALER_DIV64_Val << HW_RTC_MODE0_CTRLA_PRESCALER_Pos)
#define HW_RTC_MODE0_CTRLA_PRESCALER_DIV128 (HW_RTC_MODE0_CTRLA_PRESCALER_DIV128_Val << HW_RTC_MODE0_CTRLA_PRESCALER_Pos)
#define HW_RTC_MODE0_CTRLA_PRESCALER_DIV256 (HW_RTC_MODE0_CTRLA_PRESCALER_DIV256_Val << HW_RTC_MODE0_CTRLA_PRESCALER_Pos)
#define HW_RTC_MODE0_CTRLA_PRESCALER_DIV512 (HW_RTC_MODE0_CTRLA_PRESCALER_DIV512_Val << HW_RTC_MODE0_CTRLA_PRESCALER_Pos)
#define HW_RTC_MODE0_CTRLA_PRESCALER_DIV1024 (HW_RTC_MODE0_CTRLA_PRESCALER_DIV1024_Val << HW_RTC_MODE0_CTRLA_PRESCALER_Pos)
#define HW_RTC_MODE0_CTRLA_COUNTSYNC_Pos 15           /**< \brief (HW_RTC_MODE0_CTRLA) Count Read Synchronization Enable */
#define HW_RTC_MODE0_CTRLA_COUNTSYNC   (_U_(0x1) << HW_RTC_MODE0_CTRLA_COUNTSYNC_Pos)
#define HW_RTC_MODE0_CTRLA_MASK        _U_(0x8F8F)  /**< \brief (HW_RTC_MODE0_CTRLA) MASK Register */

/* -------- HW_RTC_MODE1_CTRLA : (RTC Offset: 0x00) (R/W 16) MODE1 MODE1 Control A -------- */
typedef union {
  struct {
    uint16_t SWRST:1;          /*!< bit:      0  Software Reset                     */
    uint16_t ENABLE:1;         /*!< bit:      1  Enable                             */
    uint16_t MODE:2;           /*!< bit:  2.. 3  Operating Mode                     */
    uint16_t :4;               /*!< bit:  4.. 7  Reserved                           */
    uint16_t PRESCALER:4;      /*!< bit:  8..11  Prescaler                          */
    uint16_t :3;               /*!< bit: 12..14  Reserved                           */
    uint16_t COUNTSYNC:1;      /*!< bit:     15  Count Read Synchronization Enable  */
  } bit;                       /*!< Structure used for bit  access                  */
  uint16_t reg;                /*!< Type      used for register access              */
} HW_RTC_MODE1_CTRLA_Type;

#define HW_RTC_MODE1_CTRLA_OFFSET      0x00         /**< \brief (HW_RTC_MODE1_CTRLA offset) MODE1 Control A */
#define HW_RTC_MODE1_CTRLA_RESETVALUE  _U_(0x0000)  /**< \brief (HW_RTC_MODE1_CTRLA reset_value) MODE1 Control A */

#define HW_RTC_MODE1_CTRLA_SWRST_Pos   0            /**< \brief (HW_RTC_MODE1_CTRLA) Software Reset */
#define HW_RTC_MODE1_CTRLA_SWRST       (_U_(0x1) << HW_RTC_MODE1_CTRLA_SWRST_Pos)
#define HW_RTC_MODE1_CTRLA_ENABLE_Pos  1            /**< \brief (HW_RTC_MODE1_CTRLA) Enable */
#define HW_RTC_MODE1_CTRLA_ENABLE      (_U_(0x1) << HW_RTC_MODE1_CTRLA_ENABLE_Pos)
#define HW_RTC_MODE1_CTRLA_MODE_Pos    2            /**< \brief (HW_RTC_MODE1_CTRLA) Operating Mode */
#define HW_RTC_MODE1_CTRLA_MODE_Msk    (_U_(0x3) << HW_RTC_MODE1_CTRLA_MODE_Pos)
#define HW_RTC_MODE1_CTRLA_MODE(value) (HW_RTC_MODE1_CTRLA_MODE_Msk & ((value) << HW_RTC_MODE1_CTRLA_MODE_Pos))
#define   HW_RTC_MODE1_CTRLA_MODE_COUNT32_Val _U_(0x0)   /**< \brief (HW_RTC_MODE1_CTRLA) Mode 0: 32-bit Counter */
#define   HW_RTC_MODE1_CTRLA_MODE_COUNT16_Val _U_(0x1)   /**< \brief (HW_RTC_MODE1_CTRLA) Mode 1: 16-bit Counter */
#define   HW_RTC_MODE1_CTRLA_MODE_CLOCK_Val  _U_(0x2)   /**< \brief (HW_RTC_MODE1_CTRLA) Mode 2: Clock/Calendar */
#define HW_RTC_MODE1_CTRLA_MODE_COUNT32 (HW_RTC_MODE1_CTRLA_MODE_COUNT32_Val << HW_RTC_MODE1_CTRLA_MODE_Pos)
#define HW_RTC_MODE1_CTRLA_MODE_COUNT16 (HW_RTC_MODE1_CTRLA_MODE_COUNT16_Val << HW_RTC_MODE1_CTRLA_MODE_Pos)
#define HW_RTC_MODE1_CTRLA_MODE_CLOCK  (HW_RTC_MODE1_CTRLA_MODE_CLOCK_Val << HW_RTC_MODE1_CTRLA_MODE_Pos)
#define HW_RTC_MODE1_CTRLA_PRESCALER_Pos 8            /**< \brief (HW_RTC_MODE1_CTRLA) Prescaler */
#define HW_RTC_MODE1_CTRLA_PRESCALER_Msk (_U_(0xF) << HW_RTC_MODE1_CTRLA_PRESCALER_Pos)
#define HW_RTC_MODE1_CTRLA_PRESCALER(value) (HW_RTC_MODE1_CTRLA_PRESCALER_Msk & ((value) << HW_RTC_MODE1_CTRLA_PRESCALER_Pos))
#define   HW_RTC_MODE1_CTRLA_PRESCALER_OFF_Val _U_(0x0)   /**< \brief (HW_RTC_MODE1_CTRLA) CLK_HW_RTC_CNT = GCLK_RTC/1 */
#define   HW_RTC_MODE1_CTRLA_PRESCALER_DIV1_Val _U_(0x1)   /**< \brief (HW_RTC_MODE1_CTRLA) CLK_HW_RTC_CNT = GCLK_RTC/1 */
#define   HW_RTC_MODE1_CTRLA_PRESCALER_DIV2_Val _U_(0x2)   /**< \brief (HW_RTC_MODE1_CTRLA) CLK_HW_RTC_CNT = GCLK_RTC/2 */
#define   HW_RTC_MODE1_CTRLA_PRESCALER_DIV4_Val _U_(0x3)   /**< \brief (HW_RTC_MODE1_CTRLA) CLK_HW_RTC_CNT = GCLK_RTC/4 */
#define   HW_RTC_MODE1_CTRLA_PRESCALER_DIV8_Val _U_(0x4)   /**< \brief (HW_RTC_MODE1_CTRLA) CLK_HW_RTC_CNT = GCLK_RTC/8 */
#define   HW_RTC_MODE1_CTRLA_PRESCALER_DIV16_Val _U_(0x5)   /**< \brief (HW_RTC_MODE1_CTRLA) CLK_HW_RTC_CNT = GCLK_RTC/16 */
#define   HW_RTC_MODE1_CTRLA_PRESCALER_DIV32_Val _U_(0x6)   /**< \brief (HW_RTC_MODE1_CTRLA) CLK_HW_RTC_CNT = GCLK_RTC/32 */
#define   HW_RTC_MODE1_CTRLA_PRESCALER_DIV64_Val _U_(0x7)   /**< \brief (HW_RTC_MODE1_CTRLA) CLK_HW_RTC_CNT = GCLK_RTC/64 */
#define   HW_RTC_MODE1_CTRLA_PRESCALER_DIV128_Val _U_(0x8)   /**< \brief (HW_RTC_MODE1_CTRLA) CLK_HW_RTC_CNT = GCLK_RTC/128 */
#define   HW_RTC_MODE1_CTRLA_PRESCALER_DIV256_Val _U_(0x9)   /**< \brief (HW_RTC_MODE1_CTRLA) CLK_HW_RTC_CNT = GCLK_RTC/256 */
#define   HW_RTC_MODE1_CTRLA_PRESCALER_DIV512_Val _U_(0xA)   /**< \brief (HW_RTC_MODE1_CTRLA) CLK_HW_RTC_CNT = GCLK_RTC/512 */
#define   HW_RTC_MODE1_CTRLA_PRESCALER_DIV1024_Val _U_(0xB)   /**< \brief (HW_RTC_MODE1_CTRLA) CLK_HW_RTC_CNT = GCLK_RTC/1024 */
#define HW_RTC_MODE1_CTRLA_PRESCALER_OFF (HW_RTC_MODE1_CTRLA_PRESCALER_OFF_Val << HW_RTC_MODE1_CTRLA_PRESCALER_Pos)
#define HW_RTC_MODE1_CTRLA_PRESCALER_DIV1 (HW_RTC_MODE1_CTRLA_PRESCALER_DIV1_Val << HW_RTC_MODE1_CTRLA_PRESCALER_Pos)
#define HW_RTC_MODE1_CTRLA_PRESCALER_DIV2 (HW_RTC_MODE1_CTRLA_PRESCALER_DIV2_Val << HW_RTC_MODE1_CTRLA_PRESCALER_Pos)
#define HW_RTC_MODE1_CTRLA_PRESCALER_DIV4 (HW_RTC_MODE1_CTRLA_PRESCALER_DIV4_Val << HW_RTC_MODE1_CTRLA_PRESCALER_Pos)
#define HW_RTC_MODE1_CTRLA_PRESCALER_DIV8 (HW_RTC_MODE1_CTRLA_PRESCALER_DIV8_Val << HW_RTC_MODE1_CTRLA_PRESCALER_Pos)
#define HW_RTC_MODE1_CTRLA_PRESCALER_DIV16 (HW_RTC_MODE1_CTRLA_PRESCALER_DIV16_Val << HW_RTC_MODE1_CTRLA_PRESCALER_Pos)
#define HW_RTC_MODE1_CTRLA_PRESCALER_DIV32 (HW_RTC_MODE1_CTRLA_PRESCALER_DIV32_Val << HW_RTC_MODE1_CTRLA_PRESCALER_Pos)
#define HW_RTC_MODE1_CTRLA_PRESCALER_DIV64 (HW_RTC_MODE1_CTRLA_PRESCALER_DIV64_Val << HW_RTC_MODE1_CTRLA_PRESCALER_Pos)
#define HW_RTC_MODE1_CTRLA_PRESCALER_DIV128 (HW_RTC_MODE1_CTRLA_PRESCALER_DIV128_Val << HW_RTC_MODE1_CTRLA_PRESCALER_Pos)
#define HW_RTC_MODE1_CTRLA_PRESCALER_DIV256 (HW_RTC_MODE1_CTRLA_PRESCALER_DIV256_Val << HW_RTC_MODE1_CTRLA_PRESCALER_Pos)
#define HW_RTC_MODE1_CTRLA_PRESCALER_DIV512 (HW_RTC_MODE1_CTRLA_PRESCALER_DIV512_Val << HW_RTC_MODE1_CTRLA_PRESCALER_Pos)
#define HW_RTC_MODE1_CTRLA_PRESCALER_DIV1024 (HW_RTC_MODE1_CTRLA_PRESCALER_DIV1024_Val << HW_RTC_MODE1_CTRLA_PRESCALER_Pos)
#define HW_RTC_MODE1_CTRLA_COUNTSYNC_Pos 15           /**< \brief (HW_RTC_MODE1_CTRLA) Count Read Synchronization Enable */
#define HW_RTC_MODE1_CTRLA_COUNTSYNC   (_U_(0x1) << HW_RTC_MODE1_CTRLA_COUNTSYNC_Pos)
#define HW_RTC_MODE1_CTRLA_MASK        _U_(0x8F0F)  /**< \brief (HW_RTC_MODE1_CTRLA) MASK Register */

/* -------- HW_RTC_MODE2_CTRLA : (RTC Offset: 0x00) (R/W 16) MODE2 MODE2 Control A -------- */
typedef union {
  struct {
    uint16_t SWRST:1;          /*!< bit:      0  Software Reset                     */
    uint16_t ENABLE:1;         /*!< bit:      1  Enable                             */
    uint16_t MODE:2;           /*!< bit:  2.. 3  Operating Mode                     */
    uint16_t :2;               /*!< bit:  4.. 5  Reserved                           */
    uint16_t CLKREP:1;         /*!< bit:      6  Clock Representation               */
    uint16_t MATCHCLR:1;       /*!< bit:      7  Clear on Match                     */
    uint16_t PRESCALER:4;      /*!< bit:  8..11  Prescaler                          */
    uint16_t :3;               /*!< bit: 12..14  Reserved                           */
    uint16_t CLOCKSYNC:1;      /*!< bit:     15  Clock Read Synchronization Enable  */
  } bit;                       /*!< Structure used for bit  access                  */
  uint16_t reg;                /*!< Type      used for register access              */
} HW_RTC_MODE2_CTRLA_Type;

#define HW_RTC_MODE2_CTRLA_OFFSET      0x00         /**< \brief (HW_RTC_MODE2_CTRLA offset) MODE2 Control A */
#define HW_RTC_MODE2_CTRLA_RESETVALUE  _U_(0x0000)  /**< \brief (HW_RTC_MODE2_CTRLA reset_value) MODE2 Control A */

#define HW_RTC_MODE2_CTRLA_SWRST_Pos   0            /**< \brief (HW_RTC_MODE2_CTRLA) Software Reset */
#define HW_RTC_MODE2_CTRLA_SWRST       (_U_(0x1) << HW_RTC_MODE2_CTRLA_SWRST_Pos)
#define HW_RTC_MODE2_CTRLA_ENABLE_Pos  1            /**< \brief (HW_RTC_MODE2_CTRLA) Enable */
#define HW_RTC_MODE2_CTRLA_ENABLE      (_U_(0x1) << HW_RTC_MODE2_CTRLA_ENABLE_Pos)
#define HW_RTC_MODE2_CTRLA_MODE_Pos    2            /**< \brief (HW_RTC_MODE2_CTRLA) Operating Mode */
#define HW_RTC_MODE2_CTRLA_MODE_Msk    (_U_(0x3) << HW_RTC_MODE2_CTRLA_MODE_Pos)
#define HW_RTC_MODE2_CTRLA_MODE(value) (HW_RTC_MODE2_CTRLA_MODE_Msk & ((value) << HW_RTC_MODE2_CTRLA_MODE_Pos))
#define   HW_RTC_MODE2_CTRLA_MODE_COUNT32_Val _U_(0x0)   /**< \brief (HW_RTC_MODE2_CTRLA) Mode 0: 32-bit Counter */
#define   HW_RTC_MODE2_CTRLA_MODE_COUNT16_Val _U_(0x1)   /**< \brief (HW_RTC_MODE2_CTRLA) Mode 1: 16-bit Counter */
#define   HW_RTC_MODE2_CTRLA_MODE_CLOCK_Val  _U_(0x2)   /**< \brief (HW_RTC_MODE2_CTRLA) Mode 2: Clock/Calendar */
#define HW_RTC_MODE2_CTRLA_MODE_COUNT32 (HW_RTC_MODE2_CTRLA_MODE_COUNT32_Val << HW_RTC_MODE2_CTRLA_MODE_Pos)
#define HW_RTC_MODE2_CTRLA_MODE_COUNT16 (HW_RTC_MODE2_CTRLA_MODE_COUNT16_Val << HW_RTC_MODE2_CTRLA_MODE_Pos)
#define HW_RTC_MODE2_CTRLA_MODE_CLOCK  (HW_RTC_MODE2_CTRLA_MODE_CLOCK_Val << HW_RTC_MODE2_CTRLA_MODE_Pos)
#define HW_RTC_MODE2_CTRLA_CLKREP_Pos  6            /**< \brief (HW_RTC_MODE2_CTRLA) Clock Representation */
#define HW_RTC_MODE2_CTRLA_CLKREP      (_U_(0x1) << HW_RTC_MODE2_CTRLA_CLKREP_Pos)
#define HW_RTC_MODE2_CTRLA_MATCHCLR_Pos 7            /**< \brief (HW_RTC_MODE2_CTRLA) Clear on Match */
#define HW_RTC_MODE2_CTRLA_MATCHCLR    (_U_(0x1) << HW_RTC_MODE2_CTRLA_MATCHCLR_Pos)
#define HW_RTC_MODE2_CTRLA_PRESCALER_Pos 8            /**< \brief (HW_RTC_MODE2_CTRLA) Prescaler */
#define HW_RTC_MODE2_CTRLA_PRESCALER_Msk (_U_(0xF) << HW_RTC_MODE2_CTRLA_PRESCALER_Pos)
#define HW_RTC_MODE2_CTRLA_PRESCALER(value) (HW_RTC_MODE2_CTRLA_PRESCALER_Msk & ((value) << HW_RTC_MODE2_CTRLA_PRESCALER_Pos))
#define   HW_RTC_MODE2_CTRLA_PRESCALER_OFF_Val _U_(0x0)   /**< \brief (HW_RTC_MODE2_CTRLA) CLK_HW_RTC_CNT = GCLK_RTC/1 */
#define   HW_RTC_MODE2_CTRLA_PRESCALER_DIV1_Val _U_(0x1)   /**< \brief (HW_RTC_MODE2_CTRLA) CLK_HW_RTC_CNT = GCLK_RTC/1 */
#define   HW_RTC_MODE2_CTRLA_PRESCALER_DIV2_Val _U_(0x2)   /**< \brief (HW_RTC_MODE2_CTRLA) CLK_HW_RTC_CNT = GCLK_RTC/2 */
#define   HW_RTC_MODE2_CTRLA_PRESCALER_DIV4_Val _U_(0x3)   /**< \brief (HW_RTC_MODE2_CTRLA) CLK_HW_RTC_CNT = GCLK_RTC/4 */
#define   HW_RTC_MODE2_CTRLA_PRESCALER_DIV8_Val _U_(0x4)   /**< \brief (HW_RTC_MODE2_CTRLA) CLK_HW_RTC_CNT = GCLK_RTC/8 */
#define   HW_RTC_MODE2_CTRLA_PRESCALER_DIV16_Val _U_(0x5)   /**< \brief (HW_RTC_MODE2_CTRLA) CLK_HW_RTC_CNT = GCLK_RTC/16 */
#define   HW_RTC_MODE2_CTRLA_PRESCALER_DIV32_Val _U_(0x6)   /**< \brief (HW_RTC_MODE2_CTRLA) CLK_HW_RTC_CNT = GCLK_RTC/32 */
#define   HW_RTC_MODE2_CTRLA_PRESCALER_DIV64_Val _U_(0x7)   /**< \brief (HW_RTC_MODE2_CTRLA) CLK_HW_RTC_CNT = GCLK_RTC/64 */
#define   HW_RTC_MODE2_CTRLA_PRESCALER_DIV128_Val _U_(0x8)   /**< \brief (HW_RTC_MODE2_CTRLA) CLK_HW_RTC_CNT = GCLK_RTC/128 */
#define   HW_RTC_MODE2_CTRLA_PRESCALER_DIV256_Val _U_(0x9)   /**< \brief (HW_RTC_MODE2_CTRLA) CLK_HW_RTC_CNT = GCLK_RTC/256 */
#define   HW_RTC_MODE2_CTRLA_PRESCALER_DIV512_Val _U_(0xA)   /**< \brief (HW_RTC_MODE2_CTRLA) CLK_HW_RTC_CNT = GCLK_RTC/512 */
#define   HW_RTC_MODE2_CTRLA_PRESCALER_DIV1024_Val _U_(0xB)   /**< \brief (HW_RTC_MODE2_CTRLA) CLK_HW_RTC_CNT = GCLK_RTC/1024 */
#define HW_RTC_MODE2_CTRLA_PRESCALER_OFF (HW_RTC_MODE2_CTRLA_PRESCALER_OFF_Val << HW_RTC_MODE2_CTRLA_PRESCALER_Pos)
#define HW_RTC_MODE2_CTRLA_PRESCALER_DIV1 (HW_RTC_MODE2_CTRLA_PRESCALER_DIV1_Val << HW_RTC_MODE2_CTRLA_PRESCALER_Pos)
#define HW_RTC_MODE2_CTRLA_PRESCALER_DIV2 (HW_RTC_MODE2_CTRLA_PRESCALER_DIV2_Val << HW_RTC_MODE2_CTRLA_PRESCALER_Pos)
#define HW_RTC_MODE2_CTRLA_PRESCALER_DIV4 (HW_RTC_MODE2_CTRLA_PRESCALER_DIV4_Val << HW_RTC_MODE2_CTRLA_PRESCALER_Pos)
#define HW_RTC_MODE2_CTRLA_PRESCALER_DIV8 (HW_RTC_MODE2_CTRLA_PRESCALER_DIV8_Val << HW_RTC_MODE2_CTRLA_PRESCALER_Pos)
#define HW_RTC_MODE2_CTRLA_PRESCALER_DIV16 (HW_RTC_MODE2_CTRLA_PRESCALER_DIV16_Val << HW_RTC_MODE2_CTRLA_PRESCALER_Pos)
#define HW_RTC_MODE2_CTRLA_PRESCALER_DIV32 (HW_RTC_MODE2_CTRLA_PRESCALER_DIV32_Val << HW_RTC_MODE2_CTRLA_PRESCALER_Pos)
#define HW_RTC_MODE2_CTRLA_PRESCALER_DIV64 (HW_RTC_MODE2_CTRLA_PRESCALER_DIV64_Val << HW_RTC_MODE2_CTRLA_PRESCALER_Pos)
#define HW_RTC_MODE2_CTRLA_PRESCALER_DIV128 (HW_RTC_MODE2_CTRLA_PRESCALER_DIV128_Val << HW_RTC_MODE2_CTRLA_PRESCALER_Pos)
#define HW_RTC_MODE2_CTRLA_PRESCALER_DIV256 (HW_RTC_MODE2_CTRLA_PRESCALER_DIV256_Val << HW_RTC_MODE2_CTRLA_PRESCALER_Pos)
#define HW_RTC_MODE2_CTRLA_PRESCALER_DIV512 (HW_RTC_MODE2_CTRLA_PRESCALER_DIV512_Val << HW_RTC_MODE2_CTRLA_PRESCALER_Pos)
#define HW_RTC_MODE2_CTRLA_PRESCALER_DIV1024 (HW_RTC_MODE2_CTRLA_PRESCALER_DIV1024_Val << HW_RTC_MODE2_CTRLA_PRESCALER_Pos)
#define HW_RTC_MODE2_CTRLA_CLOCKSYNC_Pos 15           /**< \brief (HW_RTC_MODE2_CTRLA) Clock Read Synchronization Enable */
#define HW_RTC_MODE2_CTRLA_CLOCKSYNC   (_U_(0x1) << HW_RTC_MODE2_CTRLA_CLOCKSYNC_Pos)
#define HW_RTC_MODE2_CTRLA_MASK        _U_(0x8FCF)  /**< \brief (HW_RTC_MODE2_CTRLA) MASK Register */

/* -------- HW_RTC_MODE0_EVCTRL : (RTC Offset: 0x04) (R/W 32) MODE0 MODE0 Event Control -------- */
typedef union {
  struct {
    uint32_t PEREO0:1;         /*!< bit:      0  Periodic Interval 0 Event Output Enable */
    uint32_t PEREO1:1;         /*!< bit:      1  Periodic Interval 1 Event Output Enable */
    uint32_t PEREO2:1;         /*!< bit:      2  Periodic Interval 2 Event Output Enable */
    uint32_t PEREO3:1;         /*!< bit:      3  Periodic Interval 3 Event Output Enable */
    uint32_t PEREO4:1;         /*!< bit:      4  Periodic Interval 4 Event Output Enable */
    uint32_t PEREO5:1;         /*!< bit:      5  Periodic Interval 5 Event Output Enable */
    uint32_t PEREO6:1;         /*!< bit:      6  Periodic Interval 6 Event Output Enable */
    uint32_t PEREO7:1;         /*!< bit:      7  Periodic Interval 7 Event Output Enable */
    uint32_t CMPEO0:1;         /*!< bit:      8  Compare 0 Event Output Enable      */
    uint32_t :6;               /*!< bit:  9..14  Reserved                           */
    uint32_t OVFEO:1;          /*!< bit:     15  Overflow Event Output Enable       */
    uint32_t :16;              /*!< bit: 16..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  struct {
    uint32_t PEREO:8;          /*!< bit:  0.. 7  Periodic Interval x Event Output Enable */
    uint32_t CMPEO:1;          /*!< bit:      8  Compare x Event Output Enable      */
    uint32_t :23;              /*!< bit:  9..31  Reserved                           */
  } vec;                       /*!< Structure used for vec  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} HW_RTC_MODE0_EVCTRL_Type;

#define HW_RTC_MODE0_EVCTRL_OFFSET     0x04         /**< \brief (HW_RTC_MODE0_EVCTRL offset) MODE0 Event Control */
#define HW_RTC_MODE0_EVCTRL_RESETVALUE _U_(0x00000000) /**< \brief (HW_RTC_MODE0_EVCTRL reset_value) MODE0 Event Control */

#define HW_RTC_MODE0_EVCTRL_PEREO0_Pos 0            /**< \brief (HW_RTC_MODE0_EVCTRL) Periodic Interval 0 Event Output Enable */
#define HW_RTC_MODE0_EVCTRL_PEREO0     (_U_(1) << HW_RTC_MODE0_EVCTRL_PEREO0_Pos)
#define HW_RTC_MODE0_EVCTRL_PEREO1_Pos 1            /**< \brief (HW_RTC_MODE0_EVCTRL) Periodic Interval 1 Event Output Enable */
#define HW_RTC_MODE0_EVCTRL_PEREO1     (_U_(1) << HW_RTC_MODE0_EVCTRL_PEREO1_Pos)
#define HW_RTC_MODE0_EVCTRL_PEREO2_Pos 2            /**< \brief (HW_RTC_MODE0_EVCTRL) Periodic Interval 2 Event Output Enable */
#define HW_RTC_MODE0_EVCTRL_PEREO2     (_U_(1) << HW_RTC_MODE0_EVCTRL_PEREO2_Pos)
#define HW_RTC_MODE0_EVCTRL_PEREO3_Pos 3            /**< \brief (HW_RTC_MODE0_EVCTRL) Periodic Interval 3 Event Output Enable */
#define HW_RTC_MODE0_EVCTRL_PEREO3     (_U_(1) << HW_RTC_MODE0_EVCTRL_PEREO3_Pos)
#define HW_RTC_MODE0_EVCTRL_PEREO4_Pos 4            /**< \brief (HW_RTC_MODE0_EVCTRL) Periodic Interval 4 Event Output Enable */
#define HW_RTC_MODE0_EVCTRL_PEREO4     (_U_(1) << HW_RTC_MODE0_EVCTRL_PEREO4_Pos)
#define HW_RTC_MODE0_EVCTRL_PEREO5_Pos 5            /**< \brief (HW_RTC_MODE0_EVCTRL) Periodic Interval 5 Event Output Enable */
#define HW_RTC_MODE0_EVCTRL_PEREO5     (_U_(1) << HW_RTC_MODE0_EVCTRL_PEREO5_Pos)
#define HW_RTC_MODE0_EVCTRL_PEREO6_Pos 6            /**< \brief (HW_RTC_MODE0_EVCTRL) Periodic Interval 6 Event Output Enable */
#define HW_RTC_MODE0_EVCTRL_PEREO6     (_U_(1) << HW_RTC_MODE0_EVCTRL_PEREO6_Pos)
#define HW_RTC_MODE0_EVCTRL_PEREO7_Pos 7            /**< \brief (HW_RTC_MODE0_EVCTRL) Periodic Interval 7 Event Output Enable */
#define HW_RTC_MODE0_EVCTRL_PEREO7     (_U_(1) << HW_RTC_MODE0_EVCTRL_PEREO7_Pos)
#define HW_RTC_MODE0_EVCTRL_PEREO_Pos  0            /**< \brief (HW_RTC_MODE0_EVCTRL) Periodic Interval x Event Output Enable */
#define HW_RTC_MODE0_EVCTRL_PEREO_Msk  (_U_(0xFF) << HW_RTC_MODE0_EVCTRL_PEREO_Pos)
#define HW_RTC_MODE0_EVCTRL_PEREO(value) (HW_RTC_MODE0_EVCTRL_PEREO_Msk & ((value) << HW_RTC_MODE0_EVCTRL_PEREO_Pos))
#define HW_RTC_MODE0_EVCTRL_CMPEO0_Pos 8            /**< \brief (HW_RTC_MODE0_EVCTRL) Compare 0 Event Output Enable */
#define HW_RTC_MODE0_EVCTRL_CMPEO0     (_U_(1) << HW_RTC_MODE0_EVCTRL_CMPEO0_Pos)
#define HW_RTC_MODE0_EVCTRL_CMPEO_Pos  8            /**< \brief (HW_RTC_MODE0_EVCTRL) Compare x Event Output Enable */
#define HW_RTC_MODE0_EVCTRL_CMPEO_Msk  (_U_(0x1) << HW_RTC_MODE0_EVCTRL_CMPEO_Pos)
#define HW_RTC_MODE0_EVCTRL_CMPEO(value) (HW_RTC_MODE0_EVCTRL_CMPEO_Msk & ((value) << HW_RTC_MODE0_EVCTRL_CMPEO_Pos))
#define HW_RTC_MODE0_EVCTRL_OVFEO_Pos  15           /**< \brief (HW_RTC_MODE0_EVCTRL) Overflow Event Output Enable */
#define HW_RTC_MODE0_EVCTRL_OVFEO      (_U_(0x1) << HW_RTC_MODE0_EVCTRL_OVFEO_Pos)
#define HW_RTC_MODE0_EVCTRL_MASK       _U_(0x000081FF) /**< \brief (HW_RTC_MODE0_EVCTRL) MASK Register */

/* -------- HW_RTC_MODE1_EVCTRL : (RTC Offset: 0x04) (R/W 32) MODE1 MODE1 Event Control -------- */
typedef union {
  struct {
    uint32_t PEREO0:1;         /*!< bit:      0  Periodic Interval 0 Event Output Enable */
    uint32_t PEREO1:1;         /*!< bit:      1  Periodic Interval 1 Event Output Enable */
    uint32_t PEREO2:1;         /*!< bit:      2  Periodic Interval 2 Event Output Enable */
    uint32_t PEREO3:1;         /*!< bit:      3  Periodic Interval 3 Event Output Enable */
    uint32_t PEREO4:1;         /*!< bit:      4  Periodic Interval 4 Event Output Enable */
    uint32_t PEREO5:1;         /*!< bit:      5  Periodic Interval 5 Event Output Enable */
    uint32_t PEREO6:1;         /*!< bit:      6  Periodic Interval 6 Event Output Enable */
    uint32_t PEREO7:1;         /*!< bit:      7  Periodic Interval 7 Event Output Enable */
    uint32_t CMPEO0:1;         /*!< bit:      8  Compare 0 Event Output Enable      */
    uint32_t CMPEO1:1;         /*!< bit:      9  Compare 1 Event Output Enable      */
    uint32_t :5;               /*!< bit: 10..14  Reserved                           */
    uint32_t OVFEO:1;          /*!< bit:     15  Overflow Event Output Enable       */
    uint32_t :16;              /*!< bit: 16..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  struct {
    uint32_t PEREO:8;          /*!< bit:  0.. 7  Periodic Interval x Event Output Enable */
    uint32_t CMPEO:2;          /*!< bit:  8.. 9  Compare x Event Output Enable      */
    uint32_t :22;              /*!< bit: 10..31  Reserved                           */
  } vec;                       /*!< Structure used for vec  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} HW_RTC_MODE1_EVCTRL_Type;

#define HW_RTC_MODE1_EVCTRL_OFFSET     0x04         /**< \brief (HW_RTC_MODE1_EVCTRL offset) MODE1 Event Control */
#define HW_RTC_MODE1_EVCTRL_RESETVALUE _U_(0x00000000) /**< \brief (HW_RTC_MODE1_EVCTRL reset_value) MODE1 Event Control */

#define HW_RTC_MODE1_EVCTRL_PEREO0_Pos 0            /**< \brief (HW_RTC_MODE1_EVCTRL) Periodic Interval 0 Event Output Enable */
#define HW_RTC_MODE1_EVCTRL_PEREO0     (_U_(1) << HW_RTC_MODE1_EVCTRL_PEREO0_Pos)
#define HW_RTC_MODE1_EVCTRL_PEREO1_Pos 1            /**< \brief (HW_RTC_MODE1_EVCTRL) Periodic Interval 1 Event Output Enable */
#define HW_RTC_MODE1_EVCTRL_PEREO1     (_U_(1) << HW_RTC_MODE1_EVCTRL_PEREO1_Pos)
#define HW_RTC_MODE1_EVCTRL_PEREO2_Pos 2            /**< \brief (HW_RTC_MODE1_EVCTRL) Periodic Interval 2 Event Output Enable */
#define HW_RTC_MODE1_EVCTRL_PEREO2     (_U_(1) << HW_RTC_MODE1_EVCTRL_PEREO2_Pos)
#define HW_RTC_MODE1_EVCTRL_PEREO3_Pos 3            /**< \brief (HW_RTC_MODE1_EVCTRL) Periodic Interval 3 Event Output Enable */
#define HW_RTC_MODE1_EVCTRL_PEREO3     (_U_(1) << HW_RTC_MODE1_EVCTRL_PEREO3_Pos)
#define HW_RTC_MODE1_EVCTRL_PEREO4_Pos 4            /**< \brief (HW_RTC_MODE1_EVCTRL) Periodic Interval 4 Event Output Enable */
#define HW_RTC_MODE1_EVCTRL_PEREO4     (_U_(1) << HW_RTC_MODE1_EVCTRL_PEREO4_Pos)
#define HW_RTC_MODE1_EVCTRL_PEREO5_Pos 5            /**< \brief (HW_RTC_MODE1_EVCTRL) Periodic Interval 5 Event Output Enable */
#define HW_RTC_MODE1_EVCTRL_PEREO5     (_U_(1) << HW_RTC_MODE1_EVCTRL_PEREO5_Pos)
#define HW_RTC_MODE1_EVCTRL_PEREO6_Pos 6            /**< \brief (HW_RTC_MODE1_EVCTRL) Periodic Interval 6 Event Output Enable */
#define HW_RTC_MODE1_EVCTRL_PEREO6     (_U_(1) << HW_RTC_MODE1_EVCTRL_PEREO6_Pos)
#define HW_RTC_MODE1_EVCTRL_PEREO7_Pos 7            /**< \brief (HW_RTC_MODE1_EVCTRL) Periodic Interval 7 Event Output Enable */
#define HW_RTC_MODE1_EVCTRL_PEREO7     (_U_(1) << HW_RTC_MODE1_EVCTRL_PEREO7_Pos)
#define HW_RTC_MODE1_EVCTRL_PEREO_Pos  0            /**< \brief (HW_RTC_MODE1_EVCTRL) Periodic Interval x Event Output Enable */
#define HW_RTC_MODE1_EVCTRL_PEREO_Msk  (_U_(0xFF) << HW_RTC_MODE1_EVCTRL_PEREO_Pos)
#define HW_RTC_MODE1_EVCTRL_PEREO(value) (HW_RTC_MODE1_EVCTRL_PEREO_Msk & ((value) << HW_RTC_MODE1_EVCTRL_PEREO_Pos))
#define HW_RTC_MODE1_EVCTRL_CMPEO0_Pos 8            /**< \brief (HW_RTC_MODE1_EVCTRL) Compare 0 Event Output Enable */
#define HW_RTC_MODE1_EVCTRL_CMPEO0     (_U_(1) << HW_RTC_MODE1_EVCTRL_CMPEO0_Pos)
#define HW_RTC_MODE1_EVCTRL_CMPEO1_Pos 9            /**< \brief (HW_RTC_MODE1_EVCTRL) Compare 1 Event Output Enable */
#define HW_RTC_MODE1_EVCTRL_CMPEO1     (_U_(1) << HW_RTC_MODE1_EVCTRL_CMPEO1_Pos)
#define HW_RTC_MODE1_EVCTRL_CMPEO_Pos  8            /**< \brief (HW_RTC_MODE1_EVCTRL) Compare x Event Output Enable */
#define HW_RTC_MODE1_EVCTRL_CMPEO_Msk  (_U_(0x3) << HW_RTC_MODE1_EVCTRL_CMPEO_Pos)
#define HW_RTC_MODE1_EVCTRL_CMPEO(value) (HW_RTC_MODE1_EVCTRL_CMPEO_Msk & ((value) << HW_RTC_MODE1_EVCTRL_CMPEO_Pos))
#define HW_RTC_MODE1_EVCTRL_OVFEO_Pos  15           /**< \brief (HW_RTC_MODE1_EVCTRL) Overflow Event Output Enable */
#define HW_RTC_MODE1_EVCTRL_OVFEO      (_U_(0x1) << HW_RTC_MODE1_EVCTRL_OVFEO_Pos)
#define HW_RTC_MODE1_EVCTRL_MASK       _U_(0x000083FF) /**< \brief (HW_RTC_MODE1_EVCTRL) MASK Register */

/* -------- HW_RTC_MODE2_EVCTRL : (RTC Offset: 0x04) (R/W 32) MODE2 MODE2 Event Control -------- */
typedef union {
  struct {
    uint32_t PEREO0:1;         /*!< bit:      0  Periodic Interval 0 Event Output Enable */
    uint32_t PEREO1:1;         /*!< bit:      1  Periodic Interval 1 Event Output Enable */
    uint32_t PEREO2:1;         /*!< bit:      2  Periodic Interval 2 Event Output Enable */
    uint32_t PEREO3:1;         /*!< bit:      3  Periodic Interval 3 Event Output Enable */
    uint32_t PEREO4:1;         /*!< bit:      4  Periodic Interval 4 Event Output Enable */
    uint32_t PEREO5:1;         /*!< bit:      5  Periodic Interval 5 Event Output Enable */
    uint32_t PEREO6:1;         /*!< bit:      6  Periodic Interval 6 Event Output Enable */
    uint32_t PEREO7:1;         /*!< bit:      7  Periodic Interval 7 Event Output Enable */
    uint32_t ALARMEO0:1;       /*!< bit:      8  Alarm 0 Event Output Enable        */
    uint32_t :6;               /*!< bit:  9..14  Reserved                           */
    uint32_t OVFEO:1;          /*!< bit:     15  Overflow Event Output Enable       */
    uint32_t :16;              /*!< bit: 16..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  struct {
    uint32_t PEREO:8;          /*!< bit:  0.. 7  Periodic Interval x Event Output Enable */
    uint32_t ALARMEO:1;        /*!< bit:      8  Alarm x Event Output Enable        */
    uint32_t :23;              /*!< bit:  9..31  Reserved                           */
  } vec;                       /*!< Structure used for vec  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} HW_RTC_MODE2_EVCTRL_Type;

#define HW_RTC_MODE2_EVCTRL_OFFSET     0x04         /**< \brief (HW_RTC_MODE2_EVCTRL offset) MODE2 Event Control */
#define HW_RTC_MODE2_EVCTRL_RESETVALUE _U_(0x00000000) /**< \brief (HW_RTC_MODE2_EVCTRL reset_value) MODE2 Event Control */

#define HW_RTC_MODE2_EVCTRL_PEREO0_Pos 0            /**< \brief (HW_RTC_MODE2_EVCTRL) Periodic Interval 0 Event Output Enable */
#define HW_RTC_MODE2_EVCTRL_PEREO0     (_U_(1) << HW_RTC_MODE2_EVCTRL_PEREO0_Pos)
#define HW_RTC_MODE2_EVCTRL_PEREO1_Pos 1            /**< \brief (HW_RTC_MODE2_EVCTRL) Periodic Interval 1 Event Output Enable */
#define HW_RTC_MODE2_EVCTRL_PEREO1     (_U_(1) << HW_RTC_MODE2_EVCTRL_PEREO1_Pos)
#define HW_RTC_MODE2_EVCTRL_PEREO2_Pos 2            /**< \brief (HW_RTC_MODE2_EVCTRL) Periodic Interval 2 Event Output Enable */
#define HW_RTC_MODE2_EVCTRL_PEREO2     (_U_(1) << HW_RTC_MODE2_EVCTRL_PEREO2_Pos)
#define HW_RTC_MODE2_EVCTRL_PEREO3_Pos 3            /**< \brief (HW_RTC_MODE2_EVCTRL) Periodic Interval 3 Event Output Enable */
#define HW_RTC_MODE2_EVCTRL_PEREO3     (_U_(1) << HW_RTC_MODE2_EVCTRL_PEREO3_Pos)
#define HW_RTC_MODE2_EVCTRL_PEREO4_Pos 4            /**< \brief (HW_RTC_MODE2_EVCTRL) Periodic Interval 4 Event Output Enable */
#define HW_RTC_MODE2_EVCTRL_PEREO4     (_U_(1) << HW_RTC_MODE2_EVCTRL_PEREO4_Pos)
#define HW_RTC_MODE2_EVCTRL_PEREO5_Pos 5            /**< \brief (HW_RTC_MODE2_EVCTRL) Periodic Interval 5 Event Output Enable */
#define HW_RTC_MODE2_EVCTRL_PEREO5     (_U_(1) << HW_RTC_MODE2_EVCTRL_PEREO5_Pos)
#define HW_RTC_MODE2_EVCTRL_PEREO6_Pos 6            /**< \brief (HW_RTC_MODE2_EVCTRL) Periodic Interval 6 Event Output Enable */
#define HW_RTC_MODE2_EVCTRL_PEREO6     (_U_(1) << HW_RTC_MODE2_EVCTRL_PEREO6_Pos)
#define HW_RTC_MODE2_EVCTRL_PEREO7_Pos 7            /**< \brief (HW_RTC_MODE2_EVCTRL) Periodic Interval 7 Event Output Enable */
#define HW_RTC_MODE2_EVCTRL_PEREO7     (_U_(1) << HW_RTC_MODE2_EVCTRL_PEREO7_Pos)
#define HW_RTC_MODE2_EVCTRL_PEREO_Pos  0            /**< \brief (HW_RTC_MODE2_EVCTRL) Periodic Interval x Event Output Enable */
#define HW_RTC_MODE2_EVCTRL_PEREO_Msk  (_U_(0xFF) << HW_RTC_MODE2_EVCTRL_PEREO_Pos)
#define HW_RTC_MODE2_EVCTRL_PEREO(value) (HW_RTC_MODE2_EVCTRL_PEREO_Msk & ((value) << HW_RTC_MODE2_EVCTRL_PEREO_Pos))
#define HW_RTC_MODE2_EVCTRL_ALARMEO0_Pos 8            /**< \brief (HW_RTC_MODE2_EVCTRL) Alarm 0 Event Output Enable */
#define HW_RTC_MODE2_EVCTRL_ALARMEO0   (_U_(1) << HW_RTC_MODE2_EVCTRL_ALARMEO0_Pos)
#define HW_RTC_MODE2_EVCTRL_ALARMEO_Pos 8            /**< \brief (HW_RTC_MODE2_EVCTRL) Alarm x Event Output Enable */
#define HW_RTC_MODE2_EVCTRL_ALARMEO_Msk (_U_(0x1) << HW_RTC_MODE2_EVCTRL_ALARMEO_Pos)
#define HW_RTC_MODE2_EVCTRL_ALARMEO(value) (HW_RTC_MODE2_EVCTRL_ALARMEO_Msk & ((value) << HW_RTC_MODE2_EVCTRL_ALARMEO_Pos))
#define HW_RTC_MODE2_EVCTRL_OVFEO_Pos  15           /**< \brief (HW_RTC_MODE2_EVCTRL) Overflow Event Output Enable */
#define HW_RTC_MODE2_EVCTRL_OVFEO      (_U_(0x1) << HW_RTC_MODE2_EVCTRL_OVFEO_Pos)
#define HW_RTC_MODE2_EVCTRL_MASK       _U_(0x000081FF) /**< \brief (HW_RTC_MODE2_EVCTRL) MASK Register */

/* -------- HW_RTC_MODE0_INTENCLR : (RTC Offset: 0x08) (R/W 16) MODE0 MODE0 Interrupt Enable Clear -------- */
typedef union {
  struct {
    uint16_t PER0:1;           /*!< bit:      0  Periodic Interval 0 Interrupt Enable */
    uint16_t PER1:1;           /*!< bit:      1  Periodic Interval 1 Interrupt Enable */
    uint16_t PER2:1;           /*!< bit:      2  Periodic Interval 2 Interrupt Enable */
    uint16_t PER3:1;           /*!< bit:      3  Periodic Interval 3 Interrupt Enable */
    uint16_t PER4:1;           /*!< bit:      4  Periodic Interval 4 Interrupt Enable */
    uint16_t PER5:1;           /*!< bit:      5  Periodic Interval 5 Interrupt Enable */
    uint16_t PER6:1;           /*!< bit:      6  Periodic Interval 6 Interrupt Enable */
    uint16_t PER7:1;           /*!< bit:      7  Periodic Interval 7 Interrupt Enable */
    uint16_t CMP0:1;           /*!< bit:      8  Compare 0 Interrupt Enable         */
    uint16_t :6;               /*!< bit:  9..14  Reserved                           */
    uint16_t OVF:1;            /*!< bit:     15  Overflow Interrupt Enable          */
  } bit;                       /*!< Structure used for bit  access                  */
  struct {
    uint16_t PER:8;            /*!< bit:  0.. 7  Periodic Interval x Interrupt Enable */
    uint16_t CMP:1;            /*!< bit:      8  Compare x Interrupt Enable         */
    uint16_t :7;               /*!< bit:  9..15  Reserved                           */
  } vec;                       /*!< Structure used for vec  access                  */
  uint16_t reg;                /*!< Type      used for register access              */
} HW_RTC_MODE0_INTENCLR_Type;

#define HW_RTC_MODE0_INTENCLR_OFFSET   0x08         /**< \brief (HW_RTC_MODE0_INTENCLR offset) MODE0 Interrupt Enable Clear */
#define HW_RTC_MODE0_INTENCLR_RESETVALUE _U_(0x0000)  /**< \brief (HW_RTC_MODE0_INTENCLR reset_value) MODE0 Interrupt Enable Clear */

#define HW_RTC_MODE0_INTENCLR_PER0_Pos 0            /**< \brief (HW_RTC_MODE0_INTENCLR) Periodic Interval 0 Interrupt Enable */
#define HW_RTC_MODE0_INTENCLR_PER0     (_U_(1) << HW_RTC_MODE0_INTENCLR_PER0_Pos)
#define HW_RTC_MODE0_INTENCLR_PER1_Pos 1            /**< \brief (HW_RTC_MODE0_INTENCLR) Periodic Interval 1 Interrupt Enable */
#define HW_RTC_MODE0_INTENCLR_PER1     (_U_(1) << HW_RTC_MODE0_INTENCLR_PER1_Pos)
#define HW_RTC_MODE0_INTENCLR_PER2_Pos 2            /**< \brief (HW_RTC_MODE0_INTENCLR) Periodic Interval 2 Interrupt Enable */
#define HW_RTC_MODE0_INTENCLR_PER2     (_U_(1) << HW_RTC_MODE0_INTENCLR_PER2_Pos)
#define HW_RTC_MODE0_INTENCLR_PER3_Pos 3            /**< \brief (HW_RTC_MODE0_INTENCLR) Periodic Interval 3 Interrupt Enable */
#define HW_RTC_MODE0_INTENCLR_PER3     (_U_(1) << HW_RTC_MODE0_INTENCLR_PER3_Pos)
#define HW_RTC_MODE0_INTENCLR_PER4_Pos 4            /**< \brief (HW_RTC_MODE0_INTENCLR) Periodic Interval 4 Interrupt Enable */
#define HW_RTC_MODE0_INTENCLR_PER4     (_U_(1) << HW_RTC_MODE0_INTENCLR_PER4_Pos)
#define HW_RTC_MODE0_INTENCLR_PER5_Pos 5            /**< \brief (HW_RTC_MODE0_INTENCLR) Periodic Interval 5 Interrupt Enable */
#define HW_RTC_MODE0_INTENCLR_PER5     (_U_(1) << HW_RTC_MODE0_INTENCLR_PER5_Pos)
#define HW_RTC_MODE0_INTENCLR_PER6_Pos 6            /**< \brief (HW_RTC_MODE0_INTENCLR) Periodic Interval 6 Interrupt Enable */
#define HW_RTC_MODE0_INTENCLR_PER6     (_U_(1) << HW_RTC_MODE0_INTENCLR_PER6_Pos)
#define HW_RTC_MODE0_INTENCLR_PER7_Pos 7            /**< \brief (HW_RTC_MODE0_INTENCLR) Periodic Interval 7 Interrupt Enable */
#define HW_RTC_MODE0_INTENCLR_PER7     (_U_(1) << HW_RTC_MODE0_INTENCLR_PER7_Pos)
#define HW_RTC_MODE0_INTENCLR_PER_Pos  0            /**< \brief (HW_RTC_MODE0_INTENCLR) Periodic Interval x Interrupt Enable */
#define HW_RTC_MODE0_INTENCLR_PER_Msk  (_U_(0xFF) << HW_RTC_MODE0_INTENCLR_PER_Pos)
#define HW_RTC_MODE0_INTENCLR_PER(value) (HW_RTC_MODE0_INTENCLR_PER_Msk & ((value) << HW_RTC_MODE0_INTENCLR_PER_Pos))
#define HW_RTC_MODE0_INTENCLR_CMP0_Pos 8            /**< \brief (HW_RTC_MODE0_INTENCLR) Compare 0 Interrupt Enable */
#define HW_RTC_MODE0_INTENCLR_CMP0     (_U_(1) << HW_RTC_MODE0_INTENCLR_CMP0_Pos)
#define HW_RTC_MODE0_INTENCLR_CMP_Pos  8            /**< \brief (HW_RTC_MODE0_INTENCLR) Compare x Interrupt Enable */
#define HW_RTC_MODE0_INTENCLR_CMP_Msk  (_U_(0x1) << HW_RTC_MODE0_INTENCLR_CMP_Pos)
#define HW_RTC_MODE0_INTENCLR_CMP(value) (HW_RTC_MODE0_INTENCLR_CMP_Msk & ((value) << HW_RTC_MODE0_INTENCLR_CMP_Pos))
#define HW_RTC_MODE0_INTENCLR_OVF_Pos  15           /**< \brief (HW_RTC_MODE0_INTENCLR) Overflow Interrupt Enable */
#define HW_RTC_MODE0_INTENCLR_OVF      (_U_(0x1) << HW_RTC_MODE0_INTENCLR_OVF_Pos)
#define HW_RTC_MODE0_INTENCLR_MASK     _U_(0x81FF)  /**< \brief (HW_RTC_MODE0_INTENCLR) MASK Register */

/* -------- HW_RTC_MODE1_INTENCLR : (RTC Offset: 0x08) (R/W 16) MODE1 MODE1 Interrupt Enable Clear -------- */
typedef union {
  struct {
    uint16_t PER0:1;           /*!< bit:      0  Periodic Interval 0 Interrupt Enable */
    uint16_t PER1:1;           /*!< bit:      1  Periodic Interval 1 Interrupt Enable */
    uint16_t PER2:1;           /*!< bit:      2  Periodic Interval 2 Interrupt Enable */
    uint16_t PER3:1;           /*!< bit:      3  Periodic Interval 3 Interrupt Enable */
    uint16_t PER4:1;           /*!< bit:      4  Periodic Interval 4 Interrupt Enable */
    uint16_t PER5:1;           /*!< bit:      5  Periodic Interval 5 Interrupt Enable */
    uint16_t PER6:1;           /*!< bit:      6  Periodic Interval 6 Interrupt Enable */
    uint16_t PER7:1;           /*!< bit:      7  Periodic Interval 7 Interrupt Enable */
    uint16_t CMP0:1;           /*!< bit:      8  Compare 0 Interrupt Enable         */
    uint16_t CMP1:1;           /*!< bit:      9  Compare 1 Interrupt Enable         */
    uint16_t :5;               /*!< bit: 10..14  Reserved                           */
    uint16_t OVF:1;            /*!< bit:     15  Overflow Interrupt Enable          */
  } bit;                       /*!< Structure used for bit  access                  */
  struct {
    uint16_t PER:8;            /*!< bit:  0.. 7  Periodic Interval x Interrupt Enable */
    uint16_t CMP:2;            /*!< bit:  8.. 9  Compare x Interrupt Enable         */
    uint16_t :6;               /*!< bit: 10..15  Reserved                           */
  } vec;                       /*!< Structure used for vec  access                  */
  uint16_t reg;                /*!< Type      used for register access              */
} HW_RTC_MODE1_INTENCLR_Type;

#define HW_RTC_MODE1_INTENCLR_OFFSET   0x08         /**< \brief (HW_RTC_MODE1_INTENCLR offset) MODE1 Interrupt Enable Clear */
#define HW_RTC_MODE1_INTENCLR_RESETVALUE _U_(0x0000)  /**< \brief (HW_RTC_MODE1_INTENCLR reset_value) MODE1 Interrupt Enable Clear */

#define HW_RTC_MODE1_INTENCLR_PER0_Pos 0            /**< \brief (HW_RTC_MODE1_INTENCLR) Periodic Interval 0 Interrupt Enable */
#define HW_RTC_MODE1_INTENCLR_PER0     (_U_(1) << HW_RTC_MODE1_INTENCLR_PER0_Pos)
#define HW_RTC_MODE1_INTENCLR_PER1_Pos 1            /**< \brief (HW_RTC_MODE1_INTENCLR) Periodic Interval 1 Interrupt Enable */
#define HW_RTC_MODE1_INTENCLR_PER1     (_U_(1) << HW_RTC_MODE1_INTENCLR_PER1_Pos)
#define HW_RTC_MODE1_INTENCLR_PER2_Pos 2            /**< \brief (HW_RTC_MODE1_INTENCLR) Periodic Interval 2 Interrupt Enable */
#define HW_RTC_MODE1_INTENCLR_PER2     (_U_(1) << HW_RTC_MODE1_INTENCLR_PER2_Pos)
#define HW_RTC_MODE1_INTENCLR_PER3_Pos 3            /**< \brief (HW_RTC_MODE1_INTENCLR) Periodic Interval 3 Interrupt Enable */
#define HW_RTC_MODE1_INTENCLR_PER3     (_U_(1) << HW_RTC_MODE1_INTENCLR_PER3_Pos)
#define HW_RTC_MODE1_INTENCLR_PER4_Pos 4            /**< \brief (HW_RTC_MODE1_INTENCLR) Periodic Interval 4 Interrupt Enable */
#define HW_RTC_MODE1_INTENCLR_PER4     (_U_(1) << HW_RTC_MODE1_INTENCLR_PER4_Pos)
#define HW_RTC_MODE1_INTENCLR_PER5_Pos 5            /**< \brief (HW_RTC_MODE1_INTENCLR) Periodic Interval 5 Interrupt Enable */
#define HW_RTC_MODE1_INTENCLR_PER5     (_U_(1) << HW_RTC_MODE1_INTENCLR_PER5_Pos)
#define HW_RTC_MODE1_INTENCLR_PER6_Pos 6            /**< \brief (HW_RTC_MODE1_INTENCLR) Periodic Interval 6 Interrupt Enable */
#define HW_RTC_MODE1_INTENCLR_PER6     (_U_(1) << HW_RTC_MODE1_INTENCLR_PER6_Pos)
#define HW_RTC_MODE1_INTENCLR_PER7_Pos 7            /**< \brief (HW_RTC_MODE1_INTENCLR) Periodic Interval 7 Interrupt Enable */
#define HW_RTC_MODE1_INTENCLR_PER7     (_U_(1) << HW_RTC_MODE1_INTENCLR_PER7_Pos)
#define HW_RTC_MODE1_INTENCLR_PER_Pos  0            /**< \brief (HW_RTC_MODE1_INTENCLR) Periodic Interval x Interrupt Enable */
#define HW_RTC_MODE1_INTENCLR_PER_Msk  (_U_(0xFF) << HW_RTC_MODE1_INTENCLR_PER_Pos)
#define HW_RTC_MODE1_INTENCLR_PER(value) (HW_RTC_MODE1_INTENCLR_PER_Msk & ((value) << HW_RTC_MODE1_INTENCLR_PER_Pos))
#define HW_RTC_MODE1_INTENCLR_CMP0_Pos 8            /**< \brief (HW_RTC_MODE1_INTENCLR) Compare 0 Interrupt Enable */
#define HW_RTC_MODE1_INTENCLR_CMP0     (_U_(1) << HW_RTC_MODE1_INTENCLR_CMP0_Pos)
#define HW_RTC_MODE1_INTENCLR_CMP1_Pos 9            /**< \brief (HW_RTC_MODE1_INTENCLR) Compare 1 Interrupt Enable */
#define HW_RTC_MODE1_INTENCLR_CMP1     (_U_(1) << HW_RTC_MODE1_INTENCLR_CMP1_Pos)
#define HW_RTC_MODE1_INTENCLR_CMP_Pos  8            /**< \brief (HW_RTC_MODE1_INTENCLR) Compare x Interrupt Enable */
#define HW_RTC_MODE1_INTENCLR_CMP_Msk  (_U_(0x3) << HW_RTC_MODE1_INTENCLR_CMP_Pos)
#define HW_RTC_MODE1_INTENCLR_CMP(value) (HW_RTC_MODE1_INTENCLR_CMP_Msk & ((value) << HW_RTC_MODE1_INTENCLR_CMP_Pos))
#define HW_RTC_MODE1_INTENCLR_OVF_Pos  15           /**< \brief (HW_RTC_MODE1_INTENCLR) Overflow Interrupt Enable */
#define HW_RTC_MODE1_INTENCLR_OVF      (_U_(0x1) << HW_RTC_MODE1_INTENCLR_OVF_Pos)
#define HW_RTC_MODE1_INTENCLR_MASK     _U_(0x83FF)  /**< \brief (HW_RTC_MODE1_INTENCLR) MASK Register */

/* -------- HW_RTC_MODE2_INTENCLR : (RTC Offset: 0x08) (R/W 16) MODE2 MODE2 Interrupt Enable Clear -------- */
typedef union {
  struct {
    uint16_t PER0:1;           /*!< bit:      0  Periodic Interval 0 Interrupt Enable */
    uint16_t PER1:1;           /*!< bit:      1  Periodic Interval 1 Interrupt Enable */
    uint16_t PER2:1;           /*!< bit:      2  Periodic Interval 2 Interrupt Enable */
    uint16_t PER3:1;           /*!< bit:      3  Periodic Interval 3 Interrupt Enable */
    uint16_t PER4:1;           /*!< bit:      4  Periodic Interval 4 Interrupt Enable */
    uint16_t PER5:1;           /*!< bit:      5  Periodic Interval 5 Interrupt Enable */
    uint16_t PER6:1;           /*!< bit:      6  Periodic Interval 6 Interrupt Enable */
    uint16_t PER7:1;           /*!< bit:      7  Periodic Interval 7 Interrupt Enable */
    uint16_t ALARM0:1;         /*!< bit:      8  Alarm 0 Interrupt Enable           */
    uint16_t :6;               /*!< bit:  9..14  Reserved                           */
    uint16_t OVF:1;            /*!< bit:     15  Overflow Interrupt Enable          */
  } bit;                       /*!< Structure used for bit  access                  */
  struct {
    uint16_t PER:8;            /*!< bit:  0.. 7  Periodic Interval x Interrupt Enable */
    uint16_t ALARM:1;          /*!< bit:      8  Alarm x Interrupt Enable           */
    uint16_t :7;               /*!< bit:  9..15  Reserved                           */
  } vec;                       /*!< Structure used for vec  access                  */
  uint16_t reg;                /*!< Type      used for register access              */
} HW_RTC_MODE2_INTENCLR_Type;

#define HW_RTC_MODE2_INTENCLR_OFFSET   0x08         /**< \brief (HW_RTC_MODE2_INTENCLR offset) MODE2 Interrupt Enable Clear */
#define HW_RTC_MODE2_INTENCLR_RESETVALUE _U_(0x0000)  /**< \brief (HW_RTC_MODE2_INTENCLR reset_value) MODE2 Interrupt Enable Clear */

#define HW_RTC_MODE2_INTENCLR_PER0_Pos 0            /**< \brief (HW_RTC_MODE2_INTENCLR) Periodic Interval 0 Interrupt Enable */
#define HW_RTC_MODE2_INTENCLR_PER0     (_U_(1) << HW_RTC_MODE2_INTENCLR_PER0_Pos)
#define HW_RTC_MODE2_INTENCLR_PER1_Pos 1            /**< \brief (HW_RTC_MODE2_INTENCLR) Periodic Interval 1 Interrupt Enable */
#define HW_RTC_MODE2_INTENCLR_PER1     (_U_(1) << HW_RTC_MODE2_INTENCLR_PER1_Pos)
#define HW_RTC_MODE2_INTENCLR_PER2_Pos 2            /**< \brief (HW_RTC_MODE2_INTENCLR) Periodic Interval 2 Interrupt Enable */
#define HW_RTC_MODE2_INTENCLR_PER2     (_U_(1) << HW_RTC_MODE2_INTENCLR_PER2_Pos)
#define HW_RTC_MODE2_INTENCLR_PER3_Pos 3            /**< \brief (HW_RTC_MODE2_INTENCLR) Periodic Interval 3 Interrupt Enable */
#define HW_RTC_MODE2_INTENCLR_PER3     (_U_(1) << HW_RTC_MODE2_INTENCLR_PER3_Pos)
#define HW_RTC_MODE2_INTENCLR_PER4_Pos 4            /**< \brief (HW_RTC_MODE2_INTENCLR) Periodic Interval 4 Interrupt Enable */
#define HW_RTC_MODE2_INTENCLR_PER4     (_U_(1) << HW_RTC_MODE2_INTENCLR_PER4_Pos)
#define HW_RTC_MODE2_INTENCLR_PER5_Pos 5            /**< \brief (HW_RTC_MODE2_INTENCLR) Periodic Interval 5 Interrupt Enable */
#define HW_RTC_MODE2_INTENCLR_PER5     (_U_(1) << HW_RTC_MODE2_INTENCLR_PER5_Pos)
#define HW_RTC_MODE2_INTENCLR_PER6_Pos 6            /**< \brief (HW_RTC_MODE2_INTENCLR) Periodic Interval 6 Interrupt Enable */
#define HW_RTC_MODE2_INTENCLR_PER6     (_U_(1) << HW_RTC_MODE2_INTENCLR_PER6_Pos)
#define HW_RTC_MODE2_INTENCLR_PER7_Pos 7            /**< \brief (HW_RTC_MODE2_INTENCLR) Periodic Interval 7 Interrupt Enable */
#define HW_RTC_MODE2_INTENCLR_PER7     (_U_(1) << HW_RTC_MODE2_INTENCLR_PER7_Pos)
#define HW_RTC_MODE2_INTENCLR_PER_Pos  0            /**< \brief (HW_RTC_MODE2_INTENCLR) Periodic Interval x Interrupt Enable */
#define HW_RTC_MODE2_INTENCLR_PER_Msk  (_U_(0xFF) << HW_RTC_MODE2_INTENCLR_PER_Pos)
#define HW_RTC_MODE2_INTENCLR_PER(value) (HW_RTC_MODE2_INTENCLR_PER_Msk & ((value) << HW_RTC_MODE2_INTENCLR_PER_Pos))
#define HW_RTC_MODE2_INTENCLR_ALARM0_Pos 8            /**< \brief (HW_RTC_MODE2_INTENCLR) Alarm 0 Interrupt Enable */
#define HW_RTC_MODE2_INTENCLR_ALARM0   (_U_(1) << HW_RTC_MODE2_INTENCLR_ALARM0_Pos)
#define HW_RTC_MODE2_INTENCLR_ALARM_Pos 8            /**< \brief (HW_RTC_MODE2_INTENCLR) Alarm x Interrupt Enable */
#define HW_RTC_MODE2_INTENCLR_ALARM_Msk (_U_(0x1) << HW_RTC_MODE2_INTENCLR_ALARM_Pos)
#define HW_RTC_MODE2_INTENCLR_ALARM(value) (HW_RTC_MODE2_INTENCLR_ALARM_Msk & ((value) << HW_RTC_MODE2_INTENCLR_ALARM_Pos))
#define HW_RTC_MODE2_INTENCLR_OVF_Pos  15           /**< \brief (HW_RTC_MODE2_INTENCLR) Overflow Interrupt Enable */
#define HW_RTC_MODE2_INTENCLR_OVF      (_U_(0x1) << HW_RTC_MODE2_INTENCLR_OVF_Pos)
#define HW_RTC_MODE2_INTENCLR_MASK     _U_(0x81FF)  /**< \brief (HW_RTC_MODE2_INTENCLR) MASK Register */

/* -------- HW_RTC_MODE0_INTENSET : (RTC Offset: 0x0A) (R/W 16) MODE0 MODE0 Interrupt Enable Set -------- */
typedef union {
  struct {
    uint16_t PER0:1;           /*!< bit:      0  Periodic Interval 0 Interrupt Enable */
    uint16_t PER1:1;           /*!< bit:      1  Periodic Interval 1 Interrupt Enable */
    uint16_t PER2:1;           /*!< bit:      2  Periodic Interval 2 Interrupt Enable */
    uint16_t PER3:1;           /*!< bit:      3  Periodic Interval 3 Interrupt Enable */
    uint16_t PER4:1;           /*!< bit:      4  Periodic Interval 4 Interrupt Enable */
    uint16_t PER5:1;           /*!< bit:      5  Periodic Interval 5 Interrupt Enable */
    uint16_t PER6:1;           /*!< bit:      6  Periodic Interval 6 Interrupt Enable */
    uint16_t PER7:1;           /*!< bit:      7  Periodic Interval 7 Interrupt Enable */
    uint16_t CMP0:1;           /*!< bit:      8  Compare 0 Interrupt Enable         */
    uint16_t :6;               /*!< bit:  9..14  Reserved                           */
    uint16_t OVF:1;            /*!< bit:     15  Overflow Interrupt Enable          */
  } bit;                       /*!< Structure used for bit  access                  */
  struct {
    uint16_t PER:8;            /*!< bit:  0.. 7  Periodic Interval x Interrupt Enable */
    uint16_t CMP:1;            /*!< bit:      8  Compare x Interrupt Enable         */
    uint16_t :7;               /*!< bit:  9..15  Reserved                           */
  } vec;                       /*!< Structure used for vec  access                  */
  uint16_t reg;                /*!< Type      used for register access              */
} HW_RTC_MODE0_INTENSET_Type;

#define HW_RTC_MODE0_INTENSET_OFFSET   0x0A         /**< \brief (HW_RTC_MODE0_INTENSET offset) MODE0 Interrupt Enable Set */
#define HW_RTC_MODE0_INTENSET_RESETVALUE _U_(0x0000)  /**< \brief (HW_RTC_MODE0_INTENSET reset_value) MODE0 Interrupt Enable Set */

#define HW_RTC_MODE0_INTENSET_PER0_Pos 0            /**< \brief (HW_RTC_MODE0_INTENSET) Periodic Interval 0 Interrupt Enable */
#define HW_RTC_MODE0_INTENSET_PER0     (_U_(1) << HW_RTC_MODE0_INTENSET_PER0_Pos)
#define HW_RTC_MODE0_INTENSET_PER1_Pos 1            /**< \brief (HW_RTC_MODE0_INTENSET) Periodic Interval 1 Interrupt Enable */
#define HW_RTC_MODE0_INTENSET_PER1     (_U_(1) << HW_RTC_MODE0_INTENSET_PER1_Pos)
#define HW_RTC_MODE0_INTENSET_PER2_Pos 2            /**< \brief (HW_RTC_MODE0_INTENSET) Periodic Interval 2 Interrupt Enable */
#define HW_RTC_MODE0_INTENSET_PER2     (_U_(1) << HW_RTC_MODE0_INTENSET_PER2_Pos)
#define HW_RTC_MODE0_INTENSET_PER3_Pos 3            /**< \brief (HW_RTC_MODE0_INTENSET) Periodic Interval 3 Interrupt Enable */
#define HW_RTC_MODE0_INTENSET_PER3     (_U_(1) << HW_RTC_MODE0_INTENSET_PER3_Pos)
#define HW_RTC_MODE0_INTENSET_PER4_Pos 4            /**< \brief (HW_RTC_MODE0_INTENSET) Periodic Interval 4 Interrupt Enable */
#define HW_RTC_MODE0_INTENSET_PER4     (_U_(1) << HW_RTC_MODE0_INTENSET_PER4_Pos)
#define HW_RTC_MODE0_INTENSET_PER5_Pos 5            /**< \brief (HW_RTC_MODE0_INTENSET) Periodic Interval 5 Interrupt Enable */
#define HW_RTC_MODE0_INTENSET_PER5     (_U_(1) << HW_RTC_MODE0_INTENSET_PER5_Pos)
#define HW_RTC_MODE0_INTENSET_PER6_Pos 6            /**< \brief (HW_RTC_MODE0_INTENSET) Periodic Interval 6 Interrupt Enable */
#define HW_RTC_MODE0_INTENSET_PER6     (_U_(1) << HW_RTC_MODE0_INTENSET_PER6_Pos)
#define HW_RTC_MODE0_INTENSET_PER7_Pos 7            /**< \brief (HW_RTC_MODE0_INTENSET) Periodic Interval 7 Interrupt Enable */
#define HW_RTC_MODE0_INTENSET_PER7     (_U_(1) << HW_RTC_MODE0_INTENSET_PER7_Pos)
#define HW_RTC_MODE0_INTENSET_PER_Pos  0            /**< \brief (HW_RTC_MODE0_INTENSET) Periodic Interval x Interrupt Enable */
#define HW_RTC_MODE0_INTENSET_PER_Msk  (_U_(0xFF) << HW_RTC_MODE0_INTENSET_PER_Pos)
#define HW_RTC_MODE0_INTENSET_PER(value) (HW_RTC_MODE0_INTENSET_PER_Msk & ((value) << HW_RTC_MODE0_INTENSET_PER_Pos))
#define HW_RTC_MODE0_INTENSET_CMP0_Pos 8            /**< \brief (HW_RTC_MODE0_INTENSET) Compare 0 Interrupt Enable */
#define HW_RTC_MODE0_INTENSET_CMP0     (_U_(1) << HW_RTC_MODE0_INTENSET_CMP0_Pos)
#define HW_RTC_MODE0_INTENSET_CMP_Pos  8            /**< \brief (HW_RTC_MODE0_INTENSET) Compare x Interrupt Enable */
#define HW_RTC_MODE0_INTENSET_CMP_Msk  (_U_(0x1) << HW_RTC_MODE0_INTENSET_CMP_Pos)
#define HW_RTC_MODE0_INTENSET_CMP(value) (HW_RTC_MODE0_INTENSET_CMP_Msk & ((value) << HW_RTC_MODE0_INTENSET_CMP_Pos))
#define HW_RTC_MODE0_INTENSET_OVF_Pos  15           /**< \brief (HW_RTC_MODE0_INTENSET) Overflow Interrupt Enable */
#define HW_RTC_MODE0_INTENSET_OVF      (_U_(0x1) << HW_RTC_MODE0_INTENSET_OVF_Pos)
#define HW_RTC_MODE0_INTENSET_MASK     _U_(0x81FF)  /**< \brief (HW_RTC_MODE0_INTENSET) MASK Register */

/* -------- HW_RTC_MODE1_INTENSET : (RTC Offset: 0x0A) (R/W 16) MODE1 MODE1 Interrupt Enable Set -------- */
typedef union {
  struct {
    uint16_t PER0:1;           /*!< bit:      0  Periodic Interval 0 Interrupt Enable */
    uint16_t PER1:1;           /*!< bit:      1  Periodic Interval 1 Interrupt Enable */
    uint16_t PER2:1;           /*!< bit:      2  Periodic Interval 2 Interrupt Enable */
    uint16_t PER3:1;           /*!< bit:      3  Periodic Interval 3 Interrupt Enable */
    uint16_t PER4:1;           /*!< bit:      4  Periodic Interval 4 Interrupt Enable */
    uint16_t PER5:1;           /*!< bit:      5  Periodic Interval 5 Interrupt Enable */
    uint16_t PER6:1;           /*!< bit:      6  Periodic Interval 6 Interrupt Enable */
    uint16_t PER7:1;           /*!< bit:      7  Periodic Interval 7 Interrupt Enable */
    uint16_t CMP0:1;           /*!< bit:      8  Compare 0 Interrupt Enable         */
    uint16_t CMP1:1;           /*!< bit:      9  Compare 1 Interrupt Enable         */
    uint16_t :5;               /*!< bit: 10..14  Reserved                           */
    uint16_t OVF:1;            /*!< bit:     15  Overflow Interrupt Enable          */
  } bit;                       /*!< Structure used for bit  access                  */
  struct {
    uint16_t PER:8;            /*!< bit:  0.. 7  Periodic Interval x Interrupt Enable */
    uint16_t CMP:2;            /*!< bit:  8.. 9  Compare x Interrupt Enable         */
    uint16_t :6;               /*!< bit: 10..15  Reserved                           */
  } vec;                       /*!< Structure used for vec  access                  */
  uint16_t reg;                /*!< Type      used for register access              */
} HW_RTC_MODE1_INTENSET_Type;

#define HW_RTC_MODE1_INTENSET_OFFSET   0x0A         /**< \brief (HW_RTC_MODE1_INTENSET offset) MODE1 Interrupt Enable Set */
#define HW_RTC_MODE1_INTENSET_RESETVALUE _U_(0x0000)  /**< \brief (HW_RTC_MODE1_INTENSET reset_value) MODE1 Interrupt Enable Set */

#define HW_RTC_MODE1_INTENSET_PER0_Pos 0            /**< \brief (HW_RTC_MODE1_INTENSET) Periodic Interval 0 Interrupt Enable */
#define HW_RTC_MODE1_INTENSET_PER0     (_U_(1) << HW_RTC_MODE1_INTENSET_PER0_Pos)
#define HW_RTC_MODE1_INTENSET_PER1_Pos 1            /**< \brief (HW_RTC_MODE1_INTENSET) Periodic Interval 1 Interrupt Enable */
#define HW_RTC_MODE1_INTENSET_PER1     (_U_(1) << HW_RTC_MODE1_INTENSET_PER1_Pos)
#define HW_RTC_MODE1_INTENSET_PER2_Pos 2            /**< \brief (HW_RTC_MODE1_INTENSET) Periodic Interval 2 Interrupt Enable */
#define HW_RTC_MODE1_INTENSET_PER2     (_U_(1) << HW_RTC_MODE1_INTENSET_PER2_Pos)
#define HW_RTC_MODE1_INTENSET_PER3_Pos 3            /**< \brief (HW_RTC_MODE1_INTENSET) Periodic Interval 3 Interrupt Enable */
#define HW_RTC_MODE1_INTENSET_PER3     (_U_(1) << HW_RTC_MODE1_INTENSET_PER3_Pos)
#define HW_RTC_MODE1_INTENSET_PER4_Pos 4            /**< \brief (HW_RTC_MODE1_INTENSET) Periodic Interval 4 Interrupt Enable */
#define HW_RTC_MODE1_INTENSET_PER4     (_U_(1) << HW_RTC_MODE1_INTENSET_PER4_Pos)
#define HW_RTC_MODE1_INTENSET_PER5_Pos 5            /**< \brief (HW_RTC_MODE1_INTENSET) Periodic Interval 5 Interrupt Enable */
#define HW_RTC_MODE1_INTENSET_PER5     (_U_(1) << HW_RTC_MODE1_INTENSET_PER5_Pos)
#define HW_RTC_MODE1_INTENSET_PER6_Pos 6            /**< \brief (HW_RTC_MODE1_INTENSET) Periodic Interval 6 Interrupt Enable */
#define HW_RTC_MODE1_INTENSET_PER6     (_U_(1) << HW_RTC_MODE1_INTENSET_PER6_Pos)
#define HW_RTC_MODE1_INTENSET_PER7_Pos 7            /**< \brief (HW_RTC_MODE1_INTENSET) Periodic Interval 7 Interrupt Enable */
#define HW_RTC_MODE1_INTENSET_PER7     (_U_(1) << HW_RTC_MODE1_INTENSET_PER7_Pos)
#define HW_RTC_MODE1_INTENSET_PER_Pos  0            /**< \brief (HW_RTC_MODE1_INTENSET) Periodic Interval x Interrupt Enable */
#define HW_RTC_MODE1_INTENSET_PER_Msk  (_U_(0xFF) << HW_RTC_MODE1_INTENSET_PER_Pos)
#define HW_RTC_MODE1_INTENSET_PER(value) (HW_RTC_MODE1_INTENSET_PER_Msk & ((value) << HW_RTC_MODE1_INTENSET_PER_Pos))
#define HW_RTC_MODE1_INTENSET_CMP0_Pos 8            /**< \brief (HW_RTC_MODE1_INTENSET) Compare 0 Interrupt Enable */
#define HW_RTC_MODE1_INTENSET_CMP0     (_U_(1) << HW_RTC_MODE1_INTENSET_CMP0_Pos)
#define HW_RTC_MODE1_INTENSET_CMP1_Pos 9            /**< \brief (HW_RTC_MODE1_INTENSET) Compare 1 Interrupt Enable */
#define HW_RTC_MODE1_INTENSET_CMP1     (_U_(1) << HW_RTC_MODE1_INTENSET_CMP1_Pos)
#define HW_RTC_MODE1_INTENSET_CMP_Pos  8            /**< \brief (HW_RTC_MODE1_INTENSET) Compare x Interrupt Enable */
#define HW_RTC_MODE1_INTENSET_CMP_Msk  (_U_(0x3) << HW_RTC_MODE1_INTENSET_CMP_Pos)
#define HW_RTC_MODE1_INTENSET_CMP(value) (HW_RTC_MODE1_INTENSET_CMP_Msk & ((value) << HW_RTC_MODE1_INTENSET_CMP_Pos))
#define HW_RTC_MODE1_INTENSET_OVF_Pos  15           /**< \brief (HW_RTC_MODE1_INTENSET) Overflow Interrupt Enable */
#define HW_RTC_MODE1_INTENSET_OVF      (_U_(0x1) << HW_RTC_MODE1_INTENSET_OVF_Pos)
#define HW_RTC_MODE1_INTENSET_MASK     _U_(0x83FF)  /**< \brief (HW_RTC_MODE1_INTENSET) MASK Register */

/* -------- HW_RTC_MODE2_INTENSET : (RTC Offset: 0x0A) (R/W 16) MODE2 MODE2 Interrupt Enable Set -------- */
typedef union {
  struct {
    uint16_t PER0:1;           /*!< bit:      0  Periodic Interval 0 Enable         */
    uint16_t PER1:1;           /*!< bit:      1  Periodic Interval 1 Enable         */
    uint16_t PER2:1;           /*!< bit:      2  Periodic Interval 2 Enable         */
    uint16_t PER3:1;           /*!< bit:      3  Periodic Interval 3 Enable         */
    uint16_t PER4:1;           /*!< bit:      4  Periodic Interval 4 Enable         */
    uint16_t PER5:1;           /*!< bit:      5  Periodic Interval 5 Enable         */
    uint16_t PER6:1;           /*!< bit:      6  Periodic Interval 6 Enable         */
    uint16_t PER7:1;           /*!< bit:      7  Periodic Interval 7 Enable         */
    uint16_t ALARM0:1;         /*!< bit:      8  Alarm 0 Interrupt Enable           */
    uint16_t :6;               /*!< bit:  9..14  Reserved                           */
    uint16_t OVF:1;            /*!< bit:     15  Overflow Interrupt Enable          */
  } bit;                       /*!< Structure used for bit  access                  */
  struct {
    uint16_t PER:8;            /*!< bit:  0.. 7  Periodic Interval x Enable         */
    uint16_t ALARM:1;          /*!< bit:      8  Alarm x Interrupt Enable           */
    uint16_t :7;               /*!< bit:  9..15  Reserved                           */
  } vec;                       /*!< Structure used for vec  access                  */
  uint16_t reg;                /*!< Type      used for register access              */
} HW_RTC_MODE2_INTENSET_Type;

#define HW_RTC_MODE2_INTENSET_OFFSET   0x0A         /**< \brief (HW_RTC_MODE2_INTENSET offset) MODE2 Interrupt Enable Set */
#define HW_RTC_MODE2_INTENSET_RESETVALUE _U_(0x0000)  /**< \brief (HW_RTC_MODE2_INTENSET reset_value) MODE2 Interrupt Enable Set */

#define HW_RTC_MODE2_INTENSET_PER0_Pos 0            /**< \brief (HW_RTC_MODE2_INTENSET) Periodic Interval 0 Enable */
#define HW_RTC_MODE2_INTENSET_PER0     (_U_(1) << HW_RTC_MODE2_INTENSET_PER0_Pos)
#define HW_RTC_MODE2_INTENSET_PER1_Pos 1            /**< \brief (HW_RTC_MODE2_INTENSET) Periodic Interval 1 Enable */
#define HW_RTC_MODE2_INTENSET_PER1     (_U_(1) << HW_RTC_MODE2_INTENSET_PER1_Pos)
#define HW_RTC_MODE2_INTENSET_PER2_Pos 2            /**< \brief (HW_RTC_MODE2_INTENSET) Periodic Interval 2 Enable */
#define HW_RTC_MODE2_INTENSET_PER2     (_U_(1) << HW_RTC_MODE2_INTENSET_PER2_Pos)
#define HW_RTC_MODE2_INTENSET_PER3_Pos 3            /**< \brief (HW_RTC_MODE2_INTENSET) Periodic Interval 3 Enable */
#define HW_RTC_MODE2_INTENSET_PER3     (_U_(1) << HW_RTC_MODE2_INTENSET_PER3_Pos)
#define HW_RTC_MODE2_INTENSET_PER4_Pos 4            /**< \brief (HW_RTC_MODE2_INTENSET) Periodic Interval 4 Enable */
#define HW_RTC_MODE2_INTENSET_PER4     (_U_(1) << HW_RTC_MODE2_INTENSET_PER4_Pos)
#define HW_RTC_MODE2_INTENSET_PER5_Pos 5            /**< \brief (HW_RTC_MODE2_INTENSET) Periodic Interval 5 Enable */
#define HW_RTC_MODE2_INTENSET_PER5     (_U_(1) << HW_RTC_MODE2_INTENSET_PER5_Pos)
#define HW_RTC_MODE2_INTENSET_PER6_Pos 6            /**< \brief (HW_RTC_MODE2_INTENSET) Periodic Interval 6 Enable */
#define HW_RTC_MODE2_INTENSET_PER6     (_U_(1) << HW_RTC_MODE2_INTENSET_PER6_Pos)
#define HW_RTC_MODE2_INTENSET_PER7_Pos 7            /**< \brief (HW_RTC_MODE2_INTENSET) Periodic Interval 7 Enable */
#define HW_RTC_MODE2_INTENSET_PER7     (_U_(1) << HW_RTC_MODE2_INTENSET_PER7_Pos)
#define HW_RTC_MODE2_INTENSET_PER_Pos  0            /**< \brief (HW_RTC_MODE2_INTENSET) Periodic Interval x Enable */
#define HW_RTC_MODE2_INTENSET_PER_Msk  (_U_(0xFF) << HW_RTC_MODE2_INTENSET_PER_Pos)
#define HW_RTC_MODE2_INTENSET_PER(value) (HW_RTC_MODE2_INTENSET_PER_Msk & ((value) << HW_RTC_MODE2_INTENSET_PER_Pos))
#define HW_RTC_MODE2_INTENSET_ALARM0_Pos 8            /**< \brief (HW_RTC_MODE2_INTENSET) Alarm 0 Interrupt Enable */
#define HW_RTC_MODE2_INTENSET_ALARM0   (_U_(1) << HW_RTC_MODE2_INTENSET_ALARM0_Pos)
#define HW_RTC_MODE2_INTENSET_ALARM_Pos 8            /**< \brief (HW_RTC_MODE2_INTENSET) Alarm x Interrupt Enable */
#define HW_RTC_MODE2_INTENSET_ALARM_Msk (_U_(0x1) << HW_RTC_MODE2_INTENSET_ALARM_Pos)
#define HW_RTC_MODE2_INTENSET_ALARM(value) (HW_RTC_MODE2_INTENSET_ALARM_Msk & ((value) << HW_RTC_MODE2_INTENSET_ALARM_Pos))
#define HW_RTC_MODE2_INTENSET_OVF_Pos  15           /**< \brief (HW_RTC_MODE2_INTENSET) Overflow Interrupt Enable */
#define HW_RTC_MODE2_INTENSET_OVF      (_U_(0x1) << HW_RTC_MODE2_INTENSET_OVF_Pos)
#define HW_RTC_MODE2_INTENSET_MASK     _U_(0x81FF)  /**< \brief (HW_RTC_MODE2_INTENSET) MASK Register */

/* -------- HW_RTC_MODE0_INTFLAG : (RTC Offset: 0x0C) (R/W 16) MODE0 MODE0 Interrupt Flag Status and Clear -------- */
typedef union { // __I to avoid read-modify-write on write-to-clear register
  struct {
    __I uint16_t PER0:1;           /*!< bit:      0  Periodic Interval 0                */
    __I uint16_t PER1:1;           /*!< bit:      1  Periodic Interval 1                */
    __I uint16_t PER2:1;           /*!< bit:      2  Periodic Interval 2                */
    __I uint16_t PER3:1;           /*!< bit:      3  Periodic Interval 3                */
    __I uint16_t PER4:1;           /*!< bit:      4  Periodic Interval 4                */
    __I uint16_t PER5:1;           /*!< bit:      5  Periodic Interval 5                */
    __I uint16_t PER6:1;           /*!< bit:      6  Periodic Interval 6                */
    __I uint16_t PER7:1;           /*!< bit:      7  Periodic Interval 7                */
    __I uint16_t CMP0:1;           /*!< bit:      8  Compare 0                          */
    __I uint16_t :6;               /*!< bit:  9..14  Reserved                           */
    __I uint16_t OVF:1;            /*!< bit:     15  Overflow                           */
  } bit;                       /*!< Structure used for bit  access                  */
  struct {
    __I uint16_t PER:8;            /*!< bit:  0.. 7  Periodic Interval x                */
    __I uint16_t CMP:1;            /*!< bit:      8  Compare x                          */
    __I uint16_t :7;               /*!< bit:  9..15  Reserved                           */
  } vec;                       /*!< Structure used for vec  access                  */
  uint16_t reg;                /*!< Type      used for register access              */
} HW_RTC_MODE0_INTFLAG_Type;

#define HW_RTC_MODE0_INTFLAG_OFFSET    0x0C         /**< \brief (HW_RTC_MODE0_INTFLAG offset) MODE0 Interrupt Flag Status and Clear */
#define HW_RTC_MODE0_INTFLAG_RESETVALUE _U_(0x0000)  /**< \brief (HW_RTC_MODE0_INTFLAG reset_value) MODE0 Interrupt Flag Status and Clear */

#define HW_RTC_MODE0_INTFLAG_PER0_Pos  0            /**< \brief (HW_RTC_MODE0_INTFLAG) Periodic Interval 0 */
#define HW_RTC_MODE0_INTFLAG_PER0      (_U_(1) << HW_RTC_MODE0_INTFLAG_PER0_Pos)
#define HW_RTC_MODE0_INTFLAG_PER1_Pos  1            /**< \brief (HW_RTC_MODE0_INTFLAG) Periodic Interval 1 */
#define HW_RTC_MODE0_INTFLAG_PER1      (_U_(1) << HW_RTC_MODE0_INTFLAG_PER1_Pos)
#define HW_RTC_MODE0_INTFLAG_PER2_Pos  2            /**< \brief (HW_RTC_MODE0_INTFLAG) Periodic Interval 2 */
#define HW_RTC_MODE0_INTFLAG_PER2      (_U_(1) << HW_RTC_MODE0_INTFLAG_PER2_Pos)
#define HW_RTC_MODE0_INTFLAG_PER3_Pos  3            /**< \brief (HW_RTC_MODE0_INTFLAG) Periodic Interval 3 */
#define HW_RTC_MODE0_INTFLAG_PER3      (_U_(1) << HW_RTC_MODE0_INTFLAG_PER3_Pos)
#define HW_RTC_MODE0_INTFLAG_PER4_Pos  4            /**< \brief (HW_RTC_MODE0_INTFLAG) Periodic Interval 4 */
#define HW_RTC_MODE0_INTFLAG_PER4      (_U_(1) << HW_RTC_MODE0_INTFLAG_PER4_Pos)
#define HW_RTC_MODE0_INTFLAG_PER5_Pos  5            /**< \brief (HW_RTC_MODE0_INTFLAG) Periodic Interval 5 */
#define HW_RTC_MODE0_INTFLAG_PER5      (_U_(1) << HW_RTC_MODE0_INTFLAG_PER5_Pos)
#define HW_RTC_MODE0_INTFLAG_PER6_Pos  6            /**< \brief (HW_RTC_MODE0_INTFLAG) Periodic Interval 6 */
#define HW_RTC_MODE0_INTFLAG_PER6      (_U_(1) << HW_RTC_MODE0_INTFLAG_PER6_Pos)
#define HW_RTC_MODE0_INTFLAG_PER7_Pos  7            /**< \brief (HW_RTC_MODE0_INTFLAG) Periodic Interval 7 */
#define HW_RTC_MODE0_INTFLAG_PER7      (_U_(1) << HW_RTC_MODE0_INTFLAG_PER7_Pos)
#define HW_RTC_MODE0_INTFLAG_PER_Pos   0            /**< \brief (HW_RTC_MODE0_INTFLAG) Periodic Interval x */
#define HW_RTC_MODE0_INTFLAG_PER_Msk   (_U_(0xFF) << HW_RTC_MODE0_INTFLAG_PER_Pos)
#define HW_RTC_MODE0_INTFLAG_PER(value) (HW_RTC_MODE0_INTFLAG_PER_Msk & ((value) << HW_RTC_MODE0_INTFLAG_PER_Pos))
#define HW_RTC_MODE0_INTFLAG_CMP0_Pos  8            /**< \brief (HW_RTC_MODE0_INTFLAG) Compare 0 */
#define HW_RTC_MODE0_INTFLAG_CMP0      (_U_(1) << HW_RTC_MODE0_INTFLAG_CMP0_Pos)
#define HW_RTC_MODE0_INTFLAG_CMP_Pos   8            /**< \brief (HW_RTC_MODE0_INTFLAG) Compare x */
#define HW_RTC_MODE0_INTFLAG_CMP_Msk   (_U_(0x1) << HW_RTC_MODE0_INTFLAG_CMP_Pos)
#define HW_RTC_MODE0_INTFLAG_CMP(value) (HW_RTC_MODE0_INTFLAG_CMP_Msk & ((value) << HW_RTC_MODE0_INTFLAG_CMP_Pos))
#define HW_RTC_MODE0_INTFLAG_OVF_Pos   15           /**< \brief (HW_RTC_MODE0_INTFLAG) Overflow */
#define HW_RTC_MODE0_INTFLAG_OVF       (_U_(0x1) << HW_RTC_MODE0_INTFLAG_OVF_Pos)
#define HW_RTC_MODE0_INTFLAG_MASK      _U_(0x81FF)  /**< \brief (HW_RTC_MODE0_INTFLAG) MASK Register */

/* -------- HW_RTC_MODE1_INTFLAG : (RTC Offset: 0x0C) (R/W 16) MODE1 MODE1 Interrupt Flag Status and Clear -------- */
typedef union { // __I to avoid read-modify-write on write-to-clear register
  struct {
    __I uint16_t PER0:1;           /*!< bit:      0  Periodic Interval 0                */
    __I uint16_t PER1:1;           /*!< bit:      1  Periodic Interval 1                */
    __I uint16_t PER2:1;           /*!< bit:      2  Periodic Interval 2                */
    __I uint16_t PER3:1;           /*!< bit:      3  Periodic Interval 3                */
    __I uint16_t PER4:1;           /*!< bit:      4  Periodic Interval 4                */
    __I uint16_t PER5:1;           /*!< bit:      5  Periodic Interval 5                */
    __I uint16_t PER6:1;           /*!< bit:      6  Periodic Interval 6                */
    __I uint16_t PER7:1;           /*!< bit:      7  Periodic Interval 7                */
    __I uint16_t CMP0:1;           /*!< bit:      8  Compare 0                          */
    __I uint16_t CMP1:1;           /*!< bit:      9  Compare 1                          */
    __I uint16_t :5;               /*!< bit: 10..14  Reserved                           */
    __I uint16_t OVF:1;            /*!< bit:     15  Overflow                           */
  } bit;                       /*!< Structure used for bit  access                  */
  struct {
    __I uint16_t PER:8;            /*!< bit:  0.. 7  Periodic Interval x                */
    __I uint16_t CMP:2;            /*!< bit:  8.. 9  Compare x                          */
    __I uint16_t :6;               /*!< bit: 10..15  Reserved                           */
  } vec;                       /*!< Structure used for vec  access                  */
  uint16_t reg;                /*!< Type      used for register access              */
} HW_RTC_MODE1_INTFLAG_Type;

#define HW_RTC_MODE1_INTFLAG_OFFSET    0x0C         /**< \brief (HW_RTC_MODE1_INTFLAG offset) MODE1 Interrupt Flag Status and Clear */
#define HW_RTC_MODE1_INTFLAG_RESETVALUE _U_(0x0000)  /**< \brief (HW_RTC_MODE1_INTFLAG reset_value) MODE1 Interrupt Flag Status and Clear */

#define HW_RTC_MODE1_INTFLAG_PER0_Pos  0            /**< \brief (HW_RTC_MODE1_INTFLAG) Periodic Interval 0 */
#define HW_RTC_MODE1_INTFLAG_PER0      (_U_(1) << HW_RTC_MODE1_INTFLAG_PER0_Pos)
#define HW_RTC_MODE1_INTFLAG_PER1_Pos  1            /**< \brief (HW_RTC_MODE1_INTFLAG) Periodic Interval 1 */
#define HW_RTC_MODE1_INTFLAG_PER1      (_U_(1) << HW_RTC_MODE1_INTFLAG_PER1_Pos)
#define HW_RTC_MODE1_INTFLAG_PER2_Pos  2            /**< \brief (HW_RTC_MODE1_INTFLAG) Periodic Interval 2 */
#define HW_RTC_MODE1_INTFLAG_PER2      (_U_(1) << HW_RTC_MODE1_INTFLAG_PER2_Pos)
#define HW_RTC_MODE1_INTFLAG_PER3_Pos  3            /**< \brief (HW_RTC_MODE1_INTFLAG) Periodic Interval 3 */
#define HW_RTC_MODE1_INTFLAG_PER3      (_U_(1) << HW_RTC_MODE1_INTFLAG_PER3_Pos)
#define HW_RTC_MODE1_INTFLAG_PER4_Pos  4            /**< \brief (HW_RTC_MODE1_INTFLAG) Periodic Interval 4 */
#define HW_RTC_MODE1_INTFLAG_PER4      (_U_(1) << HW_RTC_MODE1_INTFLAG_PER4_Pos)
#define HW_RTC_MODE1_INTFLAG_PER5_Pos  5            /**< \brief (HW_RTC_MODE1_INTFLAG) Periodic Interval 5 */
#define HW_RTC_MODE1_INTFLAG_PER5      (_U_(1) << HW_RTC_MODE1_INTFLAG_PER5_Pos)
#define HW_RTC_MODE1_INTFLAG_PER6_Pos  6            /**< \brief (HW_RTC_MODE1_INTFLAG) Periodic Interval 6 */
#define HW_RTC_MODE1_INTFLAG_PER6      (_U_(1) << HW_RTC_MODE1_INTFLAG_PER6_Pos)
#define HW_RTC_MODE1_INTFLAG_PER7_Pos  7            /**< \brief (HW_RTC_MODE1_INTFLAG) Periodic Interval 7 */
#define HW_RTC_MODE1_INTFLAG_PER7      (_U_(1) << HW_RTC_MODE1_INTFLAG_PER7_Pos)
#define HW_RTC_MODE1_INTFLAG_PER_Pos   0            /**< \brief (HW_RTC_MODE1_INTFLAG) Periodic Interval x */
#define HW_RTC_MODE1_INTFLAG_PER_Msk   (_U_(0xFF) << HW_RTC_MODE1_INTFLAG_PER_Pos)
#define HW_RTC_MODE1_INTFLAG_PER(value) (HW_RTC_MODE1_INTFLAG_PER_Msk & ((value) << HW_RTC_MODE1_INTFLAG_PER_Pos))
#define HW_RTC_MODE1_INTFLAG_CMP0_Pos  8            /**< \brief (HW_RTC_MODE1_INTFLAG) Compare 0 */
#define HW_RTC_MODE1_INTFLAG_CMP0      (_U_(1) << HW_RTC_MODE1_INTFLAG_CMP0_Pos)
#define HW_RTC_MODE1_INTFLAG_CMP1_Pos  9            /**< \brief (HW_RTC_MODE1_INTFLAG) Compare 1 */
#define HW_RTC_MODE1_INTFLAG_CMP1      (_U_(1) << HW_RTC_MODE1_INTFLAG_CMP1_Pos)
#define HW_RTC_MODE1_INTFLAG_CMP_Pos   8            /**< \brief (HW_RTC_MODE1_INTFLAG) Compare x */
#define HW_RTC_MODE1_INTFLAG_CMP_Msk   (_U_(0x3) << HW_RTC_MODE1_INTFLAG_CMP_Pos)
#define HW_RTC_MODE1_INTFLAG_CMP(value) (HW_RTC_MODE1_INTFLAG_CMP_Msk & ((value) << HW_RTC_MODE1_INTFLAG_CMP_Pos))
#define HW_RTC_MODE1_INTFLAG_OVF_Pos   15           /**< \brief (HW_RTC_MODE1_INTFLAG) Overflow */
#define HW_RTC_MODE1_INTFLAG_OVF       (_U_(0x1) << HW_RTC_MODE1_INTFLAG_OVF_Pos)
#define HW_RTC_MODE1_INTFLAG_MASK      _U_(0x83FF)  /**< \brief (HW_RTC_MODE1_INTFLAG) MASK Register */

/* -------- HW_RTC_MODE2_INTFLAG : (RTC Offset: 0x0C) (R/W 16) MODE2 MODE2 Interrupt Flag Status and Clear -------- */
typedef union { // __I to avoid read-modify-write on write-to-clear register
  struct {
    __I uint16_t PER0:1;           /*!< bit:      0  Periodic Interval 0                */
    __I uint16_t PER1:1;           /*!< bit:      1  Periodic Interval 1                */
    __I uint16_t PER2:1;           /*!< bit:      2  Periodic Interval 2                */
    __I uint16_t PER3:1;           /*!< bit:      3  Periodic Interval 3                */
    __I uint16_t PER4:1;           /*!< bit:      4  Periodic Interval 4                */
    __I uint16_t PER5:1;           /*!< bit:      5  Periodic Interval 5                */
    __I uint16_t PER6:1;           /*!< bit:      6  Periodic Interval 6                */
    __I uint16_t PER7:1;           /*!< bit:      7  Periodic Interval 7                */
    __I uint16_t ALARM0:1;         /*!< bit:      8  Alarm 0                            */
    __I uint16_t :6;               /*!< bit:  9..14  Reserved                           */
    __I uint16_t OVF:1;            /*!< bit:     15  Overflow                           */
  } bit;                       /*!< Structure used for bit  access                  */
  struct {
    __I uint16_t PER:8;            /*!< bit:  0.. 7  Periodic Interval x                */
    __I uint16_t ALARM:1;          /*!< bit:      8  Alarm x                            */
    __I uint16_t :7;               /*!< bit:  9..15  Reserved                           */
  } vec;                       /*!< Structure used for vec  access                  */
  uint16_t reg;                /*!< Type      used for register access              */
} HW_RTC_MODE2_INTFLAG_Type;

#define HW_RTC_MODE2_INTFLAG_OFFSET    0x0C         /**< \brief (HW_RTC_MODE2_INTFLAG offset) MODE2 Interrupt Flag Status and Clear */
#define HW_RTC_MODE2_INTFLAG_RESETVALUE _U_(0x0000)  /**< \brief (HW_RTC_MODE2_INTFLAG reset_value) MODE2 Interrupt Flag Status and Clear */

#define HW_RTC_MODE2_INTFLAG_PER0_Pos  0            /**< \brief (HW_RTC_MODE2_INTFLAG) Periodic Interval 0 */
#define HW_RTC_MODE2_INTFLAG_PER0      (_U_(1) << HW_RTC_MODE2_INTFLAG_PER0_Pos)
#define HW_RTC_MODE2_INTFLAG_PER1_Pos  1            /**< \brief (HW_RTC_MODE2_INTFLAG) Periodic Interval 1 */
#define HW_RTC_MODE2_INTFLAG_PER1      (_U_(1) << HW_RTC_MODE2_INTFLAG_PER1_Pos)
#define HW_RTC_MODE2_INTFLAG_PER2_Pos  2            /**< \brief (HW_RTC_MODE2_INTFLAG) Periodic Interval 2 */
#define HW_RTC_MODE2_INTFLAG_PER2      (_U_(1) << HW_RTC_MODE2_INTFLAG_PER2_Pos)
#define HW_RTC_MODE2_INTFLAG_PER3_Pos  3            /**< \brief (HW_RTC_MODE2_INTFLAG) Periodic Interval 3 */
#define HW_RTC_MODE2_INTFLAG_PER3      (_U_(1) << HW_RTC_MODE2_INTFLAG_PER3_Pos)
#define HW_RTC_MODE2_INTFLAG_PER4_Pos  4            /**< \brief (HW_RTC_MODE2_INTFLAG) Periodic Interval 4 */
#define HW_RTC_MODE2_INTFLAG_PER4      (_U_(1) << HW_RTC_MODE2_INTFLAG_PER4_Pos)
#define HW_RTC_MODE2_INTFLAG_PER5_Pos  5            /**< \brief (HW_RTC_MODE2_INTFLAG) Periodic Interval 5 */
#define HW_RTC_MODE2_INTFLAG_PER5      (_U_(1) << HW_RTC_MODE2_INTFLAG_PER5_Pos)
#define HW_RTC_MODE2_INTFLAG_PER6_Pos  6            /**< \brief (HW_RTC_MODE2_INTFLAG) Periodic Interval 6 */
#define HW_RTC_MODE2_INTFLAG_PER6      (_U_(1) << HW_RTC_MODE2_INTFLAG_PER6_Pos)
#define HW_RTC_MODE2_INTFLAG_PER7_Pos  7            /**< \brief (HW_RTC_MODE2_INTFLAG) Periodic Interval 7 */
#define HW_RTC_MODE2_INTFLAG_PER7      (_U_(1) << HW_RTC_MODE2_INTFLAG_PER7_Pos)
#define HW_RTC_MODE2_INTFLAG_PER_Pos   0            /**< \brief (HW_RTC_MODE2_INTFLAG) Periodic Interval x */
#define HW_RTC_MODE2_INTFLAG_PER_Msk   (_U_(0xFF) << HW_RTC_MODE2_INTFLAG_PER_Pos)
#define HW_RTC_MODE2_INTFLAG_PER(value) (HW_RTC_MODE2_INTFLAG_PER_Msk & ((value) << HW_RTC_MODE2_INTFLAG_PER_Pos))
#define HW_RTC_MODE2_INTFLAG_ALARM0_Pos 8            /**< \brief (HW_RTC_MODE2_INTFLAG) Alarm 0 */
#define HW_RTC_MODE2_INTFLAG_ALARM0    (_U_(1) << HW_RTC_MODE2_INTFLAG_ALARM0_Pos)
#define HW_RTC_MODE2_INTFLAG_ALARM_Pos 8            /**< \brief (HW_RTC_MODE2_INTFLAG) Alarm x */
#define HW_RTC_MODE2_INTFLAG_ALARM_Msk (_U_(0x1) << HW_RTC_MODE2_INTFLAG_ALARM_Pos)
#define HW_RTC_MODE2_INTFLAG_ALARM(value) (HW_RTC_MODE2_INTFLAG_ALARM_Msk & ((value) << HW_RTC_MODE2_INTFLAG_ALARM_Pos))
#define HW_RTC_MODE2_INTFLAG_OVF_Pos   15           /**< \brief (HW_RTC_MODE2_INTFLAG) Overflow */
#define HW_RTC_MODE2_INTFLAG_OVF       (_U_(0x1) << HW_RTC_MODE2_INTFLAG_OVF_Pos)
#define HW_RTC_MODE2_INTFLAG_MASK      _U_(0x81FF)  /**< \brief (HW_RTC_MODE2_INTFLAG) MASK Register */

/* -------- HW_RTC_DBGCTRL : (RTC Offset: 0x0E) (R/W  8) Debug Control -------- */
typedef union {
  struct {
    uint8_t  DBGRUN:1;         /*!< bit:      0  Run During Debug                   */
    uint8_t  :7;               /*!< bit:  1.. 7  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} HW_RTC_DBGCTRL_Type;

#define HW_RTC_DBGCTRL_OFFSET          0x0E         /**< \brief (HW_RTC_DBGCTRL offset) Debug Control */
#define HW_RTC_DBGCTRL_RESETVALUE      _U_(0x00)    /**< \brief (HW_RTC_DBGCTRL reset_value) Debug Control */

#define HW_RTC_DBGCTRL_DBGRUN_Pos      0            /**< \brief (HW_RTC_DBGCTRL) Run During Debug */
#define HW_RTC_DBGCTRL_DBGRUN          (_U_(0x1) << HW_RTC_DBGCTRL_DBGRUN_Pos)
#define HW_RTC_DBGCTRL_MASK            _U_(0x01)    /**< \brief (HW_RTC_DBGCTRL) MASK Register */

/* -------- HW_RTC_MODE0_SYNCBUSY : (RTC Offset: 0x10) (R/  32) MODE0 MODE0 Synchronization Busy Status -------- */
typedef union {
  struct {
    uint32_t SWRST:1;          /*!< bit:      0  Software Reset Busy                */
    uint32_t ENABLE:1;         /*!< bit:      1  Enable Bit Busy                    */
    uint32_t FREQCORR:1;       /*!< bit:      2  FREQCORR Register Busy             */
    uint32_t COUNT:1;          /*!< bit:      3  COUNT Register Busy                */
    uint32_t :1;               /*!< bit:      4  Reserved                           */
    uint32_t COMP0:1;          /*!< bit:      5  COMP 0 Register Busy               */
    uint32_t :9;               /*!< bit:  6..14  Reserved                           */
    uint32_t COUNTSYNC:1;      /*!< bit:     15  Count Read Synchronization Enable Bit Busy */
    uint32_t :16;              /*!< bit: 16..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  struct {
    uint32_t :5;               /*!< bit:  0.. 4  Reserved                           */
    uint32_t COMP:1;           /*!< bit:      5  COMP x Register Busy               */
    uint32_t :26;              /*!< bit:  6..31  Reserved                           */
  } vec;                       /*!< Structure used for vec  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} HW_RTC_MODE0_SYNCBUSY_Type;

#define HW_RTC_MODE0_SYNCBUSY_OFFSET   0x10         /**< \brief (HW_RTC_MODE0_SYNCBUSY offset) MODE0 Synchronization Busy Status */
#define HW_RTC_MODE0_SYNCBUSY_RESETVALUE _U_(0x00000000) /**< \brief (HW_RTC_MODE0_SYNCBUSY reset_value) MODE0 Synchronization Busy Status */

#define HW_RTC_MODE0_SYNCBUSY_SWRST_Pos 0            /**< \brief (HW_RTC_MODE0_SYNCBUSY) Software Reset Busy */
#define HW_RTC_MODE0_SYNCBUSY_SWRST    (_U_(0x1) << HW_RTC_MODE0_SYNCBUSY_SWRST_Pos)
#define HW_RTC_MODE0_SYNCBUSY_ENABLE_Pos 1            /**< \brief (HW_RTC_MODE0_SYNCBUSY) Enable Bit Busy */
#define HW_RTC_MODE0_SYNCBUSY_ENABLE   (_U_(0x1) << HW_RTC_MODE0_SYNCBUSY_ENABLE_Pos)
#define HW_RTC_MODE0_SYNCBUSY_FREQCORR_Pos 2            /**< \brief (HW_RTC_MODE0_SYNCBUSY) FREQCORR Register Busy */
#define HW_RTC_MODE0_SYNCBUSY_FREQCORR (_U_(0x1) << HW_RTC_MODE0_SYNCBUSY_FREQCORR_Pos)
#define HW_RTC_MODE0_SYNCBUSY_COUNT_Pos 3            /**< \brief (HW_RTC_MODE0_SYNCBUSY) COUNT Register Busy */
#define HW_RTC_MODE0_SYNCBUSY_COUNT    (_U_(0x1) << HW_RTC_MODE0_SYNCBUSY_COUNT_Pos)
#define HW_RTC_MODE0_SYNCBUSY_COMP0_Pos 5            /**< \brief (HW_RTC_MODE0_SYNCBUSY) COMP 0 Register Busy */
#define HW_RTC_MODE0_SYNCBUSY_COMP0    (_U_(1) << HW_RTC_MODE0_SYNCBUSY_COMP0_Pos)
#define HW_RTC_MODE0_SYNCBUSY_COMP_Pos 5            /**< \brief (HW_RTC_MODE0_SYNCBUSY) COMP x Register Busy */
#define HW_RTC_MODE0_SYNCBUSY_COMP_Msk (_U_(0x1) << HW_RTC_MODE0_SYNCBUSY_COMP_Pos)
#define HW_RTC_MODE0_SYNCBUSY_COMP(value) (HW_RTC_MODE0_SYNCBUSY_COMP_Msk & ((value) << HW_RTC_MODE0_SYNCBUSY_COMP_Pos))
#define HW_RTC_MODE0_SYNCBUSY_COUNTSYNC_Pos 15           /**< \brief (HW_RTC_MODE0_SYNCBUSY) Count Read Synchronization Enable Bit Busy */
#define HW_RTC_MODE0_SYNCBUSY_COUNTSYNC (_U_(0x1) << HW_RTC_MODE0_SYNCBUSY_COUNTSYNC_Pos)
#define HW_RTC_MODE0_SYNCBUSY_MASK     _U_(0x0000802F) /**< \brief (HW_RTC_MODE0_SYNCBUSY) MASK Register */

/* -------- HW_RTC_MODE1_SYNCBUSY : (RTC Offset: 0x10) (R/  32) MODE1 MODE1 Synchronization Busy Status -------- */
typedef union {
  struct {
    uint32_t SWRST:1;          /*!< bit:      0  Software Reset Bit Busy            */
    uint32_t ENABLE:1;         /*!< bit:      1  Enable Bit Busy                    */
    uint32_t FREQCORR:1;       /*!< bit:      2  FREQCORR Register Busy             */
    uint32_t COUNT:1;          /*!< bit:      3  COUNT Register Busy                */
    uint32_t PER:1;            /*!< bit:      4  PER Register Busy                  */
    uint32_t COMP0:1;          /*!< bit:      5  COMP 0 Register Busy               */
    uint32_t COMP1:1;          /*!< bit:      6  COMP 1 Register Busy               */
    uint32_t :8;               /*!< bit:  7..14  Reserved                           */
    uint32_t COUNTSYNC:1;      /*!< bit:     15  Count Read Synchronization Enable Bit Busy */
    uint32_t :16;              /*!< bit: 16..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  struct {
    uint32_t :5;               /*!< bit:  0.. 4  Reserved                           */
    uint32_t COMP:2;           /*!< bit:  5.. 6  COMP x Register Busy               */
    uint32_t :25;              /*!< bit:  7..31  Reserved                           */
  } vec;                       /*!< Structure used for vec  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} HW_RTC_MODE1_SYNCBUSY_Type;

#define HW_RTC_MODE1_SYNCBUSY_OFFSET   0x10         /**< \brief (HW_RTC_MODE1_SYNCBUSY offset) MODE1 Synchronization Busy Status */
#define HW_RTC_MODE1_SYNCBUSY_RESETVALUE _U_(0x00000000) /**< \brief (HW_RTC_MODE1_SYNCBUSY reset_value) MODE1 Synchronization Busy Status */

#define HW_RTC_MODE1_SYNCBUSY_SWRST_Pos 0            /**< \brief (HW_RTC_MODE1_SYNCBUSY) Software Reset Bit Busy */
#define HW_RTC_MODE1_SYNCBUSY_SWRST    (_U_(0x1) << HW_RTC_MODE1_SYNCBUSY_SWRST_Pos)
#define HW_RTC_MODE1_SYNCBUSY_ENABLE_Pos 1            /**< \brief (HW_RTC_MODE1_SYNCBUSY) Enable Bit Busy */
#define HW_RTC_MODE1_SYNCBUSY_ENABLE   (_U_(0x1) << HW_RTC_MODE1_SYNCBUSY_ENABLE_Pos)
#define HW_RTC_MODE1_SYNCBUSY_FREQCORR_Pos 2            /**< \brief (HW_RTC_MODE1_SYNCBUSY) FREQCORR Register Busy */
#define HW_RTC_MODE1_SYNCBUSY_FREQCORR (_U_(0x1) << HW_RTC_MODE1_SYNCBUSY_FREQCORR_Pos)
#define HW_RTC_MODE1_SYNCBUSY_COUNT_Pos 3            /**< \brief (HW_RTC_MODE1_SYNCBUSY) COUNT Register Busy */
#define HW_RTC_MODE1_SYNCBUSY_COUNT    (_U_(0x1) << HW_RTC_MODE1_SYNCBUSY_COUNT_Pos)
#define HW_RTC_MODE1_SYNCBUSY_PER_Pos  4            /**< \brief (HW_RTC_MODE1_SYNCBUSY) PER Register Busy */
#define HW_RTC_MODE1_SYNCBUSY_PER      (_U_(0x1) << HW_RTC_MODE1_SYNCBUSY_PER_Pos)
#define HW_RTC_MODE1_SYNCBUSY_COMP0_Pos 5            /**< \brief (HW_RTC_MODE1_SYNCBUSY) COMP 0 Register Busy */
#define HW_RTC_MODE1_SYNCBUSY_COMP0    (_U_(1) << HW_RTC_MODE1_SYNCBUSY_COMP0_Pos)
#define HW_RTC_MODE1_SYNCBUSY_COMP1_Pos 6            /**< \brief (HW_RTC_MODE1_SYNCBUSY) COMP 1 Register Busy */
#define HW_RTC_MODE1_SYNCBUSY_COMP1    (_U_(1) << HW_RTC_MODE1_SYNCBUSY_COMP1_Pos)
#define HW_RTC_MODE1_SYNCBUSY_COMP_Pos 5            /**< \brief (HW_RTC_MODE1_SYNCBUSY) COMP x Register Busy */
#define HW_RTC_MODE1_SYNCBUSY_COMP_Msk (_U_(0x3) << HW_RTC_MODE1_SYNCBUSY_COMP_Pos)
#define HW_RTC_MODE1_SYNCBUSY_COMP(value) (HW_RTC_MODE1_SYNCBUSY_COMP_Msk & ((value) << HW_RTC_MODE1_SYNCBUSY_COMP_Pos))
#define HW_RTC_MODE1_SYNCBUSY_COUNTSYNC_Pos 15           /**< \brief (HW_RTC_MODE1_SYNCBUSY) Count Read Synchronization Enable Bit Busy */
#define HW_RTC_MODE1_SYNCBUSY_COUNTSYNC (_U_(0x1) << HW_RTC_MODE1_SYNCBUSY_COUNTSYNC_Pos)
#define HW_RTC_MODE1_SYNCBUSY_MASK     _U_(0x0000807F) /**< \brief (HW_RTC_MODE1_SYNCBUSY) MASK Register */

/* -------- HW_RTC_MODE2_SYNCBUSY : (RTC Offset: 0x10) (R/  32) MODE2 MODE2 Synchronization Busy Status -------- */
typedef union {
  struct {
    uint32_t SWRST:1;          /*!< bit:      0  Software Reset Bit Busy            */
    uint32_t ENABLE:1;         /*!< bit:      1  Enable Bit Busy                    */
    uint32_t FREQCORR:1;       /*!< bit:      2  FREQCORR Register Busy             */
    uint32_t CLOCK:1;          /*!< bit:      3  CLOCK Register Busy                */
    uint32_t :1;               /*!< bit:      4  Reserved                           */
    uint32_t ALARM0:1;         /*!< bit:      5  ALARM 0 Register Busy              */
    uint32_t :5;               /*!< bit:  6..10  Reserved                           */
    uint32_t MASK0:1;          /*!< bit:     11  MASK 0 Register Busy               */
    uint32_t :3;               /*!< bit: 12..14  Reserved                           */
    uint32_t CLOCKSYNC:1;      /*!< bit:     15  Clock Read Synchronization Enable Bit Busy */
    uint32_t :16;              /*!< bit: 16..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  struct {
    uint32_t :5;               /*!< bit:  0.. 4  Reserved                           */
    uint32_t ALARM:1;          /*!< bit:      5  ALARM x Register Busy              */
    uint32_t :5;               /*!< bit:  6..10  Reserved                           */
    uint32_t MASK:1;           /*!< bit:     11  MASK x Register Busy               */
    uint32_t :20;              /*!< bit: 12..31  Reserved                           */
  } vec;                       /*!< Structure used for vec  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} HW_RTC_MODE2_SYNCBUSY_Type;

#define HW_RTC_MODE2_SYNCBUSY_OFFSET   0x10         /**< \brief (HW_RTC_MODE2_SYNCBUSY offset) MODE2 Synchronization Busy Status */
#define HW_RTC_MODE2_SYNCBUSY_RESETVALUE _U_(0x00000000) /**< \brief (HW_RTC_MODE2_SYNCBUSY reset_value) MODE2 Synchronization Busy Status */

#define HW_RTC_MODE2_SYNCBUSY_SWRST_Pos 0            /**< \brief (HW_RTC_MODE2_SYNCBUSY) Software Reset Bit Busy */
#define HW_RTC_MODE2_SYNCBUSY_SWRST    (_U_(0x1) << HW_RTC_MODE2_SYNCBUSY_SWRST_Pos)
#define HW_RTC_MODE2_SYNCBUSY_ENABLE_Pos 1            /**< \brief (HW_RTC_MODE2_SYNCBUSY) Enable Bit Busy */
#define HW_RTC_MODE2_SYNCBUSY_ENABLE   (_U_(0x1) << HW_RTC_MODE2_SYNCBUSY_ENABLE_Pos)
#define HW_RTC_MODE2_SYNCBUSY_FREQCORR_Pos 2            /**< \brief (HW_RTC_MODE2_SYNCBUSY) FREQCORR Register Busy */
#define HW_RTC_MODE2_SYNCBUSY_FREQCORR (_U_(0x1) << HW_RTC_MODE2_SYNCBUSY_FREQCORR_Pos)
#define HW_RTC_MODE2_SYNCBUSY_CLOCK_Pos 3            /**< \brief (HW_RTC_MODE2_SYNCBUSY) CLOCK Register Busy */
#define HW_RTC_MODE2_SYNCBUSY_CLOCK    (_U_(0x1) << HW_RTC_MODE2_SYNCBUSY_CLOCK_Pos)
#define HW_RTC_MODE2_SYNCBUSY_ALARM0_Pos 5            /**< \brief (HW_RTC_MODE2_SYNCBUSY) ALARM 0 Register Busy */
#define HW_RTC_MODE2_SYNCBUSY_ALARM0   (_U_(1) << HW_RTC_MODE2_SYNCBUSY_ALARM0_Pos)
#define HW_RTC_MODE2_SYNCBUSY_ALARM_Pos 5            /**< \brief (HW_RTC_MODE2_SYNCBUSY) ALARM x Register Busy */
#define HW_RTC_MODE2_SYNCBUSY_ALARM_Msk (_U_(0x1) << HW_RTC_MODE2_SYNCBUSY_ALARM_Pos)
#define HW_RTC_MODE2_SYNCBUSY_ALARM(value) (HW_RTC_MODE2_SYNCBUSY_ALARM_Msk & ((value) << HW_RTC_MODE2_SYNCBUSY_ALARM_Pos))
#define HW_RTC_MODE2_SYNCBUSY_MASK0_Pos 11           /**< \brief (HW_RTC_MODE2_SYNCBUSY) MASK 0 Register Busy */
#define HW_RTC_MODE2_SYNCBUSY_MASK0    (_U_(1) << HW_RTC_MODE2_SYNCBUSY_MASK0_Pos)
#define HW_RTC_MODE2_SYNCBUSY_MASK_Pos 11           /**< \brief (HW_RTC_MODE2_SYNCBUSY) MASK x Register Busy */
#define HW_RTC_MODE2_SYNCBUSY_MASK_Msk (_U_(0x1) << HW_RTC_MODE2_SYNCBUSY_MASK_Pos)
#define HW_RTC_MODE2_SYNCBUSY_MASK(value) (HW_RTC_MODE2_SYNCBUSY_MASK_Msk & ((value) << HW_RTC_MODE2_SYNCBUSY_MASK_Pos))
#define HW_RTC_MODE2_SYNCBUSY_CLOCKSYNC_Pos 15           /**< \brief (HW_RTC_MODE2_SYNCBUSY) Clock Read Synchronization Enable Bit Busy */
#define HW_RTC_MODE2_SYNCBUSY_CLOCKSYNC (_U_(0x1) << HW_RTC_MODE2_SYNCBUSY_CLOCKSYNC_Pos)
#define HW_RTC_MODE2_SYNCBUSY_MASK_    _U_(0x0000882F) /**< \brief (HW_RTC_MODE2_SYNCBUSY) MASK Register */

/* -------- HW_RTC_FREQCORR : (RTC Offset: 0x14) (R/W  8) Frequency Correction -------- */
typedef union {
  struct {
    uint8_t  VALUE:7;          /*!< bit:  0.. 6  Correction Value                   */
    uint8_t  SIGN:1;           /*!< bit:      7  Correction Sign                    */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} HW_RTC_FREQCORR_Type;

#define HW_RTC_FREQCORR_OFFSET         0x14         /**< \brief (HW_RTC_FREQCORR offset) Frequency Correction */
#define HW_RTC_FREQCORR_RESETVALUE     _U_(0x00)    /**< \brief (HW_RTC_FREQCORR reset_value) Frequency Correction */

#define HW_RTC_FREQCORR_VALUE_Pos      0            /**< \brief (HW_RTC_FREQCORR) Correction Value */
#define HW_RTC_FREQCORR_VALUE_Msk      (_U_(0x7F) << HW_RTC_FREQCORR_VALUE_Pos)
#define HW_RTC_FREQCORR_VALUE(value)   (HW_RTC_FREQCORR_VALUE_Msk & ((value) << HW_RTC_FREQCORR_VALUE_Pos))
#define HW_RTC_FREQCORR_SIGN_Pos       7            /**< \brief (HW_RTC_FREQCORR) Correction Sign */
#define HW_RTC_FREQCORR_SIGN           (_U_(0x1) << HW_RTC_FREQCORR_SIGN_Pos)
#define HW_RTC_FREQCORR_MASK           _U_(0xFF)    /**< \brief (HW_RTC_FREQCORR) MASK Register */

/* -------- HW_RTC_MODE0_COUNT : (RTC Offset: 0x18) (R/W 32) MODE0 MODE0 Counter Value -------- */
typedef union {
  struct {
    uint32_t COUNT:32;         /*!< bit:  0..31  Counter Value                      */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} HW_RTC_MODE0_COUNT_Type;

#define HW_RTC_MODE0_COUNT_OFFSET      0x18         /**< \brief (HW_RTC_MODE0_COUNT offset) MODE0 Counter Value */
#define HW_RTC_MODE0_COUNT_RESETVALUE  _U_(0x00000000) /**< \brief (HW_RTC_MODE0_COUNT reset_value) MODE0 Counter Value */

#define HW_RTC_MODE0_COUNT_COUNT_Pos   0            /**< \brief (HW_RTC_MODE0_COUNT) Counter Value */
#define HW_RTC_MODE0_COUNT_COUNT_Msk   (_U_(0xFFFFFFFF) << HW_RTC_MODE0_COUNT_COUNT_Pos)
#define HW_RTC_MODE0_COUNT_COUNT(value) (HW_RTC_MODE0_COUNT_COUNT_Msk & ((value) << HW_RTC_MODE0_COUNT_COUNT_Pos))
#define HW_RTC_MODE0_COUNT_MASK        _U_(0xFFFFFFFF) /**< \brief (HW_RTC_MODE0_COUNT) MASK Register */

/* -------- HW_RTC_MODE1_COUNT : (RTC Offset: 0x18) (R/W 16) MODE1 MODE1 Counter Value -------- */
typedef union {
  struct {
    uint16_t COUNT:16;         /*!< bit:  0..15  Counter Value                      */
  } bit;                       /*!< Structure used for bit  access                  */
  uint16_t reg;                /*!< Type      used for register access              */
} HW_RTC_MODE1_COUNT_Type;

#define HW_RTC_MODE1_COUNT_OFFSET      0x18         /**< \brief (HW_RTC_MODE1_COUNT offset) MODE1 Counter Value */
#define HW_RTC_MODE1_COUNT_RESETVALUE  _U_(0x0000)  /**< \brief (HW_RTC_MODE1_COUNT reset_value) MODE1 Counter Value */

#define HW_RTC_MODE1_COUNT_COUNT_Pos   0            /**< \brief (HW_RTC_MODE1_COUNT) Counter Value */
#define HW_RTC_MODE1_COUNT_COUNT_Msk   (_U_(0xFFFF) << HW_RTC_MODE1_COUNT_COUNT_Pos)
#define HW_RTC_MODE1_COUNT_COUNT(value) (HW_RTC_MODE1_COUNT_COUNT_Msk & ((value) << HW_RTC_MODE1_COUNT_COUNT_Pos))
#define HW_RTC_MODE1_COUNT_MASK        _U_(0xFFFF)  /**< \brief (HW_RTC_MODE1_COUNT) MASK Register */

/* -------- HW_RTC_MODE2_CLOCK : (RTC Offset: 0x18) (R/W 32) MODE2 MODE2 Clock Value -------- */
typedef union {
  struct {
    uint32_t SECOND:6;         /*!< bit:  0.. 5  Second                             */
    uint32_t MINUTE:6;         /*!< bit:  6..11  Minute                             */
    uint32_t HOUR:5;           /*!< bit: 12..16  Hour                               */
    uint32_t DAY:5;            /*!< bit: 17..21  Day                                */
    uint32_t MONTH:4;          /*!< bit: 22..25  Month                              */
    uint32_t YEAR:6;           /*!< bit: 26..31  Year                               */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} HW_RTC_MODE2_CLOCK_Type;

#define HW_RTC_MODE2_CLOCK_OFFSET      0x18         /**< \brief (HW_RTC_MODE2_CLOCK offset) MODE2 Clock Value */
#define HW_RTC_MODE2_CLOCK_RESETVALUE  _U_(0x00000000) /**< \brief (HW_RTC_MODE2_CLOCK reset_value) MODE2 Clock Value */

#define HW_RTC_MODE2_CLOCK_SECOND_Pos  0            /**< \brief (HW_RTC_MODE2_CLOCK) Second */
#define HW_RTC_MODE2_CLOCK_SECOND_Msk  (_U_(0x3F) << HW_RTC_MODE2_CLOCK_SECOND_Pos)
#define HW_RTC_MODE2_CLOCK_SECOND(value) (HW_RTC_MODE2_CLOCK_SECOND_Msk & ((value) << HW_RTC_MODE2_CLOCK_SECOND_Pos))
#define HW_RTC_MODE2_CLOCK_MINUTE_Pos  6            /**< \brief (HW_RTC_MODE2_CLOCK) Minute */
#define HW_RTC_MODE2_CLOCK_MINUTE_Msk  (_U_(0x3F) << HW_RTC_MODE2_CLOCK_MINUTE_Pos)
#define HW_RTC_MODE2_CLOCK_MINUTE(value) (HW_RTC_MODE2_CLOCK_MINUTE_Msk & ((value) << HW_RTC_MODE2_CLOCK_MINUTE_Pos))
#define HW_RTC_MODE2_CLOCK_HOUR_Pos    12           /**< \brief (HW_RTC_MODE2_CLOCK) Hour */
#define HW_RTC_MODE2_CLOCK_HOUR_Msk    (_U_(0x1F) << HW_RTC_MODE2_CLOCK_HOUR_Pos)
#define HW_RTC_MODE2_CLOCK_HOUR(value) (HW_RTC_MODE2_CLOCK_HOUR_Msk & ((value) << HW_RTC_MODE2_CLOCK_HOUR_Pos))
#define   HW_RTC_MODE2_CLOCK_HOUR_AM_Val     _U_(0x0)   /**< \brief (HW_RTC_MODE2_CLOCK) AM when CLKREP in 12-hour */
#define   HW_RTC_MODE2_CLOCK_HOUR_PM_Val     _U_(0x10)   /**< \brief (HW_RTC_MODE2_CLOCK) PM when CLKREP in 12-hour */
#define HW_RTC_MODE2_CLOCK_HOUR_AM     (HW_RTC_MODE2_CLOCK_HOUR_AM_Val   << HW_RTC_MODE2_CLOCK_HOUR_Pos)
#define HW_RTC_MODE2_CLOCK_HOUR_PM     (HW_RTC_MODE2_CLOCK_HOUR_PM_Val   << HW_RTC_MODE2_CLOCK_HOUR_Pos)
#define HW_RTC_MODE2_CLOCK_DAY_Pos     17           /**< \brief (HW_RTC_MODE2_CLOCK) Day */
#define HW_RTC_MODE2_CLOCK_DAY_Msk     (_U_(0x1F) << HW_RTC_MODE2_CLOCK_DAY_Pos)
#define HW_RTC_MODE2_CLOCK_DAY(value)  (HW_RTC_MODE2_CLOCK_DAY_Msk & ((value) << HW_RTC_MODE2_CLOCK_DAY_Pos))
#define HW_RTC_MODE2_CLOCK_MONTH_Pos   22           /**< \brief (HW_RTC_MODE2_CLOCK) Month */
#define HW_RTC_MODE2_CLOCK_MONTH_Msk   (_U_(0xF) << HW_RTC_MODE2_CLOCK_MONTH_Pos)
#define HW_RTC_MODE2_CLOCK_MONTH(value) (HW_RTC_MODE2_CLOCK_MONTH_Msk & ((value) << HW_RTC_MODE2_CLOCK_MONTH_Pos))
#define HW_RTC_MODE2_CLOCK_YEAR_Pos    26           /**< \brief (HW_RTC_MODE2_CLOCK) Year */
#define HW_RTC_MODE2_CLOCK_YEAR_Msk    (_U_(0x3F) << HW_RTC_MODE2_CLOCK_YEAR_Pos)
#define HW_RTC_MODE2_CLOCK_YEAR(value) (HW_RTC_MODE2_CLOCK_YEAR_Msk & ((value) << HW_RTC_MODE2_CLOCK_YEAR_Pos))
#define HW_RTC_MODE2_CLOCK_MASK        _U_(0xFFFFFFFF) /**< \brief (HW_RTC_MODE2_CLOCK) MASK Register */

/* -------- HW_RTC_MODE1_PER : (RTC Offset: 0x1C) (R/W 16) MODE1 MODE1 Counter Period -------- */
typedef union {
  struct {
    uint16_t PER:16;           /*!< bit:  0..15  Counter Period                     */
  } bit;                       /*!< Structure used for bit  access                  */
  uint16_t reg;                /*!< Type      used for register access              */
} HW_RTC_MODE1_PER_Type;

#define HW_RTC_MODE1_PER_OFFSET        0x1C         /**< \brief (HW_RTC_MODE1_PER offset) MODE1 Counter Period */
#define HW_RTC_MODE1_PER_RESETVALUE    _U_(0x0000)  /**< \brief (HW_RTC_MODE1_PER reset_value) MODE1 Counter Period */

#define HW_RTC_MODE1_PER_PER_Pos       0            /**< \brief (HW_RTC_MODE1_PER) Counter Period */
#define HW_RTC_MODE1_PER_PER_Msk       (_U_(0xFFFF) << HW_RTC_MODE1_PER_PER_Pos)
#define HW_RTC_MODE1_PER_PER(value)    (HW_RTC_MODE1_PER_PER_Msk & ((value) << HW_RTC_MODE1_PER_PER_Pos))
#define HW_RTC_MODE1_PER_MASK          _U_(0xFFFF)  /**< \brief (HW_RTC_MODE1_PER) MASK Register */

/* -------- HW_RTC_MODE0_COMP : (RTC Offset: 0x20) (R/W 32) MODE0 MODE0 Compare n Value -------- */
typedef union {
  struct {
    uint32_t COMP:32;          /*!< bit:  0..31  Compare Value                      */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} HW_RTC_MODE0_COMP_Type;

#define HW_RTC_MODE0_COMP_OFFSET       0x20         /**< \brief (HW_RTC_MODE0_COMP offset) MODE0 Compare n Value */
#define HW_RTC_MODE0_COMP_RESETVALUE   _U_(0x00000000) /**< \brief (HW_RTC_MODE0_COMP reset_value) MODE0 Compare n Value */

#define HW_RTC_MODE0_COMP_COMP_Pos     0            /**< \brief (HW_RTC_MODE0_COMP) Compare Value */
#define HW_RTC_MODE0_COMP_COMP_Msk     (_U_(0xFFFFFFFF) << HW_RTC_MODE0_COMP_COMP_Pos)
#define HW_RTC_MODE0_COMP_COMP(value)  (HW_RTC_MODE0_COMP_COMP_Msk & ((value) << HW_RTC_MODE0_COMP_COMP_Pos))
#define HW_RTC_MODE0_COMP_MASK         _U_(0xFFFFFFFF) /**< \brief (HW_RTC_MODE0_COMP) MASK Register */

/* -------- HW_RTC_MODE1_COMP : (RTC Offset: 0x20) (R/W 16) MODE1 MODE1 Compare n Value -------- */
typedef union {
  struct {
    uint16_t COMP:16;          /*!< bit:  0..15  Compare Value                      */
  } bit;                       /*!< Structure used for bit  access                  */
  uint16_t reg;                /*!< Type      used for register access              */
} HW_RTC_MODE1_COMP_Type;

#define HW_RTC_MODE1_COMP_OFFSET       0x20         /**< \brief (HW_RTC_MODE1_COMP offset) MODE1 Compare n Value */
#define HW_RTC_MODE1_COMP_RESETVALUE   _U_(0x0000)  /**< \brief (HW_RTC_MODE1_COMP reset_value) MODE1 Compare n Value */

#define HW_RTC_MODE1_COMP_COMP_Pos     0            /**< \brief (HW_RTC_MODE1_COMP) Compare Value */
#define HW_RTC_MODE1_COMP_COMP_Msk     (_U_(0xFFFF) << HW_RTC_MODE1_COMP_COMP_Pos)
#define HW_RTC_MODE1_COMP_COMP(value)  (HW_RTC_MODE1_COMP_COMP_Msk & ((value) << HW_RTC_MODE1_COMP_COMP_Pos))
#define HW_RTC_MODE1_COMP_MASK         _U_(0xFFFF)  /**< \brief (HW_RTC_MODE1_COMP) MASK Register */

/* -------- HW_RTC_MODE2_ALARM : (RTC Offset: 0x20) (R/W 32) MODE2 MODE2_ALARM Alarm n Value -------- */
typedef union {
  struct {
    uint32_t SECOND:6;         /*!< bit:  0.. 5  Second                             */
    uint32_t MINUTE:6;         /*!< bit:  6..11  Minute                             */
    uint32_t HOUR:5;           /*!< bit: 12..16  Hour                               */
    uint32_t DAY:5;            /*!< bit: 17..21  Day                                */
    uint32_t MONTH:4;          /*!< bit: 22..25  Month                              */
    uint32_t YEAR:6;           /*!< bit: 26..31  Year                               */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} HW_RTC_MODE2_ALARM_Type;

#define HW_RTC_MODE2_ALARM_OFFSET      0x20         /**< \brief (HW_RTC_MODE2_ALARM offset) MODE2_ALARM Alarm n Value */
#define HW_RTC_MODE2_ALARM_RESETVALUE  _U_(0x00000000) /**< \brief (HW_RTC_MODE2_ALARM reset_value) MODE2_ALARM Alarm n Value */

#define HW_RTC_MODE2_ALARM_SECOND_Pos  0            /**< \brief (HW_RTC_MODE2_ALARM) Second */
#define HW_RTC_MODE2_ALARM_SECOND_Msk  (_U_(0x3F) << HW_RTC_MODE2_ALARM_SECOND_Pos)
#define HW_RTC_MODE2_ALARM_SECOND(value) (HW_RTC_MODE2_ALARM_SECOND_Msk & ((value) << HW_RTC_MODE2_ALARM_SECOND_Pos))
#define HW_RTC_MODE2_ALARM_MINUTE_Pos  6            /**< \brief (HW_RTC_MODE2_ALARM) Minute */
#define HW_RTC_MODE2_ALARM_MINUTE_Msk  (_U_(0x3F) << HW_RTC_MODE2_ALARM_MINUTE_Pos)
#define HW_RTC_MODE2_ALARM_MINUTE(value) (HW_RTC_MODE2_ALARM_MINUTE_Msk & ((value) << HW_RTC_MODE2_ALARM_MINUTE_Pos))
#define HW_RTC_MODE2_ALARM_HOUR_Pos    12           /**< \brief (HW_RTC_MODE2_ALARM) Hour */
#define HW_RTC_MODE2_ALARM_HOUR_Msk    (_U_(0x1F) << HW_RTC_MODE2_ALARM_HOUR_Pos)
#define HW_RTC_MODE2_ALARM_HOUR(value) (HW_RTC_MODE2_ALARM_HOUR_Msk & ((value) << HW_RTC_MODE2_ALARM_HOUR_Pos))
#define   HW_RTC_MODE2_ALARM_HOUR_AM_Val     _U_(0x0)   /**< \brief (HW_RTC_MODE2_ALARM) Morning hour */
#define   HW_RTC_MODE2_ALARM_HOUR_PM_Val     _U_(0x10)   /**< \brief (HW_RTC_MODE2_ALARM) Afternoon hour */
#define HW_RTC_MODE2_ALARM_HOUR_AM     (HW_RTC_MODE2_ALARM_HOUR_AM_Val   << HW_RTC_MODE2_ALARM_HOUR_Pos)
#define HW_RTC_MODE2_ALARM_HOUR_PM     (HW_RTC_MODE2_ALARM_HOUR_PM_Val   << HW_RTC_MODE2_ALARM_HOUR_Pos)
#define HW_RTC_MODE2_ALARM_DAY_Pos     17           /**< \brief (HW_RTC_MODE2_ALARM) Day */
#define HW_RTC_MODE2_ALARM_DAY_Msk     (_U_(0x1F) << HW_RTC_MODE2_ALARM_DAY_Pos)
#define HW_RTC_MODE2_ALARM_DAY(value)  (HW_RTC_MODE2_ALARM_DAY_Msk & ((value) << HW_RTC_MODE2_ALARM_DAY_Pos))
#define HW_RTC_MODE2_ALARM_MONTH_Pos   22           /**< \brief (HW_RTC_MODE2_ALARM) Month */
#define HW_RTC_MODE2_ALARM_MONTH_Msk   (_U_(0xF) << HW_RTC_MODE2_ALARM_MONTH_Pos)
#define HW_RTC_MODE2_ALARM_MONTH(value) (HW_RTC_MODE2_ALARM_MONTH_Msk & ((value) << HW_RTC_MODE2_ALARM_MONTH_Pos))
#define HW_RTC_MODE2_ALARM_YEAR_Pos    26           /**< \brief (HW_RTC_MODE2_ALARM) Year */
#define HW_RTC_MODE2_ALARM_YEAR_Msk    (_U_(0x3F) << HW_RTC_MODE2_ALARM_YEAR_Pos)
#define HW_RTC_MODE2_ALARM_YEAR(value) (HW_RTC_MODE2_ALARM_YEAR_Msk & ((value) << HW_RTC_MODE2_ALARM_YEAR_Pos))
#define HW_RTC_MODE2_ALARM_MASK        _U_(0xFFFFFFFF) /**< \brief (HW_RTC_MODE2_ALARM) MASK Register */

/* -------- HW_RTC_MODE2_MASK : (RTC Offset: 0x24) (R/W  8) MODE2 MODE2_ALARM Alarm n Mask -------- */
typedef union {
  struct {
    uint8_t  SEL:3;            /*!< bit:  0.. 2  Alarm Mask Selection               */
    uint8_t  :5;               /*!< bit:  3.. 7  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} HW_RTC_MODE2_MASK_Type;

#define HW_RTC_MODE2_MASK_OFFSET       0x24         /**< \brief (HW_RTC_MODE2_MASK offset) MODE2_ALARM Alarm n Mask */
#define HW_RTC_MODE2_MASK_RESETVALUE   _U_(0x00)    /**< \brief (HW_RTC_MODE2_MASK reset_value) MODE2_ALARM Alarm n Mask */

#define HW_RTC_MODE2_MASK_SEL_Pos      0            /**< \brief (HW_RTC_MODE2_MASK) Alarm Mask Selection */
#define HW_RTC_MODE2_MASK_SEL_Msk      (_U_(0x7) << HW_RTC_MODE2_MASK_SEL_Pos)
#define HW_RTC_MODE2_MASK_SEL(value)   (HW_RTC_MODE2_MASK_SEL_Msk & ((value) << HW_RTC_MODE2_MASK_SEL_Pos))
#define   HW_RTC_MODE2_MASK_SEL_OFF_Val      _U_(0x0)   /**< \brief (HW_RTC_MODE2_MASK) Alarm Disabled */
#define   HW_RTC_MODE2_MASK_SEL_SS_Val       _U_(0x1)   /**< \brief (HW_RTC_MODE2_MASK) Match seconds only */
#define   HW_RTC_MODE2_MASK_SEL_MMSS_Val     _U_(0x2)   /**< \brief (HW_RTC_MODE2_MASK) Match seconds and minutes only */
#define   HW_RTC_MODE2_MASK_SEL_HHMMSS_Val   _U_(0x3)   /**< \brief (HW_RTC_MODE2_MASK) Match seconds, minutes, and hours only */
#define   HW_RTC_MODE2_MASK_SEL_DDHHMMSS_Val _U_(0x4)   /**< \brief (HW_RTC_MODE2_MASK) Match seconds, minutes, hours, and days only */
#define   HW_RTC_MODE2_MASK_SEL_MMDDHHMMSS_Val _U_(0x5)   /**< \brief (HW_RTC_MODE2_MASK) Match seconds, minutes, hours, days, and months only */
#define   HW_RTC_MODE2_MASK_SEL_YYMMDDHHMMSS_Val _U_(0x6)   /**< \brief (HW_RTC_MODE2_MASK) Match seconds, minutes, hours, days, months, and years */
#define HW_RTC_MODE2_MASK_SEL_OFF      (HW_RTC_MODE2_MASK_SEL_OFF_Val    << HW_RTC_MODE2_MASK_SEL_Pos)
#define HW_RTC_MODE2_MASK_SEL_SS       (HW_RTC_MODE2_MASK_SEL_SS_Val     << HW_RTC_MODE2_MASK_SEL_Pos)
#define HW_RTC_MODE2_MASK_SEL_MMSS     (HW_RTC_MODE2_MASK_SEL_MMSS_Val   << HW_RTC_MODE2_MASK_SEL_Pos)
#define HW_RTC_MODE2_MASK_SEL_HHMMSS   (HW_RTC_MODE2_MASK_SEL_HHMMSS_Val << HW_RTC_MODE2_MASK_SEL_Pos)
#define HW_RTC_MODE2_MASK_SEL_DDHHMMSS (HW_RTC_MODE2_MASK_SEL_DDHHMMSS_Val << HW_RTC_MODE2_MASK_SEL_Pos)
#define HW_RTC_MODE2_MASK_SEL_MMDDHHMMSS (HW_RTC_MODE2_MASK_SEL_MMDDHHMMSS_Val << HW_RTC_MODE2_MASK_SEL_Pos)
#define HW_RTC_MODE2_MASK_SEL_YYMMDDHHMMSS (HW_RTC_MODE2_MASK_SEL_YYMMDDHHMMSS_Val << HW_RTC_MODE2_MASK_SEL_Pos)
#define HW_RTC_MODE2_MASK_MASK         _U_(0x07)    /**< \brief (HW_RTC_MODE2_MASK) MASK Register */

/* -------- HW_RTC_GP : (RTC Offset: 0x40) (R/W 32) General Purpose -------- */
typedef union {
  uint32_t reg;                /*!< Type      used for register access              */
} HW_RTC_GP_Type;

#define HW_RTC_GP_OFFSET               0x40         /**< \brief (HW_RTC_GP offset) General Purpose */
#define HW_RTC_GP_RESETVALUE           _U_(0x00000000) /**< \brief (HW_RTC_GP reset_value) General Purpose */
#define HW_RTC_GP_MASK                 _U_(0xFFFFFFFF) /**< \brief (HW_RTC_GP) MASK Register */

/** \brief RtcMode2Alarm hardware registers */
typedef struct {
  __IO HW_RTC_MODE2_ALARM_Type      ALARM;       /**< \brief Offset: 0x00 (R/W 32) MODE2_ALARM Alarm n Value */
  __IO HW_RTC_MODE2_MASK_Type       MASK;        /**< \brief Offset: 0x04 (R/W  8) MODE2_ALARM Alarm n Mask */
       RoReg8                    Reserved1[0x3];
} RtcMode2Alarm;

/** \brief HW_RTC_MODE0 hardware registers */
typedef struct { /* 32-bit Counter with Single 32-bit Compare */
  __IO HW_RTC_MODE0_CTRLA_Type      CTRLA;       /**< \brief Offset: 0x00 (R/W 16) MODE0 Control A */
       RoReg8                    Reserved1[0x2];
  __IO HW_RTC_MODE0_EVCTRL_Type     EVCTRL;      /**< \brief Offset: 0x04 (R/W 32) MODE0 Event Control */
  __IO HW_RTC_MODE0_INTENCLR_Type   INTENCLR;    /**< \brief Offset: 0x08 (R/W 16) MODE0 Interrupt Enable Clear */
  __IO HW_RTC_MODE0_INTENSET_Type   INTENSET;    /**< \brief Offset: 0x0A (R/W 16) MODE0 Interrupt Enable Set */
  __IO HW_RTC_MODE0_INTFLAG_Type    INTFLAG;     /**< \brief Offset: 0x0C (R/W 16) MODE0 Interrupt Flag Status and Clear */
  __IO HW_RTC_DBGCTRL_Type          DBGCTRL;     /**< \brief Offset: 0x0E (R/W  8) Debug Control */
       RoReg8                    Reserved2[0x1];
  __I  HW_RTC_MODE0_SYNCBUSY_Type   SYNCBUSY;    /**< \brief Offset: 0x10 (R/  32) MODE0 Synchronization Busy Status */
  __IO HW_RTC_FREQCORR_Type         FREQCORR;    /**< \brief Offset: 0x14 (R/W  8) Frequency Correction */
       RoReg8                    Reserved3[0x3];
  __IO HW_RTC_MODE0_COUNT_Type      COUNT;       /**< \brief Offset: 0x18 (R/W 32) MODE0 Counter Value */
       RoReg8                    Reserved4[0x4];
  __IO HW_RTC_MODE0_COMP_Type       COMP[1];     /**< \brief Offset: 0x20 (R/W 32) MODE0 Compare n Value */
       RoReg8                    Reserved5[0x1C];
  __IO HW_RTC_GP_Type               GP[4];       /**< \brief Offset: 0x40 (R/W 32) General Purpose */
} RtcMode0;

/** \brief HW_RTC_MODE1 hardware registers */
typedef struct { /* 16-bit Counter with Two 16-bit Compares */
  __IO HW_RTC_MODE1_CTRLA_Type      CTRLA;       /**< \brief Offset: 0x00 (R/W 16) MODE1 Control A */
       RoReg8                    Reserved1[0x2];
  __IO HW_RTC_MODE1_EVCTRL_Type     EVCTRL;      /**< \brief Offset: 0x04 (R/W 32) MODE1 Event Control */
  __IO HW_RTC_MODE1_INTENCLR_Type   INTENCLR;    /**< \brief Offset: 0x08 (R/W 16) MODE1 Interrupt Enable Clear */
  __IO HW_RTC_MODE1_INTENSET_Type   INTENSET;    /**< \brief Offset: 0x0A (R/W 16) MODE1 Interrupt Enable Set */
  __IO HW_RTC_MODE1_INTFLAG_Type    INTFLAG;     /**< \brief Offset: 0x0C (R/W 16) MODE1 Interrupt Flag Status and Clear */
  __IO HW_RTC_DBGCTRL_Type          DBGCTRL;     /**< \brief Offset: 0x0E (R/W  8) Debug Control */
       RoReg8                    Reserved2[0x1];
  __I  HW_RTC_MODE1_SYNCBUSY_Type   SYNCBUSY;    /**< \brief Offset: 0x10 (R/  32) MODE1 Synchronization Busy Status */
  __IO HW_RTC_FREQCORR_Type         FREQCORR;    /**< \brief Offset: 0x14 (R/W  8) Frequency Correction */
       RoReg8                    Reserved3[0x3];
  __IO HW_RTC_MODE1_COUNT_Type      COUNT;       /**< \brief Offset: 0x18 (R/W 16) MODE1 Counter Value */
       RoReg8                    Reserved4[0x2];
  __IO HW_RTC_MODE1_PER_Type        PER;         /**< \brief Offset: 0x1C (R/W 16) MODE1 Counter Period */
       RoReg8                    Reserved5[0x2];
  __IO HW_RTC_MODE1_COMP_Type       COMP[2];     /**< \brief Offset: 0x20 (R/W 16) MODE1 Compare n Value */
       RoReg8                    Reserved6[0x1C];
  __IO HW_RTC_GP_Type               GP[4];       /**< \brief Offset: 0x40 (R/W 32) General Purpose */
} RtcMode1;

/** \brief HW_RTC_MODE2 hardware registers */
typedef struct { /* Clock/Calendar with Alarm */
  __IO HW_RTC_MODE2_CTRLA_Type      CTRLA;       /**< \brief Offset: 0x00 (R/W 16) MODE2 Control A */
       RoReg8                    Reserved1[0x2];
  __IO HW_RTC_MODE2_EVCTRL_Type     EVCTRL;      /**< \brief Offset: 0x04 (R/W 32) MODE2 Event Control */
  __IO HW_RTC_MODE2_INTENCLR_Type   INTENCLR;    /**< \brief Offset: 0x08 (R/W 16) MODE2 Interrupt Enable Clear */
  __IO HW_RTC_MODE2_INTENSET_Type   INTENSET;    /**< \brief Offset: 0x0A (R/W 16) MODE2 Interrupt Enable Set */
  __IO HW_RTC_MODE2_INTFLAG_Type    INTFLAG;     /**< \brief Offset: 0x0C (R/W 16) MODE2 Interrupt Flag Status and Clear */
  __IO HW_RTC_DBGCTRL_Type          DBGCTRL;     /**< \brief Offset: 0x0E (R/W  8) Debug Control */
       RoReg8                    Reserved2[0x1];
  __I  HW_RTC_MODE2_SYNCBUSY_Type   SYNCBUSY;    /**< \brief Offset: 0x10 (R/  32) MODE2 Synchronization Busy Status */
  __IO HW_RTC_FREQCORR_Type         FREQCORR;    /**< \brief Offset: 0x14 (R/W  8) Frequency Correction */
       RoReg8                    Reserved3[0x3];
  __IO HW_RTC_MODE2_CLOCK_Type      CLOCK;       /**< \brief Offset: 0x18 (R/W 32) MODE2 Clock Value */
       RoReg8                    Reserved4[0x4];
       RtcMode2Alarm             Mode2Alarm[1]; /**< \brief Offset: 0x20 RtcMode2Alarm groups [ALARM_NUM] */
       RoReg8                    Reserved5[0x18];
  __IO HW_RTC_GP_Type               GP[4];       /**< \brief Offset: 0x40 (R/W 32) General Purpose */
} RtcMode2;

typedef union {
       RtcMode0                  MODE0;       /**< \brief Offset: 0x00 32-bit Counter with Single 32-bit Compare */
       RtcMode1                  MODE1;       /**< \brief Offset: 0x00 16-bit Counter with Two 16-bit Compares */
       RtcMode2                  MODE2;       /**< \brief Offset: 0x00 Clock/Calendar with Alarm */
} Rtc;


#define HW_REG_RTC_DBGCTRL            (*(RwReg8 *)0x4000200EUL) /**< \brief (RTC) Debug Control */
#define HW_REG_RTC_FREQCORR           (*(RwReg8 *)0x40002014UL) /**< \brief (RTC) Frequency Correction */
#define HW_REG_RTC_GP0                (*(RwReg  *)0x40002040UL) /**< \brief (RTC) General Purpose 0 */
#define HW_REG_RTC_GP1                (*(RwReg  *)0x40002044UL) /**< \brief (RTC) General Purpose 1 */
#define HW_REG_RTC_GP2                (*(RwReg  *)0x40002048UL) /**< \brief (RTC) General Purpose 2 */
#define HW_REG_RTC_GP3                (*(RwReg  *)0x4000204CUL) /**< \brief (RTC) General Purpose 3 */
#define HW_REG_RTC_MODE0_CTRLA        (*(RwReg16*)0x40002000UL) /**< \brief (RTC) MODE0 Control A */
#define HW_REG_RTC_MODE0_EVCTRL       (*(RwReg  *)0x40002004UL) /**< \brief (RTC) MODE0 Event Control */
#define HW_REG_RTC_MODE0_INTENCLR     (*(RwReg16*)0x40002008UL) /**< \brief (RTC) MODE0 Interrupt Enable Clear */
#define HW_REG_RTC_MODE0_INTENSET     (*(RwReg16*)0x4000200AUL) /**< \brief (RTC) MODE0 Interrupt Enable Set */
#define HW_REG_RTC_MODE0_INTFLAG      (*(RwReg16*)0x4000200CUL) /**< \brief (RTC) MODE0 Interrupt Flag Status and Clear */
#define HW_REG_RTC_MODE0_SYNCBUSY     (*(RoReg  *)0x40002010UL) /**< \brief (RTC) MODE0 Synchronization Busy Status */
#define HW_REG_RTC_MODE0_COUNT        (*(RwReg  *)0x40002018UL) /**< \brief (RTC) MODE0 Counter Value */
#define HW_REG_RTC_MODE0_COMP0        (*(RwReg  *)0x40002020UL) /**< \brief (RTC) MODE0 Compare 0 Value */
#define HW_REG_RTC_MODE1_CTRLA        (*(RwReg16*)0x40002000UL) /**< \brief (RTC) MODE1 Control A */
#define HW_REG_RTC_MODE1_EVCTRL       (*(RwReg  *)0x40002004UL) /**< \brief (RTC) MODE1 Event Control */
#define HW_REG_RTC_MODE1_INTENCLR     (*(RwReg16*)0x40002008UL) /**< \brief (RTC) MODE1 Interrupt Enable Clear */
#define HW_REG_RTC_MODE1_INTENSET     (*(RwReg16*)0x4000200AUL) /**< \brief (RTC) MODE1 Interrupt Enable Set */
#define HW_REG_RTC_MODE1_INTFLAG      (*(RwReg16*)0x4000200CUL) /**< \brief (RTC) MODE1 Interrupt Flag Status and Clear */
#define HW_REG_RTC_MODE1_SYNCBUSY     (*(RoReg  *)0x40002010UL) /**< \brief (RTC) MODE1 Synchronization Busy Status */
#define HW_REG_RTC_MODE1_COUNT        (*(RwReg16*)0x40002018UL) /**< \brief (RTC) MODE1 Counter Value */
#define HW_REG_RTC_MODE1_PER          (*(RwReg16*)0x4000201CUL) /**< \brief (RTC) MODE1 Counter Period */
#define HW_REG_RTC_MODE1_COMP0        (*(RwReg16*)0x40002020UL) /**< \brief (RTC) MODE1 Compare 0 Value */
#define HW_REG_RTC_MODE1_COMP1        (*(RwReg16*)0x40002022UL) /**< \brief (RTC) MODE1 Compare 1 Value */
#define HW_REG_RTC_MODE2_CTRLA        (*(RwReg16*)0x40002000UL) /**< \brief (RTC) MODE2 Control A */
#define HW_REG_RTC_MODE2_EVCTRL       (*(RwReg  *)0x40002004UL) /**< \brief (RTC) MODE2 Event Control */
#define HW_REG_RTC_MODE2_INTENCLR     (*(RwReg16*)0x40002008UL) /**< \brief (RTC) MODE2 Interrupt Enable Clear */
#define HW_REG_RTC_MODE2_INTENSET     (*(RwReg16*)0x4000200AUL) /**< \brief (RTC) MODE2 Interrupt Enable Set */
#define HW_REG_RTC_MODE2_INTFLAG      (*(RwReg16*)0x4000200CUL) /**< \brief (RTC) MODE2 Interrupt Flag Status and Clear */
#define HW_REG_RTC_MODE2_SYNCBUSY     (*(RoReg  *)0x40002010UL) /**< \brief (RTC) MODE2 Synchronization Busy Status */
#define HW_REG_RTC_MODE2_CLOCK        (*(RwReg  *)0x40002018UL) /**< \brief (RTC) MODE2 Clock Value */
#define HW_REG_RTC_MODE2_ALARM_ALARM0 (*(RwReg  *)0x40002020UL) /**< \brief (RTC) MODE2_ALARM Alarm 0 Value */
#define HW_REG_RTC_MODE2_ALARM_MASK0  (*(RwReg8 *)0x40002024UL) /**< \brief (RTC) MODE2_ALARM Alarm 0 Mask */

/* ========== Instance parameters for RTC peripheral ========== */
#define HW_RTC_ALARM_NUM               1        // Number of Alarms
#define HW_RTC_COMP16_NUM              2        // Number of 16-bit Comparators
#define HW_RTC_COMP32_NUM              1        // Number of 32-bit Comparators
#define HW_RTC_GPR_NUM                 4        // Number of General-Purpose Registers
#define HW_RTC_PER_NUM                 8        // Number of Periodic Intervals



#endif //HW_RAK4260_RTC_H