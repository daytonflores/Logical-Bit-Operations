#include <stdlib.h>
#include "bitops.h"

#define PREFIX_BYTES_BIN (2)
#define PREFIX_BYTES_HEX (2)
#define NULL_TERMINATOR_BYTE (1)
#define UINT32_T_BITS (32)

int main(void) {
	char str[PREFIX_BYTES_BIN + UINT32_T_BITS + NULL_TERMINATOR_BYTE];
	
	test_uint_to_binstr(str, (size_t)PREFIX_BYTES_BIN + (size_t)UINT32_T_BITS + (size_t)NULL_TERMINATOR_BYTE, 0, (uint8_t)UINT32_T_BITS);
	test_int_to_binstr(str, (size_t)PREFIX_BYTES_BIN + (size_t)UINT32_T_BITS + (size_t)NULL_TERMINATOR_BYTE, 0, (uint8_t)UINT32_T_BITS);
	test_uint_to_hexstr(str, (size_t)PREFIX_BYTES_HEX + (size_t)UINT32_T_BITS + (size_t)NULL_TERMINATOR_BYTE, 0, (uint8_t)UINT32_T_BITS);
	test_twiggle_bit((uint32_t)0, (int)0, (operation_t)0);
	test_grab_three_bits((uint32_t)0, (int)0);

	return EXIT_SUCCESS;
}