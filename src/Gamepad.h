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

#pragma once

#include "HID.h"

#if !defined(_USING_HID)

#error "This is not an USB AVR or you use an old version of the IDE."

#else

//================================================================================
// Gamepad
//================================================================================

#ifndef HID_REPORTID_GAMEPAD
#define HID_REPORTID_GAMEPAD 6
#endif

// Dpad directions
#define GAMEPAD_DPAD_CENTERED 0
#define GAMEPAD_DPAD_UP 1
#define GAMEPAD_DPAD_UP_RIGHT 2
#define GAMEPAD_DPAD_RIGHT 3
#define GAMEPAD_DPAD_DOWN_RIGHT 4
#define GAMEPAD_DPAD_DOWN 5
#define GAMEPAD_DPAD_DOWN_LEFT 6
#define GAMEPAD_DPAD_LEFT 7
#define GAMEPAD_DPAD_UP_LEFT 8

static const uint8_t _gamepadReportDescriptor[] PROGMEM = {
	/* Gamepad with 32 buttons and 6 axis*/
	0x05, 0x01,							/* USAGE_PAGE (Generic Desktop) */
	0x09, 0x04,							/* USAGE (Joystick) */
	0xa1, 0x01,							/* COLLECTION (Application) */
	0x85, HID_REPORTID_GAMEPAD,			/*   REPORT_ID */
	/* 32 Buttons */
	0x05, 0x09,							/*   USAGE_PAGE (Button) */
	0x19, 0x01,							/*   USAGE_MINIMUM (Button 1) */
	0x29, 0x20,							/*   USAGE_MAXIMUM (Button 32) */
	0x15, 0x00,							/*   LOGICAL_MINIMUM (0) */
	0x25, 0x01,							/*   LOGICAL_MAXIMUM (1) */
	0x75, 0x01,							/*   REPORT_SIZE (1) */
	0x95, 0x20,							/*   REPORT_COUNT (32) */
	0x81, 0x02,							/*   INPUT (Data,Var,Abs) */
	/* 4 16bit Axis */
	0x05, 0x01,							/*   USAGE_PAGE (Generic Desktop) */
	0xa1, 0x00,							/*   COLLECTION (Physical) */
	0x09, 0x30,							/*     USAGE (X) */
	0x09, 0x31,							/*     USAGE (Y) */
	0x09, 0x33,							/*     USAGE (Rx) */
	0x09, 0x34,							/*     USAGE (Ry) */
	0x16, 0x00, 0x80,					/*     LOGICAL_MINIMUM (-32768) */
	0x26, 0xFF, 0x7F,					/*     LOGICAL_MAXIMUM (32767) */
	0x75, 0x10,							/*     REPORT_SIZE (16) */
	0x95, 0x04,							/*     REPORT_COUNT (4) */
	0x81, 0x02,							/*     INPUT (Data,Var,Abs) */
	/* 2 8bit Axis */
	0x09, 0x32,							/*     USAGE (Z) */
	0x09, 0x35,							/*     USAGE (Rz) */
	0x15, 0x80,							/*     LOGICAL_MINIMUM (-128) */
	0x25, 0x7F,							/*     LOGICAL_MAXIMUM (127) */
	0x75, 0x08,							/*     REPORT_SIZE (8) */
	0x95, 0x02,							/*     REPORT_COUNT (2) */
	0x81, 0x02,							/*     INPUT (Data,Var,Abs) */
	0xc0,								/*   END_COLLECTION */
	/* 2 Hat Switches */
	0x05, 0x01,							/*   USAGE_PAGE (Generic Desktop) */
	0x09, 0x39,							/*   USAGE (Hat switch) */
	0x09, 0x39,							/*   USAGE (Hat switch) */
	0x15, 0x01,							/*   LOGICAL_MINIMUM (1) */
	0x25, 0x08,							/*   LOGICAL_MAXIMUM (8) */
	0x95, 0x02,							/*   REPORT_COUNT (2) */
	0x75, 0x04,							/*   REPORT_SIZE (4) */
	0x81, 0x02,							/*   INPUT (Data,Var,Abs) */
	0xc0								/* END_COLLECTION */
};

typedef union {
	// 32 Buttons, 6 Axis, 2 D-Pads
	uint8_t whole8[];
	uint16_t whole16[];
	uint32_t whole32[];
	uint32_t buttons;

	struct{
		uint8_t button1 : 1;
		uint8_t button2 : 1;
		uint8_t button3 : 1;
		uint8_t button4 : 1;
		uint8_t button5 : 1;
		uint8_t button6 : 1;
		uint8_t button7 : 1;
		uint8_t button8 : 1;

		uint8_t button9 : 1;
		uint8_t button10 : 1;
		uint8_t button11 : 1;
		uint8_t button12 : 1;
		uint8_t button13 : 1;
		uint8_t button14 : 1;
		uint8_t button15 : 1;
		uint8_t button16 : 1;

		uint8_t button17 : 1;
		uint8_t button18 : 1;
		uint8_t button19 : 1;
		uint8_t button20 : 1;
		uint8_t button21 : 1;
		uint8_t button22 : 1;
		uint8_t button23 : 1;
		uint8_t button24 : 1;

		uint8_t button25 : 1;
		uint8_t button26 : 1;
		uint8_t button27 : 1;
		uint8_t button28 : 1;
		uint8_t button29 : 1;
		uint8_t button30 : 1;
		uint8_t button31 : 1;
		uint8_t button32 : 1;

		int16_t	xAxis;
		int16_t	yAxis;

		int16_t	rxAxis;
		int16_t	ryAxis;

		int8_t	zAxis;
		int8_t	rzAxis;

		uint8_t	dPad1 : 4;
		uint8_t	dPad2 : 4;
	};
} HID_GamepadReport_Data_t;

extern HID_ HID;

class Gamepad_{
public:
	inline Gamepad_(void){
		static HID_Descriptor cb = {
			.length = sizeof(_gamepadReportDescriptor),
			.descriptor = _gamepadReportDescriptor,
		};
		static HIDDescriptorListNode node(&cb);
		HID.AppendDescriptor(&node);
	}

	inline void begin(void){
		// release all buttons
		end();
	}

	inline void end(void){
		memset(&_report, 0, sizeof(_report));
		HID.SendReport(HID_REPORTID_GAMEPAD, &_report, sizeof(_report));
	}

	inline void write(void){ HID.SendReport(HID_REPORTID_GAMEPAD, &_report, sizeof(_report)); }
	inline void press(uint8_t b){ _report.buttons |= (uint32_t)1 << (b - 1); }
	inline void release(uint8_t b){ _report.buttons &= ~((uint32_t)1 << (b - 1)); }
	inline void releaseAll(void){ memset(&_report, 0x00, sizeof(_report)); }

	inline void buttons(uint32_t b){ _report.buttons = b; }
	inline void xAxis(int16_t a){ _report.xAxis = a; }
	inline void yAxis(int16_t a){ _report.yAxis = a; }
	inline void zAxis(int8_t a){ _report.zAxis = a; }
	inline void rxAxis(int16_t a){ _report.rxAxis = a; }
	inline void ryAxis(int16_t a){ _report.ryAxis = a; }
	inline void rzAxis(int8_t a){ _report.rzAxis = a; }
	inline void dPad1(int8_t d){ _report.dPad1 = d; }
	inline void dPad2(int8_t d){ _report.dPad2 = d; }

private:
	HID_GamepadReport_Data_t _report;
};
extern Gamepad_ Gamepad;

#endif
