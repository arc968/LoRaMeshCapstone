#ifndef DRV_H
#define DRV_H

//LoRa Drivers
#if !defined(GPS_NONE)
	#include "gps/drv_gps.h"
#endif
#if !defined(LORA_NONE)
	#include "lora/drv_lora.h"
#endif
#if !defined(GPS_NONE) && !defined(LORA_NONE)
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

#endif //DRV_H