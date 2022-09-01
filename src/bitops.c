#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "bitops.h"

#define EXIT_BIT_FAILURE (0xFFFFFFFF)
#define EXIT_FAILURE_N (-1)
#define EXIT_TEST_SUCCESS (1)
#define EXIT_TEST_FAILURE (0)

#define BITS_PER_NIBBLE (4)
#define NULL_TERMINATOR_BYTE (1)
#define PREFIX_BYTES_BIN (2)
#define PREFIX_BYTES_HEX (2)
#define UINT32_T_BITS (32)

#define TEST_1A_DEC (18u)
#define TEST_1A_BITS (8u)
#define TEST_1A_RETURN (10)
#define TEST_1B_DEC (65400u)
#define TEST_1B_BITS (16u)
#define TEST_1B_RETURN (18)
#define TEST_1C_DEC (310u)
#define TEST_1C_BITS (4u)
#define TEST_1C_RETURN (-1)

char TEST_1A_EXPECTED[PREFIX_BYTES_BIN + UINT32_T_BITS + NULL_TERMINATOR_BYTE] = "0b00010010";
char TEST_1B_EXPECTED[PREFIX_BYTES_BIN + UINT32_T_BITS + NULL_TERMINATOR_BYTE] = "0b1111111101111000";
char TEST_1C_EXPECTED[PREFIX_BYTES_BIN + UINT32_T_BITS + NULL_TERMINATOR_BYTE] = "";

#define TEST_2A_DEC (18)
#define TEST_2A_BITS (8u)
#define TEST_2A_RETURN (10)
#define TEST_2B_DEC (-1)
#define TEST_2B_BITS (4u)
#define TEST_2B_RETURN (6)
#define TEST_2C_DEC (-3)
#define TEST_2C_BITS (8u)
#define TEST_2C_RETURN (10)

char TEST_2A_EXPECTED[PREFIX_BYTES_BIN + UINT32_T_BITS + NULL_TERMINATOR_BYTE] = "0b00010010";
char TEST_2B_EXPECTED[PREFIX_BYTES_BIN + UINT32_T_BITS + NULL_TERMINATOR_BYTE] = "0b1111";
char TEST_2C_EXPECTED[PREFIX_BYTES_BIN + UINT32_T_BITS + NULL_TERMINATOR_BYTE] = "0b11111101";

#define TEST_3A_DEC (18u)
#define TEST_3A_BITS (8u)
#define TEST_3A_RETURN (4)
#define TEST_3B_DEC (18u)
#define TEST_3B_BITS (16u)
#define TEST_3B_RETURN (6)
#define TEST_3C_DEC (65400)
#define TEST_3C_BITS (16u)
#define TEST_3C_RETURN (6)

char TEST_3A_EXPECTED[PREFIX_BYTES_HEX + UINT32_T_BITS + NULL_TERMINATOR_BYTE] = "0x12";
char TEST_3B_EXPECTED[PREFIX_BYTES_HEX + UINT32_T_BITS + NULL_TERMINATOR_BYTE] = "0x0012";
char TEST_3C_EXPECTED[PREFIX_BYTES_HEX + UINT32_T_BITS + NULL_TERMINATOR_BYTE] = "0xFF78";

#define TEST_4A_DEC (0u)
#define TEST_4A_BIT (0)
#define TEST_4A_OP (SET)
#define TEST_4B_DEC (0u)
#define TEST_4B_BIT (3)
#define TEST_4B_OP (SET)
#define TEST_4C_DEC (29495u)
#define TEST_4C_BIT (5)
#define TEST_4C_OP (TOGGLE)

uint32_t TEST_4A_EXPECTED = 1u;
uint32_t TEST_4B_EXPECTED = 8u;
uint32_t TEST_4C_EXPECTED = 29463u;

#define TEST_5A_DEC (29495u)
#define TEST_5A_SBIT (6)
#define TEST_5B_DEC (29495u)
#define TEST_5B_SBIT (7)

