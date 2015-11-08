/*
  Copyright (c) 2014-2015 NicoHood
  See the readme for credit to other people.

  RawHIDPaintpack example

  Shows how to use RawHID with the Hyperion Lightpack device.
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
uint8_t rawhidData[sizeof(leds) + 2];

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

  // Set the RawHID OUT report array.
  // Feature reports are also (parallel) possible, see the other example for this.
  RawHID.begin(rawhidData, sizeof(rawhidData));
}

void loop() {
  // Check if there is new data from the RawHID device
  auto bytesAvailable = RawHID.available();
  if (bytesAvailable == sizeof(rawhidData))
  {
    digitalWrite(pinLed, HIGH);

    // Check header for errors
    if (RawHID.read() != 3) {
      return;
    }
    if (RawHID.read() != 0) {
      return;
    }

    // Write data to led array
    uint8_t* ptr = (uint8_t*)leds;
    for (int i = 0; i < sizeof(leds); i++) {
      *ptr = RawHID.read();
      ptr++;
    }

    // Update leds, do not update in the loop, to avoid corrupted data.
    // For example if you write (0, 0, 0) and the interrupt
    // changes the data to (255, 255, 255) you might get (0, 255, 255).
    // Using a duplicated led array in cli() context would also work.
    FastLED.show();

    digitalWrite(pinLed, LOW);
  }
}
