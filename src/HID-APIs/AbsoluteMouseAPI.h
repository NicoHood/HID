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

// Include guard
#pragma once

#include <Arduino.h>
#include "HID-Settings.h"

#define MOUSE_LEFT		(1 << 0)
#define MOUSE_RIGHT		(1 << 1)
#define MOUSE_MIDDLE	(1 << 2)
#define MOUSE_PREV		(1 << 3)
#define MOUSE_NEXT		(1 << 4)
// actually this mouse report has 8 buttons (for smaller descriptor)
// but the last 3 wont do anything from what I tested
#define MOUSE_ALL (MOUSE_LEFT | MOUSE_RIGHT | MOUSE_MIDDLE | MOUSE_PREV | MOUSE_NEXT)


typedef union ATTRIBUTE_PACKED {
	// Absolute mouse report: 8 buttons, 2 absolute axis, wheel
	uint8_t whole8[0];
	uint16_t whole16[0];
	uint32_t whole32[0];
	struct ATTRIBUTE_PACKED {
		uint8_t buttons;
		int16_t xAxis;
		int16_t yAxis;
		int8_t wheel;
	};
} HID_MouseAbsoluteReport_Data_t;


class AbsoluteMouseAPI
{
protected:
	int16_t xAxis;
	int16_t yAxis;
	uint8_t _buttons;
	inline void buttons(uint8_t b);

	inline int16_t qadd16(int16_t base, int16_t increment);

public:
	inline AbsoluteMouseAPI(void);
	inline void begin(void);
	inline void end(void);

	inline void click(uint8_t b = MOUSE_LEFT);
	inline void moveTo(int x, int y, signed char wheel = 0);
	inline void move(int x, int y, signed char wheel = 0);
	inline void press(uint8_t b = MOUSE_LEFT);
	inline void release(uint8_t b = MOUSE_LEFT);
	inline void releaseAll(void);
	inline bool isPressed(uint8_t b = MOUSE_LEFT);

	// Sending is public in the base class for advanced users.
	virtual void SendReport(void* data, int length) = 0;
};

// Implementation is inline
#include "AbsoluteMouseAPI.hpp"
