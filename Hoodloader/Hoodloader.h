/*
Copyright (c) 2014 NicoHood
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

/** \file
*
*  Header file for Hoodloader.c.
*/

#ifndef HOODLOADER_H
#define HOODLOADER_H

/* Includes: */
#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/power.h>
#include <avr/interrupt.h>
#include <string.h>

#include "Descriptors.h"

#include "Lib/LightweightRingBuff.h"

#include <LUFA/Drivers/Board/LEDs.h>
#include <LUFA/Drivers/USB/USB.h>
#include <LUFA/Platform/Platform.h>

//new, version: unnecessary? help <--
#include <LUFA/Version.h>
#include <LUFA/Drivers/Peripheral/Serial.h>

#include "../../NicoHoodProtocol/NicoHoodProtocol_c.h"

/* Macros: */

//new, normally passed through makefile <--
#define TX_RX_LED_PULSE_MS 3
#define PING_PONG_LED_PULSE_MS 100

#define AVR_RESET_LINE_PORT PORTD
#define AVR_RESET_LINE_DDR DDRD
#define AVR_RESET_LINE_MASK (1 << 7)

#define AVR_NO_HID_PORT PORTB
#define AVR_NO_HID_DDR DDRB
#define AVR_NO_HID_PIN PINB
#define AVR_NO_HID_MASK (1 << 2)

/** LED mask for the library LED driver, to indicate TX activity. */
#define LEDMASK_TX               LEDS_LED1

/** LED mask for the library LED driver, to indicate RX activity. */
#define LEDMASK_RX               LEDS_LED2

/** LED mask for the library LED driver, to indicate that an error has occurred in the USB interface. */
#define LEDMASK_ERROR            (LEDS_LED1 | LEDS_LED2)

/** LED mask for the library LED driver, to indicate that the USB interface is busy. */
#define LEDMASK_BUSY             (LEDS_LED1 | LEDS_LED2)		


/* Function Prototypes: */
void SetupHardware(void);

void checkNHPProtocol(RingBuff_Data_t input);
void checkNHPControlAddressError(void);
void writeNHPreadBuffer(uint8_t length);

void EVENT_USB_Device_Connect(void);
void EVENT_USB_Device_Disconnect(void);
void EVENT_USB_Device_ConfigurationChanged(void);
void EVENT_USB_Device_UnhandledControlRequest(void);

void EVENT_CDC_Device_LineEncodingChanged(USB_ClassInfo_CDC_Device_t* const CDCInterfaceInfo);
void EVENT_CDC_Device_ControLineStateChanged(USB_ClassInfo_CDC_Device_t* const CDCInterfaceInfo);	

// new <--
void EVENT_USB_Device_ControlRequest(void);
void EVENT_USB_Device_StartOfFrame(void);

bool CALLBACK_HID_Device_CreateHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
										 uint8_t* const ReportID,
										 const uint8_t ReportType,
										 void* ReportData,
										 uint16_t* const ReportSize);
void CALLBACK_HID_Device_ProcessHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
										  const uint8_t ReportID,
										  const uint8_t ReportType,
										  const void* ReportData,
										  const uint16_t ReportSize);
#endif

