#include <assert.h>
#include "bitops.h"

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

}

int test_int_to_binstr(char* str, size_t size, int32_t num, uint8_t nbits) {

}

int test_uint_to_hexstr(char* str, size_t size, uint32_t num, uint8_t nbits) {

}

uint32_t test_twiggle_bit(uint32_t input, int bit, operation_t operation) {

}

uint32_t test_grab_three_bits(uint32_t input, int start_bit) {

}

char* test_hexdump(char* str, size_t size, const void* loc, size_t nbytes) {

}