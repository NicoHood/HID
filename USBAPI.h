/*
  USBAPI.h
  Copyright (c) 2005-2014 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
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

#ifndef __USBAPI__
#define __USBAPI__

#include <inttypes.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include <avr/interrupt.h>
#include <util/delay.h>

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

#include "Arduino.h"

#ifdef USBCON
// include needed HID devices
// the more you activate, the more flash it will take
// by default only Mouse + Keyboard are activated
#define HID_MOUSE_ENABLED
#define HID_KEYBOARD_ENABLED
//#define HID_KEYBOARD_LEDS_ENABLED

//#define HID_RAWHID_ENABLED
//#define HID_MEDIA_ENABLED
//#define HID_SYSTEM_ENABLED
//#define HID_GAMEPAD_ENABLED

// calculate HID report size for each device

#ifdef HID_MOUSE_ENABLED
#define HID_MOUSE_SIZE 54
#else
#define HID_MOUSE_SIZE 0
#endif

#ifdef HID_KEYBOARD_ENABLED
#define HID_KEYBOARD_SIZE (65-18) //18 for missing led out report = 47

#if defined USBCON && defined(HID_KEYBOARD_ENABLED) && defined(HID_KEYBOARD_LEDS_ENABLED)
// extern accessible led out report
extern uint8_t hid_keyboard_leds;

#define LED_NUM_LOCK			0x01
#define LED_CAPS_LOCK			0x02
#define LED_SCROLL_LOCK			0x04
#endif
#else
#define HID_KEYBOARD_SIZE 0
#endif

#ifdef HID_RAWHID_ENABLED
#define HID_RAWHID_SIZE 30
#else
#define HID_RAWHID_SIZE 0
#endif

#ifdef HID_MEDIA_ENABLED
#define HID_MEDIA_SIZE 25
#else
#define HID_MEDIA_SIZE 0
#endif

#ifdef HID_SYSTEM_ENABLED
#define HID_SYSTEM_SIZE 24
#else
#define HID_SYSTEM_SIZE 0
#endif

#ifdef HID_GAMEPAD_ENABLED
#define HID_GAMEPAD_SIZE 80
#else
#define HID_GAMEPAD_SIZE 0
#endif

// check if usb descriptor isn't too big for USBCore (seems to not work properly then)
#define HID_DESCRIPTOR_SIZE (HID_MOUSE_SIZE + HID_KEYBOARD_SIZE + HID_RAWHID_SIZE + \
HID_MEDIA_SIZE + HID_SYSTEM_SIZE + HID_GAMEPAD_SIZE + 0)
#if (HID_DESCRIPTOR_SIZE >= 256)
#error Please do not use HID reports >= 256 bytes. Edit USBAPI.h and remove some devices, please.
#endif

#else // ifdef USBCON

// still use USE_USB_API sending API to be able to overwrite the HID_SendReport function
#define USE_USB_API 

// activate all API's
#define HID_MOUSE_ENABLED
#define HID_KEYBOARD_ENABLED
#define HID_RAWHID_ENABLED
#define HID_MEDIA_ENABLED
#define HID_SYSTEM_ENABLED
#define HID_GAMEPAD_ENABLED

#endif

/** Enum for the HID report IDs used in the device. */
typedef enum{
	HID_REPORTID_NotAReport = 0x00,		/**< first entry is always zero for multireports */
	HID_REPORTID_MouseReport = 0x01,		/**< Report ID for the Mouse report within the device. */
	HID_REPORTID_KeyboardReport = 0x02,		/**< Report ID for the Keyboard report within the device. */
	HID_REPORTID_RawKeyboardReport = 0x03,		/**< Report ID for the Raw Keyboard report within the device. */
	HID_REPORTID_MediaReport = 0x04,		/**< Report ID for the Media report within the device. */
	HID_REPORTID_SystemReport = 0x05,		/**< Report ID for the Power report within the device. */
	HID_REPORTID_GamepadReport = 0x06,		/**< Report ID for the Gamepad report within the device. */
} HID_Report_IDs;

// usb core functions
#if defined(USBCON)

#include "USBDesc.h"
#include "USBCore.h"

//================================================================================
//================================================================================
//	USB

class USBDevice_
{
public:
	USBDevice_();
	bool configured();

	void attach();
	void detach();	// Serial port goes down too...
	void poll();
};
extern USBDevice_ USBDevice;

