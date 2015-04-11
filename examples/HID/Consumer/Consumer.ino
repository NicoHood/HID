/*
 Copyright (c) 2014 NicoHood
 See the readme for credit to other people.

 Consumer example (former Media example)

 Press a button to play/pause music player
 See HID Project documentation for more Consumer keys.
 https://github.com/NicoHood/HID/wiki/Consumer-API
*/

const int pinLed = LED_BUILTIN;
const int pinButton = 2;

void setup() {
  pinMode(pinLed, OUTPUT);
  pinMode(pinButton, INPUT_PULLUP);

  // Sends a clean report to the host. This is important on any Arduino type.
  Consumer.begin();
}

void loop() {
  if (!digitalRead(pinButton)) {
    digitalWrite(pinLed, HIGH);

    // See list above for more definitions or the official usb documentation
    Consumer.write(MEDIA_PLAY_PAUSE);

    // simple debounce
    delay(300);
    digitalWrite(pinLed, LOW);
  }
}
