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

// include the standard leonardo board definition file
#include "../leonardo/pins_arduino.h"

//================================================================================
// HID Settings
//================================================================================

/*
You have two options to enable/disbale hid functions:

The nearly full automatic way which enables the specific hid report for you,
enables the specific hid api and also enables the keyboard led function if needed.

The fully customizable variant where you can create your very own HID report.
You still can use the predefined hid reports or add you very own ones.
You have to enable the specific hid apis on your own then, also the keyboard led function.
*/

#define HID_AUTOMATIC
//#define HID_CUSTOM_SETTINGS

//================================================================================
// Automatic
//================================================================================

#ifdef HID_AUTOMATIC
// pre selected hid reports with autoinclude of the api
#define HID_MOUSE_ENABLE // normal mouse with buttons + wheel
//#define HID_MOUSE_ABSOLUTE_ENABLE // only works with system and without gamepad
#define HID_KEYBOARD_LEDS_ENABLE // leds OR keys
//#define HID_KEYBOARD_KEYS_ENABLE
//#define HID_RAWHID_ENABLE // currently not working
//#define HID_CONSUMERCONTROL_ENABLE
//#define HID_SYSTEMCONTROL_ENABLE
//#define HID_GAMEPAD_ENABLE // only works without mouse absolute

//================================================================================
// Custom Settings
//================================================================================

#elif defined(HID_CUSTOM_SETTINGS)

// default setting here shows a mouse + keyboard with no led function
// like in IDE 1.0.6/1.5.8 or lower

// use this to enable the Keyboard Led functions
//#define HID_KEYBOARD_LEDS_ENABLED

// add your custom report here:
#define EXTERN_HID_REPORT \
HID_REPORT_KEYBOARD_KEYS(HID_REPORTID_KEYBOARD), \
HID_REPORT_MOUSE(HID_REPORTID_MOUSE)

// activate your custom HID-APIs here:
#define HID_MOUSE_API_ENABLE
//#define HID_MOUSE_ABSOLUTE_API_ENABLE
#define HID_KEYBOARD_API_ENABLE
//#define HID_RAWHID_API_ENABLE
//#define HID_CONSUMERCONTROL_API_ENABLE
//#define HID_SYSTEMCONTROL_API_ENABLE
//#define HID_GAMEPAD_API_ENABLE
//#define HID_ENABLE_ALL_APIS // enables all of the ones above


//// 2nd example with a custom Joystick report (the Gamepad API wont work anymor since the report is different)
//#define EXTERN_HID_REPORT \ /* Gamepad with 32 buttons and 10 axis*/ \
//0x05, 0x01,							/* USAGE_PAGE (Generic Desktop) */ \
//0x09, 0x04,							/* USAGE (Joystick) */ \
//0xa1, 0x01,							/* COLLECTION (Application) */ \
//0x85, HID_REPORTID_GAMEPAD,					/*   REPORT_ID */ \
///* 32 Buttons */ \
//0x05, 0x09,							/*   USAGE_PAGE (Button) */ \
//0x19, 0x01,							/*   USAGE_MINIMUM (Button 1) */ \
//0x29, 0x20,							/*   USAGE_MAXIMUM (Button 32) */ \
//0x15, 0x00,							/*   LOGICAL_MINIMUM (0) */ \
//0x25, 0x01,							/*   LOGICAL_MAXIMUM (1) */ \
//0x75, 0x01,							/*   REPORT_SIZE (1) */ \
//0x95, 0x20,							/*   REPORT_COUNT (32) */ \
//0x81, 0x02,							/*   INPUT (Data,Var,Abs) */ \
///* 10 8bit Axis */ \
//0x05, 0x01,							/*   USAGE_PAGE (Generic Desktop) */ \
//0xa1, 0x00,							/*   COLLECTION (Physical) */ \
//0x09, 0x30,							/*     USAGE (X) */ \
//0x09, 0x31,							/*     USAGE (Y) */ \
//0x09, 0x33,							/*     USAGE (Rx) */ \
//0x09, 0x34,							/*     USAGE (Ry) */ \
//0x09, 0x32,							/*     USAGE (Z) */ \
//0x09, 0x35,							/*     USAGE (Rz) */ \
//0x09, 0x36,							/*	   Usage (Slider) */ \
//0x09, 0x36,							/*	   Usage (Slider) */ \
//0x09, 0x36,							/*	   Usage (Slider) */ \
//0x09, 0x36,							/*	   Usage (Slider) */ \
//0x15, 0x80,							/*     LOGICAL_MINIMUM (-128) */ \
//0x25, 0x7F,							/*     LOGICAL_MAXIMUM (127) */ \
//0x75, 0x08,							/*     REPORT_SIZE (8) */ \
//0x95, 0x0A,							/*     REPORT_COUNT (10) */ \
//0x81, 0x02,							/*     INPUT (Data,Var,Abs) */ \
//0xc0,								/*   END_COLLECTION */ \
//0xc0								/* END_COLLECTION */
//
//// activate your custom HID-APIs here:
////#define HID_MOUSE_API_ENABLE
////#define HID_MOUSE_ABSOLUTE_API_ENABLE
////#define HID_KEYBOARD_API_ENABLE
////#define HID_RAWHID_API_ENABLE
////#define HID_CONSUMERCONTROL_API_ENABLE
////#define HID_SYSTEMCONTROL_API_ENABLE
////#define HID_GAMEPAD_API_ENABLE
////#define HID_ENABLE_ALL_APIS // enables all of the ones above


/*
You can use the pre defined reports as well.
Keep in mind that changing the ids or reports might confuse your OS.
Then you might need to reinstall all drivers or change the USB PID.
Mouse Abs only works with a System report together.
Gamepad and Mouse Abs dont work together.
Gamepads can causes some recognition problems with some OS.
RAW HID seems to not works properly in a multireport.
Currently available pre defined reports :
*/

//HID_REPORT_KEYBOARD_LEDS(HID_REPORTID_KEYBOARD),
//HID_REPORT_KEYBOARD_KEYS(HID_REPORTID_KEYBOARD),
//HID_REPORT_MOUSE(HID_REPORTID_MOUSE),
//HID_REPORT_MOUSE_ABSOLUTE(HID_REPORTID_MOUSE_ABSOLUTE),
//HID_REPORT_RAWHID(HID_REPORTID_RAWHID),
//HID_REPORT_CONSUMERCONTROL(HID_REPORTID_CONSUMERCONTROL),
//HID_REPORT_SYSTEMCONTROL(HID_REPORTID_SYSTEMCONTROL),
//HID_REPORT_GAMEPAD(HID_REPORTID_GAMEPAD),

#else
#error Please select automatic or custom hid report in the pins_arduino.h!
#endif