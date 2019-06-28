/*
  Copyright (c) 2019-2020 Blahlicus
  See the readme for credit to other people.

  Alternate input method example using german

  Demonstrates how to set the _asciimap bindings to alternate input methods.

  Users also have to change the OS level input method to match the one used
  in the firmware.

*/
#define HID_CUSTOM_LAYOUT // set this flag to indicate that a custom layout is selected
// if the above flag is not defined, then the default US layout is used instead

#define LAYOUT_GERMAN // set this flag after the above flag to indicate the custom input method is German
// for more layouts, see /src/KeyboardLayouts/ImprovedKeylayouts.h

// you must set the above flags before including HID-Project
#include "HID-Project.h"


void setup() {
  BootKeyboard.begin();
  delay(2000);
  BootKeyboard.write(KEY_7|MOD_LEFT_SHIFT); // this outputs the / symbol as per the german input method
}


void loop() {

}
