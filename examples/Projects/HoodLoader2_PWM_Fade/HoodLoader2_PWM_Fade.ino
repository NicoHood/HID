/*
 Copyright (c) 2014 NicoHood
 See the readme for credit to other people.

 PWM Fade
 
 This example shows how to fade an LED on pin 7
 using the analogWrite() function.
 
 Basically it is a demonstartion that PWM on pin 7 works fine.
 You can also deactivate the USB Core for this example, but then you'd
 need the workaround. See the other example for this.
*/

int led = 7;           // the pin that the LED is attached to
int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by

// the setup routine runs once when you press reset:
void setup()  {
  // declare pin 9 to be an output:
  pinMode(led, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop()  {
  // set the brightness of pin 9:
  analogWrite(led, brightness);    

  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade:
  if (brightness == 0 || brightness == 255) {
    fadeAmount = -fadeAmount ;
  }    
  // wait for 30 milliseconds to see the dimming effect    
  delay(30);                            
}
