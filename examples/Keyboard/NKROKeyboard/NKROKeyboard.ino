/*
  Copyright (c) 2014-2015 NicoHood
  See the readme for credit to other people.

  NKROKeyboard example

  Press a button to hold a lot of keys at the same time.
  NKRO can push 113 keys at the same time,
  the other Keyboards only 6 keys + 8 modifiers!

  You may also use SingleNKROKeyboard to enable a single report NKROKeyboard.

  See HID Project documentation for more information.
  https://github.com/NicoHood/HID/wiki/Keyboard-API#nkro-keyboard
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
    NKROKeyboard.add('0');
    NKROKeyboard.add('1');
    NKROKeyboard.add('2');
    NKROKeyboard.add('3');
    NKROKeyboard.add('4');
    NKROKeyboard.add('5');
    NKROKeyboard.add('6');
    NKROKeyboard.add('7');
    NKROKeyboard.add('8');
    NKROKeyboard.add('9');
    NKROKeyboard.send();

    // Release all keys and hit enter
    NKROKeyboard.releaseAll();
    NKROKeyboard.println();

    // Simple debounce
    delay(300);
  }
}

