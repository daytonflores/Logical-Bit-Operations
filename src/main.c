#include <stdlib.h>
#include "bitops.h"

#define BINARY_PREFIX_BYTE (2)
#define NULL_TERMINATOR_BYTE (1)
#define UINT32_T_BITS (32)

int main(void) {
	char str[BINARY_PREFIX_BYTE + UINT32_T_BITS + NULL_TERMINATOR_BYTE];
	
	test_uint_to_binstr(str, (size_t)BINARY_PREFIX_BYTE + (size_t)UINT32_T_BITS + (size_t)NULL_TERMINATOR_BYTE, 0, (uint8_t)UINT32_T_BITS);
	test_int_to_binstr(str, (size_t)BINARY_PREFIX_BYTE + (size_t)UINT32_T_BITS + (size_t)NULL_TERMINATOR_BYTE, 0, (uint8_t)UINT32_T_BITS);

	return EXIT_SUCCESS;
}