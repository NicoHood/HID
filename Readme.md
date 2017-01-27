Arduino HID Project 2.4.4
=========================

![Header Picture](header.jpg)

This project went through a lot of phases and has now reached a new Arduino ~~USB-Core~~ Library
with a lot of new functions like extended HID. It also supports HoodLoader1+2.
The idea is to enable enhanced USB functions to almost all 'standard' Arduino boards.

**Supported Arduinos (IDE 1.6.7 or higher!):**
* Uno (with [HoodLoader2](https://github.com/NicoHood/HoodLoader2))
* Mega (with [HoodLoader2](https://github.com/NicoHood/HoodLoader2))
* Leonardo
* (Pro)Micro
* Any other 8u2/16u2/at90usb8/162/32u2/32u4 compatible board
* No SAM/ARM support (Due, Zero etc)

**Supported HID devices:**
* Keyboard with Leds out (8 modifiers + 6 keys pressed at the same time, + 1 limited linux consumer key)
* ~~Teensy Keyboard with different keyboard layouts (german, french and many more)~~ soon
* NKRO Keyboard with Leds out (press up to 113 keys at the same time)
* Mouse (5 buttons, move, wheel)
* BootKeyboard/BootMouse BIOS protocol support
* Absolute Mouse
* Consumer/Media Keys (4 keys for music player, web browser and more)
* System Key (for PC standby/shutdown)
* Gamepad (32 buttons, 4 16bit axis, 2 8bit axis, 2 D-Pads)
* RawHID
* Each device is available as single or multi report device (except RawHID)

See the [wiki](https://github.com/NicoHood/HID/wiki/Features) for more information about features etc.

Wiki
====

All documentation moved to the [wiki page](https://github.com/NicoHood/HID/wiki).

An offline snapshot is available in [releases](https://github.com/NicoHood/HID/releases).


Contact
=======

www.nicohood.de


Version History
===============
```
2.4.4 Release (27.01.2017)
* Added releaseAll() to Mouse API
* Fix flexible array errors

2.4.3 Release (02.03.2016)
* Fixed NKRO Keyboard modifier add() #76

2.4.2 Release (04.01.2016)
* RawHID >64 byte fix (Arduino IDE 1.6.8 fix)
* Fixed Keyboard modifier add() issue #68

2.4.1 Release (19.12.2015)
* RawHID Improvements
* Added Keyboard Feature Report
* NKRO and Keyboard API fixes
* Arduino library manager fix

2.4 Release (06.11.2015)
* Added Arduino IDE 1.6.6 compatibility with Pluggable HID
* Improved Pluggable HID (see Arduyuino changelog for my improvements)
* Changed USB-Core into a simple library, only made possible with Pluggable HID
* Removed HID presets in boards menu (like mouse + keyboard + consumer + system)
* Added NKRO Keyboard
* Added Led report for Keyboard
* Added 1 Linux consumer key for keyboard
* Added BootKeyboard/Mouse support (BIOS compatibility)
* Added RawHID
* Added a few key definitions
* Renew whole Keyboard API and its definitions via enum
* Uses .alinkage custom IDE option
* Improved and updated examples
* A lot of other minor and major fixes I missed to mention.

2.3 Release (never released)
* Updated Libraries
* Updated Arduino Core
* Added Minor Consumer definitions
* Fixed platforms.txt
* SERIAL_RX_BUFFER_SIZE reverted to 16 (TODO add -D to build option)

2.2 Release (12.04.2015)
* added experimental, not finished nor documented HID-Bridge between 16u2 and 328/2560
* increased HW Serial1 RX buffer size from 16 to 32 (TX still 16)
* added colour highlighting (through HID-Bridge library)
* removed fixed size in report buffers
* used HID_KeyboardReport_Data_t now in Keyboard API
* Arduino as ISP fix for 328
* Upload verification on USB hubs fix for HL2.0.4
* No USB workaround for Leonardo integrated into variants
* Changed USB Wakeup in System API
* Consumer Key fix (issue #3)
* Gamepad fix (issue #14)
* Added Keycode example
* Mouse press + release fix

2.1 Release (28.01.2015)
* Reworked the whole USB-Core from scratch
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
* Added RawHID API (but RawHID itself isnt working still)
* Added USB Wakeup support
* Separated USB-Core in its own folder
* Added HID Tables
* USB-Serial now fully reprogrammable
* Easy USB-Core selection via Tools->USB-Core
* Added Arduino as ISP fix for 32u4 and 16u2
* Moved documentation to the wiki
* Added AVR libraries to the core with the better SoftSerial

2.0 Release (29.11.2014)
* Added HoodLoader2
* Separated HoodLoader1&2 more
* Added u2 series for USB-Core
* Extended USB core and fixed minor things for the u2 series
* Added Led Out report.
* Added CDC Line state
* Reworked the whole library structure again

1.8 Beta Release (26.08.2014)
* Changes in the Hoodloader1:
 * **Huge improvements**, see Hoodloader1 repository
 * Reworked the whole library, easy installation now
 * HID fixes for Media Keys/Ubuntu
 * Removed Joystick, added 4 Gamepads

1.7.3 Beta Release (10.08.2014)
* Changes in the Hoodloader1:
 * Fixed HID flush bug (1.6 - 1.7.2)

1.7.2 Beta Release (10.08.2014)
* Changes in the Hoodloader1:
 * Added Lite version for 8u2
 * Added Versions that show up as Uno/Mega (not recommended)
 * Makefile and structure changes

1.7.1 Beta Release (10.08.2014)
* Changes in the Hoodloader1:
 * Fixed HID deactivation bug

1.7 Beta Release (10.08.2014)
* Changes in the Hoodloader1:
 * Works as ISP now. See Hoodloader1 Repository for more information.
 * Exceeded 8kb limit. For flashing a 8u2 use v1.6 please!
* Changed Readme text

1.6 Beta Release (09.08.2014)
* Bugfixes in the Hoodloader1:
 * Changed HID management (not blocking that much, faster)
 * added RawHID in/out (HID to Serial)
* Added RawHID Class and example

1.5 Beta Release (21.07.2014)
* Moved Hoodloader1 source to a separate Github page
* Bugfixes in the Hoodloader:
 * Firmware is still available here
 * Overall a lot of ram improvements, now with a big global union of ram
 * Removed USBtoUSART buffer (not needed, saved 128/500 bytes)
 * Removed Lite version because of better ram usage not needed
 * Separated different modes better to not cause any errors in default mode
 * Improved the deactivate option
 * Integrated NHP directly
 * Replaced LightweightRingbuffer with native Lufa Ringbuffer
 * Improved writing to CDC Host
 * Fixed a bug in checkNHPProtocol: & needs to be a ==
 * General structure changes
 * Improved stability
 * Fixed Arduino as ISP bug

1.4.1 Beta Release (10.07.2014)
* #define Bugfix in USBAPI.h

1.4 Beta Release (10.07.2014)
* Bugfixes in the Hoodloader1:
 * Added Lite Version with less ram usage
 * Changed PIDs, edited driver file
* merged v1.0.x and v1.5.x together (both are compatible!)
* added IDE v1.5.7 support
* added Tutorials

1.3 Beta Release (01.07.2014)
* Bugfixes in the Hoodloader1:
 * Improved ram usage
* **Important NHP fix inside the HID Class for Uno/Mega**

1.2 Beta Release (22.06.2014)
* Added 1.0.x/1.5.x support
* Bugfixes in the Hoodloader1:
 * Sometimes HID Devices weren't updating
   when using more than 1 Device (set forcewrite to true)
 * Fast updates crashed the bootloader
  (too much ram usage, set CDC buffer from 128b to 100b each)
* Minor file structure changes

1.1 Beta Release (05.06.2014)
* Added Leonardo/Micro support
* Included NicoHoodProtocol
* Minor fixes

1.0 Beta Release (03.06.2014)
```


Licence and Copyright
=====================
If you use this library for any cool project let me know!

```
Copyright (c) 2014-2016 NicoHood
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
