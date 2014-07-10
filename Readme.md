Arduino HID Project BETA 1.4
===================
Dont you always wanted to turn your Arduino in a Generic HID device like a Keyboard or a Gamepad?
Disappointed that the Uno doesnt support this at all and the Micro/Leonardo only Mouse + Keyboard?

Introducing the Arduino HID Project that gives you everything you need for that.
No need for extra hardware. You just need one of the Arduinos and an USB cable.

**Main difference is that you can upload new sketches to the Uno/Mega and dont need to reflash the firmware.**
Before you had to upload a sketch, flash the firmware, test, flash the firmware, upload, flash again. Thats all gone!

**For the Leonardo/Micro it is 'just' new device stuff, no need for a bootloader.**

Features
========
Use your **Arduino Uno, Mega, Micro, Leonardo or Micro Pro** as Generic HID Device and still be able to upload sketches how you are used to do.
This project provides a new bootloader for the 8u2/16u2 and HID libraries Arduino Uno/Mega and Micro/Leonardo.
I also corrected some bugs in the original sources.

**Software includes:**

* Arduino HID Uno/Mega library
* Arduino HID Micro/Leonardo library
* Arduino HID Bootloader (Hoodloader) + driver
* Compatible with Linux/Mac/Windows XP/7/8.1*
* Compatible with IDE 1.0.x - 1.5.7 (newer versions might need an update)

**The following devices are supported:**

* Keyboard (modifiers + 6 keys)
* Mouse (5 buttons, move, wheel)
* Media Keys (4 keys for music player)
* System Key (for PC standby/shutdown)
* 2 Gamepads (32 buttons, 6 16bit axis, 2 D-Pads)
* 2 Joysticks (2 buttons, 2 10bit axis)