//================================================================================
//================================================================================
//	Serial over CDC (Serial1 is the physical port)

struct ring_buffer;

#if (RAMEND < 1000)
#define SERIAL_BUFFER_SIZE 16
#else
#define SERIAL_BUFFER_SIZE 64
#endif

class Serial_ : public Stream
{
private:
	int peek_buffer;
public:
	Serial_() { peek_buffer = -1; };
	void begin(unsigned long);
	void begin(unsigned long, uint8_t);
	void end(void);

	// edit by NicoHood
	uint8_t lineState(void);

	virtual int available(void);
	virtual int peek(void);
	virtual int read(void);
	virtual void flush(void);
	virtual size_t write(uint8_t);
	virtual size_t write(const uint8_t*, size_t);
	using Print::write; // pull in write(str) and write(buf, size) from Print
	operator bool();

	volatile uint8_t _rx_buffer_head;
	volatile uint8_t _rx_buffer_tail;
	unsigned char _rx_buffer[SERIAL_BUFFER_SIZE];
};
extern Serial_ Serial;

#define HAVE_CDCSERIAL

//================================================================================
//================================================================================
//	Low level API

typedef struct
{
	uint8_t bmRequestType;
	uint8_t bRequest;
	uint8_t wValueL;
	uint8_t wValueH;
	uint16_t wIndex;
	uint16_t wLength;
} Setup;

//================================================================================
//================================================================================
//	HID 'Driver'

int		HID_GetInterface(uint8_t* interfaceNum);
int		HID_GetDescriptor(int i);
bool	HID_Setup(Setup& setup);
void	HID_SendReport(uint8_t id, const void* data, int len);

//================================================================================
//================================================================================
//	MSC 'Driver'

int		MSC_GetInterface(uint8_t* interfaceNum);
int		MSC_GetDescriptor(int i);
bool	MSC_Setup(Setup& setup);
bool	MSC_Data(uint8_t rx, uint8_t tx);

//================================================================================
//================================================================================
//	CSC 'Driver'

int		CDC_GetInterface(uint8_t* interfaceNum);
int		CDC_GetDescriptor(int i);
bool	CDC_Setup(Setup& setup);

//================================================================================
//================================================================================

#define TRANSFER_PGM		0x80
#define TRANSFER_RELEASE	0x40
#define TRANSFER_ZERO		0x20

int USB_SendControl(uint8_t flags, const void* d, int len);
int USB_RecvControl(void* d, int len);

uint8_t	USB_Available(uint8_t ep);
int USB_Send(uint8_t ep, const void* data, int len);	// blocking
int USB_Recv(uint8_t ep, void* data, int len);		// non-blocking
int USB_Recv(uint8_t ep);							// non-blocking
void USB_Flush(uint8_t ep);


#else if defined(USE_USB_API)

// still provide the weak HID_SendReport function to be able to overwrite it externaly
void HID_SendReport(uint8_t id, const void* data, int len);

#endif /* if defined(USBCON) */

// HID API libs are only included if the device has USB functionality or if the USE_USB_API is needed
#if defined(USBCON) || defined(USE_USB_API)

//================================================================================
// Mouse
//================================================================================

#ifdef HID_MOUSE_ENABLED

#define MOUSE_LEFT		0x01
#define MOUSE_RIGHT		0x02
#define MOUSE_MIDDLE	0x04
#define MOUSE_PREV		0x08
#define MOUSE_NEXT		0x10
#define MOUSE_ALL (MOUSE_LEFT | MOUSE_RIGHT | MOUSE_MIDDLE | MOUSE_PREV | MOUSE_NEXT)

typedef union{
	// mouse report: 5 buttons, position, wheel
	uint8_t whole8[4];
	uint16_t whole16[4 / 2];
	uint32_t whole32[4 / 4];

	struct{
		uint8_t buttons : 5;
		uint8_t reserved : 3;
		int8_t xAxis;
		int8_t yAxis;
		int8_t wheel;
	};
} HID_MouseReport_Data_t;

class Mouse_
{
public:
	inline Mouse_(void) {
		// removed this to avoid creating an instance of Mouse if not needed
		// the user should call begin first.
		//: _buttons(0){
		// empty
	}

	inline void begin(void){
		// release all buttons
		end();
	}

	inline void end(void){
		_buttons = 0;
		move(0, 0, 0);
	}

	inline void click(uint8_t b = MOUSE_LEFT){
		_buttons = b;
		move(0, 0, 0);
		_buttons = 0;
		move(0, 0, 0);
	}

