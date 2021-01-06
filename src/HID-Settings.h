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

//================================================================================
// Settings
//================================================================================


#define HID_REPORTID_NONE 0

#ifndef HID_REPORTID_MOUSE
#define HID_REPORTID_MOUSE 1
#endif

#ifndef HID_REPORTID_KEYBOARD
#define HID_REPORTID_KEYBOARD 2
#endif

#ifndef HID_REPORTID_RAWHID
// This will not work properly in most cases.
// The number is just kept from the old number counting.
//#define HID_REPORTID_RAWHID 3
#endif

#ifndef HID_REPORTID_CONSUMERCONTROL
#define HID_REPORTID_CONSUMERCONTROL 4
#endif

#ifndef HID_REPORTID_SYSTEMCONTROL
#define HID_REPORTID_SYSTEMCONTROL 5
#endif

#ifndef HID_REPORTID_GAMEPAD
#define HID_REPORTID_GAMEPAD 6
#endif

#ifndef HID_REPORTID_MOUSE_ABSOLUTE
#define HID_REPORTID_MOUSE_ABSOLUTE 7
#endif

#ifndef HID_REPORTID_NKRO_KEYBOARD
#define HID_REPORTID_NKRO_KEYBOARD 8
#endif

#ifndef HID_REPORTID_TEENSY_KEYBOARD
#define HID_REPORTID_TEENSY_KEYBOARD 9
#endif

#ifndef HID_REPORTID_SURFACEDIAL
#define HID_REPORTID_SURFACEDIAL 10
#endif

#if defined(ARDUINO_ARCH_AVR)

// Use default alignment for AVR
#define ATTRIBUTE_PACKED

#include "PluggableUSB.h"

#define EPTYPE_DESCRIPTOR_SIZE      uint8_t

#elif defined(ARDUINO_ARCH_SAM)

#define ATTRIBUTE_PACKED  __attribute__((packed, aligned(1)))

#include "USB/PluggableUSB.h"

#define EPTYPE_DESCRIPTOR_SIZE      uint32_t
#define EP_TYPE_INTERRUPT_IN        (UOTGHS_DEVEPTCFG_EPSIZE_512_BYTE | \
                                    UOTGHS_DEVEPTCFG_EPDIR_IN |         \
                                    UOTGHS_DEVEPTCFG_EPTYPE_BLK |       \
                                    UOTGHS_DEVEPTCFG_EPBK_1_BANK |      \
                                    UOTGHS_DEVEPTCFG_NBTRANS_1_TRANS |  \
                                    UOTGHS_DEVEPTCFG_ALLOC)
#define EP_TYPE_INTERRUPT_OUT       (UOTGHS_DEVEPTCFG_EPSIZE_512_BYTE | \
                                    UOTGHS_DEVEPTCFG_EPTYPE_BLK |       \
                                    UOTGHS_DEVEPTCFG_EPBK_1_BANK |      \
                                    UOTGHS_DEVEPTCFG_NBTRANS_1_TRANS |  \
                                    UOTGHS_DEVEPTCFG_ALLOC)
#define USB_EP_SIZE                 EPX_SIZE
#define USB_SendControl             USBD_SendControl
#define USB_Available               USBD_Available
#define USB_Recv                    USBD_Recv
#define USB_Send                    USBD_Send
#define USB_Flush                   USBD_Flush

#elif defined(ARDUINO_ARCH_SAMD)

#define ATTRIBUTE_PACKED  __attribute__((packed, aligned(1)))

#define USB_EP_SIZE                 EPX_SIZE
#define EP_TYPE_INTERRUPT_IN        USB_ENDPOINT_TYPE_INTERRUPT | USB_ENDPOINT_IN(0);
#define EP_TYPE_INTERRUPT_OUT       USB_ENDPOINT_TYPE_INTERRUPT | USB_ENDPOINT_OUT(0);

#if defined(ARDUINO_API_VERSION)
#include "api/PluggableUSB.h"
#define EPTYPE_DESCRIPTOR_SIZE		unsigned int
#else
#include "USB/PluggableUSB.h"

#define EPTYPE_DESCRIPTOR_SIZE      uint32_t
//#define USB_SendControl           USBDevice.sendControl -> real C++ functions to take care of PGM overloading
#define USB_Available               USBDevice.available
#define USB_Recv                    USBDevice.recv
#define USB_RecvControl             USBDevice.recvControl
#define USB_Send                    USBDevice.send
#define USB_Flush                   USBDevice.flush

int USB_SendControl(void* y, uint8_t z);
int USB_SendControl(uint8_t x, const void* y, uint8_t z);
#endif

#define TRANSFER_PGM                0
#define TRANSFER_RELEASE            0

#define HID_REPORT_TYPE_INPUT       1
#define HID_REPORT_TYPE_OUTPUT      2
#define HID_REPORT_TYPE_FEATURE     3

#else

#error "Unsupported architecture"

#endif
