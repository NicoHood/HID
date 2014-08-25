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


#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "HID.h"

//================================================================================
// Joystick
//================================================================================

class Joystick_{
public:
	Joystick_(uint8_t reportID);
	void begin(void);
	void end(void);
	void write(void);
	void press(uint8_t b);
	void release(uint8_t b);
	void releaseAll(void);
	inline void buttons(uint8_t b){ _report.buttons = b; }
	inline void xAxis(uint16_t a){ _report.xAxis = a; }
	inline void yAxis(uint16_t a){ _report.yAxis = a; }

private:
	HID_JoystickReport_Data_t _report;
	uint8_t _reportID;
};
extern Joystick_ Joystick1;
extern Joystick_ Joystick2;

#endif

