/*
Copyright (c) 2014 NicoHood
 See the readme for credit to other people.
 
 Keyboard example
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
  // not needed for Leonardo/Micro, Serial will not be set
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
  Keyboard.begin();
}


void loop() {
  // press a button to write some text to your pc
  if (!digitalRead(pinButton)) {
    digitalWrite(pinLed, HIGH);

    // Same use as the official library, pretty much self explaining
    Keyboard.println("This message was sent with my Arduino.");
    Serial.println("Serial port is still working and not glitching out");

    // you can press any key, see list below
    static uint8_t count = 0;
    if (++count == 10) {
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.press(KEY_DELETE);
      Keyboard.releaseAll();
      count = 0;
    }

    // simple debounce
    delay(300);
    digitalWrite(pinLed, LOW);
  }
}

/*
Definitions:
 
 KEY_LEFT_CTRL
 KEY_LEFT_SHIFT
 KEY_LEFT_ALT
 KEY_LEFT_GUI
 KEY_RIGHT_CTRL
 KEY_RIGHT_SHIFT
 KEY_RIGHT_ALT
 KEY_RIGHT_GUI
 
 KEY_UP_ARROW
 KEY_DOWN_ARROW
 KEY_LEFT_ARROW
 KEY_RIGHT_ARROW
 KEY_BACKSPACE
 KEY_TAB
 KEY_RETURN
 KEY_ESC
 KEY_INSERT
 KEY_DELETE
 KEY_PAGE_UP
 KEY_PAGE_DOWN
 KEY_HOME
 KEY_END
 KEY_CAPS_LOCK
 KEY_F1
 KEY_F2
 KEY_F3
 KEY_F4
 KEY_F5
 KEY_F6
 KEY_F7
 KEY_F8
 KEY_F9
 KEY_F10
 KEY_F11
 KEY_F12
 
 KEY_PRINT
 KEY_SCROLL_LOCK
 KEY_PAUSE
 */