/*
Copyright (c) 2014 NicoHood
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

#include "NicoHoodProtocol_c.h"

//================================================================================
// Public variables
//================================================================================

uint8_t NHPreadbuffer[6]={0};
uint8_t NHPreadlength=0;
uint8_t NHPwritebuffer[6]={0};
uint8_t NHPwritelength=0;

//================================================================================
// Private variables
//================================================================================

// Fully read data
static uint8_t mCommand=0;
static uint8_t mAddress=0;
static uint32_t mData=0;
static uint8_t mErrorLevel=NHP_INPUT_RESET;

// in progress reading data
static uint8_t mBlocks=0;
static uint32_t mWorkData=0;

//================================================================================
//General Functions
//================================================================================

// reset Protocol on the next reading to start a new clean reading
void NHPreset(void){ mErrorLevel=NHP_INPUT_RESET; }

// access for the variables
uint8_t  NHPgetCommand()   { return mCommand;    }
uint8_t  NHPgetAddress()   { return mAddress;    }
uint32_t NHPgetData()      { return mData;       }
uint16_t NHPgetChecksumData() { return mData;	   }
uint8_t  NHPgetChecksumData0() { return mData;	 }
uint8_t  NHPgetChecksumData1() { return mData>>8;}
uint8_t  NHPgetErrorLevel(){ return mErrorLevel; }

// reset buffer for read/write operations
void NHPresetreadbuffer() { 
	while(NHPreadlength){
		NHPreadlength--;
		NHPreadbuffer[NHPreadlength]=0;
	}
}
void NHPresetwritebuffer(){ 
	while(NHPwritelength){
		NHPwritelength--;
		NHPwritebuffer[NHPwritelength]=0;
	}
}

//================================================================================
//Read
//================================================================================

bool NHPread(uint8_t input){
	//reset if previous read was with an input/error
	if(mErrorLevel){
		// cancel any pending data reads if a reset was triggered
		if(mErrorLevel & NHP_INPUT_RESET){
			mBlocks=0;
			mWorkData=0;
		}
		// if previous read was a lead error keep this byte
		if(mErrorLevel&NHP_ERR_LEAD){
			NHPreadbuffer[0]=NHPreadbuffer[NHPreadlength];
			NHPreadlength=1;
		}
		else NHPreadlength=0;
	}

	// reset fully read data
	mCommand=0;
	mAddress=0;
	mData=0;
	mErrorLevel=0;

	//write input to the buffer
	NHPreadbuffer[NHPreadlength]=input;
	NHPreadlength++;

	// check the lead/end/data indicator
	switch(input&NHP_MASK_START){

	case(NHP_MASK_LEAD): 
		{
			// we were still reading!  Log an error
			if(mBlocks){
				mErrorLevel |= NHP_ERR_LEAD | NHP_ERR_READ;
				NHPreadlength--;
			}

			// read command indicator or block length
			mBlocks = (input & NHP_MASK_LENGTH)>>3;
			switch(mBlocks){
			case 0:
			case 1:
				// save 4 bit command
				mCommand=(input & NHP_MASK_COMMAND)+1;
				mBlocks = 0;
				mErrorLevel |= NHP_INPUT_COMMAND | NHP_INPUT_NEW;
				return true;
				break;
			case 7:
				// save block length + first 4 data bits (special case)
				mWorkData = input & NHP_MASK_DATA_4BIT;
				mBlocks -=2;
				break;
			default:
				// save block length + first 3 data bits
				mWorkData = input & NHP_MASK_DATA_3BIT;
				mBlocks--;
				break;
			}
		}
		break;

	case(NHP_MASK_END): 
		{
			if(mBlocks--==1){
				// save data + address
				mAddress=(input&0x3F)+1;
				mData=mWorkData;
				mErrorLevel |= NHP_INPUT_ADDRESS | NHP_INPUT_NEW;
				return true;
			}
			else{
				// log an error, not ready for an address byte, and reset data counters
				mErrorLevel |= NHP_ERR_DATA | NHP_ERR_READ;
				mBlocks=0;
			}
		}
		break;

		//case NHP_MASK_DATA1/2?? <--
	default: //NHP_MASK_DATA1/2
		{
			if(mBlocks--<2){
				// log an error, expecting an address or header byte
				mErrorLevel |= NHP_ERR_END | NHP_ERR_READ;
				mBlocks=0;
			}
			else{
				// get next 7 bits of data
				mWorkData<<=7;
				// dont need &NHP_MASK_DATA_7BIT because first bit is zero!
				mWorkData|=input; 
			}
		} 
		break;
	} // end switch

	// no new input
	return false; 
}

// reads two bytes and check its inverse
bool NHPreadChecksum(uint8_t input){
	if(NHPread(input)){
		// if there is an address input (comand invalid, too insecure)
		if(NHPgetAddress() && (((NHPgetData()&0xFFFF) ^ (NHPgetData()>>16))==0xFFFF)){
			// make sure to use getAddress() and getData()&0xFFFF
			return true;
		}
		// else you can forward the buffer or pass -1 as error
	}
	return false;
}

//================================================================================
//Write
//================================================================================

void NHPwriteCommand(uint8_t command){
	// send lead mask 11 + length 00|0 or 00|1 including the last bit for the 4 bit command
	NHPwritebuffer[0] = NHP_MASK_LEAD | ((command-1) & NHP_MASK_COMMAND);
	NHPwritelength=1;
}

void NHPwriteAddress(uint8_t address, uint32_t data){
	// start with the maximum size of blocks
	uint8_t blocks=7;

	// check for the first 7 bit block that doesnt fit into the first 3 bits
	while(blocks>2){
		uint8_t nextvalue=(data>>(7*(blocks-3)));
		if(nextvalue>NHP_MASK_DATA_3BIT){
			// special case for the MSB
			if(blocks==7) {
				NHPwritebuffer[0] = nextvalue;
				blocks--;
			}
			break;
		}
		else{
			// write the possible first 3 bits and check again after
			NHPwritebuffer[0] = nextvalue;
			blocks--;
		}
	}

	// write the rest of the data bits
	uint8_t datablocks=blocks-2;
	while(datablocks>0){
		NHPwritebuffer[datablocks] = data & NHP_MASK_DATA_7BIT;
		data>>=7;
		datablocks--;
	}

	// write lead + length mask
	NHPwritebuffer[0] |= NHP_MASK_LEAD | (blocks <<3);

	// write end mask
	NHPwritebuffer[blocks-1] = NHP_MASK_END | ((address-1) & NHP_MASK_ADDRESS);

	// save the length
	NHPwritelength=blocks;
}


// writes two bytes with its inverse
void NHPwriteChecksum(uint8_t address, uint16_t data){
	uint32_t temp=~data;
	uint32_t checksum=(temp<<16)|data;
	NHPwriteAddress(address,checksum);  
}

