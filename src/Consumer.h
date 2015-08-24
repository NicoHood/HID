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

#pragma once

#include "HID.h"

#if !defined(_USING_HID)

#error "This is not an USB AVR or you use an old version of the IDE."

#else

//================================================================================
// Consumer
//================================================================================

#ifndef HID_REPORTID_CONSUMERCONTROL
#define HID_REPORTID_CONSUMERCONTROL 4
#endif

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

#define CONSUMER_EMAIL_READER	0x18A
#define CONSUMER_CALCULATOR	0x192
#define CONSUMER_EXPLORER	0x194

#define CONSUMER_BROWSER_HOME	0x223
#define CONSUMER_BROWSER_BACK	0x224
#define CONSUMER_BROWSER_FORWARD	0x225
#define CONSUMER_BROWSER_REFRESH	0x227
#define CONSUMER_BROWSER_BOOKMARKS	0x22A

static const uint8_t _consumerReportDescriptor[] PROGMEM = {
	/* Consumer Control (Sound/Media keys) */
	0x05, 0x0C,									/* usage page (consumer device) */
	0x09, 0x01, 								/* usage -- consumer control */
	0xA1, 0x01, 								/* collection (application) */
	0x85, HID_REPORTID_CONSUMERCONTROL, 		/* report id */
	/* 4 Media Keys */
	0x15, 0x00, 								/* logical minimum */
	0x26, 0xFF, 0x03, 							/* logical maximum (3ff) */
	0x19, 0x00, 								/* usage minimum (0) */
	0x2A, 0xFF, 0x03, 							/* usage maximum (3ff) */
	0x95, 0x04, 								/* report count (4) */
	0x75, 0x10, 								/* report size (16) */
	0x81, 0x00, 								/* input */
	0xC0 /* end collection */
};

typedef union {
	// every usable Consumer key possible, up to 4 keys presses possible
	uint8_t whole8[];
	uint16_t whole16[];
	uint32_t whole32[];
	struct {
		uint16_t key1;
		uint16_t key2;
		uint16_t key3;
		uint16_t key4;
	};
} HID_ConsumerControlReport_Data_t;

extern HID_ HID;

class Consumer_ {
public:
	inline Consumer_(void) {
		static HID_Descriptor cb = {
			.length = sizeof(_consumerReportDescriptor),
			.descriptor = _consumerReportDescriptor,
		};
		static HIDDescriptorListNode node(&cb);
		HID.AppendDescriptor(&node);
	}

	inline void begin(void) {
		// release all buttons
		end();
	}

	inline void end(void) {
		memset(&_report, 0, sizeof(_report));
		HID.SendReport(HID_REPORTID_CONSUMERCONTROL, &_report, sizeof(_report));
	}

	inline void write(uint16_t m) {
		press(m);
		release(m);
	}

	inline void press(uint16_t m) {
		// search for a free spot
		for (int i = 0; i < sizeof(HID_ConsumerControlReport_Data_t) / 2; i++) {
			if (_report.whole16[i] == 0x00) {
				_report.whole16[i] = m;
				break;
			}
		}
		HID.SendReport(HID_REPORTID_CONSUMERCONTROL, &_report, sizeof(_report));
	}

	inline void release(uint16_t m) {
		// search and release the keypress
		for (int i = 0; i < sizeof(HID_ConsumerControlReport_Data_t) / 2; i++) {
			if (_report.whole16[i] == m) {
				_report.whole16[i] = 0x00;
				// no break to delete multiple keys
			}
		}
		HID.SendReport(HID_REPORTID_CONSUMERCONTROL, &_report, sizeof(_report));
	}

	inline void releaseAll(void) {
		end();
	}

private:
	HID_ConsumerControlReport_Data_t _report;
};
extern Consumer_ Consumer;

#endif
