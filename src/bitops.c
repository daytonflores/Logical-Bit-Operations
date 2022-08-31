#include <assert.h>
#include <stdlib.h>
#include "bitops.h"

#define BINARY_PREFIX_BYTES (2)
#define EXIT_FAILURE_N (-1)
#define EXIT_TEST_SUCCESS (1)
#define EXIT_TEST_FAILURE (0)
#define NULL_TERMINATOR_BYTE (1)

#define TEST_A_UNUM_DEC (0u)
#define TEST_A_UNUM_BITS (1u)
#define TEST_B_UNUM_DEC (1431655765u)
#define TEST_B_UNUM_BITS (5u)
#define TEST_C_UNUM_DEC (4294967295u)
#define TEST_C_UNUM_BITS (32u)

#define TEST_A_NUM_DEC (0)
#define TEST_A_NUM_BITS (1u)
#define TEST_B_NUM_DEC (1431655765)
#define TEST_B_NUM_BITS (5u)
#define TEST_C_NUM_DEC (-1)
#define TEST_C_NUM_BITS (32u)


#define UINT32_T_BITS (32)

char TEST_A_UNUM_BIN[BINARY_PREFIX_BYTES + UINT32_T_BITS + NULL_TERMINATOR_BYTE] = "0b0";
char TEST_B_UNUM_BIN[BINARY_PREFIX_BYTES + UINT32_T_BITS + NULL_TERMINATOR_BYTE] = "0b10101";
char TEST_C_UNUM_BIN[BINARY_PREFIX_BYTES + UINT32_T_BITS + NULL_TERMINATOR_BYTE] = "0b11111111111111111111111111111111";
char TEST_A_NUM_BIN[BINARY_PREFIX_BYTES + UINT32_T_BITS + NULL_TERMINATOR_BYTE] = "0b0";
char TEST_B_NUM_BIN[BINARY_PREFIX_BYTES + UINT32_T_BITS + NULL_TERMINATOR_BYTE] = "0b10101";
char TEST_C_NUM_BIN[BINARY_PREFIX_BYTES + UINT32_T_BITS + NULL_TERMINATOR_BYTE] = "0b11111111111111111111111111111111";

uint32_t BIT_0_HIGH = 0x00000001;
uint32_t BIT_0_LOW = 0x00000000;
uint32_t BIT_31_HIGH = 0x80000000;
uint32_t BIT_31_LOW = 0x00000000;

/**
 * \fn uint_to_binstr(char* str, size_t size, uint32_t num, uint8_t nbits)
 * \brief Stores binary representation of a 32-bit unsigned int into a null-terminated string
 * 
 * \param str Pointer to a char array
 * \param size Num of bytes of the char array pointed to by str
 * \param num The value to be converted
 * \param nbits The number of bits in the input
 * 
 * \return If successful, returns the number of characters written to str, not including the terminal \0. In the case of an error, the function returns a negative value, and str is set to the empty string.
 */
int uint_to_binstr(char* str, size_t size, uint32_t num, uint8_t nbits) {
	assert(size > (size_t)nbits);
	assert(nbits > 0);

	int i;
	int num_chars = 0;
	int current_byte = BINARY_PREFIX_BYTES;

	str[0] = '0';
	str[1] = 'b';

	for (i = nbits - 1; i >= 0; i--) {
		if (num & (uint32_t)(1 << i)) {
			str[current_byte] = '1';
		}
		else {
			str[current_byte] = '0';
		}

		current_byte++;
	}

	///< Terminate str with NULL
	str[current_byte] = '\0';

	return current_byte;
}

/**
 * \fn int_to_binstr(char* str, size_t size, uint32_t num, uint8_t nbits)
 * \brief Stores binary representation of a 32-bit signed int into a null-terminated string
 *
 * \param str Pointer to a char array
 * \param size Num of bytes of the char array pointed to by str
 * \param num The value to be converted
 * \param nbits The number of bits in the input
 *
 * \return If successful, returns the number of characters written to str, not including the terminal \0. In the case of an error, the function returns a negative value, and str is set to the empty string.
 */
int int_to_binstr(char* str, size_t size, int32_t num, uint8_t nbits) {
	assert(size > (size_t)nbits);
	assert(nbits > 0);

	int i;
	int num_chars = 0;
	int current_byte = BINARY_PREFIX_BYTES;

	str[0] = '0';
	str[1] = 'b';

	for (i = nbits - 1; i >= 0; i--) {
		if (num & (uint32_t)(1 << i)) {
			str[current_byte] = '1';
		}
		else {
			str[current_byte] = '0';
		}

		current_byte++;
	}

	///< Terminate str with NULL
	str[current_byte] = '\0';

	return current_byte;
}

