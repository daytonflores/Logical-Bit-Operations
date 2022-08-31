#include <assert.h>
#include <stdlib.h>
#include "bitops.h"

#define BITS_PER_NIBBLE (4)
#define PREFIX_BYTES_BIN (2)
#define PREFIX_BYTES_HEX (2)
#define EXIT_FAILURE_N (-1)
#define EXIT_TEST_SUCCESS (1)
#define EXIT_TEST_FAILURE (0)
#define NULL_TERMINATOR_BYTE (1)

#define TEST_1A_DEC (18u)
#define TEST_1A_BITS (8u)
#define TEST_1B_DEC (65400u)
#define TEST_1B_BITS (16u)
#define TEST_1C_DEC (310u)
#define TEST_1C_BITS (4u)

#define TEST_2A_DEC (18)
#define TEST_2A_BITS (8u)
#define TEST_2B_DEC (-1)
#define TEST_2B_BITS (4u)
#define TEST_2C_DEC (-3)
#define TEST_2C_BITS (8u)

#define TEST_3A_DEC (18u)
#define TEST_3A_BITS (8u)
#define TEST_3B_DEC (18u)
#define TEST_3B_BITS (16u)
#define TEST_3C_DEC (65400)
#define TEST_3C_BITS (16u)

#define UINT32_T_BITS (32)

char TEST_1A_EXPECTED[PREFIX_BYTES_BIN + UINT32_T_BITS + NULL_TERMINATOR_BYTE] = "0b00010010";
char TEST_1B_EXPECTED[PREFIX_BYTES_BIN + UINT32_T_BITS + NULL_TERMINATOR_BYTE] = "0b1111111101111000";
char TEST_1C_EXPECTED[PREFIX_BYTES_BIN + UINT32_T_BITS + NULL_TERMINATOR_BYTE] = "";

char TEST_2A_EXPECTED[PREFIX_BYTES_BIN + UINT32_T_BITS + NULL_TERMINATOR_BYTE] = "0b00010010";
char TEST_2B_EXPECTED[PREFIX_BYTES_BIN + UINT32_T_BITS + NULL_TERMINATOR_BYTE] = "0b1111";
char TEST_2C_EXPECTED[PREFIX_BYTES_BIN + UINT32_T_BITS + NULL_TERMINATOR_BYTE] = "0b11111101";