	inline void move(signed char x, signed char y, signed char wheel = 0){
		u8 m[4];
		m[0] = _buttons;
		m[1] = x;
		m[2] = y;
		m[3] = wheel;
		HID_SendReport(1, m, 4);
	}

	inline void press(uint8_t b = MOUSE_LEFT){
		// press LEFT by default
		buttons(_buttons | b);
	}

	inline void release(uint8_t b = MOUSE_LEFT){
		// release LEFT by default
		buttons(_buttons & ~b);
	}

	inline bool isPressed(uint8_t b = MOUSE_LEFT){
		// check LEFT by default
		if ((b & _buttons) > 0)
			return true;
		return false;
	}

private:
	uint8_t _buttons;
	inline void buttons(uint8_t b){
		if (b != _buttons)
		{
			_buttons = b;
			move(0, 0, 0);
		}
	}
};
extern Mouse_ Mouse;

#endif


//================================================================================
// Keyboard
//================================================================================

#ifdef HID_KEYBOARD_ENABLED

//Keyboard fixed/added missing Keys
#define KEY_PRINT			0xCE
#define KEY_NUM_LOCK		0xDB
#define KEY_SCROLL_LOCK		0xCF
#define KEY_PAUSE			0xD0

#define KEY_LEFT_CTRL		0x80
#define KEY_LEFT_SHIFT		0x81
#define KEY_LEFT_ALT		0x82
#define KEY_LEFT_GUI		0x83
#define KEY_LEFT_WINDOWS KEY_LEFT_GUI
#define KEY_RIGHT_CTRL		0x84
#define KEY_RIGHT_SHIFT		0x85
#define KEY_RIGHT_ALT		0x86
#define KEY_RIGHT_GUI		0x87
#define KEY_RIGHT_WINDOWS KEY_RIGHT_GUI

#define KEY_UP_ARROW		0xDA
#define KEY_DOWN_ARROW		0xD9
#define KEY_LEFT_ARROW		0xD8
#define KEY_RIGHT_ARROW		0xD7
#define KEY_BACKSPACE		0xB2
#define KEY_TAB				0xB3
#define KEY_RETURN			0xB0
#define KEY_ENTER KEY_RETURN
#define KEY_ESC				0xB1
#define KEY_INSERT			0xD1
#define KEY_DELETE			0xD4
#define KEY_PAGE_UP			0xD3
#define KEY_PAGE_DOWN		0xD6
#define KEY_HOME			0xD2
#define KEY_END				0xD5
#define KEY_CAPS_LOCK		0xC1
#define KEY_F1				0xC2
#define KEY_F2				0xC3
#define KEY_F3				0xC4
#define KEY_F4				0xC5
#define KEY_F5				0xC6
#define KEY_F6				0xC7
#define KEY_F7				0xC8
#define KEY_F8				0xC9
#define KEY_F9				0xCA
#define KEY_F10				0xCB
#define KEY_F11				0xCC
#define KEY_F12				0xCD

//Raw Keyboard definitions
#define RAW_KEYBOARD_LEFT_CTRL   B00000001
#define RAW_KEYBOARD_LEFT_SHIFT  B00000010
#define RAW_KEYBOARD_LEFT_ALT    B00000100
#define RAW_KEYBOARD_LEFT_GUI  	 B00001000
#define RAW_KEYBOARD_RIGHT_CTRL  B00010000
#define RAW_KEYBOARD_RIGHT_SHIFT B00100000
#define RAW_KEYBOARD_RIGHT_ALT   B01000000
#define RAW_KEYBOARD_RIGHT_GUI 	 B10000000

#define RAW_KEYBOARD_KEY(key) ((key>='a' && key<='z') ? (0x04 + key-'a') :\
(key>='A' && key<='Z') ? (0x04 + key-'A') : (key>='1' && key<='9') ? (0x1E + key-'1') : 0x27)

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

