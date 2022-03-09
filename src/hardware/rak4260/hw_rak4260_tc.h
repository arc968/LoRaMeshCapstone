#ifndef HW_RAK4260_TC_H
#define HW_RAK4260_TC_H

#define HW_TC_U2249
#define REV_TC                      0x200

/* -------- HW_TC_CTRLA : (HW_TC Offset: 0x00) (R/W 32) Control A -------- */
typedef union {
  struct {
    uint32_t SWRST:1;          /*!< bit:      0  Software Reset                     */
    uint32_t ENABLE:1;         /*!< bit:      1  Enable                             */
    uint32_t MODE:2;           /*!< bit:  2.. 3  Timer Counter Mode                 */
    uint32_t PRESCSYNC:2;      /*!< bit:  4.. 5  Prescaler and Counter Synchronization */
    uint32_t RUNSTDBY:1;       /*!< bit:      6  Run during Standby                 */
    uint32_t ONDEMAND:1;       /*!< bit:      7  Clock On Demand                    */
    uint32_t PRESCALER:3;      /*!< bit:  8..10  Prescaler                          */
    uint32_t ALOCK:1;          /*!< bit:     11  Auto Lock                          */
    uint32_t :4;               /*!< bit: 12..15  Reserved                           */
    uint32_t CAPTEN0:1;        /*!< bit:     16  Capture Channel 0 Enable           */
    uint32_t CAPTEN1:1;        /*!< bit:     17  Capture Channel 1 Enable           */
    uint32_t :2;               /*!< bit: 18..19  Reserved                           */
    uint32_t COPEN0:1;         /*!< bit:     20  Capture On Pin 0 Enable            */
    uint32_t COPEN1:1;         /*!< bit:     21  Capture On Pin 1 Enable            */
    uint32_t :10;              /*!< bit: 22..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  struct {
    uint32_t :16;              /*!< bit:  0..15  Reserved                           */
    uint32_t CAPTEN:2;         /*!< bit: 16..17  Capture Channel x Enable           */
    uint32_t :2;               /*!< bit: 18..19  Reserved                           */
    uint32_t COPEN:2;          /*!< bit: 20..21  Capture On Pin x Enable            */
    uint32_t :10;              /*!< bit: 22..31  Reserved                           */
  } vec;                       /*!< Structure used for vec  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} HW_TC_CTRLA_Type;

#define HW_TC_CTRLA_OFFSET             0x00         /**< \brief (HW_TC_CTRLA offset) Control A */
#define HW_TC_CTRLA_RESETVALUE         _U_(0x00000000) /**< \brief (HW_TC_CTRLA reset_value) Control A */

#define HW_TC_CTRLA_SWRST_Pos          0            /**< \brief (HW_TC_CTRLA) Software Reset */
#define HW_TC_CTRLA_SWRST              (_U_(0x1) << HW_TC_CTRLA_SWRST_Pos)
#define HW_TC_CTRLA_ENABLE_Pos         1            /**< \brief (HW_TC_CTRLA) Enable */
#define HW_TC_CTRLA_ENABLE             (_U_(0x1) << HW_TC_CTRLA_ENABLE_Pos)
#define HW_TC_CTRLA_MODE_Pos           2            /**< \brief (HW_TC_CTRLA) Timer Counter Mode */
#define HW_TC_CTRLA_MODE_Msk           (_U_(0x3) << HW_TC_CTRLA_MODE_Pos)
#define HW_TC_CTRLA_MODE(value)        (HW_TC_CTRLA_MODE_Msk & ((value) << HW_TC_CTRLA_MODE_Pos))
#define   HW_TC_CTRLA_MODE_COUNT16_Val       _U_(0x0)   /**< \brief (HW_TC_CTRLA) Counter in 16-bit mode */
#define   HW_TC_CTRLA_MODE_COUNT8_Val        _U_(0x1)   /**< \brief (HW_TC_CTRLA) Counter in 8-bit mode */
#define   HW_TC_CTRLA_MODE_COUNT32_Val       _U_(0x2)   /**< \brief (HW_TC_CTRLA) Counter in 32-bit mode */
#define HW_TC_CTRLA_MODE_COUNT16       (HW_TC_CTRLA_MODE_COUNT16_Val     << HW_TC_CTRLA_MODE_Pos)
#define HW_TC_CTRLA_MODE_COUNT8        (HW_TC_CTRLA_MODE_COUNT8_Val      << HW_TC_CTRLA_MODE_Pos)
#define HW_TC_CTRLA_MODE_COUNT32       (HW_TC_CTRLA_MODE_COUNT32_Val     << HW_TC_CTRLA_MODE_Pos)
#define HW_TC_CTRLA_PRESCSYNC_Pos      4            /**< \brief (HW_TC_CTRLA) Prescaler and Counter Synchronization */
#define HW_TC_CTRLA_PRESCSYNC_Msk      (_U_(0x3) << HW_TC_CTRLA_PRESCSYNC_Pos)
#define HW_TC_CTRLA_PRESCSYNC(value)   (HW_TC_CTRLA_PRESCSYNC_Msk & ((value) << HW_TC_CTRLA_PRESCSYNC_Pos))
#define   HW_TC_CTRLA_PRESCSYNC_GCLK_Val     _U_(0x0)   /**< \brief (HW_TC_CTRLA) Reload or reset the counter on next generic clock */
#define   HW_TC_CTRLA_PRESCSYNC_PRESC_Val    _U_(0x1)   /**< \brief (HW_TC_CTRLA) Reload or reset the counter on next prescaler clock */
#define   HW_TC_CTRLA_PRESCSYNC_RESYNC_Val   _U_(0x2)   /**< \brief (HW_TC_CTRLA) Reload or reset the counter on next generic clock and reset the prescaler counter */
#define HW_TC_CTRLA_PRESCSYNC_GCLK     (HW_TC_CTRLA_PRESCSYNC_GCLK_Val   << HW_TC_CTRLA_PRESCSYNC_Pos)
#define HW_TC_CTRLA_PRESCSYNC_PRESC    (HW_TC_CTRLA_PRESCSYNC_PRESC_Val  << HW_TC_CTRLA_PRESCSYNC_Pos)
#define HW_TC_CTRLA_PRESCSYNC_RESYNC   (HW_TC_CTRLA_PRESCSYNC_RESYNC_Val << HW_TC_CTRLA_PRESCSYNC_Pos)
#define HW_TC_CTRLA_RUNSTDBY_Pos       6            /**< \brief (HW_TC_CTRLA) Run during Standby */
#define HW_TC_CTRLA_RUNSTDBY           (_U_(0x1) << HW_TC_CTRLA_RUNSTDBY_Pos)
#define HW_TC_CTRLA_ONDEMAND_Pos       7            /**< \brief (HW_TC_CTRLA) Clock On Demand */
#define HW_TC_CTRLA_ONDEMAND           (_U_(0x1) << HW_TC_CTRLA_ONDEMAND_Pos)
#define HW_TC_CTRLA_PRESCALER_Pos      8            /**< \brief (HW_TC_CTRLA) Prescaler */
#define HW_TC_CTRLA_PRESCALER_Msk      (_U_(0x7) << HW_TC_CTRLA_PRESCALER_Pos)
#define HW_TC_CTRLA_PRESCALER(value)   (HW_TC_CTRLA_PRESCALER_Msk & ((value) << HW_TC_CTRLA_PRESCALER_Pos))
#define   HW_TC_CTRLA_PRESCALER_DIV1_Val     _U_(0x0)   /**< \brief (HW_TC_CTRLA) Prescaler: GCLK_HW_TC */
#define   HW_TC_CTRLA_PRESCALER_DIV2_Val     _U_(0x1)   /**< \brief (HW_TC_CTRLA) Prescaler: GCLK_HW_TC/2 */
#define   HW_TC_CTRLA_PRESCALER_DIV4_Val     _U_(0x2)   /**< \brief (HW_TC_CTRLA) Prescaler: GCLK_HW_TC/4 */
#define   HW_TC_CTRLA_PRESCALER_DIV8_Val     _U_(0x3)   /**< \brief (HW_TC_CTRLA) Prescaler: GCLK_HW_TC/8 */
#define   HW_TC_CTRLA_PRESCALER_DIV16_Val    _U_(0x4)   /**< \brief (HW_TC_CTRLA) Prescaler: GCLK_HW_TC/16 */
#define   HW_TC_CTRLA_PRESCALER_DIV64_Val    _U_(0x5)   /**< \brief (HW_TC_CTRLA) Prescaler: GCLK_HW_TC/64 */
#define   HW_TC_CTRLA_PRESCALER_DIV256_Val   _U_(0x6)   /**< \brief (HW_TC_CTRLA) Prescaler: GCLK_HW_TC/256 */
#define   HW_TC_CTRLA_PRESCALER_DIV1024_Val  _U_(0x7)   /**< \brief (HW_TC_CTRLA) Prescaler: GCLK_HW_TC/1024 */
#define HW_TC_CTRLA_PRESCALER_DIV1     (HW_TC_CTRLA_PRESCALER_DIV1_Val   << HW_TC_CTRLA_PRESCALER_Pos)
#define HW_TC_CTRLA_PRESCALER_DIV2     (HW_TC_CTRLA_PRESCALER_DIV2_Val   << HW_TC_CTRLA_PRESCALER_Pos)
#define HW_TC_CTRLA_PRESCALER_DIV4     (HW_TC_CTRLA_PRESCALER_DIV4_Val   << HW_TC_CTRLA_PRESCALER_Pos)
#define HW_TC_CTRLA_PRESCALER_DIV8     (HW_TC_CTRLA_PRESCALER_DIV8_Val   << HW_TC_CTRLA_PRESCALER_Pos)
#define HW_TC_CTRLA_PRESCALER_DIV16    (HW_TC_CTRLA_PRESCALER_DIV16_Val  << HW_TC_CTRLA_PRESCALER_Pos)
#define HW_TC_CTRLA_PRESCALER_DIV64    (HW_TC_CTRLA_PRESCALER_DIV64_Val  << HW_TC_CTRLA_PRESCALER_Pos)
#define HW_TC_CTRLA_PRESCALER_DIV256   (HW_TC_CTRLA_PRESCALER_DIV256_Val << HW_TC_CTRLA_PRESCALER_Pos)
#define HW_TC_CTRLA_PRESCALER_DIV1024  (HW_TC_CTRLA_PRESCALER_DIV1024_Val << HW_TC_CTRLA_PRESCALER_Pos)
#define HW_TC_CTRLA_ALOCK_Pos          11           /**< \brief (HW_TC_CTRLA) Auto Lock */
#define HW_TC_CTRLA_ALOCK              (_U_(0x1) << HW_TC_CTRLA_ALOCK_Pos)
#define HW_TC_CTRLA_CAPTEN0_Pos        16           /**< \brief (HW_TC_CTRLA) Capture Channel 0 Enable */
#define HW_TC_CTRLA_CAPTEN0            (_U_(1) << HW_TC_CTRLA_CAPTEN0_Pos)
#define HW_TC_CTRLA_CAPTEN1_Pos        17           /**< \brief (HW_TC_CTRLA) Capture Channel 1 Enable */
#define HW_TC_CTRLA_CAPTEN1            (_U_(1) << HW_TC_CTRLA_CAPTEN1_Pos)
#define HW_TC_CTRLA_CAPTEN_Pos         16           /**< \brief (HW_TC_CTRLA) Capture Channel x Enable */
#define HW_TC_CTRLA_CAPTEN_Msk         (_U_(0x3) << HW_TC_CTRLA_CAPTEN_Pos)
#define HW_TC_CTRLA_CAPTEN(value)      (HW_TC_CTRLA_CAPTEN_Msk & ((value) << HW_TC_CTRLA_CAPTEN_Pos))
#define HW_TC_CTRLA_COPEN0_Pos         20           /**< \brief (HW_TC_CTRLA) Capture On Pin 0 Enable */
#define HW_TC_CTRLA_COPEN0             (_U_(1) << HW_TC_CTRLA_COPEN0_Pos)
#define HW_TC_CTRLA_COPEN1_Pos         21           /**< \brief (HW_TC_CTRLA) Capture On Pin 1 Enable */
#define HW_TC_CTRLA_COPEN1             (_U_(1) << HW_TC_CTRLA_COPEN1_Pos)
#define HW_TC_CTRLA_COPEN_Pos          20           /**< \brief (HW_TC_CTRLA) Capture On Pin x Enable */
#define HW_TC_CTRLA_COPEN_Msk          (_U_(0x3) << HW_TC_CTRLA_COPEN_Pos)
#define HW_TC_CTRLA_COPEN(value)       (HW_TC_CTRLA_COPEN_Msk & ((value) << HW_TC_CTRLA_COPEN_Pos))
#define HW_TC_CTRLA_MASK               _U_(0x00330FFF) /**< \brief (HW_TC_CTRLA) MASK Register */

/* -------- HW_TC_CTRLBCLR : (HW_TC Offset: 0x04) (R/W  8) Control B Clear -------- */
typedef union {
  struct {
    uint8_t  DIR:1;            /*!< bit:      0  Counter Direction                  */
    uint8_t  LUPD:1;           /*!< bit:      1  Lock Update                        */
    uint8_t  ONESHOT:1;        /*!< bit:      2  One-Shot on Counter                */
    uint8_t  :2;               /*!< bit:  3.. 4  Reserved                           */
    uint8_t  CMD:3;            /*!< bit:  5.. 7  Command                            */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} HW_TC_CTRLBCLR_Type;

#define HW_TC_CTRLBCLR_OFFSET          0x04         /**< \brief (HW_TC_CTRLBCLR offset) Control B Clear */
#define HW_TC_CTRLBCLR_RESETVALUE      _U_(0x00)    /**< \brief (HW_TC_CTRLBCLR reset_value) Control B Clear */

#define HW_TC_CTRLBCLR_DIR_Pos         0            /**< \brief (HW_TC_CTRLBCLR) Counter Direction */
#define HW_TC_CTRLBCLR_DIR             (_U_(0x1) << HW_TC_CTRLBCLR_DIR_Pos)
#define HW_TC_CTRLBCLR_LUPD_Pos        1            /**< \brief (HW_TC_CTRLBCLR) Lock Update */
#define HW_TC_CTRLBCLR_LUPD            (_U_(0x1) << HW_TC_CTRLBCLR_LUPD_Pos)
#define HW_TC_CTRLBCLR_ONESHOT_Pos     2            /**< \brief (HW_TC_CTRLBCLR) One-Shot on Counter */
#define HW_TC_CTRLBCLR_ONESHOT         (_U_(0x1) << HW_TC_CTRLBCLR_ONESHOT_Pos)
#define HW_TC_CTRLBCLR_CMD_Pos         5            /**< \brief (HW_TC_CTRLBCLR) Command */
#define HW_TC_CTRLBCLR_CMD_Msk         (_U_(0x7) << HW_TC_CTRLBCLR_CMD_Pos)
#define HW_TC_CTRLBCLR_CMD(value)      (HW_TC_CTRLBCLR_CMD_Msk & ((value) << HW_TC_CTRLBCLR_CMD_Pos))
#define   HW_TC_CTRLBCLR_CMD_NONE_Val        _U_(0x0)   /**< \brief (HW_TC_CTRLBCLR) No action */
#define   HW_TC_CTRLBCLR_CMD_RETRIGGER_Val   _U_(0x1)   /**< \brief (HW_TC_CTRLBCLR) Force a start, restart or retrigger */
#define   HW_TC_CTRLBCLR_CMD_STOP_Val        _U_(0x2)   /**< \brief (HW_TC_CTRLBCLR) Force a stop */
#define   HW_TC_CTRLBCLR_CMD_UPDATE_Val      _U_(0x3)   /**< \brief (HW_TC_CTRLBCLR) Force update of double-buffered register */
#define   HW_TC_CTRLBCLR_CMD_READSYNC_Val    _U_(0x4)   /**< \brief (HW_TC_CTRLBCLR) Force a read synchronization of COUNT */
#define   HW_TC_CTRLBCLR_CMD_DMAOS_Val       _U_(0x5)   /**< \brief (HW_TC_CTRLBCLR) One-shot DMA trigger */
#define HW_TC_CTRLBCLR_CMD_NONE        (HW_TC_CTRLBCLR_CMD_NONE_Val      << HW_TC_CTRLBCLR_CMD_Pos)
#define HW_TC_CTRLBCLR_CMD_RETRIGGER   (HW_TC_CTRLBCLR_CMD_RETRIGGER_Val << HW_TC_CTRLBCLR_CMD_Pos)
#define HW_TC_CTRLBCLR_CMD_STOP        (HW_TC_CTRLBCLR_CMD_STOP_Val      << HW_TC_CTRLBCLR_CMD_Pos)
#define HW_TC_CTRLBCLR_CMD_UPDATE      (HW_TC_CTRLBCLR_CMD_UPDATE_Val    << HW_TC_CTRLBCLR_CMD_Pos)
#define HW_TC_CTRLBCLR_CMD_READSYNC    (HW_TC_CTRLBCLR_CMD_READSYNC_Val  << HW_TC_CTRLBCLR_CMD_Pos)
#define HW_TC_CTRLBCLR_CMD_DMAOS       (HW_TC_CTRLBCLR_CMD_DMAOS_Val     << HW_TC_CTRLBCLR_CMD_Pos)
#define HW_TC_CTRLBCLR_MASK            _U_(0xE7)    /**< \brief (HW_TC_CTRLBCLR) MASK Register */

/* -------- HW_TC_CTRLBSET : (HW_TC Offset: 0x05) (R/W  8) Control B Set -------- */
typedef union {
  struct {
    uint8_t  DIR:1;            /*!< bit:      0  Counter Direction                  */
    uint8_t  LUPD:1;           /*!< bit:      1  Lock Update                        */
    uint8_t  ONESHOT:1;        /*!< bit:      2  One-Shot on Counter                */
    uint8_t  :2;               /*!< bit:  3.. 4  Reserved                           */
    uint8_t  CMD:3;            /*!< bit:  5.. 7  Command                            */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} HW_TC_CTRLBSET_Type;

#define HW_TC_CTRLBSET_OFFSET          0x05         /**< \brief (HW_TC_CTRLBSET offset) Control B Set */
#define HW_TC_CTRLBSET_RESETVALUE      _U_(0x00)    /**< \brief (HW_TC_CTRLBSET reset_value) Control B Set */

#define HW_TC_CTRLBSET_DIR_Pos         0            /**< \brief (HW_TC_CTRLBSET) Counter Direction */
#define HW_TC_CTRLBSET_DIR             (_U_(0x1) << HW_TC_CTRLBSET_DIR_Pos)
#define HW_TC_CTRLBSET_LUPD_Pos        1            /**< \brief (HW_TC_CTRLBSET) Lock Update */
#define HW_TC_CTRLBSET_LUPD            (_U_(0x1) << HW_TC_CTRLBSET_LUPD_Pos)
#define HW_TC_CTRLBSET_ONESHOT_Pos     2            /**< \brief (HW_TC_CTRLBSET) One-Shot on Counter */
#define HW_TC_CTRLBSET_ONESHOT         (_U_(0x1) << HW_TC_CTRLBSET_ONESHOT_Pos)
#define HW_TC_CTRLBSET_CMD_Pos         5            /**< \brief (HW_TC_CTRLBSET) Command */
#define HW_TC_CTRLBSET_CMD_Msk         (_U_(0x7) << HW_TC_CTRLBSET_CMD_Pos)
#define HW_TC_CTRLBSET_CMD(value)      (HW_TC_CTRLBSET_CMD_Msk & ((value) << HW_TC_CTRLBSET_CMD_Pos))
#define   HW_TC_CTRLBSET_CMD_NONE_Val        _U_(0x0)   /**< \brief (HW_TC_CTRLBSET) No action */
#define   HW_TC_CTRLBSET_CMD_RETRIGGER_Val   _U_(0x1)   /**< \brief (HW_TC_CTRLBSET) Force a start, restart or retrigger */
#define   HW_TC_CTRLBSET_CMD_STOP_Val        _U_(0x2)   /**< \brief (HW_TC_CTRLBSET) Force a stop */
#define   HW_TC_CTRLBSET_CMD_UPDATE_Val      _U_(0x3)   /**< \brief (HW_TC_CTRLBSET) Force update of double-buffered register */
#define   HW_TC_CTRLBSET_CMD_READSYNC_Val    _U_(0x4)   /**< \brief (HW_TC_CTRLBSET) Force a read synchronization of COUNT */
#define   HW_TC_CTRLBSET_CMD_DMAOS_Val       _U_(0x5)   /**< \brief (HW_TC_CTRLBSET) One-shot DMA trigger */
#define HW_TC_CTRLBSET_CMD_NONE        (HW_TC_CTRLBSET_CMD_NONE_Val      << HW_TC_CTRLBSET_CMD_Pos)
#define HW_TC_CTRLBSET_CMD_RETRIGGER   (HW_TC_CTRLBSET_CMD_RETRIGGER_Val << HW_TC_CTRLBSET_CMD_Pos)
#define HW_TC_CTRLBSET_CMD_STOP        (HW_TC_CTRLBSET_CMD_STOP_Val      << HW_TC_CTRLBSET_CMD_Pos)
#define HW_TC_CTRLBSET_CMD_UPDATE      (HW_TC_CTRLBSET_CMD_UPDATE_Val    << HW_TC_CTRLBSET_CMD_Pos)
#define HW_TC_CTRLBSET_CMD_READSYNC    (HW_TC_CTRLBSET_CMD_READSYNC_Val  << HW_TC_CTRLBSET_CMD_Pos)
#define HW_TC_CTRLBSET_CMD_DMAOS       (HW_TC_CTRLBSET_CMD_DMAOS_Val     << HW_TC_CTRLBSET_CMD_Pos)
#define HW_TC_CTRLBSET_MASK            _U_(0xE7)    /**< \brief (HW_TC_CTRLBSET) MASK Register */

/* -------- HW_TC_EVCTRL : (HW_TC Offset: 0x06) (R/W 16) Event Control -------- */
typedef union {
  struct {
    uint16_t EVACT:3;          /*!< bit:  0.. 2  Event Action                       */
    uint16_t :1;               /*!< bit:      3  Reserved                           */
    uint16_t HW_TCINV:1;          /*!< bit:      4  HW_TC Event Input Polarity            */
    uint16_t HW_TCEI:1;           /*!< bit:      5  HW_TC Event Enable                    */
    uint16_t :2;               /*!< bit:  6.. 7  Reserved                           */
    uint16_t OVFEO:1;          /*!< bit:      8  Event Output Enable                */
    uint16_t :3;               /*!< bit:  9..11  Reserved                           */
    uint16_t MCEO0:1;          /*!< bit:     12  MC Event Output Enable 0           */
    uint16_t MCEO1:1;          /*!< bit:     13  MC Event Output Enable 1           */
    uint16_t :2;               /*!< bit: 14..15  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  struct {
    uint16_t :12;              /*!< bit:  0..11  Reserved                           */
    uint16_t MCEO:2;           /*!< bit: 12..13  MC Event Output Enable x           */
    uint16_t :2;               /*!< bit: 14..15  Reserved                           */
  } vec;                       /*!< Structure used for vec  access                  */
  uint16_t reg;                /*!< Type      used for register access              */
} HW_TC_EVCTRL_Type;

#define HW_TC_EVCTRL_OFFSET            0x06         /**< \brief (HW_TC_EVCTRL offset) Event Control */
#define HW_TC_EVCTRL_RESETVALUE        _U_(0x0000)  /**< \brief (HW_TC_EVCTRL reset_value) Event Control */

#define HW_TC_EVCTRL_EVACT_Pos         0            /**< \brief (HW_TC_EVCTRL) Event Action */
#define HW_TC_EVCTRL_EVACT_Msk         (_U_(0x7) << HW_TC_EVCTRL_EVACT_Pos)
#define HW_TC_EVCTRL_EVACT(value)      (HW_TC_EVCTRL_EVACT_Msk & ((value) << HW_TC_EVCTRL_EVACT_Pos))
#define   HW_TC_EVCTRL_EVACT_OFF_Val         _U_(0x0)   /**< \brief (HW_TC_EVCTRL) Event action disabled */
#define   HW_TC_EVCTRL_EVACT_RETRIGGER_Val   _U_(0x1)   /**< \brief (HW_TC_EVCTRL) Start, restart or retrigger HW_TC on event */
#define   HW_TC_EVCTRL_EVACT_COUNT_Val       _U_(0x2)   /**< \brief (HW_TC_EVCTRL) Count on event */
#define   HW_TC_EVCTRL_EVACT_START_Val       _U_(0x3)   /**< \brief (HW_TC_EVCTRL) Start HW_TC on event */
#define   HW_TC_EVCTRL_EVACT_STAMP_Val       _U_(0x4)   /**< \brief (HW_TC_EVCTRL) Time stamp capture */
#define   HW_TC_EVCTRL_EVACT_PPW_Val         _U_(0x5)   /**< \brief (HW_TC_EVCTRL) Period captured in CC0, pulse width in CC1 */
#define   HW_TC_EVCTRL_EVACT_PWP_Val         _U_(0x6)   /**< \brief (HW_TC_EVCTRL) Period captured in CC1, pulse width in CC0 */
#define   HW_TC_EVCTRL_EVACT_PW_Val          _U_(0x7)   /**< \brief (HW_TC_EVCTRL) Pulse width capture */
#define HW_TC_EVCTRL_EVACT_OFF         (HW_TC_EVCTRL_EVACT_OFF_Val       << HW_TC_EVCTRL_EVACT_Pos)
#define HW_TC_EVCTRL_EVACT_RETRIGGER   (HW_TC_EVCTRL_EVACT_RETRIGGER_Val << HW_TC_EVCTRL_EVACT_Pos)
#define HW_TC_EVCTRL_EVACT_COUNT       (HW_TC_EVCTRL_EVACT_COUNT_Val     << HW_TC_EVCTRL_EVACT_Pos)
#define HW_TC_EVCTRL_EVACT_START       (HW_TC_EVCTRL_EVACT_START_Val     << HW_TC_EVCTRL_EVACT_Pos)
#define HW_TC_EVCTRL_EVACT_STAMP       (HW_TC_EVCTRL_EVACT_STAMP_Val     << HW_TC_EVCTRL_EVACT_Pos)
#define HW_TC_EVCTRL_EVACT_PPW         (HW_TC_EVCTRL_EVACT_PPW_Val       << HW_TC_EVCTRL_EVACT_Pos)
#define HW_TC_EVCTRL_EVACT_PWP         (HW_TC_EVCTRL_EVACT_PWP_Val       << HW_TC_EVCTRL_EVACT_Pos)
#define HW_TC_EVCTRL_EVACT_PW          (HW_TC_EVCTRL_EVACT_PW_Val        << HW_TC_EVCTRL_EVACT_Pos)
#define HW_TC_EVCTRL_HW_TCINV_Pos         4            /**< \brief (HW_TC_EVCTRL) HW_TC Event Input Polarity */
#define HW_TC_EVCTRL_HW_TCINV             (_U_(0x1) << HW_TC_EVCTRL_HW_TCINV_Pos)
#define HW_TC_EVCTRL_HW_TCEI_Pos          5            /**< \brief (HW_TC_EVCTRL) HW_TC Event Enable */
#define HW_TC_EVCTRL_HW_TCEI              (_U_(0x1) << HW_TC_EVCTRL_HW_TCEI_Pos)
#define HW_TC_EVCTRL_OVFEO_Pos         8            /**< \brief (HW_TC_EVCTRL) Event Output Enable */
#define HW_TC_EVCTRL_OVFEO             (_U_(0x1) << HW_TC_EVCTRL_OVFEO_Pos)
#define HW_TC_EVCTRL_MCEO0_Pos         12           /**< \brief (HW_TC_EVCTRL) MC Event Output Enable 0 */
#define HW_TC_EVCTRL_MCEO0             (_U_(1) << HW_TC_EVCTRL_MCEO0_Pos)
#define HW_TC_EVCTRL_MCEO1_Pos         13           /**< \brief (HW_TC_EVCTRL) MC Event Output Enable 1 */
#define HW_TC_EVCTRL_MCEO1             (_U_(1) << HW_TC_EVCTRL_MCEO1_Pos)
#define HW_TC_EVCTRL_MCEO_Pos          12           /**< \brief (HW_TC_EVCTRL) MC Event Output Enable x */
#define HW_TC_EVCTRL_MCEO_Msk          (_U_(0x3) << HW_TC_EVCTRL_MCEO_Pos)
#define HW_TC_EVCTRL_MCEO(value)       (HW_TC_EVCTRL_MCEO_Msk & ((value) << HW_TC_EVCTRL_MCEO_Pos))
#define HW_TC_EVCTRL_MASK              _U_(0x3137)  /**< \brief (HW_TC_EVCTRL) MASK Register */

/* -------- HW_TC_INTENCLR : (HW_TC Offset: 0x08) (R/W  8) Interrupt Enable Clear -------- */
typedef union {
  struct {
    uint8_t  OVF:1;            /*!< bit:      0  OVF Interrupt Disable              */
    uint8_t  ERR:1;            /*!< bit:      1  ERR Interrupt Disable              */
    uint8_t  :2;               /*!< bit:  2.. 3  Reserved                           */
    uint8_t  MC0:1;            /*!< bit:      4  MC Interrupt Disable 0             */
    uint8_t  MC1:1;            /*!< bit:      5  MC Interrupt Disable 1             */
    uint8_t  :2;               /*!< bit:  6.. 7  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  struct {
    uint8_t  :4;               /*!< bit:  0.. 3  Reserved                           */
    uint8_t  MC:2;             /*!< bit:  4.. 5  MC Interrupt Disable x             */
    uint8_t  :2;               /*!< bit:  6.. 7  Reserved                           */
  } vec;                       /*!< Structure used for vec  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} HW_TC_INTENCLR_Type;

#define HW_TC_INTENCLR_OFFSET          0x08         /**< \brief (HW_TC_INTENCLR offset) Interrupt Enable Clear */
#define HW_TC_INTENCLR_RESETVALUE      _U_(0x00)    /**< \brief (HW_TC_INTENCLR reset_value) Interrupt Enable Clear */

#define HW_TC_INTENCLR_OVF_Pos         0            /**< \brief (HW_TC_INTENCLR) OVF Interrupt Disable */
#define HW_TC_INTENCLR_OVF             (_U_(0x1) << HW_TC_INTENCLR_OVF_Pos)
#define HW_TC_INTENCLR_ERR_Pos         1            /**< \brief (HW_TC_INTENCLR) ERR Interrupt Disable */
#define HW_TC_INTENCLR_ERR             (_U_(0x1) << HW_TC_INTENCLR_ERR_Pos)
#define HW_TC_INTENCLR_MC0_Pos         4            /**< \brief (HW_TC_INTENCLR) MC Interrupt Disable 0 */
#define HW_TC_INTENCLR_MC0             (_U_(1) << HW_TC_INTENCLR_MC0_Pos)
#define HW_TC_INTENCLR_MC1_Pos         5            /**< \brief (HW_TC_INTENCLR) MC Interrupt Disable 1 */
#define HW_TC_INTENCLR_MC1             (_U_(1) << HW_TC_INTENCLR_MC1_Pos)
#define HW_TC_INTENCLR_MC_Pos          4            /**< \brief (HW_TC_INTENCLR) MC Interrupt Disable x */
#define HW_TC_INTENCLR_MC_Msk          (_U_(0x3) << HW_TC_INTENCLR_MC_Pos)
#define HW_TC_INTENCLR_MC(value)       (HW_TC_INTENCLR_MC_Msk & ((value) << HW_TC_INTENCLR_MC_Pos))
#define HW_TC_INTENCLR_MASK            _U_(0x33)    /**< \brief (HW_TC_INTENCLR) MASK Register */

/* -------- HW_TC_INTENSET : (HW_TC Offset: 0x09) (R/W  8) Interrupt Enable Set -------- */
typedef union {
  struct {
    uint8_t  OVF:1;            /*!< bit:      0  OVF Interrupt Enable               */
    uint8_t  ERR:1;            /*!< bit:      1  ERR Interrupt Enable               */
    uint8_t  :2;               /*!< bit:  2.. 3  Reserved                           */
    uint8_t  MC0:1;            /*!< bit:      4  MC Interrupt Enable 0              */
    uint8_t  MC1:1;            /*!< bit:      5  MC Interrupt Enable 1              */
    uint8_t  :2;               /*!< bit:  6.. 7  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  struct {
    uint8_t  :4;               /*!< bit:  0.. 3  Reserved                           */
    uint8_t  MC:2;             /*!< bit:  4.. 5  MC Interrupt Enable x              */
    uint8_t  :2;               /*!< bit:  6.. 7  Reserved                           */
  } vec;                       /*!< Structure used for vec  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} HW_TC_INTENSET_Type;

#define HW_TC_INTENSET_OFFSET          0x09         /**< \brief (HW_TC_INTENSET offset) Interrupt Enable Set */
#define HW_TC_INTENSET_RESETVALUE      _U_(0x00)    /**< \brief (HW_TC_INTENSET reset_value) Interrupt Enable Set */

#define HW_TC_INTENSET_OVF_Pos         0            /**< \brief (HW_TC_INTENSET) OVF Interrupt Enable */
#define HW_TC_INTENSET_OVF             (_U_(0x1) << HW_TC_INTENSET_OVF_Pos)
#define HW_TC_INTENSET_ERR_Pos         1            /**< \brief (HW_TC_INTENSET) ERR Interrupt Enable */
#define HW_TC_INTENSET_ERR             (_U_(0x1) << HW_TC_INTENSET_ERR_Pos)
#define HW_TC_INTENSET_MC0_Pos         4            /**< \brief (HW_TC_INTENSET) MC Interrupt Enable 0 */
#define HW_TC_INTENSET_MC0             (_U_(1) << HW_TC_INTENSET_MC0_Pos)
#define HW_TC_INTENSET_MC1_Pos         5            /**< \brief (HW_TC_INTENSET) MC Interrupt Enable 1 */
#define HW_TC_INTENSET_MC1             (_U_(1) << HW_TC_INTENSET_MC1_Pos)
#define HW_TC_INTENSET_MC_Pos          4            /**< \brief (HW_TC_INTENSET) MC Interrupt Enable x */
#define HW_TC_INTENSET_MC_Msk          (_U_(0x3) << HW_TC_INTENSET_MC_Pos)
#define HW_TC_INTENSET_MC(value)       (HW_TC_INTENSET_MC_Msk & ((value) << HW_TC_INTENSET_MC_Pos))
#define HW_TC_INTENSET_MASK            _U_(0x33)    /**< \brief (HW_TC_INTENSET) MASK Register */

/* -------- HW_TC_INTFLAG : (HW_TC Offset: 0x0A) (R/W  8) Interrupt Flag Status and Clear -------- */
typedef union { // __I to avoid read-modify-write on write-to-clear register
  struct {
    __I uint8_t  OVF:1;            /*!< bit:      0  OVF Interrupt Flag                 */
    __I uint8_t  ERR:1;            /*!< bit:      1  ERR Interrupt Flag                 */
    __I uint8_t  :2;               /*!< bit:  2.. 3  Reserved                           */
    __I uint8_t  MC0:1;            /*!< bit:      4  MC Interrupt Flag 0                */
    __I uint8_t  MC1:1;            /*!< bit:      5  MC Interrupt Flag 1                */
    __I uint8_t  :2;               /*!< bit:  6.. 7  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  struct {
    __I uint8_t  :4;               /*!< bit:  0.. 3  Reserved                           */
    __I uint8_t  MC:2;             /*!< bit:  4.. 5  MC Interrupt Flag x                */
    __I uint8_t  :2;               /*!< bit:  6.. 7  Reserved                           */
  } vec;                       /*!< Structure used for vec  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} HW_TC_INTFLAG_Type;

#define HW_TC_INTFLAG_OFFSET           0x0A         /**< \brief (HW_TC_INTFLAG offset) Interrupt Flag Status and Clear */
#define HW_TC_INTFLAG_RESETVALUE       _U_(0x00)    /**< \brief (HW_TC_INTFLAG reset_value) Interrupt Flag Status and Clear */

#define HW_TC_INTFLAG_OVF_Pos          0            /**< \brief (HW_TC_INTFLAG) OVF Interrupt Flag */
#define HW_TC_INTFLAG_OVF              (_U_(0x1) << HW_TC_INTFLAG_OVF_Pos)
#define HW_TC_INTFLAG_ERR_Pos          1            /**< \brief (HW_TC_INTFLAG) ERR Interrupt Flag */
#define HW_TC_INTFLAG_ERR              (_U_(0x1) << HW_TC_INTFLAG_ERR_Pos)
#define HW_TC_INTFLAG_MC0_Pos          4            /**< \brief (HW_TC_INTFLAG) MC Interrupt Flag 0 */
#define HW_TC_INTFLAG_MC0              (_U_(1) << HW_TC_INTFLAG_MC0_Pos)
#define HW_TC_INTFLAG_MC1_Pos          5            /**< \brief (HW_TC_INTFLAG) MC Interrupt Flag 1 */
#define HW_TC_INTFLAG_MC1              (_U_(1) << HW_TC_INTFLAG_MC1_Pos)
#define HW_TC_INTFLAG_MC_Pos           4            /**< \brief (HW_TC_INTFLAG) MC Interrupt Flag x */
#define HW_TC_INTFLAG_MC_Msk           (_U_(0x3) << HW_TC_INTFLAG_MC_Pos)
#define HW_TC_INTFLAG_MC(value)        (HW_TC_INTFLAG_MC_Msk & ((value) << HW_TC_INTFLAG_MC_Pos))
#define HW_TC_INTFLAG_MASK             _U_(0x33)    /**< \brief (HW_TC_INTFLAG) MASK Register */

/* -------- HW_TC_STATUS : (HW_TC Offset: 0x0B) (R/W  8) Status -------- */
typedef union {
  struct {
    uint8_t  STOP:1;           /*!< bit:      0  Stop Status Flag                   */
    uint8_t  SLAVE:1;          /*!< bit:      1  Slave Status Flag                  */
    uint8_t  :1;               /*!< bit:      2  Reserved                           */
    uint8_t  PERBUFV:1;        /*!< bit:      3  Synchronization Busy Status        */
    uint8_t  CCBUFV0:1;        /*!< bit:      4  Compare channel buffer 0 valid     */
    uint8_t  CCBUFV1:1;        /*!< bit:      5  Compare channel buffer 1 valid     */
    uint8_t  :2;               /*!< bit:  6.. 7  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  struct {
    uint8_t  :4;               /*!< bit:  0.. 3  Reserved                           */
    uint8_t  CCBUFV:2;         /*!< bit:  4.. 5  Compare channel buffer x valid     */
    uint8_t  :2;               /*!< bit:  6.. 7  Reserved                           */
  } vec;                       /*!< Structure used for vec  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} HW_TC_STATUS_Type;

#define HW_TC_STATUS_OFFSET            0x0B         /**< \brief (HW_TC_STATUS offset) Status */
#define HW_TC_STATUS_RESETVALUE        _U_(0x01)    /**< \brief (HW_TC_STATUS reset_value) Status */

#define HW_TC_STATUS_STOP_Pos          0            /**< \brief (HW_TC_STATUS) Stop Status Flag */
#define HW_TC_STATUS_STOP              (_U_(0x1) << HW_TC_STATUS_STOP_Pos)
#define HW_TC_STATUS_SLAVE_Pos         1            /**< \brief (HW_TC_STATUS) Slave Status Flag */
#define HW_TC_STATUS_SLAVE             (_U_(0x1) << HW_TC_STATUS_SLAVE_Pos)
#define HW_TC_STATUS_PERBUFV_Pos       3            /**< \brief (HW_TC_STATUS) Synchronization Busy Status */
#define HW_TC_STATUS_PERBUFV           (_U_(0x1) << HW_TC_STATUS_PERBUFV_Pos)
#define HW_TC_STATUS_CCBUFV0_Pos       4            /**< \brief (HW_TC_STATUS) Compare channel buffer 0 valid */
#define HW_TC_STATUS_CCBUFV0           (_U_(1) << HW_TC_STATUS_CCBUFV0_Pos)
#define HW_TC_STATUS_CCBUFV1_Pos       5            /**< \brief (HW_TC_STATUS) Compare channel buffer 1 valid */
#define HW_TC_STATUS_CCBUFV1           (_U_(1) << HW_TC_STATUS_CCBUFV1_Pos)
#define HW_TC_STATUS_CCBUFV_Pos        4            /**< \brief (HW_TC_STATUS) Compare channel buffer x valid */
#define HW_TC_STATUS_CCBUFV_Msk        (_U_(0x3) << HW_TC_STATUS_CCBUFV_Pos)
#define HW_TC_STATUS_CCBUFV(value)     (HW_TC_STATUS_CCBUFV_Msk & ((value) << HW_TC_STATUS_CCBUFV_Pos))
#define HW_TC_STATUS_MASK              _U_(0x3B)    /**< \brief (HW_TC_STATUS) MASK Register */

/* -------- HW_TC_WAVE : (HW_TC Offset: 0x0C) (R/W  8) Waveform Generation Control -------- */
typedef union {
  struct {
    uint8_t  WAVEGEN:2;        /*!< bit:  0.. 1  Waveform Generation Mode           */
    uint8_t  :6;               /*!< bit:  2.. 7  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} HW_TC_WAVE_Type;

#define HW_TC_WAVE_OFFSET              0x0C         /**< \brief (HW_TC_WAVE offset) Waveform Generation Control */
#define HW_TC_WAVE_RESETVALUE          _U_(0x00)    /**< \brief (HW_TC_WAVE reset_value) Waveform Generation Control */

#define HW_TC_WAVE_WAVEGEN_Pos         0            /**< \brief (HW_TC_WAVE) Waveform Generation Mode */
#define HW_TC_WAVE_WAVEGEN_Msk         (_U_(0x3) << HW_TC_WAVE_WAVEGEN_Pos)
#define HW_TC_WAVE_WAVEGEN(value)      (HW_TC_WAVE_WAVEGEN_Msk & ((value) << HW_TC_WAVE_WAVEGEN_Pos))
#define   HW_TC_WAVE_WAVEGEN_NFRQ_Val        _U_(0x0)   /**< \brief (HW_TC_WAVE) Normal frequency */
#define   HW_TC_WAVE_WAVEGEN_MFRQ_Val        _U_(0x1)   /**< \brief (HW_TC_WAVE) Match frequency */
#define   HW_TC_WAVE_WAVEGEN_NPWM_Val        _U_(0x2)   /**< \brief (HW_TC_WAVE) Normal PWM */
#define   HW_TC_WAVE_WAVEGEN_MPWM_Val        _U_(0x3)   /**< \brief (HW_TC_WAVE) Match PWM */
#define HW_TC_WAVE_WAVEGEN_NFRQ        (HW_TC_WAVE_WAVEGEN_NFRQ_Val      << HW_TC_WAVE_WAVEGEN_Pos)
#define HW_TC_WAVE_WAVEGEN_MFRQ        (HW_TC_WAVE_WAVEGEN_MFRQ_Val      << HW_TC_WAVE_WAVEGEN_Pos)
#define HW_TC_WAVE_WAVEGEN_NPWM        (HW_TC_WAVE_WAVEGEN_NPWM_Val      << HW_TC_WAVE_WAVEGEN_Pos)
#define HW_TC_WAVE_WAVEGEN_MPWM        (HW_TC_WAVE_WAVEGEN_MPWM_Val      << HW_TC_WAVE_WAVEGEN_Pos)
#define HW_TC_WAVE_MASK                _U_(0x03)    /**< \brief (HW_TC_WAVE) MASK Register */

/* -------- HW_TC_DRVCTRL : (HW_TC Offset: 0x0D) (R/W  8) Control C -------- */
typedef union {
  struct {
    uint8_t  INVEN0:1;         /*!< bit:      0  Output Waveform Invert Enable 0    */
    uint8_t  INVEN1:1;         /*!< bit:      1  Output Waveform Invert Enable 1    */
    uint8_t  :6;               /*!< bit:  2.. 7  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  struct {
    uint8_t  INVEN:2;          /*!< bit:  0.. 1  Output Waveform Invert Enable x    */
    uint8_t  :6;               /*!< bit:  2.. 7  Reserved                           */
  } vec;                       /*!< Structure used for vec  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} HW_TC_DRVCTRL_Type;

#define HW_TC_DRVCTRL_OFFSET           0x0D         /**< \brief (HW_TC_DRVCTRL offset) Control C */
#define HW_TC_DRVCTRL_RESETVALUE       _U_(0x00)    /**< \brief (HW_TC_DRVCTRL reset_value) Control C */

#define HW_TC_DRVCTRL_INVEN0_Pos       0            /**< \brief (HW_TC_DRVCTRL) Output Waveform Invert Enable 0 */
#define HW_TC_DRVCTRL_INVEN0           (_U_(1) << HW_TC_DRVCTRL_INVEN0_Pos)
#define HW_TC_DRVCTRL_INVEN1_Pos       1            /**< \brief (HW_TC_DRVCTRL) Output Waveform Invert Enable 1 */
#define HW_TC_DRVCTRL_INVEN1           (_U_(1) << HW_TC_DRVCTRL_INVEN1_Pos)
#define HW_TC_DRVCTRL_INVEN_Pos        0            /**< \brief (HW_TC_DRVCTRL) Output Waveform Invert Enable x */
#define HW_TC_DRVCTRL_INVEN_Msk        (_U_(0x3) << HW_TC_DRVCTRL_INVEN_Pos)
#define HW_TC_DRVCTRL_INVEN(value)     (HW_TC_DRVCTRL_INVEN_Msk & ((value) << HW_TC_DRVCTRL_INVEN_Pos))
#define HW_TC_DRVCTRL_MASK             _U_(0x03)    /**< \brief (HW_TC_DRVCTRL) MASK Register */

/* -------- HW_TC_DBGCTRL : (HW_TC Offset: 0x0F) (R/W  8) Debug Control -------- */
typedef union {
  struct {
    uint8_t  DBGRUN:1;         /*!< bit:      0  Run During Debug                   */
    uint8_t  :7;               /*!< bit:  1.. 7  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} HW_TC_DBGCTRL_Type;

#define HW_TC_DBGCTRL_OFFSET           0x0F         /**< \brief (HW_TC_DBGCTRL offset) Debug Control */
#define HW_TC_DBGCTRL_RESETVALUE       _U_(0x00)    /**< \brief (HW_TC_DBGCTRL reset_value) Debug Control */

#define HW_TC_DBGCTRL_DBGRUN_Pos       0            /**< \brief (HW_TC_DBGCTRL) Run During Debug */
#define HW_TC_DBGCTRL_DBGRUN           (_U_(0x1) << HW_TC_DBGCTRL_DBGRUN_Pos)
#define HW_TC_DBGCTRL_MASK             _U_(0x01)    /**< \brief (HW_TC_DBGCTRL) MASK Register */

/* -------- HW_TC_SYNCBUSY : (HW_TC Offset: 0x10) (R/  32) Synchronization Status -------- */
typedef union {
  struct {
    uint32_t SWRST:1;          /*!< bit:      0  swrst                              */
    uint32_t ENABLE:1;         /*!< bit:      1  enable                             */
    uint32_t CTRLB:1;          /*!< bit:      2  CTRLB                              */
    uint32_t STATUS:1;         /*!< bit:      3  STATUS                             */
    uint32_t COUNT:1;          /*!< bit:      4  Counter                            */
    uint32_t PER:1;            /*!< bit:      5  Period                             */
    uint32_t CC0:1;            /*!< bit:      6  Compare Channel 0                  */
    uint32_t CC1:1;            /*!< bit:      7  Compare Channel 1                  */
    uint32_t :24;              /*!< bit:  8..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  struct {
    uint32_t :6;               /*!< bit:  0.. 5  Reserved                           */
    uint32_t CC:2;             /*!< bit:  6.. 7  Compare Channel x                  */
    uint32_t :24;              /*!< bit:  8..31  Reserved                           */
  } vec;                       /*!< Structure used for vec  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} HW_TC_SYNCBUSY_Type;

#define HW_TC_SYNCBUSY_OFFSET          0x10         /**< \brief (HW_TC_SYNCBUSY offset) Synchronization Status */
#define HW_TC_SYNCBUSY_RESETVALUE      _U_(0x00000000) /**< \brief (HW_TC_SYNCBUSY reset_value) Synchronization Status */

#define HW_TC_SYNCBUSY_SWRST_Pos       0            /**< \brief (HW_TC_SYNCBUSY) swrst */
#define HW_TC_SYNCBUSY_SWRST           (_U_(0x1) << HW_TC_SYNCBUSY_SWRST_Pos)
#define HW_TC_SYNCBUSY_ENABLE_Pos      1            /**< \brief (HW_TC_SYNCBUSY) enable */
#define HW_TC_SYNCBUSY_ENABLE          (_U_(0x1) << HW_TC_SYNCBUSY_ENABLE_Pos)
#define HW_TC_SYNCBUSY_CTRLB_Pos       2            /**< \brief (HW_TC_SYNCBUSY) CTRLB */
#define HW_TC_SYNCBUSY_CTRLB           (_U_(0x1) << HW_TC_SYNCBUSY_CTRLB_Pos)
#define HW_TC_SYNCBUSY_STATUS_Pos      3            /**< \brief (HW_TC_SYNCBUSY) STATUS */
#define HW_TC_SYNCBUSY_STATUS          (_U_(0x1) << HW_TC_SYNCBUSY_STATUS_Pos)
#define HW_TC_SYNCBUSY_COUNT_Pos       4            /**< \brief (HW_TC_SYNCBUSY) Counter */
#define HW_TC_SYNCBUSY_COUNT           (_U_(0x1) << HW_TC_SYNCBUSY_COUNT_Pos)
#define HW_TC_SYNCBUSY_PER_Pos         5            /**< \brief (HW_TC_SYNCBUSY) Period */
#define HW_TC_SYNCBUSY_PER             (_U_(0x1) << HW_TC_SYNCBUSY_PER_Pos)
#define HW_TC_SYNCBUSY_CC0_Pos         6            /**< \brief (HW_TC_SYNCBUSY) Compare Channel 0 */
#define HW_TC_SYNCBUSY_CC0             (_U_(1) << HW_TC_SYNCBUSY_CC0_Pos)
#define HW_TC_SYNCBUSY_CC1_Pos         7            /**< \brief (HW_TC_SYNCBUSY) Compare Channel 1 */
#define HW_TC_SYNCBUSY_CC1             (_U_(1) << HW_TC_SYNCBUSY_CC1_Pos)
#define HW_TC_SYNCBUSY_CC_Pos          6            /**< \brief (HW_TC_SYNCBUSY) Compare Channel x */
#define HW_TC_SYNCBUSY_CC_Msk          (_U_(0x3) << HW_TC_SYNCBUSY_CC_Pos)
#define HW_TC_SYNCBUSY_CC(value)       (HW_TC_SYNCBUSY_CC_Msk & ((value) << HW_TC_SYNCBUSY_CC_Pos))
#define HW_TC_SYNCBUSY_MASK            _U_(0x000000FF) /**< \brief (HW_TC_SYNCBUSY) MASK Register */

/* -------- HW_TC_COUNT16_COUNT : (HW_TC Offset: 0x14) (R/W 16) COUNT16 COUNT16 Count -------- */
typedef union {
  struct {
    uint16_t COUNT:16;         /*!< bit:  0..15  Counter Value                      */
  } bit;                       /*!< Structure used for bit  access                  */
  uint16_t reg;                /*!< Type      used for register access              */
} HW_TC_COUNT16_COUNT_Type;

#define HW_TC_COUNT16_COUNT_OFFSET     0x14         /**< \brief (HW_TC_COUNT16_COUNT offset) COUNT16 Count */
#define HW_TC_COUNT16_COUNT_RESETVALUE _U_(0x0000)  /**< \brief (HW_TC_COUNT16_COUNT reset_value) COUNT16 Count */

#define HW_TC_COUNT16_COUNT_COUNT_Pos  0            /**< \brief (HW_TC_COUNT16_COUNT) Counter Value */
#define HW_TC_COUNT16_COUNT_COUNT_Msk  (_U_(0xFFFF) << HW_TC_COUNT16_COUNT_COUNT_Pos)
#define HW_TC_COUNT16_COUNT_COUNT(value) (HW_TC_COUNT16_COUNT_COUNT_Msk & ((value) << HW_TC_COUNT16_COUNT_COUNT_Pos))
#define HW_TC_COUNT16_COUNT_MASK       _U_(0xFFFF)  /**< \brief (HW_TC_COUNT16_COUNT) MASK Register */

/* -------- HW_TC_COUNT32_COUNT : (HW_TC Offset: 0x14) (R/W 32) COUNT32 COUNT32 Count -------- */
typedef union {
  struct {
    uint32_t COUNT:32;         /*!< bit:  0..31  Counter Value                      */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} HW_TC_COUNT32_COUNT_Type;

#define HW_TC_COUNT32_COUNT_OFFSET     0x14         /**< \brief (HW_TC_COUNT32_COUNT offset) COUNT32 Count */
#define HW_TC_COUNT32_COUNT_RESETVALUE _U_(0x00000000) /**< \brief (HW_TC_COUNT32_COUNT reset_value) COUNT32 Count */

#define HW_TC_COUNT32_COUNT_COUNT_Pos  0            /**< \brief (HW_TC_COUNT32_COUNT) Counter Value */
#define HW_TC_COUNT32_COUNT_COUNT_Msk  (_U_(0xFFFFFFFF) << HW_TC_COUNT32_COUNT_COUNT_Pos)
#define HW_TC_COUNT32_COUNT_COUNT(value) (HW_TC_COUNT32_COUNT_COUNT_Msk & ((value) << HW_TC_COUNT32_COUNT_COUNT_Pos))
#define HW_TC_COUNT32_COUNT_MASK       _U_(0xFFFFFFFF) /**< \brief (HW_TC_COUNT32_COUNT) MASK Register */

/* -------- HW_TC_COUNT8_COUNT : (HW_TC Offset: 0x14) (R/W  8) COUNT8 COUNT8 Count -------- */
typedef union {
  struct {
    uint8_t  COUNT:8;          /*!< bit:  0.. 7  Counter Value                      */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} HW_TC_COUNT8_COUNT_Type;

#define HW_TC_COUNT8_COUNT_OFFSET      0x14         /**< \brief (HW_TC_COUNT8_COUNT offset) COUNT8 Count */
#define HW_TC_COUNT8_COUNT_RESETVALUE  _U_(0x00)    /**< \brief (HW_TC_COUNT8_COUNT reset_value) COUNT8 Count */

#define HW_TC_COUNT8_COUNT_COUNT_Pos   0            /**< \brief (HW_TC_COUNT8_COUNT) Counter Value */
#define HW_TC_COUNT8_COUNT_COUNT_Msk   (_U_(0xFF) << HW_TC_COUNT8_COUNT_COUNT_Pos)
#define HW_TC_COUNT8_COUNT_COUNT(value) (HW_TC_COUNT8_COUNT_COUNT_Msk & ((value) << HW_TC_COUNT8_COUNT_COUNT_Pos))
#define HW_TC_COUNT8_COUNT_MASK        _U_(0xFF)    /**< \brief (HW_TC_COUNT8_COUNT) MASK Register */

/* -------- HW_TC_COUNT8_PER : (HW_TC Offset: 0x1B) (R/W  8) COUNT8 COUNT8 Period -------- */
typedef union {
  struct {
    uint8_t  PER:8;            /*!< bit:  0.. 7  Period Value                       */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} HW_TC_COUNT8_PER_Type;

#define HW_TC_COUNT8_PER_OFFSET        0x1B         /**< \brief (HW_TC_COUNT8_PER offset) COUNT8 Period */
#define HW_TC_COUNT8_PER_RESETVALUE    _U_(0xFF)    /**< \brief (HW_TC_COUNT8_PER reset_value) COUNT8 Period */

#define HW_TC_COUNT8_PER_PER_Pos       0            /**< \brief (HW_TC_COUNT8_PER) Period Value */
#define HW_TC_COUNT8_PER_PER_Msk       (_U_(0xFF) << HW_TC_COUNT8_PER_PER_Pos)
#define HW_TC_COUNT8_PER_PER(value)    (HW_TC_COUNT8_PER_PER_Msk & ((value) << HW_TC_COUNT8_PER_PER_Pos))
#define HW_TC_COUNT8_PER_MASK          _U_(0xFF)    /**< \brief (HW_TC_COUNT8_PER) MASK Register */

/* -------- HW_TC_COUNT16_CC : (HW_TC Offset: 0x1C) (R/W 16) COUNT16 COUNT16 Compare and Capture -------- */
typedef union {
  struct {
    uint16_t CC:16;            /*!< bit:  0..15  Counter/Compare Value              */
  } bit;                       /*!< Structure used for bit  access                  */
  uint16_t reg;                /*!< Type      used for register access              */
} HW_TC_COUNT16_CC_Type;

#define HW_TC_COUNT16_CC_OFFSET        0x1C         /**< \brief (HW_TC_COUNT16_CC offset) COUNT16 Compare and Capture */
#define HW_TC_COUNT16_CC_RESETVALUE    _U_(0x0000)  /**< \brief (HW_TC_COUNT16_CC reset_value) COUNT16 Compare and Capture */

#define HW_TC_COUNT16_CC_CC_Pos        0            /**< \brief (HW_TC_COUNT16_CC) Counter/Compare Value */
#define HW_TC_COUNT16_CC_CC_Msk        (_U_(0xFFFF) << HW_TC_COUNT16_CC_CC_Pos)
#define HW_TC_COUNT16_CC_CC(value)     (HW_TC_COUNT16_CC_CC_Msk & ((value) << HW_TC_COUNT16_CC_CC_Pos))
#define HW_TC_COUNT16_CC_MASK          _U_(0xFFFF)  /**< \brief (HW_TC_COUNT16_CC) MASK Register */

/* -------- HW_TC_COUNT32_CC : (HW_TC Offset: 0x1C) (R/W 32) COUNT32 COUNT32 Compare and Capture -------- */
typedef union {
  struct {
    uint32_t CC:32;            /*!< bit:  0..31  Counter/Compare Value              */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} HW_TC_COUNT32_CC_Type;

#define HW_TC_COUNT32_CC_OFFSET        0x1C         /**< \brief (HW_TC_COUNT32_CC offset) COUNT32 Compare and Capture */
#define HW_TC_COUNT32_CC_RESETVALUE    _U_(0x00000000) /**< \brief (HW_TC_COUNT32_CC reset_value) COUNT32 Compare and Capture */

#define HW_TC_COUNT32_CC_CC_Pos        0            /**< \brief (HW_TC_COUNT32_CC) Counter/Compare Value */
#define HW_TC_COUNT32_CC_CC_Msk        (_U_(0xFFFFFFFF) << HW_TC_COUNT32_CC_CC_Pos)
#define HW_TC_COUNT32_CC_CC(value)     (HW_TC_COUNT32_CC_CC_Msk & ((value) << HW_TC_COUNT32_CC_CC_Pos))
#define HW_TC_COUNT32_CC_MASK          _U_(0xFFFFFFFF) /**< \brief (HW_TC_COUNT32_CC) MASK Register */

/* -------- HW_TC_COUNT8_CC : (HW_TC Offset: 0x1C) (R/W  8) COUNT8 COUNT8 Compare and Capture -------- */
typedef union {
  struct {
    uint8_t  CC:8;             /*!< bit:  0.. 7  Counter/Compare Value              */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} HW_TC_COUNT8_CC_Type;

#define HW_TC_COUNT8_CC_OFFSET         0x1C         /**< \brief (HW_TC_COUNT8_CC offset) COUNT8 Compare and Capture */
#define HW_TC_COUNT8_CC_RESETVALUE     _U_(0x00)    /**< \brief (HW_TC_COUNT8_CC reset_value) COUNT8 Compare and Capture */

#define HW_TC_COUNT8_CC_CC_Pos         0            /**< \brief (HW_TC_COUNT8_CC) Counter/Compare Value */
#define HW_TC_COUNT8_CC_CC_Msk         (_U_(0xFF) << HW_TC_COUNT8_CC_CC_Pos)
#define HW_TC_COUNT8_CC_CC(value)      (HW_TC_COUNT8_CC_CC_Msk & ((value) << HW_TC_COUNT8_CC_CC_Pos))
#define HW_TC_COUNT8_CC_MASK           _U_(0xFF)    /**< \brief (HW_TC_COUNT8_CC) MASK Register */

/* -------- HW_TC_COUNT8_PERBUF : (HW_TC Offset: 0x2F) (R/W  8) COUNT8 COUNT8 Period Buffer -------- */
typedef union {
  struct {
    uint8_t  PERBUF:8;         /*!< bit:  0.. 7  Period Buffer Value                */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} HW_TC_COUNT8_PERBUF_Type;

#define HW_TC_COUNT8_PERBUF_OFFSET     0x2F         /**< \brief (HW_TC_COUNT8_PERBUF offset) COUNT8 Period Buffer */
#define HW_TC_COUNT8_PERBUF_RESETVALUE _U_(0xFF)    /**< \brief (HW_TC_COUNT8_PERBUF reset_value) COUNT8 Period Buffer */

#define HW_TC_COUNT8_PERBUF_PERBUF_Pos 0            /**< \brief (HW_TC_COUNT8_PERBUF) Period Buffer Value */
#define HW_TC_COUNT8_PERBUF_PERBUF_Msk (_U_(0xFF) << HW_TC_COUNT8_PERBUF_PERBUF_Pos)
#define HW_TC_COUNT8_PERBUF_PERBUF(value) (HW_TC_COUNT8_PERBUF_PERBUF_Msk & ((value) << HW_TC_COUNT8_PERBUF_PERBUF_Pos))
#define HW_TC_COUNT8_PERBUF_MASK       _U_(0xFF)    /**< \brief (HW_TC_COUNT8_PERBUF) MASK Register */

/* -------- HW_TC_COUNT16_CCBUF : (HW_TC Offset: 0x30) (R/W 16) COUNT16 COUNT16 Compare and Capture Buffer -------- */
typedef union {
  struct {
    uint16_t CCBUF:16;         /*!< bit:  0..15  Counter/Compare Buffer Value       */
  } bit;                       /*!< Structure used for bit  access                  */
  uint16_t reg;                /*!< Type      used for register access              */
} HW_TC_COUNT16_CCBUF_Type;

#define HW_TC_COUNT16_CCBUF_OFFSET     0x30         /**< \brief (HW_TC_COUNT16_CCBUF offset) COUNT16 Compare and Capture Buffer */
#define HW_TC_COUNT16_CCBUF_RESETVALUE _U_(0x0000)  /**< \brief (HW_TC_COUNT16_CCBUF reset_value) COUNT16 Compare and Capture Buffer */

#define HW_TC_COUNT16_CCBUF_CCBUF_Pos  0            /**< \brief (HW_TC_COUNT16_CCBUF) Counter/Compare Buffer Value */
#define HW_TC_COUNT16_CCBUF_CCBUF_Msk  (_U_(0xFFFF) << HW_TC_COUNT16_CCBUF_CCBUF_Pos)
#define HW_TC_COUNT16_CCBUF_CCBUF(value) (HW_TC_COUNT16_CCBUF_CCBUF_Msk & ((value) << HW_TC_COUNT16_CCBUF_CCBUF_Pos))
#define HW_TC_COUNT16_CCBUF_MASK       _U_(0xFFFF)  /**< \brief (HW_TC_COUNT16_CCBUF) MASK Register */

/* -------- HW_TC_COUNT32_CCBUF : (HW_TC Offset: 0x30) (R/W 32) COUNT32 COUNT32 Compare and Capture Buffer -------- */
typedef union {
  struct {
    uint32_t CCBUF:32;         /*!< bit:  0..31  Counter/Compare Buffer Value       */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} HW_TC_COUNT32_CCBUF_Type;

#define HW_TC_COUNT32_CCBUF_OFFSET     0x30         /**< \brief (HW_TC_COUNT32_CCBUF offset) COUNT32 Compare and Capture Buffer */
#define HW_TC_COUNT32_CCBUF_RESETVALUE _U_(0x00000000) /**< \brief (HW_TC_COUNT32_CCBUF reset_value) COUNT32 Compare and Capture Buffer */

#define HW_TC_COUNT32_CCBUF_CCBUF_Pos  0            /**< \brief (HW_TC_COUNT32_CCBUF) Counter/Compare Buffer Value */
#define HW_TC_COUNT32_CCBUF_CCBUF_Msk  (_U_(0xFFFFFFFF) << HW_TC_COUNT32_CCBUF_CCBUF_Pos)
#define HW_TC_COUNT32_CCBUF_CCBUF(value) (HW_TC_COUNT32_CCBUF_CCBUF_Msk & ((value) << HW_TC_COUNT32_CCBUF_CCBUF_Pos))
#define HW_TC_COUNT32_CCBUF_MASK       _U_(0xFFFFFFFF) /**< \brief (HW_TC_COUNT32_CCBUF) MASK Register */

/* -------- HW_TC_COUNT8_CCBUF : (HW_TC Offset: 0x30) (R/W  8) COUNT8 COUNT8 Compare and Capture Buffer -------- */
typedef union {
  struct {
    uint8_t  CCBUF:8;          /*!< bit:  0.. 7  Counter/Compare Buffer Value       */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} HW_TC_COUNT8_CCBUF_Type;

#define HW_TC_COUNT8_CCBUF_OFFSET      0x30         /**< \brief (HW_TC_COUNT8_CCBUF offset) COUNT8 Compare and Capture Buffer */
#define HW_TC_COUNT8_CCBUF_RESETVALUE  _U_(0x00)    /**< \brief (HW_TC_COUNT8_CCBUF reset_value) COUNT8 Compare and Capture Buffer */

#define HW_TC_COUNT8_CCBUF_CCBUF_Pos   0            /**< \brief (HW_TC_COUNT8_CCBUF) Counter/Compare Buffer Value */
#define HW_TC_COUNT8_CCBUF_CCBUF_Msk   (_U_(0xFF) << HW_TC_COUNT8_CCBUF_CCBUF_Pos)
#define HW_TC_COUNT8_CCBUF_CCBUF(value) (HW_TC_COUNT8_CCBUF_CCBUF_Msk & ((value) << HW_TC_COUNT8_CCBUF_CCBUF_Pos))
#define HW_TC_COUNT8_CCBUF_MASK        _U_(0xFF)    /**< \brief (HW_TC_COUNT8_CCBUF) MASK Register */

/** \brief HW_TC_COUNT8 hardware registers */
typedef struct { /* 8-bit Counter Mode */
  __IO HW_TC_CTRLA_Type             CTRLA;       /**< \brief Offset: 0x00 (R/W 32) Control A */
  __IO HW_TC_CTRLBCLR_Type          CTRLBCLR;    /**< \brief Offset: 0x04 (R/W  8) Control B Clear */
  __IO HW_TC_CTRLBSET_Type          CTRLBSET;    /**< \brief Offset: 0x05 (R/W  8) Control B Set */
  __IO HW_TC_EVCTRL_Type            EVCTRL;      /**< \brief Offset: 0x06 (R/W 16) Event Control */
  __IO HW_TC_INTENCLR_Type          INTENCLR;    /**< \brief Offset: 0x08 (R/W  8) Interrupt Enable Clear */
  __IO HW_TC_INTENSET_Type          INTENSET;    /**< \brief Offset: 0x09 (R/W  8) Interrupt Enable Set */
  __IO HW_TC_INTFLAG_Type           INTFLAG;     /**< \brief Offset: 0x0A (R/W  8) Interrupt Flag Status and Clear */
  __IO HW_TC_STATUS_Type            STATUS;      /**< \brief Offset: 0x0B (R/W  8) Status */
  __IO HW_TC_WAVE_Type              WAVE;        /**< \brief Offset: 0x0C (R/W  8) Waveform Generation Control */
  __IO HW_TC_DRVCTRL_Type           DRVCTRL;     /**< \brief Offset: 0x0D (R/W  8) Control C */
       RoReg8                    Reserved1[0x1];
  __IO HW_TC_DBGCTRL_Type           DBGCTRL;     /**< \brief Offset: 0x0F (R/W  8) Debug Control */
  __I  HW_TC_SYNCBUSY_Type          SYNCBUSY;    /**< \brief Offset: 0x10 (R/  32) Synchronization Status */
  __IO HW_TC_COUNT8_COUNT_Type      COUNT;       /**< \brief Offset: 0x14 (R/W  8) COUNT8 Count */
       RoReg8                    Reserved2[0x6];
  __IO HW_TC_COUNT8_PER_Type        PER;         /**< \brief Offset: 0x1B (R/W  8) COUNT8 Period */
  __IO HW_TC_COUNT8_CC_Type         CC[2];       /**< \brief Offset: 0x1C (R/W  8) COUNT8 Compare and Capture */
       RoReg8                    Reserved3[0x11];
  __IO HW_TC_COUNT8_PERBUF_Type     PERBUF;      /**< \brief Offset: 0x2F (R/W  8) COUNT8 Period Buffer */
  __IO HW_TC_COUNT8_CCBUF_Type      CCBUF[2];    /**< \brief Offset: 0x30 (R/W  8) COUNT8 Compare and Capture Buffer */
} TcCount8;

/** \brief HW_TC_COUNT16 hardware registers */
typedef struct { /* 16-bit Counter Mode */
  __IO HW_TC_CTRLA_Type             CTRLA;       /**< \brief Offset: 0x00 (R/W 32) Control A */
  __IO HW_TC_CTRLBCLR_Type          CTRLBCLR;    /**< \brief Offset: 0x04 (R/W  8) Control B Clear */
  __IO HW_TC_CTRLBSET_Type          CTRLBSET;    /**< \brief Offset: 0x05 (R/W  8) Control B Set */
  __IO HW_TC_EVCTRL_Type            EVCTRL;      /**< \brief Offset: 0x06 (R/W 16) Event Control */
  __IO HW_TC_INTENCLR_Type          INTENCLR;    /**< \brief Offset: 0x08 (R/W  8) Interrupt Enable Clear */
  __IO HW_TC_INTENSET_Type          INTENSET;    /**< \brief Offset: 0x09 (R/W  8) Interrupt Enable Set */
  __IO HW_TC_INTFLAG_Type           INTFLAG;     /**< \brief Offset: 0x0A (R/W  8) Interrupt Flag Status and Clear */
  __IO HW_TC_STATUS_Type            STATUS;      /**< \brief Offset: 0x0B (R/W  8) Status */
  __IO HW_TC_WAVE_Type              WAVE;        /**< \brief Offset: 0x0C (R/W  8) Waveform Generation Control */
  __IO HW_TC_DRVCTRL_Type           DRVCTRL;     /**< \brief Offset: 0x0D (R/W  8) Control C */
       RoReg8                    Reserved1[0x1];
  __IO HW_TC_DBGCTRL_Type           DBGCTRL;     /**< \brief Offset: 0x0F (R/W  8) Debug Control */
  __I  HW_TC_SYNCBUSY_Type          SYNCBUSY;    /**< \brief Offset: 0x10 (R/  32) Synchronization Status */
  __IO HW_TC_COUNT16_COUNT_Type     COUNT;       /**< \brief Offset: 0x14 (R/W 16) COUNT16 Count */
       RoReg8                    Reserved2[0x6];
  __IO HW_TC_COUNT16_CC_Type        CC[2];       /**< \brief Offset: 0x1C (R/W 16) COUNT16 Compare and Capture */
       RoReg8                    Reserved3[0x10];
  __IO HW_TC_COUNT16_CCBUF_Type     CCBUF[2];    /**< \brief Offset: 0x30 (R/W 16) COUNT16 Compare and Capture Buffer */
} TcCount16;

/** \brief HW_TC_COUNT32 hardware registers */
typedef struct { /* 32-bit Counter Mode */
  __IO HW_TC_CTRLA_Type             CTRLA;       /**< \brief Offset: 0x00 (R/W 32) Control A */
  __IO HW_TC_CTRLBCLR_Type          CTRLBCLR;    /**< \brief Offset: 0x04 (R/W  8) Control B Clear */
  __IO HW_TC_CTRLBSET_Type          CTRLBSET;    /**< \brief Offset: 0x05 (R/W  8) Control B Set */
  __IO HW_TC_EVCTRL_Type            EVCTRL;      /**< \brief Offset: 0x06 (R/W 16) Event Control */
  __IO HW_TC_INTENCLR_Type          INTENCLR;    /**< \brief Offset: 0x08 (R/W  8) Interrupt Enable Clear */
  __IO HW_TC_INTENSET_Type          INTENSET;    /**< \brief Offset: 0x09 (R/W  8) Interrupt Enable Set */
  __IO HW_TC_INTFLAG_Type           INTFLAG;     /**< \brief Offset: 0x0A (R/W  8) Interrupt Flag Status and Clear */
  __IO HW_TC_STATUS_Type            STATUS;      /**< \brief Offset: 0x0B (R/W  8) Status */
  __IO HW_TC_WAVE_Type              WAVE;        /**< \brief Offset: 0x0C (R/W  8) Waveform Generation Control */
  __IO HW_TC_DRVCTRL_Type           DRVCTRL;     /**< \brief Offset: 0x0D (R/W  8) Control C */
       RoReg8                    Reserved1[0x1];
  __IO HW_TC_DBGCTRL_Type           DBGCTRL;     /**< \brief Offset: 0x0F (R/W  8) Debug Control */
  __I  HW_TC_SYNCBUSY_Type          SYNCBUSY;    /**< \brief Offset: 0x10 (R/  32) Synchronization Status */
  __IO HW_TC_COUNT32_COUNT_Type     COUNT;       /**< \brief Offset: 0x14 (R/W 32) COUNT32 Count */
       RoReg8                    Reserved2[0x4];
  __IO HW_TC_COUNT32_CC_Type        CC[2];       /**< \brief Offset: 0x1C (R/W 32) COUNT32 Compare and Capture */
       RoReg8                    Reserved3[0xC];
  __IO HW_TC_COUNT32_CCBUF_Type     CCBUF[2];    /**< \brief Offset: 0x30 (R/W 32) COUNT32 Compare and Capture Buffer */
} TcCount32;

typedef union {
       TcCount8                  COUNT8;      /**< \brief Offset: 0x00 8-bit Counter Mode */
       TcCount16                 COUNT16;     /**< \brief Offset: 0x00 16-bit Counter Mode */
       TcCount32                 COUNT32;     /**< \brief Offset: 0x00 32-bit Counter Mode */
} Tc;


/* ========== Register definition for HW_TC0 peripheral ========== */
#define HW_REG_TC0_CTRLA              (*(RwReg  *)0x42002000UL) /**< \brief (HW_TC0) Control A */
#define HW_REG_TC0_CTRLBCLR           (*(RwReg8 *)0x42002004UL) /**< \brief (HW_TC0) Control B Clear */
#define HW_REG_TC0_CTRLBSET           (*(RwReg8 *)0x42002005UL) /**< \brief (HW_TC0) Control B Set */
#define HW_REG_TC0_EVCTRL             (*(RwReg16*)0x42002006UL) /**< \brief (HW_TC0) Event Control */
#define HW_REG_TC0_INTENCLR           (*(RwReg8 *)0x42002008UL) /**< \brief (HW_TC0) Interrupt Enable Clear */
#define HW_REG_TC0_INTENSET           (*(RwReg8 *)0x42002009UL) /**< \brief (HW_TC0) Interrupt Enable Set */
#define HW_REG_TC0_INTFLAG            (*(RwReg8 *)0x4200200AUL) /**< \brief (HW_TC0) Interrupt Flag Status and Clear */
#define HW_REG_TC0_STATUS             (*(RwReg8 *)0x4200200BUL) /**< \brief (HW_TC0) Status */
#define HW_REG_TC0_WAVE               (*(RwReg8 *)0x4200200CUL) /**< \brief (HW_TC0) Waveform Generation Control */
#define HW_REG_TC0_DRVCTRL            (*(RwReg8 *)0x4200200DUL) /**< \brief (HW_TC0) Control C */
#define HW_REG_TC0_DBGCTRL            (*(RwReg8 *)0x4200200FUL) /**< \brief (HW_TC0) Debug Control */
#define HW_REG_TC0_SYNCBUSY           (*(RoReg  *)0x42002010UL) /**< \brief (HW_TC0) Synchronization Status */
#define HW_REG_TC0_COUNT16_COUNT      (*(RwReg16*)0x42002014UL) /**< \brief (HW_TC0) COUNT16 Count */
#define HW_REG_TC0_COUNT16_CC0        (*(RwReg16*)0x4200201CUL) /**< \brief (HW_TC0) COUNT16 Compare and Capture 0 */
#define HW_REG_TC0_COUNT16_CC1        (*(RwReg16*)0x4200201EUL) /**< \brief (HW_TC0) COUNT16 Compare and Capture 1 */
#define HW_REG_TC0_COUNT16_CCBUF0     (*(RwReg16*)0x42002030UL) /**< \brief (HW_TC0) COUNT16 Compare and Capture Buffer 0 */
#define HW_REG_TC0_COUNT16_CCBUF1     (*(RwReg16*)0x42002032UL) /**< \brief (HW_TC0) COUNT16 Compare and Capture Buffer 1 */
#define HW_REG_TC0_COUNT32_COUNT      (*(RwReg  *)0x42002014UL) /**< \brief (HW_TC0) COUNT32 Count */
#define HW_REG_TC0_COUNT32_CC0        (*(RwReg  *)0x4200201CUL) /**< \brief (HW_TC0) COUNT32 Compare and Capture 0 */
#define HW_REG_TC0_COUNT32_CC1        (*(RwReg  *)0x42002020UL) /**< \brief (HW_TC0) COUNT32 Compare and Capture 1 */
#define HW_REG_TC0_COUNT32_CCBUF0     (*(RwReg  *)0x42002030UL) /**< \brief (HW_TC0) COUNT32 Compare and Capture Buffer 0 */
#define HW_REG_TC0_COUNT32_CCBUF1     (*(RwReg  *)0x42002034UL) /**< \brief (HW_TC0) COUNT32 Compare and Capture Buffer 1 */
#define HW_REG_TC0_COUNT8_COUNT       (*(RwReg8 *)0x42002014UL) /**< \brief (HW_TC0) COUNT8 Count */
#define HW_REG_TC0_COUNT8_PER         (*(RwReg8 *)0x4200201BUL) /**< \brief (HW_TC0) COUNT8 Period */
#define HW_REG_TC0_COUNT8_CC0         (*(RwReg8 *)0x4200201CUL) /**< \brief (HW_TC0) COUNT8 Compare and Capture 0 */
#define HW_REG_TC0_COUNT8_CC1         (*(RwReg8 *)0x4200201DUL) /**< \brief (HW_TC0) COUNT8 Compare and Capture 1 */
#define HW_REG_TC0_COUNT8_PERBUF      (*(RwReg8 *)0x4200202FUL) /**< \brief (HW_TC0) COUNT8 Period Buffer */
#define HW_REG_TC0_COUNT8_CCBUF0      (*(RwReg8 *)0x42002030UL) /**< \brief (HW_TC0) COUNT8 Compare and Capture Buffer 0 */
#define HW_REG_TC0_COUNT8_CCBUF1      (*(RwReg8 *)0x42002031UL) /**< \brief (HW_TC0) COUNT8 Compare and Capture Buffer 1 */

/* ========== Instance parameters for HW_TC0 peripheral ========== */
#define HW_TC0_CC_NUM                  2       
#define HW_TC0_DMAC_ID_MC_0            23
#define HW_TC0_DMAC_ID_MC_1            24
#define HW_TC0_DMAC_ID_MC_LSB          23
#define HW_TC0_DMAC_ID_MC_MSB          24
#define HW_TC0_DMAC_ID_MC_SIZE         2
#define HW_TC0_DMAC_ID_OVF             22       // Indexes of DMA Overflow trigger
#define HW_TC0_EXT                     0       
#define HW_TC0_GCLK_ID                 27      
#define HW_TC0_MASTER                  1       
#define HW_TC0_OW_NUM                  2       

/* ========== Register definition for HW_TC1 peripheral ========== */
#define HW_REG_TC1_CTRLA              (*(RwReg  *)0x42002400UL) /**< \brief (HW_TC1) Control A */
#define HW_REG_TC1_CTRLBCLR           (*(RwReg8 *)0x42002404UL) /**< \brief (HW_TC1) Control B Clear */
#define HW_REG_TC1_CTRLBSET           (*(RwReg8 *)0x42002405UL) /**< \brief (HW_TC1) Control B Set */
#define HW_REG_TC1_EVCTRL             (*(RwReg16*)0x42002406UL) /**< \brief (HW_TC1) Event Control */
#define HW_REG_TC1_INTENCLR           (*(RwReg8 *)0x42002408UL) /**< \brief (HW_TC1) Interrupt Enable Clear */
#define HW_REG_TC1_INTENSET           (*(RwReg8 *)0x42002409UL) /**< \brief (HW_TC1) Interrupt Enable Set */
#define HW_REG_TC1_INTFLAG            (*(RwReg8 *)0x4200240AUL) /**< \brief (HW_TC1) Interrupt Flag Status and Clear */
#define HW_REG_TC1_STATUS             (*(RwReg8 *)0x4200240BUL) /**< \brief (HW_TC1) Status */
#define HW_REG_TC1_WAVE               (*(RwReg8 *)0x4200240CUL) /**< \brief (HW_TC1) Waveform Generation Control */
#define HW_REG_TC1_DRVCTRL            (*(RwReg8 *)0x4200240DUL) /**< \brief (HW_TC1) Control C */
#define HW_REG_TC1_DBGCTRL            (*(RwReg8 *)0x4200240FUL) /**< \brief (HW_TC1) Debug Control */
#define HW_REG_TC1_SYNCBUSY           (*(RoReg  *)0x42002410UL) /**< \brief (HW_TC1) Synchronization Status */
#define HW_REG_TC1_COUNT16_COUNT      (*(RwReg16*)0x42002414UL) /**< \brief (HW_TC1) COUNT16 Count */
#define HW_REG_TC1_COUNT16_CC0        (*(RwReg16*)0x4200241CUL) /**< \brief (HW_TC1) COUNT16 Compare and Capture 0 */
#define HW_REG_TC1_COUNT16_CC1        (*(RwReg16*)0x4200241EUL) /**< \brief (HW_TC1) COUNT16 Compare and Capture 1 */
#define HW_REG_TC1_COUNT16_CCBUF0     (*(RwReg16*)0x42002430UL) /**< \brief (HW_TC1) COUNT16 Compare and Capture Buffer 0 */
#define HW_REG_TC1_COUNT16_CCBUF1     (*(RwReg16*)0x42002432UL) /**< \brief (HW_TC1) COUNT16 Compare and Capture Buffer 1 */
#define HW_REG_TC1_COUNT32_COUNT      (*(RwReg  *)0x42002414UL) /**< \brief (HW_TC1) COUNT32 Count */
#define HW_REG_TC1_COUNT32_CC0        (*(RwReg  *)0x4200241CUL) /**< \brief (HW_TC1) COUNT32 Compare and Capture 0 */
#define HW_REG_TC1_COUNT32_CC1        (*(RwReg  *)0x42002420UL) /**< \brief (HW_TC1) COUNT32 Compare and Capture 1 */
#define HW_REG_TC1_COUNT32_CCBUF0     (*(RwReg  *)0x42002430UL) /**< \brief (HW_TC1) COUNT32 Compare and Capture Buffer 0 */
#define HW_REG_TC1_COUNT32_CCBUF1     (*(RwReg  *)0x42002434UL) /**< \brief (HW_TC1) COUNT32 Compare and Capture Buffer 1 */
#define HW_REG_TC1_COUNT8_COUNT       (*(RwReg8 *)0x42002414UL) /**< \brief (HW_TC1) COUNT8 Count */
#define HW_REG_TC1_COUNT8_PER         (*(RwReg8 *)0x4200241BUL) /**< \brief (HW_TC1) COUNT8 Period */
#define HW_REG_TC1_COUNT8_CC0         (*(RwReg8 *)0x4200241CUL) /**< \brief (HW_TC1) COUNT8 Compare and Capture 0 */
#define HW_REG_TC1_COUNT8_CC1         (*(RwReg8 *)0x4200241DUL) /**< \brief (HW_TC1) COUNT8 Compare and Capture 1 */
#define HW_REG_TC1_COUNT8_PERBUF      (*(RwReg8 *)0x4200242FUL) /**< \brief (HW_TC1) COUNT8 Period Buffer */
#define HW_REG_TC1_COUNT8_CCBUF0      (*(RwReg8 *)0x42002430UL) /**< \brief (HW_TC1) COUNT8 Compare and Capture Buffer 0 */
#define HW_REG_TC1_COUNT8_CCBUF1      (*(RwReg8 *)0x42002431UL) /**< \brief (HW_TC1) COUNT8 Compare and Capture Buffer 1 */

/* ========== Instance parameters for HW_TC1 peripheral ========== */
#define HW_TC1_CC_NUM                  2       
#define HW_TC1_DMAC_ID_MC_0            26
#define HW_TC1_DMAC_ID_MC_1            27
#define HW_TC1_DMAC_ID_MC_LSB          26
#define HW_TC1_DMAC_ID_MC_MSB          27
#define HW_TC1_DMAC_ID_MC_SIZE         2
#define HW_TC1_DMAC_ID_OVF             25       // Indexes of DMA Overflow trigger
#define HW_TC1_EXT                     0       
#define HW_TC1_GCLK_ID                 27      
#define HW_TC1_MASTER                  0       
#define HW_TC1_OW_NUM                  2       

/* ========== Register definition for HW_TC2 peripheral ========== */
#define HW_REG_TC2_CTRLA              (*(RwReg  *)0x42002800UL) /**< \brief (HW_TC2) Control A */
#define HW_REG_TC2_CTRLBCLR           (*(RwReg8 *)0x42002804UL) /**< \brief (HW_TC2) Control B Clear */
#define HW_REG_TC2_CTRLBSET           (*(RwReg8 *)0x42002805UL) /**< \brief (HW_TC2) Control B Set */
#define HW_REG_TC2_EVCTRL             (*(RwReg16*)0x42002806UL) /**< \brief (HW_TC2) Event Control */
#define HW_REG_TC2_INTENCLR           (*(RwReg8 *)0x42002808UL) /**< \brief (HW_TC2) Interrupt Enable Clear */
#define HW_REG_TC2_INTENSET           (*(RwReg8 *)0x42002809UL) /**< \brief (HW_TC2) Interrupt Enable Set */
#define HW_REG_TC2_INTFLAG            (*(RwReg8 *)0x4200280AUL) /**< \brief (HW_TC2) Interrupt Flag Status and Clear */
#define HW_REG_TC2_STATUS             (*(RwReg8 *)0x4200280BUL) /**< \brief (HW_TC2) Status */
#define HW_REG_TC2_WAVE               (*(RwReg8 *)0x4200280CUL) /**< \brief (HW_TC2) Waveform Generation Control */
#define HW_REG_TC2_DRVCTRL            (*(RwReg8 *)0x4200280DUL) /**< \brief (HW_TC2) Control C */
#define HW_REG_TC2_DBGCTRL            (*(RwReg8 *)0x4200280FUL) /**< \brief (HW_TC2) Debug Control */
#define HW_REG_TC2_SYNCBUSY           (*(RoReg  *)0x42002810UL) /**< \brief (HW_TC2) Synchronization Status */
#define HW_REG_TC2_COUNT16_COUNT      (*(RwReg16*)0x42002814UL) /**< \brief (HW_TC2) COUNT16 Count */
#define HW_REG_TC2_COUNT16_CC0        (*(RwReg16*)0x4200281CUL) /**< \brief (HW_TC2) COUNT16 Compare and Capture 0 */
#define HW_REG_TC2_COUNT16_CC1        (*(RwReg16*)0x4200281EUL) /**< \brief (HW_TC2) COUNT16 Compare and Capture 1 */
#define HW_REG_TC2_COUNT16_CCBUF0     (*(RwReg16*)0x42002830UL) /**< \brief (HW_TC2) COUNT16 Compare and Capture Buffer 0 */
#define HW_REG_TC2_COUNT16_CCBUF1     (*(RwReg16*)0x42002832UL) /**< \brief (HW_TC2) COUNT16 Compare and Capture Buffer 1 */
#define HW_REG_TC2_COUNT32_COUNT      (*(RwReg  *)0x42002814UL) /**< \brief (HW_TC2) COUNT32 Count */
#define HW_REG_TC2_COUNT32_CC0        (*(RwReg  *)0x4200281CUL) /**< \brief (HW_TC2) COUNT32 Compare and Capture 0 */
#define HW_REG_TC2_COUNT32_CC1        (*(RwReg  *)0x42002820UL) /**< \brief (HW_TC2) COUNT32 Compare and Capture 1 */
#define HW_REG_TC2_COUNT32_CCBUF0     (*(RwReg  *)0x42002830UL) /**< \brief (HW_TC2) COUNT32 Compare and Capture Buffer 0 */
#define HW_REG_TC2_COUNT32_CCBUF1     (*(RwReg  *)0x42002834UL) /**< \brief (HW_TC2) COUNT32 Compare and Capture Buffer 1 */
#define HW_REG_TC2_COUNT8_COUNT       (*(RwReg8 *)0x42002814UL) /**< \brief (HW_TC2) COUNT8 Count */
#define HW_REG_TC2_COUNT8_PER         (*(RwReg8 *)0x4200281BUL) /**< \brief (HW_TC2) COUNT8 Period */
#define HW_REG_TC2_COUNT8_CC0         (*(RwReg8 *)0x4200281CUL) /**< \brief (HW_TC2) COUNT8 Compare and Capture 0 */
#define HW_REG_TC2_COUNT8_CC1         (*(RwReg8 *)0x4200281DUL) /**< \brief (HW_TC2) COUNT8 Compare and Capture 1 */
#define HW_REG_TC2_COUNT8_PERBUF      (*(RwReg8 *)0x4200282FUL) /**< \brief (HW_TC2) COUNT8 Period Buffer */
#define HW_REG_TC2_COUNT8_CCBUF0      (*(RwReg8 *)0x42002830UL) /**< \brief (HW_TC2) COUNT8 Compare and Capture Buffer 0 */
#define HW_REG_TC2_COUNT8_CCBUF1      (*(RwReg8 *)0x42002831UL) /**< \brief (HW_TC2) COUNT8 Compare and Capture Buffer 1 */

/* ========== Instance parameters for HW_TC2 peripheral ========== */
#define HW_TC2_CC_NUM                  2       
#define HW_TC2_DMAC_ID_MC_0            29
#define HW_TC2_DMAC_ID_MC_1            30
#define HW_TC2_DMAC_ID_MC_LSB          29
#define HW_TC2_DMAC_ID_MC_MSB          30
#define HW_TC2_DMAC_ID_MC_SIZE         2
#define HW_TC2_DMAC_ID_OVF             28       // Indexes of DMA Overflow trigger
#define HW_TC2_EXT                     0       
#define HW_TC2_GCLK_ID                 28      
#define HW_TC2_MASTER                  1       
#define HW_TC2_OW_NUM                  2       

/* ========== Register definition for HW_TC3 peripheral ========== */
#define HW_REG_TC3_CTRLA              (*(RwReg  *)0x42002C00UL) /**< \brief (HW_TC3) Control A */
#define HW_REG_TC3_CTRLBCLR           (*(RwReg8 *)0x42002C04UL) /**< \brief (HW_TC3) Control B Clear */
#define HW_REG_TC3_CTRLBSET           (*(RwReg8 *)0x42002C05UL) /**< \brief (HW_TC3) Control B Set */
#define HW_REG_TC3_EVCTRL             (*(RwReg16*)0x42002C06UL) /**< \brief (HW_TC3) Event Control */
#define HW_REG_TC3_INTENCLR           (*(RwReg8 *)0x42002C08UL) /**< \brief (HW_TC3) Interrupt Enable Clear */
#define HW_REG_TC3_INTENSET           (*(RwReg8 *)0x42002C09UL) /**< \brief (HW_TC3) Interrupt Enable Set */
#define HW_REG_TC3_INTFLAG            (*(RwReg8 *)0x42002C0AUL) /**< \brief (HW_TC3) Interrupt Flag Status and Clear */
#define HW_REG_TC3_STATUS             (*(RwReg8 *)0x42002C0BUL) /**< \brief (HW_TC3) Status */
#define HW_REG_TC3_WAVE               (*(RwReg8 *)0x42002C0CUL) /**< \brief (HW_TC3) Waveform Generation Control */
#define HW_REG_TC3_DRVCTRL            (*(RwReg8 *)0x42002C0DUL) /**< \brief (HW_TC3) Control C */
#define HW_REG_TC3_DBGCTRL            (*(RwReg8 *)0x42002C0FUL) /**< \brief (HW_TC3) Debug Control */
#define HW_REG_TC3_SYNCBUSY           (*(RoReg  *)0x42002C10UL) /**< \brief (HW_TC3) Synchronization Status */
#define HW_REG_TC3_COUNT16_COUNT      (*(RwReg16*)0x42002C14UL) /**< \brief (HW_TC3) COUNT16 Count */
#define HW_REG_TC3_COUNT16_CC0        (*(RwReg16*)0x42002C1CUL) /**< \brief (HW_TC3) COUNT16 Compare and Capture 0 */
#define HW_REG_TC3_COUNT16_CC1        (*(RwReg16*)0x42002C1EUL) /**< \brief (HW_TC3) COUNT16 Compare and Capture 1 */
#define HW_REG_TC3_COUNT16_CCBUF0     (*(RwReg16*)0x42002C30UL) /**< \brief (HW_TC3) COUNT16 Compare and Capture Buffer 0 */
#define HW_REG_TC3_COUNT16_CCBUF1     (*(RwReg16*)0x42002C32UL) /**< \brief (HW_TC3) COUNT16 Compare and Capture Buffer 1 */
#define HW_REG_TC3_COUNT32_COUNT      (*(RwReg  *)0x42002C14UL) /**< \brief (HW_TC3) COUNT32 Count */
#define HW_REG_TC3_COUNT32_CC0        (*(RwReg  *)0x42002C1CUL) /**< \brief (HW_TC3) COUNT32 Compare and Capture 0 */
#define HW_REG_TC3_COUNT32_CC1        (*(RwReg  *)0x42002C20UL) /**< \brief (HW_TC3) COUNT32 Compare and Capture 1 */
#define HW_REG_TC3_COUNT32_CCBUF0     (*(RwReg  *)0x42002C30UL) /**< \brief (HW_TC3) COUNT32 Compare and Capture Buffer 0 */
#define HW_REG_TC3_COUNT32_CCBUF1     (*(RwReg  *)0x42002C34UL) /**< \brief (HW_TC3) COUNT32 Compare and Capture Buffer 1 */
#define HW_REG_TC3_COUNT8_COUNT       (*(RwReg8 *)0x42002C14UL) /**< \brief (HW_TC3) COUNT8 Count */
#define HW_REG_TC3_COUNT8_PER         (*(RwReg8 *)0x42002C1BUL) /**< \brief (HW_TC3) COUNT8 Period */
#define HW_REG_TC3_COUNT8_CC0         (*(RwReg8 *)0x42002C1CUL) /**< \brief (HW_TC3) COUNT8 Compare and Capture 0 */
#define HW_REG_TC3_COUNT8_CC1         (*(RwReg8 *)0x42002C1DUL) /**< \brief (HW_TC3) COUNT8 Compare and Capture 1 */
#define HW_REG_TC3_COUNT8_PERBUF      (*(RwReg8 *)0x42002C2FUL) /**< \brief (HW_TC3) COUNT8 Period Buffer */
#define HW_REG_TC3_COUNT8_CCBUF0      (*(RwReg8 *)0x42002C30UL) /**< \brief (HW_TC3) COUNT8 Compare and Capture Buffer 0 */
#define HW_REG_TC3_COUNT8_CCBUF1      (*(RwReg8 *)0x42002C31UL) /**< \brief (HW_TC3) COUNT8 Compare and Capture Buffer 1 */

/* ========== Instance parameters for HW_TC3 peripheral ========== */
#define HW_TC3_CC_NUM                  2       
#define HW_TC3_DMAC_ID_MC_0            32
#define HW_TC3_DMAC_ID_MC_1            33
#define HW_TC3_DMAC_ID_MC_LSB          32
#define HW_TC3_DMAC_ID_MC_MSB          33
#define HW_TC3_DMAC_ID_MC_SIZE         2
#define HW_TC3_DMAC_ID_OVF             31       // Indexes of DMA Overflow trigger
#define HW_TC3_EXT                     0       
#define HW_TC3_GCLK_ID                 28      
#define HW_TC3_MASTER                  0       
#define HW_TC3_OW_NUM                  2       

/* ========== Register definition for HW_TC4 peripheral ========== */
#define HW_REG_TC4_CTRLA              (*(RwReg  *)0x43000800UL) /**< \brief (HW_TC4) Control A */
#define HW_REG_TC4_CTRLBCLR           (*(RwReg8 *)0x43000804UL) /**< \brief (HW_TC4) Control B Clear */
#define HW_REG_TC4_CTRLBSET           (*(RwReg8 *)0x43000805UL) /**< \brief (HW_TC4) Control B Set */
#define HW_REG_TC4_EVCTRL             (*(RwReg16*)0x43000806UL) /**< \brief (HW_TC4) Event Control */
#define HW_REG_TC4_INTENCLR           (*(RwReg8 *)0x43000808UL) /**< \brief (HW_TC4) Interrupt Enable Clear */
#define HW_REG_TC4_INTENSET           (*(RwReg8 *)0x43000809UL) /**< \brief (HW_TC4) Interrupt Enable Set */
#define HW_REG_TC4_INTFLAG            (*(RwReg8 *)0x4300080AUL) /**< \brief (HW_TC4) Interrupt Flag Status and Clear */
#define HW_REG_TC4_STATUS             (*(RwReg8 *)0x4300080BUL) /**< \brief (HW_TC4) Status */
#define HW_REG_TC4_WAVE               (*(RwReg8 *)0x4300080CUL) /**< \brief (HW_TC4) Waveform Generation Control */
#define HW_REG_TC4_DRVCTRL            (*(RwReg8 *)0x4300080DUL) /**< \brief (HW_TC4) Control C */
#define HW_REG_TC4_DBGCTRL            (*(RwReg8 *)0x4300080FUL) /**< \brief (HW_TC4) Debug Control */
#define HW_REG_TC4_SYNCBUSY           (*(RoReg  *)0x43000810UL) /**< \brief (HW_TC4) Synchronization Status */
#define HW_REG_TC4_COUNT16_COUNT      (*(RwReg16*)0x43000814UL) /**< \brief (HW_TC4) COUNT16 Count */
#define HW_REG_TC4_COUNT16_CC0        (*(RwReg16*)0x4300081CUL) /**< \brief (HW_TC4) COUNT16 Compare and Capture 0 */
#define HW_REG_TC4_COUNT16_CC1        (*(RwReg16*)0x4300081EUL) /**< \brief (HW_TC4) COUNT16 Compare and Capture 1 */
#define HW_REG_TC4_COUNT16_CCBUF0     (*(RwReg16*)0x43000830UL) /**< \brief (HW_TC4) COUNT16 Compare and Capture Buffer 0 */
#define HW_REG_TC4_COUNT16_CCBUF1     (*(RwReg16*)0x43000832UL) /**< \brief (HW_TC4) COUNT16 Compare and Capture Buffer 1 */
#define HW_REG_TC4_COUNT32_COUNT      (*(RwReg  *)0x43000814UL) /**< \brief (HW_TC4) COUNT32 Count */
#define HW_REG_TC4_COUNT32_CC0        (*(RwReg  *)0x4300081CUL) /**< \brief (HW_TC4) COUNT32 Compare and Capture 0 */
#define HW_REG_TC4_COUNT32_CC1        (*(RwReg  *)0x43000820UL) /**< \brief (HW_TC4) COUNT32 Compare and Capture 1 */
#define HW_REG_TC4_COUNT32_CCBUF0     (*(RwReg  *)0x43000830UL) /**< \brief (HW_TC4) COUNT32 Compare and Capture Buffer 0 */
#define HW_REG_TC4_COUNT32_CCBUF1     (*(RwReg  *)0x43000834UL) /**< \brief (HW_TC4) COUNT32 Compare and Capture Buffer 1 */
#define HW_REG_TC4_COUNT8_COUNT       (*(RwReg8 *)0x43000814UL) /**< \brief (HW_TC4) COUNT8 Count */
#define HW_REG_TC4_COUNT8_PER         (*(RwReg8 *)0x4300081BUL) /**< \brief (HW_TC4) COUNT8 Period */
#define HW_REG_TC4_COUNT8_CC0         (*(RwReg8 *)0x4300081CUL) /**< \brief (HW_TC4) COUNT8 Compare and Capture 0 */
#define HW_REG_TC4_COUNT8_CC1         (*(RwReg8 *)0x4300081DUL) /**< \brief (HW_TC4) COUNT8 Compare and Capture 1 */
#define HW_REG_TC4_COUNT8_PERBUF      (*(RwReg8 *)0x4300082FUL) /**< \brief (HW_TC4) COUNT8 Period Buffer */
#define HW_REG_TC4_COUNT8_CCBUF0      (*(RwReg8 *)0x43000830UL) /**< \brief (HW_TC4) COUNT8 Compare and Capture Buffer 0 */
#define HW_REG_TC4_COUNT8_CCBUF1      (*(RwReg8 *)0x43000831UL) /**< \brief (HW_TC4) COUNT8 Compare and Capture Buffer 1 */

/* ========== Instance parameters for HW_TC4 peripheral ========== */
#define HW_TC4_CC_NUM                  2       
#define HW_TC4_DMAC_ID_MC_0            35
#define HW_TC4_DMAC_ID_MC_1            36
#define HW_TC4_DMAC_ID_MC_LSB          35
#define HW_TC4_DMAC_ID_MC_MSB          36
#define HW_TC4_DMAC_ID_MC_SIZE         2
#define HW_TC4_DMAC_ID_OVF             34       // Indexes of DMA Overflow trigger
#define HW_TC4_EXT                     0       
#define HW_TC4_GCLK_ID                 29      
#define HW_TC4_MASTER                  0       
#define HW_TC4_OW_NUM                  2       


#endif //HW_RAK4260_TC_H