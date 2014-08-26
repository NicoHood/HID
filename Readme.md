Arduino HID Project
===================
Dont you always wanted to turn your Arduino in a Generic HID device like a Keyboard or a Gamepad?
Disappointed that the Uno doesnt support this at all and the Micro/Leonardo only Mouse + Keyboard?

Introducing the Arduino HID Project that **enables enhanced USB functionality to Arduino Uno, Mega, Leonardo, Micro.**
No need for extra hardware. You just need one of the Arduinos and an USB cable.

**Main difference is that you can upload new sketches to the Uno/Mega and dont need to reflash the firmware over and over again.**
Before you had to upload a sketch, flash the firmware, test, flash the firmware, upload, flash again. Thats all gone!

**For the Leonardo/Micro it is 'just' new HID devices, no need for a bootloader (like on Uno/Mega).**

Note: [Hoodloader Repository moved here.](https://github.com/NicoHood/Hoodloader)

Features
========
Use your **Arduino Uno, Mega, Micro, Leonardo or (Pro)Micro** as Generic HID Device and still be able to upload sketches how you are used to do.
This project provides HID libraries for Arduino Uno/Mega (with a new 16u2 bootloader) and Micro/Leonardo.
I also corrected some bugs in the original sources.

**Software includes:**

* Arduino HID Uno/Mega library
* Arduino HID Micro/Leonardo library
* Arduino HID Bootloader (Hoodloader) + driver for Uno/Mega
* Arduino as ISP with the 16u2 (Hoodloader only, [more information](https://github.com/NicoHood/Hoodloader))
* Compatible with Linux/Mac/Windows XP/7/8.1
* Compatible with IDE 1.0.x - 1.5.7

**The following devices are supported:**

* Keyboard (modifiers + 6 keys pressed at the same time)
* Mouse (5 buttons, move, wheel)
* Media Keys (4 keys for music player, webbrowser and more)
* System Key (for PC standby/shutdown)
* 4 Gamepads (32 buttons, 4 16bit axis, 2 8bit axis, 2 D-Pads)

**Projects can be found here:**
* [Gamecube to PC adapter](https://github.com/NicoHood/Nintendo)
* [Other projects](http://nicohood.wordpress.com/)

Version differences
===================

| Arduino Uno/Mega                       | Arduino Leonardo/(Pro)Micro        |
|:---------------------------------------|:-----------------------------------|
| HID via Hoodloader on 16u2             | Uses USB core with main MCU (32u4) |
| Serial0 without HID fully usable       | Serial0 fully usable               |
| Serial0 with HID at baud 115200 only   | Serial0 slow + buggy               |
| Serial0 with HID fully usable via USB  |                                    |
| Serial0 with HID not usable via extern |                                    |
| Uses less flash (Serial Protocol only) | Uses more flash (full USB core)    |
| ISP function                           | No ISP function                    |

Over all the Uno/Mega solution gives you more opportunities except that the Serial0 is limited when you use HID.

Installation Leonardo/Micro/Uno/Mega
====================================

#### Leonardo/Micro only
Download the library and [install it](http://arduino.cc/en/pmwiki.php?n=Guide/Libraries) like you are used to.

**For the whole Project IDE 1.5.7 or higher is recommended!**

**Edit HID.h to de/activate usb functions.**
By default Mouse, Keyboard, Media, System, Gamepad1 is activated.

Each function will take some flash,
so if you want to save flash deactivate everything you dont need.
You cannot use more than 255 bytes HID report on the Leonardo/Micro.
The number after each definition tells you the size of each report.
I have no idea why you cannot use more than 255 bytes (yet), its a bug in the Arduino code.

#### Uno/Mega onl
Download the library and [install it](http://arduino.cc/en/pmwiki.php?n=Guide/Libraries) like you are used to.

**For the whole Project IDE 1.5.7 or higher is recommended!**

To install the new bootloader connect your Arduino to your PC via USB and see
[Hoodloader installing instructions](https://github.com/NicoHood/Hoodloader).
No special programmer needed, just an USB cable.
**You can always switch back to the original firmware, nothing to break.**

Edit HID.h to add an extra delay for raspberry pi. This is a workaround to fix this for slower PCs. There is still a problem with Raspberry.

Usage
=====
You are ready to use the libraries. **Just have a look at the examples and test it out.** They are pretty much self explaining.
All examples use a button on pin 8 and show the basic usage of the libraries.
The libraries will work for all Arduinos listed above but it will use 2 different HID libraries (automatically).
For Keyboard + Mouse usage also see the [official documentation](http://arduino.cc/en/pmwiki.php?n=Reference/MouseKeyboard).

**#include <HID.h> is now needed for every device.**

**On Arduino/Mega you can only use baud 115200 for HID** due to speed/programming reasons.
Use Serial.begin(SERIAL_HID_BAUD); as typedef to start Serial at baud 115200.
Its not bad anyway because its the fastest baud and you want fast HID recognition.
You still can **fully use any other baud** for normal sketches but HID wont work.
If you try nevertheless it will output Serial crap to the monitor.

**Always release buttons to not cause any erros.** Replug USB cable to reset the values if anything went wrong.
On Windows every USB report will reset when you open the lock screen.
See [deactivate HID function (Hoodloader only)](https://github.com/NicoHood/Hoodloader) how to disable HID again.

For Arduino as ISP usage (optional, Hoodloader only, has nothing to do with HID function)
see [Hoodloader repository](https://github.com/NicoHood/Hoodloader).

Updating to a newer Version
===========================
HID library:

To upgrade to v1.8 you need to redownload the Arduino IDE files, restore the original files and install the library like you are used to.
You library is now located in sketchbook/libraries/HID/<files>
Its now way easier to install the library, no need to replace system files. For further releases just replace all files again.

**Restart the IDE**

Hoodloader (Not needed for Leonardo/Micro):

Just upload the new hex file and check the HID Project if the HID library code has changed and replace the new files too.
You normally dont need to reinstall the drivers for windows if the changelog dosnt note anything.
Versions below 1.5 might need the new drivers.

How it works
============
For the Leonardo/Micro its just a modified version of the HID descriptor and Classes for the new devices.
Its not that complicated, everything you need is in the main 4 .h/cpp files.

For the Uno/Mega you need a special Bootloader. Why? See [Hoodloader repository](https://github.com/NicoHood/Hoodloader).
To sum it up: Serial information is grabbed by the "man in the middle, 16u2" and you dont have to worry to get any wrong Serial stuff via USB.
Thatswhy you need a special baud (115200) that both sides can communicate with each other.
Every USB command is send via a special [NicoHood Protocol](https://github.com/NicoHood/NicoHoodProtocol)
that's filtered out by the 16u2. If you use Serial0 for extern devices it cannot filter the signal of course.
You can still use the NHP, just dont use the reserved Address 1.

This project wouldnt be possible without
========================================

* [Lufa 140302 from Dean Camera](http://www.fourwalledcubicle.com/LUFA.php)
* [Darran's HID Projects] (https://github.com/harlequin-tech/arduino-usb)
* [Connor's Joystick for the Leonardo](http://www.imaginaryindustries.com/blog/?p=80)
* [Stefan Jones Multimedia Keys Example](http://stefanjones.ca/blog/arduino-leonardo-remote-multimedia-keys/)
* [Athanasios Douitsis Multimedia Keys Example](https://github.com/aduitsis/ardumultimedia)
* [The Original Arduino Sources](https://github.com/arduino/Arduino/tree/master/hardware/arduino/firmwares/atmegaxxu2/arduino-usbserial)
* [USBlyzer](http://www.usblyzer.com/)
* A lot of searching through the web
* The awesome official Arduino IRC chat!
* [The NicoHood Protocol ^.^](https://github.com/NicoHood/NicoHoodProtocol)
* For donations please contact me on my blog :)

Ideas for the future
====================
* Add more devices (even more?)
* Add Midi (no more free Endpoints, possible on 32u4)
* Add HID rumble support (very hard)
* Add Xbox Support (too hard)
* Add Report Out function (for Keyboard Leds etc)

Known Bugs
==========
See [Hoodloader repository](https://github.com/NicoHood/Hoodloader) for Hoodloader related Bugs/Issues.

System Wakeup is currently not working on all versions!
System Shutdown is only working on Windows systems.

RawHID only works on Uno/Mega. It still has some bugs.

Feel free to open an Issue on Github if you find a bug. Or message me via my [blog](http://nicohood.wordpress.com/)!

Known Issues
============

**Do not name your sketch HID.ino, this wont work!**

Opening the examples with doubleclick doesnt work, starting from IDE does.

**Do not use HID in interrupts because it uses Serial (Hoodloader only). Your Arduino can crash!**

**If you get a checksum error after uploading please message me and send me the whole project.**
Same if your Arduino crashes and dont want to upload sketches anymore (Replug usb fixes this).
These bugs occurred while developing the bootloader and should be fixed. Just in case it happens again I noted it here.
USB can behave weird, so please check your code for errors first. If you cannot find a mistake open a Github issue.

**If You have weird Problems especially with controllers, let me know.**
Sometimes the problem is just that Windows messes up the PID so you might want to compile the hoodloader with a different PID
or reinstall the drivers.

XBMC 13.1 (a Media Center) uses Gamepad input. Its seems to not work and may cause weird errors.
Even with a standard Gamepad I have these errors. Just want to mention it here.

Not tested on the 8u2, lite version should work with flashing via ISP.

Not tested on the Due (message me if it works!)

The USB implementation of the Leonardo/Micro is not that good it can cause errors or disconnects with massiv Serial input.
This has nothing to do with this library! For example Adalight dosnt work well for me,
so you better use an Arduino Uno with Hoodloader for Mediacenter control and Ambilight.

Version History
===============
```
1.8 Beta Release (26.08.2014)
* Changes in the Hoodloader:
 * **Huge improvements**, see [Hoodloader repository](https://github.com/NicoHood/Hoodloader)
 * Reworked the whole library, easy installation now
 * HID fixes for Media Keys/Ubuntu
 * Removed Joystick, added 4 Gamepads

1.7.3 Beta Release (10.08.2014)
* Changes in the Hoodloader:
 * Fixed HID flush bug (1.6 - 1.7.2)

1.7.2 Beta Release (10.08.2014)
* Changes in the Hoodloader:
 * Added Lite version for 8u2
 * Added Versions that show up as Uno/Mega (not recommended)
 * Makefile and structure changes

1.7.1 Beta Release (10.08.2014)
* Changes in the Hoodloader:
 * Fixed HID deactivation bug

1.7 Beta Release (10.08.2014)
* Changes in the Hoodloader:
 * Works as ISP now. See the [Hoodloader Repository](https://github.com/NicoHood/Hoodloader) for more information.
 * Exceeded 8kb limit. For flashing a 8u2 use v1.6 please!
* Changed Readme text

1.6 Beta Release (09.08.2014)
* Bugfixes in the Hoodloader:
 * Changed HID management (not blocking that much, faster)
 * added RawHID in/out (HID to Serial)
* Added RawHID Class and example

1.5 Beta Release (21.07.2014)
* Moved Hoodloader source to a [separate Github page](https://github.com/NicoHood/Hoodloader)
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
* Bugfixes in the Hoodloader:
 * Added Lite Version with less ram usage
 * Changed PIDs, edited driver file
* merged v1.0.x and v1.5.x together (both are compatible!)
* added IDE v1.5.7 support
* added Tutorials

1.3 Beta Release (01.07.2014)
* Bugfixes in the Hoodloader:
 * Improved ram usage (you can get even better but that messes up code and increases flash)
* **Important NHP fix inside the HID Class for Uno/Mega**

1.2 Beta Release (22.06.2014)
* Added 1.0.x/1.5.x support
* Bugfixes in the Hoodloader:
 * Sometimes HID Devices weren't updating when using more than 1 Device (set forcewrite to true)
 * Fast updates crashed the bootloader (too much ram usage, set CDC buffer from 128b to 100b each)
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

For Developers
==============
If you deactivate some reports it can occur that windows will cause problems and recognize it as different device.
While developing I had that much trouble that I had to change the PID. No way to repair the broken windows driver settings.
So be careful if you change the source on your own with important PIDs. (Therefore I made a 2nd Lite Version with a different PID and more ram)
Therefore reinstall the divers for any device or just dont touch the HID reports in the Bootloader.
The Leonardo/Micro version worked fine till now.

See this how to uninstall the drivers:
https://support.microsoft.com/kb/315539

The Hootloader was coded with Windows7 and Visual Studio and compiled with a Raspberry Pi.
Lufa version 140302 is included!
**To recompile see instructions in [Hoodloader Repository](https://github.com/NicoHood/Hoodloader).**

The difference between the Leonardo/Micro and Uno/Mega is that the HID Class is different. All other classes are the same.
The Leonardo/Micro Version uses USBAPI.h and no Serial while the Uno/Mega Version uses Serial.
You can also modify the library to send HID reports to other devices/other serials.
Just modify the HID Class (#define HID_SERIAL Serial).