uint32_t TEST_5A_EXPECTED = 4u;
uint32_t TEST_5B_EXPECTED = 6u;

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
	assert(str != NULL);
	assert(size > (size_t)nbits + PREFIX_BYTES_BIN);
	assert(nbits > 0);

	if (num > (0xFFFFFFFF >> (UINT32_T_BITS - nbits))) {
		str[0] = '\0';
		return EXIT_FAILURE_N;
	}

	int i;
	int current_byte = PREFIX_BYTES_BIN;

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
	assert(str != NULL);
	assert(size > (size_t)nbits + PREFIX_BYTES_BIN);
	assert(nbits > 0);

	int i;
	int current_byte = PREFIX_BYTES_BIN;

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
	assert(str != NULL);
	assert(size > (size_t)nbits + PREFIX_BYTES_HEX);
	assert((nbits == 4) || (nbits == 8) || (nbits == 16) || (nbits == 32));

	int i;
	int current_byte = PREFIX_BYTES_HEX;
	uint8_t current_nibble;

	str[0] = '0';
	str[1] = 'x';

	for (i = nbits; i > 0; i = i - 4) {
		current_nibble = 0;
		//printf("--- %u & %u, i = %u\n", num, (uint32_t)(1 << i) | (uint32_t)(1 << (i - 1)) | (uint32_t)(1 << (i - 2)) | (uint32_t)(1 << (i - 3)), i);
		current_nibble = (((num & (uint32_t)(1 << (i - 1))) | (num & (uint32_t)(1 << (i - 2))) | (num & (uint32_t)(1 << (i - 3))) | (num & (uint32_t)(1 << (i - 4)))) >> (i - BITS_PER_NIBBLE));

		switch (current_nibble) {
			case 0b1111:
				str[current_byte] = 'F';
				break;
			case 0b1110:
				str[current_byte] = 'E';
				break;
			case 0b1101:
				str[current_byte] = 'D';
				break;
			case 0b1100:
				str[current_byte] = 'C';
				break;
			case 0b1011:
				str[current_byte] = 'B';
				break;
			case 0b1010:
				str[current_byte] = 'A';
				break;
			case 0b1001:
				str[current_byte] = '9';
				break;
			case 0b1000:
				str[current_byte] = '8';
				break;
			case 0b0111:
				str[current_byte] = '7';
				break;
			case 0b0110:
				str[current_byte] = '6';
				break;
			case 0b0101:
				str[current_byte] = '5';
				break;
			case 0b0100:
				str[current_byte] = '4';
				break;
			case 0b0011:
				str[current_byte] = '3';
				break;
			case 0b0010:
				str[current_byte] = '2';
				break;
			case 0b0001:
				str[current_byte] = '1';
				break;
			case 0b0000:
				str[current_byte] = '0';
				break;
			default:
				return EXIT_TEST_FAILURE;
		}
		//printf(" - str[%d] = %c, current_nibble = %u\n", current_byte, str[current_byte], current_nibble);
		current_byte++;
	}

	///< Terminate str with NULL
	str[current_byte] = '\0';

	return current_byte;
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
	assert((UINT32_T_BITS > bit) && (bit >= 0));
	assert((operation == CLEAR) || (operation == SET) || (operation == TOGGLE));

	switch (operation) {
		case CLEAR:
			input &= (0xFFFFFFFF & (0 << bit));
			break;
		case SET:
			input |= (1 << bit);
			break;
		case TOGGLE:
			input ^= (1 << bit);
			break;
		default:
			return EXIT_BIT_FAILURE;
			break;
	}

	return input;
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
	assert((UINT32_T_BITS - 3 >= start_bit) && (start_bit >= 0));

	uint32_t output = 0;

	output = ((input & (1 << (start_bit))) | (input & (1 << (start_bit + 1))) | (input & (1 << (start_bit + 2)))) >> start_bit;

	return output;
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
	return NULL;
}

