#if defined(HW_H) && !defined(HW_MKRWAN1300_H)
	#error "Multiple hardware definitions"
#elif !defined(HW_H) && !defined(HW_MKRWAN1300_H)
	#define HW_H
	#define HW_ARDUINO
	#define HW_MKRWAN1300_H
	#include "hw_mkrwan1300_registers.h"
	#include "Arduino.h"

#endif // HW_H MKRWAN1300_H