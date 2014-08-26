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


#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "HID.h"

//================================================================================
// HID
//================================================================================

void HID_SendReport(uint8_t id, const void* data, int len);

//================================================================================
// Keyboard
//================================================================================

//Keyboard fixed/added missing Keys
#define KEY_PRINT			0xCE
#define KEY_SCROLL_LOCK		0xCF
#define KEY_PAUSE			0xD0

#ifndef USBCON

#define KEY_LEFT_CTRL		0x80
#define KEY_LEFT_SHIFT		0x81
#define KEY_LEFT_ALT		0x82
#define KEY_LEFT_GUI		0x83
#define KEY_RIGHT_CTRL		0x84
#define KEY_RIGHT_SHIFT		0x85
#define KEY_RIGHT_ALT		0x86
#define KEY_RIGHT_GUI		0x87

#define KEY_UP_ARROW		0xDA
#define KEY_DOWN_ARROW		0xD9
#define KEY_LEFT_ARROW		0xD8
#define KEY_RIGHT_ARROW		0xD7
#define KEY_BACKSPACE		0xB2
#define KEY_TAB				0xB3
#define KEY_RETURN			0xB0
#define KEY_ESC				0xB1
#define KEY_INSERT			0xD1
#define KEY_DELETE			0xD4
#define KEY_PAGE_UP			0xD3
#define KEY_PAGE_DOWN		0xD6
#define KEY_HOME			0xD2
#define KEY_END				0xD5
#define KEY_CAPS_LOCK		0xC1
#define KEY_F1				0xC2
#define KEY_F2				0xC3
#define KEY_F3				0xC4
#define KEY_F4				0xC5
#define KEY_F5				0xC6
#define KEY_F6				0xC7
#define KEY_F7				0xC8
#define KEY_F8				0xC9
#define KEY_F9				0xCA
#define KEY_F10				0xCB
#define KEY_F11				0xCC
#define KEY_F12				0xCD

//Raw Keyboard definitions
#define RAW_KEYBOARD_LEFT_CTRL   B00000001
#define RAW_KEYBOARD_LEFT_SHIFT  B00000010
#define RAW_KEYBOARD_LEFT_ALT    B00000100
#define RAW_KEYBOARD_LEFT_GUI  	 B00001000
#define RAW_KEYBOARD_RIGHT_CTRL  B00010000
#define RAW_KEYBOARD_RIGHT_SHIFT B00100000
#define RAW_KEYBOARD_RIGHT_ALT   B01000000
#define RAW_KEYBOARD_RIGHT_GUI 	 B10000000

#define RAW_KEYBOARD_UP_ARROW		0x52
#define RAW_KEYBOARD_DOWN_ARROW		0x51
#define RAW_KEYBOARD_LEFT_ARROW		0x50
#define RAW_KEYBOARD_RIGHT_ARROW	0x4F
#define RAW_KEYBOARD_SPACEBAR		0x2C
#define RAW_KEYBOARD_BACKSPACE		0x2A
#define RAW_KEYBOARD_TAB			0x2B
#define RAW_KEYBOARD_RETURN			0x28
#define RAW_KEYBOARD_ESC			0x29
#define RAW_KEYBOARD_INSERT			0x49
#define RAW_KEYBOARD_DELETE			0x4C
#define RAW_KEYBOARD_PAGE_UP		0x4B
#define RAW_KEYBOARD_PAGE_DOWN		0x4E
#define RAW_KEYBOARD_HOME			0x4A
#define RAW_KEYBOARD_END			0x4D
#define RAW_KEYBOARD_CAPS_LOCK		0x39
#define RAW_KEYBOARD_F1				0x3A
#define RAW_KEYBOARD_F2				0x3B
#define RAW_KEYBOARD_F3				0x3C
#define RAW_KEYBOARD_F4				0x3D
#define RAW_KEYBOARD_F5				0x3E
#define RAW_KEYBOARD_F6				0x3F
#define RAW_KEYBOARD_F7				0x40
#define RAW_KEYBOARD_F8				0x41
#define RAW_KEYBOARD_F9				0x42
#define RAW_KEYBOARD_F10			0x43
#define RAW_KEYBOARD_F11			0x44
#define RAW_KEYBOARD_F12			0x45
#define RAW_KEYBOARD_PRINT			0x46
#define RAW_KEYBOARD_SCROLL_LOCK	0x47
#define RAW_KEYBOARD_PAUSE			0x48

//Keyboard fixed/added missing Keys
#define KEY_PRINT				0xCE
#define KEY_SCROLL_LOCK			0xCF
#define KEY_PAUSE				0xD0

// typedef this report again because we cannot include the USBAPI
typedef HID_KeyboardReport_Data_t KeyReport;

class Keyboard_ : public Print{
public:
	Keyboard_(void);
	void begin(void);
	void end(void);
	virtual size_t write(uint8_t k);
	virtual size_t press(uint8_t k);
	virtual size_t release(uint8_t k);
	virtual void releaseAll(void);
private:
	KeyReport _keyReport;
	void sendReport(KeyReport* keys);
};
extern Keyboard_ Keyboard;

#endif
#endif

