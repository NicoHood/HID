TODO
====

Under Construction. This is a todo list for myself and a feature list so far.

```
Keyboard Layout for different Languages
Clean up USB Core code from fixed values. Use better understandable definitions
Magic key fix for 32u4?

Add Keywords.txt definitions
add examples
keycode/raw for keyboard
Check Keyboard keycode function again?
Generalize HID key definitions via HIDTables for example?
Add custom HID reports example
add copyright

update Burning via ISP (advanced)
Test with Android phone
update no usb workaround notice (no longer needed for hoodloader2, but for leonardo)


Bugs
Mouse Abs only works with system report under special circumstances.
Gamepad + Mouse Abs doesnt work (fix Gamepad)
Fix HID_SendReport() prototype workaround in HID-APIs
```


```
(flash numbers might be irrelevant due to a lot of improvements)
* Uses less flash if HID or Serial is not used
* Extended and compacter(flash) HID Report Descriptors
* Fixed USB Device Descriptor
* Added u2 compatibility with smaller USB_EP_SIZE (16u2 etc)
* Added Serial Event for LineEncoding and LineState (+12b flash)
* Added Serial Function to get dtr state, line encoding etc
* Added Keyboard Led Out report to get Led states (for numlock etc, +52b flash, 1b ram)
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