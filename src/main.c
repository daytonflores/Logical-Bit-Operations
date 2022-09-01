#include <stdio.h>
#include <stdlib.h>
#include "bitops.h"

#define EXIT_TEST_SUCCESS (1)

#define NULL_TERMINATOR_BYTE (1)
#define PREFIX_BYTES_BIN (2)
#define PREFIX_BYTES_HEX (2)
#define UINT32_T_BITS (32)


int main(void) {
	int return_code;
	char str[PREFIX_BYTES_BIN + UINT32_T_BITS + NULL_TERMINATOR_BYTE];
	
	return_code = test_uint_to_binstr(str, (size_t)PREFIX_BYTES_BIN + (size_t)UINT32_T_BITS + (size_t)NULL_TERMINATOR_BYTE, 0, (uint8_t)UINT32_T_BITS);
	if (return_code == EXIT_TEST_SUCCESS) {
		printf("\nAll test_uint_to_binstr tests were successful!\n\n");
	}
	else {
		printf("\ntest_uint_to_binstr test failed...\n");
	}

	return_code = test_int_to_binstr(str, (size_t)PREFIX_BYTES_BIN + (size_t)UINT32_T_BITS + (size_t)NULL_TERMINATOR_BYTE, 0, (uint8_t)UINT32_T_BITS);
	if (return_code == EXIT_TEST_SUCCESS) {
		printf("\nAll test_int_to_binstr tests were successful!\n\n");
	}
	else {
		printf("\ntest_int_to_binstr test failed...\n\n");
	}

	return_code = test_uint_to_hexstr(str, (size_t)PREFIX_BYTES_HEX + (size_t)UINT32_T_BITS + (size_t)NULL_TERMINATOR_BYTE, 0, (uint8_t)UINT32_T_BITS);
	if (return_code == EXIT_TEST_SUCCESS) {
		printf("\nAll test_uint_to_hexstr tests were successful!\n\n");
	}
	else {
		printf("\ntest_uint_to_hexstr test failed...\n\n");
	}

	return_code = test_twiggle_bit((uint32_t)0, (int)0, (operation_t)0);
	if (return_code == EXIT_TEST_SUCCESS) {
		printf("\nAll test_twiggle_bit tests were successful!\n\n");
	}
	else {
		printf("\ntest_twiggle_bit test failed...\n\n");
	}

	return_code = test_grab_three_bits((uint32_t)0, (int)0);
	if (return_code == EXIT_TEST_SUCCESS) {
		printf("\nAll test_grab_three_bits tests were successful!\n\n");
	}
	else {
		printf("\ntest_grab_three_bits test failed...\n\n");
	}

	//return_code = test_hexdump(str, (size_t)PREFIX_BYTES_HEX + (size_t)UINT32_T_BITS + (size_t)NULL_TERMINATOR_BYTE, (const void *)0, (size_t)0);
	//if (return_code == EXIT_TEST_SUCCESS) {
	//	printf("\nAll test_hexdump tests were successful!\n\n");
	//}
	//else {
	//	printf("\ntest_hexdump test failed...\n\n");
	//}

	return EXIT_SUCCESS;
}