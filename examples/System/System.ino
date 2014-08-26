/*
Copyright (c) 2014 NicoHood
See the readme for credit to other people.

System example
Press a button to put pc into standby mode
*/

// include HID library
#include <HID.h>

const int pinLed = 13;
const int pinButton = 8;

void setup() {
  pinMode(pinLed, OUTPUT);
  pinMode(pinButton, INPUT_PULLUP);

  // Starts Serial at baud 115200 otherwise HID wont work on Uno/Mega.
  // This is not needed for Leonado/(Pro)Micro but make sure to activate desired USB functions in HID.h
  Serial.begin(SERIAL_HID_BAUD);

  // Sends a clean report to the host. This is important because
  // the 16u2 of the Uno/Mega is not turned off while programming
  // so you want to start with a clean report to avoid strange bugs after reset.
  System.begin();
}

void loop() {
  if (!digitalRead(pinButton)) {
    digitalWrite(pinLed, HIGH);

    // See list below for more definitions or the official usb documentation
    System.write(SYSTEM_SLEEP);

    // simple debounce
    delay(300);
    digitalWrite(pinLed, LOW);
  }
}

/*
Definitions:

SYSTEM_POWER_DOWN
SYSTEM_SLEEP
SYSTEM_WAKE_UP
*/
