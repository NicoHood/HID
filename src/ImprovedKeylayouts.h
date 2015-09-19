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
// Key definitions
//================================================================================

// Modifiers
#define KEY_LEFT_CTRL		0x80
#define KEY_LEFT_SHIFT		0x81
#define KEY_LEFT_ALT		0x82
#define KEY_LEFT_GUI		0x83
#define KEY_RIGHT_CTRL		0x84
#define KEY_RIGHT_SHIFT		0x85
#define KEY_RIGHT_ALT		0x86
#define KEY_RIGHT_GUI		0x87

// Normal keys
#define KEY_UP_ARROW		(RAW_KEYBOARD_UP_ARROW + 136)
#define KEY_DOWN_ARROW		(RAW_KEYBOARD_DOWN_ARROW + 136)
#define KEY_LEFT_ARROW		(RAW_KEYBOARD_LEFT_ARROW + 136)
#define KEY_RIGHT_ARROW		(RAW_KEYBOARD_RIGHT_ARROW + 136)
#define KEY_BACKSPACE		(RAW_KEYBOARD_BACKSPACE + 136)
#define KEY_TAB				(RAW_KEYBOARD_TAB + 136)
#define KEY_RETURN			(RAW_KEYBOARD_RETURN + 136)
#define KEY_ESC				(RAW_KEYBOARD_ESC + 136)
#define KEY_INSERT			(RAW_KEYBOARD_INSERT + 136)
#define KEY_DELETE			(RAW_KEYBOARD_DELETE + 136)
#define KEY_PAGE_UP			(RAW_KEYBOARD_PAGE_UP + 136)
#define KEY_PAGE_DOWN		(RAW_KEYBOARD_PAGE_DOWN + 136)
#define KEY_HOME			(RAW_KEYBOARD_HOME + 136)
#define KEY_END				(RAW_KEYBOARD_END + 136)
#define KEY_CAPS_LOCK		(RAW_KEYBOARD_CAPS_LOCK + 136)
#define KEY_F1				(RAW_KEYBOARD_F1 + 136)
#define KEY_F2				(RAW_KEYBOARD_F2 + 136)
#define KEY_F3				(RAW_KEYBOARD_F3 + 136)
#define KEY_F4				(RAW_KEYBOARD_F4 + 136)
#define KEY_F5				(RAW_KEYBOARD_F5 + 136)
#define KEY_F6				(RAW_KEYBOARD_F6 + 136)
#define KEY_F7				(RAW_KEYBOARD_F7 + 136)
#define KEY_F8				(RAW_KEYBOARD_F8 + 136)
#define KEY_F9				(RAW_KEYBOARD_F9 + 136)
#define KEY_F10				(RAW_KEYBOARD_F10 + 136)
#define KEY_F11				(RAW_KEYBOARD_F11 + 136)
#define KEY_F12				(RAW_KEYBOARD_F12 + 136)


// New key definitions
#define KEY_PRINT			(RAW_KEYBOARD_PRINT + 136)
#define KEY_NUM_LOCK		(RAW_KEYBOARD_NUM_LOCK + 136)
#define KEY_SCROLL_LOCK		(RAW_KEYBOARD_SCROLL_LOCK + 136)
#define KEY_PAUSE			(RAW_KEYBOARD_PAUSE + 136)
#define KEY_MENU			(RAW_KEYBOARD_MENU + 136)
#define KEY_SPACE           ' '
#define KEY_LEFT_WINDOWS	KEY_LEFT_GUI
#define KEY_RIGHT_WINDOWS	KEY_RIGHT_GUI
#define KEY_PRINTSCREEN		KEY_PRINT

// TODO implement Leds
#define LED_NUM_LOCK			0x01
#define LED_CAPS_LOCK			0x02
#define LED_SCROLL_LOCK			0x04

//================================================================================
// LAYOUT_US_ENGLISH
//================================================================================

#define RAW_KEYBOARD_LEFT_CTRL   (1 << 0)
#define RAW_KEYBOARD_LEFT_SHIFT  (1 << 1)
#define RAW_KEYBOARD_LEFT_ALT    (1 << 2)
#define RAW_KEYBOARD_LEFT_GUI  	 (1 << 3)
#define RAW_KEYBOARD_RIGHT_CTRL  (1 << 4)
#define RAW_KEYBOARD_RIGHT_SHIFT (1 << 5)
#define RAW_KEYBOARD_RIGHT_ALT   (1 << 6)
#define RAW_KEYBOARD_RIGHT_GUI 	 (1 << 7)

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

