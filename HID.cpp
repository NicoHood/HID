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

//================================================================================
// Mouse
//================================================================================

Mouse_ Mouse;

//================================================================================
// Keyboard
//================================================================================

Keyboard_ Keyboard;

//================================================================================
// RawHID
//================================================================================

RawHID_ RawHID;

//================================================================================
// Media
//================================================================================

Media_ Media;

//================================================================================
// System
//================================================================================

System_ System;

//================================================================================
// HID Uno/Mega
//================================================================================

#ifndef USBCON

void HID_SendReport(uint8_t id, const void* data, int len)
{
	// write the Report via Protocol and checksum. 16bit for each sending
	// send control address
	NHPwriteChecksum(NHP_ADDRESS_CONTROL, (NHP_USAGE_ARDUINOHID << 8) | id);
	const uint8_t* report = (const uint8_t*)data;
	for (int i = 0; i < len; i++){
		uint8_t data0 = report[i++];
		uint8_t data1 = 0;
		if (i != len)
			data1 = report[i];
		// valid HID reports start at Address 2
		NHPwriteChecksum(2 + i / 2, (data1 << 8) | data0);
	}
#ifdef HID_EXTRADELAY
	delay(HID_EXTRADELAY);
#endif
}

// simple copy/modification of the NicoHoodProtocol writechecksum function
void NHPwriteChecksum(uint8_t address, uint16_t indata){
	// writes two bytes with its inverse
	uint32_t temp = ~indata;
	uint32_t data = (temp << 16) | indata;

	// buffer for write operation
	uint8_t writebuffer[6];

	// start with the maximum size of blocks
	uint8_t blocks = 7;

	// check for the first 7 bit block that doesnt fit into the first 3 bits
	while (blocks > 2){
		uint8_t nextvalue = (data >> (7 * (blocks - 3)));

		if (nextvalue > NHP_MASK_DATA_3BIT){
			// special case for the MSB
			if (blocks == 7) {
				writebuffer[0] = nextvalue;
				blocks--;
			}
			// this block is too big, write this into the next data block
			break;
		}
		else{
			// write the possible first 3 bits and check again after if zero
			writebuffer[0] = nextvalue;
			blocks--;
			// we have our first bits, stop (nonzero)
			if (nextvalue)
				break;
		}
	}

	// write the rest of the data bits
	uint8_t datablocks = blocks - 2;
	while (datablocks > 0){
		writebuffer[datablocks] = data & NHP_MASK_DATA_7BIT;
		data >>= 7;
		datablocks--;
	}

	// write lead + length mask
	writebuffer[0] |= NHP_MASK_LEAD | (blocks << 3);

	// write end mask
	writebuffer[blocks - 1] = NHP_MASK_END | ((address - 1) & NHP_MASK_ADDRESS);

	// write the buffer
	HID_SERIAL.write(writebuffer, blocks);
}

#else // #ifdef USBCON

//================================================================================
// HID Leonardo/Micro
//================================================================================

#include "Platform.h"
#include "USBAPI.h"
#include "USBDesc.h"

#ifdef HID_ENABLED

//================================================================================
//================================================================================

//	HID report descriptor

extern const u8 _hidReportDescriptor[] PROGMEM;
const u8 _hidReportDescriptor[] = {

#ifdef HID_MOUSE_ENABLE
	// Mouse
	0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)	// 54
	0x09, 0x02,                    // USAGE (Mouse)
	0xa1, 0x01,                    // COLLECTION (Application)
	0x09, 0x01,                    //   USAGE (Pointer)
	0xa1, 0x00,                    //   COLLECTION (Physical)
	0x85, HID_REPORTID_MouseReport,//     REPORT_ID
	// 5 buttons
	0x05, 0x09,                    //     USAGE_PAGE (Button)
	0x19, 0x01,                    //     USAGE_MINIMUM (Button 1)
	0x29, 0x05,                    //     USAGE_MAXIMUM (Button 5)
	0x15, 0x00,                    //     LOGICAL_MINIMUM (0)
	0x25, 0x01,                    //     LOGICAL_MAXIMUM (1)
	0x95, 0x05,                    //     REPORT_COUNT (5)
	0x75, 0x01,                    //     REPORT_SIZE (1)
	0x81, 0x02,                    //     INPUT (Data,Var,Abs)
	// reserved
	0x95, 0x01,                    //     REPORT_COUNT (1)
	0x75, 0x03,                    //     REPORT_SIZE (3)
	0x81, 0x03,                    //     INPUT (Cnst,Var,Abs)
	// x, y, wheel
	0x05, 0x01,                    //     USAGE_PAGE (Generic Desktop)
	0x09, 0x30,                    //     USAGE (X)
	0x09, 0x31,                    //     USAGE (Y)
	0x09, 0x38,                    //     USAGE (Wheel)
	0x15, 0x81,                    //     LOGICAL_MINIMUM (-127)
	0x25, 0x7f,                    //     LOGICAL_MAXIMUM (127)
	0x75, 0x08,                    //     REPORT_SIZE (8)
	0x95, 0x03,                    //     REPORT_COUNT (3)
	0x81, 0x06,                    //     INPUT (Data,Var,Rel)
	// end
	0xc0,                          //   END_COLLECTION
	0xc0,                          // END_COLLECTION
