/*
 Copyright (c) 2014 NicoHood
 See the readme for credit to other people.

 Keyboard example

 Press a button to write some text to your pc.
 See official and HID Project documentation for more infos
 https://github.com/NicoHood/HID/wiki/Keyboard-API
*/

const int pinLed = LED_BUILTIN;
const int pinButton = 2;

void setup() {
  pinMode(pinLed, OUTPUT);
  pinMode(pinButton, INPUT_PULLUP);

  // Starts Serial debug output
  Serial.begin(115200);

  // Sends a clean report to the host. This is important on any Arduino type.
  teensy_Keyboard.begin();
}


void loop() {
  if (!digitalRead(pinButton)) {
    digitalWrite(pinLed, HIGH);

    // Same use as the official library, pretty much self explaining
    teensy_Keyboard.println(F("This message was sent with my Arduino."));
    teensy_Keyboard.println(F("Lowercase:  abcdefghijklmnopqrstuvwxyz"));
    teensy_Keyboard.println(F("Uppercase:  ABCDEFGHIJKLMNOPQRSTUVWXYZ"));

/*
    // Single keypress
    teensy_Keyboard.press(MODIFIERKEY_SHIFT);
    teensy_Keyboard.press('a');
    teensy_Keyboard.releaseAll();
    
    teensy_Keyboard.println();
    
    // Write a single keystroke
    teensy_Keyboard.write('a');
    
    teensy_Keyboard.println();    
*/

    // simple debounce
    delay(300);
    digitalWrite(pinLed, LOW);
  }
}
