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
//================================================================================
//	Mouse

#ifndef HID_REPORTID_MOUSE_ABSOLUTE
#define HID_REPORTID_MOUSE_ABSOLUTE 7
#endif

#define MOUSE_LEFT		(1 << 0)
#define MOUSE_RIGHT		(1 << 1)
#define MOUSE_MIDDLE	(1 << 2)
#define MOUSE_PREV		(1 << 3)
#define MOUSE_NEXT		(1 << 4)
// actually this mouse report has 8 buttons (for smaller descriptor)
// but the last 3 wont do anything from what I tested
#define MOUSE_ALL (MOUSE_LEFT | MOUSE_RIGHT | MOUSE_MIDDLE | MOUSE_PREV | MOUSE_NEXT)

static const uint8_t _absmouseReportDescriptor[] PROGMEM = {
	/*  Mouse absolute */
    0x05, 0x01,                      /* USAGE_PAGE (Generic Desktop)	  54 */
    0x09, 0x02,                      /* USAGE (Mouse) */
    0xA1, 0x01,                      /* COLLECTION (Application) */
    0x85, HID_REPORTID_MOUSE_ABSOLUTE,	/*     REPORT_ID */

	/* 8 Buttons */
    0x05, 0x09,                      /*     USAGE_PAGE (Button) */
    0x19, 0x01,                      /*     USAGE_MINIMUM (Button 1) */
    0x29, 0x08,                      /*     USAGE_MAXIMUM (Button 8) */
    0x15, 0x00,                      /*     LOGICAL_MINIMUM (0) */
    0x25, 0x01,                      /*     LOGICAL_MAXIMUM (1) */
    0x95, 0x08,                      /*     REPORT_COUNT (8) */
    0x75, 0x01,                      /*     REPORT_SIZE (1) */
    0x81, 0x02,                      /*     INPUT (Data,Var,Abs) */

	/* X, Y */
    0x05, 0x01,                      /*     USAGE_PAGE (Generic Desktop) */
    0x09, 0x30,                      /*     USAGE (X) */
    0x09, 0x31,                      /*     USAGE (Y) */
	0x16, 0x00, 0x80,				 /* 	Logical Minimum (-32768) */
	0x26, 0xFF, 0x7F,				 /* 	Logical Maximum (32767) */
	0x75, 0x10,						 /* 	Report Size (16), */
	0x95, 0x02,						 /* 	Report Count (2), */
	0x81, 0x02,						 /* 	Input (Data, Variable, Absolute) */

	/* Wheel */
    0x09, 0x38,                      /*     USAGE (Wheel) */
    0x15, 0x81,                      /*     LOGICAL_MINIMUM (-127) */
    0x25, 0x7f,                      /*     LOGICAL_MAXIMUM (127) */
    0x75, 0x08,                      /*     REPORT_SIZE (8) */
    0x95, 0x01,                      /*     REPORT_COUNT (1) */
    0x81, 0x06,                      /*     INPUT (Data,Var,Rel) */

	/* End */
    0xc0                            /* END_COLLECTION */ 
};

typedef union{
	// mouse absolute report: 8 buttons, 2 absolute axis, wheel
	uint8_t whole8[];
	uint16_t whole16[];
	uint32_t whole32[];
	struct{
		uint8_t buttons;
		int16_t xAxis;
		int16_t yAxis;
		int8_t wheel;
	};
} HID_MouseAbsoluteReport_Data_t;

extern HID_ HID;

class AbsMouse_
{
private:
	int16_t xAxis = 0;
	int16_t yAxis = 0;
	uint8_t _buttons = 0;
	inline void buttons(uint8_t b){
		if (b != _buttons){
			_buttons = b;
			moveTo(xAxis, yAxis, 0);
		}
	}

	inline int16_t qadd16(int16_t base, int16_t increment) {
  		// Separate between subtracting and adding  
  		if (increment < 0) {
    		// Subtracting more would cause an undefined overflow
   	 		if ((int16_t)0x8000 - increment > base)
      			base = 0x8000;
    		else
      			base += increment;
  		}
  		else {
    		// Adding more would cause an undefined overflow
    		if ((int16_t)0x7FFF - increment < base)
      			base = 0x7FFF;
    		else
      			base += increment;
  		}
  		return base;
	}

public:
	inline AbsMouse_(void) {
		static HID_Descriptor cb = {
			.length = sizeof(_absmouseReportDescriptor),
			.descriptor = _absmouseReportDescriptor,
		};
		static HIDDescriptorListNode node(&cb);
		HID.AppendDescriptor(&node);
	}

	inline void begin(void){
		// release all buttons
		end();
	}

	inline void end(void){
		_buttons = 0;
		moveTo(xAxis, yAxis, 0);
	}

	inline void click(uint8_t b = MOUSE_LEFT){
		_buttons = b;
		moveTo(xAxis, yAxis, 0);
		_buttons = 0;
		moveTo(xAxis, yAxis, 0);
	}

	inline void moveTo(int x, int y, signed char wheel = 0){
		xAxis = x;
		yAxis = y;
		HID_MouseAbsoluteReport_Data_t report;
		report.buttons = _buttons;
		report.xAxis = x;
		report.yAxis = y;
		report.wheel = wheel;
		HID.SendReport(HID_REPORTID_MOUSE_ABSOLUTE, &report, sizeof(report));
	}

	inline void move(int x, int y, signed char wheel = 0){
		moveTo(qadd16(xAxis, x), qadd16(yAxis, y), wheel);
	}

	inline void press(uint8_t b = MOUSE_LEFT){
		// press LEFT by default
		buttons(_buttons | b);
	}

	inline void release(uint8_t b = MOUSE_LEFT){
		// release LEFT by default
		buttons(_buttons & ~b);
	}

	inline bool isPressed(uint8_t b = MOUSE_LEFT){
		// check LEFT by default
		if ((b & _buttons) > 0)
			return true;
		return false;
	}
};
extern AbsMouse_ AbsoluteMouse;

#endif
