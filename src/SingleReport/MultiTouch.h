/*
Copyright (c) 2021 ilufang
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
#include "HID.h"
#include "HID-Settings.h"
#include "../HID-APIs/MultiTouchAPI.h"


class MultiTouch_ : public PluggableUSBModule, public MultiTouchAPI
{
public:
	MultiTouch_();
	uint8_t getProtocol();
	void wakeupHost();

	virtual int sendReport(void *report, int length) final;
	virtual int sendReport(HID_MultiTouchReport_Data_t &report) final;

protected:

	// Implementation of the PUSBListNode
	int getInterface(uint8_t* interfaceCount);
	int getDescriptor(USBSetup& setup);
	bool setup(USBSetup& setup);

	EPTYPE_DESCRIPTOR_SIZE epType[1];
	uint8_t protocol;
	uint8_t idle;

	struct ATTRIBUTE_PACKED {
		uint8_t contactCountMaximum;
	} _ccmFeature;
};

extern MultiTouch_ MultiTouch;
