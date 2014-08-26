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

#ifndef HID_REPORTS_H
#define HID_REPORTS_H

//================================================================================
//Definitions
//================================================================================

#define LSB(_x) ((_x) & 0xFF)
#define MSB(_x) ((_x) >> 8)

#define RAWHID_USAGE_PAGE	0xFFC0 // recommended: 0xFF00 to 0xFFFF
#define RAWHID_USAGE		0x0C00 // recommended: 0x0100 to 0xFFFF
#define RAWHID_TX_SIZE 15 // 1 byte for report ID
#define RAWHID_RX_SIZE 15 // 1 byte for report ID

//================================================================================
//Report Typedefinitions
//================================================================================

typedef union{
	// mouse report: 5 buttons, position, wheel
	uint8_t whole8[4];
	uint16_t whole16[4/2];
	uint32_t whole32[4/4];

	struct{
		uint8_t buttons:5;
		uint8_t reserved:3;
		int8_t xAxis;
		int8_t yAxis;
		int8_t wheel;
	};
} HID_MouseReport_Data_t;


typedef union{
	// Low level key report: up to 6 keys and shift, ctrl etc at once
	uint8_t whole8[8];
	uint16_t whole16[8/2];
	uint32_t whole32[8/4];

	struct{
		uint8_t modifiers;
		uint8_t reserved;
		uint8_t keys[6];
	};
} HID_KeyboardReport_Data_t;


typedef union{
	// a 32 byte buffer for rx or tx
	uint8_t whole8[RAWHID_TX_SIZE];
	uint16_t whole16[RAWHID_TX_SIZE / 2];
	uint32_t whole32[RAWHID_TX_SIZE / 4];
	uint8_t buff[RAWHID_TX_SIZE];
} HID_RawKeyboardReport_Data_t;


typedef union{
	// every usable media key possible. Only one at the same time.
	uint8_t whole8[8];
	uint16_t whole16[8/2];
	uint32_t whole32[8/4];

	struct{
		uint16_t key1;
		uint16_t key2;
		uint16_t key3;
		uint16_t key4;
	};
} HID_MediaReport_Data_t;


typedef union{
	// every usable system control key possible. Only one at the same time.
	uint8_t whole8[1];
	uint8_t key;
} HID_SystemReport_Data_t;


typedef union {
	// 32 Buttons, 6 Axis, 2 D-Pads
	uint8_t whole8[15];
	uint16_t whole16[15/2];
	uint32_t whole32[15/4];
	uint32_t buttons;

	struct{
		uint8_t button1 :1;
		uint8_t button2 :1;
		uint8_t button3 :1;
		uint8_t button4 :1;
		uint8_t button5 :1;
		uint8_t button6 :1;
		uint8_t button7 :1;
		uint8_t button8 :1;

		uint8_t button9 :1;
		uint8_t button10 :1;
		uint8_t button11 :1;
		uint8_t button12 :1;
		uint8_t button13 :1;
		uint8_t button14 :1;
		uint8_t button15 :1;
		uint8_t button16 :1;

		uint8_t button17 :1;
		uint8_t button18 :1;
		uint8_t button19 :1;
		uint8_t button20 :1;
		uint8_t button21 :1;
		uint8_t button22 :1;
		uint8_t button23 :1;
		uint8_t button24 :1;

		uint8_t button25 :1;
		uint8_t button26 :1;
		uint8_t button27 :1;
		uint8_t button28 :1;
		uint8_t button29 :1;
		uint8_t button30 :1;
		uint8_t button31 :1;
		uint8_t button32 :1;

		int16_t	xAxis;
		int16_t	yAxis;

		int16_t	rxAxis;
		int16_t	ryAxis;

		int8_t	zAxis;
		int8_t	rzAxis;		

		uint8_t		dPad1: 4;
		uint8_t		dPad2: 4;
	};
} HID_GamepadReport_Data_t;


typedef union{
	// 2 Buttons, 2 Axis
	uint8_t whole8[3];
	uint16_t whole16[3/2];
	uint8_t buttons :2;

	struct{
		uint16_t button1 :1;
		uint16_t button2 :1;
		uint16_t xAxis :10;
		uint16_t yAxis :10;
		uint16_t reserved :2;
	};
} HID_JoystickReport_Data_t;


typedef union{
	HID_MouseReport_Data_t Mouse;
	HID_KeyboardReport_Data_t Keyboard;
	HID_RawKeyboardReport_Data_t RawKeyboard;
	HID_MediaReport_Data_t Media;
	HID_GamepadReport_Data_t Gamepad1;
	HID_GamepadReport_Data_t Gamepad2;
	HID_JoystickReport_Data_t Joystick1;
	HID_JoystickReport_Data_t Joystick2;
} HID_HIDReport_Data_t;


/** Enum for the HID report IDs used in the device. */
typedef enum{
	HID_REPORTID_NotAReport			= 0x00,  // first entry is always zero for multireports
	HID_REPORTID_MouseReport		= 0x01, /**< Report ID for the Mouse report within the device. */
	HID_REPORTID_KeyboardReport		= 0x02, /**< Report ID for the Keyboard report within the device. */
	HID_REPORTID_RawKeyboardReport	= 0x03, /**< Report ID for the Raw Keyboard report within the device. */
	HID_REPORTID_MediaReport		= 0x04, /**< Report ID for the Media report within the device. */
	HID_REPORTID_SystemReport		= 0x05, /**< Report ID for the Power report within the device. */
	HID_REPORTID_Gamepad1Report		= 0x06, /**< Report ID for the Gamepad1 report within the device. */
	HID_REPORTID_Gamepad2Report		= 0x07, /**< Report ID for the Gamepad2 report within the device. */
	HID_REPORTID_Gamepad3Report		= 0x08, /**< Report ID for the Gamepad3 report within the device. */
	HID_REPORTID_Gamepad4Report		= 0x09, /**< Report ID for the Gamepad4 report within the device. */
	HID_REPORTID_Joystick1Report	= 0x10, /**< Report ID for the Joystick1 report within the device. */
	HID_REPORTID_Joystick2Report	= 0x11, /**< Report ID for the Joystick2 report within the device. */
	HID_REPORTID_LastNotAReport,			// determinate whats the maximum number of reports -1
} HID_Report_IDs;

#endif