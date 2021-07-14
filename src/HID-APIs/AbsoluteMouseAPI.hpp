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

void AbsoluteMouseAPI::buttons(uint8_t b){
	if (b != _buttons){
		_buttons = b;
		moveTo(xAxis, yAxis, 0);
	}
}

int16_t AbsoluteMouseAPI::qadd16(int16_t base, int16_t increment) {
	// Separate between subtracting and adding
	if (increment < 0) {
		// Subtracting more would cause an undefined overflow
 		if ((int16_t)0x8000 - increment > base)
  			base = 0x8000;
		else
  			base += increment;
	}
	else {
		// Adding more would cause an undefined overflow
		if ((int16_t)0x7FFF - increment < base)
  			base = 0x7FFF;
		else
  			base += increment;
	}
	return base;
}

AbsoluteMouseAPI::AbsoluteMouseAPI(void):
xAxis(0), yAxis(0), _buttons(0)
{
	// Empty
}

void AbsoluteMouseAPI::begin(void){
	// release all buttons
	end();
}

void AbsoluteMouseAPI::end(void){
	_buttons = 0;
	moveTo(xAxis, yAxis, 0);
}

void AbsoluteMouseAPI::click(uint8_t b){
	_buttons = b;
	moveTo(xAxis, yAxis, 0);
	_buttons = 0;
	moveTo(xAxis, yAxis, 0);
}

void AbsoluteMouseAPI::moveTo(int x, int y, signed char wheel){
	xAxis = x;
	yAxis = y;
	HID_MouseAbsoluteReport_Data_t report;
	report.buttons = _buttons;
	// The range -32768...32767 is converted to 0...32767 because Windows 7
	// does not support negative coordinates.
	// Negative values are supported here for API compatibility reasons to keep (0,0) as a center of screen.
	// See detauls in AbsoluteMouse sources and here: https://github.com/NicoHood/HID/pull/306
	report.xAxis = ((int32_t)x + 32768) / 2;
	report.yAxis = ((int32_t)y + 32768) / 2;
	report.wheel = wheel;
	SendReport(&report, sizeof(report));
}

void AbsoluteMouseAPI::move(int x, int y, signed char wheel){
	moveTo(qadd16(xAxis, x), qadd16(yAxis, y), wheel);
}

void AbsoluteMouseAPI::press(uint8_t b){
	// press LEFT by default
	buttons(_buttons | b);
}

void AbsoluteMouseAPI::release(uint8_t b){
	// release LEFT by default
	buttons(_buttons & ~b);
}

void AbsoluteMouseAPI::releaseAll(void){
	_buttons = 0;
	moveTo(xAxis, yAxis, 0);
}

bool AbsoluteMouseAPI::isPressed(uint8_t b){
	// check LEFT by default
	if ((b & _buttons) > 0)
		return true;
	return false;
}