#define SHIFT 0x80
static const uint8_t _asciimap[128] PROGMEM =
{
	0x00,             // NUL
	0x00,             // SOH
	0x00,             // STX
	0x00,             // ETX
	0x00,             // EOT
	0x00,             // ENQ
	0x00,             // ACK  
	0x00,             // BEL
	0x2a,			// BS	Backspace
	0x2b,			// TAB	Tab
	0x28,			// LF	Enter
	0x00,             // VT 
	0x00,             // FF 
	0x00,             // CR 
	0x00,             // SO 
	0x00,             // SI 
	0x00,             // DEL
	0x00,             // DC1
	0x00,             // DC2
	0x00,             // DC3
	0x00,             // DC4
	0x00,             // NAK
	0x00,             // SYN
	0x00,             // ETB
	0x00,             // CAN
	0x00,             // EM 
	0x00,             // SUB
	0x00,             // ESC
	0x00,             // FS 
	0x00,             // GS 
	0x00,             // RS 
	0x00,             // US 

	0x2c,		   //  ' '
	0x1e | SHIFT,	   // !
	0x34 | SHIFT,	   // "
	0x20 | SHIFT,    // #
	0x21 | SHIFT,    // $
	0x22 | SHIFT,    // %
	0x24 | SHIFT,    // &
	0x34,          // '
	0x26 | SHIFT,    // (
	0x27 | SHIFT,    // )
	0x25 | SHIFT,    // *
	0x2e | SHIFT,    // +
	0x36,          // ,
	0x2d,          // -
	0x37,          // .
	0x38,          // /
	0x27,          // 0
	0x1e,          // 1
	0x1f,          // 2
	0x20,          // 3
	0x21,          // 4
	0x22,          // 5
	0x23,          // 6
	0x24,          // 7
	0x25,          // 8
	0x26,          // 9
	0x33 | SHIFT,      // :
	0x33,          // ;
	0x36 | SHIFT,      // <
	0x2e,          // =
	0x37 | SHIFT,      // >
	0x38 | SHIFT,      // ?
	0x1f | SHIFT,      // @
	0x04 | SHIFT,      // A
	0x05 | SHIFT,      // B
	0x06 | SHIFT,      // C
	0x07 | SHIFT,      // D
	0x08 | SHIFT,      // E
	0x09 | SHIFT,      // F
	0x0a | SHIFT,      // G
	0x0b | SHIFT,      // H
	0x0c | SHIFT,      // I
	0x0d | SHIFT,      // J
	0x0e | SHIFT,      // K
	0x0f | SHIFT,      // L
	0x10 | SHIFT,      // M
	0x11 | SHIFT,      // N
	0x12 | SHIFT,      // O
	0x13 | SHIFT,      // P
	0x14 | SHIFT,      // Q
	0x15 | SHIFT,      // R
	0x16 | SHIFT,      // S
	0x17 | SHIFT,      // T
	0x18 | SHIFT,      // U
	0x19 | SHIFT,      // V
	0x1a | SHIFT,      // W
	0x1b | SHIFT,      // X
	0x1c | SHIFT,      // Y
	0x1d | SHIFT,      // Z
	0x2f,          // [
	0x31,          // bslash
	0x30,          // ]
	0x23 | SHIFT,    // ^
	0x2d | SHIFT,    // _
	0x35,          // `
	0x04,          // a
	0x05,          // b
	0x06,          // c
	0x07,          // d
	0x08,          // e
	0x09,          // f
	0x0a,          // g
	0x0b,          // h
	0x0c,          // i
	0x0d,          // j
	0x0e,          // k
	0x0f,          // l
	0x10,          // m
	0x11,          // n
	0x12,          // o
	0x13,          // p
	0x14,          // q
	0x15,          // r
	0x16,          // s
	0x17,          // t
	0x18,          // u
	0x19,          // v
	0x1a,          // w
	0x1b,          // x
	0x1c,          // y
	0x1d,          // z
	0x2f | SHIFT,    // 
	0x31 | SHIFT,    // |
	0x30 | SHIFT,    // }
	0x35 | SHIFT,    // ~
	0				// DEL
};

typedef union{
	// Low level key report: up to 6 keys and shift, ctrl etc at once
	uint8_t whole8[8];
	uint16_t whole16[8 / 2];
	uint32_t whole32[8 / 4];

	struct{
		uint8_t modifiers;
		uint8_t reserved;
		uint8_t keys[6];
	};
} HID_KeyboardReport_Data_t;

class Keyboard_ : public Print{
public:
	inline Keyboard_(void){
		// empty
	}

	inline void begin(void){
		end();
	}

	inline void end(void){
		// edit by NicoHood
		releaseAll();
	}

#if defined(HID_KEYBOARD_LEDS_ENABLED)
	inline uint8_t getLEDs(void){
		return hid_keyboard_leds;
	}
#endif

