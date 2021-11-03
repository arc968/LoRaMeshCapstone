#if defined(HW_H) && !defined(IBUG_H)
	#error "Multiple hardware definitions"
#elif !defined(HW_H) && !defined(IBUG_H)
	#define HW_H
	#define IBUG_H
	#include "ibug_registers.h"


#endif // HW_H IBUG_H