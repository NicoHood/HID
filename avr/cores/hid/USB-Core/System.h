/*
System.h
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

#ifndef __SYSTEMAPI__
#define __SYSTEMAPI__

// to access the HID_SendReport via USBAPI.h and report number
#include "Arduino.h"

//TODO workaround to access the weak sending function
void HID_SendReport(uint8_t id, const void* data, int len);

//================================================================================
// System
//================================================================================

#define SYSTEM_POWER_DOWN	0x81
#define SYSTEM_SLEEP	0x82
#define SYSTEM_WAKE_UP	0x83

typedef union{
	// every usable system control key possible
	uint8_t whole8[1];
	uint8_t key;
} HID_SystemReport_Data_t;

class System_{
public:
	inline System_(void){
		// empty
	}
	inline void begin(void){
		// release all buttons
		end();
	}
	inline void end(void){
		uint8_t _report = 0;
		HID_SendReport(HID_REPORTID_SYSTEMCONTROL, &_report, sizeof(_report));
	}
	inline void write(uint8_t s){
		press(s);
		release();
	}
	inline void press(uint8_t s){
		HID_SendReport(HID_REPORTID_SYSTEMCONTROL, &s, sizeof(s));
	}
	inline void release(void){
		begin();
	}
	inline void releaseAll(void){
		begin();
	}
};
extern System_ System;

#endif