Arduino HID Project
===================
Dont you always wanted to turn your Arduino in a Generic HID device like a Keyboard or a Gamepad?
Disappointed that the Uno doesnt support this at all and the Micro/Leonardo only Mouse + Keyboard?

Introducing the Arduino HID Project that gives you everything you need for that.
No need for extra hardware. You just need one of the Arduinos and an USB cable.

Features
========
Use your **Arduino Uno, Mega, Micro, Leonardo or Micro Pro** as Generic HID Device and still be able to upload sketches how you are used to do.
This project provides a new bootloader for the 8u2/16u2 and HID libraries Arduino Uno/Mega and Micro/Leonardo.
I also corrected some bugs in the original sources.

Software includes:

* Arduino HID Uno/Mega library
* Arduino HID Micro/Leonardo library
* Arduino HID Bootloader
* [NicoHoodProtocol](https://github.com/NicoHood/NicoHoodProtocol) library needed for the Uno/Mega!

The following devices are supported:

* Keyboard (modifiers + 6 keys)
* Mouse (5 buttons, move, wheel)
* Media Keys (4 keys for music player)
* System Key (for PC standby/shutdown)
* 2 Gamepads (32 buttons, 6 16bit axis, 2 D-Pads)
* 2 Joysticks (2 buttons, 2 10bit axis)

Projects can be found here:
http://nicohood.wordpress.com/

Installation
============
Download the library and rename the folder. See [this instruction](http://arduino.cc/en/Guide/Libraries) how to install new libraries.

[NicoHoodProtocol](https://github.com/NicoHood/NicoHoodProtocol) library needed for the Uno/Mega!

**Always release buttons to not cause any erros. Replug USB cable to reset the values if anything went wrong.
Connect GND and MOSI2 to deactivate HID function on Uno/Mega**

*Arduino Uno/Mega only*
To install the new bootloader connect your Arduino to your PC and put it into DFU mode.
See [this](http://arduino.cc/en/Hacking/DFUProgramming8U2) and [this](http://forum.arduino.cc/index.php?topic=111.0)
and also [this](http://andrewmemory.wordpress.com/2011/04/14/upgrading-the-arduino-uno-8u2-using-flip/) on how to upload
the hey file to your Arduino. Some notes here: The Arduino R3 doesnt need a resistor or so, just connect the two pins near
the USB B jack. Choose atmega16u2 for the new R3 version. For older version you need to check the links.

Upload the hex file to your Arduino. It doesnt care if its a Uno/Mega/Mega ADK. It will just work the same.
Unplug the Arduino if it sais successful and plug it back in. You cannot destroy anything here and you can always
switch back to the original firmware.
You need to install new drivers for that on Windows. Actually they are not new, its just an .inf file that tells
Windows to use its built in CDC Serial driver. Ironically Microsoft never signed its own driver.
Also see [this tutorial](http://arduino.cc/en/guide/windows) on how to install the drivers.

You are ready to use the libraries. Just have a look at the examples and test it out.
The libraries will work for all Arduinos listed above but it will use 2 different libraries.
On Arduino/Mega you can only use baud 115200 for HID due to programming reasons. Its not bad anyways
because its the fastest baud and you want fast HID recognition. You still can use any other baud for
normal sketches without HID.

For Arduino Mega2560 I recommend the nightly IDE. See Issue on Github.
```
https://github.com/arduino/Arduino/issues/1071
http://downloads.arduino.cc/arduino-avr-toolchain-nightly-gcc-4.8.1-linux32.tgz
http://downloads.arduino.cc/arduino-avr-toolchain-nightly-gcc-4.8.1-linux64.tgz
http://downloads.arduino.cc/arduino-avr-toolchain-nightly-gcc-4.8.1-macosx.zip
http://downloads.arduino.cc/arduino-avr-toolchain-nightly-gcc-4.8.1-windows.zip
```

This library wouldnt be possible without
========================================

[Lufa 140302 from Dean Camera](http://www.fourwalledcubicle.com/LUFA.php)
[Darran's HID Projects] (https://github.com/harlequin-tech/arduino-usb)
[Connor's Joystick for the Leonardo](http://www.imaginaryindustries.com/blog/?p=80)
[Stefan Jones Multimedia Keys Example](http://stefanjones.ca/blog/arduino-leonardo-remote-multimedia-keys/)
[Athanasios Douitsis Multimedia Keys Example](https://github.com/aduitsis/ardumultimedia)
[The Original Arduino Sources](https://github.com/arduino/Arduino/tree/master/hardware/arduino/firmwares/atmegaxxu2/arduino-usbserial)
A lot of searching through the web
The awesome official Arduino IRC chat!
[The NicoHood Protocol ^.^](https://github.com/NicoHood/NicoHoodProtocol)

For donations please contact me on my blog :)

Todo
====
Micro/Leonardo library
License!!!
Remove debug leds
Add more devices
Add ICSP Programmer function
Add rumble support
Add Xbox Support
Add Midi Support
Add Report Out function (for Keyboard Leds etc)
To deactivate the HID function bridge Pin x with x

Known Bugs
==========
HID only works with baud 115200 because there is no "programming finished" indicator. If you dont use HID you can still choose the baud of your choice

System Wakeup is currently not working for Arduino Uno/Mega.

Not tested on the 8u2

If you get a checksum Error after Uploading please message me and send me the whole project.
Same if your Arduino crashes and dont want to upload sketches anymore (Replug usb fixes this).
These bugs occured while devoloping the bootloader and should be fixed. Just in case it happens again I noted it here.

Version History
===============
```
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
While developing i had that much trouble that i had to change the PID. No way to repair the broken windows driver settings.
So be careful if you change the source on your own with important PIDs.
Therefore uninstall the divers for any device or just dont touch the HID reports.

You need to install avr-gcc for compiling
```
sudo apt-get install avr-gcc
```

To uninstall the drivers on windows you need [registrar](http://www.resplendence.com/registrar).
Delete these entrys (my gamepad driver with the PID was still broken. If you know how to fix this message me):
```
HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Enum\USB\VID_03EB&PID_4E48
HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Enum\USB\VID_03EB&PID_4E48&MI_00
HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Enum\USB\VID_03EB&PID_4E48&MI_02
```