**Projects can be found here:**
* [Gamecube to PC adapter](https://github.com/NicoHood/Nintendo)
* [Other projects](http://nicohood.wordpress.com/)

Installation Leonardo/Micro/Uno/Mega
====================================
Download the library and install like you are used to.
Then **move and replace** all files from "HID_Source" to the folder that matches your Arduino IDE version to one of these paths
(depending on your version):
```
C:\Arduino\arduino-1.0.5\hardware\arduino\cores\arduino
C:\Arduino\arduino-1.5.6-r2\hardware\arduino\avr\cores\arduino
C:\Arduino\arduino-1.5.7\hardware\arduino\avr\cores\arduino
```
The installation path may differ to yours. Newer Versions than 1.5.7 may not work.

**I strongly recommend to install the library like this. Otherwise it wont work.**
Now you are able to use the library with all kind of Arduinos. The HID include and HID.begin() is optional for Leonardo/Micro
but necessary for Uno/Mega. I'd recommend to use it every time so you can port the library from one to another device.

#### Leonardo/Micro only
**Edit HID.h to de/activate usb functions.** Each function will take some flash,
so if you want to save flash deactivate everything you dont need.
By default Mouse, Keyboard, Media, System, Gamepad1 is activated.
You cannot use more than 255 bytes HID report on the leonardo/micro.
The number after each definition tells you the size of each report.
I have no idea why you cannot use more than 255 bytes (yet).

#### Uno/Mega only
To **install the new bootloader** connect your Arduino to your PC and put it into DFU mode.
**You can always switch back to the original firmware, nothing to break.**
See the readme in the Firmware folder or [this general (outdated) tutorial](http://arduino.cc/en/Hacking/DFUProgramming8U2)
on how to upload the hex file to your Arduino. Some notes here: The Arduino R3 doesnt need a resistor or so, just connect the two pins near
the USB B jack. Choose atmega16u2 for the new R3 version. For older version you need to check Google.
For a Flip dll error install the drivers manually from the flip directory.

Upload the hex file to your Arduino (The Lite Version is only if you have any Problems. Its takes less Ram).
It doesnt care if its a Uno/Mega/Mega ADK. It will just work the same.
Unplug the Arduino if it says successful and plug it back in. You cannot destroy anything here and you can always
switch back to the original firmware which is included with the download.
**You need to install new drivers for the new device on Windows.** Actually they are not new, its just an .inf file that tells
Windows to use its built in CDC Serial driver. Ironically Microsoft never signed its own driver.
Also see [this tutorial](http://arduino.cc/en/guide/windows) on how to install the drivers (rightclick the .inf file and hit install).
[How to install drivers for Windows 8/8.1](https://learn.sparkfun.com/tutorials/disabling-driver-signature-on-windows-8/disabling-signed-driver-enforcement-on-windows-8).
If you want it to be recognized as Uno/Mega edit the makefile. I dont recommend this to know what
Bootloader currently is on your Board.

For Arduino Mega2560 I recommend the nightly IDE. [See Issue on Github.](https://github.com/arduino/Arduino/issues/1071)

#### For all Arduinos
You are ready to use the libraries. **Just have a look at the examples and test it out.**
The libraries will work for all Arduinos listed above but it will use 2 different HID libraries.
**On Arduino/Mega you can only use baud 115200 for HID** due to programming reasons. Its not bad anyway
because its the fastest baud and you want fast HID recognition. You still can use any other baud for
normal sketches without HID. The HID include and HID.begin() is not needed for Leonardo/Micro.

**Always release buttons to not cause any erros.** Replug USB cable to reset the values if anything went wrong.
Connect GND and MOSI2 to deactivate HID function on Uno/Mega (see picture)

How does it work
================
For the Leonardo/Micro its just a modified version of the HID descriptor and Classes for the new devices.
Its not that complicated, everything you need is in the main 4 .h/cpp files.

For the Uno/Mega you need a special Bootloader. Why? Because the Uno/Mega has 2 chips on board.
The 328/2560 and 16u2 each. And the only communication between the 16u2 and the main chip is via Serial.
But the Serial is also used to program the chip. So what i do here is to filter out all Serial Data that comes in
via the NicoHoodProtocol (NHP). There is an indicator ad Address 1 which contains the beginning and the Report ID.
If the following Serial information is Address 2 with a valid checksum the report will be created and sent if its
finished successful. If any error occurred within the first 2 Protocol Addresses the information will be sent via Serial.
The Program should forward this information because it could be a normal information. Everything above 2 Addresses that goes
wrong wont be sent and discarded due to a normal wrong HID report. Normally you dont have to worry about getting weird HID
presses. You need to send exactly 6 bytes with the special Numbers and another 6 bytes for the first information with checksum.
And if the reading timed out the Data will also be forwarded. And if you only send Ascii Code the Information is forwarded instantly
because the NHP filters that out instantly (see documentation of the NHP).

To sum it up: Serial information is grabbed by the "man in the middle" and you dont have to worry to get any wrong report.
See picture how to deactivate HID function by hardware.

This library wouldnt be possible without
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

Todo
====
* Remove debug stuff (shouldnt effect anything for you)
* Add more devices (even more?)
* Add Midi  (do you want that?)
* Add ICSP Programmer function (ram limit is a problem)
* Add Led/SPI support (discarded, not needed, too slow)
* Add rumble support (very hard)
* Add Xbox Support (too hard)
* Add Report Out function (for Keyboard Leds etc, maybe the 4 pin header?)
* RAW HID

Known Bugs
==========
**If You have weird Problems especially with controllers, let me know.
You can try the Lite version that uses less Ram (smaller Serial Buff).
Sometimes the Problem is just that Windows messes up the PID, so changing to Lite can help**

XBMC 13.1 (a Media Center) uses Gamepad input. Its seems to not work and may cause weird errors.
Even with a standard Gamepad I have these errors. Just want to mention it here.

System Wakeup is currently not working on all versions!

Not tested on the 8u2 (should only work without DFU due to size. message me if it works!)

Not tested on the Due (message me if it works!)

If you get a checksum error after uploading please message me and send me the whole project.
Same if your Arduino crashes and dont want to upload sketches anymore (Replug usb fixes this).
These bugs occurred while developing the bootloader and should be fixed. Just in case it happens again I noted it here.
USB can behave weird, so please check your code for errors first. If you cannot find a mistake open a Github issue.

HID only works with baud 115200 (on Uno/Mega) because there is no "programming finished" indicator. If you dont use HID you can still choose the baud of your choice.

Oh and by the way: I also removed some bugs from the official firmware.

Version History
===============
```
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

The Bootloader was coded with Windows7 and Visual Studio and compiled with a Raspberry Pi.
Lufa version 140302 is included!
**To recompile see instructions in Hoodloader_Source/Readme.md**

The difference between the Leonardo/Micro and Uno/Mega is that the HID Class is different. All other classes are the same.
The Leonardo/Micro Version uses USBAPI.h and no Serial while the Uno/Mega Version uses Serial.
You can also modify the library to send HID reports to other devices/other serials.
Just modify the HID Class (#define HID_SERIAL Serial).

To uninstall the drivers on windows you need [registrar](http://www.resplendence.com/registrar).
Delete these entrys (my gamepad driver with the PID was **still broken**. The only way to fix this was ti change the PID.
If you know how to fix this message me.):
```
HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Enum\USB\VID_03EB&PID_4E48
HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Enum\USB\VID_03EB&PID_4E48&MI_00
HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Enum\USB\VID_03EB&PID_4E48&MI_02
```

