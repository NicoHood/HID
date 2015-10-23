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

#if !defined(LAYOUT_US_ENGLISH)
#error This API does not support non US english layouts.
#endif

// Hut1_12v2.pdf
enum KeyboardModifier : uint8_t {
	KEY_LEFT_CTRL		= (1 << 0),
	KEY_LEFT_SHIFT		= (1 << 1),
	KEY_LEFT_ALT		= (1 << 2),
	KEY_LEFT_GUI		= (1 << 3),
	KEY_LEFT_WINDOWS	= (1 << 3), // Alias
	KEY_RIGHT_CTRL		= (1 << 4),
	KEY_RIGHT_SHIFT		= (1 << 5),
	KEY_RIGHT_ALT		= (1 << 6),
	KEY_RIGHT_GUI		= (1 << 7),
	KEY_RIGHT_WINDOWS	= (1 << 7), // Alias
};

enum KeyboardKeycode : uint8_t {
	KEY_RESERVED		=  0,
	KEY_ERRORROLLOVER	=  1,
	KEY_POSTFAIL		=  2,
	KEY_ERRORUNDEFINED	=  3,
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
    KEY_ESC             = 41,
    KEY_BACKSPACE       = 42,
    KEY_TAB             = 43,
    KEY_SPACE           = 44,
    KEY_MINUS           = 45,
    KEY_EQUAL           = 46,
    KEY_LEFT_BRACE      = 47,
    KEY_RIGHT_BRACE     = 48,
    KEY_BACKSLASH       = 49,
    KEY_NON_US_NUM      = 50,
    KEY_SEMICOLON       = 51,
    KEY_QUOTE           = 52,
    KEY_TILDE           = 53,
    KEY_COMMA           = 54,
    KEY_PERIOD          = 55,
    KEY_SLASH           = 56,
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
    KEY_NUM_LOCK		= 0x53,
    KEYPAD_SLASH        = 0x54,
    KEYPAD_ASTERICS		= 0x55,
    KEYPAD_MINUS 		= 0x56,
    KEYPAD_PLUS 		= 0x57,
    KEYPAD_ENTER 		= 0x59,
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
    KEY_APPLICATION		= 0x65, // Context menu/right click
    
    // Most of the following keys will only work with Linux or not at all.
    // F13+ keys are mostly used for laptop functions like ECO key.
    KEY_POWER			= 0x66,
    KEY_PAD_EQUAL		= 0x67,
    KEY_F13				= 0x68,
    KEY_F14				= 0x69,
    KEY_F15				= 0x6A,
    KEY_F16				= 0x6B,
    KEY_F17				= 0x6C,
    KEY_F18				= 0x6D,
    KEY_F19				= 0x6E,
    KEY_F20				= 0x6F,
    KEY_F21				= 0x70,
    KEY_F22				= 0x71,
    KEY_F23				= 0x72,
    KEY_F24				= 0x73,
    KEY_EXECUTE			= 0x74,
    KEY_HELP			= 0x75,
    KEY_MENU			= 0x76,
    KEY_SELECT			= 0x77,
    KEY_STOP			= 0x78,
    KEY_AGAIN			= 0x79,
    KEY_UNDO			= 0x7A,
    KEY_CUT				= 0x7B,
    KEY_COPY			= 0x7C,
    KEY_PASTE			= 0x7D,
    KEY_FIND			= 0x7E,
    KEY_MUTE	  		= 0x7F,
    KEY_VOLUME_MUTE	    = 0x7F, // Alias
    KEY_VOLUME_UP		= 0x80,
    KEY_VOLUME_DOWN	    = 0x81,
    KEY_LOCKING_CAPS_LOCK	= 0x82,
    KEY_LOCKING_NUM_LOCK	= 0x83,
    KEY_LOCKING_SCROLL_LOCK	= 0x84,
    KEYPAD_COMMA			= 0x85,
    KEYPAD_EQUAL_SIGN		= 0x86, // Dont confuse with KEYPAD_EQUAL
    KEY_INTERNATIONAL1		= 0x87,
	KEY_INTERNATIONAL2		= 0x88,
	KEY_INTERNATIONAL3		= 0x89,
	KEY_INTERNATIONAL4		= 0x8A,
	KEY_INTERNATIONAL5		= 0x8B,
	KEY_INTERNATIONAL6		= 0x8C,
	KEY_INTERNATIONAL7		= 0x8D,
	KEY_INTERNATIONAL8		= 0x8E,
	KEY_INTERNATIONAL9		= 0x8F,
	KEY_LANG1				= 0x90,
	KEY_LANG2				= 0x91,
	KEY_LANG3				= 0x92,
	KEY_LANG4				= 0x93,
	KEY_LANG5				= 0x94,
	KEY_LANG6				= 0x95,
	KEY_LANG7				= 0x96,
	KEY_LANG8				= 0x97,
	KEY_LANG9				= 0x98,
	KEY_ALTERNATE_ERASE		= 0x99,
	KEY_SYSREQ_ATTENTION	= 0x9A,
    KEY_CANCEL		        = 0x9B,
    KEY_CLEAR		        = 0x9C,
    KEY_PRIOR		        = 0x9D,
    KEY_RETURN		        = 0x9E, // Do not confuse this with KEY_ENTER
    KEY_SEPARATOR		    = 0x9F,
    KEY_OUT		            = 0xA0,
    KEY_OPER		        = 0xA1,
    KEY_CLEAR_AGAIN		    = 0xA2,
    KEY_CRSEL_PROPS		    = 0xA3,
    KEY_EXSEL		        = 0xA4,
    
