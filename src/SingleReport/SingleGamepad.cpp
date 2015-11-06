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

#include "SingleGamepad.h"

static const uint8_t _hidReportDescriptorGamepad[] PROGMEM = {
	/* Gamepad with 32 buttons and 6 axis*/
	0x05, 0x01,							/* USAGE_PAGE (Generic Desktop) */
	0x09, 0x04,							/* USAGE (Joystick) */
	0xa1, 0x01,							/* COLLECTION (Application) */
	/* 32 Buttons */
	0x05, 0x09,							/*   USAGE_PAGE (Button) */
	0x19, 0x01,							/*   USAGE_MINIMUM (Button 1) */
	0x29, 0x20,							/*   USAGE_MAXIMUM (Button 32) */
	0x15, 0x00,							/*   LOGICAL_MINIMUM (0) */
	0x25, 0x01,							/*   LOGICAL_MAXIMUM (1) */
	0x75, 0x01,							/*   REPORT_SIZE (1) */
	0x95, 0x20,							/*   REPORT_COUNT (32) */
	0x81, 0x02,							/*   INPUT (Data,Var,Abs) */
	/* 4 16bit Axis */
	0x05, 0x01,							/*   USAGE_PAGE (Generic Desktop) */
	0xa1, 0x00,							/*   COLLECTION (Physical) */
	0x09, 0x30,							/*     USAGE (X) */
	0x09, 0x31,							/*     USAGE (Y) */
	0x09, 0x33,							/*     USAGE (Rx) */
	0x09, 0x34,							/*     USAGE (Ry) */
	0x16, 0x00, 0x80,					/*     LOGICAL_MINIMUM (-32768) */
	0x26, 0xFF, 0x7F,					/*     LOGICAL_MAXIMUM (32767) */
	0x75, 0x10,							/*     REPORT_SIZE (16) */
	0x95, 0x04,							/*     REPORT_COUNT (4) */
	0x81, 0x02,							/*     INPUT (Data,Var,Abs) */
	/* 2 8bit Axis */
	0x09, 0x32,							/*     USAGE (Z) */
	0x09, 0x35,							/*     USAGE (Rz) */
	0x15, 0x80,							/*     LOGICAL_MINIMUM (-128) */
	0x25, 0x7F,							/*     LOGICAL_MAXIMUM (127) */
	0x75, 0x08,							/*     REPORT_SIZE (8) */
	0x95, 0x02,							/*     REPORT_COUNT (2) */
	0x81, 0x02,							/*     INPUT (Data,Var,Abs) */
	0xc0,								/*   END_COLLECTION */
	/* 2 Hat Switches */
	0x05, 0x01,							/*   USAGE_PAGE (Generic Desktop) */
	0x09, 0x39,							/*   USAGE (Hat switch) */
	0x09, 0x39,							/*   USAGE (Hat switch) */
	0x15, 0x01,							/*   LOGICAL_MINIMUM (1) */
	0x25, 0x08,							/*   LOGICAL_MAXIMUM (8) */
	0x95, 0x02,							/*   REPORT_COUNT (2) */
	0x75, 0x04,							/*   REPORT_SIZE (4) */
	0x81, 0x02,							/*   INPUT (Data,Var,Abs) */
	0xc0								/* END_COLLECTION */
};

SingleGamepad_::SingleGamepad_(void) : PluggableUSBModule(1, 1, epType), protocol(HID_REPORT_PROTOCOL), idle(1)
{
	epType[0] = EP_TYPE_INTERRUPT_IN;
	PluggableUSB().plug(this);
}

int SingleGamepad_::getInterface(uint8_t* interfaceCount)
{
	*interfaceCount += 1; // uses 1
	HIDDescriptor hidInterface = {
		D_INTERFACE(pluggedInterface, 1, USB_DEVICE_CLASS_HUMAN_INTERFACE, HID_SUBCLASS_NONE, HID_PROTOCOL_NONE),
		D_HIDREPORT(sizeof(_hidReportDescriptorGamepad)),
		D_ENDPOINT(USB_ENDPOINT_IN(pluggedEndpoint), USB_ENDPOINT_TYPE_INTERRUPT, USB_EP_SIZE, 0x01)
	};
	return USB_SendControl(0, &hidInterface, sizeof(hidInterface));
}

int SingleGamepad_::getDescriptor(USBSetup& setup)
{
	// Check if this is a HID Class Descriptor request
	if (setup.bmRequestType != REQUEST_DEVICETOHOST_STANDARD_INTERFACE) { return 0; }
	if (setup.wValueH != HID_REPORT_DESCRIPTOR_TYPE) { return 0; }

	// In a HID Class Descriptor wIndex cointains the interface number
	if (setup.wIndex != pluggedInterface) { return 0; }

	// Reset the protocol on reenumeration. Normally the host should not assume the state of the protocol
	// due to the USB specs, but Windows and Linux just assumes its in report mode.
	protocol = HID_REPORT_PROTOCOL;

	return USB_SendControl(TRANSFER_PGM, _hidReportDescriptorGamepad, sizeof(_hidReportDescriptorGamepad));
}

bool SingleGamepad_::setup(USBSetup& setup)
{
	if (pluggedInterface != setup.wIndex) {
		return false;
	}

	uint8_t request = setup.bRequest;
	uint8_t requestType = setup.bmRequestType;

	if (requestType == REQUEST_DEVICETOHOST_CLASS_INTERFACE)
	{
		if (request == HID_GET_REPORT) {
			// TODO: HID_GetReport();
			return true;
		}
		if (request == HID_GET_PROTOCOL) {
			// TODO: Send8(protocol);
			return true;
		}
	}

	if (requestType == REQUEST_HOSTTODEVICE_CLASS_INTERFACE)
	{
		if (request == HID_SET_PROTOCOL) {
			protocol = setup.wValueL;
			return true;
		}
		if (request == HID_SET_IDLE) {
			idle = setup.wValueL;
			return true;
		}
		if (request == HID_SET_REPORT)
		{
		}
	}

	return false;
}

void SingleGamepad_::SendReport(void* data, int length){
	USB_Send(pluggedEndpoint | TRANSFER_RELEASE, data, length);
}

SingleGamepad_ Gamepad1;
SingleGamepad_ Gamepad2;
SingleGamepad_ Gamepad3;
SingleGamepad_ Gamepad4;


