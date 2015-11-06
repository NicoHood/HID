/*
  Copyright (c) 2014-2015 NicoHood
  See the readme for credit to other people.

  Consumer example
  Press a button to play/pause music player

  You may also use SingleConsumer to use a single report.

  See HID Project documentation for more Consumer keys.
  https://github.com/NicoHood/HID/wiki/Consumer-API
*/

#include "HID-Project.h"

const int pinLed = LED_BUILTIN;
const int pinButton = 2;

void setup() {
  pinMode(pinLed, OUTPUT);
  pinMode(pinButton, INPUT_PULLUP);

  // Sends a clean report to the host. This is important on any Arduino type.
  Consumer.begin();
}

void loop() {
  if (!digitalRead(pinButton)) {
    digitalWrite(pinLed, HIGH);

    // See HID Project documentation for more Consumer keys
    Consumer.write(MEDIA_PLAY_PAUSE);

    // Simple debounce
    delay(300);
    digitalWrite(pinLed, LOW);
  }
}
