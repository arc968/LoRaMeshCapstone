#if !defined(HARDWARE_H_SCOPE) && !defined(HW_LORA_SEMTECH_SX1276_C)
	#error "Do not directly include this header file, include hardware.h instead."
#elif defined(HW_LORA_H) && !defined(HW_LORA_SEMTECH_SX1276_H)
	#error "Multiple GPS hardware definitions."
#elif !defined(HW_LORA_SEMTECH_SX1276_H)
	#define HW_LORA_SEMTECH_SCOPE

	#define HW_LORA_SEMTECH
	#define HW_LORA_SEMTECH_SX1276_H
	#include "../hw_lora_semtech.h"
	
	#undef HW_LORA_SEMTECH_SCOPE
#endif // HW_LORA_SEMTECH_SX1276_H