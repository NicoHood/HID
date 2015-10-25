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

#include "SingleNKROKeyboard.h"

static const uint8_t _hidReportDescriptorNKRO[] PROGMEM = {
    //  NKRO Keyboard
    0x05, 0x01,                      /* USAGE_PAGE (Generic Desktop)	  47 */
    0x09, 0x06,                      /* USAGE (Keyboard) */
    0xa1, 0x01,                      /* COLLECTION (Application) */
    0x05, 0x07,                      /*   USAGE_PAGE (Keyboard) */

    /* Keyboard Modifiers (shift, alt, ...) */
    0x19, 0xe0,                      /*   USAGE_MINIMUM (Keyboard LeftControl) */
    0x29, 0xe7,                      /*   USAGE_MAXIMUM (Keyboard Right GUI) */
    0x15, 0x00,                      /*   LOGICAL_MINIMUM (0) */
    0x25, 0x01,                      /*   LOGICAL_MAXIMUM (1) */
    0x75, 0x01,                      /*   REPORT_SIZE (1) */
	0x95, 0x08,                      /*   REPORT_COUNT (8) */
    0x81, 0x02,                      /*   INPUT (Data,Var,Abs) */

	/* 5 LEDs for num lock etc, 3 left for advanced, custom usage */
	0x05, 0x08,						 /*   USAGE_PAGE (LEDs) */
	0x19, 0x01,						 /*   USAGE_MINIMUM (Num Lock) */
	0x29, 0x08,						 /*   USAGE_MAXIMUM (Kana + 3 custom)*/
	0x95, 0x08,						 /*   REPORT_COUNT (8) */
	0x75, 0x01,						 /*   REPORT_SIZE (1) */
	0x91, 0x02,						 /*   OUTPUT (Data,Var,Abs) */

	/* 104 Keys as bitmap */
    0x05, 0x07,                     /*   USAGE_PAGE (Keyboard) */
	0x19, 0x00,						/*   Usage Minimum (0) */
	0x29, NKRO_KEY_COUNT - 1,		/*   Usage Maximum (103) */
	0x15, 0x00,						/*   Logical Minimum (0) */
	0x25, 0x01,						/*   Logical Maximum (1) */
	0x75, 0x01,						/*   Report Size (1) */
	0x95, NKRO_KEY_COUNT,			/*   Report Count (104) */
	0x81, 0x02,						/*   Input (Data, Variable, Absolute) */

    /* 1 Custom Keyboard key */
    0x95, 0x01,                      /*   REPORT_COUNT (1) */
    0x75, 0x08,                      /*   REPORT_SIZE (8) */
    0x15, 0x00,                      /*   LOGICAL_MINIMUM (0) */
    0x26, 0xE7, 0x00,                /*   LOGICAL_MAXIMUM (231) */
    0x19, 0x00,                      /*   USAGE_MINIMUM (Reserved (no event indicated)) */
    0x29, 0xE7,                      /*   USAGE_MAXIMUM (Keyboard Right GUI) */
    0x81, 0x00,                      /*   INPUT (Data,Ary,Abs) */

    /* End */
	0xC0						     /*   End Collection */
};

SingleNKROKeyboard_::SingleNKROKeyboard_(void) : PluggableUSBModule(1, 1, epType), protocol(HID_REPORT_PROTOCOL), idle(1), leds(0)
{
	epType[0] = EP_TYPE_INTERRUPT_IN;
	PluggableUSB().plug(this);
}

int SingleNKROKeyboard_::getInterface(uint8_t* interfaceCount)
{
	*interfaceCount += 1; // uses 1
	HIDDescriptor hidInterface = {
		D_INTERFACE(pluggedInterface, 1, USB_DEVICE_CLASS_HUMAN_INTERFACE, HID_SUBCLASS_NONE, HID_PROTOCOL_NONE),
		D_HIDREPORT(sizeof(_hidReportDescriptorNKRO)),
		D_ENDPOINT(USB_ENDPOINT_IN(pluggedEndpoint), USB_ENDPOINT_TYPE_INTERRUPT, USB_EP_SIZE, 0x01)
	};
	return USB_SendControl(0, &hidInterface, sizeof(hidInterface));
}

int SingleNKROKeyboard_::getDescriptor(USBSetup& setup)
{
	// Check if this is a HID Class Descriptor request
	if (setup.bmRequestType != REQUEST_DEVICETOHOST_STANDARD_INTERFACE) { return 0; }
	if (setup.wValueH != HID_REPORT_DESCRIPTOR_TYPE) { return 0; }

	// In a HID Class Descriptor wIndex cointains the interface number
	if (setup.wIndex != pluggedInterface) { return 0; }

	// Reset the protocol on reenumeration. Normally the host should not assume the state of the protocol
	// due to the USB specs, but Windows and Linux just assumes its in report mode.
	protocol = HID_REPORT_PROTOCOL;

	return USB_SendControl(TRANSFER_PGM, _hidReportDescriptorNKRO, sizeof(_hidReportDescriptorNKRO));
}

bool SingleNKROKeyboard_::setup(USBSetup& setup)
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
			// Check if data has the correct length
			auto length = setup.wLength;
			if(length == sizeof(leds)){
				USB_RecvControl(&leds, length);
			}
		}
	}

	return false;
}

uint8_t SingleNKROKeyboard_::getLeds(void){
    return leds;
}

int SingleNKROKeyboard_::send(void){
	return USB_Send(pluggedEndpoint | TRANSFER_RELEASE, &_keyReport, sizeof(_keyReport));
}

SingleNKROKeyboard_ SingleNKROKeyboard;


