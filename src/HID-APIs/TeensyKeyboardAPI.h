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

// Keyboard Protocol 1, HID 1.11 spec, Appendix B, page 59-60
static const uint8_t PROGMEM teensykeyboard_hid_report_desc[] = {
        0x05, 0x01,             //  Usage Page (Generic Desktop),
        0x09, 0x06,             //  Usage (Keyboard),
        0xA1, 0x01,             //  Collection (Application),
        0x85, HID_REPORTID_TEENSY_KEYBOARD,   //   REPORT_ID
        0x75, 0x01,             //  Report Size (1),
        0x95, 0x08,             //  Report Count (8),
        0x05, 0x07,             //  Usage Page (Key Codes),
        0x19, 0xE0,             //  Usage Minimum (224),
        0x29, 0xE7,             //  Usage Maximum (231),
        0x15, 0x00,             //  Logical Minimum (0),
        0x25, 0x01,             //  Logical Maximum (1),
        0x81, 0x02,             //  Input (Data, Variable, Absolute), ;Modifier byte
        0x95, 0x08,             //  Report Count (8),
        0x75, 0x01,             //  Report Size (1),
        0x15, 0x00,		//  Logical Minimum (0),
        0x25, 0x01,             //  Logical Maximum (1),
        0x05, 0x0C,             //  Usage Page (Consumer),
	0x09, 0xE9,		//  Usage (Volume Increment),
	0x09, 0xEA,		//  Usage (Volume Decrement),
	0x09, 0xE2,		//  Usage (Mute),
	0x09, 0xCD,		//  Usage (Play/Pause),
	0x09, 0xB5,		//  Usage (Scan Next Track),
	0x09, 0xB6,		//  Usage (Scan Previous Track),
	0x09, 0xB7,		//  Usage (Stop),
	0x09, 0xB8,		//  Usage (Eject),
        0x81, 0x02,             //  Input (Data, Variable, Absolute), ;Media keys
        
        // Note: Teensy ledreport was not modified to 8 bit, nor left out when leds are deactivated
        0x95, 0x05,             //  Report Count (5),
        0x75, 0x01,             //  Report Size (1),
        0x05, 0x08,             //  Usage Page (LEDs),
        0x19, 0x01,             //  Usage Minimum (1),
        0x29, 0x05,             //  Usage Maximum (5),
        0x91, 0x02,             //  Output (Data, Variable, Absolute), ;LED report
        0x95, 0x01,             //  Report Count (1),
        0x75, 0x03,             //  Report Size (3),
        0x91, 0x03,             //  Output (Constant),                 ;LED report padding
        0x95, 0x06,             //  Report Count (6),
        0x75, 0x08,             //  Report Size (8),
        0x15, 0x00,             //  Logical Minimum (0),
        0x25, 0x7F,             //  Logical Maximum(104),
        0x05, 0x07,             //  Usage Page (Key Codes),
        0x19, 0x00,             //  Usage Minimum (0),
        0x29, 0x7F,             //  Usage Maximum (104),
        0x81, 0x00,             //  Input (Data, Array),		;Normal keys
        0xc0			// End Collection
};

typedef union ATTRIBUTE_PACKED {
	// Low level key report: up to 6 keys and shift, ctrl etc at once
	uint8_t whole8[];
	uint16_t whole16[];
	uint32_t whole32[];
	struct ATTRIBUTE_PACKED {
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

// Implementation is inline
#include "TeensyKeyboardAPI.hpp"
