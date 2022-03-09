#define HW_LORA_SEMTECH_SX1276_C
//#include "hw_lora_semtech_sx1276.h"
#include "../../../hardware.h"

#ifdef HW_LORA_SEMTECH_SX1276_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "../../../../hal/hal.h"
#include "../../../../lib/byteorder/lib_byteorder.h"
#include "../../../../drivers/lora/drv_lora.h"
#include "../../../../drivers/timer/drv_timer.h"
#include "../../../../drivers/sched/drv_sched.h"

void drv_lora_init(struct drv_lora_s * handle, pin_t pin) {
	
}

#endif // HW_LORA_SEMTECH_SX1276_H

#undef HW_LORA_SEMTECH_SX1276_C