#define RAW_KEYBOARD_KEY(key) ((key>='a' && key<='z') ? (0x04 + key-'a') :\
(key>='A' && key<='Z') ? (0x04 + key-'A') : (key>='1' && key<='9') ? (0x1E + key-'1') : 0x27)

#define RAW_KEYBOARD_A           ( 4  )
#define RAW_KEYBOARD_B           ( 5  )
#define RAW_KEYBOARD_C           ( 6  )
#define RAW_KEYBOARD_D           ( 7  )
#define RAW_KEYBOARD_E           ( 8  )
#define RAW_KEYBOARD_F           ( 9  )
#define RAW_KEYBOARD_G           ( 10 )
#define RAW_KEYBOARD_H           ( 11 )
#define RAW_KEYBOARD_I           ( 12 )
#define RAW_KEYBOARD_J           ( 13 )
#define RAW_KEYBOARD_K           ( 14 )
#define RAW_KEYBOARD_L           ( 15 )
#define RAW_KEYBOARD_M           ( 16 )
#define RAW_KEYBOARD_N           ( 17 )
#define RAW_KEYBOARD_O           ( 18 )
#define RAW_KEYBOARD_P           ( 19 )
#define RAW_KEYBOARD_Q           ( 20 )
#define RAW_KEYBOARD_R           ( 21 )
#define RAW_KEYBOARD_S           ( 22 )
#define RAW_KEYBOARD_T           ( 23 )
#define RAW_KEYBOARD_U           ( 24 )
#define RAW_KEYBOARD_V           ( 25 )
#define RAW_KEYBOARD_W           ( 26 )
#define RAW_KEYBOARD_X           ( 27 )
#define RAW_KEYBOARD_Y           ( 28 )
#define RAW_KEYBOARD_Z           ( 29 )
#define RAW_KEYBOARD_1           ( 30 )
#define RAW_KEYBOARD_2           ( 31 )
#define RAW_KEYBOARD_3           ( 32 )
#define RAW_KEYBOARD_4           ( 33 )
#define RAW_KEYBOARD_5           ( 34 )
#define RAW_KEYBOARD_6           ( 35 )
#define RAW_KEYBOARD_7           ( 36 )
#define RAW_KEYBOARD_8           ( 37 )
#define RAW_KEYBOARD_9           ( 38 )
#define RAW_KEYBOARD_0           ( 39 )
#define RAW_KEYBOARD_ENTER       ( 40 )
#define RAW_KEYBOARD_ESC         ( 41 )
#define RAW_KEYBOARD_BACKSPACE   ( 42 )
#define RAW_KEYBOARD_TAB         ( 43 )
#define RAW_KEYBOARD_SPACE       ( 44 )
#define RAW_KEYBOARD_MINUS       ( 45 )
#define RAW_KEYBOARD_EQUAL       ( 46 )
#define RAW_KEYBOARD_LEFT_BRACE  ( 47 )
#define RAW_KEYBOARD_RIGHT_BRACE ( 48 )
#define RAW_KEYBOARD_BACKSLASH   ( 49 )
#define RAW_KEYBOARD_NON_US_NUM  ( 50 )
#define RAW_KEYBOARD_SEMICOLON   ( 51 )
#define RAW_KEYBOARD_QUOTE       ( 52 )
#define RAW_KEYBOARD_TILDE       ( 53 )
#define RAW_KEYBOARD_COMMA       ( 54 )
#define RAW_KEYBOARD_PERIOD      ( 55 )
#define RAW_KEYBOARD_SLASH       ( 56 )