	inline size_t write(uint8_t c){
		uint8_t p = press(c);		// Keydown
		release(c);					// Keyup
		return (p);					// just return the result of press() since release() almost always returns 1
	}

	// press() adds the specified key (printing, non-printing, or modifier)
	// to the persistent key report and sends the report.  Because of the way 
	// USB HID works, the host acts like the key remains pressed until we 
	// call release(), releaseAll(), or otherwise clear the report and resend.
	inline size_t press(uint8_t k)
	{
		uint8_t i;
		if (k >= 136) {			// it's a non-printing key (not a modifier)
			k = k - 136;
		}
		else if (k >= 128) {	// it's a modifier key
			_keyReport.modifiers |= (1 << (k - 128));
			k = 0;
		}
		else {				// it's a printing key
			k = pgm_read_byte(_asciimap + k);
			if (!k) {
				setWriteError();
				return 0;
			}
			if (k & 0x80) {						// it's a capital letter or other character reached with shift
				_keyReport.modifiers |= 0x02;	// the left shift modifier
				k &= 0x7F;
			}
		}

		// Add k to the key report only if it's not already present
		// and if there is an empty slot.
		if (_keyReport.keys[0] != k && _keyReport.keys[1] != k &&
			_keyReport.keys[2] != k && _keyReport.keys[3] != k &&
			_keyReport.keys[4] != k && _keyReport.keys[5] != k) {

			for (i = 0; i < 6; i++) {
				if (_keyReport.keys[i] == 0x00) {
					_keyReport.keys[i] = k;
					break;
				}
			}
			if (i == 6) {
				setWriteError();
				return 0;
			}
		}
		sendReport(&_keyReport);
		return 1;
	}

	// release() takes the specified key out of the persistent key report and
	// sends the report.  This tells the OS the key is no longer pressed and that
	// it shouldn't be repeated any more.
	inline size_t release(uint8_t k)
	{
		uint8_t i;
		if (k >= 136) {			// it's a non-printing key (not a modifier)
			k = k - 136;
		}
		else if (k >= 128) {	// it's a modifier key
			_keyReport.modifiers &= ~(1 << (k - 128));
			k = 0;
		}
		else {				// it's a printing key
			k = pgm_read_byte(_asciimap + k);
			if (!k) {
				return 0;
			}
			if (k & 0x80) {							// it's a capital letter or other character reached with shift
				_keyReport.modifiers &= ~(0x02);	// the left shift modifier
				k &= 0x7F;
			}
		}

		// Test the key report to see if k is present.  Clear it if it exists.
		// Check all positions in case the key is present more than once (which it shouldn't be)
		for (i = 0; i < 6; i++) {
			if (0 != k && _keyReport.keys[i] == k) {
				_keyReport.keys[i] = 0x00;
			}
		}

		sendReport(&_keyReport);
		return 1;
	}

	inline void releaseAll(void){
		// release all keys
		memset(&_keyReport, 0x00, sizeof(_keyReport));
		sendReport(&_keyReport);
	}

private:
	HID_KeyboardReport_Data_t _keyReport;
	inline void sendReport(HID_KeyboardReport_Data_t* keys){
		HID_SendReport(HID_REPORTID_KeyboardReport, &_keyReport, sizeof(_keyReport));
	}
};
extern Keyboard_ Keyboard;

#endif


//================================================================================
// RawHID
//================================================================================

#ifdef HID_RAWHID_ENABLED

#define LSB(_x) ((_x) & 0xFF)
#define MSB(_x) ((_x) >> 8)

//TODO
#define RAWHID_USAGE_PAGE	0xFFC0 // recommended: 0xFF00 to 0xFFFF
#define RAWHID_USAGE		0x0C00 // recommended: 0x0100 to 0xFFFF
#define RAWHID_TX_SIZE 64 //TODO 16?
#define RAWHID_RX_SIZE 64
//#define RAWHID_TX_SIZE 15 // 1 byte for report ID
//#define RAWHID_RX_SIZE 15 // 1 byte for report ID

typedef union{
	// a RAWHID_TX_SIZE byte buffer for rx or tx
	uint8_t whole8[RAWHID_TX_SIZE];
	uint16_t whole16[RAWHID_TX_SIZE / 2];
	uint32_t whole32[RAWHID_TX_SIZE / 4];
	uint8_t buff[RAWHID_TX_SIZE];
} HID_RawKeyboardReport_Data_t;

