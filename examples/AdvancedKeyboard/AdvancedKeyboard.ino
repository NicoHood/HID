/*
Copyright (c) 2014 NicoHood
 See the readme for credit to other people.
 
 Advanced Keyboard example
 */

// include HID library
#include <HID.h>

const int pinLed = 13;
const int pinButton = 8;

void setup() {
  pinMode(pinLed, OUTPUT);
  pinMode(pinButton, INPUT_PULLUP);

  // Starts Serial at baud 115200 otherwise HID wont work on Uno/Mega.
  // This is not needed for Leonado/(Pro)Micro but make sure to activate desired USB functions in HID.h
  Serial.begin(SERIAL_HID_BAUD);

  // Sends a clean report to the host. This is important because
  // the 16u2 of the Uno/Mega is not turned off while programming
  // so you want to start with a clean report to avoid strange bugs after reset.
  pressRawKeyboard(0, 0);
}

void loop() {
  if (!digitalRead(pinButton)) {
    digitalWrite(pinLed, HIGH);

    // This demo is actually made for advanced users to show them how they can write an own report.
    // This might be useful for a Keyboard if you only use one key, 
    // because the library has a lot of code for simple use

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
  uint8_t keys[8] = { 
    modifiers, 0, key, 0, 0, 0, 0, 0    }; //modifiers, reserved, key[0]
  HID_SendReport(HID_REPORTID_KeyboardReport, keys, sizeof(keys));
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
