/*
Copyright (c) 2014 NicoHood
See the readme for credit to other people.

System example
*/

// The protocol ist still needed for Uno/Mega here
#include <NicoHoodProtocol.h>
#include <HID.h>

const int pinLed = 13;
const int pinButton = 8;

void setup() {
  pinMode(pinLed, OUTPUT);
  pinMode(pinButton, INPUT_PULLUP);

  // Starts Serial at baud 115200. end just ends the Serial
  // Make sure to end your special HIDs before, this does not clear them!
  // You need this baud for the HID library but still can use other bauds
  // without HID functions.
  HID.begin();

  // Sends a clean report to the host. This is important because
  // the 16u2 of the Uno/Mega is not turned off while programming
  // so you want to start with a clear report to avoid strange bugs.
  // its exactly the same like the end() function.
  // You can also unplug the device if anything goes wrong.
  // To prevent the 16u2 to send more reports just pull the Serial TX (pin1) low
  // or see readme for turning off HID functions.
  // If you did anything wrong (keyboard is doing weird stuff)
  // just logout (no shutdown needed).
  System.begin();
}

void loop() {
  // press a button to put pc into standby mode/wake up
  if (!digitalRead(pinButton)) {
    digitalWrite(pinLed, HIGH);

    // See list below for more definitions or the official usb documentation
    static bool on = true;
    if (on)
      System.write(SYSTEM_SLEEP);
    else
      // System Wakeup is currently not working for Arduino Uno/Mega.
      System.write(SYSTEM_WAKE_UP);

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
