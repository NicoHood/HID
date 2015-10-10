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

static const uint8_t _hidReportDescriptorMouse[] PROGMEM = {
 /*  Mouse relative */
    0x05, 0x01,                      /* USAGE_PAGE (Generic Desktop)	  54 */
    0x09, 0x02,                      /* USAGE (Mouse) */
    0xa1, 0x01,                      /* COLLECTION (Application) */

	/* 8 Buttons */
    0x05, 0x09,                      /*     USAGE_PAGE (Button) */
    0x19, 0x01,                      /*     USAGE_MINIMUM (Button 1) */
    0x29, 0x08,                      /*     USAGE_MAXIMUM (Button 8) */
    0x15, 0x00,                      /*     LOGICAL_MINIMUM (0) */
    0x25, 0x01,                      /*     LOGICAL_MAXIMUM (1) */
    0x95, 0x08,                      /*     REPORT_COUNT (8) */
    0x75, 0x01,                      /*     REPORT_SIZE (1) */
    0x81, 0x02,                      /*     INPUT (Data,Var,Abs) */

	/* X, Y, Wheel */
    0x05, 0x01,                      /*     USAGE_PAGE (Generic Desktop) */
    0x09, 0x30,                      /*     USAGE (X) */
    0x09, 0x31,                      /*     USAGE (Y) */
    0x09, 0x38,                      /*     USAGE (Wheel) */
    0x15, 0x81,                      /*     LOGICAL_MINIMUM (-127) */
    0x25, 0x7f,                      /*     LOGICAL_MAXIMUM (127) */
    0x75, 0x08,                      /*     REPORT_SIZE (8) */
    0x95, 0x03,                      /*     REPORT_COUNT (3) */
    0x81, 0x06,                      /*     INPUT (Data,Var,Rel) */

	/* End */
    0xc0                            /* END_COLLECTION */
};

static const uint8_t _hidMultiReportDescriptorMouse[] PROGMEM = {
 /*  Mouse relative */
    0x05, 0x01,                      /* USAGE_PAGE (Generic Desktop)	  54 */
    0x09, 0x02,                      /* USAGE (Mouse) */
    0xa1, 0x01,                      /* COLLECTION (Application) */
    0x85, HID_REPORTID_MOUSE,				/*     REPORT_ID */

	/* 8 Buttons */
    0x05, 0x09,                      /*     USAGE_PAGE (Button) */
    0x19, 0x01,                      /*     USAGE_MINIMUM (Button 1) */
    0x29, 0x08,                      /*     USAGE_MAXIMUM (Button 8) */
    0x15, 0x00,                      /*     LOGICAL_MINIMUM (0) */
    0x25, 0x01,                      /*     LOGICAL_MAXIMUM (1) */
    0x95, 0x08,                      /*     REPORT_COUNT (8) */
    0x75, 0x01,                      /*     REPORT_SIZE (1) */
    0x81, 0x02,                      /*     INPUT (Data,Var,Abs) */

	/* X, Y, Wheel */
    0x05, 0x01,                      /*     USAGE_PAGE (Generic Desktop) */
    0x09, 0x30,                      /*     USAGE (X) */
    0x09, 0x31,                      /*     USAGE (Y) */
    0x09, 0x38,                      /*     USAGE (Wheel) */
    0x15, 0x81,                      /*     LOGICAL_MINIMUM (-127) */
    0x25, 0x7f,                      /*     LOGICAL_MAXIMUM (127) */
    0x75, 0x08,                      /*     REPORT_SIZE (8) */
    0x95, 0x03,                      /*     REPORT_COUNT (3) */
    0x81, 0x06,                      /*     INPUT (Data,Var,Rel) */

	/* End */
    0xc0                            /* END_COLLECTION */
};

#define MOUSE_LEFT		(1 << 0)
#define MOUSE_RIGHT		(1 << 1)
#define MOUSE_MIDDLE	(1 << 2)
#define MOUSE_PREV		(1 << 3)
#define MOUSE_NEXT		(1 << 4)
// actually this mouse report has 8 buttons (for smaller descriptor)
// but the last 3 wont do anything from what I tested
#define MOUSE_ALL (MOUSE_LEFT | MOUSE_RIGHT | MOUSE_MIDDLE | MOUSE_PREV | MOUSE_NEXT)

typedef union{
	// Mouse report: 8 buttons, position, wheel
	uint8_t whole8[];
	uint16_t whole16[];
	uint32_t whole32[];
	struct{
		uint8_t buttons;
		int8_t xAxis;
		int8_t yAxis;
		int8_t wheel;
	};
} HID_MouseReport_Data_t;

typedef union{
	// BootMouse report: 3 buttons, position
	// Wheel is not supported by boot protocol
	uint8_t whole8[];
	uint16_t whole16[];
	uint32_t whole32[];
	struct{
		uint8_t buttons;
		int8_t xAxis;
		int8_t yAxis;
	};
} HID_BootMouseReport_Data_t;

class MouseAPI
{
public:
  MouseAPI(void);
  void begin(void);
  void end(void);
  void click(uint8_t b = MOUSE_LEFT);
  void move(signed char x, signed char y, signed char wheel = 0); 
  void press(uint8_t b = MOUSE_LEFT);   // press LEFT by default
  void release(uint8_t b = MOUSE_LEFT); // release LEFT by default
  bool isPressed(uint8_t b = MOUSE_LEFT); // check LEFT by default
  
  // Sending is public in the base class for advanced users.
  virtual void sendReport(void* data, int length) = 0;
  
private:
  uint8_t _buttons;
  void buttons(uint8_t b);
};


