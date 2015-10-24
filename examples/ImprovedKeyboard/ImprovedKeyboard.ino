/*
  Copyright (c) 2014-2015 NicoHood
  See the readme for credit to other people.

  Improved Keyboard example

  Shows how to use the new Keyboard API.

  See HID Project documentation for more information.
  https://github.com/NicoHood/HID/wiki/Keyboard-API#improved-keyboard
*/

#include "HID-Project.h"

const int pinLed = LED_BUILTIN;
const int pinButton = 2;

void setup() {
  pinMode(pinLed, OUTPUT);
  pinMode(pinButton, INPUT_PULLUP);

  // Sends a clean report to the host. This is important on any Arduino type.
  Keyboard.begin();
}


void loop() {
  // Trigger caps lock manually via button
  if (!digitalRead(pinButton)) {
    digitalWrite(pinLed, HIGH);

    // Use the default print functions
    Keyboard.println("Hello World!");

    // Press a single character, special non ascii characters wont work.
    //Keyboard.write('a');

    // Write single keys, do not use a number here!
    //Keyboard.write(KEY_ENTER);

    // If you really wish to press a RAW keycode without the name use this:
    //Keyboard.write(KeyboardKeycode(40));

    // Simple debounce
    delay(300);
    digitalWrite(pinLed, LOW);
  }
}
