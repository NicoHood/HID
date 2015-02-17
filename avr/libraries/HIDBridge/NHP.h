/*
Copyright (c) 2014-2015 NicoHood
See the readme for credit to other people.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#ifndef NHP_H
#define NHP_H


#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h> //uint_t definitions
#include <stdbool.h> //bool type

//================================================================================
//Settings
//================================================================================

// empty

//================================================================================
//Definitions
//================================================================================

// Header Masks
#define NHP_HEADER_MASK		0xC0 // B11|000000 the two MSB bits determine the block type
#define NHP_HEADER_LEAD		0xC0 // B11|000000 11 MSB
#define NHP_HEADER_DATA_A	0x00 // B00|000000 0X MSB only the first MSB is important
#define NHP_HEADER_DATA_B	0x40 // B01|000000 0X MSB only the first MSB is important
#define NHP_HEADER_END		0x80 // B10|000000 01 MSB

// Lead
#define NHP_LENGTH_MASK		0x38 // B00|111|000
#define NHP_LENGTH_OFFSET      3
#define NHP_LENGTH_COMMAND_0   0 // length 0 indicates a command
#define NHP_LENGTH_COMMAND_1   1 // length 1 indicates a command
#define NHP_LENGTH_HIGH_MSB31  7 // length 7 indicates MSB 31 is high (1)
#define NHP_COMMAND_MASK	0x0F // B0000|1111 // 4bit command(0-15) in lead block

// Data
#define NHP_DATA_7BIT		   7 // data blocks contain 7 bit of information
#define NHP_DATA_7BIT_MASK	0x7F // B0|1111111 // data in data block
#define NHP_DATA_4BIT_MASK	0x0F // B0000|1111 // data in lead (32 bit special MSB case)
#define NHP_DATA_3BIT_MASK	0x07 // B00000|111 // data in lead

// End
#define NHP_ADDRESS_MASK	0x3F // B00|111111 // 6 bit address (0-63) in end block

// mode indicators
#define NHP_IN_PROGRESS	0
#define NHP_ADDRESS		1
#define NHP_COMMAND		2
#define NHP_RESET		3

// errorLevels
#define NHP_ERR_NONE	0
#define NHP_ERR_LEAD	1
#define NHP_ERR_DATA	2
#define NHP_ERR_END		3

// buffer sizes
#define NHP_BUFFER_SIZE 6
#define NHP_READ_BUFFER_SIZE NHP_BUFFER_SIZE
#define NHP_WRITE_BUFFER_SIZE NHP_BUFFER_SIZE

// definition to convert an uint8_t array to an uint16_t/uint32_t at any position (thx timeage!)
#define UINT16_AT_OFFSET(p_to_8, offset)    ((uint16_t)*((const uint16_t *)((p_to_8)+(offset))))
#define UINT32_AT_OFFSET(p_to_8, offset)    ((uint32_t)*((const uint32_t *)((p_to_8)+(offset))))

//================================================================================
// Typedefs
//================================================================================
	
// protocol read data for temporary variables
typedef union {
	struct {
		// buffer for read operations
		uint8_t readBuffer[NHP_READ_BUFFER_SIZE];

		// in progress reading data variables
		uint8_t readLength : 3;	// 0-6 (7 invalid)
		uint8_t mode : 2;		// in progress, address, command, reset on error (except lead)
		uint8_t blocks : 3;		// 0-7
		// 2nd byte
		uint8_t errorLevel : 2;	// no err, lead err, data err, end err
		uint8_t address : 6;	// 6 bit address (0-63)
		union{
			// temporary + final data
			uint32_t data;
			uint32_t data32;
			uint16_t data16[sizeof(uint32_t) / sizeof(uint16_t)];
			uint8_t  data8[sizeof(uint32_t) / sizeof(uint8_t)];
			uint8_t command : 4;
		};
	};
	uint8_t raw[NHP_READ_BUFFER_SIZE + sizeof(uint8_t) + sizeof(uint8_t) + sizeof(uint32_t)];
} NHP_Read_Data_t;

// protocol write data for temporary variables
typedef union {
	struct{
		// buffer for write operations
		uint8_t writeBuffer[NHP_WRITE_BUFFER_SIZE];
		uint8_t writeLength;
	};

	uint8_t raw[NHP_WRITE_BUFFER_SIZE + sizeof(uint8_t)];
} NHP_Write_Data_t;

//================================================================================
// Function Prototypes
//================================================================================

bool readNHP(uint8_t input, NHP_Read_Data_t* protocol);
uint8_t writeNHPCommand(uint8_t command);
void writeNHPAddress(uint8_t address, uint32_t data, NHP_Write_Data_t* protocol);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // include guard