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

#ifndef __MOUSEAPI__
#define __MOUSEAPI__

// to access the HID_SendReport via USBAPI.h and report number
#include "Arduino.h"

//TODO workaround to access the weak sending function
void HID_SendReport(uint8_t id, const void* data, int len);

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

	inline void moveTo(uint16_t x, uint16_t y){
		// uses different report ID and different HID mouse device!
		uint32_t pos = ((uint32_t)y << 16) | x;
		HID_SendReport(HID_REPORTID_MOUSE_ABSOLUTE, &pos, sizeof(pos));
	}
};
extern Mouse_ Mouse;

#endif
