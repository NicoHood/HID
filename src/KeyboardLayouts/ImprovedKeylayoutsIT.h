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

#include "ImprovedKeylayouts.h"

// Hut1_12v2.pdf

/* The following symbols are not available in the Italian layout:
 * - BACKQUOTE (AltGr + KEY_QUOTE on Linux, Alt + 96 on Windows)
 * - TILDE (AltGr + KEY_IGRAVE on Linux, Alt + 126 on Windows)
 */
enum KeyboardKeycode : uint8_t {
	KEY_RESERVED		=  0,
	KEY_ERROR_ROLLOVER	=  1,
	KEY_POST_FAIL		=  2,
	KEY_ERROR_UNDEFINED	=  3,
	
    KEY_A               =  4,
    KEY_B               =  5,
    KEY_C               =  6,
    KEY_D               =  7,
    KEY_E               =  8,
    KEY_F               =  9,
    KEY_G               = 10,
    KEY_H               = 11,
    KEY_I               = 12,
    KEY_J               = 13,
    KEY_K               = 14,
    KEY_L               = 15,
    KEY_M               = 16,
    KEY_N               = 17,
    KEY_O               = 18,
    KEY_P               = 19,
    KEY_Q               = 20,
    KEY_R               = 21,
    KEY_S               = 22,
    KEY_T               = 23,
    KEY_U               = 24,
    KEY_V               = 25,
    KEY_W               = 26,
    KEY_X               = 27,
    KEY_Y               = 28,
    KEY_Z               = 29,
    KEY_1               = 30,
    KEY_2               = 31,
    KEY_3               = 32,
    KEY_4               = 33,
    KEY_5               = 34,
    KEY_6               = 35,
    KEY_7               = 36,
	KEY_8               = 37,
	KEY_9               = 38,
    KEY_0               = 39,
    KEY_ENTER           = 40,
    KEY_RETURN          = 40, // Alias
    KEY_ESC             = 41,
    KEY_BACKSPACE       = 42,
    KEY_TAB             = 43,
    KEY_SPACE           = 44,
    // Customizations for IT layout start here
    KEY_QUOTE           = 45,
    KEY_IGRAVE          = 46,
    KEY_EGRAVE          = 47,
    KEY_PLUS            = 48,
    KEY_UGRAVE          = 49,
    KEY_NON_US_NUM      = 50,
    KEY_OGRAVE          = 51,
    KEY_AGRAVE          = 52,
    KEY_BACKSLASH       = 53,
    KEY_COMMA           = 54,
    KEY_PERIOD          = 55,
    KEY_MINUS           = 56,
    // Customizations for IT layout end here
    KEY_CAPS_LOCK		= 0x39,
    KEY_F1				= 0x3A,
    KEY_F2				= 0x3B,
    KEY_F3				= 0x3C,
    KEY_F4				= 0x3D,
    KEY_F5				= 0x3E,
    KEY_F6				= 0x3F,
    KEY_F7				= 0x40,
    KEY_F8				= 0x41,
    KEY_F9				= 0x42,
    KEY_F10			    = 0x43,
    KEY_F11			    = 0x44,
    KEY_F12			    = 0x45,
    KEY_PRINT			= 0x46,
    KEY_PRINTSCREEN     = 0x46, // Alias
    KEY_SCROLL_LOCK	    = 0x47,
    KEY_PAUSE			= 0x48,
    KEY_INSERT			= 0x49,
    KEY_HOME			= 0x4A,
    KEY_PAGE_UP		    = 0x4B,
    KEY_DELETE			= 0x4C,
    KEY_END			    = 0x4D,
    KEY_PAGE_DOWN		= 0x4E,
    KEY_RIGHT_ARROW	    = 0x4F,
    KEY_LEFT_ARROW		= 0x50,
    KEY_DOWN_ARROW		= 0x51,
    KEY_UP_ARROW		= 0x52,
    KEY_RIGHT   	    = 0x4F, // Alias
    KEY_LEFT	    	= 0x50, // Alias
    KEY_DOWN	    	= 0x51, // Alias
    KEY_UP	        	= 0x52, // Alias
    KEY_NUM_LOCK		= 0x53,
    KEYPAD_DIVIDE	    = 0x54,
    KEYPAD_MULTIPLY	    = 0x55,
    KEYPAD_SUBTRACT	    = 0x56,
    KEYPAD_ADD	        = 0x57,
    KEYPAD_ENTER 		= 0x58,
    KEYPAD_1 			= 0x59,
    KEYPAD_2 			= 0x5A,
    KEYPAD_3 			= 0x5B,
    KEYPAD_4 			= 0x5C,
    KEYPAD_5 			= 0x5D,
    KEYPAD_6 			= 0x5E,
    KEYPAD_7 			= 0x5F,
    KEYPAD_8 			= 0x60,
    KEYPAD_9 			= 0x61,
    KEYPAD_0 			= 0x62,
    KEYPAD_DOT			= 0x63,
    KEY_NON_US			= 0x64,
	KEY_LT_GT			= 0x64, // Alias for IT layout
    KEY_APPLICATION		= 0x65, // Context menu/right click
    KEY_MENU            = 0x65, // Alias
    
