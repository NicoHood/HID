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


#ifndef DEFAULT_H
#define DEFAULT_H

#include "HID.h"

//================================================================================
// HID
//================================================================================

void HID_SendReport(uint8_t id, const void* data, int len);

//================================================================================
// RawHID
//================================================================================

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
			HID_SendReport(HID_REPORTID_RawKeyboardReport, &buffer[size - bytesleft], RAWHID_RX_SIZE);
			bytesleft -= RAWHID_RX_SIZE;
		}
		// write down the other bytes and fill with zeros
		if (bytesleft){
			uint8_t rest[RAWHID_RX_SIZE];
			memcpy(rest, &buffer[size - bytesleft], bytesleft);
			memset(&rest[bytesleft], 0, RAWHID_RX_SIZE - bytesleft);
			HID_SendReport(HID_REPORTID_RawKeyboardReport, &rest, RAWHID_RX_SIZE);
		}
	}
};
extern RawHID_ RawHID;

#endif

