#include "Arduino.h"

#ifdef ARDUINO_ARCH_SAMD

#if !defined(ARDUINO_API_VERSION)
int USB_SendControl(void* b, unsigned char c) {
    USBDevice.sendControl(b, c);
}

int USB_SendControl(uint8_t a, const void* b, uint8_t c) {
    USBDevice.sendControl(b, c);
}
#endif

#endif
