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

#include "KeyboardAPI.h"
#include "ConsumerAPI.h"

typedef union ATTRIBUTE_PACKED {
	// Low level key report: up to 6 keys and shift, ctrl etc at once
	uint8_t whole8[0];
	uint16_t whole16[0];
	uint32_t whole32[0];
	struct ATTRIBUTE_PACKED {
		uint8_t modifiers;
		uint8_t reserved;
		KeyboardKeycode keycodes[6];
	};
	uint8_t keys[8];
} HID_KeyboardReport_Data_t;


class DefaultKeyboardAPI : public KeyboardAPI
{
public:
  // Add special consumer key API for the reserved byte
  inline size_t write(ConsumerKeycode k);
  inline size_t press(ConsumerKeycode k);
  inline size_t release(ConsumerKeycode k);
  inline size_t add(ConsumerKeycode k);
  inline size_t remove(ConsumerKeycode k);

  // Also use the base class functions
  // http://en.cppreference.com/w/cpp/language/using_declaration
  using KeyboardAPI::write;
  using KeyboardAPI::press;
  using KeyboardAPI::release;
  using KeyboardAPI::add;
  using KeyboardAPI::remove;

  // Implement adding/removing key functions
  inline virtual size_t removeAll(void) override;

  // Needs to be implemented in a lower level
  virtual int send(void) = 0;

protected:
  HID_KeyboardReport_Data_t _keyReport;

private:
  inline virtual size_t set(KeyboardKeycode k, bool s) override;
};

// Implementation is inline
#include "DefaultKeyboardAPI.hpp"
