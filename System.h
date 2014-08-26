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


#ifndef SYSTEM_H
#define SYSTEM_H

#include "HID.h"

//================================================================================
// HID
//================================================================================

void HID_SendReport(uint8_t id, const void* data, int len);

//================================================================================
// System
//================================================================================

#define SYSTEM_POWER_DOWN	0x81
#define SYSTEM_SLEEP		0x82
#define SYSTEM_WAKE_UP		0x83

class System_{
public:
	inline System_(void){
		// empty
	}

	inline void begin(void){
		uint8_t _report = 0;
		HID_SendReport(HID_REPORTID_SystemReport, &_report, sizeof(_report));
	}

	inline void end(void){
		begin();
	}

	inline void write(uint8_t s){
		press(s);
		release();
	}

	inline void press(uint8_t s){
		HID_SendReport(HID_REPORTID_SystemReport, &s, sizeof(s));
	}

	inline void release(void){
		begin();
	}

	inline void releaseAll(void){
		begin();
	}
};
extern System_ System;

#endif

