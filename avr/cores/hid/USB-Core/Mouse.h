/*
Mouse.h
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

#ifndef __MOUSEAPI__
#define __MOUSEAPI__

// to access the HID_SendReport via USBAPI.h and report number
#include "Arduino.h"

//================================================================================
//================================================================================
//	Mouse

#define MOUSE_LEFT		(1 << 0)
#define MOUSE_RIGHT		(1 << 1)
#define MOUSE_MIDDLE	(1 << 2)
#define MOUSE_PREV		(1 << 3)
#define MOUSE_NEXT		(1 << 4)
// actually this mouse report has 8 buttons (for smaller descriptor)
// but the last 3 wont do anything from what I tested
#define MOUSE_ALL (MOUSE_LEFT | MOUSE_RIGHT | MOUSE_MIDDLE | MOUSE_PREV | MOUSE_NEXT)

typedef union{
	// mouse report: 8 buttons, position, wheel
	uint8_t whole8[4];
	uint16_t whole16[4 / 2];
	uint32_t whole32[4 / 4];
	struct{
		uint8_t buttons;
		int8_t xAxis;
		int8_t yAxis;
		int8_t wheel;
	};
} HID_MouseReport_Data_t;

typedef union{
	// mouse absolute report: 2 absolute axis
	uint8_t whole8[4];
	uint16_t whole16[4 / 2];
	uint32_t whole32[4 / 4];
	struct{
		int16_t xAxis;
		int16_t yAxis;
	};
} HID_MouseAbsoluteReport_Data_t;

class Mouse_
{
private:
	uint8_t _buttons;
	void buttons(uint8_t b);
public:
	inline Mouse_(void) {
		// removed this to avoid creating an instance of Mouse if not needed
		// the user should call begin first.
		//: _buttons(0){
		// empty
	}

	inline void begin(void){
		// release all buttons
		end();
	}

	inline void end(void){
		_buttons = 0;
		move(0, 0, 0);
	}

	inline void click(uint8_t b = MOUSE_LEFT){
		_buttons = b;
		move(0, 0, 0);
		_buttons = 0;
		move(0, 0, 0);
	}

	inline void move(signed char x, signed char y, signed char wheel = 0){
		u8 m[4];
		m[0] = _buttons;
		m[1] = x;
		m[2] = y;
		m[3] = wheel;
		HID_SendReport(HID_REPORTID_MOUSE, m, 4);
	}

	inline void press(uint8_t b = MOUSE_LEFT){
		// press LEFT by default
		buttons(_buttons | b);
	}

	inline void release(uint8_t b = MOUSE_LEFT){
		// release LEFT by default
		buttons(_buttons & ~b);
	}

	inline bool isPressed(uint8_t b = MOUSE_LEFT){
		// check LEFT by default
		if ((b & _buttons) > 0)
			return true;
		return false;
	}
#ifdef HID_MOUSE_ABSOLUTE_API_ENABLE
	inline void moveTo(int16_t x, int16_t y){
		// uses different report ID and different HID mouse device!
		uint32_t pos = ((uint32_t)y << 16) | x;
		HID_SendReport(HID_REPORTID_MOUSE_ABSOLUTE, &pos, sizeof(pos));
	}
#endif
};
extern Mouse_ Mouse;

#endif
