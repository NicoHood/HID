/*
 Copyright (c) 2014 NicoHood
 See the readme for credit to other people.

 System example

 Press a button to put pc into sleep/shut it down or wake it up again.
 See HID Project documentation for more infos
 https://github.com/NicoHood/HID/wiki/System-API
*/

const int pinLed = LED_BUILTIN;
const int pinButtonS = 2;
const int pinButtonW = 3;

void setup() {
  // prepare led + buttons
  pinMode(pinLed, OUTPUT);
  pinMode(pinButtonS, INPUT_PULLUP);
  pinMode(pinButtonW, INPUT_PULLUP);

  // Sends a clean report to the host. This is important on any Arduino type.
  System.begin();
}

void loop() {
  if (!digitalRead(pinButtonS)) {
    digitalWrite(pinLed, HIGH);

    // puts pc into sleep mode/shuts it down
    System.write(SYSTEM_SLEEP);
    //System.write(SYSTEM_POWER_DOWN);

    // simple debounce
    delay(300);
    digitalWrite(pinLed, LOW);
  }
  
  if (!digitalRead(pinButtonW)) {
    digitalWrite(pinLed, HIGH);

    // tries to wake up the PC
    // this might fail on some PCs where USB wakeup isnt supported
    System.write(SYSTEM_WAKE_UP);

    // simple debounce
    delay(300);
    digitalWrite(pinLed, LOW);
  }
}
