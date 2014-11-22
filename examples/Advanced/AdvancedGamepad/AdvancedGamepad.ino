/*
 Copyright (c) 2014 NicoHood
 See the readme for credit to other people.
 
 Advanced Gamepad example
 */

// include HID library
#include <HID.h>

// see HID_Reports.h for all data structures
HID_GamepadReport_Data_t Gamepadreport;

const int pinLed = LED_BUILTIN;
const int pinButton = 2;

// see HID_Reports.h for all data structures
HID_GamepadReport_Data_t Gamepadreport;

void setup() {
  pinMode(pinLed, OUTPUT);
  pinMode(pinButton, INPUT_PULLUP);

  // Sends a clean report to the host. This is important on any Arduino type.
  // Make sure all desired USB functions are activated in USBAPI.h!
  memset(&Gamepadreport, 0, sizeof(Gamepadreport));
  HID_SendReport(HID_REPORTID_Gamepad1Report, &Gamepadreport, sizeof(Gamepadreport));
}

void loop() {
  if (!digitalRead(pinButton)) {
    digitalWrite(pinLed, HIGH);

    // This demo is actually made for advanced users to show them how they can write an own report.
    // This might be useful for a Gamepad if you want to edit the values direct on your own. 

    // count with buttons binary
    static uint32_t count = 0;
    Gamepadreport.whole32[0] = count++;

    // move x/y Axis to a new position (16bit)
    Gamepadreport.whole16[2] = (random(0xFFFF));

    // functions before only set the values
    // this writes the report to the host
    HID_SendReport(HID_REPORTID_Gamepad1Report, &Gamepadreport, sizeof(Gamepadreport));

    // simple debounce
    delay(300);
    digitalWrite(pinLed, LOW);
  }
}

