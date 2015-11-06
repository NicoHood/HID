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

// Step #1, decode UTF8 to Unicode code points
//
size_t TeensyKeyboardAPI::write(uint8_t c)
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
KEYCODE_TYPE TeensyKeyboardAPI::unicode_to_keycode(uint16_t cpoint)
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
void TeensyKeyboardAPI::write_keycode(KEYCODE_TYPE keycode)
{
	if (!keycode) return;
	#ifdef DEADKEYS_MASK
	KEYCODE_TYPE deadkeycode = deadkey_to_keycode(keycode);
	if (deadkeycode) write_key(deadkeycode);
	#endif
	write_key(keycode);
}

KEYCODE_TYPE TeensyKeyboardAPI::deadkey_to_keycode(KEYCODE_TYPE keycode)
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
void TeensyKeyboardAPI::write_key(KEYCODE_TYPE keycode)
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

uint8_t TeensyKeyboardAPI::keycode_to_modifier(KEYCODE_TYPE keycode)
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

uint8_t TeensyKeyboardAPI::keycode_to_key(KEYCODE_TYPE keycode)
{
	uint8_t key = keycode & 0x3F;
	#ifdef KEY_NON_US_100
	if (key == KEY_NON_US_100) key = 100;
	#endif
	return key;
}



void TeensyKeyboardAPI::set_modifier(uint8_t c)
{
	keyboard_report_data[0] = c;
}
void TeensyKeyboardAPI::set_key1(uint8_t c)
{
	keyboard_report_data[2] = c;
}
void TeensyKeyboardAPI::set_key2(uint8_t c)
{
	keyboard_report_data[3] = c;
}
void TeensyKeyboardAPI::set_key3(uint8_t c)
{
	keyboard_report_data[4] = c;
}
void TeensyKeyboardAPI::set_key4(uint8_t c)
{
	keyboard_report_data[5] = c;
}
void TeensyKeyboardAPI::set_key5(uint8_t c)
{
	keyboard_report_data[6] = c;
}
void TeensyKeyboardAPI::set_key6(uint8_t c)
{
	keyboard_report_data[7] = c;
}
void TeensyKeyboardAPI::set_media(uint8_t c)
{
	keyboard_report_data[1] = c;
}


void TeensyKeyboardAPI::send_now(void)
{
	sendReport(keyboard_report_data, sizeof(keyboard_report_data));
}


void TeensyKeyboardAPI::press(uint16_t n)
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

void TeensyKeyboardAPI::release(uint16_t n)
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

void TeensyKeyboardAPI::presskey(uint8_t key, uint8_t modifier)
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

void TeensyKeyboardAPI::releasekey(uint8_t key, uint8_t modifier)
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

void TeensyKeyboardAPI::releaseAll(void)
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

#include <avr/pgmspace.h>
#include <stdint.h>

#ifdef M
#undef M
#endif
#define M(n) ((n) & 0x3FFF)

const KEYCODE_TYPE PROGMEM keycodes_ascii[] = {
        M(ASCII_20), M(ASCII_21), M(ASCII_22), M(ASCII_23),
        M(ASCII_24), M(ASCII_25), M(ASCII_26), M(ASCII_27),
        M(ASCII_28), M(ASCII_29), M(ASCII_2A), M(ASCII_2B),
        M(ASCII_2C), M(ASCII_2D), M(ASCII_2E), M(ASCII_2F),
        M(ASCII_30), M(ASCII_31), M(ASCII_32), M(ASCII_33),
        M(ASCII_34), M(ASCII_35), M(ASCII_36), M(ASCII_37),
        M(ASCII_38), M(ASCII_39), M(ASCII_3A), M(ASCII_3B),
        M(ASCII_3C), M(ASCII_3D), M(ASCII_3E), M(ASCII_3F),
        M(ASCII_40), M(ASCII_41), M(ASCII_42), M(ASCII_43),
        M(ASCII_44), M(ASCII_45), M(ASCII_46), M(ASCII_47),
        M(ASCII_48), M(ASCII_49), M(ASCII_4A), M(ASCII_4B),
        M(ASCII_4C), M(ASCII_4D), M(ASCII_4E), M(ASCII_4F),
        M(ASCII_50), M(ASCII_51), M(ASCII_52), M(ASCII_53),
        M(ASCII_54), M(ASCII_55), M(ASCII_56), M(ASCII_57),
        M(ASCII_58), M(ASCII_59), M(ASCII_5A), M(ASCII_5B),
        M(ASCII_5C), M(ASCII_5D), M(ASCII_5E), M(ASCII_5F),
        M(ASCII_60), M(ASCII_61), M(ASCII_62), M(ASCII_63),
        M(ASCII_64), M(ASCII_65), M(ASCII_66), M(ASCII_67),
        M(ASCII_68), M(ASCII_69), M(ASCII_6A), M(ASCII_6B),
        M(ASCII_6C), M(ASCII_6D), M(ASCII_6E), M(ASCII_6F),
        M(ASCII_70), M(ASCII_71), M(ASCII_72), M(ASCII_73),
        M(ASCII_74), M(ASCII_75), M(ASCII_76), M(ASCII_77),
        M(ASCII_78), M(ASCII_79), M(ASCII_7A), M(ASCII_7B),
        M(ASCII_7C), M(ASCII_7D), M(ASCII_7E), M(ASCII_7F)
};      

