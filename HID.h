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

#ifndef HID_H
#define HID_H

#include <Arduino.h>

// HID Resources
#include "HID_Reports.h"
#include "RawHID.h"
#include "Media.h"
#include "System.h"
#include "Gamepad.h"
#include "Keyboard.h"
#include "Mouse.h"

//================================================================================
//Settings
//================================================================================

// deactive unnecessary stuff for Leonardo/Micro
// reports needs to be <=255 bytes for leonardo/micro!
#define HID_MOUSE_ENABLE 54
#define HID_KEYBOARD_ENABLE 65-18 //18 for missing led out report = 47
//#define HID_RAWKEYBOARD_ENABLE 30
#define HID_MEDIA_ENABLE 25
#define HID_SYSTEM_ENABLE 24
#define HID_GAMEPAD1_ENABLE 71
//#define HID_GAMEPAD2_ENABLE 71
//#define HID_GAMEPAD3_ENABLE 71
//#define HID_GAMEPAD4_ENABLE 71
//#define HID_JOYSTICK1_ENABLE 51
//#define HID_JOYSTICK2_ENABLE 51

// extra delay for raspberry. Only needed for Hoodloader and slow devices
//#define HID_EXTRADELAY 20

//================================================================================
// NHP
//================================================================================

// Start Mask
#define NHP_MASK_START		0xC0 //B11|000000 the two MSB bits
#define NHP_MASK_LEAD		0xC0 //B11|000000
#define NHP_MASK_DATA		0x00 //B0|0000000 only the first MSB is important
#define NHP_MASK_END		0x80 //B10|000000

// Content Mask
#define NHP_MASK_LENGTH		0x38 //B00|111|000
#define NHP_MASK_COMMAND	0x0F //B0000|1111
#define NHP_MASK_DATA_7BIT	0x7F //B0|1111111
#define NHP_MASK_DATA_4BIT	0x0F //B0000|1111
#define NHP_MASK_DATA_3BIT	0x07 //B00000|111
#define NHP_MASK_ADDRESS	0x3F //B00|111111

// Reserved Addresses
#define NHP_ADDRESS_CONTROL 0x01

// Reserved Usages
#define NHP_USAGE_ARDUINOHID 0x01

// Serial to write Protocol data to. Default: Serial
#define HID_SERIAL Serial
#define SERIAL_HID_BAUD 115200

void NHPwriteChecksum(uint8_t address, uint16_t indata);

//================================================================================
// Keyboard Definitions
//================================================================================

//Keyboard fixed/added missing Keys
#define KEY_PRINT			0xCE
#define KEY_SCROLL_LOCK		0xCF
#define KEY_PAUSE			0xD0

//Raw Keyboard definitions
#define RAW_KEYBOARD_LEFT_CTRL   B00000001
#define RAW_KEYBOARD_LEFT_SHIFT  B00000010
#define RAW_KEYBOARD_LEFT_ALT    B00000100
#define RAW_KEYBOARD_LEFT_GUI  	 B00001000
#define RAW_KEYBOARD_RIGHT_CTRL  B00010000
#define RAW_KEYBOARD_RIGHT_SHIFT B00100000
#define RAW_KEYBOARD_RIGHT_ALT   B01000000
#define RAW_KEYBOARD_RIGHT_GUI 	 B10000000

#define RAW_KEYBOARD_UP_ARROW		0x52
#define RAW_KEYBOARD_DOWN_ARROW		0x51
#define RAW_KEYBOARD_LEFT_ARROW		0x50
#define RAW_KEYBOARD_RIGHT_ARROW	0x4F
#define RAW_KEYBOARD_SPACEBAR		0x2C
#define RAW_KEYBOARD_BACKSPACE		0x2A
#define RAW_KEYBOARD_TAB			0x2B
#define RAW_KEYBOARD_RETURN			0x28
#define RAW_KEYBOARD_ESC			0x29
#define RAW_KEYBOARD_INSERT			0x49
#define RAW_KEYBOARD_DELETE			0x4C
#define RAW_KEYBOARD_PAGE_UP		0x4B
#define RAW_KEYBOARD_PAGE_DOWN		0x4E
#define RAW_KEYBOARD_HOME			0x4A
#define RAW_KEYBOARD_END			0x4D
#define RAW_KEYBOARD_CAPS_LOCK		0x39
#define RAW_KEYBOARD_F1				0x3A
#define RAW_KEYBOARD_F2				0x3B
#define RAW_KEYBOARD_F3				0x3C
#define RAW_KEYBOARD_F4				0x3D
#define RAW_KEYBOARD_F5				0x3E
#define RAW_KEYBOARD_F6				0x3F
#define RAW_KEYBOARD_F7				0x40
#define RAW_KEYBOARD_F8				0x41
#define RAW_KEYBOARD_F9				0x42
#define RAW_KEYBOARD_F10			0x43
#define RAW_KEYBOARD_F11			0x44
#define RAW_KEYBOARD_F12			0x45
#define RAW_KEYBOARD_PRINT			0x46
#define RAW_KEYBOARD_SCROLL_LOCK	0x47
#define RAW_KEYBOARD_PAUSE			0x48

#endif

