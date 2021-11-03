#if defined(HW_H) && !defined(IBUG_H)
	#error "Multiple hardware definitions"
#else
	#define HW_H
	#define IBUG_H
#endif // HW_H

#ifdef IBUG_H
#include "ibug_registers.h"


#endif // IBUG_H