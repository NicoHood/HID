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

// Keyboard Modifiers
enum KeyboardMods : uint16_t {
	MOD_LEFT_CTRL		= (1 <<  8),
	MOD_LEFT_SHIFT		= (1 <<  9),
	MOD_LEFT_ALT		= (1 << 10),
	MOD_LEFT_GUI		= (1 << 11),
	MOD_RIGHT_CTRL		= (1 << 12),
	MOD_RIGHT_SHIFT		= (1 << 13),
	MOD_RIGHT_ALT		= (1 << 14),
	MOD_RIGHT_GUI		= (uint16_t)(1 << 15),
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

#ifndef HID_CUSTOM_LAYOUT
	#define HID_CUSTOM_LAYOUT
	#define LAYOUT_US_ENGLISH
	#pragma message "Using default ASCII layout for keyboard modules"
#else
	#pragma message "Using custom layout for keyboard modules"
#endif

#if defined(LAYOUT_US_ENGLISH)
	#include "ImprovedKeylayoutsUS.h"
#elif defined(LAYOUT_CANADIAN_FRENCH)
#elif defined(LAYOUT_CANADIAN_MULTILINGUAL)
#elif defined(LAYOUT_DANISH)
#elif defined(LAYOUT_FINNISH)
#elif defined(LAYOUT_FRENCH)
#elif defined(LAYOUT_FRENCH_BELGIAN)
#elif defined(LAYOUT_FRENCH_SWISS)
#elif defined(LAYOUT_GERMAN)
	#include "ImprovedKeylayoutsDE.h"
#elif defined(LAYOUT_GERMAN_MAC)
#elif defined(LAYOUT_GERMAN_SWISS)
#elif defined(LAYOUT_ICELANDIC)
#elif defined(LAYOUT_IRISH)
#elif defined(LAYOUT_ITALIAN)
#elif defined(LAYOUT_NORWEGIAN)
#elif defined(LAYOUT_PORTUGUESE)
#elif defined(LAYOUT_PORTUGUESE_BRAZILIAN)
#elif defined(LAYOUT_SPANISH)
#elif defined(LAYOUT_SPANISH_LATIN_AMERICA)
#elif defined(LAYOUT_SWEDISH)
#elif defined(LAYOUT_TURKISH)
#elif defined(LAYOUT_UNITED_KINGDOM)
#elif defined(LAYOUT_US_INTERNATIONAL)
#endif

// Hut1_12v2.pdf
/*
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

    // Keyboard HID mappings

    //  Reserved (no_event_indicated)
    HID_KEYBOARD_ERROR_ROLLOVER	= 0x01,
    HID_KEYBOARD_POST_FAIL	= 0x02,
    HID_KEYBOARD_ERROR_UNDEFINED	= 0x03,
    HID_KEYBOARD_A_AND_A	= 0x04,
    HID_KEYBOARD_B_AND_B	= 0x05,
    HID_KEYBOARD_C_AND_C	= 0x06,
    HID_KEYBOARD_D_AND_D	= 0x07,
    HID_KEYBOARD_E_AND_E	= 0x08,
    HID_KEYBOARD_F_AND_F	= 0x09,
    HID_KEYBOARD_G_AND_G	= 0x0A,
    HID_KEYBOARD_H_AND_H	= 0x0B,
    HID_KEYBOARD_I_AND_I	= 0x0C,
    HID_KEYBOARD_J_AND_J	= 0x0D,
    HID_KEYBOARD_K_AND_K	= 0x0E,
    HID_KEYBOARD_L_AND_L	= 0x0F,
    HID_KEYBOARD_M_AND_M	= 0x10,
    HID_KEYBOARD_N_AND_N	= 0x11,
    HID_KEYBOARD_O_AND_O	= 0x12,
    HID_KEYBOARD_P_AND_P	= 0x13,
    HID_KEYBOARD_Q_AND_Q	= 0x14,
    HID_KEYBOARD_R_AND_R	= 0x15,
    HID_KEYBOARD_S_AND_S	= 0x16,
    HID_KEYBOARD_T_AND_T	= 0x17,
    HID_KEYBOARD_U_AND_U	= 0x18,
    HID_KEYBOARD_V_AND_V	= 0x19,
    HID_KEYBOARD_W_AND_W	= 0x1A,
    HID_KEYBOARD_X_AND_X	= 0x1B,
    HID_KEYBOARD_Y_AND_Y	= 0x1C,
    HID_KEYBOARD_Z_AND_Z	= 0x1D,
    HID_KEYBOARD_1_AND_EXCLAMATION_POINT	= 0x1E,
    HID_KEYBOARD_2_AND_AT	= 0x1F,
    HID_KEYBOARD_3_AND_POUND	= 0x20,
    HID_KEYBOARD_4_AND_DOLLAR	= 0x21,
    HID_KEYBOARD_5_AND_PERCENT	= 0x22,
    HID_KEYBOARD_6_AND_CARAT	= 0x23,
    HID_KEYBOARD_7_AND_AMPERSAND	= 0x24,
    HID_KEYBOARD_8_AND_ASTERISK	= 0x25,
    HID_KEYBOARD_9_AND_LEFT_PAREN	= 0x26,
    HID_KEYBOARD_0_AND_RIGHT_PAREN	= 0x27,
    HID_KEYBOARD_ENTER	= 0x28,	 // (MARKED AS ENTER_SLASH_RETURN)
    HID_KEYBOARD_ESCAPE	= 0x29,
    HID_KEYBOARD_DELETE	= 0x2A,	// (BACKSPACE)
    HID_KEYBOARD_TAB	= 0x2B,
    HID_KEYBOARD_SPACEBAR	= 0x2C,
    HID_KEYBOARD_MINUS_AND_UNDERSCORE	= 0x2D,	 // (UNDERSCORE)
    HID_KEYBOARD_EQUALS_AND_PLUS	= 0x2E,
    HID_KEYBOARD_LEFT_BRACKET_AND_LEFT_CURLY_BRACE	= 0x2F,
    HID_KEYBOARD_RIGHT_BRACKET_AND_RIGHT_CURLY_BRACE	= 0x30,
    HID_KEYBOARD_BACKSLASH_AND_PIPE	= 0x31,
    HID_KEYBOARD_NON_US_POUND_AND_TILDE	= 0x32,
    HID_KEYBOARD_SEMICOLON_AND_COLON	= 0x33,
    HID_KEYBOARD_QUOTE_AND_DOUBLEQUOTE	= 0x34,
    HID_KEYBOARD_GRAVE_ACCENT_AND_TILDE	= 0x35,
    HID_KEYBOARD_COMMA_AND_LESS_THAN	= 0x36,
    HID_KEYBOARD_PERIOD_AND_GREATER_THAN	= 0x37,
    HID_KEYBOARD_SLASH_AND_QUESTION_MARK	= 0x38,
    HID_KEYBOARD_CAPS_LOCK	= 0x39,
    HID_KEYBOARD_F1	= 0x3A,
    HID_KEYBOARD_F2	= 0x3B,
    HID_KEYBOARD_F3	= 0x3C,
    HID_KEYBOARD_F4	= 0x3D,
    HID_KEYBOARD_F5	= 0x3E,
    HID_KEYBOARD_F6	= 0x3F,
    HID_KEYBOARD_F7	= 0x40,
    HID_KEYBOARD_F8	= 0x41,
    HID_KEYBOARD_F9	= 0x42,
    HID_KEYBOARD_F10	= 0x43,
    HID_KEYBOARD_F11	= 0x44,
    HID_KEYBOARD_F12	= 0x45,
    HID_KEYBOARD_PRINTSCREEN	= 0x46,
    HID_KEYBOARD_SCROLL_LOCK	= 0x47,
    HID_KEYBOARD_PAUSE	= 0x48,
    HID_KEYBOARD_INSERT	= 0x49,
    HID_KEYBOARD_HOME	= 0x4A,
    HID_KEYBOARD_PAGE_UP	= 0x4B,
    HID_KEYBOARD_DELETE_FORWARD	= 0x4C,
    HID_KEYBOARD_END	= 0x4D,
    HID_KEYBOARD_PAGE_DOWN	= 0x4E,
    HID_KEYBOARD_RIGHTARROW	= 0x4F,
    HID_KEYBOARD_LEFTARROW	= 0x50,
    HID_KEYBOARD_DOWNARROW	= 0x51,
    HID_KEYBOARD_UPARROW	= 0x52,
    HID_KEYPAD_NUM_LOCK_AND_CLEAR	= 0x53,
    HID_KEYPAD_DIVIDE	= 0x54,
    HID_KEYPAD_MULTIPLY	= 0x55,
    HID_KEYPAD_SUBTRACT	= 0x56,
    HID_KEYPAD_ADD	= 0x57,
    HID_KEYPAD_ENTER	= 0x58,
    HID_KEYPAD_1_AND_END	= 0x59,
    HID_KEYPAD_2_AND_DOWN_ARROW	= 0x5A,
    HID_KEYPAD_3_AND_PAGE_DOWN	= 0x5B,
    HID_KEYPAD_4_AND_LEFT_ARROW	= 0x5C,
    HID_KEYPAD_5	= 0x5D,
    HID_KEYPAD_6_AND_RIGHT_ARROW	= 0x5E,
    HID_KEYPAD_7_AND_HOME	= 0x5F,
    HID_KEYPAD_8_AND_UP_ARROW	= 0x60,
    HID_KEYPAD_9_AND_PAGE_UP	= 0x61,
    HID_KEYPAD_0_AND_INSERT	= 0x62,
    HID_KEYPAD_PERIOD_AND_DELETE	= 0x63,
    HID_KEYBOARD_NON_US_BACKSLASH_AND_PIPE	= 0x64,
    HID_KEYBOARD_APPLICATION	= 0x65,
    HID_KEYBOARD_POWER	= 0x66,
    HID_KEYPAD_EQUALS	= 0x67,
    HID_KEYBOARD_F13	= 0x68,
    HID_KEYBOARD_F14	= 0x69,
    HID_KEYBOARD_F15	= 0x6A,
    HID_KEYBOARD_F16	= 0x6B,
    HID_KEYBOARD_F17	= 0x6C,
    HID_KEYBOARD_F18	= 0x6D,
    HID_KEYBOARD_F19	= 0x6E,
    HID_KEYBOARD_F20	= 0x6F,
    HID_KEYBOARD_F21	= 0x70,
    HID_KEYBOARD_F22	= 0x71,
    HID_KEYBOARD_F23	= 0x72,
    HID_KEYBOARD_F24	= 0x73,
    HID_KEYBOARD_EXECUTE	= 0x74,
    HID_KEYBOARD_HELP	= 0x75,
    HID_KEYBOARD_MENU	= 0x76,
    HID_KEYBOARD_SELECT	= 0x77,
    HID_KEYBOARD_STOP	= 0x78,
    HID_KEYBOARD_AGAIN	= 0x79,
    HID_KEYBOARD_UNDO	= 0x7A,
    HID_KEYBOARD_CUT	= 0x7B,
    HID_KEYBOARD_COPY	= 0x7C,
    HID_KEYBOARD_PASTE	= 0x7D,
    HID_KEYBOARD_FIND	= 0x7E,
    HID_KEYBOARD_MUTE	= 0x7F,
    HID_KEYBOARD_VOLUME_UP	= 0x80,
    HID_KEYBOARD_VOLUME_DOWN	= 0x81,
    HID_KEYBOARD_LOCKING_CAPS_LOCK	= 0x82,
    HID_KEYBOARD_LOCKING_NUM_LOCK	= 0x83,
    HID_KEYBOARD_LOCKING_SCROLL_LOCK	= 0x84,
    HID_KEYPAD_COMMA	= 0x85,
    HID_KEYPAD_EQUAL_SIGN	= 0x86,
    HID_KEYBOARD_INTERNATIONAL1	= 0x87,
    HID_KEYBOARD_INTERNATIONAL2	= 0x88,
    HID_KEYBOARD_INTERNATIONAL3	= 0x89,
    HID_KEYBOARD_INTERNATIONAL4	= 0x8A,
    HID_KEYBOARD_INTERNATIONAL5	= 0x8B,
    HID_KEYBOARD_INTERNATIONAL6	= 0x8C,
    HID_KEYBOARD_INTERNATIONAL7	= 0x8D,
    HID_KEYBOARD_INTERNATIONAL8	= 0x8E,
    HID_KEYBOARD_INTERNATIONAL9	= 0x8F,
    HID_KEYBOARD_LANG1	= 0x90,
    HID_KEYBOARD_LANG2	= 0x91,
    HID_KEYBOARD_LANG3	= 0x92,
    HID_KEYBOARD_LANG4	= 0x93,
    HID_KEYBOARD_LANG5	= 0x94,
    HID_KEYBOARD_LANG6	= 0x95,
    HID_KEYBOARD_LANG7	= 0x96,
    HID_KEYBOARD_LANG8	= 0x97,
    HID_KEYBOARD_LANG9	= 0x98,
    HID_KEYBOARD_ALTERNATE_ERASE	= 0x99,
    HID_KEYBOARD_SYSREQ_SLASH_ATTENTION	= 0x9A,
    HID_KEYBOARD_CANCEL	= 0x9B,
    HID_KEYBOARD_CLEAR	= 0x9C,
    HID_KEYBOARD_PRIOR	= 0x9D,
    HID_KEYBOARD_RETURN	= 0x9E,
    HID_KEYBOARD_SEPARATOR	= 0x9F,
    HID_KEYBOARD_OUT	= 0xA0,
    HID_KEYBOARD_OPER	= 0xA1,
    HID_KEYBOARD_CLEAR_SLASH_AGAIN	= 0xA2,
    HID_KEYBOARD_CRSEL_SLASH_PROPS	= 0xA3,
    HID_KEYBOARD_EXSEL	= 0xA4,
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
*/

/*
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
*/
