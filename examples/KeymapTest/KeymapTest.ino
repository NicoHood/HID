/*
  Copyright (c) 2014-2021 NicoHood
  See the readme for credit to other people.

  KeymapTest Example
  Test a keymap to make sure that all keys type the character they are ssupposed to

  See HID Project documentation for more information about the keyboard API:
  https://github.com/NicoHood/HID/wiki/Keyboard-API
*/

#include <HID-Project.h>

void setup() {
  Serial.begin(115200);
  while (!Serial) {
  }

  BootKeyboard.begin();
  BootKeyboard.releaseAll();

  Serial.println ("--- HID Project Keyboard Layout Test ---");
  Serial.println ("You will see two columns of characters. If the chosen keymap is correct, the two characters");
  Serial.println ("will be the same on every line. If they are not, try again with a different keymap.");
  Serial.println ("DO NOT CHANGE WINDOW UNTIL THE SKETCH IS DONE!!!");
  Serial.println ("Please click in the input box above, make sure it is empty and press ENTER");
  while (!Serial.available()) {
  }
  while (Serial.available()) {
    Serial.read ();
  }
  delay (100);
  
  for (char c = ' '; c <= '~'; ++c) {
    Serial.print(c);
    Serial.print(' ');
    BootKeyboard.press(c);
    delay (5);
    BootKeyboard.release(c);
    delay (5);
    BootKeyboard.press(KEY_ENTER);
    delay (5);
    BootKeyboard.release(KEY_ENTER);
    delay (5);
    while (!Serial.available()) {
    }
    char r = Serial.read();
    while (Serial.available()) {
      Serial.read();
    }
    Serial.print (r);
    if (r == c) {
      Serial.print(" OK");
    } else {
      Serial.print(" FAIL");
    }
    Serial.println();
  }

  Serial.println("--- Done ---");
}

void loop() {
  // Nothing to do, yay!
}
