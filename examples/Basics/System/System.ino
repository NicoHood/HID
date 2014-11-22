/*
Copyright (c) 2014 NicoHood
See the readme for credit to other people.

System example

Press a button to put pc into standby mode
*/

const int pinLed = LED_BUILTIN;
const int pinButton = 2;

void setup() {
  pinMode(pinLed, OUTPUT);
  pinMode(pinButton, INPUT_PULLUP);

  // Sends a clean report to the host. This is important on any Arduino type.
  // Make sure all desired USB functions are activated in USBAPI.h!
  System.begin();
}

void loop() {
  if (!digitalRead(pinButton)) {
    digitalWrite(pinLed, HIGH);

    // See list below for more definitions or the official usb documentation
    System.write(SYSTEM_SLEEP);

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
