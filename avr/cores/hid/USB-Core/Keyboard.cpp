/*
Keyboard.cpp
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

#include "Keyboard.h"

//================================================================================
//================================================================================
//	Keyboard

Keyboard_ Keyboard;

void Keyboard_::sendReport(HID_KeyboardReport_Data_t* keys)
{
	HID_SendReport(HID_REPORTID_KEYBOARD, keys, sizeof(HID_KeyboardReport_Data_t));
}

extern
const uint8_t _asciimap[128] PROGMEM;

#define SHIFT 0x80
const uint8_t _asciimap[128] =
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

// press() adds the specified key (printing, non-printing, or modifier)
// to the persistent key report and sends the report.  Because of the way 
// USB HID works, the host acts like the key remains pressed until we 
// call release(), releaseAll(), or otherwise clear the report and resend.
size_t Keyboard_::press(uint8_t k)
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
		if (k & SHIFT) {						// it's a capital letter or other character reached with shift
			_keyReport.modifiers |= 0x02;	// the left shift modifier
			k = k ^ SHIFT;
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
size_t Keyboard_::release(uint8_t k)
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
		if (k & SHIFT) {							// it's a capital letter or other character reached with shift
			_keyReport.modifiers &= ~(0x02);	// the left shift modifier
			k = k ^ SHIFT;
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

void Keyboard_::releaseAll(void)
{
	// release all keys
	memset(&_keyReport, 0x00, sizeof(_keyReport));
	sendReport(&_keyReport);
}

size_t Keyboard_::write(uint8_t c)
{
	uint8_t p = press(c);  // Keydown
	release(c);            // Keyup
	return p;              // just return the result of press() since release() almost always returns 1
}


// pressKeycode() adds the specified key (printing, non-printing, or modifier)
// to the persistent key report and sends the report.  Because of the way 
// USB HID works, the host acts like the key remains pressed until we 
// call releaseKeycode(), releaseAll(), or otherwise clear the report and resend.
size_t Keyboard_::pressKeycode(uint8_t k)
{
	if (!addKeycodeToReport(k)) {
		return 0;
	}
	sendReport(&_keyReport);
}

size_t Keyboard_::addKeycodeToReport(uint8_t k)
{
	uint8_t index = 0;
	uint8_t done = 0;

	if ((k >= HID_KEYBOARD_LEFT_CONTROL) && (k <= HID_KEYBOARD_RIGHT_GUI)) {
		// it's a modifier key
		_keyReport.modifiers |= (0x01 << (k - HID_KEYBOARD_LEFT_CONTROL));
	}
	else {
		// it's some other key:
		// Add k to the key report only if it's not already present
		// and if there is an empty slot.
		for (index = 0; index < sizeof(_keyReport.keys); index++) {
			if (_keyReport.keys[index] != k) { // is k already in list?
				if (0 == _keyReport.keys[index]) { // have we found an empty slot?
					_keyReport.keys[index] = k;
					done = 1;
					break;
				}
			}
			else {
				done = 1;
				break;
			}

		}

		// use separate variable to check if slot was found
		// for style reasons - we do not know how the compiler
		// handles the for() index when it leaves the loop
		if (0 == done) {
			setWriteError();
			return 0;
		}
	}

	return 1;
}


// releaseKeycode() takes the specified key out of the persistent key report and
// sends the report.  This tells the OS the key is no longer pressed and that
// it shouldn't be repeated any more.
// When send is set to FALSE (= 0) no sendReport() is executed. This comes in
// handy when combining key releases (e.g. SHIFT+A).
size_t Keyboard_::releaseKeycode(uint8_t k)
{
	if (!removeKeycodeFromReport(k)) {
		return 0;
	}
	sendReport(&_keyReport);
}

size_t Keyboard_::removeKeycodeFromReport(uint8_t k)
{
	uint8_t indexA;
	uint8_t indexB;
	uint8_t count;

	if ((k >= HID_KEYBOARD_LEFT_CONTROL) && (k <= HID_KEYBOARD_RIGHT_GUI)) {
		// it's a modifier key
		_keyReport.modifiers = _keyReport.modifiers & (~(0x01 << (k - HID_KEYBOARD_LEFT_CONTROL)));
	}
	else {
		// it's some other key:
		// Test the key report to see if k is present.  Clear it if it exists.
		// Check all positions in case the key is present more than once (which it shouldn't be)
		for (indexA = 0; indexA < sizeof(_keyReport.keys); indexA++) {
			if (_keyReport.keys[indexA] == k) {
				_keyReport.keys[indexA] = 0;
			}
		}

		// finally rearrange the keys list so that the free (= 0x00) are at the
		// end of the keys list - some implementations stop for keys at the
		// first occurence of an 0x00 in the keys list
		// so (0x00)(0x01)(0x00)(0x03)(0x02)(0x00) becomes 
		//    (0x01)(0x03)(0x02)(0x00)(0x00)(0x00)
		count = 0; // holds the number of zeros we've found
		indexA = 0;
		while ((indexA + count) < sizeof(_keyReport.keys)) {
			if (0 == _keyReport.keys[indexA]) {
				count++; // one more zero
				for (indexB = indexA; indexB < sizeof(_keyReport.keys) - count; indexB++) {
					_keyReport.keys[indexB] = _keyReport.keys[indexB + 1];
				}
				_keyReport.keys[sizeof(_keyReport.keys) - count] = 0;
			}
			else {
				indexA++; // one more non-zero
			}
		}
	}

	return 1;
}


size_t Keyboard_::writeKeycode(uint8_t c)
{
	uint8_t p = pressKeycode(c);	// Keydown
	releaseKeycode(c);				// Keyup
	return (p);						// just return the result of pressKeycode() since release() almost always returns 1
}