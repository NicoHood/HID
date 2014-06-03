/*
Copyright (c) 2014 NicoHood
See the readme for credit to other people.

Advanced HID example
*/

// The protocol ist still needed for Uno/Mega here
#include <NicoHoodProtocol.h>
#include <HID.h>

const int pinLed = 13;
const int pinButton = 8;

// see HID_Reports.h for all data structures
HID_GamepadReport_Data_t Gamepadreport;

void setup() {
  pinMode(pinLed, OUTPUT);
  pinMode(pinButton, INPUT_PULLUP);

  // Starts Serial at baud 115200. end just ends the Serial
  // Make sure to end your special HIDs before, this does not clear them!
  // You need this baud for the HID library but still can use other bauds
  // without HID functions.
  HID.begin();

  // Sends a clean report to the host. This is important because
  // the 16u2 of the Uno/Mega is not turned off while programming
  // so you want to start with a clear report to avoid strange bugs.
  // its exactly the same like the end() function.
  // You can also unplug the device if anything goes wrong.
  // To prevent the 16u2 to send more reports just pull the Serial TX (pin1) low
  // or see readme for turning off HID functions.
  // If you did anything wrong (keyboard is doing weird stuff)
  // just logout (no shutdown needed).
  memset(&Gamepadreport, 0, sizeof(Gamepadreport));
  HID.sendReport(HID_REPORTID_Gamepad1Report, &Gamepadreport, sizeof(Gamepadreport));
  pressRawKeyboard(0, 0);
}

void loop() {
  // press a button and demonstrate Joystick actions
  if (!digitalRead(pinButton)) {
    digitalWrite(pinLed, HIGH);

    // This demo is actually made for advanced users to show them how they can write an own report.
    // This might be useful for a Gamepad or a especially Keyboard if you only use one key, 
    // because the library has a lot of code for simple use

    // count with buttons binary
    static uint32_t count = 0;
    Gamepadreport.whole32[0] = count++;

    // move x/y Axis to a new position (16bit)
    Gamepadreport.whole16[2] = (random(0xFFFF));

    // functions before only set the values
    // this writes the report to the host
    HID.sendReport(HID_REPORTID_Gamepad1Report, &Gamepadreport, sizeof(Gamepadreport));


    // press STRG + ALT + DEL on keyboard (see usb documentation)
    //pressRawKeyboard(0, 4); //modifiers + 4
    //pressRawKeyboard(0, 29); //modifiers + z
    pressRawKeyboard(RAW_KEYBOARD_LEFT_CTRL | RAW_KEYBOARD_LEFT_ALT , RAW_KEYBOARD_DELETE); //modifiers + key
    pressRawKeyboard(0, 0); // release! Important

    // simple debounce
    delay(300);
    digitalWrite(pinLed, LOW);
  }
}

void pressRawKeyboard(uint8_t modifiers, uint8_t key) {
  uint8_t keys[8] = { modifiers, 0, key, 0, 0, 0, 0, 0  }; //modifiers, reserved, key[0]
  HID.sendReport(HID_REPORTID_KeyboardReport, keys, sizeof(keys));
}

/*
See Hut1_12v2.pdf Chapter 10 (Page 53) for more Keys
(especially a-z, a=0x04 z=29)
Definitions:

RAW_KEYBOARD_LEFT_CTRL
RAW_KEYBOARD_LEFT_SHIFT
RAW_KEYBOARD_LEFT_ALT
RAW_KEYBOARD_LEFT_GUI
RAW_KEYBOARD_RIGHT_CTRL
RAW_KEYBOARD_RIGHT_SHIFT
RAW_KEYBOARD_RIGHT_ALT
RAW_KEYBOARD_RIGHT_GUI

RAW_KEYBOARD_UP_ARROW
RAW_KEYBOARD_DOWN_ARROW
RAW_KEYBOARD_LEFT_ARROW
RAW_KEYBOARD_RIGHT_ARROW
RAW_KEYBOARD_SPACEBAR
RAW_KEYBOARD_BACKSPACE
RAW_KEYBOARD_TAB
RAW_KEYBOARD_RETURN
RAW_KEYBOARD_ESC
RAW_KEYBOARD_INSERT
RAW_KEYBOARD_DELETE
RAW_KEYBOARD_PAGE_UP
RAW_KEYBOARD_PAGE_DOWN
RAW_KEYBOARD_HOME
RAW_KEYBOARD_END
RAW_KEYBOARD_CAPS_LOCK
RAW_KEYBOARD_F1
RAW_KEYBOARD_F2
RAW_KEYBOARD_F3
RAW_KEYBOARD_F4
RAW_KEYBOARD_F5
RAW_KEYBOARD_F6
RAW_KEYBOARD_F7
RAW_KEYBOARD_F8
RAW_KEYBOARD_F9
RAW_KEYBOARD_F10
RAW_KEYBOARD_F11
RAW_KEYBOARD_F12
RAW_KEYBOARD_PRINT
RAW_KEYBOARD_SCROLL_LOCK
RAW_KEYBOARD_PAUSE
*/
