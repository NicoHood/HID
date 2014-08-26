/*
Copyright (c) 2014 NicoHood
See the readme for credit to other people.

Gamepad example
Press a button and demonstrate Gamepad actions
*/

// include HID library
#include <HID.h>

// create a new Gamepad instance (1-4)
Gamepad Gamepad1(1);
//Gamepad Gamepad2(2);
//Gamepad Gamepad3(3);
//Gamepad Gamepad4(4);

const int pinLed = 13;
const int pinButton = 8;

void setup() {
  pinMode(pinLed, OUTPUT);
  pinMode(pinButton, INPUT_PULLUP);

  // Starts Serial at baud 115200 otherwise HID wont work on Uno/Mega.
  // This is not needed for Leonado/(Pro)Micro but make sure to activate desired USB functions in HID.h
  Serial.begin(SERIAL_HID_BAUD);

  // Sends a clean report to the host. This is important because
  // the 16u2 of the Uno/Mega is not turned off while programming
  // so you want to start with a clean report to avoid strange bugs after reset.
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
    static uint8_t dpad1 = GAMEPAD_DPAD_CENTERED;
    Gamepad1.dPad1(dpad1++);
    if(dpad1>GAMEPAD_DPAD_UP_LEFT) dpad1 = GAMEPAD_DPAD_CENTERED;
    static int8_t dpad2 = GAMEPAD_DPAD_CENTERED;
    Gamepad1.dPad2(dpad2--);
    if(dpad2<GAMEPAD_DPAD_CENTERED) dpad2 = GAMEPAD_DPAD_UP_LEFT;


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
void xAxis(int16_t a);
void yAxis(int16_t a);
void rxAxis(int16_t a);
void ryAxis(int16_t a);
void zAxis(int8_t a);
void rzAxis(int8_t a);
void dPad1(int8_t d);
void dPad2(int8_t d);

Definitions:
GAMEPAD_DPAD_CENTERED 0
GAMEPAD_DPAD_UP 1
GAMEPAD_DPAD_UP_RIGHT 2
GAMEPAD_DPAD_RIGHT 3
GAMEPAD_DPAD_DOWN_RIGHT 4
GAMEPAD_DPAD_DOWN 5
GAMEPAD_DPAD_DOWN_LEFT 6
GAMEPAD_DPAD_LEFT 7
GAMEPAD_DPAD_UP_LEFT 8
*/
