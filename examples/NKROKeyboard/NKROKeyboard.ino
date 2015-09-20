/*
  Copyright (c) 2014-2015 NicoHood
  See the readme for credit to other people.

  NKROKeyboard example

  Press a button to hold a lot of keys at the same time.
  NKRO can push 113 keys at the same time,
  the other Keyboards only 6 keys + 8 modifiers!

  See HID Project documentation for more information.
  https://github.com/NicoHood/HID/wiki/Keyboard-API
*/

#include "HID-Project.h"

const int pinLed = LED_BUILTIN;
const int pinButton = 2;

void setup() {
  pinMode(pinLed, OUTPUT);
  pinMode(pinButton, INPUT_PULLUP);

  // Sends a clean report to the host. This is important on any Arduino type.
  NKROKeyboard.begin();
}

void loop() {
  // Hold a lot of keys at the same time
  if (!digitalRead(pinButton)) {
    digitalWrite(pinLed, HIGH);

    // Do not press to many at once or some OS will have problems.
    // Note that the resulting pressed order might differ,
    // because all keys are pressed at the same time.
    NKROKeyboard.addKeyToReport('0');
    NKROKeyboard.addKeyToReport('1');
    NKROKeyboard.addKeyToReport('2');
    NKROKeyboard.addKeyToReport('3');
    NKROKeyboard.addKeyToReport('4');
    NKROKeyboard.addKeyToReport('5');
    NKROKeyboard.addKeyToReport('6');
    NKROKeyboard.addKeyToReport('7');
    NKROKeyboard.addKeyToReport('8');
    NKROKeyboard.addKeyToReport('9');
    NKROKeyboard.send_now();

    // Release all keys and hit enter
    NKROKeyboard.releaseAll();
    NKROKeyboard.println();

    // Simple debounce
    delay(300);
  }
}

