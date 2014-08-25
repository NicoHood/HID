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


#ifndef MOUSE_H
#define MOUSE_H

#include "HID.h"

//================================================================================
// HID
//================================================================================

void HID_SendReport(uint8_t id, const void* data, int len);

//================================================================================
// Mouse
//================================================================================

#ifndef USBCON

#define MOUSE_LEFT		0x01
#define MOUSE_RIGHT		0x02
#define MOUSE_MIDDLE	0x04
#define MOUSE_PREV		0x08
#define MOUSE_NEXT		0x10
#define MOUSE_ALL (MOUSE_LEFT | MOUSE_RIGHT | MOUSE_MIDDLE | MOUSE_PREV | MOUSE_NEXT)

class Mouse_
{
private:
	uint8_t _buttons;
	void buttons(uint8_t b);
public:
	Mouse_(void);
	void begin(void);
	void end(void);
	void click(uint8_t b = MOUSE_LEFT);
	void move(signed char x, signed char y, signed char wheel = 0);
	void press(uint8_t b = MOUSE_LEFT);		// press LEFT by default
	void release(uint8_t b = MOUSE_LEFT);	// release LEFT by default
	bool isPressed(uint8_t b = MOUSE_LEFT);	// check LEFT by default
};
extern Mouse_ Mouse;
#endif


#endif