    // Most of the following keys will only work with Linux or not at all.
    // F13+ keys are mostly used for laptop functions like ECO key.
    KEY_POWER			= 0x66, // PowerOff (Ubuntu)
    KEY_PAD_EQUALS		= 0x67, // Dont confuse with KEYPAD_EQUAL_SIGN
    KEY_F13				= 0x68, // Tools (Ubunutu)
    KEY_F14				= 0x69, // Launch5 (Ubuntu)
    KEY_F15				= 0x6A, // Launch6 (Ubuntu)
    KEY_F16				= 0x6B, // Launch7 (Ubuntu)
    KEY_F17				= 0x6C, // Launch8 (Ubuntu)
    KEY_F18				= 0x6D, // Launch9 (Ubuntu)
    KEY_F19				= 0x6E, // Disabled (Ubuntu)
    KEY_F20				= 0x6F, // AudioMicMute (Ubuntu)
    KEY_F21				= 0x70, // Touchpad toggle (Ubuntu)
    KEY_F22				= 0x71, // TouchpadOn (Ubuntu)
    KEY_F23				= 0x72, // TouchpadOff Ubuntu)
    KEY_F24				= 0x73, // Disabled (Ubuntu)
    KEY_EXECUTE			= 0x74, // Open (Ubuntu)
    KEY_HELP			= 0x75, // Help (Ubuntu)
    KEY_MENU2			= 0x76, // Disabled (Ubuntu)
    KEY_SELECT			= 0x77, // Disabled (Ubuntu)
    KEY_STOP			= 0x78, // Cancel (Ubuntu)
    KEY_AGAIN			= 0x79, // Redo (Ubuntu)
    KEY_UNDO			= 0x7A, // Undo (Ubuntu)
    KEY_CUT				= 0x7B, // Cut (Ubuntu)
    KEY_COPY			= 0x7C, // Copy (Ubuntu)
    KEY_PASTE			= 0x7D, // Paste (Ubuntu)
    KEY_FIND			= 0x7E, // Find (Ubuntu)
    KEY_MUTE	  		= 0x7F,
    KEY_VOLUME_MUTE	    = 0x7F, // Alias
    KEY_VOLUME_UP		= 0x80,
    KEY_VOLUME_DOWN	    = 0x81,
    KEY_LOCKING_CAPS_LOCK	= 0x82, // Disabled (Ubuntu)
    KEY_LOCKING_NUM_LOCK	= 0x83, // Disabled (Ubuntu)
    KEY_LOCKING_SCROLL_LOCK	= 0x84, // Disabled (Ubuntu)
    KEYPAD_COMMA			= 0x85, // .
    KEYPAD_EQUAL_SIGN		= 0x86, // Disabled (Ubuntu), Dont confuse with KEYPAD_EQUAL
    KEY_INTERNATIONAL1		= 0x87, // Disabled (Ubuntu)
	KEY_INTERNATIONAL2		= 0x88, // Hiragana Katakana (Ubuntu)
	KEY_INTERNATIONAL3		= 0x89, // Disabled (Ubuntu)
	KEY_INTERNATIONAL4		= 0x8A, // Henkan (Ubuntu)
	KEY_INTERNATIONAL5		= 0x8B, // Muhenkan (Ubuntu)
	KEY_INTERNATIONAL6		= 0x8C, // Disabled (Ubuntu)
	KEY_INTERNATIONAL7		= 0x8D, // Disabled (Ubuntu)
	KEY_INTERNATIONAL8		= 0x8E, // Disabled (Ubuntu)
	KEY_INTERNATIONAL9		= 0x8F, // Disabled (Ubuntu)
	KEY_LANG1				= 0x90, // Disabled (Ubuntu)
	KEY_LANG2				= 0x91, // Disabled (Ubuntu)
	KEY_LANG3				= 0x92, // Katana (Ubuntu)
	KEY_LANG4				= 0x93, // Hiragana (Ubuntu)
	KEY_LANG5				= 0x94, // Disabled (Ubuntu)
	KEY_LANG6				= 0x95, // Disabled (Ubuntu)
	KEY_LANG7				= 0x96, // Disabled (Ubuntu)
	KEY_LANG8				= 0x97, // Disabled (Ubuntu)
	KEY_LANG9				= 0x98, // Disabled (Ubuntu)
	KEY_ALTERNATE_ERASE		= 0x99, // Disabled (Ubuntu)
	KEY_SYSREQ_ATTENTION	= 0x9A, // Disabled (Ubuntu)
    KEY_CANCEL		        = 0x9B, // Disabled (Ubuntu)
    KEY_CLEAR		        = 0x9C, // Delete (Ubuntu)
    KEY_PRIOR		        = 0x9D, // Disabled (Ubuntu)
    KEY_RETURN2		        = 0x9E, // Disabled (Ubuntu), Do not confuse this with KEY_ENTER
    KEY_SEPARATOR		    = 0x9F, // Disabled (Ubuntu)
    KEY_OUT		            = 0xA0, // Disabled (Ubuntu)
    KEY_OPER		        = 0xA1, // Disabled (Ubuntu)
    KEY_CLEAR_AGAIN		    = 0xA2, // Disabled (Ubuntu)
    KEY_CRSEL_PROPS		    = 0xA3, // Disabled (Ubuntu)
    KEY_EXSEL		        = 0xA4, // Disabled (Ubuntu)
    
