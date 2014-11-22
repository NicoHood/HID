/*
Copyright (c) 2014 NicoHood
See the readme for credit to other people.

Media example

Press a button to play/pause music player
*/

const int pinLed = LED_BUILTIN;
const int pinButton = 2;

void setup() {
  pinMode(pinLed, OUTPUT);
  pinMode(pinButton, INPUT_PULLUP);

  // Sends a clean report to the host. This is important on any Arduino type.
  // Make sure all desired USB functions are activated in USBAPI.h!
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
