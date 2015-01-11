/*
 Copyright (c) 2014 NicoHood
 See the readme for credit to other people.

 Hello World Keyboard Beginner example

 Press a button to write some text to your pc.
 See official and HID Project documentation for more information.
*/

const int pinLed = LED_BUILTIN;
const int pinButton = 2;

void setup() {
  // hardware setup
  pinMode(pinLed, OUTPUT);
  pinMode(pinButton, INPUT_PULLUP);

  // Sends a clean report to the host. This is important on any Arduino type.
  Keyboard.begin();
}

void loop() {
  if (digitalRead(pinButton) == LOW) {
    digitalWrite(pinLed, HIGH);

    // Same use as the official library, pretty much self explaining
    Keyboard.println("Hello World");

    // simple debounce
    delay(500);
    digitalWrite(pinLed, LOW);
  }
}
