#if !defined(HW_LORA_SCOPE)
	#error "Do not directly include this header file, include hardware.h instead."
#elif !defined(HW_LORA_H)
#ifdef __cplusplus
extern "C" {
#endif

	#if !defined(HW_LORA) && !defined(LORA_NONE)
		#error "No LoRa hardware defined."
	#endif

	#define HW_LORA_H

#ifdef __cplusplus
}
#endif

#endif // HW_LORA_H