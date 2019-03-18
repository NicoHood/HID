
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

  Edited by OmegaRogue
*/

#include "HID-Project.h"

// input pins for encoder channel A and channel B
int pinA = 2;
int pinB = 3;

// input pin for pushbutton
int pinButton = 4;

unsigned long keyPrevMillis = 0;
const unsigned long keySampleIntervalMs = 25;
byte longKeyPressCountMax = 840;    // 80 * 25 = 2000 ms
byte longKeyPressCount = 0;

byte prevKeyState = HIGH;         // button is active low

volatile int previous = 0;
volatile int counter = 0;

void setup() {
  pinMode(pinA, INPUT_PULLUP);
  pinMode(pinB, INPUT_PULLUP);

  pinMode(pinButton, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(pinA), changed, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pinB), changed, CHANGE);

  SurfaceDial.begin();
  SurfaceDial.onScreen(true);
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
  if (millis() - keyPrevMillis >= keySampleIntervalMs) {
    keyPrevMillis = millis();

    byte currKeyState = digitalRead(pinButton);

    if ((prevKeyState == HIGH) && (currKeyState == LOW)) {
      keyPress();
    }
    else if ((prevKeyState == LOW) && (currKeyState == HIGH)) {
      keyRelease();
    }
    else if (currKeyState == LOW) {
      longKeyPressCount++;
    }

    prevKeyState = currKeyState;
  }

  if(counter >= 1) {
    SurfaceDial.reportData(10,0,0);
    counter -= 1;
  } else if(counter <= -1) {
    SurfaceDial.reportData(-10,0,0);
    counter += 1;
  }
}

// called when button is kept pressed for less than 2 seconds
void shortKeyPress() {
  SurfaceDial.click();
}


// called when button is kept pressed for more than 2 seconds
void longKeyPress() {

  SurfaceDial.release();
}



// called when key goes from not pressed to pressed
void keyPress() {
  SurfaceDial.press();
  longKeyPressCount = 0;
}

// called when key goes from pressed to not pressed
void keyRelease() {


  if (longKeyPressCount >= longKeyPressCountMax) {
    longKeyPress();
  }
  else {
    shortKeyPress();
  }
}