#if !defined(HARDWARE_H_SCOPE) && !defined(HW_LORA_SEMTECH_SX1276_CPP)
	#error "Do not directly include this header file, include hardware.h instead."
#elif defined(HW_LORA_H) && !defined(HW_LORA_SEMTECH_SX1276_H)
	#error "Multiple LoRa hardware definitions."
#elif !defined(HW_LORA_SEMTECH_SX1276_H)
#ifdef __cplusplus
extern "C" {
#endif
	#define HW_LORA_SEMTECH_SCOPE

	#define HW_LORA_SEMTECH
	#define HW_LORA_SEMTECH_SX1276_H
	#include "../hw_lora_semtech.h"
	
	#undef HW_LORA_SEMTECH_SCOPE
#ifdef __cplusplus
}
#endif

#endif // HW_LORA_SEMTECH_SX1276_H