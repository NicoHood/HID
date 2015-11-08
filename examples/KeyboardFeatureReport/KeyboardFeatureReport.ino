/*
  Copyright (c) 2014-2015 NicoHood
  See the readme for credit to other people.

  KeyboardFeatureReport example

  Shows how to use BootKeyboard with a modified Hyperion Lightpack device.
  This example also works with RawHID.
  Might only work under linux.
  https://github.com/tvdzwan/hyperion/pull/407
  https://github.com/tvdzwan/hyperion/wiki
  https://github.com/FastLED/FastLED

  See HID Project documentation for more information.
  https://github.com/NicoHood/HID/wiki/RawHID-API
  https://github.com/NicoHood/HID/wiki/Keyboard-API#boot-keyboard
*/

#include "HID-Project.h"

const int pinLed = LED_BUILTIN;


// FastLED
#include "FastLED.h"

#define LED_PINS    MOSI, SCK // DATA_PIN, or DATA_PIN, CLOCK_PIN
#define COLOR_ORDER RGB
#define CHIPSET     WS2801 // WS2811, LPD8806, etc
#define NUM_LEDS    25

#define BRIGHTNESS  255  // Reduce power consumption
#define LED_DITHER  255  // Try 0 to disable flickering
#define CORRECTION  TypicalLEDStrip

CRGB leds[NUM_LEDS]; // Define the array of leds

void setup() {
  // FastLED setup
  FastLED.addLeds<CHIPSET, LED_PINS, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(CORRECTION);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.setDither(LED_DITHER);

  // Startup animation
  fill_solid(leds, NUM_LEDS, CRGB::Red);
  FastLED.show();
  delay(500);
  fill_solid(leds, NUM_LEDS, CRGB::Green);
  FastLED.show();
  delay(500);
  fill_solid(leds, NUM_LEDS, CRGB::Blue);
  FastLED.show();
  delay(500);
  FastLED.clear();
  FastLED.show();

  pinMode(pinLed, OUTPUT);

  // Sends a clean report to the host. This is important on any Arduino type.
  BootKeyboard.begin();

  // Let the feature report data directly point at the led array
  BootKeyboard.setFeatureReport(leds, sizeof(leds));
  BootKeyboard.enableFeatureReport();
}

void loop() {
  // Check if there is new feature request data from the keyboard
  if (BootKeyboard.availableFeatureReport())
  {
    digitalWrite(pinLed, HIGH);

    // Update leds, do not update in the loop, to avoid corrupted data.
    // For example if you write (0, 0, 0) and the interrupt
    // changes the data to (255, 255, 255) you might get (0, 255, 255).
    // Using a duplicated led array in cli() context would also work.
    FastLED.show();

    // Release data to let the USB interrupt overwrite it again
    BootKeyboard.enableFeatureReport();

    digitalWrite(pinLed, LOW);
  }
}
