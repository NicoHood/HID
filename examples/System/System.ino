/*
  Copyright (c) 2014-2015 NicoHood
  See the readme for credit to other people.

  System example
  Press a button to put pc into sleep/shut it down or wake it up again.

  You may also use SingleSystem to use a single report.

  See HID Project documentation for more Consumer keys.
  https://github.com/NicoHood/HID/wiki/System-API
*/

#include "HID-Project.h"

const int pinLed = LED_BUILTIN;
const int pinButtonS = 2;
const int pinButtonW = 3;

void setup() {
  // prepare led + buttons
  pinMode(pinLed, OUTPUT);
  pinMode(pinButtonS, INPUT_PULLUP);
  pinMode(pinButtonW, INPUT_PULLUP);

  // Sends a clean report to the host. This is important on any Arduino type.
  System.begin();
}

void loop() {
  if (!digitalRead(pinButtonS)) {
    digitalWrite(pinLed, HIGH);

    // Puts PC into sleep mode/shuts it down
    System.write(SYSTEM_SLEEP);
    //System.write(SYSTEM_POWER_DOWN);

    // Simple debounce
    delay(300);
    digitalWrite(pinLed, LOW);
  }

  if (!digitalRead(pinButtonW)) {
    digitalWrite(pinLed, HIGH);

    // Try to wake up the PC
    // This might fail on some PCs/Laptops where USB wakeup is not supported
    System.write(SYSTEM_WAKE_UP);

    // Simple debounce
    delay(300);
    digitalWrite(pinLed, LOW);
  }
}
