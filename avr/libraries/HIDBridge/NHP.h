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
#define NHP_COMMAND_MASK	0x0F // B0000|1111 // 4bit command(0-15) in lead block

// Data
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

// protocol data for temporary variables
typedef union {
	struct { //TODO change order to save flash?
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
			uint16_t data16[sizeof(data) / sizeof(uint16_t)];
			uint8_t  data8[sizeof(data)];
			uint8_t command : 4;
		};
	};
	uint8_t raw[sizeof(uint8_t) + sizeof(uint8_t) + sizeof(uint32_t) + sizeof(readBuffer)];
} NHP_Read_Data_t;

// protocol data for temporary variables
typedef union {
	struct{
		// buffer for write operations
		uint8_t writeBuffer[NHP_WRITE_BUFFER_SIZE];
		uint8_t writeLength;
	};

	uint8_t raw[sizeof(writeBuffer) + sizeof(uint8_t)];
} NHP_Write_Data_t;

//================================================================================
// Protocol Function Prototypes
//================================================================================

static bool NHPread(uint8_t input, NHP_Read_Data_t* protocol) {
	// get old protocol states and save into temporary variables (better compiler optimization)
	uint8_t readLength = protocol->readLength;
	uint8_t mode;
	uint8_t blocks = protocol->blocks;
	uint8_t errorLevel = protocol->errorLevel;
	uint32_t data = protocol->data;
	uint8_t address;
	bool newInput = false;

	// completely reset the protocol after sucessfull reading/error last time
	if (protocol->mode) {
		blocks = 0;
		readLength = 0;
	}
	// check if previous reading had a lead error, copy that lead byte to the beginning
	else if (errorLevel == NHP_ERR_LEAD) {
		protocol->readBuffer[0] = protocol->readBuffer[readLength];
		readLength = 1;
	}

	// write new byte input to the buffer
	protocol->readBuffer[readLength++] = input;

	// reset mode and errorLevel to the default (no error, no input)
	errorLevel = NHP_ERR_NONE;
	mode = NHP_IN_PROGRESS;

	// check the header(lead/data/end) indicator
	uint8_t header = input & NHP_HEADER_MASK;

	if (header == NHP_HEADER_LEAD)
	{
		if (blocks) {
			// we were still reading! Log an error but continue reading with this new lead
			// set indicator to move this lead byte to the beginning next reading
			errorLevel = NHP_ERR_LEAD;
			// write the buffer without the new lead, move it next reading
			readLength--;
		}

		// read command indicator or block length
		blocks = (input >> NHP_LENGTH_OFFSET) & (NHP_LENGTH_MASK >> NHP_LENGTH_OFFSET);

		if (blocks == 0 || blocks == 1) {
			// save command in data variable
			data = input & NHP_COMMAND_MASK;
			// return command indicator, reset next reading
			mode = NHP_COMMAND;
			newInput = true;
		}
		// address data
		else if (blocks == 7) {
			// save block length + first 4 data bits (special 32 bit case)
			data = input & NHP_DATA_4BIT_MASK;
			blocks -= 2;
		}
		else {
			// save block length + first 3 data bits
			data = input & NHP_DATA_3BIT_MASK;
			blocks--;
		}
	}

	else if (header == NHP_HEADER_END)
	{
		// reset next reading on both: valid input or error
		if (blocks == 1){
			// valid input, save the address
			address = input & NHP_ADDRESS_MASK;
			mode = NHP_ADDRESS;
			newInput = true;
		}
		else{
			// too early for an end, reset next time
			errorLevel = NHP_ERR_END;
			mode = NHP_RESET;
		}
	}

	else if (header == NHP_HEADER_DATA_A || header == NHP_HEADER_DATA_B)
	{
		if (blocks >= 2) {
			// get next 7 bits of data
			blocks--;
			data <<= 7;
			// normally dont need & NHP_DATA_7BIT_MASK because the MSB bit is zero
			data |= (input & NHP_DATA_7BIT_MASK);
		}
		else {
			// log an error, expecting a lead or end byte
			errorLevel = NHP_ERR_DATA;
			mode = NHP_RESET;
		}
	}

	// save temporary values to the data struct
	protocol->blocks = blocks;
	protocol->mode = mode;
	protocol->readLength = readLength;
	protocol->address = address;
	protocol->errorLevel = errorLevel;
	protocol->data = data;

	// return if we have a new address or command
	return newInput;
}

//================================================================================
// Write NHP
//================================================================================

static uint8_t NHPwriteCommand(uint8_t command) {
	// write lead mask 11 + length 00|0 or 00|1 including the last bit for the 4 bit command
	// return the command with protocol around
	return NHP_HEADER_LEAD | (command & NHP_COMMAND_MASK);
}

static void NHPwriteAddress(uint8_t address, uint32_t data, NHP_Write_Data_t* protocol) {
	// start with the maximum size of blocks (6+1 for special MSB case)
	uint8_t blocks = 7;

	// check for the first 7 bit block that doesnt fit into the first 3 bits
	while (blocks > 2) {
		uint8_t nextvalue = (data >> (7 * (blocks - 3)));
		if (nextvalue > NHP_DATA_3BIT_MASK) {
			// data won't fit into the first 3 bits, wee need an extra block for them
			// don't write them to the lead block, keep the data for the data blocks
			if (blocks == 7) {
				// special case for the MSB where we still want to write
				// the 'too big' value into the lead block
				protocol->writeBuffer[0] = nextvalue;
				blocks = 6;
			}
			break;
		}
		else {
			// write the possible first 3 bits and check again if the value is zero
			// this also ensures that the first byte is always initialized
			protocol->writeBuffer[0] = nextvalue;
			blocks--;

			// we have our first bits, stop
			if (nextvalue)
				break;
		}
	}

	// write the rest of the data blocks
	uint8_t datablocks = blocks - 2;
	while (datablocks > 0) {
		protocol->writeBuffer[datablocks] = data & NHP_DATA_7BIT_MASK;
		data >>= 7;
		datablocks--;
	}

	// add lead 11 + length to the first 3 (or 4 for special MSB case) data bits
	protocol->writeBuffer[0] |= NHP_HEADER_LEAD | (blocks << NHP_LENGTH_OFFSET);

	// write end 10 + address
	protocol->writeBuffer[blocks - 1] = NHP_HEADER_END | (address & NHP_ADDRESS_MASK);

	// save the number of blocks
	protocol->writeLength = blocks;
}

#endif