int test_uint_to_binstr(char* str, size_t size, uint32_t num, uint8_t nbits) {
	int i;
	int num_chars;
	int return_code = EXIT_TEST_SUCCESS;

	num_chars = uint_to_binstr(str, size, (uint32_t)TEST_1A_DEC, TEST_1A_BITS);

	if (num_chars != (int)TEST_1A_RETURN) {
		return_code = EXIT_TEST_FAILURE;
	}

	for (i = 0; i < num_chars; i++) {
		if (str[i] != TEST_1A_EXPECTED[i]) {
			printf("test_uint_to_binstr: TEST_A (FAILURE): num = %u, nbits = %u, EXPECT[%d] = %c, return value = %d\n", (uint32_t)TEST_1A_DEC, (uint8_t)TEST_1A_BITS, i, TEST_1A_EXPECTED[i], (int)TEST_1A_RETURN);
			printf("                                       num = %u, nbits = %u, RESULT[%d] = %c, return value = %d\n", (uint32_t)TEST_1A_DEC, (uint8_t)TEST_1A_BITS, i, str[i], num_chars);
			return_code = EXIT_TEST_FAILURE;
		}
	}

	printf("test_uint_to_binstr: TEST_A (EXPECT) : num = %u, nbits = %u, EXPECT = %s, return value = %d\n", (uint32_t)TEST_1A_DEC, (uint8_t)TEST_1A_BITS, TEST_1A_EXPECTED, (int)TEST_1A_RETURN);
	printf("test_uint_to_binstr: TEST_A (RESULT) : num = %u, nbits = %u, RESULT = %s, return value = %d\n", (uint32_t)TEST_1A_DEC, (uint8_t)TEST_1A_BITS, str,num_chars);

	num_chars = uint_to_binstr(str, size, (uint32_t)TEST_1B_DEC, TEST_1B_BITS);

	if (num_chars != (int)TEST_1B_RETURN) {
		return_code = EXIT_TEST_FAILURE;
	}

	for (i = 0; i < num_chars; i++) {
		if (str[i] != TEST_1B_EXPECTED[i]) {
			printf("test_uint_to_binstr: TEST_B (FAILURE): num = %u, nbits = %u, EXPECT[%d] = %c, return value = %d\n", (uint32_t)TEST_1B_DEC, (uint8_t)TEST_1B_BITS, i, TEST_1B_EXPECTED[i], (int)TEST_1B_RETURN);
			printf("                                       num = %u, nbits = %u, RESULT[%d] = %c, return value = %d\n", (uint32_t)TEST_1B_DEC, (uint8_t)TEST_1B_BITS, i, str[i], num_chars);
			return_code = EXIT_TEST_FAILURE;
		}
	}
	printf("test_uint_to_binstr: TEST_B (EXPECT) : num = %u, nbits = %u, EXPECT = %s, return value = %d\n", (uint32_t)TEST_1B_DEC, (uint8_t)TEST_1B_BITS, TEST_1B_EXPECTED, (int)TEST_1B_RETURN);
	printf("test_uint_to_binstr: TEST_B (RESULT) : num = %u, nbits = %u, RESULT = %s, return value = %d\n", (uint32_t)TEST_1B_DEC, (uint8_t)TEST_1B_BITS, str, num_chars);

	num_chars = uint_to_binstr(str, size, (uint32_t)TEST_1C_DEC, TEST_1C_BITS);

	if (num_chars != (int)TEST_1C_RETURN) {
		return_code = EXIT_TEST_FAILURE;
	}

	for (i = 0; i < num_chars; i++) {
		if (str[i] != TEST_1C_EXPECTED[i]) {
			printf("test_uint_to_binstr: TEST_C (FAILURE): num = %u, nbits = %u, EXPECT[%d] = %c, return value = %d\n", (uint32_t)TEST_1C_DEC, (uint8_t)TEST_1C_BITS, i, TEST_1C_EXPECTED[i], (int)TEST_1C_RETURN);
			printf("                                       num = %u, nbits = %u, RESULT[%d] = %c, return value = %d\n", (uint32_t)TEST_1C_DEC, (uint8_t)TEST_1C_BITS, i, str[i], num_chars);
			return_code = EXIT_TEST_FAILURE;
		}
	}
	printf("test_uint_to_binstr: TEST_C (EXPECT) : num = %u, nbits = %u, EXPECT = %s, return value = %d\n", (uint32_t)TEST_1C_DEC, (uint8_t)TEST_1C_BITS, TEST_1C_EXPECTED, (int)TEST_1C_RETURN);
	printf("test_uint_to_binstr: TEST_C (RESULT) : num = %u, nbits = %u, RESULT = %s, return value = %d\n", (uint32_t)TEST_1C_DEC, (uint8_t)TEST_1C_BITS, str, num_chars);

	return return_code;
}