/**
 * \fn uint_to_hexstr(char* str, size_t size, uint32_t num, uint8_t nbits)
 * \brief Stores hex representation of a 32-bit unsigned int into a null-terminated string
 *
 * \param str Pointer to a char array
 * \param size Num of bytes of the char array pointed to by str
 * \param num The value to be converted
 * \param nbits The number of bits in the input (note: nbits must be one of the values 4, 8, 16, or 32 to correspond to 1, 2, 4, or 8 hex digits)
 *
 * \return If successful, returns the number of characters written to str, not including the terminal \0. In the case of an error, the function returns a negative value, and str is set to the empty string.
 */
int uint_to_hexstr(char* str, size_t size, uint32_t num, uint8_t nbits) {

}

/**
 * \fn twiggle_bit(uint32_t input, int bit, operation_t operation)
 * \brief Changes exactly a single bit of a 32-bit unsigned int
 *
 * \param input The 32-bit value to operate on
 * \param bit The single bit in input to operate on (range from 0 to 31)
 * \param operation The type of operation to perform on bit (CLEAR, SET, TOGGLE)
 *
 * \return If successful, returns the transformed 32-bit value. In the case of an error, the function returns 0xFFFFFFFF.
 */
uint32_t twiggle_bit(uint32_t input, int bit, operation_t operation) {

}

/**
 * \fn grab_three_bits(uint32_t input, int start_bit)
 * \brief Returns 3 consecutive bits of a 32-bit unsigned int as a 32-bit unsigned int
 *
 * \param input The 32-bit value to operate on
 * \param start_bit The least-significant bit number of input to begin grabbing three bits from (range from 0 to 31)
 *
 * \return If successful, returns a 32-bit value whose 3 least significant bits are the 3 bits grabbed from input, in respective order. In the case of an error, the function returns 0xFFFFFFFF.
 */
uint32_t grab_three_bits(uint32_t input, int start_bit) {

}

/**
 * \fn hexdump(char* str, size_t size, const void* loc, size_t nbytes)
 * \brief Returns a string representing a dump of nbytes of memory starting at loc. Bytes are printed up to 16 bytes per line, separate by newlines. Each row will begin with the offset in bytes from loc, in hex.
 *
 * \param str Pointer to a char array
 * \param size Num of bytes of the char array pointed to by str
 * \param loc Starting location of memory to begin dumping bytes from
 * \param nbytes The number of bytes to read from loc
 *
 * \return If successful, returns the char* str which facilitates daisy-chaining this function into other string manipulation functions (such as puts). In the case of an error (i.e. str is not large enough to hold the requested hex dump), str will be set to empty.
 */
char* hexdump(char* str, size_t size, const void* loc, size_t nbytes) {

}

