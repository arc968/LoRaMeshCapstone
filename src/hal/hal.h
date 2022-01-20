/**
 * \addtogroup hallayer Hardware Abstraction Layer
 * @{
 */

/**
 * \file hal.h
 * \brief This file is used to provide a simple one line include of all the hardware abstraction layer files.
 * 
 * To use this file uncomment all the hardware abstraction layer files you want to include in your file, and 
 * you then just need to include this one file using one line instead of a large include block like in this file.
 */


#ifndef HAL_H
#define HAL_H
#ifdef __cplusplus
extern "C" {
#endif

#include "hal_gpio.h"
#include "hal_i2c.h"
#include "hal_interrupt.h"
#include "hal_serial.h"
#include "hal_spi.h"
#include "hal_timer.h"
#include "hal_power.h"

#ifdef __cplusplus
}
#endif
#endif // HAL_H

/** @} */ // end of hallayer