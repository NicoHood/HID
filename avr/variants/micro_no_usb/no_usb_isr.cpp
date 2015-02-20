#include <Arduino.h>
#include <pins_arduino.h>

// workaround for undefined USBCON has to be placed in every sketch
// otherwise the timings wont work correctly
// this is only needed for Leonardo/Micro boards and not for HoodLoader2
// due to a better bootloader reset (usb clock does not run after programming)
ISR(USB_GEN_vect)
{
	UDINT = 0;
}