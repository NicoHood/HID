/*
  Copyright (c) 2017 wind-rider
  See the readme for credit to other people.

  Surface dial example
  
  Use an encoder and a button to create a Surface Dial-compatible device.
  See the connection diagram how to wire it up.

  Please note that:
   - I tested it using an Arduino Pro Micro; TinkerCad didn't have that in its component library
   - you obviously don't need a motor, but TinkerCad didn't have a separate encoder

  The encoder processing code is coming from https://www.allwinedesigns.com/blog/pocketnc-jog-wheel
*/

#include "HID-Project.h"

// input pins for encoder channel A and channel B
int pinA = 2;
int pinB = 3;

// input pin for pushbutton
int pinButton = 4;

volatile bool previousButtonValue = false;

volatile int previous = 0;
volatile int counter = 0;

void setup() {
  pinMode(pinA, INPUT_PULLUP); 
  pinMode(pinB, INPUT_PULLUP);

  pinMode(pinButton, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(pinA), changed, CHANGE); 
  attachInterrupt(digitalPinToInterrupt(pinB), changed, CHANGE);
  
  SurfaceDial.begin();
}

void changed() {
  int A = digitalRead(pinA); 
  int B = digitalRead(pinB);

  int current = (A << 1) | B;
  int combined  = (previous << 2) | current;
   
  if(combined == 0b0010 || 
     combined == 0b1011 ||
     combined == 0b1101 || 
     combined == 0b0100) {
    counter++;
  }
   
  if(combined == 0b0001 ||
     combined == 0b0111 ||
     combined == 0b1110 ||
     combined == 0b1000) {
    counter--;
  }

  previous = current;
}

void loop(){ 
  bool buttonValue = digitalRead(pinButton);
  if(buttonValue != previousButtonValue){
    if(buttonValue) {
      SurfaceDial.press();
    } else {
      SurfaceDial.release();
    }    
    previousButtonValue = buttonValue;
  }

  if(counter >= 4) {
    SurfaceDial.rotate(10);
    counter -= 4;
  } else if(counter <= -4) {
    SurfaceDial.rotate(-10);
    counter += 4;
  } 
}