#ifdef ISO_8859_1_A0
const KEYCODE_TYPE PROGMEM keycodes_iso_8859_1[] = {
        M(ISO_8859_1_A0), M(ISO_8859_1_A1), M(ISO_8859_1_A2), M(ISO_8859_1_A3),
        M(ISO_8859_1_A4), M(ISO_8859_1_A5), M(ISO_8859_1_A6), M(ISO_8859_1_A7),
        M(ISO_8859_1_A8), M(ISO_8859_1_A9), M(ISO_8859_1_AA), M(ISO_8859_1_AB),
        M(ISO_8859_1_AC), M(ISO_8859_1_AD), M(ISO_8859_1_AE), M(ISO_8859_1_AF),
        M(ISO_8859_1_B0), M(ISO_8859_1_B1), M(ISO_8859_1_B2), M(ISO_8859_1_B3),
        M(ISO_8859_1_B4), M(ISO_8859_1_B5), M(ISO_8859_1_B6), M(ISO_8859_1_B7),
        M(ISO_8859_1_B8), M(ISO_8859_1_B9), M(ISO_8859_1_BA), M(ISO_8859_1_BB),
        M(ISO_8859_1_BC), M(ISO_8859_1_BD), M(ISO_8859_1_BE), M(ISO_8859_1_BF),
        M(ISO_8859_1_C0), M(ISO_8859_1_C1), M(ISO_8859_1_C2), M(ISO_8859_1_C3),
        M(ISO_8859_1_C4), M(ISO_8859_1_C5), M(ISO_8859_1_C6), M(ISO_8859_1_C7),
        M(ISO_8859_1_C8), M(ISO_8859_1_C9), M(ISO_8859_1_CA), M(ISO_8859_1_CB),
        M(ISO_8859_1_CC), M(ISO_8859_1_CD), M(ISO_8859_1_CE), M(ISO_8859_1_CF),
        M(ISO_8859_1_D0), M(ISO_8859_1_D1), M(ISO_8859_1_D2), M(ISO_8859_1_D3),
        M(ISO_8859_1_D4), M(ISO_8859_1_D5), M(ISO_8859_1_D6), M(ISO_8859_1_D7),
        M(ISO_8859_1_D8), M(ISO_8859_1_D9), M(ISO_8859_1_DA), M(ISO_8859_1_DB),
        M(ISO_8859_1_DC), M(ISO_8859_1_DD), M(ISO_8859_1_DE), M(ISO_8859_1_DF),
        M(ISO_8859_1_E0), M(ISO_8859_1_E1), M(ISO_8859_1_E2), M(ISO_8859_1_E3),
        M(ISO_8859_1_E4), M(ISO_8859_1_E5), M(ISO_8859_1_E6), M(ISO_8859_1_E7),
        M(ISO_8859_1_E8), M(ISO_8859_1_E9), M(ISO_8859_1_EA), M(ISO_8859_1_EB),
        M(ISO_8859_1_EC), M(ISO_8859_1_ED), M(ISO_8859_1_EE), M(ISO_8859_1_EF),
        M(ISO_8859_1_F0), M(ISO_8859_1_F1), M(ISO_8859_1_F2), M(ISO_8859_1_F3),
        M(ISO_8859_1_F4), M(ISO_8859_1_F5), M(ISO_8859_1_F6), M(ISO_8859_1_F7),
        M(ISO_8859_1_F8), M(ISO_8859_1_F9), M(ISO_8859_1_FA), M(ISO_8859_1_FB),
        M(ISO_8859_1_FC), M(ISO_8859_1_FD), M(ISO_8859_1_FE), M(ISO_8859_1_FF)
};
#endif // ISO_8859_1_A0
