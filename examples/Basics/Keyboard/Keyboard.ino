/*
Copyright (c) 2014 NicoHood
 See the readme for credit to other people.
 
 Keyboard example
 
 Press a button to write some text to your pc.
 See official documentation for more infos
 */

const int pinLed = LED_BUILTIN;
const int pinButton = 2;

void setup() {
  pinMode(pinLed, OUTPUT);
  pinMode(pinButton, INPUT_PULLUP);

  // Starts Serial debug output
  Serial.begin(115200);

  // Sends a clean report to the host. This is important on any Arduino type.
  // Make sure all desired USB functions are activated in USBAPI.h!
  Keyboard.begin();
}


void loop() {
  if (!digitalRead(pinButton)) {
    digitalWrite(pinLed, HIGH);

    // Same use as the official library, pretty much self explaining
    Keyboard.println("This message was sent with my Arduino.");
    Serial.println("Serial port is still working and not glitching out");

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