#endif

#ifdef HID_KEYBOARD_ENABLE
	// Keyboard
	0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
	0x09, 0x06,                    // USAGE (Keyboard)
	0xa1, 0x01,                    // COLLECTION (Application)
	0x85, HID_REPORTID_KeyboardReport, //   REPORT_ID
	0x05, 0x07,                    //   USAGE_PAGE (Keyboard)
	// modifiers
	0x19, 0xe0,                    //   USAGE_MINIMUM (Keyboard LeftControl)
	0x29, 0xe7,                    //   USAGE_MAXIMUM (Keyboard Right GUI)
	0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
	0x25, 0x01,                    //   LOGICAL_MAXIMUM (1)
	0x75, 0x01,                    //   REPORT_SIZE (1)
	0x95, 0x08,                    //   REPORT_COUNT (8)
	0x81, 0x02,                    //   INPUT (Data,Var,Abs)
	// reserved byte
	0x95, 0x01,                    //   REPORT_COUNT (1)
	0x75, 0x08,                    //   REPORT_SIZE (8)
	0x81, 0x03,                    //   INPUT (Cnst,Var,Abs)
	// Key[6] Array
	0x95, 0x06,                    //   REPORT_COUNT (6)
	0x75, 0x08,                    //   REPORT_SIZE (8)
	0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
	0x25, 0x65,                    //   LOGICAL_MAXIMUM (101)
	0x05, 0x07,                    //   USAGE_PAGE (Keyboard)
	0x19, 0x00,                    //   USAGE_MINIMUM (Reserved (no event indicated))
	0x29, 0x65,                    //   USAGE_MAXIMUM (Keyboard Application)
	0x81, 0x00,                    //   INPUT (Data,Ary,Abs)
	// LEDs for num lock etc
	//0x05, 0x08,   /*   USAGE_PAGE (LEDs) */
	//0x19, 0x01,   /*   USAGE_MINIMUM (Num Lock) */
	//0x29, 0x05,   /*   USAGE_MAXIMUM (Kana) */
	//0x95, 0x05,   /*   REPORT_COUNT (5) */
	//0x75, 0x01,   /*   REPORT_SIZE (1) */
	//0x91, 0x02,   /*   OUTPUT (Data,Var,Abs) */
	// Reserved 3 bits
	//0x95, 0x01,   /*   REPORT_COUNT (1) */
	//0x75, 0x03,   /*   REPORT_SIZE (3) */
	//0x91, 0x03,   /*   OUTPUT (Cnst,Var,Abs) */
	// end
	0xc0,                          // END_COLLECTION
#endif

#ifdef HID_RAWKEYBOARD_ENABLE
	// RAW HID
	0x06, LSB(RAWHID_USAGE_PAGE), MSB(RAWHID_USAGE_PAGE),	// 30
	0x0A, LSB(RAWHID_USAGE), MSB(RAWHID_USAGE),

	0xA1, 0x01,								// Collection 0x01
	0x85, HID_REPORTID_RawKeyboardReport,   // REPORT_ID
	0x75, 0x08,								// report size = 8 bits
	0x15, 0x00,								// logical minimum = 0
	0x26, 0xFF, 0x00,						// logical maximum = 255

	0x95, RAWHID_TX_SIZE,					// report count TX
	0x09, 0x01,								// usage
	0x81, 0x02,								// Input (array)

	0x95, RAWHID_RX_SIZE,					// report count RX
	0x09, 0x02,								// usage
	0x91, 0x02,								// Output (array)
	0xC0,									// end collection
