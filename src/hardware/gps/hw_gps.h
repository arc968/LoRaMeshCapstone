#if !defined(HW_GPS_SCOPE)
	#error "Do not directly include this header file, include hardware.h instead."
#elif !defined(HW_GPS_H)

	#if !defined(HW_GPS) && !defined(GPS_NONE)
		#error "No GPS hardware defined."
	#endif

	#define HW_GPS_H

#endif // HW_GPS_H