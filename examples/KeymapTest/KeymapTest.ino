/*
  Copyright (c) 2014-2021 NicoHood
  See the readme for credit to other people.

  KeymapTest Example
  Test a keylayout to make sure that all keys type the character they are
  supposed to.

  See HID Project documentation for more information about the keyboard API:
  https://github.com/NicoHood/HID/wiki/Keyboard-API
*/

/* By default the US English layout is selected. To test a different keylayout,
 * uncomment the following two lines and change the second to reflect your
 * chosen layout. You can see the available layouts at the bottom of
 * ImprovedKeylayouts.h in the library sources.
 */
//#define HID_CUSTOM_LAYOUT
//#define LAYOUT_ITALIAN

#include <HID-Project.h>

/* Time to wait after each key press/release so that it gets picked up by the
 * host system [ms].
 */
#define KEYDELAY 5

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
    delay (KEYDELAY);
    BootKeyboard.release(c);
    delay (KEYDELAY);
    BootKeyboard.press(KEY_ENTER);
    delay (KEYDELAY);
    BootKeyboard.release(KEY_ENTER);
    delay (KEYDELAY);
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