    KEY_PAD_00				    = 0xB0,
    KEY_PAD_000				    = 0xB1,
    KEY_THOUSANDS_SEPARATOR	    = 0xB2,
    KEY_DECIMAL_SEPARATOR	    = 0xB3,
    KEY_CURRENCY_UNIT		    = 0xB4,
    KEY_CURRENCY_SUB_UNIT	    = 0xB5,
    KEYPAD_LEFT_BRACE		    = 0xB6,
    KEYPAD_RIGHT_BRACE		    = 0xB7,
    KEYPAD_LEFT_CURLY_BRACE	    = 0xB8,
    KEYPAD_RIGHT_CURLY_BRACE    = 0xB9,
    KEYPAD_TAB		            = 0xBA,
    KEYPAD_BACKSPACE		    = 0xBB,
    KEYPAD_A		            = 0xBC,
    KEYPAD_B		            = 0xBD,
    KEYPAD_C		            = 0xBE,
    KEYPAD_D		            = 0xBF,
    KEYPAD_E		            = 0xC0,
    KEYPAD_F		            = 0xC1,
    KEYPAD_XOR		            = 0xC2,
    KEYPAD_CARET		        = 0xC3,
    KEYPAD_PERCENT		        = 0xC4,
    KEYPAD_LEFT_ANGLE		    = 0xC5,
    KEYPAD_RIGHT_ANGLE		    = 0xC6,
    KEYPAD_AMPERSAND		    = 0xC7,
    KEYPAD_DOUBLE_AMPERSAND		= 0xC8,
    KEYPAD_PIPE		            = 0xC9,
    KEYPAD_DOUBLE_PIPE	        = 0xCA,
    KEYPAD_COLON	            = 0xCB,
    KEYPAD_POUND	            = 0xCC,
    KEYPAD_SPACE	            = 0xCD,
    KEYPAD_AT	                = 0xCE,
    KEYPAD_EXCLAMATION	        = 0xCF,
    KEYPAD_MEMORY_STORE	        = 0xD0,
    KEYPAD_MEMORY_RECALL	    = 0xD1,
    KEYPAD_MEMORY_CLEAR	        = 0xD2,
    KEYPAD_MEMORY_ADD	        = 0xD3,
    KEYPAD_MEMORY_SUBTRACT	    = 0xD4,
    KEYPAD_MEMORY_MULTIPLY	    = 0xD5,
    KEYPAD_MEMORY_DIVIDE	    = 0xD6,
    KEYPAD_PLUS_MINUS	        = 0xD7,
    KEYPAD_CLEAR	            = 0xD8,
    KEYPAD_CLEAR_ENTRY	        = 0xD9,
    KEYPAD_BINARY	            = 0xDA,
    KEYPAD_OCTAL	            = 0xDB,
    KEYPAD_DECIMAL	            = 0xDC,
    KEYPAD_HEXADECIMAL	        = 0xDD,
    
