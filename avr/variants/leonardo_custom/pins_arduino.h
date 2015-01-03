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
#include <../../variants/leonardo/pins_arduino.h>

//================================================================================
// HID Settings
//================================================================================

// use this to enable the Keyboard Led functions
#define HID_KEYBOARD_LEDS_ENABLED

// add your custom report here:
#define EXTERN_HID_REPORT \
HID_REPORT_KEYBOARD_LEDS(HID_REPORTID_KEYBOARD), \
HID_REPORT_MOUSE(HID_REPORTID_MOUSE)

// activate your custom HID-APIs here:
#define HID_MOUSE_API_ENABLE
#define HID_KEYBOARD_API_ENABLE
//#define HID_CONSUMER_API_ENABLE
//#define HID_SYSTEM_API_ENABLE
//#define HID_GAMEPAD_API_ENABLE

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
////HID_REPORT_RAWHID(HID_REPORTID_RAWHID), // not working at the moment
//HID_REPORT_CONSUMERCONTROL(HID_REPORTID_CONSUMERCONTROL),
//HID_REPORT_SYSTEMCONTROL(HID_REPORTID_SYSTEMCONTROL),
//HID_REPORT_GAMEPAD(HID_REPORTID_GAMEPAD),