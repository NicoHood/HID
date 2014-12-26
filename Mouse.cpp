/*
Mouse.cpp
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

#include "Mouse.h"

//================================================================================
//================================================================================
//	Mouse

Mouse_ Mouse;

Mouse_::Mouse_(void) : _buttons(0)
{
}

void Mouse_::begin(void)
{
}

void Mouse_::end(void)
{
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

void Mouse_::moveTo(uint16_t x, uint16_t y)
{
	uint32_t pos = ((uint32_t)y << 16) | x;
	HID_SendReport(HID_REPORTID_MOUSE_ABSOLUTE, &pos, sizeof(pos));
}