    KEY_PAD_00				    = 0xB0, // Disabled (Ubuntu)
    KEY_PAD_000				    = 0xB1, // Disabled (Ubuntu)
    KEY_THOUSANDS_SEPARATOR	    = 0xB2, // Disabled (Ubuntu)
    KEY_DECIMAL_SEPARATOR	    = 0xB3, // Disabled (Ubuntu)
    KEY_CURRENCY_UNIT		    = 0xB4, // Disabled (Ubuntu)
    KEY_CURRENCY_SUB_UNIT	    = 0xB5, // Disabled (Ubuntu)
    KEYPAD_LEFT_BRACE		    = 0xB6, // (
    KEYPAD_RIGHT_BRACE		    = 0xB7, // )
    KEYPAD_LEFT_CURLY_BRACE	    = 0xB8, // Disabled (Ubuntu)
    KEYPAD_RIGHT_CURLY_BRACE    = 0xB9, // Disabled (Ubuntu)
    KEYPAD_TAB		            = 0xBA, // Disabled (Ubuntu)
    KEYPAD_BACKSPACE		    = 0xBB, // Disabled (Ubuntu)
    KEYPAD_A		            = 0xBC, // Disabled (Ubuntu)
    KEYPAD_B		            = 0xBD, // Disabled (Ubuntu)
    KEYPAD_C		            = 0xBE, // Disabled (Ubuntu)
    KEYPAD_D		            = 0xBF, // Disabled (Ubuntu)
    KEYPAD_E		            = 0xC0, // Disabled (Ubuntu)
    KEYPAD_F		            = 0xC1, // Disabled (Ubuntu)
    KEYPAD_XOR		            = 0xC2, // Disabled (Ubuntu)
    KEYPAD_CARET		        = 0xC3, // Disabled (Ubuntu)
    KEYPAD_PERCENT		        = 0xC4, // Disabled (Ubuntu)
    KEYPAD_LESS_THAN		    = 0xC5, // Disabled (Ubuntu)
    KEYPAD_GREATER_THAN		    = 0xC6, // Disabled (Ubuntu)
    KEYPAD_AMPERSAND		    = 0xC7, // Disabled (Ubuntu)
    KEYPAD_DOUBLEAMPERSAND		= 0xC8, // Disabled (Ubuntu)
    KEYPAD_PIPE		            = 0xC9, // Disabled (Ubuntu)
    KEYPAD_DOUBLEPIPE	        = 0xCA, // Disabled (Ubuntu)
    KEYPAD_COLON	            = 0xCB, // Disabled (Ubuntu)
    KEYPAD_POUND_SIGN           = 0xCC, // Disabled (Ubuntu)
    KEYPAD_SPACE	            = 0xCD, // Disabled (Ubuntu)
    KEYPAD_AT_SIGN              = 0xCE, // Disabled (Ubuntu)
    KEYPAD_EXCLAMATION_POINT    = 0xCF, // Disabled (Ubuntu)
    KEYPAD_MEMORY_STORE	        = 0xD0, // Disabled (Ubuntu)
    KEYPAD_MEMORY_RECALL	    = 0xD1, // Disabled (Ubuntu)
    KEYPAD_MEMORY_CLEAR	        = 0xD2, // Disabled (Ubuntu)
    KEYPAD_MEMORY_ADD	        = 0xD3, // Disabled (Ubuntu)
    KEYPAD_MEMORY_SUBTRACT	    = 0xD4, // Disabled (Ubuntu)
    KEYPAD_MEMORY_MULTIPLY	    = 0xD5, // Disabled (Ubuntu)
    KEYPAD_MEMORY_DIVIDE	    = 0xD6, // Disabled (Ubuntu)
    KEYPAD_PLUS_MINUS	        = 0xD7, // Disabled (Ubuntu)
    KEYPAD_CLEAR	            = 0xD8, // Delete (Ubuntu)
    KEYPAD_CLEAR_ENTRY	        = 0xD9, // Disabled (Ubuntu)
    KEYPAD_BINARY	            = 0xDA, // Disabled (Ubuntu)
    KEYPAD_OCTAL	            = 0xDB, // Disabled (Ubuntu)
    KEYPAD_DECIMAL	            = 0xDC, // Disabled (Ubuntu)
    KEYPAD_HEXADECIMAL	        = 0xDD, // Disabled (Ubuntu)
    
