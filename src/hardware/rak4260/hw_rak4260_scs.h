#ifndef HW_RAK4260_SCS_H
#define HW_RAK4260_SCS_H


/* -------- SCS_AIRCR : (SCS Offset: 0x0C) (R/W  32) Application Interrupt and Reset Control Register -------- */
typedef union {
  struct {
    uint8_t  VECTRESET:1;              		/*!< bit:      0   Writing 1 to this bit causes a local system reset */
    volatile uint8_t  VECTCLRACTIVE:1;      /*!< bit:      1   VECTCLRACTIVE                     */
    uint8_t  SYSRESETREQ:1;            		/*!< bit:      2   System Reset Request, Writing 1 to this bit causes a local system reset */
    uint8_t  :6;          			   		/*!< bit:   3..7   Reserved                      */
    uint8_t  PRIGROUP:3;               		/*!< bit:  8..10   Priority grouping, indicates the binary point position. */
    uint8_t  :4;          			   		/*!< bit: 11..14   Reserved */
    uint8_t  ENDIANNESS:1;             		/*!< bit:     15   Indicates the memory system endianness */
    uint16_t  VECTKEY:16;              		/*!< bit: 16..31   Reserved */
  } bit;                       				/*!< Structure used for bit  access */
  uint32_t reg;                				/*!< Type      used for register access   */
} SCS_AIRCR_Type;

#endif //HW_RAK4260_SCS_H