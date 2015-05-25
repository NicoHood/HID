/*
 Copyright (c) 2014-2015 NicoHood
 See the readme for credit to other people.

 Keyboard example

 Press a button to write some text to your pc.
 See official and HID Project documentation for more infos
 https://github.com/NicoHood/HID/wiki/Keyboard-API
*/

const int pinLed = LED_BUILTIN;
const int pinButton = 2;

void setup() {
  pinMode(pinLed, OUTPUT);
  pinMode(pinButton, INPUT_PULLUP);

  // Starts Serial debug output
  Serial.begin(115200);

  // Sends a clean report to the host. This is important on any Arduino type.
  Keyboard.begin();
}


void loop() {
  if (!digitalRead(pinButton)) {
    digitalWrite(pinLed, HIGH);

    // Same use as the official library, pretty much self explaining
    Keyboard.println(F("This message was sent with my Arduino."));
    Serial.println(F("Serial port is still working and not glitching out"));

    // simple debounce
    delay(300);
    digitalWrite(pinLed, LOW);
  }
}
