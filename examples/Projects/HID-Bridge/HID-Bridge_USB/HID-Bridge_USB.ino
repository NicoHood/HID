/*
 Copyright (c) 2014-2015 NicoHood
 See the readme for credit to other people.

 Serial HID-Bridge USB
 Select Arduino Uno/Mega HID-Bridge as board.

 After upload make sure the 16u2 sketch runs, not the HoodLoader2 bootloader.
*/

void setup() {
  // start the Serial1 which is connected with the 16u2.
  // make sure both baud rates are the same
  // you can go up to 2000000 for very fast data transmission
  Serial1.begin(115200);

  // Sends a clean report to the host. This is important on any Arduino type.
  Keyboard.begin();

  // start the USB Serial for debugging
  Serial.begin(115200);
}

void loop() {
  // check if any Serial data from the I/O MCU was received
  char c = Serial1.read();

  // if it's a character, print it!
  if (c >= 'a' && c <= 'z') {
    Serial.print(F("USB: "));
    Serial.println(c);
    Keyboard.println(c);
  }
}
