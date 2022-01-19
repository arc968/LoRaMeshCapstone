#if !defined(HARDWARE_H_SCOPE)
	#error "Do not directly include this header file, include hardware.h instead."
#elif !defined(HW_GPS_H)

	#if !defined(HW_GPS) && !defined(GPS_NONE)
		#error "No GPS hardware defined. Do not include hw_gps.h directly."
	#endif

	#define HW_GPS_H

#endif // HW_GPS_H