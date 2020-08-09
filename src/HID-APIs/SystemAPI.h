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

enum SystemKeycode : uint8_t {
	SYSTEM_POWER_DOWN	= 0x81,
	SYSTEM_SLEEP	= 0x82,
	SYSTEM_WAKE_UP	= 0x83,

	// System control mappings
	HID_SYSTEM_UNASSIGNED		= 0x00,
	HID_SYSTEM_POWER_DOWN	= 0x81,	// HID type OSC
	HID_SYSTEM_SLEEP	= 0x82,	// HID type OSC
	HID_SYSTEM_WAKE_UP	= 0x83,	// HID type OSC
	HID_SYSTEM_CONTEXT_MENU	= 0x84,	// HID type OSC
	HID_SYSTEM_MAIN_MENU	= 0x85,	// HID type OSC
	HID_SYSTEM_APP_MENU	= 0x86,	// HID type OSC
	HID_SYSTEM_MENU_HELP	= 0x87,	// HID type OSC
	HID_SYSTEM_MENU_EXIT	= 0x88,	// HID type OSC
	HID_SYSTEM_MENU_SELECT	= 0x89,	// HID type OSC
	HID_SYSTEM_MENU_RIGHT	= 0x8A,	// HID type RTC
	HID_SYSTEM_MENU_LEFT	= 0x8B,	// HID type RTC
	HID_SYSTEM_MENU_UP	= 0x8C,	// HID type RTC
	HID_SYSTEM_MENU_DOWN	= 0x8D,	// HID type RTC
	HID_SYSTEM_COLD_RESTART	= 0x8E,	// HID type OSC
	HID_SYSTEM_WARM_RESTART	= 0x8F,	// HID type OSC
	HID_D_PAD_UP	= 0x90,	// HID type OOC
	HID_D_PAD_DOWN	= 0x91,	// HID type OOC
	HID_D_PAD_RIGHT	= 0x92,	// HID type OOC
	HID_D_PAD_LEFT	= 0x93,	// HID type OOC
	// 0x94-0x9F are reserved
	HID_SYSTEM_DOCK	= 0xA0,	// HID type OSC
	HID_SYSTEM_UNDOCK	= 0xA1,	// HID type OSC
	HID_SYSTEM_SETUP	= 0xA2,	// HID type OSC
	HID_SYSTEM_BREAK	= 0xA3,	// HID type OSC
	HID_SYSTEM_DEBUGGER_BREAK	= 0xA4,	// HID type OSC
	HID_APPLICATION_BREAK	= 0xA5,	// HID type OSC
	HID_APPLICATION_DEBUGGER_BREAK	= 0xA6,	// HID type OSC
	HID_SYSTEM_SPEAKER_MUTE	= 0xA7,	// HID type OSC
	HID_SYSTEM_HIBERNATE	= 0xA8,	// HID type OSC
	// 0xA9-0xAF are reserved
	HID_SYSTEM_DISPLAY_INVERT	= 0xB0,	// HID type OSC
	HID_SYSTEM_DISPLAY_INTERNAL	= 0xB1,	// HID type OSC
	HID_SYSTEM_DISPLAY_EXTERNAL	= 0xB2,	// HID type OSC
	HID_SYSTEM_DISPLAY_BOTH	= 0xB3,	// HID type OSC
	HID_SYSTEM_DISPLAY_DUAL	= 0xB4,	// HID type OSC
	HID_SYSTEM_DISPLAY_TOGGLE_INT_SLASH_EXT	= 0xB5,	// HID type OSC
	HID_SYSTEM_DISPLAY_SWAP_PRIMARY_SLASH_SECONDARY	= 0xB6,	// HID type OSC
	HID_SYSTEM_DISPLAY_LCD_AUTOSCALE	= 0xB7,	// HID type OSC
};

typedef union ATTRIBUTE_PACKED {
	// Every usable system control key possible
	uint8_t whole8[0];
	uint8_t key;
} HID_SystemControlReport_Data_t;

class SystemAPI{
public:
	inline SystemAPI(void);
	inline void begin(void);
	inline void end(void);
	inline void write(SystemKeycode s);
	inline void press(SystemKeycode s);
	inline void release(void);
	inline void releaseAll(void);

	// Sending is public in the base class for advanced users.
	virtual void SendReport(void* data, int length) = 0;
};

// Implementation is inline
#include "SystemAPI.hpp"