#endif

#ifdef HID_MEDIA_ENABLE
	// Media
	0x05, 0x0C,						// usage page (consumer device)
	0x09, 0x01,						// usage -- consumer control
	0xA1, 0x01,						// collection (application)
	0x85, HID_REPORTID_MediaReport, // report id
	//0x05, 0x0C, // usage page (consumer)

	// 4 media Keys
	0x15, 0x00,						//logical minimum
	0x26, 0xFF, 0x03,				//logical maximum (3ff)
	0x19, 0x00,						// usage minimum (0)
	0x2A, 0xFF, 0x03, //usage maximum (3ff)
	0x95, 0x04,						//report count (4)
	0x75, 0x10,						//report size (16)

	0x81, 0x00,						//input
	0xC0,							//end collection
#endif

#ifdef HID_SYSTEM_ENABLE
	// System
	0x05, 0x01,							// USAGE_PAGE (Generic Desktop)
	0x09, 0x80,							// USAGE (System Control)
	0xa1, 0x01,							// COLLECTION (Application)
	0x85, HID_REPORTID_SystemReport,	//   REPORT_ID
	// 1 system key
	0x15, 0x00,							//   LOGICAL_MINIMUM (0)
	0x26, 0xff, 0x00,					//   LOGICAL_MAXIMUM (255)
	0x19, 0x00,							//   USAGE_MINIMUM (Undefined)
	0x29, 0xff,							//   USAGE_MAXIMUM (System Menu Down)
	0x95, 0x01,							//   REPORT_COUNT (1)
	0x75, 0x08,							//   REPORT_SIZE (8)
	0x81, 0x00,							//   INPUT (Data,Ary,Abs)
	0xc0,								// END_COLLECTION
#endif

#ifdef HID_GAMEPAD1_ENABLE
	// Gamepad1
	0x05, 0x01,							// USAGE_PAGE (Generic Desktop)
	0x09, 0x04,							// USAGE (Joystick)
	0xa1, 0x01,							// COLLECTION (Application)
	0x85, HID_REPORTID_Gamepad1Report,	//   REPORT_ID
	// 32 Buttons
	0x05, 0x09,							//   USAGE_PAGE (Button)
	0x19, 0x01,							//   USAGE_MINIMUM (Button 1)
	0x29, 0x20,							//   USAGE_MAXIMUM (Button 32)
	0x15, 0x00,							//   LOGICAL_MINIMUM (0)
	0x25, 0x01,							//   LOGICAL_MAXIMUM (1)
	0x75, 0x01,							//   REPORT_SIZE (1)
	0x95, 0x20,							//   REPORT_COUNT (32)
	0x81, 0x02,							//   INPUT (Data,Var,Abs)
	// 4 16bit Axis
	0x05, 0x01,							//   USAGE_PAGE (Generic Desktop)
	0xa1, 0x00,							//   COLLECTION (Physical)
	0x09, 0x30,							//     USAGE (X)
	0x09, 0x31,							//     USAGE (Y)
	0x09, 0x33,							//     USAGE (Rx)
	0x09, 0x34,							//     USAGE (Ry)
	0x16, 0x00, 0x80,					//     LOGICAL_MINIMUM (-32768)
	0x26, 0xFF, 0x7F,					//     LOGICAL_MAXIMUM (32767)
	0x75, 0x10,							//     REPORT_SIZE (16)
	0x95, 0x04,							//     REPORT_COUNT (4)
	0x81, 0x02,							//     INPUT (Data,Var,Abs)
	// 2 8bit Axis
	0x09, 0x32,							//     USAGE (Z)
	0x09, 0x35,							//     USAGE (Rz)
	0x15, 0x80,							//     LOGICAL_MINIMUM (-128)
	0x25, 0x7F,							//     LOGICAL_MAXIMUM (127)
	0x75, 0x08,							//     REPORT_SIZE (8)
	0x95, 0x02,							//     REPORT_COUNT (2)
	0x81, 0x02,							//     INPUT (Data,Var,Abs)
	0xc0,								//   END_COLLECTION
	// 2 Hat Switches
	0x05, 0x01,							//   USAGE_PAGE (Generic Desktop)
	0x09, 0x39,							//   USAGE (Hat switch)
	0x09, 0x39,							//   USAGE (Hat switch)
	0x15, 0x01,							//   LOGICAL_MINIMUM (1)
	0x25, 0x08,							//   LOGICAL_MAXIMUM (8)
	0x95, 0x02,							//   REPORT_COUNT (2)
	0x75, 0x04,							//   REPORT_SIZE (4)
	0x81, 0x02,							//   INPUT (Data,Var,Abs)
	// 8bit Throttle + Rudder
	//0x05, 0x02,							//   USAGE_PAGE (Simulation Controls)
	//0xa1, 0x00,							//   COLLECTION (Physical)
	//0x15, 0x00,							//     LOGICAL_MINIMUM (0)
	//0x26, 0xff, 0x00,					//     LOGICAL_MAXIMUM (255)
	//0x09, 0xbb,							//     USAGE (Throttle)
	//0x09, 0xba,							//     USAGE (Rudder)
	//0x75, 0x08,							//     REPORT_SIZE (8)
	//0x95, 0x02,							//     REPORT_COUNT (2)
	//0x81, 0x02,							//     INPUT (Data,Var,Abs)
	//0xc0,								//   END_COLLECTION
	0xc0,								// END_COLLECTION
