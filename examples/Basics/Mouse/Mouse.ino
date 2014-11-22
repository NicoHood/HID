/*
 Copyright (c) 2014 NicoHood
 See the readme for credit to other people.

 Mouse example
 
 Press a button to click with mouse. See official documentation for more infos
 */

const int pinLed = LED_BUILTIN;
const int pinButton = 2;

void setup() {
  pinMode(pinLed, OUTPUT);
  pinMode(pinButton, INPUT_PULLUP);

  // Starts Serial debug output
  Serial.begin(115200);

  // Sends a clean report to the host. This is important on any Arduino type.
  // Make sure all desired USB functions are activated in USBAPI.h!
  Mouse.begin();
}

void loop() {
  if (!digitalRead(pinButton)) {
    digitalWrite(pinLed, HIGH);

    // Same use as the official library, pretty much self explaining
    Mouse.click();
    Serial.println("Serial port is still working and not glitching out");

    // simple debounce
    delay(300);
    digitalWrite(pinLed, LOW);
  }
}

/*
Definitions:

 MOUSE_LEFT
 MOUSE_RIGHT
 MOUSE_MIDDLE
 MOUSE_PREV
 MOUSE_NEXT
 */
