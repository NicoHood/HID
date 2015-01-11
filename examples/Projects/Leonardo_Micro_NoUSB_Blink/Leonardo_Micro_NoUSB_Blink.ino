/*
 Copyright (c) 2014 NicoHood
 See the readme for credit to other people.

 Leonardo_Micro_NoUSB_Blink
 
 Blinks Led and shows what workaround is needed to fix the timing.
 This is not needed for HoodLoader2 devices any more.
*/


// workaround for undefined USBCON has to be placed in every sketch
// otherwise the timings wont work correctly
ISR(USB_GEN_vect)
{
  UDINT = 0;
}

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);              // wait for a second
}
