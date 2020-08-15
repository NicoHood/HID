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

#include "SurfaceDial.h"

static const uint8_t _hidMultiReportDescriptorSurfaceDial[] PROGMEM = {
    // Integrated Radial Controller TLC
    0x05, 0x01,       // USAGE_PAGE (Generic Desktop)
    0x09, 0x0e,       // USAGE (System Multi-Axis Controller)
    0xa1, 0x01,       // COLLECTION (Application)
    0x85, HID_REPORTID_SURFACEDIAL,       //   REPORT_ID (Radial Controller)
    0x05, 0x0d,       //   USAGE_PAGE (Digitizers)
    0x09, 0x21,       //   USAGE (Puck)
    0xa1, 0x00,       //   COLLECTION (Physical)
    0x05, 0x09,       //     USAGE_PAGE (Buttons)
    0x09, 0x01,       //     USAGE (Button 1)
    0x95, 0x01,       //     REPORT_COUNT (1)
    0x75, 0x01,       //     REPORT_SIZE (1)
    0x15, 0x00,       //     LOGICAL_MINIMUM (0)
    0x25, 0x01,       //     LOGICAL_MAXIMUM (1)
    0x81, 0x02,       //     INPUT (Data,Var,Abs)
    0x05, 0x01,       //     USAGE_PAGE (Generic Desktop)
    0x09, 0x37,       //     USAGE (Dial)
    0x95, 0x01,       //     REPORT_COUNT (1)
    0x75, 0x0f,       //     REPORT_SIZE (15)
    0x55, 0x0f,       //     UNIT_EXPONENT (-1)
    0x65, 0x14,       //     UNIT (Degrees, English Rotation)
    0x36, 0xf0, 0xf1, //     PHYSICAL_MINIMUM (-3600)
    0x46, 0x10, 0x0e, //     PHYSICAL_MAXIMUM (3600)
    0x16, 0xf0, 0xf1, //     LOGICAL_MINIMUM (-3600)
    0x26, 0x10, 0x0e, //     LOGICAL_MAXIMUM (3600)
    0x81, 0x06,       //     INPUT (Data,Var,Rel)
    // 0x09, 0x30,       //     USAGE (X)
    // 0x75, 0x10,       //     REPORT_SIZE (16)
    // 0x55, 0x0d,       //     UNIT_EXPONENT (-3)
    // 0x65, 0x13,       //     UNIT (Inch,EngLinear)
    // 0x35, 0x00,       //     PHYSICAL_MINIMUM (0)
    // 0x46, 0xc0, 0x5d, //     PHYSICAL_MAXIMUM (24000)
    // 0x15, 0x00,       //     LOGICAL_MINIMUM (0)
    // 0x26, 0xff, 0x7f, //     LOGICAL_MAXIMUM (32767)
    // 0x81, 0x02,       //     INPUT (Data,Var,Abs)
    // 0x09, 0x31,       //     USAGE (Y)
    // 0x46, 0xb0, 0x36, //     PHYSICAL_MAXIMUM (14000)
    // 0x81, 0x02,       //     INPUT (Data,Var,Abs)
    // 0x05, 0x0d,       //     USAGE_PAGE (Digitizers)
    // 0x09, 0x48,       //     USAGE (Width)
    // 0x36, 0xb8, 0x0b, //     PHYSICAL_MINIMUM (3000)
    // 0x46, 0xb8, 0x0b, //     PHYSICAL_MAXIMUM (3000)
    // 0x16, 0xb8, 0x0b, //     LOGICAL_MINIMUM (3000)
    // 0x26, 0xb8, 0x0b, //     LOGICAL_MAXIMUM (3000)
    // 0x81, 0x03,        //     INPUT (Cnst,Var,Abs)
    0xc0,             //   END_COLLECTION
    0xc0              // END_COLLECTION
};

SurfaceDial_::SurfaceDial_(void)
{
    static HIDSubDescriptor node(_hidMultiReportDescriptorSurfaceDial, sizeof(_hidMultiReportDescriptorSurfaceDial));
    HID().AppendDescriptor(&node);
}

void SurfaceDial_::SendReport(void *data, int length)
{
    HID().SendReport(HID_REPORTID_SURFACEDIAL, data, length);
}

SurfaceDial_ SurfaceDial;
