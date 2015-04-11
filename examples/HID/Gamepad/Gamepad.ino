/*
 Copyright (c) 2014 NicoHood
 See the readme for credit to other people.

 Gamepad example

 Press a button and demonstrate Gamepad actions
 See HID Project documentation for more infos
 https://github.com/NicoHood/HID/wiki/Gamepad-API
 */

const int pinLed = LED_BUILTIN;
const int pinButton = 2;

void setup() {
  pinMode(pinLed, OUTPUT);
  pinMode(pinButton, INPUT_PULLUP);

  // Sends a clean report to the host. This is important on any Arduino type.
  Gamepad.begin();
}

void loop() {
  if (!digitalRead(pinButton)) {
    digitalWrite(pinLed, HIGH);

    // press button 1-32 and reset (34 because its written later)
    static uint8_t count = 1;
    Gamepad.press(count++);
    if (count == 34) {
      Gamepad.releaseAll();
      count = 1;
    }

    // move x/y Axis to a new position (16bit)
    Gamepad.xAxis(random(0xFFFF));
    Gamepad.yAxis(random(0xFFFF));

    // go through all dPad positions
    // values: 0-8 (0==centred)
    static uint8_t dpad1 = GAMEPAD_DPAD_CENTERED;
    Gamepad.dPad1(dpad1++);
    if (dpad1 > GAMEPAD_DPAD_UP_LEFT) dpad1 = GAMEPAD_DPAD_CENTERED;
    static int8_t dpad2 = GAMEPAD_DPAD_CENTERED;
    Gamepad.dPad2(dpad2--);
    if (dpad2 < GAMEPAD_DPAD_CENTERED) dpad2 = GAMEPAD_DPAD_UP_LEFT;


    // functions above only set the values
    // this writes the report to the host
    Gamepad.write();

    // simple debounce
    delay(300);
    digitalWrite(pinLed, LOW);
  }
}