#endif

#ifdef HID_GAMEPAD2_ENABLE
	// Gamepad2
	0x05, 0x01,							// USAGE_PAGE (Generic Desktop)
	0x09, 0x04,							// USAGE (Joystick)
	0xa1, 0x01,							// COLLECTION (Application)
	0x85, HID_REPORTID_Gamepad2Report,	//   REPORT_ID
	// 32 Buttons
	0x05, 0x09,							//   USAGE_PAGE (Button)
	0x19, 0x01,							//   USAGE_MINIMUM (Button 1)
	0x29, 0x20,							//   USAGE_MAXIMUM (Button 32)
	0x15, 0x00,							//   LOGICAL_MINIMUM (0)
	0x25, 0x01,							//   LOGICAL_MAXIMUM (1)
	0x75, 0x01,							//   REPORT_SIZE (1)
	0x95, 0x20,							//   REPORT_COUNT (32)
	0x81, 0x02,							//   INPUT (Data,Var,Abs)
	// 4 16bit Axis
	0x05, 0x01,							//   USAGE_PAGE (Generic Desktop)
	0xa1, 0x00,							//   COLLECTION (Physical)
	0x09, 0x30,							//     USAGE (X)
	0x09, 0x31,							//     USAGE (Y)
	0x09, 0x33,							//     USAGE (Rx)
	0x09, 0x34,							//     USAGE (Ry)
	0x16, 0x00, 0x80,					//     LOGICAL_MINIMUM (-32768)
	0x26, 0xFF, 0x7F,					//     LOGICAL_MAXIMUM (32767)
	0x75, 0x10,							//     REPORT_SIZE (16)
	0x95, 0x04,							//     REPORT_COUNT (4)
	0x81, 0x02,							//     INPUT (Data,Var,Abs)
	// 2 8bit Axis
	0x09, 0x32,							//     USAGE (Z)
	0x09, 0x35,							//     USAGE (Rz)
	0x15, 0x80,							//     LOGICAL_MINIMUM (-128)
	0x25, 0x7F,							//     LOGICAL_MAXIMUM (127)
	0x75, 0x08,							//     REPORT_SIZE (8)
	0x95, 0x02,							//     REPORT_COUNT (2)
	0x81, 0x02,							//     INPUT (Data,Var,Abs)
	0xc0,								//   END_COLLECTION
	// 2 Hat Switches
	0x09, 0x39,							//   USAGE (Hat switch)
	0x09, 0x39,							//   USAGE (Hat switch)
	0x15, 0x01,							//   LOGICAL_MINIMUM (1)
	0x25, 0x08,							//   LOGICAL_MAXIMUM (8)
	0x95, 0x02,							//   REPORT_COUNT (2)
	0x75, 0x04,							//   REPORT_SIZE (4)
	0x81, 0x02,							//   INPUT (Data,Var,Abs)
	// 8bit Throttle + Rudder
	//0x05, 0x02,							//   USAGE_PAGE (Simulation Controls)
	//0xa1, 0x00,							//   COLLECTION (Physical)
	//0x15, 0x00,							//     LOGICAL_MINIMUM (0)
	//0x26, 0xff, 0x00,					//     LOGICAL_MAXIMUM (255)
	//0x09, 0xbb,							//     USAGE (Throttle)
	//0x09, 0xba,							//     USAGE (Rudder)
	//0x75, 0x08,							//     REPORT_SIZE (8)
	//0x95, 0x02,							//     REPORT_COUNT (2)
	//0x81, 0x02,							//     INPUT (Data,Var,Abs)
	//0xc0,								//   END_COLLECTION
	0xc0,								// END_COLLECTION