#define RAW_KEYBOARD_PRINT			0x46
#define RAW_KEYBOARD_NUM_LOCK		0x53
#define RAW_KEYBOARD_SCROLL_LOCK	0x47
#define RAW_KEYBOARD_PAUSE			0x48
#define RAW_KEYBOARD_MENU			0x65

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
	RAW_KEYBOARD_BACKSPACE,			// BS	Backspace
	RAW_KEYBOARD_TAB,			// TAB	Tab
	RAW_KEYBOARD_RETURN,			// LF	Enter
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

	RAW_KEYBOARD_SPACE,		   //  ' '
	0x1e|SHIFT,	   // !
	0x34|SHIFT,	   // "
	0x20|SHIFT,    // #
	0x21|SHIFT,    // $
	0x22|SHIFT,    // %
	0x24|SHIFT,    // &
	0x34,          // '
	0x26|SHIFT,    // (
	0x27|SHIFT,    // )
	0x25|SHIFT,    // *
	0x2e|SHIFT,    // +
	0x36,          // ,
	RAW_KEYBOARD_MINUS,          // -
	0x37,          // .
	0x38,          // /
	RAW_KEYBOARD_0,          // 0
	RAW_KEYBOARD_1,          // 1
	RAW_KEYBOARD_2,          // 2
	RAW_KEYBOARD_3,          // 3
	RAW_KEYBOARD_4,          // 4
	RAW_KEYBOARD_5,          // 5
	RAW_KEYBOARD_6,          // 6
	RAW_KEYBOARD_7,          // 7
	RAW_KEYBOARD_8,          // 8
	RAW_KEYBOARD_9,          // 9
	0x33|SHIFT,      // :
	0x33,          // ;
	0x36|SHIFT,      // <
	0x2e,          // =
	0x37|SHIFT,      // >
	0x38|SHIFT,      // ?
	0x1f|SHIFT,      // @
	RAW_KEYBOARD_A|SHIFT,      // A
	RAW_KEYBOARD_B|SHIFT,      // B
	RAW_KEYBOARD_C|SHIFT,      // C
	RAW_KEYBOARD_D|SHIFT,      // D
	RAW_KEYBOARD_E|SHIFT,      // E
	RAW_KEYBOARD_F|SHIFT,      // F
	RAW_KEYBOARD_G|SHIFT,      // G
	RAW_KEYBOARD_H|SHIFT,      // H
	RAW_KEYBOARD_I|SHIFT,      // I
	RAW_KEYBOARD_J|SHIFT,      // J
	RAW_KEYBOARD_K|SHIFT,      // K
	RAW_KEYBOARD_L|SHIFT,      // L
	RAW_KEYBOARD_M|SHIFT,      // M
	RAW_KEYBOARD_N|SHIFT,      // N
	RAW_KEYBOARD_O|SHIFT,      // O
	RAW_KEYBOARD_P|SHIFT,      // P
	RAW_KEYBOARD_Q|SHIFT,      // Q
	RAW_KEYBOARD_R|SHIFT,      // R
	RAW_KEYBOARD_S|SHIFT,      // S
	RAW_KEYBOARD_T|SHIFT,      // T
	RAW_KEYBOARD_U|SHIFT,      // U
	RAW_KEYBOARD_V|SHIFT,      // V
	RAW_KEYBOARD_W|SHIFT,      // W
	RAW_KEYBOARD_X|SHIFT,      // X
	RAW_KEYBOARD_Y|SHIFT,      // Y
	RAW_KEYBOARD_Z|SHIFT,      // Z
	0x2f,          // [
	0x31,          // bslash
	0x30,          // ]
	0x23|SHIFT,    // ^
	0x2d|SHIFT,    // _
	0x35,          // `
	RAW_KEYBOARD_A,          // a
	RAW_KEYBOARD_B,          // b
	RAW_KEYBOARD_C,          // c
	RAW_KEYBOARD_D,          // d
	RAW_KEYBOARD_E,          // e
	RAW_KEYBOARD_F,          // f
	RAW_KEYBOARD_G,          // g
	RAW_KEYBOARD_H,          // h
	RAW_KEYBOARD_I,          // i
	RAW_KEYBOARD_J,          // j
	RAW_KEYBOARD_K,          // k
	RAW_KEYBOARD_L,          // l
	RAW_KEYBOARD_M,          // m
	RAW_KEYBOARD_N,          // n
	RAW_KEYBOARD_O,          // o
	RAW_KEYBOARD_P,          // p
	RAW_KEYBOARD_Q,          // q
	RAW_KEYBOARD_R,          // r
	RAW_KEYBOARD_S,          // s
	RAW_KEYBOARD_T,          // t
	RAW_KEYBOARD_U,          // u
	RAW_KEYBOARD_V,          // v
	RAW_KEYBOARD_W,          // w
	RAW_KEYBOARD_X,          // x
	RAW_KEYBOARD_Y,          // y
	RAW_KEYBOARD_Z,          // z
	0x2f|SHIFT,    // 
	0x31|SHIFT,    // |
	0x30|SHIFT,    // }
	0x35|SHIFT,    // ~
	0				// DEL
};
