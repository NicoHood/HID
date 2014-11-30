Arduino HID Project 2.0 (Uno/Mega/Leonardo/Micro)
=================================================
![Header Picture](header.jpg)

This project went through a lot of phases and has now reached an HID library with 3 software solutions.
The idea is to enable enhanced USB functions to almost all 'standard' Arduino boards.
This is done with slightly different methods for different boards.

**Arduino IDE 1.5.8 is required for the HID Project.**

**Supported HID devices:**

* Keyboard with Leds out (modifiers + 6 keys pressed at the same time)
* Mouse (5 buttons, move, wheel)
* Media Keys (4 keys for music player, webbrowser and more)
* System Key (for PC standby/shutdown)
* 1 Gamepad (32 buttons, 4 16bit axis, 2 8bit axis, 2 D-Pads)

**Supported Arduinos:**
* Uno
* Mega
* Leonardo
* (Pro)Micro
* Any other 8u2/16u/at90usb162/32u2/32u4 compatible board

| Leonardo/Micro             | Uno/Mega HoodLoader2        | Uno/Mega HoodLoader1                  |
|:---------------------------|:----------------------------|---------------------------------------|
| Extended Arduino USB-Core  | Same Core as Leonardo/Micro | Coded with Lufa                       |
| More HID devices           | Fully reprogrammable 16u2   | No reprogrammable 16u2                |
| Keyboard Led Out report    | Serial0 fully usable        | Main MCU sends HID reports on Serial0 |
| System Wakeup fix (soon)   |                             | Serial Protocol filters HID reports   |
| Serial Control Line access |                             | Built-in ISP function                 |

The HID project contains HID APIs to generate HID reports and functions to send them to the USB Host.
The API (syntax/usage) of the HID Project is always the same for each solution, **you can port code from one device to another very easy**.