int test_int_to_binstr(char* str, size_t size, int32_t num, uint8_t nbits) {
	int i;
	int num_chars;
	int return_code = EXIT_TEST_SUCCESS;

	num_chars = int_to_binstr(str, size, (uint32_t)TEST_2A_DEC, TEST_2A_BITS);

	if (num_chars != (int)TEST_2A_RETURN) {
		return_code = EXIT_TEST_FAILURE;
	}

	for (i = 0; i < num_chars; i++) {
		if (str[i] != TEST_2A_EXPECTED[i]) {
			printf("test_int_to_binstr: TEST_A (FAILURE): num = %d, nbits = %u, EXPECT[%d] = %c, return value = %d\n", (uint32_t)TEST_2A_DEC, (uint8_t)TEST_2A_BITS, i, TEST_2A_EXPECTED[i], (int)TEST_2A_RETURN);
			printf("                                      num = %d, nbits = %u, RESULT[%d] = %c, return value = %d\n", (uint32_t)TEST_2A_DEC, (uint8_t)TEST_2A_BITS, i, str[i], num_chars);
			return_code = EXIT_TEST_FAILURE;
		}
	}
	printf("test_int_to_binstr: TEST_A (EXPECT) : num = %d, nbits = %u, EXPECT = %s, return value = %d\n", (uint32_t)TEST_2A_DEC, (uint8_t)TEST_2A_BITS, TEST_2A_EXPECTED, (int)TEST_2A_RETURN);
	printf("test_int_to_binstr: TEST_A (RESULT) : num = %d, nbits = %u, RESULT = %s, return value = %d\n", (uint32_t)TEST_2A_DEC, (uint8_t)TEST_2A_BITS, str, num_chars);

	num_chars = int_to_binstr(str, size, (uint32_t)TEST_2B_DEC, TEST_2B_BITS);

	if (num_chars != (int)TEST_2B_RETURN) {
		return_code = EXIT_TEST_FAILURE;
	}

	for (i = 0; i < num_chars; i++) {
		if (str[i] != TEST_2B_EXPECTED[i]) {
			printf("test_int_to_binstr: TEST_B (FAILURE): num = %d, nbits = %u, EXPECT[%d] = %c, return value = %d\n", (uint32_t)TEST_2B_DEC, (uint8_t)TEST_2B_BITS, i, TEST_2B_EXPECTED[i], (int)TEST_2B_RETURN);
			printf("                                      num = %d, nbits = %u, RESULT[%d] = %c, return value = %d\n", (uint32_t)TEST_2B_DEC, (uint8_t)TEST_2B_BITS, i, str[i], num_chars);
			return_code = EXIT_TEST_FAILURE;
		}
	}
	printf("test_int_to_binstr: TEST_B (EXPECT) : num = %d, nbits = %u, EXPECT = %s, return value = %d\n", (uint32_t)TEST_2B_DEC, (uint8_t)TEST_2B_BITS, TEST_2B_EXPECTED, (int)TEST_2B_RETURN);
	printf("test_int_to_binstr: TEST_B (RESULT) : num = %d, nbits = %u, RESULT = %s, return value = %d\n", (uint32_t)TEST_2B_DEC, (uint8_t)TEST_2B_BITS, str, num_chars);

	num_chars = int_to_binstr(str, size, (uint32_t)TEST_2C_DEC, TEST_2C_BITS);

	if (num_chars != (int)TEST_2C_RETURN) {
		return_code = EXIT_TEST_FAILURE;
	}

	for (i = 0; i < num_chars; i++) {
		if (str[i] != TEST_2C_EXPECTED[i]) {
			printf("test_int_to_binstr: TEST_C (FAILURE): num = %d, nbits = %u, EXPECT[%d] = %c, return value = %d\n", (uint32_t)TEST_2C_DEC, (uint8_t)TEST_2C_BITS, i, TEST_2C_EXPECTED[i], (int)TEST_2C_RETURN);
			printf("                                      num = %d, nbits = %u, RESULT[%d] = %c, return value = %d\n", (uint32_t)TEST_2C_DEC, (uint8_t)TEST_2C_BITS, i, str[i], num_chars);
			return_code = EXIT_TEST_FAILURE;
		}
	}
	printf("test_int_to_binstr: TEST_C (EXPECT) : num = %d, nbits = %u, EXPECT = %s, return value = %d\n", (uint32_t)TEST_2C_DEC, (uint8_t)TEST_2C_BITS, TEST_2C_EXPECTED, (int)TEST_2C_RETURN);
	printf("test_int_to_binstr: TEST_C (RESULT) : num = %d, nbits = %u, RESULT = %s, return value = %d\n", (uint32_t)TEST_2C_DEC, (uint8_t)TEST_2C_BITS, str, num_chars);

	return return_code;
}