char TEST_3A_EXPECTED[PREFIX_BYTES_HEX + UINT32_T_BITS + NULL_TERMINATOR_BYTE] = "0x12";
char TEST_3B_EXPECTED[PREFIX_BYTES_HEX + UINT32_T_BITS + NULL_TERMINATOR_BYTE] = "0x0012";
char TEST_3C_EXPECTED[PREFIX_BYTES_HEX + UINT32_T_BITS + NULL_TERMINATOR_BYTE] = "0xFF78";

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

	num_chars = uint_to_binstr(str, size, (uint32_t)TEST_1A_DEC, TEST_1A_BITS);

	if (num_chars < 0) {
		printf("test_uint_to_binstr: TEST_A (FAILURE): Return code %d from uint_to_binstr", num_chars);
		return EXIT_TEST_FAILURE;
	}

	for (i = 0; i < num_chars; i++) {
		if (str[i] != TEST_1A_EXPECTED[i]) {
			printf("test_uint_to_binstr: TEST_A (FAILURE): num = %u, nbits = %u, EXPECT[%d] = %c, return value = %d\n", (uint32_t)TEST_1A_DEC, (uint8_t)TEST_1A_BITS, i, TEST_1A_EXPECTED[i], (uint8_t)TEST_1A_BITS + (uint8_t)PREFIX_BYTES_BIN);
			printf("                                       num = %u, nbits = %u, RESULT[%d] = %c, return value = %d\n", (uint32_t)TEST_1A_DEC, (uint8_t)TEST_1A_BITS, i, str[i], num_chars);
			//return EXIT_TEST_FAILURE;
		}
	}
	printf("test_uint_to_binstr: TEST_A (SUCCESS): num = %u, nbits = %u, EXPECT = %s, return value = %d\n", (uint32_t)TEST_1A_DEC, (uint8_t)TEST_1A_BITS, TEST_1A_EXPECTED, (uint8_t)TEST_1A_BITS + (uint8_t)PREFIX_BYTES_BIN);
	printf("                                       num = %u, nbits = %u, RESULT = %s, return value = %d\n", (uint32_t)TEST_1A_DEC, (uint8_t)TEST_1A_BITS, str,num_chars);

	num_chars = uint_to_binstr(str, size, (uint32_t)TEST_1B_DEC, TEST_1B_BITS);

	if (num_chars < 0) {
		printf("test_uint_to_binstr: TEST_B (FAILURE): Return code %d from uint_to_binstr", num_chars);
		return EXIT_TEST_FAILURE;
	}

	for (i = 0; i < num_chars; i++) {
		if (str[i] != TEST_1B_EXPECTED[i]) {
			printf("test_uint_to_binstr: TEST_B (FAILURE): num = %u, nbits = %u, EXPECT[%d] = %c, return value = %d\n", (uint32_t)TEST_1B_DEC, (uint8_t)TEST_1B_BITS, i, TEST_1B_EXPECTED[i], (uint8_t)TEST_1B_BITS + (uint8_t)PREFIX_BYTES_BIN);
			printf("                                       num = %u, nbits = %u, RESULT[%d] = %c, return value = %d\n", (uint32_t)TEST_1B_DEC, (uint8_t)TEST_1B_BITS, i, str[i], num_chars);
			return EXIT_TEST_FAILURE;
		}
	}
	printf("test_uint_to_binstr: TEST_B (SUCCESS): num = %u, nbits = %u, EXPECT = %s, return value = %d\n", (uint32_t)TEST_1B_DEC, (uint8_t)TEST_1B_BITS, TEST_1B_EXPECTED, (uint8_t)TEST_1B_BITS + (uint8_t)PREFIX_BYTES_BIN);
	printf("                                       num = %u, nbits = %u, RESULT = %s, return value = %d\n", (uint32_t)TEST_1B_DEC, (uint8_t)TEST_1B_BITS, str, num_chars);

	num_chars = uint_to_binstr(str, size, (uint32_t)TEST_1C_DEC, TEST_1C_BITS);

	if (num_chars < 0) {
		printf("test_uint_to_binstr: TEST_C (FAILURE): Return code %d from uint_to_binstr", num_chars);
		return EXIT_TEST_FAILURE;
	}

	for (i = 0; i < num_chars; i++) {
		if (str[i] != TEST_1C_EXPECTED[i]) {
			printf("test_uint_to_binstr: TEST_C (FAILURE): num = %u, nbits = %u, EXPECT[%d] = %c, return value = %d\n", (uint32_t)TEST_1C_DEC, (uint8_t)TEST_1C_BITS, i, TEST_1C_EXPECTED[i], (uint8_t)TEST_1C_BITS + (uint8_t)PREFIX_BYTES_BIN);
			printf("                                       num = %u, nbits = %u, RESULT[%d] = %c, return value = %d\n", (uint32_t)TEST_1C_DEC, (uint8_t)TEST_1C_BITS, i, str[i], num_chars);
			return EXIT_TEST_FAILURE;
		}
	}
	printf("test_uint_to_binstr: TEST_C (SUCCESS): num = %u, nbits = %u, EXPECT = %s, return value = %d\n", (uint32_t)TEST_1C_DEC, (uint8_t)TEST_1C_BITS, TEST_1C_EXPECTED, (uint8_t)TEST_1C_BITS + (uint8_t)PREFIX_BYTES_BIN);
	printf("                                       num = %u, nbits = %u, RESULT = %s, return value = %d\n", (uint32_t)TEST_1C_DEC, (uint8_t)TEST_1C_BITS, str, num_chars);

	return EXIT_TEST_SUCCESS;
}