#endif

#ifdef HID_GAMEPAD3_ENABLE
	// Gamepad3
	0x05, 0x01,							// USAGE_PAGE (Generic Desktop)
	0x09, 0x04,							// USAGE (Joystick)
	0xa1, 0x01,							// COLLECTION (Application)
	0x85, HID_REPORTID_Gamepad3Report,	//   REPORT_ID
	// 32 Buttons
	0x05, 0x09,							//   USAGE_PAGE (Button)
	0x19, 0x01,							//   USAGE_MINIMUM (Button 1)
	0x29, 0x20,							//   USAGE_MAXIMUM (Button 32)
	0x15, 0x00,							//   LOGICAL_MINIMUM (0)
	0x25, 0x01,							//   LOGICAL_MAXIMUM (1)
	0x75, 0x01,							//   REPORT_SIZE (1)
	0x95, 0x20,							//   REPORT_COUNT (32)
	0x81, 0x02,							//   INPUT (Data,Var,Abs)
	// 4 16bit Axis
	0x05, 0x01,							//   USAGE_PAGE (Generic Desktop)
	0xa1, 0x00,							//   COLLECTION (Physical)
	0x09, 0x30,							//     USAGE (X)
	0x09, 0x31,							//     USAGE (Y)
	0x09, 0x33,							//     USAGE (Rx)
	0x09, 0x34,							//     USAGE (Ry)
	0x16, 0x00, 0x80,					//     LOGICAL_MINIMUM (-32768)
	0x26, 0xFF, 0x7F,					//     LOGICAL_MAXIMUM (32767)
	0x75, 0x10,							//     REPORT_SIZE (16)
	0x95, 0x04,							//     REPORT_COUNT (4)
	0x81, 0x02,							//     INPUT (Data,Var,Abs)
	// 2 8bit Axis
	0x09, 0x32,							//     USAGE (Z)
	0x09, 0x35,							//     USAGE (Rz)
	0x15, 0x80,							//     LOGICAL_MINIMUM (-128)
	0x25, 0x7F,							//     LOGICAL_MAXIMUM (127)
	0x75, 0x08,							//     REPORT_SIZE (8)
	0x95, 0x02,							//     REPORT_COUNT (2)
	0x81, 0x02,							//     INPUT (Data,Var,Abs)
	0xc0,								//   END_COLLECTION
	// 2 Hat Switches
	0x05, 0x01,							//   USAGE_PAGE (Generic Desktop)
	0x09, 0x39,							//   USAGE (Hat switch)
	0x09, 0x39,							//   USAGE (Hat switch)
	0x15, 0x01,							//   LOGICAL_MINIMUM (1)
	0x25, 0x08,							//   LOGICAL_MAXIMUM (8)
	0x95, 0x02,							//   REPORT_COUNT (2)
	0x75, 0x04,							//   REPORT_SIZE (4)
	0x81, 0x02,							//   INPUT (Data,Var,Abs)
	// 8bit Throttle + Rudder
	//0x05, 0x02,							//   USAGE_PAGE (Simulation Controls)
	//0xa1, 0x00,							//   COLLECTION (Physical)
	//0x15, 0x00,							//     LOGICAL_MINIMUM (0)
	//0x26, 0xff, 0x00,					//     LOGICAL_MAXIMUM (255)
	//0x09, 0xbb,							//     USAGE (Throttle)
	//0x09, 0xba,							//     USAGE (Rudder)
	//0x75, 0x08,							//     REPORT_SIZE (8)
	//0x95, 0x02,							//     REPORT_COUNT (2)
	//0x81, 0x02,							//     INPUT (Data,Var,Abs)
	//0xc0,								//   END_COLLECTION
	0xc0,								// END_COLLECTION
#endif

