/*
Copyright (c) 2014-2015 NicoHood
See the readme for credit to other people.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

// Include guard
#pragma once

#include <Arduino.h>
#include "HID-Settings.h"

typedef union{
	// SurfaceDial report: 1 button, 15-bit rotation, position
	uint8_t whole8[0];
	uint16_t whole16[0];
	uint32_t whole32[0];
	uint64_t whole64[0];
	struct{
		uint16_t button: 1;
		uint16_t rotation: 15;
		int16_t xAxis: 16;
		int16_t yAxis: 16;
		uint16_t width: 16;


	};
} HID_SurfaceDialReport_Data_t;

class SurfaceDialAPI
{
public:
  inline SurfaceDialAPI(void);
  inline void begin(void);
  inline void end(void);
  inline void click(void);
  inline void rotate(int16_t rotation);
  inline void position(int16_t x, int16_t y);
  inline void reportData(int16_t rotation, int16_t x, int16_t y);
  inline void press(void);
  inline void release(void);
  inline void releaseAll(void);
  inline void putOnScreen(bool s);
  inline bool isPressed();
  inline int8_t getX();
  inline int8_t getY();
  inline bool getOnScreen();
  inline void update();

  // Sending is public in the base class for advanced users.
  virtual void SendReport(void* data, int length) = 0;

protected:
  bool _button;
  bool _onScreen;
  int16_t _xAxis;
  int16_t _yAxis;
  inline void button(bool b);
  inline void xAxis(int16_t x);
  inline void yAxis(int16_t y);
  inline void onScreen(bool s);
};

// Implementation is inline
#include "SurfaceDialAPI.hpp"
