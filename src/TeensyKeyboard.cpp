/* USB API for Teensy USB Development Board
 * http://www.pjrc.com/teensy/teensyduino.html
 * Copyright (c) 2008 PJRC.COM, LLC
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "TeensyKeyboard.h"

usb_keyboard_class::usb_keyboard_class(void){
	static HID_Descriptor cb = {
		.length = sizeof(keyboard_hid_report_desc),
		.descriptor = keyboard_hid_report_desc,
	};
	static HIDDescriptorListNode node(&cb);
	HID.AppendDescriptor(&node);
}

// Step #1, decode UTF8 to Unicode code points
//
size_t usb_keyboard_class::write(uint8_t c)
{
	if (c < 0x80) {
		// single byte encoded, 0x00 to 0x7F
		utf8_state = 0;
		write_unicode(c);
	} else if (c < 0xC0) {
		// 2nd, 3rd or 4th byte, 0x80 to 0xBF
		c &= 0x3F;
		if (utf8_state == 1) {
			utf8_state = 0;
			write_unicode(unicode_wchar | c);
		} else if (utf8_state == 2) {
			unicode_wchar |= ((uint16_t)c << 6);
			utf8_state = 1;
		}
	} else if (c < 0xE0) {
		// begin 2 byte sequence, 0xC2 to 0xDF
		// or illegal 2 byte sequence, 0xC0 to 0xC1
		unicode_wchar = (uint16_t)(c & 0x1F) << 6;
		utf8_state = 1;
	} else if (c < 0xF0) {
		// begin 3 byte sequence, 0xE0 to 0xEF
		unicode_wchar = (uint16_t)(c & 0x0F) << 12;
		utf8_state = 2;
	} else {
		// begin 4 byte sequence (not supported), 0xF0 to 0xF4
		// or illegal, 0xF5 to 0xFF
		utf8_state = 255;
	}
	return 1;
}


// Step #2: translate Unicode code point to keystroke sequence
//
KEYCODE_TYPE usb_keyboard_class::unicode_to_keycode(uint16_t cpoint)
{
	// Unicode code points beyond U+FFFF are not supported
	// technically this input should probably be called UCS-2
	if (cpoint < 32) {
		if (cpoint == 10) return KEY_ENTER & 0x3FFF;
		return 0;
	}
	if (cpoint < 128) {
		if (sizeof(KEYCODE_TYPE) == 1) {
			return pgm_read_byte(keycodes_ascii + (cpoint - 0x20));
		} else if (sizeof(KEYCODE_TYPE) == 2) {
			return pgm_read_word(keycodes_ascii + (cpoint - 0x20));
		}
		return 0;
	}
	#ifdef ISO_8859_1_A0
	if (cpoint <= 0xA0) return 0;
	if (cpoint < 0x100) {
		if (sizeof(KEYCODE_TYPE) == 1) {
			return pgm_read_byte(keycodes_iso_8859_1 + (cpoint - 0xA0));
		} else if (sizeof(KEYCODE_TYPE) == 2) {
			return pgm_read_word(keycodes_iso_8859_1 + (cpoint - 0xA0));
		}
		return 0;
	}
	#endif
	//#ifdef UNICODE_20AC
	//if (cpoint == 0x20AC) return UNICODE_20AC & 0x3FFF;
	//#endif
	#ifdef KEYCODE_EXTRA00
	if (cpoint == UNICODE_EXTRA00) return KEYCODE_EXTRA00 & 0x3FFF;
	#endif
	#ifdef KEYCODE_EXTRA01
	if (cpoint == UNICODE_EXTRA01) return KEYCODE_EXTRA01 & 0x3FFF;
	#endif
	#ifdef KEYCODE_EXTRA02
	if (cpoint == UNICODE_EXTRA02) return KEYCODE_EXTRA02 & 0x3FFF;
	#endif
	#ifdef KEYCODE_EXTRA03
	if (cpoint == UNICODE_EXTRA03) return KEYCODE_EXTRA03 & 0x3FFF;
	#endif
	#ifdef KEYCODE_EXTRA04
	if (cpoint == UNICODE_EXTRA04) return KEYCODE_EXTRA04 & 0x3FFF;
	#endif
	#ifdef KEYCODE_EXTRA05
	if (cpoint == UNICODE_EXTRA05) return KEYCODE_EXTRA05 & 0x3FFF;
	#endif
	#ifdef KEYCODE_EXTRA06
	if (cpoint == UNICODE_EXTRA06) return KEYCODE_EXTRA06 & 0x3FFF;
	#endif
	#ifdef KEYCODE_EXTRA07
	if (cpoint == UNICODE_EXTRA07) return KEYCODE_EXTRA07 & 0x3FFF;
	#endif
	#ifdef KEYCODE_EXTRA08
	if (cpoint == UNICODE_EXTRA08) return KEYCODE_EXTRA08 & 0x3FFF;
	#endif
	#ifdef KEYCODE_EXTRA09
	if (cpoint == UNICODE_EXTRA09) return KEYCODE_EXTRA09 & 0x3FFF;
	#endif
	return 0;
}

// Step #3: execute keystroke sequence
//
void usb_keyboard_class::write_keycode(KEYCODE_TYPE keycode)
{
	if (!keycode) return;
	#ifdef DEADKEYS_MASK
	KEYCODE_TYPE deadkeycode = deadkey_to_keycode(keycode);
	if (deadkeycode) write_key(deadkeycode);
	#endif
	write_key(keycode);
}

KEYCODE_TYPE usb_keyboard_class::deadkey_to_keycode(KEYCODE_TYPE keycode)
{
	#ifdef DEADKEYS_MASK
	keycode &= DEADKEYS_MASK;
	if (keycode == 0) return 0;
	#ifdef ACUTE_ACCENT_BITS
	if (keycode == ACUTE_ACCENT_BITS) return DEADKEY_ACUTE_ACCENT;
	#endif
	#ifdef CEDILLA_BITS
	if (keycode == CEDILLA_BITS) return DEADKEY_CEDILLA;
	#endif
	#ifdef CIRCUMFLEX_BITS
	if (keycode == CIRCUMFLEX_BITS) return DEADKEY_CIRCUMFLEX;
	#endif
	#ifdef DIAERESIS_BITS
	if (keycode == DIAERESIS_BITS) return DEADKEY_DIAERESIS;
	#endif
	#ifdef GRAVE_ACCENT_BITS
	if (keycode == GRAVE_ACCENT_BITS) return DEADKEY_GRAVE_ACCENT;
	#endif
	#ifdef TILDE_BITS
	if (keycode == TILDE_BITS) return DEADKEY_TILDE;
	#endif
	#ifdef RING_ABOVE_BITS
	if (keycode == RING_ABOVE_BITS) return DEADKEY_RING_ABOVE;
	#endif
	#endif // DEADKEYS_MASK
	return 0;
}

// Step #4: do each keystroke
//
void usb_keyboard_class::write_key(KEYCODE_TYPE keycode)
{
	keyboard_report_data[0] = keycode_to_modifier(keycode);
	keyboard_report_data[1] = 0;
	keyboard_report_data[2] = keycode_to_key(keycode);
	keyboard_report_data[3] = 0;
	keyboard_report_data[4] = 0;
	keyboard_report_data[5] = 0;
	keyboard_report_data[6] = 0;
	keyboard_report_data[7] = 0;
	send_now();
	keyboard_report_data[0] = 0;
	keyboard_report_data[2] = 0;
	send_now();
}

uint8_t usb_keyboard_class::keycode_to_modifier(KEYCODE_TYPE keycode)
{
	uint8_t modifier=0;

	#ifdef SHIFT_MASK
	if (keycode & SHIFT_MASK) modifier |= MODIFIERKEY_SHIFT;
	#endif
	#ifdef ALTGR_MASK
	if (keycode & ALTGR_MASK) modifier |= MODIFIERKEY_RIGHT_ALT;
	#endif
	#ifdef RCTRL_MASK
	if (keycode & RCTRL_MASK) modifier |= MODIFIERKEY_RIGHT_CTRL;
	#endif
	return modifier;
}

uint8_t usb_keyboard_class::keycode_to_key(KEYCODE_TYPE keycode)
{
	uint8_t key = keycode & 0x3F;
	#ifdef KEY_NON_US_100
	if (key == KEY_NON_US_100) key = 100;
	#endif
	return key;
}



void usb_keyboard_class::set_modifier(uint8_t c)
{
	keyboard_report_data[0] = c;
}
void usb_keyboard_class::set_key1(uint8_t c)
{
	keyboard_report_data[2] = c;
}
void usb_keyboard_class::set_key2(uint8_t c)
{
	keyboard_report_data[3] = c;
}
void usb_keyboard_class::set_key3(uint8_t c)
{
	keyboard_report_data[4] = c;
}
void usb_keyboard_class::set_key4(uint8_t c)
{
	keyboard_report_data[5] = c;
}
void usb_keyboard_class::set_key5(uint8_t c)
{
	keyboard_report_data[6] = c;
}
void usb_keyboard_class::set_key6(uint8_t c)
{
	keyboard_report_data[7] = c;
}
void usb_keyboard_class::set_media(uint8_t c)
{
	keyboard_report_data[1] = c;
}


void usb_keyboard_class::send_now(void)
{
	HID.SendReport(HID_REPORTID_KEYBOARD,keyboard_report_data,sizeof(keyboard_report_data));
}


void usb_keyboard_class::press(uint16_t n)
{
	uint8_t key, mod, msb, modrestore=0;

	msb = n >> 8;
	if (msb >= 0xC2 && msb <= 0xDF) {
		n = (n & 0x3F) | ((uint16_t)(msb & 0x1F) << 6);
	} else
	if (msb == 0x80) {
		presskey(0, n);
		return;
	} else
	if (msb == 0x40) {
		presskey(n, 0);
		return;
	}
	KEYCODE_TYPE keycode = unicode_to_keycode(n);
	if (!keycode) return;
	#ifdef DEADKEYS_MASK
	KEYCODE_TYPE deadkeycode = deadkey_to_keycode(keycode);
	if (deadkeycode) {
		modrestore = keyboard_report_data[0];
		if (modrestore) {
			keyboard_report_data[0] = 0;
			send_now();
		}
		// TODO: test if operating systems recognize
		// deadkey sequences when other keys are held
		mod = keycode_to_modifier(deadkeycode);
		key = keycode_to_key(deadkeycode);
		presskey(key, mod);
		releasekey(key, mod);
	}
	#endif
	mod = keycode_to_modifier(keycode);
	key = keycode_to_key(keycode);
	presskey(key, mod | modrestore);
}

void usb_keyboard_class::release(uint16_t n)
{
	uint8_t key, mod, msb;

	msb = n >> 8;
	if (msb >= 0xC2 && msb <= 0xDF) {
		n = (n & 0x3F) | ((uint16_t)(msb & 0x1F) << 6);
	} else
	if (msb == 0x80) {
		releasekey(0, n);
		return;
	} else
	if (msb == 0x40) {
		releasekey(n, 0);
		return;
	}
	KEYCODE_TYPE keycode = unicode_to_keycode(n);
	if (!keycode) return;
	mod = keycode_to_modifier(keycode);
	key = keycode_to_key(keycode);
	releasekey(key, mod);
}

void usb_keyboard_class::presskey(uint8_t key, uint8_t modifier)
{
	bool send_required = false;
	uint8_t i;

	if (modifier) {
		if ((keyboard_report_data[0] & modifier) != modifier) {
			keyboard_report_data[0] |= modifier;
			send_required = true;
		}
	}
	if (key) {
		for (i=2; i < 8; i++) {
			if (keyboard_report_data[i] == key) goto end;
		}
		for (i=2; i < 8; i++) {
			if (keyboard_report_data[i] == 0) {
				keyboard_report_data[i] = key;
				send_required = true;
				goto end;
			}
		}
	}
	end:
	if (send_required) send_now();
}

void usb_keyboard_class::releasekey(uint8_t key, uint8_t modifier)
{
	bool send_required = false;
	uint8_t i;

	if (modifier) {
		if ((keyboard_report_data[0] & modifier) != 0) {
			keyboard_report_data[0] &= ~modifier;
			send_required = true;
		}
	}
	if (key) {
		for (i=2; i < 8; i++) {
			if (keyboard_report_data[i] == key) {
				keyboard_report_data[i] = 0;
				send_required = true;
			}
		}
	}
	if (send_required) send_now();
}

void usb_keyboard_class::releaseAll(void)
{
	uint8_t i, anybits;

	anybits = keyboard_report_data[0];
	for (i=2; i < 8; i++) {
		anybits |= keyboard_report_data[i];
		keyboard_report_data[i] = 0;
	}
	if (!anybits) return;
	keyboard_report_data[0] = 0;
	send_now();
}

usb_keyboard_class	TeensyKeyboard = usb_keyboard_class();
