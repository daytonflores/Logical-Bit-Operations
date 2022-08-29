#ifndef _INC_BITOPS_H
#define _INC_BITOPS_H

#include <stdint.h>
#include <stdlib.h>

typedef enum {
	CLEAR,
	SET,
	TOGGLE
} operation_t;

int uint_to_binstr(char* str, size_t size, uint32_t num, uint8_t nbits);
int int_to_binstr(char* str, size_t size, int32_t num, uint8_t nbits);
int uint_to_hexstr(char* str, size_t size, uint32_t num, uint8_t nbits);
uint32_t twiggle_bit(uint32_t input, int bit, operation_t operation);
uint32_t grab_three_bits(uint32_t input, int start_bit);
char* hexdump(char* str, size_t size, const void* loc, size_t nbytes);

int test_uint_to_binstr(char* str, size_t size, uint32_t num, uint8_t nbits);
int test_int_to_binstr(char* str, size_t size, int32_t num, uint8_t nbits);
int test_uint_to_hexstr(char* str, size_t size, uint32_t num, uint8_t nbits);
uint32_t test_twiggle_bit(uint32_t input, int bit, operation_t operation);
uint32_t test_grab_three_bits(uint32_t input, int start_bit);
char* test_hexdump(char* str, size_t size, const void* loc, size_t nbytes);

#endif