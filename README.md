# PES-Assignment-1
 Code for Assign 1 for PRES, ECEN 5813-001B, Fall 2022

# Build and Run

## Unix
- Navigate to directory of Makefile
- Run "make"
- Run "./main"

## Windows
- Navigate to directory of Makefile
- Run "make"
- Run "./main.exe"

# Test Your Own Values

- To utilize the test functions, you may modify the test case macro preambles in bitops.c, recompile, and run. Observe the printf statements according to the labeled test case(s) you modify

## test_uint_to_binstr

- For example, if we want to convert 25u to binary string using 9 bits then the following would be modified:
	- TEST_1A_DEC would be changed to: (25u)
		- Value must fall within range [0, 4294967295], inclusive
	- TEST_1A_BITS would be changed to the amount of bits to represent: (9u)
		- Value must fall within range [1, 32], inclusive
	- TEST_1A_RETURN would be changed to the expected size of binary string representation: (9u + 2u)
		- 2u is added to 9u to account for "0b" prefix in the string
	- TEST_1A_EXPECTED would be changed to the expected exact binary string representation, including 0b prefix: "0b000011001"

## test_int_to_binstr

- For example, if we want to convert -4 to binary string with 7 bits then the following would be modified:
	- TEST_2A_DEC would be changed to: (-4)
		- Value must fall within range [-2147483648, 2147483647], inclusive
	- TEST_2A_BITS would be changed to the amount of bits to represent: (7u)
		- Value must fall within range [1, 32], inclusive
	- TEST_2A_RETURN would be changed to the expected size of binary string representation: (7u + 2u)
		- 2u is added to 7u to account for "0b" prefix in the string
	- TEST_2A_EXPECTED would be changed to the expected exact binary string representation, including 0b prefix: "0b1111100"

## test_uint_to_hexstr

- For example, if we want to convert 8586 to hex string with 16 bits then the following would be modified:
	- TEST_3A_DEC would be changed to: (8586u)
		- Value must fall within range [0, 4294967295], inclusive
	- TEST_3A_BITS would be changed to the amount of bits to represent: (16u)
		- Value must be one of 4, 8, 16, 32 only
	- TEST_3A_RETURN would be changed to the expected size of hex string representation: ((16u/4u) + 2u)
		- 16u is divided by 4u because 4 bits of data will be displayed with each hex character
	- TEST_3A_EXPECTED would be changed to the expected exact hex string representation, including 0x prefix: "0x218A"

## test_twiggle_bit

- For example, if we want to SET bit #0 of 26:
	- TEST_4A_DEC would be changed to: (8586u)
		- Value must fall within range [0, 4294967295], inclusive
	- TEST_4A_BIT would be changed to: (0)
		- Value must fall within range [0, 31], inclusive
	- TEST_4A_OP would be changed to: (SET)
		- Value must be one of SET, CLEAR, TOGGLE only
	- TEST_4A_EXPECTED would be changed to the expected result: (8587u)

## test_grab_three_bits

- For example, if we want to grab consecutive bits [4:6] of 15444:
	- TEST_5A_DEC would be changed to: (15444u)
		- Value must fall within range [0, 4294967295], inclusive
	- TEST_5A_SBIT would be changed to: (4)
		- Value must fall within range [0, 28], inclusive
		- This would be the least significant of the three consecutive bits to grab
	- TEST_5A_EXPECTED would be changed to the expected result: (5u)
		- This will be the result of grabbing the three consecutive bits and shifting them all the way right. In this case, bits [4:6] were 0b101

## test_hexdump

- 

