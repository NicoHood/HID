Installation
============

put these files into *sketchbook/hardware/HID/*

at the moment you have to move
the cores/hid folder into your Arduino installation because of a bug in the ide.
This Core is ment to use with 1.5.8 or newer Arduino IDE

You can compile all HID APIs
but this doesnt mean that you can use them if no hid descriptor is set correctly.

TODO
====

Under Construction. This is a todo list for myself and a feature list so far.

```
Keyboard Layout for different Languages
Clean up USB Core code from fixed values. Use better understandable definitions
Magic key fix for 32u4?

Add Keywords.txt definitions
keycode/raw for keyboard
Check Keyboard keycode function again?
Generalize HID key definitions via HIDTables for example?
Add custom HID reports example

update Burning via ISP (advanced)
Test with Android phone
update no usb workaround notice (no longer needed for hoodloader2, but for leonardo)


Bugs
Mouse Abs only works with system report under special circumstances.
Gamepad + Mouse Abs doesnt work (fix Gamepad)
Fix HID_SendReport() prototype workaround in HID-APIs
Core selection in boards.txt is not working

Do not name the Arduino Sketch 'Mouse.ino' or 'Keyboard.ino' etc.
Your Arduino IDE will output errors then if you double click the file and try to compile.
```


```
* Uses less flash if HID or Serial is not used
* Extended and compacter(flash) HID Report Descriptors
* Fixed USB Device Descriptor
* Added u2 compatibility with smaller USB_EP_SIZE (16u2 etc)
* Added Serial Event for LineEncoding and LineState
* Added Serial Function to get dtr state, line encoding etc
* Added Keyboard Led Out report to get Led states (for numlock etc)
* Made CDC-Core independent from USB-Core
* Made HID-Core independent from USB-Core
* Made HID-API independent from HID-Core
* Removed not needed virtual functions in Keyboard
* Made HID Reports and its IDs replaceable via pins_Arduino.h
* Added Absolute Mouse
* Removed uint8_t USBPutChar(uint8_t c); in HID.cpp
* Made void Recv(volatile u8* data, u8 count) in USBCore.cpp static inline
* HID-APIs sends a clean report on begin() and end() now.
* Removed virtual functions in Keyboard API
* Added Keycode functions in Keyboard API
* Inlined a lot of the HID API functions to save flash
* Added Gamepad
* Added USB Wakeup support
* Separated USB-Core in its own folder
* Added HID Tables
* USB-Serial now fully reprogrammable
```

```
Include schematic
- Arduino.h
 - USBAPI.h -> Arduino.h, USBDESC.h, USBCore.h
 - CDC.h -> Arduino.h, USBDESC.h, USBCore.h
 - HID.h -> Arduino.h, USBDESC.h, USBCore.h, HID-API
  - HID-API -> Keyboard.h, Mouse.h
   - Keyboard.h -> Arduino.h
   - Mouse.h -> Arduino.h
   - [Other APIs].h -> Arduino.h
 - HIDTables.h

HID.h contains all HID configuration.
Each HID-API (like Mouse) includes Arduino.h and gets these settings as well.
The pins_Arduino.h can overwrite each HID descriptor or define complete new one.
```

Licence and Copyright
=====================
If you use this library for any cool project let me know!

```
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
```