/*
 Copyright (c) 2015 NicoHood
 See the readme for credit to other people.

 HoodLoader2 Run Bootloader example

 Starts Bootloader mode.
 This is useful if you only want to use
 the USB-Serial bridge again.
 
 You could delete the program with avrdude,
 but this sketch is way simpler to upload.
 
 It forces a watchdog reset,
 meaning the bootloader is started completely indipendant.
*/

#include <avr/wdt.h>

void setup() {
  // close interrupts
  cli();

  // write magic key to ram
  *(uint8_t *)0x0280 = 0x77;

  // watchdog reset
  wdt_enable(WDTO_120MS);
}

void loop() {
  // wait for reset
}