#ifdef HID_GAMEPAD4_ENABLE
	// Gamepad4
	0x05, 0x01,							// USAGE_PAGE (Generic Desktop)
	0x09, 0x04,							// USAGE (Joystick)
	0xa1, 0x01,							// COLLECTION (Application)
	0x85, HID_REPORTID_Gamepad4Report,	//   REPORT_ID
	// 32 Buttons
	0x05, 0x09,							//   USAGE_PAGE (Button)
	0x19, 0x01,							//   USAGE_MINIMUM (Button 1)
	0x29, 0x20,							//   USAGE_MAXIMUM (Button 32)
	0x15, 0x00,							//   LOGICAL_MINIMUM (0)
	0x25, 0x01,							//   LOGICAL_MAXIMUM (1)
	0x75, 0x01,							//   REPORT_SIZE (1)
	0x95, 0x20,							//   REPORT_COUNT (32)
	0x81, 0x02,							//   INPUT (Data,Var,Abs)
	// 4 16bit Axis
	0x05, 0x01,							//   USAGE_PAGE (Generic Desktop)
	0xa1, 0x00,							//   COLLECTION (Physical)
	0x09, 0x30,							//     USAGE (X)
	0x09, 0x31,							//     USAGE (Y)
	0x09, 0x33,							//     USAGE (Rx)
	0x09, 0x34,							//     USAGE (Ry)
	0x16, 0x00, 0x80,					//     LOGICAL_MINIMUM (-32768)
	0x26, 0xFF, 0x7F,					//     LOGICAL_MAXIMUM (32767)
	0x75, 0x10,							//     REPORT_SIZE (16)
	0x95, 0x04,							//     REPORT_COUNT (4)
	0x81, 0x02,							//     INPUT (Data,Var,Abs)
	// 2 8bit Axis
	0x09, 0x32,							//     USAGE (Z)
	0x09, 0x35,							//     USAGE (Rz)
	0x15, 0x80,							//     LOGICAL_MINIMUM (-128)
	0x25, 0x7F,							//     LOGICAL_MAXIMUM (127)
	0x75, 0x08,							//     REPORT_SIZE (8)
	0x95, 0x02,							//     REPORT_COUNT (2)
	0x81, 0x02,							//     INPUT (Data,Var,Abs)
	0xc0,								//   END_COLLECTION
	// 2 Hat Switches
	0x05, 0x01,							//   USAGE_PAGE (Generic Desktop)
	0x09, 0x39,							//   USAGE (Hat switch)
	0x09, 0x39,							//   USAGE (Hat switch)
	0x15, 0x01,							//   LOGICAL_MINIMUM (1)
	0x25, 0x08,							//   LOGICAL_MAXIMUM (8)
	0x95, 0x02,							//   REPORT_COUNT (2)
	0x75, 0x04,							//   REPORT_SIZE (4)
	0x81, 0x02,							//   INPUT (Data,Var,Abs)
	// 8bit Throttle + Rudder
	//0x05, 0x02,							//   USAGE_PAGE (Simulation Controls)
	//0xa1, 0x00,							//   COLLECTION (Physical)
	//0x15, 0x00,							//     LOGICAL_MINIMUM (0)
	//0x26, 0xff, 0x00,					//     LOGICAL_MAXIMUM (255)
	//0x09, 0xbb,							//     USAGE (Throttle)
	//0x09, 0xba,							//     USAGE (Rudder)
	//0x75, 0x08,							//     REPORT_SIZE (8)
	//0x95, 0x02,							//     REPORT_COUNT (2)
	//0x81, 0x02,							//     INPUT (Data,Var,Abs)
	//0xc0,								//   END_COLLECTION
	0xc0,								// END_COLLECTION
#endif