class RawHID_ : public Print{
public:
	inline RawHID_(void){
		// empty
	}

	inline void begin(void){
		// empty
	}

	inline void end(void){
		// empty
	}

	using Print::write; // to get the String version of write
	inline size_t write(uint8_t b){
		write(&b, 1);
	}

	inline size_t write(const uint8_t *buffer, size_t size){
		size_t bytesleft = size;
		// first work through the buffer thats already there
		while (bytesleft >= RAWHID_RX_SIZE){
			HID_SendReport(HID_REPORTID_RawKeyboardReport, &buffer[size - bytesleft], RAWHID_RX_SIZE);
			bytesleft -= RAWHID_RX_SIZE;
		}
		// write down the other bytes and fill with zeros
		if (bytesleft){
			uint8_t rest[RAWHID_RX_SIZE];
			memcpy(rest, &buffer[size - bytesleft], bytesleft);
			memset(&rest[bytesleft], 0, RAWHID_RX_SIZE - bytesleft);
			HID_SendReport(HID_REPORTID_RawKeyboardReport, &rest, RAWHID_RX_SIZE);
		}
	}
};
extern RawHID_ RawHID;

#endif


//================================================================================
// Media
//================================================================================

#ifdef HID_MEDIA_ENABLED

// Media key definitions, see official USB docs for more
#define MEDIA_FAST_FORWARD		0xB3
#define MEDIA_REWIND			0xB4
#define MEDIA_NEXT				0xB5
#define MEDIA_PREVIOUS			0xB6
#define MEDIA_STOP				0xB7
#define MEDIA_PLAY_PAUSE		0xCD

#define MEDIA_VOLUME_MUTE		0xE2
#define MEDIA_VOLUME_UP			0xE9
#define MEDIA_VOLUME_DOWN		0xEA

#define MEDIA_EMAIL_READER		0x18A
#define MEDIA_CALCULATOR		0x192
#define MEDIA_EXPLORER			0x194

#define MEDIA_BROWSER_HOME		0x223
#define MEDIA_BROWSER_BACK		0x224
#define MEDIA_BROWSER_FORWARD	0x225
#define MEDIA_BROWSER_REFRESH	0x227
#define MEDIA_BROWSER_BOOKMARKS	0x22A

typedef union{
	// every usable media key possible, up to 4 keys presses possible
	uint8_t whole8[8];
	uint16_t whole16[8 / 2];
	uint32_t whole32[8 / 4];

	struct{
		uint16_t key1;
		uint16_t key2;
		uint16_t key3;
		uint16_t key4;
	};
} HID_MediaReport_Data_t;

class Media_{
public:
	inline Media_(void){
		// empty
	}

	inline void begin(void){
		// release all buttons
		end();
	}

	inline void end(void){
		memset(&_report, 0, sizeof(_report));
		HID_SendReport(HID_REPORTID_MediaReport, &_report, sizeof(_report));
	}

	inline void write(uint16_t m){
		press(m);
		release(m);
	}

	inline void press(uint16_t m){
		// search for a free spot
		for (int i = 0; i < sizeof(HID_MediaReport_Data_t) / 2; i++) {
			if (_report.whole16[i] == 0x00) {
				_report.whole16[i] = m;
				break;
			}
		}
		HID_SendReport(HID_REPORTID_MediaReport, &_report, sizeof(_report));
	}

	inline void release(uint16_t m){
		// search and release the keypress
		for (int i = 0; i < sizeof(HID_MediaReport_Data_t) / 2; i++) {
			if (_report.whole16[i] == m) {
				_report.whole16[i] = 0x00;
				// no break to delete multiple keys
			}
		}
		HID_SendReport(HID_REPORTID_MediaReport, &_report, sizeof(_report));
	}

	inline void releaseAll(void){
		begin();
	}
private:
	HID_MediaReport_Data_t _report;
};
extern Media_ Media;

#endif


//================================================================================
// System
//================================================================================

#ifdef HID_SYSTEM_ENABLED

#define SYSTEM_POWER_DOWN	0x81
#define SYSTEM_SLEEP		0x82
#define SYSTEM_WAKE_UP		0x83

typedef union{
	// every usable system control key possible
	uint8_t whole8[1];
	uint8_t key;
} HID_SystemReport_Data_t;

class System_{
public:
	inline System_(void){
		// empty
	}

	inline void begin(void){
		// release all buttons
		end();
	}

