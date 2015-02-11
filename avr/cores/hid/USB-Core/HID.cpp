/* Copyright (c) 2011, Peter Barrett
**
** Permission to use, copy, modify, and/or distribute this software for
** any purpose with or without fee is hereby granted, provided that the
** above copyright notice and this permission notice appear in all copies.
**
** THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
** WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
** WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR
** BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES
** OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
** WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
** ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
** SOFTWARE.
*/

/*
Copyright (c) 2014 NicoHood
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

#include "HID.h"

#define WEAK __attribute__ ((weak))

#if defined(USBCON)
#ifdef HID_ENABLED

//================================================================================
//================================================================================

extern const u8 _hidReportDescriptor[] PROGMEM;
const u8 _hidReportDescriptor[] = {
	// by default use the standard HID descriptors
	// extern descriptors can be passed via pins_Arduino.h
#ifdef EXTERN_HID_REPORT
	EXTERN_HID_REPORT
#else
	// use the hid descriptors of the selected hid devices
#ifdef HID_KEYBOARD_LEDS_ENABLE //TODO move keyboard below mouse?
	HID_REPORT_KEYBOARD_LEDS(HID_REPORTID_KEYBOARD),
#elif defined(HID_KEYBOARD_KEYS_ENABLE)
	HID_REPORT_KEYBOARD_KEYS(HID_REPORTID_KEYBOARD),
#endif
#if defined(HID_MOUSE_ENABLE)
	HID_REPORT_MOUSE(HID_REPORTID_MOUSE),
#endif
#if defined(HID_MOUSE_ABSOLUTE_ENABLE)
	HID_REPORT_MOUSE_ABSOLUTE(HID_REPORTID_MOUSE_ABSOLUTE),
#endif
#ifdef HID_RAWHID_ENABLE
	HID_REPORT_RAWHID(HID_REPORTID_RAWHID), // not working at the moment
#endif
#ifdef HID_CONSUMER_ENABLE
	HID_REPORT_CONSUMERCONTROL(HID_REPORTID_CONSUMERCONTROL),
#endif
#ifdef HID_SYSTEM_ENABLE
	HID_REPORT_SYSTEMCONTROL(HID_REPORTID_SYSTEMCONTROL),
#endif
#ifdef HID_GAMEPAD_ENABLE
	HID_REPORT_GAMEPAD(HID_REPORTID_GAMEPAD),
#endif
#endif
};

extern const HIDDescriptor _hidInterface PROGMEM;
const HIDDescriptor _hidInterface =
{
	D_INTERFACE(HID_INTERFACE, 1, 3, 0, 0),
	D_HIDREPORT(sizeof(_hidReportDescriptor)),
	// edit by NicoHood
	D_ENDPOINT(USB_ENDPOINT_IN(HID_ENDPOINT_INT), USB_ENDPOINT_TYPE_INTERRUPT, USB_EP_SIZE, 0x01)
};

#if defined(HID_KEYBOARD_LEDS_ENABLED)
volatile uint8_t hid_keyboard_leds = 0;
#endif

//================================================================================
//================================================================================
//	Driver

u8 _hid_protocol = 1;
u8 _hid_idle = 1;

int WEAK HID_GetInterface(u8* interfaceNum)
{
	interfaceNum[0] += 1;	// uses 1
	return USB_SendControl(TRANSFER_PGM, &_hidInterface, sizeof(_hidInterface));
}

int WEAK HID_GetDescriptor(int /* i */)
{
	return USB_SendControl(TRANSFER_PGM, _hidReportDescriptor, sizeof(_hidReportDescriptor));
}

void WEAK HID_SendReport(uint8_t id, const void* data, int len)
{
	USB_Send(HID_TX, &id, 1);
	USB_Send(HID_TX | TRANSFER_RELEASE, data, len);
}

bool WEAK HID_Setup(Setup& setup)
{
	u8 r = setup.bRequest;
	u8 requestType = setup.bmRequestType;
	if (REQUEST_DEVICETOHOST_CLASS_INTERFACE == requestType)
	{
		if (HID_GET_REPORT == r)
		{
			//HID_GetReport();
			return true;
		}
		if (HID_GET_PROTOCOL == r)
		{
			//Send8(_hid_protocol);	// TODO
			return true;
		}
	}

	if (REQUEST_HOSTTODEVICE_CLASS_INTERFACE == requestType)
	{
		if (HID_SET_PROTOCOL == r)
		{
			_hid_protocol = setup.wValueL;
			return true;
		}

		if (HID_SET_IDLE == r)
		{
			_hid_idle = setup.wValueL;
			return true;
		}
#if defined(HID_KEYBOARD_LEDS_ENABLED)
		if (HID_SET_REPORT == r)
		{
			//TODO check correct report ID (not needed for now, no other device has an out report)
			// maybe make this a general weak implementation to use it for RAW HID later?
			if (setup.wLength == 2)
			{
				// write led out report data
				uint8_t data[2];
				if (2 == USB_RecvControl(data, 2))
					hid_keyboard_leds = data[1];
			}
			// else TODO check for other devices like RAW HID, not needed for now
		}
#endif
	}
	return false;
}

#endif

#else /* if defined(USBCON) */

void WEAK HID_SendReport(u8 id, const void* data, int len)
{
	// empty to let the user use the HIDAPI for different use
}

#endif /* if defined(USBCON) */
