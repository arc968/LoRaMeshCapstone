#ifndef DRV_H
#define DRV_H

#include "../hardware/hardware.h"

#ifdef __cplusplus
extern "C" {
#endif



//LoRa Drivers
#if defined(GPS_NONE)
	#warning "'gps/drv_gps.h' not included because GPS_NONE is defined."
#else
	#include "gps/drv_gps.h"
#endif
#if defined(LORA_NONE)
	#warning "'lora/drv_lora.h' not included because LORA_NONE is defined."
#else
	#include "lora/drv_lora.h"
#endif
#if defined(GPS_NONE) || defined(LORA_NONE)
	#warning "'mesh/drv_mesh.h' not included because GPS_NONE and/or LORA_NONE is defined."
#else
	#include "mesh/drv_mesh.h"
#endif
#include "timer/drv_timer.h"
#include "sched/drv_sched.h"

//Sensor Drivers
#include "sd/drv_sd.h"
#include "sensor/rtc/drv_rtc.h"
#include "sensor/accelerometer/drv_accelerometer.h"
#include "sensor/gas_sensor/drv_gas_sensor.h"
#include "sensor/co2_sensor/drv_co2_sensor.h"

#ifdef __cplusplus
}
#endif
#endif //DRV_H