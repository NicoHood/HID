/*
  Copyright (c) 2014-2015 NicoHood
  See the readme for credit to other people.

  AbsoluteMouse example
  Press a button to click, moveTo the mouse.

  See HID Project documentation for more infos
  https://github.com/NicoHood/HID/wiki/Mouse-API
  https://github.com/NicoHood/HID/wiki/AbsoluteMouse-API
*/

#include "HID.h"
#include "HID-Project.h"

//Choose which keyboard to use
#define KEYB NKROKeyboard
//#define KEYB TeensyKeyboard


const int pinLed = LED_BUILTIN;
const int pinButton = 2;

void setup() {
  pinMode(pinLed, OUTPUT);
  pinMode(pinButton, INPUT_PULLUP);

  // Sends a clean report to the host. This is important on any Arduino type.
  KEYB.begin();
}

void loop() {
  if (!digitalRead(pinButton)) {
    digitalWrite(pinLed, HIGH);
    
    KEYB.println(F("NKRO can push 113 keys at the same time, teensy only 6!"));

    KEYB.press('s');
    KEYB.press('d');
    KEYB.press('f');
    KEYB.press('g');
    KEYB.press('h');
    KEYB.press('j');
    KEYB.press('k');
    KEYB.press('l');

    delay(500);
    
    KEYB.releaseAll();
    KEYB.println();

    delay(500); 
  }
}