#ifdef HID_JOYSTICK1_ENABLE
	// Joystick1
	0x05, 0x01,							// USAGE_PAGE (Generic Desktop)
	0x09, 0x04,							// USAGE (Joystick)
	0xa1, 0x01,							// COLLECTION (Application)
	0x85, HID_REPORTID_Joystick1Report,	//   REPORT_ID
	0xa1, 0x00,							//   COLLECTION (Physical)
	0x05, 0x09,							//     USAGE_PAGE (Button)
	0x19, 0x01,							//     USAGE_MINIMUM (Button 1)
	0x29, 0x02,							//     USAGE_MAXIMUM (Button 2)
	0x15, 0x00,							//     LOGICAL_MINIMUM (0)
	0x25, 0x01,							//     LOGICAL_MAXIMUM (1)
	0x75, 0x01,							//     REPORT_SIZE (1)
	0x95, 0x02,							//     REPORT_COUNT (2)
	0x81, 0x02,							//     INPUT (Data,Var,Abs)
	0x05, 0x01,							//     USAGE_PAGE (Generic Desktop)
	0x09, 0x30,							//     USAGE (X)
	0x09, 0x31,							//     USAGE (Y)
	0x15, 0x00,							//     LOGICAL_MINIMUM (0)
	0x26, 0xff, 0x03,					//     LOGICAL_MAXIMUM (1023)
	0x75, 0x0a,							//     REPORT_SIZE (10)
	0x95, 0x02,							//     REPORT_COUNT (2)
	0x81, 0x02,							//     INPUT (Data,Var,Abs)
	0x75, 0x02,							//     REPORT_SIZE (2)
	0x95, 0x01,							//     REPORT_COUNT (1)
	0x81, 0x03,							//     INPUT (Cnst,Var,Abs)
	0xc0,								//   END_COLLECTION
	0xc0,								// END_COLLECTION
#endif

#ifdef HID_JOYSTICK2_ENABLE
	// Joystick2
	0x05, 0x01,							// USAGE_PAGE (Generic Desktop)
	0x09, 0x04,							// USAGE (Joystick)
	0xa1, 0x01,							// COLLECTION (Application)
	0x85, HID_REPORTID_Joystick2Report,	//   REPORT_ID
	0xa1, 0x00,							//   COLLECTION (Physical)
	0x05, 0x09,							//     USAGE_PAGE (Button)
	0x19, 0x01,							//     USAGE_MINIMUM (Button 1)
	0x29, 0x02,							//     USAGE_MAXIMUM (Button 2)
	0x15, 0x00,							//     LOGICAL_MINIMUM (0)
	0x25, 0x01,							//     LOGICAL_MAXIMUM (1)
	0x75, 0x01,							//     REPORT_SIZE (1)
	0x95, 0x02,							//     REPORT_COUNT (2)
	0x81, 0x02,							//     INPUT (Data,Var,Abs)
	0x05, 0x01,							//     USAGE_PAGE (Generic Desktop)
	0x09, 0x30,							//     USAGE (X)
	0x09, 0x31,							//     USAGE (Y)
	0x15, 0x00,							//     LOGICAL_MINIMUM (0)
	0x26, 0xff, 0x03,					//     LOGICAL_MAXIMUM (1023)
	0x75, 0x0a,							//     REPORT_SIZE (10)
	0x95, 0x02,							//     REPORT_COUNT (2)
	0x81, 0x02,							//     INPUT (Data,Var,Abs)
	0x75, 0x02,							//     REPORT_SIZE (2)
	0x95, 0x01,							//     REPORT_COUNT (1)
	0x81, 0x03,							//     INPUT (Cnst,Var,Abs)
	0xc0,								//   END_COLLECTION
	0xc0,								// END_COLLECTION
#endif
};

extern const HIDDescriptor _hidInterface PROGMEM;
const HIDDescriptor _hidInterface =
{
	D_INTERFACE(HID_INTERFACE, 1, 3, 0, 0),
	D_HIDREPORT(sizeof(_hidReportDescriptor)),
	D_ENDPOINT(USB_ENDPOINT_IN(HID_ENDPOINT_INT), USB_ENDPOINT_TYPE_INTERRUPT, 0x40, 0x01)
};

//================================================================================
//================================================================================
//	Driver

u8 _hid_protocol = 1;
u8 _hid_idle = 1;

#define WEAK __attribute__ ((weak))

int WEAK HID_GetInterface(u8* interfaceNum)
{
	interfaceNum[0] += 1;	// uses 1
	return USB_SendControl(TRANSFER_PGM, &_hidInterface, sizeof(_hidInterface));
}

int WEAK HID_GetDescriptor(int /* i */)
{
	return USB_SendControl(TRANSFER_PGM, _hidReportDescriptor, sizeof(_hidReportDescriptor));
}

void WEAK HID_SendReport(u8 id, const void* data, int len)
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
	}
	return false;
}

#endif // #ifdef HID_ENABLED

#endif /* if defined(USBCON) */