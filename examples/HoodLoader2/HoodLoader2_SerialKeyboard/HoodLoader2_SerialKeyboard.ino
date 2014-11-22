/*
 Copyright (c) 2014 NicoHood
 See the readme for credit to other people.

 HoodLoader2 SerialKeyboard example
 
 This sketch should demonstrate how to program a basic sketch with HoodLoader2.
 It was used to demonstrate that Serial and HID is working properly.
 The the other examples on how to use the other APIs, it works the same.
 
 Use the F() macro to save strings in PROGMEM to keep ram usage low.
 The 16u2 has very low RAM, so don't try to use that much ram.
 
 Open the Serial port, type in anything and see that Serial and Keyboard is working.
 See official documentation for more infos.
 */

void setup() {
  // start + wait for serial debug in/output
  while (!Serial);
  Serial.begin(115200);
  Serial.println(F("Startup"));

  // Sends a clean report to the host. This is important because
  // the 16u2 of the Uno/Mega is not turned off while programming
  // so you want to start with a clean report to avoid strange bugs after reset.
  Keyboard.begin();
}


void loop() {
  if (Serial.available()) {
    // discard all Serial bytes to avoid multiple sendings
    unsigned long currentMillis = millis();
    while (millis() - currentMillis < 100) {
      if (Serial.available())
        Serial.write(Serial.read());
    }

    // print an information back to the serial port
    Serial.println();
    Serial.println(F("Serial port working. Printing Text in 3 seconds."));

    // wait 3 seconds and discard all new in bytes to not crash the Arduino
    currentMillis = millis();
    while (millis() - currentMillis < 3000) {
      if (Serial.available())
        Serial.write(Serial.read());
    }

    // same use as the official library, pretty much self explaining
    Keyboard.print(F("This message was sent with my Arduino."));
  }
}