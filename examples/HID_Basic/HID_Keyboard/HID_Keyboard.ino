/*
 Copyright (c) 2014 NicoHood
 See the readme for credit to other people.

 Keyboard example

 Press a button to write some text to your pc.
 See official and HID Project documentation for more infos
*/

const int pinLed = LED_BUILTIN;
const int pinButton = 2;

void setup() {
  pinMode(pinLed, OUTPUT);
  pinMode(pinButton, INPUT_PULLUP);

  // Starts Serial debug output
  Serial.begin(115200);

  // Sends a clean report to the host. This is important on any Arduino type.
  Keyboard.begin();
}


void loop() {
  if (!digitalRead(pinButton)) {
    digitalWrite(pinLed, HIGH);

    // Same use as the official library, pretty much self explaining
    Keyboard.println(F("This message was sent with my Arduino."));
    Serial.println(F("Serial port is still working and not glitching out"));

    // simple debounce
    delay(300);
    digitalWrite(pinLed, LOW);
  }
}

/*
Definitions:
 
#define KEY_PRINT		0xCE
#define KEY_NUM_LOCK		0xDB
#define KEY_SCROLL_LOCK		0xCF
#define KEY_PAUSE		0xD0

#define KEY_LEFT_CTRL		0x80
#define KEY_LEFT_SHIFT		0x81
#define KEY_LEFT_ALT		0x82
#define KEY_LEFT_GUI		0x83
#define KEY_LEFT_WINDOWS KEY_LEFT_GUI
#define KEY_RIGHT_CTRL		0x84
#define KEY_RIGHT_SHIFT		0x85
#define KEY_RIGHT_ALT		0x86
#define KEY_RIGHT_GUI		0x87
#define KEY_RIGHT_WINDOWS KEY_RIGHT_GUI

#define KEY_UP_ARROW		0xDA
#define KEY_DOWN_ARROW		0xD9
#define KEY_LEFT_ARROW		0xD8
#define KEY_RIGHT_ARROW		0xD7
#define KEY_BACKSPACE		0xB2
#define KEY_TAB				0xB3
#define KEY_RETURN			0xB0
#define KEY_ESC				0xB1
#define KEY_INSERT			0xD1
#define KEY_DELETE			0xD4
#define KEY_PAGE_UP			0xD3
#define KEY_PAGE_DOWN		        0xD6
#define KEY_HOME			0xD2
#define KEY_END				0xD5
#define KEY_CAPS_LOCK		        0xC1
#define KEY_F1				0xC2
#define KEY_F2				0xC3
#define KEY_F3				0xC4
#define KEY_F4				0xC5
#define KEY_F5				0xC6
#define KEY_F6				0xC7
#define KEY_F7				0xC8
#define KEY_F8				0xC9
#define KEY_F9				0xCA
#define KEY_F10				0xCB
#define KEY_F11				0xCC
#define KEY_F12				0xCD

#define LED_NUM_LOCK			0x01
#define LED_CAPS_LOCK			0x02
#define LED_SCROLL_LOCK			0x04
 */
