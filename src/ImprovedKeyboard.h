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

#pragma once

#include "HID.h"

#if !defined(_USING_HID)

#warning "Using legacy HID core (non pluggable)"

#else

//================================================================================
//================================================================================
//  Keyboard

#include "HID-Project.h"
#include "ImprovedKeylayouts.h"

//  Low level key report: up to 6 keys and shift, ctrl etc at once
typedef struct
{
  uint8_t modifiers;
  uint8_t reserved;
  uint8_t keys[6];
} KeyReport;

class Keyboard_ : public Print
{
private:
  KeyReport _keyReport;
  void sendReport(KeyReport* keys);
public:
  Keyboard_(void);
  void begin(void);
  void end(void);
  size_t write(uint8_t k);
  size_t press(uint8_t k);
  size_t release(uint8_t k);
  void releaseAll(void);
  
  // Select a different layout optional:
  void useLayoutGerman(void);
  void useLayoutUS(void);
};
extern Keyboard_ Keyboard;

#endif