    // Used in KeyboardModifier enum directly
    //KEY_LEFT_CTRL		    = 0xE0,
	//KEY_LEFT_SHIFT		= 0xE1,
	//KEY_LEFT_ALT		    = 0xE2,
	//KEY_LEFT_GUI		    = 0xE3,
	//KEY_RIGHT_CTRL		= 0xE4,
	//KEY_RIGHT_SHIFT		= 0xE5,
	//KEY_RIGHT_ALT		    = 0xE6,
	//KEY_RIGHT_GUI		    = 0xE7,
};

// Keyboard Leds
enum KeyboardLeds : uint8_t {
	LED_NUM_LOCK		= (1 << 0),
	LED_CAPS_LOCK		= (1 << 1),
	LED_SCROLL_LOCK		= (1 << 2),
	LED_COMPOSE			= (1 << 3),
	LED_KANA			= (1 << 4),
	LED_POWER			= (1 << 5),
	LED_SHIFT			= (1 << 6),
	LED_DO_NOT_DISTURB	= (1 << 7),
};

#define SHIFT 0x80
static const uint8_t _asciimap[] PROGMEM =
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
	KEY_1|SHIFT,	   		// !
	KEY_QUOTE|SHIFT,	   	// "
	KEY_3|SHIFT,    		// #
	KEY_4|SHIFT,    		// $
	KEY_5|SHIFT,    		// %
	KEY_7|SHIFT,    		// &
	KEY_QUOTE,          	// '
	KEY_9|SHIFT,    		// (
	KEY_0|SHIFT,    		// )
	KEY_8|SHIFT,    		// *
	KEY_EQUAL|SHIFT,    	// +
	KEY_COMMA,          	// ,
	KEY_MINUS,          	// -
	KEY_PERIOD,          	// .
	KEY_SLASH,          	// /
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
	KEY_SEMICOLON|SHIFT,	// :
	KEY_SEMICOLON,          // ;
	KEY_COMMA|SHIFT,      	// <
	KEY_EQUAL,          	// =
	KEY_PERIOD|SHIFT,      	// >
	KEY_SLASH|SHIFT,      	// ?
	KEY_2|SHIFT,      		// @
	KEY_A|SHIFT,      		// A
	KEY_B|SHIFT,      		// B
	KEY_C|SHIFT,      		// C
	KEY_D|SHIFT,      		// D
	KEY_E|SHIFT,      		// E
	KEY_F|SHIFT,      		// F
	KEY_G|SHIFT,      		// G
	KEY_H|SHIFT,      		// H
	KEY_I|SHIFT,      		// I
	KEY_J|SHIFT,      		// J
	KEY_K|SHIFT,      		// K
	KEY_L|SHIFT,      		// L
	KEY_M|SHIFT,      		// M
	KEY_N|SHIFT,      		// N
	KEY_O|SHIFT,      		// O
	KEY_P|SHIFT,      		// P
	KEY_Q|SHIFT,      		// Q
	KEY_R|SHIFT,      		// R
	KEY_S|SHIFT,      		// S
	KEY_T|SHIFT,      		// T
	KEY_U|SHIFT,      		// U
	KEY_V|SHIFT,      		// V
	KEY_W|SHIFT,      		// W
	KEY_X|SHIFT,      		// X
	KEY_Y|SHIFT,      		// Y
	KEY_Z|SHIFT,      		// Z
	KEY_LEFT_BRACE,         // [
	KEY_BACKSLASH,          // bslash
	KEY_RIGHT_BRACE,        // ]
	KEY_6|SHIFT,    		// ^
	KEY_MINUS|SHIFT,    	// _
	KEY_TILDE,          	// `
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
	KEY_LEFT_BRACE|SHIFT,   // {
	KEY_BACKSLASH|SHIFT,    // |
	KEY_RIGHT_BRACE|SHIFT,  // }
	KEY_TILDE|SHIFT,    	// ~
	KEY_RESERVED			// DEL
};

