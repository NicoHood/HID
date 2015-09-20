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

#include "HID-Project.h"
#include "ImprovedKeylayouts.h"

// Max value for USB EP_SIZE 16
// +1 reportID, +1 modifier, +1 custom key
#define NKRO_KEY_COUNT (8*13)

typedef union{
	// modifier + keymap + 1 custom key
	uint8_t whole8[];
	uint16_t whole16[];
	uint32_t whole32[];
	struct{
		uint8_t modifiers;
		uint8_t keys[NKRO_KEY_COUNT / 8];
		uint8_t key;
	};
} HID_NKROKeyboardReport_Data_t;

class NKROKeyboard_ : public Print, private HIDDevice
{
protected:
	HID_NKROKeyboardReport_Data_t _keyReport;
	void sendReport(HID_NKROKeyboardReport_Data_t* keys);
#if defined(HID_KEYBOARD_LEDS_ENABLED)
  virtual void setReportData(const void* data, int len);
  uint8_t leds;
#endif
public:
	NKROKeyboard_(void);
	void begin(void);
	void end(void);
	size_t write(uint8_t k);
	size_t press(uint8_t k);
	size_t release(uint8_t k);
	void releaseAll(void);
	void send_now(void);

	size_t writeKeycode(uint8_t k);
	size_t pressKeycode(uint8_t k);
	size_t releaseKeycode(uint8_t k);
	size_t addKeyToReport(uint8_t k);
	size_t addKeycodeToReport(uint8_t k);
	size_t removeKeyFromReport(uint8_t k);
	size_t removeKeycodeFromReport(uint8_t k);

#if defined(HID_KEYBOARD_LEDS_ENABLED)
  uint8_t getLeds(void);
#endif
};
extern NKROKeyboard_ NKROKeyboard;

#endif
