/*
 Copyright (c) 2014 NicoHood
 See the readme for credit to other people.

 HoodLoader2 NoUSB Blink example
 
 This sketch demonstrates how to use HoodLoader2 without USB Core.
 This might be useful to keep ram/flash usage at a very low level.
 Select Tools->USB Core->No USB functions to get rid of the USB Core.
 
 Blinks Leds and shows what workaround is needed to get the timing correct.
 You can still use the normal digitalWrite(LED_BUILTIN_TX, LOW); for updating Leds.
 Keep in mind that the logic is inverted then! LOW=HIGH and vice versa.
 */

// workaround for undefined USBCON has to be placed in every sketch
// otherwise the timings wont work correctly
ISR(USB_GEN_vect)
{
  UDINT = 0;
}

void setup() {
  TX_RX_LED_INIT;
}

void loop() {
  TXLED0;
  delay(100);
  TXLED1;
  delay(100);
  RXLED0;
  delay(100);
  RXLED1;
  delay(100);
}