int test_uint_to_binstr(char* str, size_t size, uint32_t num, uint8_t nbits) {
	int i;
	int num_chars;

	num_chars = uint_to_binstr(str, size, (uint32_t)TEST_A_UNUM_DEC, TEST_A_UNUM_BITS);

	if (num_chars < 0) {
		printf("test_uint_to_binstr: TEST_A (FAILURE): Return code %d from uint_to_binstr", num_chars);
		return EXIT_TEST_FAILURE;
	}

	for (i = 0; i < num_chars; i++) {
		if (str[i] != TEST_A_UNUM_BIN[i]) {
			printf("test_uint_to_binstr: TEST_A (FAILURE): num = %u, nbits = %u, EXPECT[%d] = %c, return value = %d\n", (uint32_t)TEST_A_UNUM_DEC, (uint8_t)TEST_A_UNUM_BITS, i, TEST_A_UNUM_BIN[i], (uint8_t)TEST_A_UNUM_BITS + (uint8_t)BINARY_PREFIX_BYTES);
			printf("                                       num = %u, nbits = %u, RESULT[%d] = %c, return value = %d\n", (uint32_t)TEST_A_UNUM_DEC, (uint8_t)TEST_A_UNUM_BITS, i, str[i], num_chars);
			return EXIT_TEST_FAILURE;
		}
	}
	printf("test_uint_to_binstr: TEST_A (SUCCESS): num = %u, nbits = %u, EXPECT = %s, return value = %d\n", (uint32_t)TEST_A_UNUM_DEC, (uint8_t)TEST_A_UNUM_BITS, TEST_A_UNUM_BIN, (uint8_t)TEST_A_UNUM_BITS + (uint8_t)BINARY_PREFIX_BYTES);
	printf("                                       num = %u, nbits = %u, RESULT = %s, return value = %d\n", (uint32_t)TEST_A_UNUM_DEC, (uint8_t)TEST_A_UNUM_BITS, str,num_chars);

	num_chars = uint_to_binstr(str, size, (uint32_t)TEST_B_UNUM_DEC, TEST_B_UNUM_BITS);

	if (num_chars < 0) {
		printf("test_uint_to_binstr: TEST_B (FAILURE): Return code %d from uint_to_binstr", num_chars);
		return EXIT_TEST_FAILURE;
	}

	for (i = 0; i < num_chars; i++) {
		if (str[i] != TEST_B_UNUM_BIN[i]) {
			printf("test_uint_to_binstr: TEST_B (FAILURE): num = %u, nbits = %u, EXPECT[%d] = %c, return value = %d\n", (uint32_t)TEST_B_UNUM_DEC, (uint8_t)TEST_B_UNUM_BITS, i, TEST_B_UNUM_BIN[i], (uint8_t)TEST_B_UNUM_BITS + (uint8_t)BINARY_PREFIX_BYTES);
			printf("                                       num = %u, nbits = %u, RESULT[%d] = %c, return value = %d\n", (uint32_t)TEST_B_UNUM_DEC, (uint8_t)TEST_B_UNUM_BITS, i, str[i], num_chars);
			return EXIT_TEST_FAILURE;
		}
	}
	printf("test_uint_to_binstr: TEST_B (SUCCESS): num = %u, nbits = %u, EXPECT = %s, return value = %d\n", (uint32_t)TEST_B_UNUM_DEC, (uint8_t)TEST_B_UNUM_BITS, TEST_B_UNUM_BIN, (uint8_t)TEST_B_UNUM_BITS + (uint8_t)BINARY_PREFIX_BYTES);
	printf("                                       num = %u, nbits = %u, RESULT = %s, return value = %d\n", (uint32_t)TEST_B_UNUM_DEC, (uint8_t)TEST_B_UNUM_BITS, str, num_chars);

	num_chars = uint_to_binstr(str, size, (uint32_t)TEST_C_UNUM_DEC, TEST_C_UNUM_BITS);

	if (num_chars < 0) {
		printf("test_uint_to_binstr: TEST_C (FAILURE): Return code %d from uint_to_binstr", num_chars);
		return EXIT_TEST_FAILURE;
	}

	for (i = 0; i < num_chars; i++) {
		if (str[i] != TEST_C_UNUM_BIN[i]) {
			printf("test_uint_to_binstr: TEST_C (FAILURE): num = %u, nbits = %u, EXPECT[%d] = %c, return value = %d\n", (uint32_t)TEST_C_UNUM_DEC, (uint8_t)TEST_C_UNUM_BITS, i, TEST_C_UNUM_BIN[i], (uint8_t)TEST_C_UNUM_BITS + (uint8_t)BINARY_PREFIX_BYTES);
			printf("                                       num = %u, nbits = %u, RESULT[%d] = %c, return value = %d\n", (uint32_t)TEST_C_UNUM_DEC, (uint8_t)TEST_C_UNUM_BITS, i, str[i], num_chars);
			return EXIT_TEST_FAILURE;
		}
	}
	printf("test_uint_to_binstr: TEST_C (SUCCESS): num = %u, nbits = %u, EXPECT = %s, return value = %d\n", (uint32_t)TEST_C_UNUM_DEC, (uint8_t)TEST_C_UNUM_BITS, TEST_C_UNUM_BIN, (uint8_t)TEST_C_UNUM_BITS + (uint8_t)BINARY_PREFIX_BYTES);
	printf("                                       num = %u, nbits = %u, RESULT = %s, return value = %d\n", (uint32_t)TEST_C_UNUM_DEC, (uint8_t)TEST_C_UNUM_BITS, str, num_chars);

	return EXIT_TEST_SUCCESS;
}