int test_uint_to_hexstr(char* str, size_t size, uint32_t num, uint8_t nbits) {
	int i;
	int num_chars;
	int return_code = EXIT_TEST_SUCCESS;

	num_chars = uint_to_hexstr(str, size, (uint32_t)TEST_3A_DEC, TEST_3A_BITS);

	if (num_chars != (int)TEST_3A_RETURN) {
		return_code = EXIT_TEST_FAILURE;
	}

	for (i = 0; i < num_chars; i++) {
		if (str[i] != TEST_3A_EXPECTED[i]) {
			printf("test_uint_to_hexstr: TEST_A (FAILURE): num = %u, nbits = %u, EXPECT[%d] = %c, return value = %d\n", (uint32_t)TEST_3A_DEC, (uint8_t)TEST_3A_BITS, i, TEST_3A_EXPECTED[i], (int)TEST_3A_RETURN);
			printf("                                       num = %u, nbits = %u, RESULT[%d] = %c, return value = %d\n", (uint32_t)TEST_3A_DEC, (uint8_t)TEST_3A_BITS, i, str[i], num_chars);
			return_code = EXIT_TEST_FAILURE;
		}
	}
	printf("test_uint_to_hexstr: TEST_A (EXPECT) : num = %u, nbits = %u, EXPECT = %s, return value = %d\n", (uint32_t)TEST_3A_DEC, (uint8_t)TEST_3A_BITS, TEST_3A_EXPECTED, (int)TEST_3A_RETURN);
	printf("test_uint_to_hexstr: TEST_A (RESULT) : num = %u, nbits = %u, RESULT = %s, return value = %d\n", (uint32_t)TEST_3A_DEC, (uint8_t)TEST_3A_BITS, str, num_chars);

	num_chars = uint_to_hexstr(str, size, (uint32_t)TEST_3B_DEC, TEST_3B_BITS);

	if (num_chars != (int)TEST_3B_RETURN) {
		return_code = EXIT_TEST_FAILURE;
	}

	for (i = 0; i < num_chars; i++) {
		if (str[i] != TEST_3B_EXPECTED[i]) {
			printf("test_uint_to_hexstr: TEST_B (FAILURE): num = %u, nbits = %u, EXPECT[%d] = %c, return value = %d\n", (uint32_t)TEST_3B_DEC, (uint8_t)TEST_3B_BITS, i, TEST_3B_EXPECTED[i], (int)TEST_3B_RETURN);
			printf("                                       num = %u, nbits = %u, RESULT[%d] = %c, return value = %d\n", (uint32_t)TEST_3B_DEC, (uint8_t)TEST_3B_BITS, i, str[i], num_chars);
			return_code = EXIT_TEST_FAILURE;
		}
	}
	printf("test_uint_to_hexstr: TEST_B (EXPECT) : num = %u, nbits = %u, EXPECT = %s, return value = %d\n", (uint32_t)TEST_3B_DEC, (uint8_t)TEST_3B_BITS, TEST_3B_EXPECTED, (int)TEST_3B_RETURN);
	printf("test_uint_to_hexstr: TEST_B (RESULT) : num = %u, nbits = %u, RESULT = %s, return value = %d\n", (uint32_t)TEST_3B_DEC, (uint8_t)TEST_3B_BITS, str, num_chars);

	num_chars = uint_to_hexstr(str, size, (uint32_t)TEST_3C_DEC, TEST_3C_BITS);

	if (num_chars != (int)TEST_3C_RETURN) {
		return_code = EXIT_TEST_FAILURE;
	}

	for (i = 0; i < num_chars; i++) {
		if (str[i] != TEST_3C_EXPECTED[i]) {
			printf("test_uint_to_hexstr: TEST_C (FAILURE): num = %u, nbits = %u, EXPECT[%d] = %c, return value = %d\n", (uint32_t)TEST_3C_DEC, (uint8_t)TEST_3C_BITS, i, TEST_3C_EXPECTED[i], (int)TEST_3C_RETURN);
			printf("                                       num = %u, nbits = %u, RESULT[%d] = %c, return value = %d\n", (uint32_t)TEST_3C_DEC, (uint8_t)TEST_3C_BITS, i, str[i], num_chars);
			return_code = EXIT_TEST_FAILURE;
		}
	}
	printf("test_uint_to_hexstr: TEST_C (EXPECT) : num = %u, nbits = %u, EXPECT = %s, return value = %d\n", (uint32_t)TEST_3C_DEC, (uint8_t)TEST_3C_BITS, TEST_3C_EXPECTED, (int)TEST_3C_RETURN);
	printf("test_uint_to_hexstr: TEST_C (RESULT) : num = %u, nbits = %u, RESULT = %s, return value = %d\n", (uint32_t)TEST_3C_DEC, (uint8_t)TEST_3C_BITS, str, num_chars);

	return return_code;
}

