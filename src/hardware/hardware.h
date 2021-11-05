#ifndef HARDWARE_H
#define HARDWARE_H

#include "hw_config.h"

#if defined(MKRWAN1300)
	#include "mkrwan1300/hw_mkrwan1300.h"
#elif defined(IBUG)
	#include "ibug/hw_ibug.h"
#else
	#error "No hardware defined"
#endif

#endif // HARDWARE_H