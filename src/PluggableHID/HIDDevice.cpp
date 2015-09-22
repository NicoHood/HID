
#include "PluggableUSB.h"
#include "HIDDevice.h"
#include "HID.h"
#include "HID-Project.h"

#if defined(USBCON)

HIDDevice::HIDDevice(uint8_t* data, uint16_t length, uint8_t ID) :
descriptorData(data), descriptorLength(length), reportID(ID)
{
    HID.AppendDescriptor(this);
}

void HIDDevice::SendReport(const void* data, int len){
    HID.SendReport(reportID, data, len);
}

void HIDDevice::SendRawReport(const void* data, int len){
    HID.SendReport(HID_REPORTID_NONE, data, len);
}

void HIDDevice::setReportData(void* &data, int len){
    // Discard this information if its not implemented by the HIDDevice
}

uint8_t HIDDevice::getProtocol(void){
    return HID._hid_protocol;
}
  
#endif
