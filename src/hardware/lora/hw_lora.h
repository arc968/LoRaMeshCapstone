#if !defined(HW_LORA_SCOPE)
	#error "Do not directly include this header file, include hardware.h instead."
#elif !defined(HW_LORA_H)

	#if !defined(HW_LORA) && !defined(LORA_NONE)
		#error "No LoRa hardware defined."
	#endif

	#define HW_LORA_H

#endif // HW_LORA_H