int test_twiggle_bit(uint32_t input, int bit, operation_t operation) {
	uint32_t output;
	int return_code = EXIT_TEST_SUCCESS;

	output = twiggle_bit((uint32_t)TEST_4A_DEC, (int)TEST_4A_BIT, (operation_t)TEST_4A_OP);

	if (output != TEST_4A_EXPECTED) {
		return_code = EXIT_TEST_FAILURE;
	}

	printf("test_twiggle_bit: TEST_A (EXPECT) : input = %u, bit = %d, operation = %s EXPECT = %u\n", (uint32_t)TEST_4A_DEC, (int)TEST_4A_BIT, ((TEST_4A_OP == CLEAR) ? "CLEAR" : ((TEST_4A_OP == SET) ? "SET" : ((TEST_4A_OP == TOGGLE) ? "TOGGLE" : "UNKNOWN"))), TEST_4A_EXPECTED);
	printf("test_twiggle_bit: TEST_A (RESULT) : input = %u, bit = %d, operation = %s RESULT = %u\n", (uint32_t)TEST_4A_DEC, (int)TEST_4A_BIT, ((TEST_4A_OP == CLEAR) ? "CLEAR" : ((TEST_4A_OP == SET) ? "SET" : ((TEST_4A_OP == TOGGLE) ? "TOGGLE" : "UNKNOWN"))), output);

	output = twiggle_bit((uint32_t)TEST_4B_DEC, (int)TEST_4B_BIT, (operation_t)TEST_4B_OP);

	if (output != TEST_4B_EXPECTED) {
		return_code = EXIT_TEST_FAILURE;
	}

	printf("test_twiggle_bit: TEST_B (EXPECT) : input = %u, bit = %d, operation = %s EXPECT = %u\n", (uint32_t)TEST_4B_DEC, (int)TEST_4B_BIT, ((TEST_4B_OP == CLEAR) ? "CLEAR" : ((TEST_4B_OP == SET) ? "SET" : ((TEST_4B_OP == TOGGLE) ? "TOGGLE" : "UNKNOWN"))), TEST_4B_EXPECTED);
	printf("test_twiggle_bit: TEST_B (RESULT) : input = %u, bit = %d, operation = %s RESULT = %u\n", (uint32_t)TEST_4B_DEC, (int)TEST_4B_BIT, ((TEST_4B_OP == CLEAR) ? "CLEAR" : ((TEST_4B_OP == SET) ? "SET" : ((TEST_4B_OP == TOGGLE) ? "TOGGLE" : "UNKNOWN"))), output);

	output = twiggle_bit((uint32_t)TEST_4C_DEC, (int)TEST_4C_BIT, (operation_t)TEST_4C_OP);

	if (output != TEST_4C_EXPECTED) {
		return_code = EXIT_TEST_FAILURE;
	}

	printf("test_twiggle_bit: TEST_C (EXPECT) : input = %u, bit = %d, operation = %s EXPECT = %u\n", (uint32_t)TEST_4C_DEC, (int)TEST_4C_BIT, ((TEST_4C_OP == CLEAR) ? "CLEAR" : ((TEST_4C_OP == SET) ? "SET" : ((TEST_4C_OP == TOGGLE) ? "TOGGLE" : "UNKNOWN"))), TEST_4C_EXPECTED);
	printf("test_twiggle_bit: TEST_C (RESULT) : input = %u, bit = %d, operation = %s RESULT = %u\n", (uint32_t)TEST_4C_DEC, (int)TEST_4C_BIT, ((TEST_4C_OP == CLEAR) ? "CLEAR" : ((TEST_4C_OP == SET) ? "SET" : ((TEST_4C_OP == TOGGLE) ? "TOGGLE" : "UNKNOWN"))), output);

	return return_code;
}

