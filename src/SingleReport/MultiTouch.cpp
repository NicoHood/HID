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

#include "MultiTouch.h"

// HID Report identifiers
#define _HID_REPORTID_TOUCH 0x01
#define _HID_REPORTID_FEATURE 0x05

// First part of the descriptor. It appears only once
static const uint8_t _hidReportDescriptorTouchscreen_1[] PROGMEM = {
	0x05, 0x0D,                    // USAGE_PAGE(Digitizers)
	0x09, 0x04,                    // USAGE     (Touch Screen)
	0xA1, 0x01,                    // COLLECTION(Application)

	// define the actual amount of fingers that are concurrently touching the screen
	0x85, _HID_REPORTID_TOUCH,     //   REPORT_ID (Touch)
	0x09, 0x54,                    //   USAGE (Contact count)
	0x25, 0x7f,                    //   LOGICAL_MAXIMUM (128)
	0x95, 0x01,                    //   REPORT_COUNT(1)
	0x75, 0x08,                    //   REPORT_SIZE (8)
	0x81, 0x02                     //   INPUT (Data,Var,Abs)
};

// Finger definition part of the descriptor. It will repeat REPORTFINGERS times, once for each finger.
// If more actual fingers are present than descriptor fingers, multiple reports will be sent sequentially under "Hybrid Mode" rule (See MSDN)
static const uint8_t _hidReportDescriptorTouchscreen_2[] PROGMEM = {
	// declare a finger collection
	0x05, 0x0D,                    //   USAGE_PAGE(Digitizers)
	0x09, 0x22,                    //   USAGE (Finger)
	0xA1, 0x02,                    //   COLLECTION (Logical)

	// declare an identifier for the finger
	0x09, 0x51,                    //     USAGE (Contact Identifier)
	0x25, 0x7f,                    //     LOGICAL_MAXIMUM (127)
	0x75, 0x08,                    //     REPORT_SIZE (8)
	0x95, 0x01,                    //     REPORT_COUNT (1)
	0x81, 0x02,                    //     INPUT (Data,Var,Abs)

	// declare Tip Switch & In range
	0x09, 0x42,                    //     USAGE (Tip Switch)
	0x09, 0x32,                    //     USAGE (In Range)
	0x15, 0x00,                    //     LOGICAL_MINIMUM (0)
	0x25, 0x01,                    //     LOGICAL_MAXIMUM (1)
	0x75, 0x01,                    //     REPORT_SIZE (1)
	0x95, 0x02,                    //     REPORT_COUNT(2)
	0x81, 0x02,                    //     INPUT (Data,Var,Abs)
	// declare the 6 padding bits as constant so the driver will ignore them
	0x95, 0x06,                    //     REPORT_COUNT (6)
	0x81, 0x03,                    //     INPUT (Cnst,Ary,Abs)

	// declare pressure
	0x09, 0x30,                    //     USAGE (Pressure)
	0x25, 0x7f,                    //     LOGICAL_MAXIMUM (127)
	0x75, 0x08,                    //     REPORT_SIZE (8)
	0x95, 0x01,                    //     REPORT_COUNT (1)
	0x81, 0x02,                    //     INPUT (Data,Var,Abs)

	// define absolute X and Y coordinates of 16 bit each (percent values multiplied with 100)
	0x05, 0x01,                    //     USAGE_PAGE (Generic Desktop)
	0x09, 0x30,                    //     Usage (X)
	0x09, 0x31,                    //     Usage (Y)
	0x16, 0x00, 0x00,              //     Logical Minimum (0)
	0x26, 0x10, 0x27,              //     Logical Maximum (10000)
	0x36, 0x00, 0x00,              //     Physical Minimum (0)
	0x46, 0x10, 0x27,              //     Physical Maximum (10000)
	0x66, 0x00, 0x00,              //     UNIT (None)
	0x75, 0x10,                    //     Report Size (16),
	0x95, 0x02,                    //     Report Count (2),
	0x81, 0x02,                    //     Input (Data,Var,Abs)
	0xC0                           //   END_COLLECTION
};

// Last of the descriptor. It appears only once
static const uint8_t _hidReportDescriptorTouchscreen_3[] PROGMEM = {
	// define the maximum amount of fingers that the device supports
	0x05, 0x0D,                    //   USAGE_PAGE(Digitizers)
	0x85, _HID_REPORTID_FEATURE,   //   REPORT_ID (Feature)
	0x09, 0x55,                    //   USAGE (Contact Count Maximum)
	0x25, 0x7f,                    //   LOGICAL_MAXIMUM (127)
	0xB1, 0x02,                    //   FEATURE (Data,Var,Abs)

	0xC0                           // END_COLLECTION
};


