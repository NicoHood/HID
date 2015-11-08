/*
  Copyright (c) 2014-2015 NicoHood
  See the readme for credit to other people.

  Advanced RawHID example

  Shows how to send bytes via RawHID.
  Press a button to send some example values.

  Every received data is mirrored to the host via Serial.

  See HID Project documentation for more information.
  https://github.com/NicoHood/HID/wiki/RawHID-API
*/

#include "HID-Project.h"

const int pinLed = LED_BUILTIN;
const int pinButton = 2;

// Buffer to hold RawHID data.
// If host tries to send more data than this,
// it will respond with an error.
// If the data is not read until the host sends the next data
// it will also respond with an error and the data will be lost.
uint8_t rawhidData[255];

void setup() {
  pinMode(pinLed, OUTPUT);
  pinMode(pinButton, INPUT_PULLUP);

  Serial.begin(115200);

  // Set the RawHID OUT report array.
  // Feature reports are also (parallel) possible, see the other example for this.
  RawHID.begin(rawhidData, sizeof(rawhidData));
}

void loop() {
  // Send data to the host
  if (!digitalRead(pinButton)) {
    digitalWrite(pinLed, HIGH);

    // Create buffer with numbers and send it
    uint8_t megabuff[100];
    for (uint8_t i = 0; i < sizeof(megabuff); i++) {
      megabuff[i] = i;
    }
    RawHID.write(megabuff, sizeof(megabuff));

    // Simple debounce
    delay(300);
    digitalWrite(pinLed, LOW);
  }


  // Check if there is new data from the RawHID device
  auto bytesAvailable = RawHID.available();
  if (bytesAvailable)
  {
    digitalWrite(pinLed, HIGH);

    // Mirror data via Serial
    while (bytesAvailable--) {
      Serial.println(RawHID.read());
    }

    digitalWrite(pinLed, LOW);
  }
}

