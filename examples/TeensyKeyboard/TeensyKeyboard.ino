/*
  Copyright (c) 2014 NicoHood
  See the readme for credit to other people.

  Teens Keyboard example
  Press a button to write some text to your PC.

  You can change the keyboard layout to a different language.

  See official and HID Project documentation for more infos
  https://github.com/NicoHood/HID/wiki/Keyboard-API
*/

// Add this before you include the HID-Project.
// This is required because the Teensy uses different KEY definitions.
#define USE_TEENSY_KEYBOARD
#include "HID-Project.h"

const int pinLed = LED_BUILTIN;
const int pinButton = 2;

void setup() {
  pinMode(pinLed, OUTPUT);
  pinMode(pinButton, INPUT_PULLUP);

  // Sends a clean report to the host. This is important on any Arduino type.
  TeensyKeyboard.begin();
}


void loop() {
  if (!digitalRead(pinButton)) {
    digitalWrite(pinLed, HIGH);

    // Similar the official library, pretty much self explaining
    TeensyKeyboard.println(F("This message was sent with my Arduino."));
    TeensyKeyboard.println(F("Lowercase:  abcdefghijklmnopqrstuvwxyz"));
    TeensyKeyboard.println(F("Uppercase:  ABCDEFGHIJKLMNOPQRSTUVWXYZ"));

    // For a single keypress use press() and release()
    TeensyKeyboard.press(KEY_ENTER);
    TeensyKeyboard.releaseAll();

    // Do NOT use write(). See documentation for more help.
    //TeensyKeyboard.write(KEY_ENTER);

    // Simple debounce
    delay(300);
    digitalWrite(pinLed, LOW);
  }
}

