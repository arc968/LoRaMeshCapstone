#if defined(HW_H) && !defined(HW_IBUG_H)
	#error "Multiple hardware definitions"
#elif !defined(HW_H) && !defined(HW_IBUG_H)

	#define HW_H
	#define HW_IBUG_H
	#include "hw_ibug_registers.h"

#endif // HW_H IBUG_H