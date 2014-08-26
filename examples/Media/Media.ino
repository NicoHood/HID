/*
Copyright (c) 2014 NicoHood
See the readme for credit to other people.

Media example
Press a button to play/pause music player
*/

// include HID library
#include <HID.h>

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
  Media.begin();
}

void loop() {
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
