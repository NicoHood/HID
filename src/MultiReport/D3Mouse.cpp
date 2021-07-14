#include "D3Mouse.h"

static const uint8_t _hidMultiReportDescriptorD3Mouse[] PROGMEM = {
    0x05, 0x01,       // USAGE_PAGE (Generic Desktop)
    0x09, 0x08,       //   USAGE (Multiaxis)
    0xa1, 0x01,       // COLLECTION (Application)
    0xa1, 0x00,       //   COLLECTION (Physical)
    0x05, 0x09,       //     USAGE_PAGE (Button)
    0x19, 0x01,       //     USAGE_MINIMUM (Button 1)
    0x29, 0x03,       //     USAGE_MAXIMUM (Button 3)
    0x15, 0x00,       //     LOGICAL_MINIMUM (0)
    0x25, 0x01,       //     LOGICAL_MAXIMUM (1)
    0x95, 0x03,       //     REPORT_COUNT (3)
    0x75, 0x01,       //     REPORT_SIZE (1)
    0x81, 0x02,       //     INPUT (Data,Var,Abs)
    0x05, 0x01,       //     USAGE_PAGE (Generic Desktop)
    0x09, 0x30,       //     USAGE (X)
    0x09, 0x31,       //     USAGE (Y)
    0x09, 0x32,       //     USAGE (Z)
    0x09, 0x33,       //     USAGE (Rx)
    0x09, 0x34,       //     USAGE (Ry)
    0x09, 0x35,       //     USAGE (Rz)
    0x16, 0x00, 0xfe, //     LOGICAL_MINIMUM (-512)
    0x26, 0x00, 0x02, //     LOGICAL_MAXIMUM (512)
    0x75, 0x0a,       //     REPORT_SIZE (10)
    0x95, 0x06,       //     REPORT_COUNT (6)
    0x81, 0x06,       //     INPUT (Data,Var,Rel)
    0xc0,             //   END_COLLECTION
    0xc0              // END_COLLECTION
};

D3Mouse_ ::D3Mouse_(void)
{
    static HIDSubDescriptor node(_hidMultiReportDescriptorD3Mouse, sizeof(_hidMultiReportDescriptorD3Mouse));
    HID().AppendDescriptor(&node);
}

void D3Mouse_ ::SendReport(void *data, int length)
{
    HID().SendReport(HID_REPORTID_D3MOUSE, data, length);
}

D3Mouse_ D3Mouse;
