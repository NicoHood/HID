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

#include "NHP.h"

//================================================================================
// Read NHP
//================================================================================

bool readNHP(uint8_t input, NHP_Read_Data_t* protocol) {
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

		if (blocks == NHP_LENGTH_COMMAND_0 || blocks == NHP_LENGTH_COMMAND_1) {
			// save command in data variable
			data = input & NHP_COMMAND_MASK;
			// return command indicator, reset next reading
			mode = NHP_COMMAND;
			newInput = true;
		}
		// address data
		else if (blocks == NHP_LENGTH_HIGH_MSB31) {
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
		if (blocks > 1) {
			// get next 7 bits of data
			blocks--;
			data <<= NHP_DATA_7BIT;
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

uint8_t writeNHPCommand(uint8_t command) {
	// write lead mask 11 + length 00|0 or 00|1 including the last bit for the 4 bit command
	// return the command with protocol around
	return NHP_HEADER_LEAD | (command & NHP_COMMAND_MASK);
}

void writeNHPAddress(uint8_t address, uint32_t data, NHP_Write_Data_t* protocol) {
	// start with the maximum size of blocks (6+1 for special MSB case)
	uint8_t blocks = 7;

	// check for the first 7 bit block that doesnt fit into the first 3 bits
	while (blocks > 2) {
		// get the next 7 bit data block, starting from MSB to LSB
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