    KEY_LEFT_CTRL		    = 0xE0,
	KEY_LEFT_SHIFT		    = 0xE1,
	KEY_LEFT_ALT		    = 0xE2,
	KEY_LEFT_GUI		    = 0xE3,
	KEY_LEFT_WINDOWS	    = 0xE3, // Alias
	KEY_RIGHT_CTRL		    = 0xE4,
	KEY_RIGHT_SHIFT		    = 0xE5,
	KEY_RIGHT_ALT		    = 0xE6,
	KEY_RIGHT_GUI		    = 0xE7,
	KEY_RIGHT_WINDOWS	    = 0xE7, // Alias

	// Unavailable keys
	KEY_TILDE				= 0x00,
	KEY_EQUAL				= 0x00,
	KEY_RIGHT_BRACE			= 0x00,
	KEY_LEFT_BRACE			= 0x00,
	KEY_SEMICOLON			= 0x00,
	KEY_SLASH				= 0x00,
	
    // Keyboard HID mappings

    // Reserved	0xA5-AF
    HID_KEYPAD_00	= 0xB0,
    HID_KEYPAD_000	= 0xB1,
    HID_THOUSANDS_SEPARATOR	= 0xB2,
    HID_DECIMAL_SEPARATOR	= 0xB3,
    HID_CURRENCY_UNIT	= 0xB4,
    HID_CURRENCY_SUBUNIT	= 0xB5,
    HID_KEYPAD_LEFT_PAREN	= 0xB6,
    HID_KEYPAD_RIGHT_PAREN	= 0xB7,
    HID_KEYPAD_LEFT_CURLY_BRACE	= 0xB8,
    HID_KEYPAD_RIGHT_CURLY_BRACE	= 0xB9,
    HID_KEYPAD_TAB	= 0xBA,
    HID_KEYPAD_BACKSPACE	= 0xBB,
    HID_KEYPAD_A	= 0xBC,
    HID_KEYPAD_B	= 0xBD,
    HID_KEYPAD_C	= 0xBE,
    HID_KEYPAD_D	= 0xBF,
    HID_KEYPAD_E	= 0xC0,
    HID_KEYPAD_F	= 0xC1,
    HID_KEYPAD_XOR	= 0xC2,
    HID_KEYPAD_CARAT	= 0xC3,
    HID_KEYPAD_PERCENT	= 0xC4,
    HID_KEYPAD_LESS_THAN	= 0xC5,
    HID_KEYPAD_GREATER_THAN	= 0xC6,
    HID_KEYPAD_AMPERSAND	= 0xC7,
    HID_KEYPAD_DOUBLEAMPERSAND	= 0xC8,
    HID_KEYPAD_PIPE	= 0xC9,
    HID_KEYPAD_DOUBLEPIPE	= 0xCA,
    HID_KEYPAD_COLON	= 0xCB,
    HID_KEYPAD_POUND_SIGN	= 0xCC,
    HID_KEYPAD_SPACE	= 0xCD,
    HID_KEYPAD_AT_SIGN	= 0xCE,
    HID_KEYPAD_EXCLAMATION_POINT	= 0xCF,
    HID_KEYPAD_MEMORY_STORE	= 0xD0,
    HID_KEYPAD_MEMORY_RECALL	= 0xD1,
    HID_KEYPAD_MEMORY_CLEAR	= 0xD2,
    HID_KEYPAD_MEMORY_ADD	= 0xD3,
    HID_KEYPAD_MEMORY_SUBTRACT	= 0xD4,
    HID_KEYPAD_MEMORY_MULTIPLY	= 0xD5,
    HID_KEYPAD_MEMORY_DIVIDE	= 0xD6,
    HID_KEYPAD_PLUS_SLASH_MINUS	= 0xD7,
    HID_KEYPAD_CLEAR	= 0xD8,
    HID_KEYPAD_CLEAR_ENTRY	= 0xD9,
    HID_KEYPAD_BINARY	= 0xDA,
    HID_KEYPAD_OCTAL	= 0xDB,
    HID_KEYPAD_DECIMAL	= 0xDC,
    HID_KEYPAD_HEXADECIMAL	= 0xDD,

