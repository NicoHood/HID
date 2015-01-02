/*
 Copyright (c) 2014 NicoHood
 See the readme for credit to other people.

 Gamepad example project

 Press physical buttons to press USB Gamepad buttons.
 This can be used for a simple SNES Controller.

 Make sure the Gamepad report is set in:
 sketchbook/hardware/HID/avr/variants/hid_descriptors/hid_descriptors.h
*/

// pin mappings
const int pinButton1 = 2;
const int pinButton2 = 3;
const int pinButton3 = 4;
const int pinButton4 = 5;
const int pinButton5 = 6;
const int pinButton6 = 7;
const int pinButton7 = 8;
const int pinButton8 = 9;
const int pinButton9 = 10;
const int pinButton10 = 18;
const int pinButton11 = 19;
const int pinButton12 = 20;

void setup() {
  // pinsetup
  pinMode(pinButton1, INPUT_PULLUP);
  pinMode(pinButton2, INPUT_PULLUP);
  pinMode(pinButton3, INPUT_PULLUP);
  pinMode(pinButton4, INPUT_PULLUP);
  pinMode(pinButton5, INPUT_PULLUP);
  pinMode(pinButton6, INPUT_PULLUP);
  pinMode(pinButton7, INPUT_PULLUP);
  pinMode(pinButton8, INPUT_PULLUP);
  pinMode(pinButton9, INPUT_PULLUP);
  pinMode(pinButton10, INPUT_PULLUP);
  pinMode(pinButton11, INPUT_PULLUP);
  pinMode(pinButton12, INPUT_PULLUP);

  // Sends a clean report to the host. This is important on any Arduino type.
  // Make sure all desired USB functions are activated in USBAPI.h!
  Gamepad.begin();
}

void loop() {
  // check each button and press Gamepad if needed
  if (!digitalRead(pinButton1))
    Gamepad.press(1);
  else
    Gamepad.release(1);

  if (!digitalRead(pinButton2))
    Gamepad.press(2);
  else
    Gamepad.release(2);

  if (!digitalRead(pinButton3))
    Gamepad.press(3);
  else
    Gamepad.release(3);

  if (!digitalRead(pinButton4))
    Gamepad.press(4);
  else
    Gamepad.release(4);

  if (!digitalRead(pinButton5))
    Gamepad.press(5);
  else
    Gamepad.release(5);

  if (!digitalRead(pinButton6))
    Gamepad.press(6);
  else
    Gamepad.release(6);

  if (!digitalRead(pinButton7))
    Gamepad.press(7);
  else
    Gamepad.release(7);

  if (!digitalRead(pinButton8))
    Gamepad.press(8);
  else
    Gamepad.release(8);

  if (!digitalRead(pinButton9))
    Gamepad.press(9);
  else
    Gamepad.release(9);

  if (!digitalRead(pinButton10))
    Gamepad.press(10);
  else
    Gamepad.release(10);

  if (!digitalRead(pinButton11))
    Gamepad.press(11);
  else
    Gamepad.release(11);

  if (!digitalRead(pinButton12))
    Gamepad.press(12);
  else
    Gamepad.release(12);

  // write the information to the host now!
  Gamepad.write();
}

