/*
 Copyright (c) 2014 NicoHood
 See the readme for credit to other people.

 Keyboard Led example

 Press a button to toogle caps lock.
 Caps lock state is represented by the onboard led.
 See official and HID Project documentation for more infos
 https://github.com/NicoHood/HID/wiki/Keyboard-API
*/

const int pinLed = LED_BUILTIN;
const int pinButton = 2;

void setup() {
  pinMode(pinLed, OUTPUT);
  pinMode(pinButton, INPUT_PULLUP);

  // Sends a clean report to the host. This is important on any Arduino type.
  Keyboard.begin();
}


void loop() {
  // update Led equal to the caps lock state
  // keep in mind on HoodLoader2 high&low are inverted (like this)
  if (Keyboard.getLeds()&LED_CAPS_LOCK)
    digitalWrite(pinLed, LOW);
  else
    digitalWrite(pinLed, HIGH);

  if (!digitalRead(pinButton)) {
    // trigger caps lock
    Keyboard.write(KEY_CAPS_LOCK);

    // simple debounce
    delay(500);
  }
}