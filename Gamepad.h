/*
Gamepad.h
Copyright (c) 2005-2014 Arduino.  All right reserved.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef __GAMEPADAPI__
#define __GAMEPADAPI__

// to access the HID_SendReport via USBAPI.h and report number
#include "Arduino.h"

//TODO workaround to access the weak sending function
void HID_SendReport(uint8_t id, const void* data, int len);

//================================================================================
// Gamepad
//================================================================================

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

typedef union {
	// 32 Buttons, 6 Axis, 2 D-Pads
	uint8_t whole8[15];
	uint16_t whole16[15 / 2];
	uint32_t whole32[15 / 4];
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

		uint8_t		dPad1 : 4;
		uint8_t		dPad2 : 4;
	};
} HID_GamepadReport_Data_t;

class Gamepad_{
public:
	inline Gamepad_(void){
		// empty
	}

	inline void begin(void){
		// release all buttons
		end();
	}

	inline void end(void){
		memset(&_report, 0, sizeof(_report));
		HID_SendReport(HID_REPORTID_GAMEPAD, &_report, sizeof(_report));
	}

	inline void write(void){ HID_SendReport(HID_REPORTID_GAMEPAD, &_report, sizeof(_report)); }
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