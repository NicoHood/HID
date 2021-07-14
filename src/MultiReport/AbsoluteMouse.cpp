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

#include "AbsoluteMouse.h"


static const uint8_t _hidMultiReportDescriptorAbsoluteMouse[] PROGMEM = {
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
	0x16, 0x00, 0x00,				 /* 	Logical Minimum (0); NOTE: Windows 7 can't handle negative value */
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

AbsoluteMouse_::AbsoluteMouse_(void) 
{
	static HIDSubDescriptor node(_hidMultiReportDescriptorAbsoluteMouse, sizeof(_hidMultiReportDescriptorAbsoluteMouse));
	HID().AppendDescriptor(&node);
}


void AbsoluteMouse_::SendReport(void* data, int length)
{
	HID().SendReport(HID_REPORTID_MOUSE_ABSOLUTE, data, length);
}

AbsoluteMouse_ AbsoluteMouse;

