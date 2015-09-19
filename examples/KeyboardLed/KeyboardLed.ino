/*
  Copyright (c) 2014-2015 NicoHood
  See the readme for credit to other people.

  KeyboardLed example

  Press a button to toogle caps lock.
  Caps lock state is represented by the onboard led.

  See HID Project documentation for more information.
  https://github.com/NicoHood/HID/wiki/Keyboard-API
*/

// Choose your favourite keyboard
#define USBKEYBOARD Keyboard

//#define USBKEYBOARD NKROKeyboard

//#define USBKEYBOARD TeensyKeyboard
//#define USE_TEENSY_KEYBOARD

#include "HID-Project.h"

const int pinLed = LED_BUILTIN;
const int pinButton = 2;

void setup() {
  pinMode(pinLed, OUTPUT);
  pinMode(pinButton, INPUT_PULLUP);

  // Sends a clean report to the host. This is important on any Arduino type.
  USBKEYBOARD.begin();
}


void loop() {
  // Update Led equal to the caps lock state.
  // Keep in mind that on a 16u2 and Arduino Micro HIGH and LOW for TX/RX Leds are inverted.
  if (USBKEYBOARD.getLeds() & LED_CAPS_LOCK)
    digitalWrite(pinLed, HIGH);
  else
    digitalWrite(pinLed, LOW);

  // Trigger caps lock manually via button
  if (!digitalRead(pinButton)) {
    USBKEYBOARD.write(KEY_CAPS_LOCK);

    // Simple debounce
    delay(300);
  }
}
