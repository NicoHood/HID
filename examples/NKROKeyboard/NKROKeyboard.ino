/*
  Copyright (c) 2014-2015 NicoHood
  See the readme for credit to other people.

  NKROKeyboard example

  Press a button to press a lot of keys at the same time.
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
  // Press a lot of keys at the same time
  if (!digitalRead(pinButton)) {
    digitalWrite(pinLed, HIGH);

    NKROKeyboard.press('a');
    NKROKeyboard.press('b');
    NKROKeyboard.press('c');
    NKROKeyboard.press('d');
    NKROKeyboard.press('e');
    NKROKeyboard.press('f');
    NKROKeyboard.press('g');
    NKROKeyboard.press('h');
    NKROKeyboard.press('i');
    NKROKeyboard.press('j');
    NKROKeyboard.press('k');
    NKROKeyboard.press('l');
    NKROKeyboard.press('m');
    NKROKeyboard.press('n');
    NKROKeyboard.press('o');
    NKROKeyboard.press('p');
    NKROKeyboard.press('q');
    NKROKeyboard.press('r');
    NKROKeyboard.press('s');
    NKROKeyboard.press('t');
    NKROKeyboard.press('u');
    NKROKeyboard.press('v');
    NKROKeyboard.press('w');
    NKROKeyboard.press('x');
    NKROKeyboard.press('y');
    NKROKeyboard.press('z');

    // Release all keys and hit enter
    NKROKeyboard.releaseAll();
    NKROKeyboard.println();

    // Simple debounce
    delay(300);
  }
}

