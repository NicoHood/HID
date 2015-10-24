/*
  Copyright (c) 2014-2015 NicoHood
  See the readme for credit to other people.

  Improved Keyboard example

  Shows how to use the new Keyboard API.

  See HID Project documentation for more information.
  https://github.com/NicoHood/HID/wiki/Keyboard-API#improved-keyboard
*/

#include "HID-Project.h"

const int pinLed = LED_BUILTIN;
const int pinButton = 2;

void setup() {
  pinMode(pinLed, OUTPUT);
  pinMode(pinButton, INPUT_PULLUP);

  // Sends a clean report to the host. This is important on any Arduino type.
  Keyboard.begin();
}


void loop() {
  // Trigger caps lock manually via button
  if (!digitalRead(pinButton)) {
    digitalWrite(pinLed, HIGH);

    // Use the default print functions
    Keyboard.println("Hello World!");

    // Press a single character, special non ascii characters wont work.
    //Keyboard.write('a');

    // Write single keys, do not use a number here!
    //Keyboard.write(KEY_ENTER);


    // If you really wish to press a RAW keycode without the name use this:
    //Keyboard.write(KeyboardKeycode(40));

    // Use (a limited number of) consumer keys.
    // Only works with the lower 255 keys and on linux only.
    //Keyboard.write(MEDIA_PLAY_PAUSE);

    // Linux also supports several system function via consumer report.
    //Keyboard.write(CONSUMER_POWER);
    //Keyboard.write(CONSUMER_SLEEP);

    // You can also use some special keyboard keys on linux.
    //Keyboard.write(KEY_POWER);
    //Keyboard.write(KEY_F13);

    // You can wakeup you PC from sleep.
    // This might be not supported on all hardware, but on all OS types.
    //Keyboard.wakeupHost();

    // Simple debounce
    delay(300);
    digitalWrite(pinLed, LOW);
  }
}