    //	0xDE-0xDF	 - RESERVED
    HID_KEYBOARD_LEFT_CONTROL	= 0xE0,
    HID_KEYBOARD_LEFT_SHIFT	= 0xE1,
    HID_KEYBOARD_LEFT_ALT	= 0xE2,
    HID_KEYBOARD_LEFT_GUI	= 0xE3,
    HID_KEYBOARD_RIGHT_CONTROL	= 0xE4,
    HID_KEYBOARD_RIGHT_SHIFT	= 0xE5,
    HID_KEYBOARD_RIGHT_ALT	= 0xE6,
    HID_KEYBOARD_RIGHT_GUI	= 0xE7,
};



static const uint16_t _asciimap[] PROGMEM =
{
	KEY_RESERVED,           // NUL
	KEY_RESERVED,           // SOH
	KEY_RESERVED,           // STX
	KEY_RESERVED,           // ETX
	KEY_RESERVED,           // EOT
	KEY_RESERVED,           // ENQ
	KEY_RESERVED,           // ACK  
	KEY_RESERVED,           // BEL
	KEY_BACKSPACE,			// BS	Backspace
	KEY_TAB,				// TAB	Tab
	KEY_ENTER,				// LF	Enter
	KEY_RESERVED,           // VT 
	KEY_RESERVED,           // FF 
	KEY_RESERVED,           // CR 
	KEY_RESERVED,           // SO 
	KEY_RESERVED,           // SI 
	KEY_RESERVED,           // DEL
	KEY_RESERVED,           // DC1
	KEY_RESERVED,           // DC2
	KEY_RESERVED,           // DC3
	KEY_RESERVED,           // DC4
	KEY_RESERVED,           // NAK
	KEY_RESERVED,           // SYN
	KEY_RESERVED,           // ETB
	KEY_RESERVED,           // CAN
	KEY_RESERVED,           // EM 
	KEY_RESERVED,           // SUB
	KEY_RESERVED,           // ESC
	KEY_RESERVED,           // FS 
	KEY_RESERVED,           // GS 
	KEY_RESERVED,           // RS 
	KEY_RESERVED,           // US 

	KEY_SPACE,		   		// ' ' Space
	KEY_1|MOD_LEFT_SHIFT,	   		// !
	KEY_2|MOD_LEFT_SHIFT,	   		// "
	KEY_AGRAVE|MOD_RIGHT_ALT,    	// #
	KEY_4|MOD_LEFT_SHIFT,    		// $
	KEY_5|MOD_LEFT_SHIFT,    		// %
	KEY_6|MOD_LEFT_SHIFT,    		// &
	KEY_QUOTE,          	// '
	KEY_8|MOD_LEFT_SHIFT,    		// (
	KEY_9|MOD_LEFT_SHIFT,    		// )
	KEY_PLUS|MOD_LEFT_SHIFT,    	// *
	KEY_PLUS,				    	// +
	KEY_COMMA,          	// ,
	KEY_MINUS,          	// -
	KEY_PERIOD,          	// .
	KEY_7|MOD_LEFT_SHIFT, 	// /
	KEY_0,          		// 0
	KEY_1,          		// 1
	KEY_2,          		// 2
	KEY_3,          		// 3
	KEY_4,          		// 4
	KEY_5,          		// 5
	KEY_6,          		// 6
	KEY_7,          		// 7
	KEY_8,          		// 8
	KEY_9,          		// 9
	KEY_PERIOD|MOD_LEFT_SHIFT,		// :
	KEY_COMMA|MOD_LEFT_SHIFT,       // ;
	KEY_LT_GT,				      	// <
	KEY_0|MOD_LEFT_SHIFT,          	// =
	KEY_LT_GT|MOD_LEFT_SHIFT,      	// >
	KEY_QUOTE|MOD_LEFT_SHIFT,      	// ?
	KEY_OGRAVE|MOD_RIGHT_ALT,      	// @
	KEY_A|MOD_LEFT_SHIFT,      		// A
	KEY_B|MOD_LEFT_SHIFT,      		// B
	KEY_C|MOD_LEFT_SHIFT,      		// C
	KEY_D|MOD_LEFT_SHIFT,      		// D
	KEY_E|MOD_LEFT_SHIFT,      		// E
	KEY_F|MOD_LEFT_SHIFT,      		// F
	KEY_G|MOD_LEFT_SHIFT,      		// G
	KEY_H|MOD_LEFT_SHIFT,      		// H
	KEY_I|MOD_LEFT_SHIFT,      		// I
	KEY_J|MOD_LEFT_SHIFT,      		// J
	KEY_K|MOD_LEFT_SHIFT,      		// K
	KEY_L|MOD_LEFT_SHIFT,      		// L
	KEY_M|MOD_LEFT_SHIFT,      		// M
	KEY_N|MOD_LEFT_SHIFT,      		// N
	KEY_O|MOD_LEFT_SHIFT,      		// O
	KEY_P|MOD_LEFT_SHIFT,      		// P
	KEY_Q|MOD_LEFT_SHIFT,      		// Q
	KEY_R|MOD_LEFT_SHIFT,      		// R
	KEY_S|MOD_LEFT_SHIFT,      		// S
	KEY_T|MOD_LEFT_SHIFT,      		// T
	KEY_U|MOD_LEFT_SHIFT,      		// U
	KEY_V|MOD_LEFT_SHIFT,      		// V
	KEY_W|MOD_LEFT_SHIFT,      		// W
	KEY_X|MOD_LEFT_SHIFT,      		// X
	KEY_Y|MOD_LEFT_SHIFT,      		// Y
	KEY_Z|MOD_LEFT_SHIFT,      		// Z
	KEY_EGRAVE|MOD_RIGHT_ALT,		// [
	KEY_BACKSLASH,         			// bslash
	KEY_PLUS|MOD_RIGHT_ALT,			// ]
	KEY_IGRAVE|MOD_LEFT_SHIFT,    	// ^
	KEY_MINUS|MOD_LEFT_SHIFT,    	// _
	KEY_RESERVED,          	// `
	KEY_A,          		// a
	KEY_B,          		// b
	KEY_C,          		// c
	KEY_D,          		// d
	KEY_E,          		// e
	KEY_F,          		// f
	KEY_G,          		// g
	KEY_H,          		// h
	KEY_I,          		// i
	KEY_J,          		// j
	KEY_K,         		 	// k
	KEY_L,          		// l
	KEY_M,          		// m
	KEY_N,          		// n
	KEY_O,          		// o
	KEY_P,          		// p
	KEY_Q,          		// q
	KEY_R,          		// r
	KEY_S,          		// s
	KEY_T,          		// t
	KEY_U,          		// u
	KEY_V,          		// v
	KEY_W,          		// w
	KEY_X,          		// x
	KEY_Y,          		// y
	KEY_Z,          		// z
	KEY_EGRAVE|MOD_LEFT_SHIFT|MOD_RIGHT_ALT,   // {
	KEY_BACKSLASH|MOD_LEFT_SHIFT,    // |
	KEY_PLUS|MOD_LEFT_SHIFT|MOD_RIGHT_ALT,  // }
	KEY_RESERVED,	    	// ~
	KEY_RESERVED,			// 127 - DEL
	// 7-bit ASCII codes end here

	// The following characters belong to ISO-8859-15
	KEY_RESERVED,					// 128 - Unused
	KEY_RESERVED,					// 129 - Unused
	KEY_RESERVED,					// 130 - Unused
	KEY_RESERVED,                   // 131 - Unused
	KEY_RESERVED,                   // 132 - Unused
	KEY_RESERVED,                   // 133 - Unused
	KEY_RESERVED,                   // 134 - Unused
	KEY_RESERVED,                   // 135 - Unused
	KEY_RESERVED,                   // 136 - Unused
	KEY_RESERVED,                   // 137 - Unused
	KEY_RESERVED,                   // 138 - Unused
	KEY_RESERVED,                   // 139 - Unused
	KEY_RESERVED,                   // 140 - Unused
	KEY_RESERVED,                   // 141 - Unused
	KEY_RESERVED,                   // 142 - Unused
	KEY_RESERVED,                   // 143 - Unused
	KEY_RESERVED,                   // 144 - Unused
	KEY_RESERVED,                   // 145 - Unused
	KEY_RESERVED,                   // 146 - Unused
	KEY_RESERVED,                   // 147 - Unused
	KEY_RESERVED,                   // 148 - Unused
	KEY_RESERVED,                   // 149 - Unused
	KEY_RESERVED,                   // 150 - Unused
	KEY_RESERVED,                   // 151 - Unused
	KEY_RESERVED,                   // 152 - Unused
	KEY_RESERVED,                   // 153 - Unused
	KEY_RESERVED,                   // 154 - Unused
	KEY_RESERVED,                   // 155 - Unused
	KEY_RESERVED,                   // 156 - Unused
	KEY_RESERVED,                   // 157 - Unused
	KEY_RESERVED,                   // 158 - Unused
	KEY_RESERVED,					// 159 - Unused
	KEY_RESERVED,					// 160 - Non-breaking Space
	KEY_RESERVED,					// 161 - Inverted Exclamation Mark
	KEY_RESERVED,					// 162 - Cent
	KEY_3|MOD_LEFT_SHIFT,			// 163 - British Pound Sign
	KEY_E|MOD_RIGHT_ALT,			// 164 - Euro Sign
	KEY_RESERVED,					// 165 - Yen
	KEY_RESERVED,					// 166 - Capital 's' Inverted Circumflex
	KEY_UGRAVE|MOD_LEFT_SHIFT,		// 167 - Section Sign
	KEY_RESERVED,					// 168 - 's' Inverted Circumflex
	KEY_RESERVED,					// 169 - Copyright Sign
	KEY_RESERVED,					// 170 - Superscript 'a'
	KEY_RESERVED,					// 171 - Open Guillemet
	KEY_RESERVED,					// 172 - Logic Negation
	KEY_RESERVED,					// 173 - Soft Hypen
	KEY_RESERVED,					// 174 - Registered Trademark
	KEY_RESERVED,					// 175 - Macron
	KEY_AGRAVE|MOD_LEFT_SHIFT,		// 176 - Degree Symbol
	KEY_RESERVED,					// 177 - Plus-Minus
	KEY_RESERVED,					// 178 - Superscript '2'
	KEY_RESERVED,					// 179 - Superscript '3'
	KEY_RESERVED,					// 180 - Capital 'z' Inverted Circumflex
	KEY_RESERVED,					// 181 - Micro Symbol
	KEY_RESERVED,					// 182 - Paragraph Mark
	KEY_RESERVED,					// 183 - Interpunct
	KEY_RESERVED,					// 184 - 'z' Inverted Circumflex
	KEY_RESERVED,					// 185 - Superscript '1'
	KEY_RESERVED,					// 186 - Ordinal Indicator
	KEY_RESERVED,					// 187 - Closed Guillemet
	KEY_RESERVED,					// 188 - Capital 'oe'
	KEY_RESERVED,					// 189 - 'oe'
	KEY_RESERVED,					// 190 - Capital 'y' Umlaut
	KEY_RESERVED,					// 191 - Inverted Question Mark
	KEY_RESERVED,					// 192 - Capital 'a' Grave
	KEY_RESERVED,					// 193 - Capital 'a' Acute
	KEY_RESERVED,					// 194 - Capital 'a' Circumflex
	KEY_RESERVED,					// 195 - Capital 'a' Tilde
	KEY_RESERVED,					// 196 - Capital 'a' Umlaut
	KEY_RESERVED,					// 197 - Capital 'a' Circle
	KEY_RESERVED,					// 198 - Capital 'ae'
	KEY_RESERVED,					// 199 - Capital 'c' Cedilla
	KEY_RESERVED,					// 200 - Capital 'e' Grave
	KEY_RESERVED,					// 201 - Capital 'e' Acute
	KEY_RESERVED,					// 202 - Capital 'e' Circumflex
	KEY_RESERVED,					// 203 - Capital 'e' Umlaut
	KEY_RESERVED,					// 204 - Capital 'i' Grave
	KEY_RESERVED,					// 205 - Capital 'i' Acute
	KEY_RESERVED,					// 206 - Capital 'i' Circumflex
	KEY_RESERVED,					// 207 - Capital 'i' Umlaut
	KEY_RESERVED,					// 208 - Capital Eth
	KEY_RESERVED,					// 207 - Capital 'n' Tilde
	KEY_RESERVED,					// 210 - Capital 'o' Grave
	KEY_RESERVED,					// 211 - Capital 'o' Acute
	KEY_RESERVED,					// 212 - Capital 'o' Circumflex
	KEY_RESERVED,					// 213 - Capital 'o' Tilde
	KEY_RESERVED,					// 214 - Capital 'o' Umlaut
	KEY_RESERVED,					// 215 - Multiplication Sign
	KEY_RESERVED,					// 216 - Capital 'o' Barred
	KEY_RESERVED,					// 217 - Capital 'u' Grave
	KEY_RESERVED,					// 218 - Capital 'u' Acute
	KEY_RESERVED,					// 219 - Capital 'u' Circumflex
	KEY_RESERVED,					// 220 - Capital 'u' Umlaut
	KEY_RESERVED,					// 221 - Capital 'y' Acute
	KEY_RESERVED,					// 222 - Capital Thorn
	KEY_RESERVED,					// 223 - Eszett
	KEY_AGRAVE,						// 224 - 'a' Grave
	KEY_RESERVED,					// 225 - 'a' Acute
	KEY_RESERVED,					// 226 - 'a' Circumflex
	KEY_RESERVED,					// 227 - 'a' Tilde
	KEY_RESERVED,					// 228 - 'a' Umlaut
	KEY_RESERVED,					// 229 - 'a' Circle
	KEY_RESERVED,					// 230 - 'ae'
	KEY_OGRAVE|MOD_LEFT_SHIFT,		// 231 - 'c' Cedilla
	KEY_EGRAVE,						// 232 - 'e' Grave
	KEY_EGRAVE|MOD_LEFT_SHIFT,		// 233 - 'e' Acute
	KEY_RESERVED,					// 234 - 'e' Circumflex
	KEY_RESERVED,					// 235 - 'e' Umlaut
	KEY_IGRAVE,						// 236 - 'i' Grave
	KEY_RESERVED,					// 237 - 'i' Acute
	KEY_RESERVED,					// 238 - 'i' Circumflex
	KEY_RESERVED,					// 239 - 'i' Umlaut
	KEY_RESERVED,					// 240 - Eth
	KEY_RESERVED,					// 241 - 'n' Tilde
	KEY_OGRAVE,						// 242 - 'o' Grave
	KEY_RESERVED,					// 243 - 'o' Acute
	KEY_RESERVED,					// 244 - 'o' Circumflex
	KEY_RESERVED,					// 245 - 'o' Tilde
	KEY_RESERVED,					// 246 - 'o' Umlaut
	KEY_RESERVED,					// 247 - Multiplication Sign
	KEY_RESERVED,					// 248 - 'o' Barred
	KEY_UGRAVE,						// 249 - 'u' Grave
	KEY_RESERVED,					// 250 - 'u' Acute
	KEY_RESERVED,					// 251 - 'u' Circumflex
	KEY_RESERVED,					// 252 - 'u' Umlaut
	KEY_RESERVED,					// 253 - 'y' Acute
	KEY_RESERVED,					// 254 - Thorn
	KEY_RESERVED,					// 255 - 'y' Umlaut
};