int test_int_to_binstr(char* str, size_t size, int32_t num, uint8_t nbits) {
	int i;
	int num_chars;

	num_chars = int_to_binstr(str, size, (uint32_t)TEST_2A_DEC, TEST_2A_BITS);

	if (num_chars < 0) {
		printf("test_int_to_binstr: TEST_A (FAILURE): Return code %d from int_to_binstr", num_chars);
		return EXIT_TEST_FAILURE;
	}

	for (i = 0; i < num_chars; i++) {
		if (str[i] != TEST_2A_EXPECTED[i]) {
			printf("test_int_to_binstr: TEST_A (FAILURE): num = %d, nbits = %u, EXPECT[%d] = %c, return value = %d\n", (uint32_t)TEST_2A_DEC, (uint8_t)TEST_2A_BITS, i, TEST_2A_EXPECTED[i], (uint8_t)TEST_2A_BITS + (uint8_t)PREFIX_BYTES_BIN);
			printf("                                      num = %d, nbits = %u, RESULT[%d] = %c, return value = %d\n", (uint32_t)TEST_2A_DEC, (uint8_t)TEST_2A_BITS, i, str[i], num_chars);
			return EXIT_TEST_FAILURE;
		}
	}
	printf("test_int_to_binstr: TEST_A (SUCCESS): num = %d, nbits = %u, EXPECT = %s, return value = %d\n", (uint32_t)TEST_2A_DEC, (uint8_t)TEST_2A_BITS, TEST_2A_EXPECTED, (uint8_t)TEST_2A_BITS + (uint8_t)PREFIX_BYTES_BIN);
	printf("                                      num = %d, nbits = %u, RESULT = %s, return value = %d\n", (uint32_t)TEST_2A_DEC, (uint8_t)TEST_2A_BITS, str, num_chars);

	num_chars = int_to_binstr(str, size, (uint32_t)TEST_2B_DEC, TEST_2B_BITS);

	if (num_chars < 0) {
		printf("test_int_to_binstr: TEST_B (FAILURE): Return code %d from int_to_binstr", num_chars);
		return EXIT_TEST_FAILURE;
	}

	for (i = 0; i < num_chars; i++) {
		if (str[i] != TEST_2B_EXPECTED[i]) {
			printf("test_int_to_binstr: TEST_B (FAILURE): num = %d, nbits = %u, EXPECT[%d] = %c, return value = %d\n", (uint32_t)TEST_2B_DEC, (uint8_t)TEST_2B_BITS, i, TEST_2B_EXPECTED[i], (uint8_t)TEST_2B_BITS + (uint8_t)PREFIX_BYTES_BIN);
			printf("                                      num = %d, nbits = %u, RESULT[%d] = %c, return value = %d\n", (uint32_t)TEST_2B_DEC, (uint8_t)TEST_2B_BITS, i, str[i], num_chars);
			return EXIT_TEST_FAILURE;
		}
	}
	printf("test_int_to_binstr: TEST_B (SUCCESS): num = %d, nbits = %u, EXPECT = %s, return value = %d\n", (uint32_t)TEST_2B_DEC, (uint8_t)TEST_2B_BITS, TEST_2B_EXPECTED, (uint8_t)TEST_2B_BITS + (uint8_t)PREFIX_BYTES_BIN);
	printf("                                      num = %d, nbits = %u, RESULT = %s, return value = %d\n", (uint32_t)TEST_2B_DEC, (uint8_t)TEST_2B_BITS, str, num_chars);

	num_chars = int_to_binstr(str, size, (uint32_t)TEST_2C_DEC, TEST_2C_BITS);

	if (num_chars < 0) {
		printf("test_int_to_binstr: TEST_C (FAILURE): Return code %d from int_to_binstr", num_chars);
		return EXIT_TEST_FAILURE;
	}

	for (i = 0; i < num_chars; i++) {
		if (str[i] != TEST_2C_EXPECTED[i]) {
			printf("test_int_to_binstr: TEST_C (FAILURE): num = %d, nbits = %u, EXPECT[%d] = %c, return value = %d\n", (uint32_t)TEST_2C_DEC, (uint8_t)TEST_2C_BITS, i, TEST_2C_EXPECTED[i], (uint8_t)TEST_2C_BITS + (uint8_t)PREFIX_BYTES_BIN);
			printf("                                      num = %d, nbits = %u, RESULT[%d] = %c, return value = %d\n", (uint32_t)TEST_2C_DEC, (uint8_t)TEST_2C_BITS, i, str[i], num_chars);
			return EXIT_TEST_FAILURE;
		}
	}
	printf("test_int_to_binstr: TEST_C (SUCCESS): num = %d, nbits = %u, EXPECT = %s, return value = %d\n", (uint32_t)TEST_2C_DEC, (uint8_t)TEST_2C_BITS, TEST_2C_EXPECTED, (uint8_t)TEST_2C_BITS + (uint8_t)PREFIX_BYTES_BIN);
	printf("                                      num = %d, nbits = %u, RESULT = %s, return value = %d\n", (uint32_t)TEST_2C_DEC, (uint8_t)TEST_2C_BITS, str, num_chars);

	return EXIT_TEST_SUCCESS;
}

