#if !defined(HW_LORA_SEMTECH_SCOPE)
	#error "Do not directly include this header file, include hardware.h instead."
#elif !defined(HW_LORA_SEMTECH_H)
#ifdef __cplusplus
extern "C" {
#endif
	#define HW_LORA_SCOPE

	#ifndef HW_LORA_SEMTECH
		#error "No Semtech LoRa hardware defined."
	#endif

	#define HW_LORA
	#define HW_LORA_SEMTECH_H
	#include "../hw_lora.h"

	#undef HW_LORA_SCOPE
	
#ifdef __cplusplus
}
#endif

#endif // HW_LORA_SEMTECH_H