/*
  Copyright (c) 2021 ilufang
  See the readme for credit to other people.

  Multi-touch touchscreen example
  Draw 7 parallel lines across the screen.
  Open Microsoft Whiteboard, select a brush and press the button.

  See HID Project documentation for more infos
  https://github.com/NicoHood/HID/wiki/Gamepad-API
*/

#include <HID-Project.h>

const int pinButton = 2;

void setup() {
	pinMode(pinButton, INPUT_PULLUP);
	MultiTouch.begin();
}

void loop() {
	while(digitalRead(pinButton));

	int16_t x = 2000, y = 2000;

	for (; x <= 8000; x+=10) {
		for (int i = 0; i < 7; i++) {
			MultiTouch.setFinger(i, x, y+i*1000, (i+1)*15);
		}
		MultiTouch.send();
		delay(10);
	}

	for (int i = 0; i < 7; i++) {
		MultiTouch.releaseFinger(i);
	}
	MultiTouch.send();
}