int test_uint_to_hexstr(char* str, size_t size, uint32_t num, uint8_t nbits) {
	int i;
	int num_chars;

	num_chars = uint_to_hexstr(str, size, (uint32_t)TEST_3A_DEC, TEST_3A_BITS);

	if (num_chars < 0) {
		printf("test_uint_to_hexstr: TEST_A (FAILURE): Return code %d from uint_to_hexstr", num_chars);
		return EXIT_TEST_FAILURE;
	}

	for (i = 0; i < num_chars; i++) {
		if (str[i] != TEST_3A_EXPECTED[i]) {
			printf("test_uint_to_hexstr: TEST_A (FAILURE): num = %u, nbits = %u, EXPECT[%d] = %c, return value = %d\n", (uint32_t)TEST_3A_DEC, (uint8_t)TEST_3A_BITS, i, TEST_3A_EXPECTED[i], (uint8_t)(TEST_3A_BITS/BITS_PER_NIBBLE) + (uint8_t)PREFIX_BYTES_HEX);
			printf("                                       num = %u, nbits = %u, RESULT[%d] = %c, return value = %d\n", (uint32_t)TEST_3A_DEC, (uint8_t)TEST_3A_BITS, i, str[i], num_chars);
			//return EXIT_TEST_FAILURE;
		}
	}
	printf("test_uint_to_hexstr: TEST_A (SUCCESS): num = %u, nbits = %u, EXPECT = %s, return value = %d\n", (uint32_t)TEST_3A_DEC, (uint8_t)TEST_3A_BITS, TEST_3A_EXPECTED, (uint8_t)(TEST_3A_BITS/BITS_PER_NIBBLE) + (uint8_t)PREFIX_BYTES_HEX);
	printf("                                       num = %u, nbits = %u, RESULT = %s, return value = %d\n", (uint32_t)TEST_3A_DEC, (uint8_t)TEST_3A_BITS, str, num_chars);

	num_chars = uint_to_hexstr(str, size, (uint32_t)TEST_3B_DEC, TEST_3B_BITS);

	if (num_chars < 0) {
		printf("test_uint_to_hexstr: TEST_B (FAILURE): Return code %d from uint_to_hexstr", num_chars);
		return EXIT_TEST_FAILURE;
	}

	for (i = 0; i < num_chars; i++) {
		if (str[i] != TEST_3B_EXPECTED[i]) {
			printf("test_uint_to_hexstr: TEST_B (FAILURE): num = %u, nbits = %u, EXPECT[%d] = %c, return value = %d\n", (uint32_t)TEST_3B_DEC, (uint8_t)TEST_3B_BITS, i, TEST_3B_EXPECTED[i], (uint8_t)(TEST_3B_BITS/BITS_PER_NIBBLE) + (uint8_t)PREFIX_BYTES_HEX);
			printf("                                       num = %u, nbits = %u, RESULT[%d] = %c, return value = %d\n", (uint32_t)TEST_3B_DEC, (uint8_t)TEST_3B_BITS, i, str[i], num_chars);
			//return EXIT_TEST_FAILURE;
		}
	}
	printf("test_uint_to_hexstr: TEST_B (SUCCESS): num = %u, nbits = %u, EXPECT = %s, return value = %d\n", (uint32_t)TEST_3B_DEC, (uint8_t)TEST_3B_BITS, TEST_3B_EXPECTED, (uint8_t)(TEST_3B_BITS/BITS_PER_NIBBLE) + (uint8_t)PREFIX_BYTES_HEX);
	printf("                                       num = %u, nbits = %u, RESULT = %s, return value = %d\n", (uint32_t)TEST_3B_DEC, (uint8_t)TEST_3B_BITS, str, num_chars);

	num_chars = uint_to_hexstr(str, size, (uint32_t)TEST_3C_DEC, TEST_3C_BITS);

	if (num_chars < 0) {
		printf("test_uint_to_hexstr: TEST_C (FAILURE): Return code %d from uint_to_hexstr", num_chars);
		return EXIT_TEST_FAILURE;
	}

	for (i = 0; i < num_chars; i++) {
		if (str[i] != TEST_3C_EXPECTED[i]) {
			printf("test_uint_to_hexstr: TEST_C (FAILURE): num = %u, nbits = %u, EXPECT[%d] = %c, return value = %d\n", (uint32_t)TEST_3C_DEC, (uint8_t)TEST_3C_BITS, i, TEST_3C_EXPECTED[i], (uint8_t)(TEST_3C_BITS/BITS_PER_NIBBLE) + (uint8_t)PREFIX_BYTES_HEX);
			printf("                                       num = %u, nbits = %u, RESULT[%d] = %c, return value = %d\n", (uint32_t)TEST_3C_DEC, (uint8_t)TEST_3C_BITS, i, str[i], num_chars);
			//return EXIT_TEST_FAILURE;
		}
	}
	printf("test_uint_to_hexstr: TEST_C (SUCCESS): num = %u, nbits = %u, EXPECT = %s, return value = %d\n", (uint32_t)TEST_3C_DEC, (uint8_t)TEST_3C_BITS, TEST_3C_EXPECTED, (uint8_t)(TEST_3C_BITS/BITS_PER_NIBBLE) + (uint8_t)PREFIX_BYTES_HEX);
	printf("                                       num = %u, nbits = %u, RESULT = %s, return value = %d\n", (uint32_t)TEST_3C_DEC, (uint8_t)TEST_3C_BITS, str, num_chars);

	return EXIT_TEST_SUCCESS;
}

uint32_t test_twiggle_bit(uint32_t input, int bit, operation_t operation) {

}

uint32_t test_grab_three_bits(uint32_t input, int start_bit) {

}

char* test_hexdump(char* str, size_t size, const void* loc, size_t nbytes) {

}