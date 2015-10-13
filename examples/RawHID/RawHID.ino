/*
  Copyright (c) 2014-2015 NicoHood
  See the readme for credit to other people.

  Advanced RawHID example

  Shows how to send bytes via RawHID.
  Press a button to send some example values.

  See HID Project documentation for more information.
  https://github.com/NicoHood/HID/wiki/RawHID-API
*/

#include "HID-Project.h"

const int pinLed = LED_BUILTIN;
const int pinButton = 2;

void setup() {
  pinMode(pinLed, OUTPUT);
  pinMode(pinButton, INPUT_PULLUP);
  // No begin function needed for RawHID
}

void loop() {
  if (!digitalRead(pinButton)) {
    digitalWrite(pinLed, HIGH);

    // Create buffer and send it
    uint8_t megabuff[100];
    for (int i = 0; i < sizeof(megabuff); i++)
      megabuff[i] = i;
    RawHID.write(megabuff, sizeof(megabuff));

    // Simple debounce
    delay(300);
    digitalWrite(pinLed, LOW);
  }

  uint8_t len = RawHID.available();
  if (len) {
    digitalWrite(pinLed, HIGH);

    // Mirror the incoming data from the host back
    uint8_t buff[len + 1];
    buff[0] = len;
    for (int i = 1; i < sizeof(buff); i++) {
      buff[i] = RawHID.read();
    }
    RawHID.write(buff, len);

    // Simple debounce
    delay(300);
    digitalWrite(pinLed, LOW);
  }
}
