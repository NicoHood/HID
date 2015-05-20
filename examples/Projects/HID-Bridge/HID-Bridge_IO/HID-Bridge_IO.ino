/*
 Copyright (c) 2014-2015 NicoHood
 See the readme for credit to other people.

 Serial HID-Bridge I/O
 Select Arduino Uno/Mega HID-Bridge as board.

 After upload make sure the 16u2 sketch runs, not the HoodLoader2 bootloader.
*/

void setup() {
  // start the Serial which is connected with the 16u2.
  // make sure both baud rates are the same
  // you can go up to 2000000 for very fast data transmission
  Serial.begin(115200);
}

void loop() {
  // send random letters to the USB MCU
  Serial.write(random('a', 'z'));
  delay(1000);
}
