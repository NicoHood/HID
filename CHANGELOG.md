# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).
This changlog uses the [ISO 8601 date format](https://www.iso.org/iso-8601-date-and-time-format.html) of (YYYY-MM-DD).

## [Unreleased]

## [2.8.2] - 2021-07-14

### Fixed

* Improved Windows 7 Absolute Mouse compatibility [#306](https://github.com/NicoHood/HID/issues/305) (Thanks [@mdevaev](https://github.com/mdevaev))

## [2.8.1] - 2021-07-14

### Changed

* Moved License from readme to its own file
* Moves this changelog from readme into its own file (following keepachangelog format)

### Fixed
* Improved Mac Mouse compatibility [#305](https://github.com/NicoHood/HID/issues/305) (Thanks [@mdevaev](https://github.com/mdevaev))

## [2.8.0] - 2021-04-08

### Added

* Added lots of keyboard layout languages (Thanks [@SukkoPera](https://github.com/SukkoPera))

## [2.7.0] - 2021-03-06

### Added

* Added support for Italien Keymap [#231](https://github.com/NicoHood/HID/issues/231)

### Changed

* Changed: Use a fixed definion of keycodes and add language specific variants

### Fixed

* Fix SAMD compilation [#244](https://github.com/NicoHood/HID/issues/244)

## [2.6.2] - 2020-12-24

### Fixed

* Fix SAMD alignment [#211](https://github.com/NicoHood/HID/issues/211)
* Fix asciimap size check [#228](https://github.com/NicoHood/HID/issues/228)

## [2.6.1] - 2019-07-13

### Added

* Allow keyboard layout change within arduino sketch [#176](https://github.com/NicoHood/HID/issues/176)

## [2.6.0] - 2019-04-16

### Added

* Added generic keyboard layout support [#168](https://github.com/NicoHood/HID/issues/168)

## [2.5.0] - 2018-09-15

### Added

* Ported to SAMD architecture [#146](https://github.com/NicoHood/HID/issues/146)

### Fixed

* Fixed bad keyboard report issue [#148](https://github.com/NicoHood/HID/issues/148)


## [2.4.4] - 2017-01-27

### Added

* Added `releaseAll()` to Mouse API

### Fixed

* Fix flexible array errors


## [2.4.3] - 2016-03-02

### Fixed

* Fixed NKRO Keyboard modifier add() [#76](https://github.com/NicoHood/HID/issues/76)


## [2.4.2] - 2015-12-19

### Fixed

* RawHID >64 byte fix (Arduino IDE 1.6.8 fix)
* Fixed Keyboard modifier add() issue [#68](https://github.com/NicoHood/HID/issues/68)

## [2.4.1] - 2015-12-19

### Added

* Added Keyboard Feature Report

### Changed

* RawHID Improvements

### Fixed

* NKRO and Keyboard API fixes
* Arduino library manager fix

## [2.4] - 2015-11-06

### Added

* Added Arduino IDE 1.6.6 compatibility with Pluggable HID
* Added NKRO Keyboard
* Added Led report for Keyboard
* Added 1 Linux consumer key for keyboard
* Added BootKeyboard/Mouse support (BIOS compatibility)
* Added RawHID
* Added a few key definitions
* Uses .alinkage custom IDE option

### Changed

* Improved Pluggable HID (see Arduyuino changelog for my improvements)
* Changed USB-Core into a simple library, only made possible with Pluggable HID
* Renew whole Keyboard API and its definitions via enum
* Improved and updated examples

### Removed

* Removed HID presets in boards menu (like mouse + keyboard + consumer + system)

### Fixed

* A lot of other minor and major fixes I missed to mention.

## 2.3 (Never released)

### Added

* Added Minor Consumer definitions

### Changed

* Updated Libraries
* Updated Arduino Core
* `SERIAL_RX_BUFFER_SIZE` reverted to 16 (TODO add -D to build option)

### Fixed

* Fixed platforms.txt

## [2.2] - 2015-04-12

### Added

* Added experimental, not finished nor documented HID-Bridge between 16u2 and 328/2560
* Added colour highlighting (through HID-Bridge library)
* No USB workaround for Leonardo integrated into variants
* Added Keycode example

### Changed

* Increased HW Serial1 RX buffer size from 16 to 32 (TX still 16)
* Used `HID_KeyboardReport_Data_t` now in Keyboard API
* Changed USB Wakeup in System API

### Removed

* Removed fixed size in report buffers

### Fixed

* Arduino as ISP fix for 328
* Upload verification on USB hubs fix for HL2.0.4
* Consumer Key fix (issue [#3](https://github.com/NicoHood/HID/issues/3))
* Gamepad fix (issue [#14](https://github.com/NicoHood/HID/issues/14))
* Mouse press + release fix


## [2.1] - 2015-01-28

### Added

* Added u2 compatibility with smaller USB_EP_SIZE (16u2 etc)
* Added Serial Event for LineEncoding and LineState
* Added Serial Function to get dtr state, line encoding etc
* Added Keyboard Led Out report to get Led states (for numlock etc)
* Added Absolute Mouse
* Added Keycode functions in Keyboard API
* Added Gamepad
* Added RawHID API (but RawHID itself isnt working still)
* Added USB Wakeup support
* Added HID Tables
* USB-Serial now fully reprogrammable
* Easy USB-Core selection via Tools->USB-Core
* Added Arduino as ISP fix for 32u4 and 16u2
* Added AVR libraries to the core with the better SoftSerial

### Changed

* Reworked the whole USB-Core from scratch
* Uses less flash if HID or Serial is not used
* Extended and compacter(flash) HID Report Descriptors
* Made CDC-Core independent from USB-Core
* Made HID-Core independent from USB-Core
* Made HID-API independent from HID-Core
* Made HID Reports and its IDs replaceable via `pins_Arduino.h`
* Made void `Recv(volatile u8* data, u8 count)` in `USBCore.cpp` static inline
* HID-APIs sends a clean report on begin() and end() now.
* Inlined a lot of the HID API functions to save flash
* Separated USB-Core in its own folder
* Moved documentation to the wiki

### Removed

* Removed not needed virtual functions in Keyboard
* Removed uint8_t USBPutChar(uint8_t c); in HID.cpp
* Removed virtual functions in Keyboard API

### Fixed

* Fixed USB Device Descriptor

## [2.0] - 2014-11-29

### Added

* Added HoodLoader2
* Added u2 series for USB-Core
* Added Led Out report.
* Added CDC Line state

### Changed

* Separated HoodLoader1&2 more
* Extended USB core and fixed minor things for the u2 series
* Reworked the whole library structure again

## [1.8] Beta - 2014-08-26

### Changed

* Changes in the Hoodloader1:
 * Huge improvements, see Hoodloader1 repository
 * Reworked the whole library, easy installation now
 * HID fixes for Media Keys/Ubuntu
 * Removed Joystick, added 4 Gamepads

## 1.7.3 Beta - 2014-08-10

### Fixed

* Changes in the Hoodloader1:
 * Fixed HID flush bug (1.6 - 1.7.2)

## 1.7.2 Beta - 2014-08-10

### Added

* Changes in the Hoodloader1:
 * Added Lite version for 8u2
 * Added Versions that show up as Uno/Mega (not recommended)

### Changed

* Changes in the Hoodloader1:
 * Makefile and structure changes

## 1.7.1 Beta - 2014-08-10

### Fixed

* Changes in the Hoodloader1:
 * Fixed HID deactivation bug


## 1.7 Beta - 2014-08-10

### Changed

* Changes in the Hoodloader1:
 * Works as ISP now. See Hoodloader1 Repository for more information.
 * Exceeded 8kb limit. For flashing a 8u2 use v1.6 please!
* Changed Readme text

## 1.6 Beta - 2014-08-09

### Added

* Added RawHID Class and example

### Fixed

* Bugfixes in the Hoodloader1:
 * Changed HID management (not blocking that much, faster)
 * added RawHID in/out (HID to Serial)


## 1.5 Beta - 2014-07-21

### Changed

* Moved Hoodloader1 source to a separate Github page
* Improved the deactivate option
* Integrated NHP directly
* Replaced LightweightRingbuffer with native Lufa Ringbuffer
* Improved writing to CDC Host 
* General structure changes
* Improved stability

### Fixed

* Bugfixes in the Hoodloader:
 * Firmware is still available here
 * Overall a lot of ram improvements, now with a big global union of ram
 * Removed USBtoUSART buffer (not needed, saved 128/500 bytes)
 * Removed Lite version because of better ram usage not needed
 * Separated different modes better to not cause any errors in default 
* Fixed a bug in checkNHPProtocol: `&` needs to be a `==`
* Fixed Arduino as ISP bug


## 1.4.1 Beta - 2014-07-10

### Fixed

* `#define` Bugfix in `USBAPI.h`

## 1.4 Beta - 2014-07-10

### Added

* Added IDE v1.5.7 support
* Added Tutorials

### Changed

* Merged v1.0.x and v1.5.x together (both are compatible!)

### Fixed

* Bugfixes in the Hoodloader1:
 * Added Lite Version with less ram usage
 * Changed PIDs, edited driver file

## 1.3 Beta - 2014-07-01

### Fixed

* Important NHP fix inside the HID Class for Uno/Mega
* Improved ram usage in HoodLoader1

## 1.2 Beta - 2014-06-22

### Added

* Added Arduino IDE 1.0.x/1.5.x support

### Changed

* Minor file structure changes

### Fixed

* Bugfixes in the Hoodloader1:
  * Sometimes HID Devices weren't updating when using more than 1 Device (set forcewrite to true)
  * Fast updates crashed the bootloader (too much ram usage, set CDC buffer from 128b to 100b each)

## 1.1 Beta - 2014-06-05

### Added

* Included NicoHoodProtocol
* Added Leonardo/Micro support

### Fixed

* Minor fixes

## 1.0 Beta - 2014-06-22

### Added

* Initial Beta release

[Unreleased]: https://github.com/NicoHood/HID/compare/2.8.2...HEAD
[2.8.2]: https://github.com/NicoHood/HID/compare/2.8.1...2.8.2
[2.8.1]: https://github.com/NicoHood/HID/compare/2.8.0...2.8.1
[2.8.0]: https://github.com/NicoHood/HID/compare/2.7.0...2.8.0
[2.7.0]: https://github.com/NicoHood/HID/compare/2.6.1...2.7.0
[2.6.1]: https://github.com/NicoHood/HID/compare/2.6.0...2.6.1
[2.6.0]: https://github.com/NicoHood/HID/compare/2.5.0...2.6.0
[2.5.0]: https://github.com/NicoHood/HID/compare/2.4.4...2.5.0
[2.4.4]: https://github.com/NicoHood/HID/compare/2.4.3...2.4.4
[2.4.3]: https://github.com/NicoHood/HID/compare/2.4.2...2.4.3
[2.4.2]: https://github.com/NicoHood/HID/compare/2.4.1...2.4.2
[2.4.1]: https://github.com/NicoHood/HID/compare/2.4...2.4.1
[2.4]: https://github.com/NicoHood/HID/compare/2.2...2.4
[2.2]: https://github.com/NicoHood/HID/compare/2.1...2.2
[2.1]: https://github.com/NicoHood/HID/compare/2.0...2.1
[2.0]: https://github.com/NicoHood/HID/compare/1.8...2.0
[1.8]: https://github.com/NicoHood/HID/releases/tag/1.8
