/*
 Copyright (c) 2014 NicoHood
 See the readme for credit to other people.

 Mouse example
 
 Press a button to click, move, moveTo the mouse.
 See official documentation for more infos
 
 Make sure the Absolute Mouse report is set in:
 sketchbook/hardware/HID/avr/variants/hid_descriptors/hid_descriptors.h
 
 Mouse Key definitions:
 MOUSE_LEFT
 MOUSE_RIGHT
 MOUSE_MIDDLE
 MOUSE_PREV
 MOUSE_NEXT
*/

const int pinLed = LED_BUILTIN;
const int pinButtonC = 2;
const int pinButtonR = 3;
const int pinButtonT = 4;

void setup() {
  // prepare led + buttons
  pinMode(pinLed, OUTPUT);
  pinMode(pinButtonC, INPUT_PULLUP);
  pinMode(pinButtonR, INPUT_PULLUP);
  pinMode(pinButtonT, INPUT_PULLUP);

  // Sends a clean report to the host. This is important on any Arduino type.
  Mouse.begin();
}

void loop() {
  if (!digitalRead(pinButtonC)) {
    digitalWrite(pinLed, HIGH);

    // Same use as the official library, pretty much self explaining
    Mouse.click();
    //Mouse.click(MOUSE_RIGHT);

    // simple debounce
    delay(300);
    digitalWrite(pinLed, LOW);
  }
  
  if (!digitalRead(pinButtonR)) {
    digitalWrite(pinLed, HIGH);

    // Same use as the official library, pretty much self explaining
    Mouse.move(100, 0);

    // simple debounce
    delay(300);
    digitalWrite(pinLed, LOW);
  }
  
  if (!digitalRead(pinButtonT)) {
    digitalWrite(pinLed, HIGH);

    // Moves Mouse to an absolute position(0- 32767).
    // Make sure the Absolute Mouse report is set in hid_descriptors.h
    Mouse.moveTo(16384, 16384);

    // simple debounce
    delay(300);
    digitalWrite(pinLed, LOW);
  }
}
