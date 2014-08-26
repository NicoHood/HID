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


#ifndef MEDIA_H
#define MEDIA_H

#include "HID.h"

//================================================================================
// HID
//================================================================================

void HID_SendReport(uint8_t id, const void* data, int len);

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
	inline Media_(void){
		// empty
	}

	inline void begin(void){
		memset(&_report, 0, sizeof(_report));
		HID_SendReport(HID_REPORTID_MediaReport, &_report, sizeof(_report));
	}

	inline void end(void){
		begin();
	}

	inline void write(uint16_t m){
		press(m);
		release(m);
	}

	inline void press(uint16_t m){
		// search for a free spot
		for (int i = 0; i < sizeof(HID_MediaReport_Data_t) / 2; i++) {
			if (_report.whole16[i] == 0x00) {
				_report.whole16[i] = m;
				break;
			}
		}
		HID_SendReport(HID_REPORTID_MediaReport, &_report, sizeof(_report));
	}

	inline void release(uint16_t m){
		// search and release the keypress
		for (int i = 0; i < sizeof(HID_MediaReport_Data_t) / 2; i++) {
			if (_report.whole16[i] == m) {
				_report.whole16[i] = 0x00;
				// no break to delete multiple keys
			}
		}
		HID_SendReport(HID_REPORTID_MediaReport, &_report, sizeof(_report));
	}

	inline void releaseAll(void){
		begin();
	}
private:
	HID_MediaReport_Data_t _report;
};
extern Media_ Media;

#endif