int test_grab_three_bits(uint32_t input, int start_bit) {
	uint32_t output;
	int return_code = EXIT_TEST_SUCCESS;

	output = grab_three_bits((uint32_t)TEST_5A_DEC, (int)TEST_5A_SBIT);

	if (output != TEST_5A_EXPECTED) {
		return_code = EXIT_TEST_FAILURE;
	}

	printf("test_grab_three_bits: TEST_A (EXPECT) : input = %u, start_bit = %d, EXPECT = %u\n", (uint32_t)TEST_5A_DEC, (int)TEST_5A_SBIT, TEST_5A_EXPECTED);
	printf("test_grab_three_bits: TEST_A (RESULT) : input = %u, start_bit = %d, RESULT = %u\n", (uint32_t)TEST_5A_DEC, (int)TEST_5A_SBIT, output);

	output = grab_three_bits((uint32_t)TEST_5B_DEC, (int)TEST_5B_SBIT);

	if (output != TEST_5B_EXPECTED) {
		return_code = EXIT_TEST_FAILURE;
	}

	printf("test_grab_three_bits: TEST_B (EXPECT) : input = %u, start_bit = %d, EXPECT = %u\n", (uint32_t)TEST_5B_DEC, (int)TEST_5B_SBIT, TEST_5B_EXPECTED);
	printf("test_grab_three_bits: TEST_B (RESULT) : input = %u, start_bit = %d, RESULT = %u\n", (uint32_t)TEST_5B_DEC, (int)TEST_5B_SBIT, output);

	return return_code;
}

int test_hexdump(char* str, size_t size, const void* loc, size_t nbytes) {
	int return_code = EXIT_TEST_SUCCESS;

	return_code = EXIT_TEST_FAILURE;

	return return_code;
}