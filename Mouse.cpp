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

#include "Mouse.h"

#include "Platform.h"

//================================================================================
//================================================================================
//	Mouse

Mouse_::Mouse_(void) :
_buttons(0)
{
}

void Mouse_::begin(void)
{
#ifndef USBCON
	// release all buttons for Hoodloader
	_buttons = 0;
	move(0, 0, 0);
#endif
}

void Mouse_::end(void)
{
	// added here!
	_buttons = 0;
	move(0, 0, 0);
}

void Mouse_::click(uint8_t b)
{
	_buttons = b;
	move(0, 0, 0);
	_buttons = 0;
	move(0, 0, 0);
}

void Mouse_::move(signed char x, signed char y, signed char wheel)
{
	u8 m[4];
	m[0] = _buttons;
	m[1] = x;
	m[2] = y;
	m[3] = wheel;
	HID_SendReport(1, m, 4);
}

void Mouse_::buttons(uint8_t b)
{
	if (b != _buttons)
	{
		_buttons = b;
		move(0, 0, 0);
	}
}

void Mouse_::press(uint8_t b)
{
	buttons(_buttons | b);
}

void Mouse_::release(uint8_t b)
{
	buttons(_buttons & ~b);
}

bool Mouse_::isPressed(uint8_t b)
{
	if ((b & _buttons) > 0)
		return true;
	return false;
}