int test_int_to_binstr(char* str, size_t size, int32_t num, uint8_t nbits) {
	int i;
	int num_chars;

	num_chars = int_to_binstr(str, size, (uint32_t)TEST_A_NUM_DEC, TEST_A_NUM_BITS);

	if (num_chars < 0) {
		printf("test_int_to_binstr: TEST_A (FAILURE): Return code %d from int_to_binstr", num_chars);
		return EXIT_TEST_FAILURE;
	}

	for (i = 0; i < num_chars; i++) {
		if (str[i] != TEST_A_NUM_BIN[i]) {
			printf("test_int_to_binstr: TEST_A (FAILURE): num = %d, nbits = %u, EXPECT[%d] = %c, return value = %d\n", (uint32_t)TEST_A_NUM_DEC, (uint8_t)TEST_A_NUM_BITS, i, TEST_A_NUM_BIN[i], (uint8_t)TEST_A_NUM_BITS + (uint8_t)BINARY_PREFIX_BYTES);
			printf("                                      num = %d, nbits = %u, RESULT[%d] = %c, return value = %d\n", (uint32_t)TEST_A_NUM_DEC, (uint8_t)TEST_A_NUM_BITS, i, str[i], num_chars);
			return EXIT_TEST_FAILURE;
		}
	}
	printf("test_int_to_binstr: TEST_A (SUCCESS): num = %d, nbits = %u, EXPECT = %s, return value = %d\n", (uint32_t)TEST_A_NUM_DEC, (uint8_t)TEST_A_NUM_BITS, TEST_A_NUM_BIN, (uint8_t)TEST_A_NUM_BITS + (uint8_t)BINARY_PREFIX_BYTES);
	printf("                                      num = %d, nbits = %u, RESULT = %s, return value = %d\n", (uint32_t)TEST_A_NUM_DEC, (uint8_t)TEST_A_NUM_BITS, str, num_chars);

	num_chars = int_to_binstr(str, size, (uint32_t)TEST_B_NUM_DEC, TEST_B_NUM_BITS);

	if (num_chars < 0) {
		printf("test_int_to_binstr: TEST_B (FAILURE): Return code %d from int_to_binstr", num_chars);
		return EXIT_TEST_FAILURE;
	}

	for (i = 0; i < num_chars; i++) {
		if (str[i] != TEST_B_NUM_BIN[i]) {
			printf("test_int_to_binstr: TEST_B (FAILURE): num = %d, nbits = %u, EXPECT[%d] = %c, return value = %d\n", (uint32_t)TEST_B_NUM_DEC, (uint8_t)TEST_B_NUM_BITS, i, TEST_B_NUM_BIN[i], (uint8_t)TEST_B_NUM_BITS + (uint8_t)BINARY_PREFIX_BYTES);
			printf("                                      num = %d, nbits = %u, RESULT[%d] = %c, return value = %d\n", (uint32_t)TEST_B_NUM_DEC, (uint8_t)TEST_B_NUM_BITS, i, str[i], num_chars);
			return EXIT_TEST_FAILURE;
		}
	}
	printf("test_int_to_binstr: TEST_B (SUCCESS): num = %d, nbits = %u, EXPECT = %s, return value = %d\n", (uint32_t)TEST_B_NUM_DEC, (uint8_t)TEST_B_NUM_BITS, TEST_B_NUM_BIN, (uint8_t)TEST_B_NUM_BITS + (uint8_t)BINARY_PREFIX_BYTES);
	printf("                                      num = %d, nbits = %u, RESULT = %s, return value = %d\n", (uint32_t)TEST_B_NUM_DEC, (uint8_t)TEST_B_NUM_BITS, str, num_chars);

	num_chars = int_to_binstr(str, size, (uint32_t)TEST_C_NUM_DEC, TEST_C_NUM_BITS);

	if (num_chars < 0) {
		printf("test_int_to_binstr: TEST_C (FAILURE): Return code %d from int_to_binstr", num_chars);
		return EXIT_TEST_FAILURE;
	}

	for (i = 0; i < num_chars; i++) {
		if (str[i] != TEST_C_NUM_BIN[i]) {
			printf("test_int_to_binstr: TEST_C (FAILURE): num = %d, nbits = %u, EXPECT[%d] = %c, return value = %d\n", (uint32_t)TEST_C_NUM_DEC, (uint8_t)TEST_C_NUM_BITS, i, TEST_C_NUM_BIN[i], (uint8_t)TEST_C_NUM_BITS + (uint8_t)BINARY_PREFIX_BYTES);
			printf("                                      num = %d, nbits = %u, RESULT[%d] = %c, return value = %d\n", (uint32_t)TEST_C_NUM_DEC, (uint8_t)TEST_C_NUM_BITS, i, str[i], num_chars);
			return EXIT_TEST_FAILURE;
		}
	}
	printf("test_int_to_binstr: TEST_C (SUCCESS): num = %d, nbits = %u, EXPECT = %s, return value = %d\n", (uint32_t)TEST_C_NUM_DEC, (uint8_t)TEST_C_NUM_BITS, TEST_C_NUM_BIN, (uint8_t)TEST_C_NUM_BITS + (uint8_t)BINARY_PREFIX_BYTES);
	printf("                                      num = %d, nbits = %u, RESULT = %s, return value = %d\n", (uint32_t)TEST_C_NUM_DEC, (uint8_t)TEST_C_NUM_BITS, str, num_chars);

	return EXIT_TEST_SUCCESS;
}

int test_uint_to_hexstr(char* str, size_t size, uint32_t num, uint8_t nbits) {

}

uint32_t test_twiggle_bit(uint32_t input, int bit, operation_t operation) {

}

uint32_t test_grab_three_bits(uint32_t input, int start_bit) {

}

char* test_hexdump(char* str, size_t size, const void* loc, size_t nbytes) {

}