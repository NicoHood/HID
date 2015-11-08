/*
  Copyright (c) 2014-2015 NicoHood
  See the readme for credit to other people.

  Mouse example
  Press a button to click or move the mouse.

  You may also use BootMouse to enable a bios compatible (single report) mouse.
  However this is very unusual and not recommended.
  Bios mice dont support wheels which can cause problems after a reboot.

  See HID Project documentation for more Information.
  https://github.com/NicoHood/HID/wiki/Mouse-API
*/

#include "HID-Project.h"

const int pinLed = LED_BUILTIN;
const int pinButtonClick = 2;
const int pinButtonMove = 3;
const int pinButtonScroll = 4;

void setup() {
  // Prepare led + buttons
  pinMode(pinLed, OUTPUT);
  pinMode(pinButtonClick, INPUT_PULLUP);
  pinMode(pinButtonMove, INPUT_PULLUP);
  pinMode(pinButtonScroll, INPUT_PULLUP);

  // Sends a clean report to the host. This is important on any Arduino type.
  Mouse.begin();
}

void loop() {
  if (!digitalRead(pinButtonClick)) {
    digitalWrite(pinLed, HIGH);

    // Same use as the official library, pretty much self explaining
    Mouse.click();
    //Mouse.click(MOUSE_RIGHT);

    // Simple debounce
    delay(300);
    digitalWrite(pinLed, LOW);
  }

  if (!digitalRead(pinButtonMove)) {
    digitalWrite(pinLed, HIGH);

    // Same use as the official library, pretty much self explaining
    Mouse.move(100, 0);

    // Simple debounce
    delay(300);
    digitalWrite(pinLed, LOW);
  }

  if (!digitalRead(pinButtonScroll)) {
    digitalWrite(pinLed, HIGH);

    // Scroll down a bit, make sure the value is high enough
    Mouse.move(0, 0, 160);

    // simple debounce
    delay(300);
    digitalWrite(pinLed, LOW);
  }
}

