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

#ifndef __RAWHIDAPI__
#define __RAWHIDAPI__

// to access the HID_SendReport via USBAPI.h and report number
#include "Arduino.h"

//================================================================================
// RawHID
//================================================================================

typedef union{
// a RAWHID_TX_SIZE byte buffer for rx or tx
uint8_t whole8[RAWHID_TX_SIZE];
uint16_t whole16[RAWHID_TX_SIZE / 2];
uint32_t whole32[RAWHID_TX_SIZE / 4];
uint8_t buff[RAWHID_TX_SIZE];
} HID_RawKeyboardReport_Data_t;

class RawHID_ : public Print{
public:
	inline RawHID_(void){
		// empty
	}

	inline void begin(void){
		// empty
	}

	inline void end(void){
		// empty
	}

	using Print::write; // to get the String version of write
	inline size_t write(uint8_t b){
		write(&b, 1);
	}

	inline size_t write(const uint8_t *buffer, size_t size){
		size_t bytesleft = size;
		// first work through the buffer thats already there
		while (bytesleft >= RAWHID_RX_SIZE){
			HID_SendReport(HID_REPORTID_RAWHID, &buffer[size - bytesleft], RAWHID_RX_SIZE);
			bytesleft -= RAWHID_RX_SIZE;
		}
		// write down the other bytes and fill with zeros
		if (bytesleft){
			uint8_t rest[RAWHID_RX_SIZE];
			memcpy(rest, &buffer[size - bytesleft], bytesleft);
			memset(&rest[bytesleft], 0, RAWHID_RX_SIZE - bytesleft);
			HID_SendReport(HID_REPORTID_RAWHID, &rest, RAWHID_RX_SIZE);
		}
	}
};
extern RawHID_ RawHID;

#endif