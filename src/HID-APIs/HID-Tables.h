// These mappings were extracted and transcribed from 
// http://www.usb.org_SLASH_developers_SLASH_devclass_docs_SLASH_Hut1_12v2.pdf
//
// In most cases, I've preserved the "official" USB Implementers forum 
// "Usage Name", though I've standardized some abbreviations and spacing
// that were inconsistent in the original specification. Non alpha-numeric 
// characters in symbol names were converted into those characters' names.
//
// To match Arduino code style, all hid usage names are fully upper case.
//
// Not every HID usage listed in this file is currently supported by Arduino
// In particular, any System Control or Consumer Control entry that doesn't 
// have a comment indicating that it's "HID type OSC" will require additional
// code in the Arduino core to work.
// 
// Non-working usages are listed here in the interest of not having to manually
// convert more usage names each and every time our HID stack gets a little bit
// better.
//
//
//              -- Jesse Vincent <jesse@keyboard.io>, January 2014

#pragma once

// System control mappings

#define HID_SYSTEM_POWER_DOWN	0x81	// HID type OSC
#define HID_SYSTEM_SLEEP	0x82	// HID type OSC
#define HID_SYSTEM_WAKE_UP	0x83	// HID type OSC
#define HID_SYSTEM_CONTEXT_MENU	0x84	// HID type OSC
#define HID_SYSTEM_MAIN_MENU	0x85	// HID type OSC
#define HID_SYSTEM_APP_MENU	0x86	// HID type OSC
#define HID_SYSTEM_MENU_HELP	0x87	// HID type OSC
#define HID_SYSTEM_MENU_EXIT	0x88	// HID type OSC
#define HID_SYSTEM_MENU_SELECT	0x89	// HID type OSC
#define HID_SYSTEM_MENU_RIGHT	0x8A	// HID type RTC
#define HID_SYSTEM_MENU_LEFT	0x8B	// HID type RTC
#define HID_SYSTEM_MENU_UP	0x8C	// HID type RTC
#define HID_SYSTEM_MENU_DOWN	0x8D	// HID type RTC
#define HID_SYSTEM_COLD_RESTART	0x8E	// HID type OSC
#define HID_SYSTEM_WARM_RESTART	0x8F	// HID type OSC
#define HID_D_PAD_UP	0x90	// HID type OOC
#define HID_D_PAD_DOWN	0x91	// HID type OOC
#define HID_D_PAD_RIGHT	0x92	// HID type OOC
#define HID_D_PAD_LEFT	0x93	// HID type OOC
// 0x94-0x9F are reserved
#define HID_SYSTEM_DOCK	0xA0	// HID type OSC
#define HID_SYSTEM_UNDOCK	0xA1	// HID type OSC
#define HID_SYSTEM_SETUP	0xA2	// HID type OSC
#define HID_SYSTEM_BREAK	0xA3	// HID type OSC
#define HID_SYSTEM_DEBUGGER_BREAK	0xA4	// HID type OSC
#define HID_APPLICATION_BREAK	0xA5	// HID type OSC
#define HID_APPLICATION_DEBUGGER_BREAK	0xA6	// HID type OSC
#define HID_SYSTEM_SPEAKER_MUTE	0xA7	// HID type OSC
#define HID_SYSTEM_HIBERNATE	0xA8	// HID type OSC
// 0xA9-0xAF are reserved
#define HID_SYSTEM_DISPLAY_INVERT	0xB0	// HID type OSC
#define HID_SYSTEM_DISPLAY_INTERNAL	0xB1	// HID type OSC
#define HID_SYSTEM_DISPLAY_EXTERNAL	0xB2	// HID type OSC
#define HID_SYSTEM_DISPLAY_BOTH	0xB3	// HID type OSC
#define HID_SYSTEM_DISPLAY_DUAL	0xB4	// HID type OSC
#define HID_SYSTEM_DISPLAY_TOGGLE_INT_SLASH_EXT	0xB5	// HID type OSC
#define HID_SYSTEM_DISPLAY_SWAP_PRIMARY_SLASH_SECONDARY	0xB6	// HID type OSC
#define HID_SYSTEM_DISPLAY_LCD_AUTOSCALE	0xB7	// HID type OSC


