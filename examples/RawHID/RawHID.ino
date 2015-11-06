/*
  Copyright (c) 2014-2015 NicoHood
  See the readme for credit to other people.

  Advanced RawHID example

  Shows how to send bytes via RawHID.
  Press a button to send some example values.

  Every received data is mirrored to the host.
  The use of the RawHIDEvent() function is shown too.

  This sketch only tries to show the possiblities
  and is not perfect.You might want to use RawHID differently.

  See HID Project documentation for more information.
  https://github.com/NicoHood/HID/wiki/RawHID-API
*/

#include "HID-Project.h"

const int pinLed = LED_BUILTIN;
const int pinButton = 2;

uint8_t data[255];
volatile size_t len = 0;

void setup() {
  pinMode(pinLed, OUTPUT);
  pinMode(pinButton, INPUT_PULLUP);

  // No begin/end function required for RawHID
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


  // This will miss longer RawHID data transmissions
  // and return an error to the host if data was missed.
  // Only use this for non changing/less important data.
  // Or you can use this if the event aborted on a full buffer.
  // Please note, that all data after this full buffer is missed anyways.
  auto bytesAvailable = RawHID.available();
  while (bytesAvailable--) {
    if (len < sizeof(data)) {
      data[len++] = RawHID.read();
    }
  }

  // Process data from the host
  if (len) {
    digitalWrite(pinLed, HIGH);

    // Disable interrupts while processing the data
    uint8_t oldSREG = SREG;
    cli();

    // Mirror the incoming data from the host back
    RawHID.write(data, len);
    len = 0;

    SREG = oldSREG;

    // Simple debounce for led
    delay(300);
    digitalWrite(pinLed, LOW);
  }
}

void RawHIDEvent(void) {
  // This event is called via interrupt.
  // Do not use print inside, or other long function calls!
  // If you not use this event function,
  // you might miss some data in the loop,
  // if the host sends too fast or too much data at once.

  auto bytesAvailable = RawHID.available();
  while (bytesAvailable--) {
    // Only add data to the buffer if its not full.
    // If it is, no more event will occur
    // and the data should be discarded
    // or read (as shown) in the loop above.
    if (len < sizeof(data)) {
      data[len++] = RawHID.read();
    }
  }
}

