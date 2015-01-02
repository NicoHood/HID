/*
 Copyright (c) 2014 NicoHood
 See the readme for credit to other people.

 Consumer example (former Media example)

 Press a button to play/pause music player
 See HID Project documentation for more Consumer keys.

 Make sure the Consumer report is set in:
 sketchbook/hardware/HID/avr/variants/hid_descriptors/hid_descriptors.h

// basic Media key definitions, see HID Project and official USB docs for more
#define MEDIA_FAST_FORWARD	0xB3
#define MEDIA_REWIND	0xB4
#define MEDIA_NEXT	0xB5
#define MEDIA_PREVIOUS	0xB6
#define MEDIA_STOP	0xB7
#define MEDIA_PLAY_PAUSE	0xCD

#define MEDIA_VOLUME_MUTE	0xE2
#define MEDIA_VOLUME_UP	0xE9
#define MEDIA_VOLUME_DOWN	0xEA
*/

const int pinLed = LED_BUILTIN;
const int pinButton = 2;

void setup() {
  pinMode(pinLed, OUTPUT);
  pinMode(pinButton, INPUT_PULLUP);

  // Sends a clean report to the host. This is important on any Arduino type.
  Consumer.begin();
}

void loop() {
  if (!digitalRead(pinButton)) {
    digitalWrite(pinLed, HIGH);

    // See list above for more definitions or the official usb documentation
    Consumer.write(MEDIA_PLAY_PAUSE);

    // simple debounce
    delay(300);
    digitalWrite(pinLed, LOW);
  }
}
