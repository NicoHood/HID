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

#define HID_h

#include <stdint.h>
#include <Arduino.h>

//http://stackoverflow.com/questions/1837165/can-two-classes-see-each-other-using-c

class HID_;
extern HID_ HID;

class HIDDevice
{
public:
  HIDDevice(uint8_t* data, uint16_t length, uint8_t ID);
  
  // Needs to be public for static HID_ function access
  // Inherit this device private and everything should be fine
//private:
  HIDDevice* next = NULL;

  // HID Descriptor
  const uint8_t* descriptorData;
  const uint16_t descriptorLength;
  const uint8_t reportID;
  
  virtual void setReportData(const void* data, int len);

protected:
  // Could be used and inherited public for custom, professional usage, like raw Keyboard
  // As an alternative you may still call the HID singleton.
  void SendReport(const void* data, int len);
};



