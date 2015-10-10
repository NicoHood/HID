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
#include "TeensyKeylayouts.h"

#define HID_REPORT_KEYBOARD_START \
    0x05, 0x01,                      /* USAGE_PAGE (Generic Desktop)	  47 */ \
    0x09, 0x06,                      /* USAGE (Keyboard) */ \
    0xa1, 0x01                      /* COLLECTION (Application) */
    
#define HID_REPORT_KEYBOARD_REPORTID \
    0x85, HID_REPORTID_KEYBOARD      /*   REPORT_ID TODO order important?*/
    
#define HID_REPORT_KEYBOARD_START2 \
    0x05, 0x07                      /*   USAGE_PAGE (Keyboard) */ 

#define HID_REPORT_KEYBOARD_MODIFIERS \
      /* Keyboard Modifiers (shift, alt, ...) */ \
    0x19, 0xe0,                      /*   USAGE_MINIMUM (Keyboard LeftControl) */ \
    0x29, 0xe7,                      /*   USAGE_MAXIMUM (Keyboard Right GUI) */ \
    0x15, 0x00,                      /*   LOGICAL_MINIMUM (0) */ \
    0x25, 0x01,                      /*   LOGICAL_MAXIMUM (1) */ \
    0x75, 0x01,                      /*   REPORT_SIZE (1) */ \
	0x95, 0x08,                      /*   REPORT_COUNT (8) */ \
    0x81, 0x02                      /*   INPUT (Data,Var,Abs) */

#define HID_REPORT_KEYBOARD_RESERVED \
      /* Reserved byte TODO consumer and or system?*/ \
    0x95, 0x01,                      /*   REPORT_COUNT (1) */ \
    0x75, 0x08,                      /*   REPORT_SIZE (8) */ \
    0x81, 0x03                      /*   INPUT (Cnst,Var,Abs) */ \

#define HID_REPORT_KEYBOARD_KEYS \
      /* 6 Keyboard keys */ \
    0x95, 0x06,                      /*   REPORT_COUNT (6) */ \
    0x75, 0x08,                      /*   REPORT_SIZE (8) */ \
    0x15, 0x00,                      /*   LOGICAL_MINIMUM (0) */ \
    0x26, 0xE7, 0x00,                /*   LOGICAL_MAXIMUM (231) */ \
    0x05, 0x07,                      /*   USAGE_PAGE (Keyboard) */ \
    0x19, 0x00,                      /*   USAGE_MINIMUM (Reserved (no event indicated)) */ \
    0x29, 0xE7,                      /*   USAGE_MAXIMUM (Keyboard Right GUI) */ \
    0x81, 0x00                      /*   INPUT (Data,Ary,Abs) */

#define HID_REPORT_KEYBOARD_LEDS \
	/* 5 LEDs for num lock etc */ \
	0x05, 0x08,						 /*   USAGE_PAGE (LEDs) */ \
	0x19, 0x01,						 /*   USAGE_MINIMUM (Num Lock) */ \
	0x29, 0x05,						 /*   USAGE_MAXIMUM (Kana) TODO */ \
	0x95, 0x05,						 /*   REPORT_COUNT (5) */ \
	0x75, 0x01,						 /*   REPORT_SIZE (1) */ \
	0x91, 0x02,						 /*   OUTPUT (Data,Var,Abs) */ \
	/*  Reserved 3 bits TODO */ \
	0x95, 0x01,						 /*   REPORT_COUNT (1) */ \
	0x75, 0x03,						 /*   REPORT_SIZE (3) */ \
	0x91, 0x03						 /*   OUTPUT (Cnst,Var,Abs) */

#define HID_REPORT_KEYBOARD_END \
      /* End */ \
    0xc0                            /* END_COLLECTION */

#define HID_REPORT_KEYBOARD \
HID_REPORT_KEYBOARD_START, \
HID_REPORT_KEYBOARD_START2, \
HID_REPORT_KEYBOARD_MODIFIERS, \
HID_REPORT_KEYBOARD_RESERVED, \
HID_REPORT_KEYBOARD_KEYS, \
HID_REPORT_KEYBOARD_LEDS, \
HID_REPORT_KEYBOARD_END

#define HID_MULTIREPORT_KEYBOARD \
HID_REPORT_KEYBOARD_START, \
HID_REPORT_KEYBOARD_REPORTID, \
HID_REPORT_KEYBOARD_START2, \
HID_REPORT_KEYBOARD_MODIFIERS, \
HID_REPORT_KEYBOARD_RESERVED, \
HID_REPORT_KEYBOARD_KEYS, \
HID_REPORT_KEYBOARD_END

#define HID_REPORT_KEYBOARD_SIZE sizeof ((uint8_t[]) {HID_REPORT_KEYBOARD})
#define HID_MULTIREPORT_KEYBOARD_SIZE sizeof ((uint8_t[]) {HID_MULTIREPORT_KEYBOARD})

extern const uint8_t _hidReportDescriptorKeyboard[HID_REPORT_KEYBOARD_SIZE] PROGMEM;
extern const uint8_t _hidMultiReportDescriptorKeyboard[HID_MULTIREPORT_KEYBOARD_SIZE] PROGMEM;


typedef union{
	// Low level key report: up to 6 keys and shift, ctrl etc at once
	uint8_t whole8[];
	uint16_t whole16[];
	uint32_t whole32[];
	struct{
		uint8_t modifiers;
		uint8_t reserved;
		uint8_t keys[6];
	};
} HID_KeyboardReport_Data_t;

class TeensyKeyboardAPI : public Print
{
	public:
	TeensyKeyboardAPI(void) { }

	void begin(void) { }
	void end(void) { }
	virtual size_t write(uint8_t);
	using Print::write;
	inline void write_unicode(uint16_t unicode) { write_keycode(unicode_to_keycode(unicode)); }
	void set_modifier(uint8_t);
	void set_key1(uint8_t);
	void set_key2(uint8_t);
	void set_key3(uint8_t);
	void set_key4(uint8_t);
	void set_key5(uint8_t);
	void set_key6(uint8_t);
	void set_media(uint8_t);
	void send_now(void);
	void press(uint16_t n);
	void release(uint16_t n);
	void releaseAll(void);
	
	// Sending is public in the base class for advanced users.
    virtual void sendReport(void* data, int length) = 0;
	
private:
	KEYCODE_TYPE unicode_to_keycode(uint16_t unicode);
	KEYCODE_TYPE deadkey_to_keycode(KEYCODE_TYPE keycode);
	uint8_t keycode_to_modifier(KEYCODE_TYPE keycode);
	uint8_t keycode_to_key(KEYCODE_TYPE keycode);
	void presskey(uint8_t key, uint8_t modifier);
	void releasekey(uint8_t key, uint8_t modifier);
	void write_keycode(KEYCODE_TYPE key);
	void write_key(KEYCODE_TYPE code);
	uint8_t utf8_state;
	uint16_t unicode_wchar;
	uint8_t keyboard_report_data[8];
};

