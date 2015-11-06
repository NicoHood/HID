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

#include "System.h"


static const uint8_t _hidMultiReportDescriptorSystem[] PROGMEM = {
	//TODO limit to system keys only?
	/*  System Control (Power Down, Sleep, Wakeup, ...) */
	0x05, 0x01,								/* USAGE_PAGE (Generic Desktop) */
	0x09, 0x80,								/* USAGE (System Control) */
	0xa1, 0x01, 							/* COLLECTION (Application) */
	0x85, HID_REPORTID_SYSTEMCONTROL,		/* REPORT_ID */
	/* 1 system key */
	0x15, 0x00, 							/* LOGICAL_MINIMUM (0) */
	0x26, 0xff, 0x00, 						/* LOGICAL_MAXIMUM (255) */
	0x19, 0x00, 							/* USAGE_MINIMUM (Undefined) */
	0x29, 0xff, 							/* USAGE_MAXIMUM (System Menu Down) */
	0x95, 0x01, 							/* REPORT_COUNT (1) */
	0x75, 0x08, 							/* REPORT_SIZE (8) */
	0x81, 0x00, 							/* INPUT (Data,Ary,Abs) */
	0xc0 									/* END_COLLECTION */
};

System_::System_(void) 
{
	static HIDSubDescriptor node(_hidMultiReportDescriptorSystem, sizeof(_hidMultiReportDescriptorSystem));
	HID().AppendDescriptor(&node);
}


void System_::SendReport(void* data, int length)
{
	HID().SendReport(HID_REPORTID_SYSTEMCONTROL, data, length);
}

System_ System;

