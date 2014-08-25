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


#ifndef GAMEPAD_H
#define GAMEPAD_H

#include "HID.h"

//================================================================================
// HID
//================================================================================

void HID_SendReport(uint8_t id, const void* data, int len);

//================================================================================
// Gamepad
//================================================================================

class Gamepad{
public:
	inline Gamepad(uint8_t num){
		switch (num){
		case 1:
			_reportID = HID_REPORTID_Gamepad1Report;
			break;
		case 2:
			_reportID = HID_REPORTID_Gamepad1Report;
			break;
		case 3:
			_reportID = HID_REPORTID_Gamepad1Report;
			break;
		case 4:
			_reportID = HID_REPORTID_Gamepad1Report;
			break;
		default:
			_reportID = HID_REPORTID_NotAReport;
			break;
		}
	}

	inline void begin(void){
		memset(&_report, 0, sizeof(_report));
		HID_SendReport(_reportID, &_report, sizeof(_report));
	}

	inline void end(void){ begin(); }
	inline void write(void){ HID_SendReport(_reportID, &_report, sizeof(_report));}
	inline void press(uint8_t b){ _report.buttons |= (uint32_t)1 << (b - 1); }
	inline void release(uint8_t b){	_report.buttons &= ~((uint32_t)1 << (b - 1)); }
	inline void releaseAll(void){ _report.buttons = 0;}

	inline void buttons(uint32_t b){ _report.buttons = b; }
	inline void xAxis(uint16_t a){ _report.xAxis = a; }
	inline void yAxis(uint16_t a){ _report.yAxis = a; }
	inline void zAxis(uint8_t a){ _report.zAxis = a; }
	inline void rxAxis(uint16_t a){ _report.rxAxis = a; }
	inline void ryAxis(uint16_t a){ _report.ryAxis = a; }
	inline void rzAxis(uint8_t a){ _report.rzAxis = a; }
	inline void dPad1(uint8_t d){ _report.dPad1 = d; }
	inline void dPad2(uint8_t d){ _report.dPad2 = d; }
private:
	HID_GamepadReport_Data_t _report;
	uint8_t _reportID;
};

#endif

