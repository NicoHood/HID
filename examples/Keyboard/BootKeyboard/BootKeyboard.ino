/*
  Copyright (c) 2014-2015 NicoHood
  See the readme for credit to other people.

  BootKeyboard example

  Shows that keyboard works even in bios.
  Led indicats if we are in bios.

  See HID Project documentation for more information.
  https://github.com/NicoHood/HID/wiki/Keyboard-API#boot-keyboard
*/

#include "HID-Project.h"

const int pinLed = LED_BUILTIN;
const int pinButton = 2;

void setup() {
  pinMode(pinLed, OUTPUT);
  pinMode(pinButton, INPUT_PULLUP);

  // Sends a clean report to the host. This is important on any Arduino type.
  BootKeyboard.begin();
}


void loop() {
  // Light led if keyboard uses the boot protocol (normally while in bios)
  // Keep in mind that on a 16u2 and Arduino Micro HIGH and LOW for TX/RX Leds are inverted.
  if (BootKeyboard.getProtocol() == HID_BOOT_PROTOCOL)
    digitalWrite(pinLed, HIGH);
  else
    digitalWrite(pinLed, LOW);

  // Trigger caps lock manually via button
  if (!digitalRead(pinButton)) {
    BootKeyboard.write(KEY_ENTER);

    // Simple debounce
    delay(300);
  }
}