MultiTouch_::MultiTouch_(void) : PluggableUSBModule(2, 1, epType), protocol(HID_REPORT_PROTOCOL), idle(1), featureReport((uint8_t *)&_ccmFeature), featureLength(sizeof(_ccmFeature))
{
	_report.reportID = _HID_REPORTID_TOUCH;
	_ccmFeature.reportID = _HID_REPORTID_FEATURE;
	_ccmFeature.contactCountMaximum = HID_MULTITOUCH_MAXFINGERS;
	epType[0] = EP_TYPE_INTERRUPT_IN;
	PluggableUSB().plug(this);
}

int MultiTouch_::getInterface(uint8_t* interfaceCount)
{
	*interfaceCount += 1; // uses 1
	HIDDescriptor hidInterface = {
		D_INTERFACE(pluggedInterface, 1, USB_DEVICE_CLASS_HUMAN_INTERFACE, HID_SUBCLASS_NONE, HID_PROTOCOL_NONE),
		D_HIDREPORT(sizeof(_hidReportDescriptorTouchscreen_1) + sizeof(_hidReportDescriptorTouchscreen_2) * HID_MULTITOUCH_REPORTFINGERS + sizeof(_hidReportDescriptorTouchscreen_3)),
		D_ENDPOINT(USB_ENDPOINT_IN(pluggedEndpoint), USB_ENDPOINT_TYPE_INTERRUPT, USB_EP_SIZE, 0x01)
	};
	return USB_SendControl(0, &hidInterface, sizeof(hidInterface));
}

int MultiTouch_::getDescriptor(USBSetup& setup)
{
	// Check if this is a HID Class Descriptor request
	if (setup.bmRequestType != REQUEST_DEVICETOHOST_STANDARD_INTERFACE) { return 0; }
	if (setup.wValueH != HID_REPORT_DESCRIPTOR_TYPE) { return 0; }

	// In a HID Class Descriptor wIndex cointains the interface number
	if (setup.wIndex != pluggedInterface) { return 0; }

	// Reset the protocol on reenumeration. Normally the host should not assume the state of the protocol
	// due to the USB specs, but Windows and Linux just assumes its in report mode.
	protocol = HID_REPORT_PROTOCOL;

	// Transmit HID descriptor. See comments next to the descriptor parts
	int ret = 0;
	ret += USB_SendControl(TRANSFER_PGM, _hidReportDescriptorTouchscreen_1, sizeof(_hidReportDescriptorTouchscreen_1));
	for (int i = 0; i < HID_MULTITOUCH_REPORTFINGERS; i++) {
		ret += USB_SendControl(TRANSFER_PGM, _hidReportDescriptorTouchscreen_2, sizeof(_hidReportDescriptorTouchscreen_2));
	}
	ret += USB_SendControl(TRANSFER_PGM, _hidReportDescriptorTouchscreen_3, sizeof(_hidReportDescriptorTouchscreen_3));

	return ret;
}

bool MultiTouch_::setup(USBSetup& setup)
{
	if (pluggedInterface != setup.wIndex) {
		return false;
	}

	uint8_t request = setup.bRequest;
	uint8_t requestType = setup.bmRequestType;

	if (requestType == REQUEST_DEVICETOHOST_CLASS_INTERFACE)
	{
		if (request == HID_GET_REPORT) {
			if(setup.wValueH == HID_REPORT_TYPE_FEATURE){
				// The only feature is Contact Count Maximum
				USB_SendControl(0, featureReport, featureLength);
				return true;
			}
			return true;
		}
		if (request == HID_GET_PROTOCOL) {
			// TODO improve
#ifdef __AVR__
			UEDATX = protocol;
#endif
			return true;
		}
		if (request == HID_GET_IDLE) {
			// TODO improve
#ifdef __AVR__
			UEDATX = idle;
#endif
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
			// Check if data has the correct length afterwards
			int length = setup.wLength;

			// Feature (set feature report)
			if(setup.wValueH == HID_REPORT_TYPE_FEATURE){
				// No need to check for negative featureLength values,
				// except the host tries to send more then 32k bytes.
				// We dont have that much ram anyways.
				if (length == featureLength) {
					USB_RecvControl(featureReport, featureLength);
					return true;
				}
				// TODO fake clear data?
			}

			// Output (not applicable)
			else if(setup.wValueH == HID_REPORT_TYPE_OUTPUT){
				return true;
			}

			// Input (set HID report)
			else if(setup.wValueH == HID_REPORT_TYPE_INPUT)
			{
				if(length == sizeof(_report)){
					USB_RecvControl(&_report, length);
					return true;
				}
			}
		}
	}

	return false;
}

uint8_t MultiTouch_::getProtocol() {
	return protocol;
}

int MultiTouch_::_sendReport() {
	return USB_Send(pluggedEndpoint | TRANSFER_RELEASE, &_report, sizeof(_report));
}

void MultiTouch_::wakeupHost() {
#ifdef __AVR__
	USBDevice.wakeupHost();
#endif
}

MultiTouch_ MultiTouch;
