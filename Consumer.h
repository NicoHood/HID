/*
Consumer.h
Copyright (c) 2005-2014 Arduino.  All right reserved.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef __CONSUMERAPI__
#define __CONSUMERAPI__

// to access the HID_SendReport via USBAPI.h and report number
#include "Arduino.h"

//TODO workaround to access the weak sending function
void HID_SendReport(uint8_t id, const void* data, int len);

//================================================================================
// Consumer
//================================================================================

// Media key definitions, see official USB docs for more
#define MEDIA_FAST_FORWARD	0xB3
#define MEDIA_REWIND	0xB4
#define MEDIA_NEXT	0xB5
#define MEDIA_PREVIOUS	0xB6
#define MEDIA_STOP	0xB7
#define MEDIA_PLAY_PAUSE	0xCD

#define MEDIA_VOLUME_MUTE	0xE2
#define MEDIA_VOLUME_UP	0xE9
#define MEDIA_VOLUME_DOWN	0xEA

#define CONSUMER_EMAIL_READER	0x18A
#define CONSUMER_CALCULATOR	0x192
#define CONSUMER_EXPLORER	0x194

#define CONSUMER_BROWSER_HOME	0x223
#define CONSUMER_BROWSER_BACK	0x224
#define CONSUMER_BROWSER_FORWARD	0x225
#define CONSUMER_BROWSER_REFRESH	0x227
#define CONSUMER_BROWSER_BOOKMARKS	0x22A

typedef union{
	// every usable Consumer key possible, up to 4 keys presses possible
	uint8_t whole8[8];
	uint16_t whole16[8 / 2];
	uint32_t whole32[8 / 4];
	struct{
		uint16_t key1;
		uint16_t key2;
		uint16_t key3;
		uint16_t key4;
	};
} HID_ConsumerReport_Data_t;

class Consumer_{
public:
	inline Consumer_(void){
		// empty
	}
	inline void begin(void){
		// release all buttons
		end();
	}
	inline void end(void){
		memset(&_report, 0, sizeof(_report));
		HID_SendReport(HID_REPORTID_CONSUMERCONTROL, &_report, sizeof(_report));
	}
	inline void write(uint16_t m){
		press(m);
		release(m);
	}
	inline void press(uint16_t m){
		// search for a free spot
		for (int i = 0; i < sizeof(HID_ConsumerReport_Data_t) / 2; i++) {
			if (_report.whole16[i] == 0x00) {
				_report.whole16[i] = m;
				break;
			}
		}
		HID_SendReport(HID_REPORTID_CONSUMERCONTROL, &_report, sizeof(_report));
	}
	inline void release(uint16_t m){
		// search and release the keypress
		for (int i = 0; i < sizeof(HID_ConsumerReport_Data_t) / 2; i++) {
			if (_report.whole16[i] == m) {
				_report.whole16[i] = 0x00;
				// no break to delete multiple keys
			}
		}
		HID_SendReport(HID_REPORTID_CONSUMERCONTROL, &_report, sizeof(_report));
	}
	inline void releaseAll(void){
		begin();
	}
private:
	HID_ConsumerReport_Data_t _report;
};
extern Consumer_ Consumer;

#endif