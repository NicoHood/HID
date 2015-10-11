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

// Media key definitions, see official USB docs for more
#define MEDIA_FAST_FORWARD	0xB3
#define MEDIA_REWIND	0xB4
#define MEDIA_NEXT	0xB5
#define MEDIA_PREVIOUS	0xB6
#define MEDIA_PREV	MEDIA_PREVIOUS
#define MEDIA_STOP	0xB7
#define MEDIA_PLAY_PAUSE	0xCD

#define MEDIA_VOLUME_MUTE	0xE2
#define MEDIA_VOLUME_UP	0xE9
#define MEDIA_VOLUME_DOWN	0xEA
#define MEDIA_VOL_MUTE MEDIA_VOLUME_MUTE
#define MEDIA_VOL_UP MEDIA_VOLUME_UP
#define MEDIA_VOL_DOWN MEDIA_VOLUME_DOWN

#define CONSUMER_SCREENSAVER 0x19e

#define CONSUMER_PROGRAMMABLE_BUTTON_CONFIGURATION 0x182
#define CONSUMER_CONTROL_CONFIGURATION 0x183
#define CONSUMER_EMAIL_READER	0x18A
#define CONSUMER_CALCULATOR	0x192
#define CONSUMER_EXPLORER	0x194

#define CONSUMER_BROWSER_HOME	0x223
#define CONSUMER_BROWSER_BACK	0x224
#define CONSUMER_BROWSER_FORWARD	0x225
#define CONSUMER_BROWSER_REFRESH	0x227
#define CONSUMER_BROWSER_BOOKMARKS	0x22A


typedef union {
	// Every usable Consumer key possible, up to 4 keys presses possible
	uint8_t whole8[];
	uint16_t whole16[];
	uint32_t whole32[];
	uint16_t keys[4];
	struct {
		uint16_t key1;
		uint16_t key2;
		uint16_t key3;
		uint16_t key4;
	};
} HID_ConsumerControlReport_Data_t;

class ConsumerAPI
{
public:
	inline ConsumerAPI(void);
	inline void begin(void);
	inline void end(void);
	inline void write(uint16_t m);
	inline void press(uint16_t m);
	inline void release(uint16_t m);
	inline void releaseAll(void);
	
	// Sending is public in the base class for advanced users.
	virtual void SendReport(void* data, int length) = 0;

protected:
	HID_ConsumerControlReport_Data_t _report;
};

// Implementation is inline
#include "ConsumerAPI.hpp"

