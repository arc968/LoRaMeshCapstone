/**
 * \addtogroup hwlayer Hardware Layer
 * @{
 */

/**
 * \file hardware.h
 * \brief This file uses the selected hardware from hw_config.h to include the selected
 * hardwares setup files.
 * 
 * The included setup file of the selected hardware is included into the library's
 * compiling to allow the code in the hardware abstraction layer to work on the selected
 * hardware.
 */

#ifndef HARDWARE_H
#define HARDWARE_H
#define HARDWARE_H_SCOPE

#ifdef __cplusplus
extern "C" {
#endif

#include "hw_config.h"

#if defined(MKRWAN1300)
	#include "mkrwan1300/hw_mkrwan1300.h"
#elif defined(RAK4260)
	#include "rak4260/hw_rak4260.h"
#elif defined(RAK4600)
	#include"rak4600/hw_rak4600.h"
#elif defined(RAK11300)
	#include"rak11300/hw_rak11300.h"
#else
	#error "No hardware defined."
#endif

#if defined(GPS_UBLOX_NEO6)
	#include "gps/ublox/neo6/hw_gps_ublox_neo6.h"
#elif defined(GPS_RTC_DS3231)
	#include "gps/rtc/ds3231/hw_gps_rtc_ds3231.h"
#elif defined(GPS_NONE)
	#include "gps/hw_gps.h"
#else
	#error "No GPS hardware defined. Explicitly define GPS_NONE in hw_config.h if no GPS module is used."
#endif

#if defined(LORA_SEMTECH_SX1276)
	#include "lora/semtech/sx12xx/hw_lora_semtech_sx1276.h"
#elif defined(LORA_ARDUINO_MKRWAN1300)
	#include "lora/arduino/mkrwan1300/hw_lora_arduino_mkrwan1300.h"
#elif defined(LORA_NONE)
	#include "lora/hw_lora.h"
#else
	#error "No LoRa hardware defined. Explicitly define LORA_NONE in hw_config.h if no LoRa module is used."
#endif

#ifdef __cplusplus
}
#endif

#ifdef HW_ARDUINO
	#include <Arduino.h>
#endif

#undef HARDWARE_H_SCOPE
#endif // HARDWARE_H

/** @} */ // end of hwlayer group