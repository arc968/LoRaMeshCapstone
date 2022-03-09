#if !defined(HARDWARE_H_SCOPE) && !defined(HW_LORA_ARDUINO_MKRWAN1300_C)
	#error "Do not directly include this header file, include hardware.h instead."
#elif defined(HW_LORA_H) && !defined(HW_LORA_ARDUINO_MKRWAN1300_H)
	#error "Multiple GPS hardware definitions."
#elif !defined(HW_LORA_ARDUINO_MKRWAN1300_H)
#ifdef __cplusplus
extern "C" {
#endif

	#define HW_LORA_ARDUINO_SCOPE

	#define HW_LORA_ARDUINO
	#define HW_LORA_ARDUINO_MKRWAN1300_H
	#include "../hw_lora_arduino.h"
	
	#undef HW_LORA_ARDUINO_SCOPE
#ifdef __cplusplus
}
#endif

#endif // HW_LORA_ARDUINO_MKRWAN1300_H