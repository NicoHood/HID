/*
 Copyright (c) 2014 NicoHood
 See the readme for credit to other people.

 Keyboard Keycode example

 Press a button to write some text to your pc.
 This example is made for advanced users, to add specific keys to the HID report.
 See official and HID Project and USB docs documentation for more infos
 https://github.com/NicoHood/HID/wiki/Keyboard-API
 http://www.usb.org/developers/hidpage/Hut1_12v2.pdf
*/

const int pinLed = LED_BUILTIN;
const int pinButton = 2;

void setup() {
  pinMode(pinLed, OUTPUT);
  pinMode(pinButton, INPUT_PULLUP);

  // Sends a clean report to the host. This is important on any Arduino type.
  Keyboard.begin();
}

void loop() {
  if (!digitalRead(pinButton)) {
    digitalWrite(pinLed, HIGH);

    // the "normal" way
    //Keyboard.println("Test");

    // press 'a' via normal API
    //Keyboard.write('a');

    // press 'a' via keycodes
    Keyboard.writeKeycode(0x04);

    // press the contect menu button via normal API
    //Keyboard.write(KEY_MENU);

    // press the context menu button via keycodes (right mouse click)
    //Keyboard.writeKeycode(0x65);

    // You can also try some specific keys that do not work on every OS
    /*
    #define HID_KEYBOARD_MUTE	0x7F
    #define HID_KEYBOARD_VOLUME_UP	0x80
    #define HID_KEYBOARD_VOLUME_DOWN	0x81
    */
    //Keyboard.writeKeycode(0x7F);

    // simple debounce
    delay(300);
    digitalWrite(pinLed, LOW);
  }
}
