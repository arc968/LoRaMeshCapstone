#if defined(HW_H) && !defined(MKRWAN1300_H)
	#error "Multiple hardware definitions"
#elif !defined(HW_H) && !defined(MKRWAN1300_H)
	#define HW_H
	#define MKRWAN1300_H
	#include "hw_mkrwan1300_registers.h"


#endif // HW_H MKRWAN1300_H