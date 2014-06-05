/*
Copyright (c) 2014 NicoHood
See the readme for credit to other people.

Media example
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
  Media.begin();
}

void loop() {
  // press a button to play/pause music player
  if (!digitalRead(pinButton)) {
    digitalWrite(pinLed, HIGH);

    // See list below for more definitions or the official usb documentation
    Media.write(MEDIA_PLAY_PAUSE);

    // simple debounce
    delay(300);
    digitalWrite(pinLed, LOW);
  }
}

/*
Definitions:

MEDIA_FAST_FORWARD
MEDIA_REWIND
MEDIA_NEXT
MEDIA_PREVIOUS
MEDIA_STOP
MEDIA_PLAY_PAUSE

MEDIA_VOLUME_MUTE
MEDIA_VOLUME_UP
MEDIA_VOLUME_DOWN

MEDIA_EMAIL_READER
MEDIA_CALCULATOR
MEDIA_EXPLORER

MEDIA_BROWSER_HOME
MEDIA_BROWSER_BACK
MEDIA_BROWSER_FORWARD
MEDIA_BROWSER_REFRESH
MEDIA_BROWSER_BOOKMARKS
*/
