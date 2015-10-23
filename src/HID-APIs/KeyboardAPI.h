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
#include "ImprovedKeylayouts.h"

typedef union{
	// Low level key report: up to 6 keys and shift, ctrl etc at once
	uint8_t whole8[];
	uint16_t whole16[];
	uint32_t whole32[];
	struct{
		uint8_t modifiers;
		uint8_t reserved;
		uint8_t keys[6];
	};
} HID_KeyboardReport_Data_t;

class KeyboardAPI : public Print
{
public:
//TODO nkro compatiblity, merge them
  inline void begin(void);
  inline void end(void);
  
  inline size_t write(uint8_t k);
  inline size_t write(KeyboardKeycode k);
  inline size_t write(KeyboardModifier k);
  
  inline size_t press(uint8_t k);
  inline size_t press(KeyboardKeycode k);
  inline size_t press(KeyboardModifier k);
  
  inline size_t release(uint8_t k);
  inline size_t release(KeyboardKeycode k);
  inline size_t release(KeyboardModifier k);
  
  inline size_t add(uint8_t k);
  inline size_t add(KeyboardKeycode k);
  inline size_t add(KeyboardModifier k);
  
  inline size_t remove(uint8_t k);
  inline size_t remove(KeyboardKeycode k);
  inline size_t remove(KeyboardModifier k);
  
  // TODO media, system
  inline void setMedia(uint8_t m){
    _keyReport.reserved = m;
    send_now();
  }
 
  inline void releaseAll(void);
  inline void removeAll(void);
  inline void send_now(void);

  // Sending is public in the base class for advanced users.
  virtual void SendReport(void* data, int length) = 0;
  
protected:
  HID_KeyboardReport_Data_t _keyReport;
};

// Implementation is inline
#include "KeyboardAPI.hpp"
