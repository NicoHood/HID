/*
  Copyright (c) 2014-2015 NicoHood
  See the readme for credit to other people.

  AbsoluteMouse example
  Press a button to click, moveTo the mouse.

  You may also use SingleAbsoluteMouse to use a single report.

  See HID Project documentation for more infos
  https://github.com/NicoHood/HID/wiki/Mouse-API
  https://github.com/NicoHood/HID/wiki/AbsoluteMouse-API
*/

#include "HID-Project.h"

const int pinLed = LED_BUILTIN;
const int pinButtonClick = 2;
const int pinButtonCenter = 3;
const int pinButtonMove = 1;

void setup() {
  // Prepare led + buttons
  pinMode(pinLed, OUTPUT);
  pinMode(pinButtonClick, INPUT_PULLUP);
  pinMode(pinButtonCenter, INPUT_PULLUP);
  pinMode(pinButtonMove, INPUT_PULLUP);

  // Sends a clean report to the host. This is important on any Arduino type.
  AbsoluteMouse.begin();
}

void loop() {
  if (!digitalRead(pinButtonClick)) {
    digitalWrite(pinLed, HIGH);

    // Same use as the official library, pretty much self explaining
    AbsoluteMouse.click();
    //AbsoluteMouse.click(MOUSE_RIGHT);

    // Simple debounce
    delay(300);
    digitalWrite(pinLed, LOW);
  }

  if (!digitalRead(pinButtonCenter)) {
    digitalWrite(pinLed, HIGH);

    // Move to coordinate (16bit signed, -32768 - 32767)
    // Moving to the same position twice will not work!
    // X and Y start in the upper left corner.
    AbsoluteMouse.moveTo(0, 0);

    // Simple debounce
    delay(300);
    digitalWrite(pinLed, LOW);
  }

  if (!digitalRead(pinButtonMove)) {
    digitalWrite(pinLed, HIGH);

    // Move relative to last coordinate
    AbsoluteMouse.move(1000, 1000);

    // Simple debounce
    delay(300);
    digitalWrite(pinLed, LOW);
  }
}
