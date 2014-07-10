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

#ifndef HID_H
#define HID_H

#include <Arduino.h>
#include "HID_Reports.h"

#ifdef USBCON
#include "Platform.h"
#include "USBAPI.h"
#include "USBDesc.h"

//================================================================================
//Settings
//================================================================================

// deactive unnecessary stuff for Leonardo/Micro
// reports needs to be <=255 bytes for leonardo/micro!
#define HID_MOUSE_ENABLE 54
#define HID_KEYBOARD_ENABLE 65-18 //18 for missing led out report = 47
//#define HID_RAWKEYBOARD_ENABLE 30
#define HID_MEDIA_ENABLE 25
#define HID_SYSTEM_ENABLE 24
#define HID_GAMEPAD1_ENABLE 71
//#define HID_GAMEPAD2_ENABLE 71
//#define HID_JOYSTICK1_ENABLE 51
//#define HID_JOYSTICK2_ENABLE 51
//#define HID_MIDI_ENABLE

#endif

//================================================================================
// HID
//================================================================================

//NHP Definitions

// Start Mask
#define NHP_MASK_START		0xC0 //B11|000000 the two MSB bits
#define NHP_MASK_LEAD		0xC0 //B11|000000
#define NHP_MASK_DATA		0x00 //B0|0000000 only the first MSB is important
#define NHP_MASK_END		0x80 //B10|000000

// Content Mask
#define NHP_MASK_LENGTH		0x38 //B00|111|000
#define NHP_MASK_COMMAND	0x0F //B0000|1111
#define NHP_MASK_DATA_7BIT	0x7F //B0|1111111
#define NHP_MASK_DATA_4BIT	0x0F //B0000|1111
#define NHP_MASK_DATA_3BIT	0x07 //B00000|111
#define NHP_MASK_ADDRESS	0x3F //B00|111111

// Reserved Addresses
#define NHP_ADDRESS_CONTROL 0x01

// Reserved Usages
#define NHP_USAGE_ARDUINOHID 0x01

// Serial to write Protocol data to. Default: Serial
#define HID_SERIAL Serial

class HID_{
public:
	HID_(void);
	void begin(void);
	void end(void);

	// everything public for your own modifications
	void sendReport(uint8_t ReportID, const void* HIDReport, uint8_t length);
private:
	// simple copy/modification of the NicoHoodProtocol writechecksum function
	void NHPwriteChecksum(uint8_t address, uint16_t indata);
};
extern HID_ HID;

//================================================================================
// Mouse
//================================================================================

#define MOUSE_LEFT		0x01
#define MOUSE_RIGHT		0x02
#define MOUSE_MIDDLE	0x04
#define MOUSE_PREV		0x08
#define MOUSE_NEXT		0x10
#define MOUSE_ALL (MOUSE_LEFT | MOUSE_RIGHT | MOUSE_MIDDLE | MOUSE_PREV | MOUSE_NEXT)

class Mouse_{
public:
	Mouse_(void);
	void begin(void);
	void end(void);
	void click(uint8_t b = MOUSE_LEFT);
	void move(signed char x, signed char y, signed char wheel = 0);	
	void press(uint8_t b = MOUSE_LEFT);		// press LEFT by default
	void release(uint8_t b = MOUSE_LEFT);	// release LEFT by default
	void releaseAll(void);
	bool isPressed(uint8_t b = MOUSE_LEFT);	// check LEFT by default
private:
	void buttons(uint8_t b);
	HID_MouseReport_Data_t _report;
};
extern Mouse_ Mouse;

//================================================================================
// Keyboard
//================================================================================

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

//Keyboard fixed/added missing Keys
#define KEY_PRINT			0xCE
#define KEY_SCROLL_LOCK		0xCF
#define KEY_PAUSE			0xD0

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
	HID_KeyboardReport_Data_t _report;
};
extern Keyboard_ Keyboard;

//================================================================================
// Media
//================================================================================

#define MEDIA_FAST_FORWARD		0xB3
#define MEDIA_REWIND			0xB4
#define MEDIA_NEXT				0xB5
#define MEDIA_PREVIOUS			0xB6
#define MEDIA_STOP				0xB7
#define MEDIA_PLAY_PAUSE		0xCD

#define MEDIA_VOLUME_MUTE		0xE2
#define MEDIA_VOLUME_UP			0xE9
#define MEDIA_VOLUME_DOWN		0xEA

#define MEDIA_EMAIL_READER		0x18A
#define MEDIA_CALCULATOR		0x192
#define MEDIA_EXPLORER			0x194

#define MEDIA_BROWSER_HOME		0x223
#define MEDIA_BROWSER_BACK		0x224
#define MEDIA_BROWSER_FORWARD	0x225
#define MEDIA_BROWSER_REFRESH	0x227
#define MEDIA_BROWSER_BOOKMARKS	0x22A

class Media_{
public:
	Media_(void);
	void begin(void);
	void end(void);
	void write(uint16_t m);
	void press(uint16_t m);
	void release(uint16_t m);
	void releaseAll(void);
private:
	HID_MediaReport_Data_t _report;
};
extern Media_ Media;

//================================================================================
// System
//================================================================================

#define SYSTEM_POWER_DOWN	0x81
#define SYSTEM_SLEEP		0x82
#define SYSTEM_WAKE_UP		0x83

class System_{
public:
	System_(void);
	void begin(void);
	void end(void);
	void write(uint8_t s);
	void press(uint8_t s);
	void release(void);
	void releaseAll(void);
};
extern System_ System;

//================================================================================
// Gamepad
//================================================================================

class Gamepad_{
public:
	Gamepad_(uint8_t reportID);
	void begin(void);
	void end(void);
	void write(void);
	void press(uint8_t b);
	void release(uint8_t b);
	void releaseAll(void);
	inline void buttons(uint32_t b){ _report.buttons=b; }
	inline void xAxis(uint16_t a){ _report.xAxis=a; }
	inline void yAxis(uint16_t a){ _report.yAxis=a; }
	inline void zAxis(uint16_t a){ _report.zAxis=a; }
	inline void rxAxis(uint16_t a){ _report.rxAxis=a; }
	inline void ryAxis(uint16_t a){ _report.ryAxis=a; }
	inline void rzAxis(uint16_t a){ _report.rzAxis=a; }
	inline void dPad1(uint8_t d){ _report.dPad1=d; }
	inline void dPad2(uint8_t d){ _report.dPad2=d; }
private:
	HID_GamepadReport_Data_t _report;
	uint8_t _reportID;
};
extern Gamepad_ Gamepad1;
extern Gamepad_ Gamepad2;

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
	inline void buttons(uint8_t b){ _report.buttons=b; }
	inline void xAxis(uint16_t a){ _report.xAxis=a; }
	inline void yAxis(uint16_t a){ _report.yAxis=a; }

private:
	HID_JoystickReport_Data_t _report;
	uint8_t _reportID;
};
extern Joystick_ Joystick1;
extern Joystick_ Joystick2;

#endif

