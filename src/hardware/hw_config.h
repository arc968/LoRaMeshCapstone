/**
 * \addtogroup hwlayer Hardware Layer
 * @{
 */

/**
 * \file hw_config.h
 * \brief This file is used to select which hardware device the library code should be 
 * compiled for to work with. 
 * 
 * To use this file uncomment only one of the defined hardware names in the list. The
 * defines are the names of the supported hardware processors that this library can
 * be compiled for. Some hardware defines listed might support more than one hardware.
 * Uncommenting more than one define in the list will result in an error on compiling.
 */

#ifndef HW_CONFIG_H
#define HW_CONFIG_H
#ifdef __cplusplus
extern "C" {
#endif

#ifndef HARDWARE_H_SCOPE
	#error "Do not directly include this header file, include hardware.h instead."
#endif

//#define MKRWAN1300
#define RAK4260 //iBug
//#define RAK4600
//#define RAK11300

//#define GPS_NONE
#define GPS_UBLOX_NEO6

//#define LORA_NONE
//#define LORA_ARDUINO_MKRWAN1300
#define LORA_SEMTECH_SX1276

#ifdef __cplusplus
}
#endif
#endif // HW_CONFIG_H

/** @} */ // end of hwlayer group