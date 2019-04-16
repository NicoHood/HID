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
#include "../KeyboardLayouts/ImprovedKeylayouts.h"


class KeyboardAPI : public Print
{
public:
  inline void begin(void);
  inline void end(void);
  
  // Raw Keycode API functions
  inline size_t write(KeyboardKeycode k);
  inline size_t press(KeyboardKeycode k);
  inline size_t release(KeyboardKeycode k);
  inline size_t remove(KeyboardKeycode k);
  inline size_t add(KeyboardKeycode k);
  inline size_t releaseAll(void);
  //press(uint8_t key, uint8_t modifier) TODO variadic template
  
  // Print API functions
  inline virtual size_t write(uint8_t k) override;
  inline size_t press(uint8_t k);
  inline size_t release(uint8_t k);
  inline size_t add(uint8_t k);
  inline size_t remove(uint8_t k);

  // Needs to be implemented in a lower level
  virtual size_t removeAll(void) = 0;
  virtual int send(void) = 0;

private:
  virtual size_t set(KeyboardKeycode k, bool s) = 0;
  inline size_t set(uint8_t k, bool s);
};


// Implementation is inline
#include "KeyboardAPI.hpp"