* On a Leonardo this function is extended and improved to get more HID devices + some improvements.
* [HoodLoader2](https://github.com/NicoHood/HoodLoader2) is a BootLoader for the 16u2 that let's you use it as standalone MCU with the same USB-Core.
* [HoodLoader1](https://github.com/NicoHood/HoodLoader) is a 16u2 firmware that filters special HW Serial signals from the main MCU and sends HID signals to the USB Host.


To make things more clear the HID Software is in a separate repository than the HoodLoader (1 & 2) sources and installing instructions.
**HoodLoader 1&2 is only used for an Uno/Mega to actually enable USB functions.** The 16u2 is normally used for USB-Serial programming of the main MCU but can do way more than that.
To use HoodLoader1&2 you also need the HID Project. For more information and installation instructions see the specific repository.

HoodLoader1 was the first solution to enable HID functions to the Uno/Mega but HoodLoader2 opens way more options because you can reprogram the whole MCU standalone.
See the repository for more infos about this great new opportunity. HoodLoader1 API is still usable in a specific example. HoodLoader1&2 are not needed/compatible with a Leonardo/Micro.

Installation
============

**Please remove any older HID Project files from your sketchbook and your Arduino core to not run into any problems.**

Download the library and [install it](http://arduino.cc/en/pmwiki.php?n=Guide/Libraries) like you are used to (access the examples, keywords.txt with IDE).
Then **move and replace** all .h and .cpp files to the path below. **I strongly recommend to install the library like this. Otherwise it wont work.**

```
C:\Arduino\arduino-1.5.8\hardware\arduino\avr\cores\arduino
```
The installation path may differ to yours. **Please use Arduino IDE 1.5.8** and file an issue if a newer version isn't working.
Restart the IDE. Ensure all drivers are installed. See [this](https://learn.sparkfun.com/tutorials/disabling-driver-signature-on-windows-8/disabling-signed-driver-enforcement-on-windows-8)
on how to install the unsigned HoodLoader2 drivers.

**If you are using an Arduino Uno/Mega follow the installation instructions of the HoodLoader1 or 2** (no extra hardware needed, just a few cables).
You can grab the latest version + installing instructions of each HoodLoader in its own repository linked above.

Of course the new version [HoodLoader2](https://github.com/NicoHood/HoodLoader2) is recommend and HoodLoader1 API is only for compatibility reasons online.
The old, full HoodLoader1 HID (software)solution (before update 2.0) can be found here: https://github.com/NicoHood/HID/tree/3d8a9b40752a143141b8be4b8f744e203c80b000


How to use
==========

### Micro/Leonardo + HoodLoader2

**Edit the USBAPI.h you installed to de/activate usb functions.** By default only Mouse and Keyboard is activated.
The more you activate the more flash is used. For the Uno/Mega you have a limited ram/flash size, so please try not to exceed this limit and only use the needed HID devices.
RawHID is currently not working properly.

**Try the Basic examples for each HID device. They are pretty much self explaining.**

**The HoodLoader2 examples are to show some special cases for the 16u2.** It shows how to remove the USB functions if needed,
how to optimally use ram since its limited and some ported sketches to reprogram the main MCU or for the missing ISP function. Please check them out.


### HoodLoader1

**Try the HoodLoader1 example. It provides the basic Serial protocol API to send HID reports. You have to copy this to every sketch again.**

With HoodLoader1 you can **only use baud 115200 for HID** due to speed/programming reasons.
Use Serial.begin(115200) in every HoodLoader1 sketch.
Its not bad anyway because its the fastest baud and you want fast HID recognition.
You still can **fully use any other baud** for normal sketches but HID wont work.
If you try nevertheless it will output Serial crap to the monitor.

Keep in mind that HoodLoader1 has **no flush function**. If the PC is reading HID too slow it can miss data, like on a Raspberry Pi.
Add a delay to the sending function or just use the newer HoodLoader2.

Always release buttons to not cause any erros. Replug USB cable to reset the values if anything went wrong.
Keep in mind that **with HoodLoader1 the 16u2 is always on**. The 16u2 and its HID reports are not reset if the main MCU is reset.
So you need to reset the HID reports on every startup with a begin() of each used API.
On Windows every USB report will reset when you open the lock screen.
See [deactivate HID function (Hoodloader only)](https://github.com/NicoHood/Hoodloader) how to temporary disable HID again.

For **16u2 as ISP usage** (optional, Hoodloader only, has nothing to do with HID function)
see [Hoodloader repository](https://github.com/NicoHood/Hoodloader).

The sending API is no longer integrated directly in the HID Project since it is now more an extended USB-Core and this has nothing to do with it.
Its more a legacy version to still use HoodLoader1 or to reimplement something similar with HoodLoader2 if you still want full report access for the main MCU.

**The older, full integrated HID Core can be found here.** Keep in mind to remove all newer stuff since it may conflict (a clean arduino core would do it).
It is not better than this solution, maybe easier to use since its just more integrated.
https://github.com/NicoHood/HID/tree/3d8a9b40752a143141b8be4b8f744e203c80b000


How it works
============
For the Leonardo/Micro + HoodLoader2 its a modified version of the HID descriptors and USB-Core.
This changes were made to improve the functions, add more devices and add u2 series compatibility.

HoodLoader1 only:
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
* See HoodLoader1&2 repository for more credits/links

**Projects can be found here:**
* [Gamecube to PC adapter](https://github.com/NicoHood/Nintendo)
* [Other projects](http://nicohood.wordpress.com/)
* For donations please contact me on my blog :)

Ideas for the future
====================
* Add more devices (even more?, voice device, flight control?)
* Add Midi (no more free Endpoints, possible on 32u4)
* Add HID rumble support (very hard)

Known Bugs
==========
See [Hoodloader repository](https://github.com/NicoHood/Hoodloader) for Hoodloader related Bugs/Issues.

System Wakeup is currently not working on all versions! Will be fixed soon!
System Shutdown is only working on Windows systems.

RawHID is not working properly, test it at your own risk.

Feel free to open an Issue on Github if you find a bug. Or message me via my [blog](http://nicohood.wordpress.com/)!

Known Issues
============

**If You have weird Problems especially with controllers, let me know.**
Sometimes the problem is just that Windows messes up the PID so you might want to compile the hoodloader with a different PID
or reinstall the drivers. With HoodLoader1 we had a lot of problems especially with linux.

XBMC 13.1 (a Media Center) uses Gamepad input. Its seems to not work and may cause weird errors.
Even with a standard Gamepad I have these errors. Just want to mention it here.

The USB implementation of the Leonardo/Micro is not that good it can cause errors or disconnects with massiv Serial input.
This has nothing to do with this library! For example Adalight dosnt work well for me,
so you better use an Arduino Uno with Hoodloader1 (yes the older one!) for Mediacenter control and Ambilight.

Do not use HID in interrupts because it uses Serial (Hoodloader1 only). Your Arduino can crash!

HoodLoader1 only: If you get a checksum error after uploading please message me and send me the whole project.
Same if your Arduino crashes and dont want to upload sketches anymore (Replug usb fixes this).
These bugs occurred while developing the bootloader and should be fixed. Just in case it happens again I noted it here.
USB can behave weird, so please check your code for errors first. If you cannot find a mistake open a Github issue.

Version History
===============
```
2.0 Release (29.11.2014)
* Added HoodLoader2
* Separated HoodLoader1&2 more
* Added u2 series for USB-Core
* Extended USB core and fixed minor things for the u2 series
* Added Led Out report.
* Added CDC Line state
* Reworked the whole library structure again

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