	inline void end(void){
		uint8_t _report = 0;
		HID_SendReport(HID_REPORTID_SystemReport, &_report, sizeof(_report));
	}

	inline void write(uint8_t s){
		press(s);
		release();
	}

	inline void press(uint8_t s){
		HID_SendReport(HID_REPORTID_SystemReport, &s, sizeof(s));
	}

	inline void release(void){
		begin();
	}

	inline void releaseAll(void){
		begin();
	}
};
extern System_ System;

#endif

//================================================================================
// Gamepad
//================================================================================

#ifdef HID_GAMEPAD_ENABLED

// Dpad directions
#define GAMEPAD_DPAD_CENTERED 0
#define GAMEPAD_DPAD_UP 1
#define GAMEPAD_DPAD_UP_RIGHT 2
#define GAMEPAD_DPAD_RIGHT 3
#define GAMEPAD_DPAD_DOWN_RIGHT 4
#define GAMEPAD_DPAD_DOWN 5
#define GAMEPAD_DPAD_DOWN_LEFT 6
#define GAMEPAD_DPAD_LEFT 7
#define GAMEPAD_DPAD_UP_LEFT 8

typedef union {
	// 32 Buttons, 6 Axis, 2 D-Pads
	uint8_t whole8[15];
	uint16_t whole16[15 / 2];
	uint32_t whole32[15 / 4];
	uint32_t buttons;

	struct{
		uint8_t button1 : 1;
		uint8_t button2 : 1;
		uint8_t button3 : 1;
		uint8_t button4 : 1;
		uint8_t button5 : 1;
		uint8_t button6 : 1;
		uint8_t button7 : 1;
		uint8_t button8 : 1;

		uint8_t button9 : 1;
		uint8_t button10 : 1;
		uint8_t button11 : 1;
		uint8_t button12 : 1;
		uint8_t button13 : 1;
		uint8_t button14 : 1;
		uint8_t button15 : 1;
		uint8_t button16 : 1;

		uint8_t button17 : 1;
		uint8_t button18 : 1;
		uint8_t button19 : 1;
		uint8_t button20 : 1;
		uint8_t button21 : 1;
		uint8_t button22 : 1;
		uint8_t button23 : 1;
		uint8_t button24 : 1;

		uint8_t button25 : 1;
		uint8_t button26 : 1;
		uint8_t button27 : 1;
		uint8_t button28 : 1;
		uint8_t button29 : 1;
		uint8_t button30 : 1;
		uint8_t button31 : 1;
		uint8_t button32 : 1;

		int16_t	xAxis;
		int16_t	yAxis;

		int16_t	rxAxis;
		int16_t	ryAxis;

		int8_t	zAxis;
		int8_t	rzAxis;

		uint8_t		dPad1 : 4;
		uint8_t		dPad2 : 4;
	};
} HID_GamepadReport_Data_t;

class Gamepad_{
public:
	inline Gamepad_(void){
		// empty
	}

	inline void begin(void){
		// release all buttons
		end();
	}

	inline void end(void){
		memset(&_report, 0, sizeof(_report));
		HID_SendReport(HID_REPORTID_GamepadReport, &_report, sizeof(_report));
	}

	inline void write(void){ HID_SendReport(HID_REPORTID_GamepadReport, &_report, sizeof(_report)); }
	inline void press(uint8_t b){ _report.buttons |= (uint32_t)1 << (b - 1); }
	inline void release(uint8_t b){ _report.buttons &= ~((uint32_t)1 << (b - 1)); }
	inline void releaseAll(void){ memset(&_report, 0x00, sizeof(_report)); }

	inline void buttons(uint32_t b){ _report.buttons = b; }
	inline void xAxis(int16_t a){ _report.xAxis = a; }
	inline void yAxis(int16_t a){ _report.yAxis = a; }
	inline void zAxis(int8_t a){ _report.zAxis = a; }
	inline void rxAxis(int16_t a){ _report.rxAxis = a; }
	inline void ryAxis(int16_t a){ _report.ryAxis = a; }
	inline void rzAxis(int8_t a){ _report.rzAxis = a; }
	inline void dPad1(int8_t d){ _report.dPad1 = d; }
	inline void dPad2(int8_t d){ _report.dPad2 = d; }
private:
	HID_GamepadReport_Data_t _report;
};
extern Gamepad_ Gamepad;

#endif

#endif // if defined(USBCON) || defined(USE_USB_API)

#endif /* if defined(__USBAPI__) */
