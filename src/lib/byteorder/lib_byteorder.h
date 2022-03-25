#ifndef LIB_BYTEORDER_H
#define LIB_BYTEORDER_H
#if defined (__cplusplus)
extern "C" {
#endif

#include <stdint.h>

#define LIB_BYTEORDER_SWAP_2(data) ( (((data) >> 8) & 0x00FF) | (((data) << 8) & 0xFF00) )

#define LIB_BYTEORDER_SWAP_4(data) \
( (((data) >> 24) & 0x000000FF) | (((data) >>  8) & 0x0000FF00) | \
  (((data) <<  8) & 0x00FF0000) | (((data) << 24) & 0xFF000000) )

#define LIB_BYTEORDER_SWAP_8(data) \
( (((data) >> 56) & 0x00000000000000FF) | (((data) >> 40) & 0x000000000000FF00) | \
  (((data) >> 24) & 0x0000000000FF0000) | (((data) >>  8) & 0x00000000FF000000) | \
  (((data) <<  8) & 0x000000FF00000000) | (((data) << 24) & 0x0000FF0000000000) | \
  (((data) << 40) & 0x00FF000000000000) | (((data) << 56) & 0xFF00000000000000) )

// Derived from https://stackoverflow.com/questions/4239993/determining-endianness-at-compile-time
#if (defined(__BYTE_ORDER) && (__BYTE_ORDER == __BIG_ENDIAN)) || \
	(defined(__BYTE_ORDER__) && (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)) || \
	defined(__BIG_ENDIAN__) || \
	defined(__BIG_ENDIAN) || \
	defined(_BIG_ENDIAN) || \
	defined(__ARMEB__) || \
	defined(__THUMBEB__) || \
	defined(__AARCH64EB__) || \
	defined(_MIBSEB) || defined(__MIBSEB) || defined(__MIBSEB__)
	// It's a big-endian target architecture
	#define LIB_BYTEORDER__BIG_ENDIAN
#elif (defined(__BYTE_ORDER) && (__BYTE_ORDER == __LITTLE_ENDIAN)) || \
	(defined(__BYTE_ORDER__) && (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)) || \
	defined(__LITTLE_ENDIAN__) || \
	defined(__LITTLE_ENDIAN) || \
	defined(_LITTLE_ENDIAN) || \
	defined(__ARMEL__) || \
	defined(__THUMBEL__) || \
	defined(__AARCH64EL__) || \
	defined(_MIPSEL) || defined(__MIPSEL) || defined(__MIPSEL__)
	// It's a little-endian target architecture
	#define LIB_BYTEORDER__LITTLE_ENDIAN
#else
	#error "Unable to determine architecture endianness."
#endif

#ifdef LIB_BYTEORDER__BIG_ENDIAN

	#define LIB_BYTEORDER_HTON_U16(data) ( (uint16_t)(data) )
	#define LIB_BYTEORDER_HTON_U32(data) ( (uint32_t)(data) )
	#define LIB_BYTEORDER_HTON_U64(data) ( (uint64_t)(data) )

	#define LIB_BYTEORDER_NTOH_U16(data) ( (uint16_t)(data) )
	#define LIB_BYTEORDER_NTOH_U32(data) ( (uint32_t)(data) )
	#define LIB_BYTEORDER_NTOH_U64(data) ( (uint64_t)(data) )

	#define LIB_BYTEORDER_HTOL_U16(data) ( ((uint16_t) LIB_BYTEORDER_SWAP_2((uint16_t)(data))) )
	#define LIB_BYTEORDER_HTOL_U32(data) ( ((uint32_t) LIB_BYTEORDER_SWAP_4((uint32_t)(data))) )
	#define LIB_BYTEORDER_HTOL_U64(data) ( ((uint64_t) LIB_BYTEORDER_SWAP_8((uint64_t)(data))) )

	#define LIB_BYTEORDER_LTOH_U16(data) ( ((uint16_t) LIB_BYTEORDER_SWAP_2((uint16_t)(data))) )
	#define LIB_BYTEORDER_LTOH_U32(data) ( ((uint32_t) LIB_BYTEORDER_SWAP_4((uint32_t)(data))) )
	#define LIB_BYTEORDER_LTOH_U64(data) ( ((uint64_t) LIB_BYTEORDER_SWAP_8((uint64_t)(data))) )

#endif

#ifdef LIB_BYTEORDER__LITTLE_ENDIAN

	#define LIB_BYTEORDER_HTON_U16(data) ( ((uint16_t) LIB_BYTEORDER_SWAP_2((uint16_t)(data))) )
	#define LIB_BYTEORDER_HTON_U32(data) ( ((uint32_t) LIB_BYTEORDER_SWAP_4((uint32_t)(data))) )
	#define LIB_BYTEORDER_HTON_U64(data) ( ((uint64_t) LIB_BYTEORDER_SWAP_8((uint64_t)(data))) )

	#define LIB_BYTEORDER_NTOH_U16(data) ( ((uint16_t) LIB_BYTEORDER_SWAP_2((uint16_t)(data))) )
	#define LIB_BYTEORDER_NTOH_U32(data) ( ((uint32_t) LIB_BYTEORDER_SWAP_4((uint32_t)(data))) )
	#define LIB_BYTEORDER_NTOH_U64(data) ( ((uint64_t) LIB_BYTEORDER_SWAP_8((uint64_t)(data))) )

	#define LIB_BYTEORDER_HTOL_U16(data) ( (uint16_t)(data) )
	#define LIB_BYTEORDER_HTOL_U32(data) ( (uint32_t)(data) )
	#define LIB_BYTEORDER_HTOL_U64(data) ( (uint64_t)(data) )

	#define LIB_BYTEORDER_LTOH_U16(data) ( (uint16_t)(data) )
	#define LIB_BYTEORDER_LTOH_U32(data) ( (uint32_t)(data) )
	#define LIB_BYTEORDER_LTOH_U64(data) ( (uint64_t)(data) )

#endif

#if defined (__cplusplus)
}
#endif
#endif // LIB_BYTEORDER_H