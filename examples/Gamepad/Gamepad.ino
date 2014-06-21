/*
Copyright (c) 2014 NicoHood
See the readme for credit to other people.

Gamepad example
Press a button and demonstrate Gamepad actions
*/

// not needed for Leonardo/Micro
#include <HID.h>

// for Leonardo/Micro: make sure to activate desired USB functions in HID_Reports.h

const int pinLed = 13;
const int pinButton = 8;

void setup() {
  pinMode(pinLed, OUTPUT);
  pinMode(pinButton, INPUT_PULLUP);

  // Starts Serial at baud 115200. end just ends the Serial
  // Make sure to end your special HIDs before, this does not clear them!
  // You need this baud for the HID library but still can use other bauds
  // without HID functions.
  // not needed for Leonado/Micro, Serial will not be set
  HID.begin();

  // Sends a clean report to the host. This is important because
  // the 16u2 of the Uno/Mega is not turned off while programming
  // so you want to start with a clear report to avoid strange bugs.
  // its exactly the same like the end() function.
  // You can also unplug the device if anything goes wrong.
  // To prevent the 16u2 to send more reports just pull the Serial TX (pin1) low
  // or see readme for turning off HID functions.
  // If you did anything wrong (keyboard is doing weird stuff)
  // just logout (no shutdown needed).
  Gamepad1.begin();
}

void loop() {
  if (!digitalRead(pinButton)) {
    digitalWrite(pinLed, HIGH);

    // press button 1-32 and reset (34 becaue its written later)
    static uint8_t count = 1;
    Gamepad1.press(count++);
    if (count == 34) {
      Gamepad1.releaseAll();
      count = 1;
    }

    // move x/y Axis to a new position (16bit)
    Gamepad1.xAxis(random(0xFFFF));
    Gamepad1.yAxis(analogRead(A0) << 6);

    // go through all dPad positions
    // values: 0-8 (0==centred)
    static uint8_t dpad1 = 0;
    Gamepad1.dPad1(dpad1++);
    if (dpad1 == 9) dpad1 = 0;
    static int8_t dpad2 = 0;
    Gamepad1.dPad2(dpad2--);
    if (dpad2 == -1) dpad2 = 8;

    // functions before only set the values
    // this writes the report to the host
    Gamepad1.write();

    // simple debounce
    delay(300);
    digitalWrite(pinLed, LOW);
  }
}

/*
Prototypes:

void begin(void);
void end(void);
void write(void);
void press(uint8_t b);
void release(uint8_t b);
void releaseAll(void);
void buttons(uint32_t b);
void xAxis(uint16_t a);
void yAxis(uint16_t a);
void zAxis(uint16_t a);
void rxAxis(uint16_t a);
void ryAxis(uint16_t a);
void rzAxis(uint16_t a);
void dPad1(uint8_t d);
void dPad2(uint8_t d);
*/
