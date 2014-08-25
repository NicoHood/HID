/*
 Copyright (c) 2014 NicoHood
 See the readme for credit to other people.

 Advanced RawHID example
 Shows how to send bytes via raw HID
 Press a button to send some example values.
 Keep in mind that you can only send full data packets, the rest is filled with zero!
 
 Definitions from HID_Reports.h:
 RAWHID_USAGE_PAGE 0xFFC0 // recommended: 0xFF00 to 0xFFFF
 RAWHID_USAGE		0x0C00 // recommended: 0x0100 to 0xFFFF
 RAWHID_TX_SIZE 15 // 1 byte for report ID
 RAWHID_RX_SIZE 15 // 1 byte for report ID
 */

// include HID library
#include <HID.h>

const int pinLed = 13;
const int pinButton = 8;

void setup() {
  pinMode(pinLed, OUTPUT);
  pinMode(pinButton, INPUT_PULLUP);

  // Starts Serial at baud 115200 otherwise HID wont work on Uno/Mega.
  // This is not needed for Leonado/(Pro)Micro but make sure to activate desired USB functions in HID.h
  Serial.begin(SERIAL_HID_BAUD);

  // no begin function needed for RawHID
}

void loop() {
  if (!digitalRead(pinButton)) {
    digitalWrite(pinLed, HIGH);

    // direct without library. Always send RAWHID_RX_SIZE bytes!
    uint8_t buff[RAWHID_RX_SIZE]; // unitialized, has random values
    HID_SendReport(HID_REPORTID_RawKeyboardReport, buff, sizeof(buff));

    // with library
    memset(&buff, 42, sizeof(buff));
    RawHID.write(buff, sizeof(buff));

    // write a single byte, will fill the rest with zeros
    RawHID.write(0xCD);

    // huge buffer with library, will fill the rest with zeros
    uint8_t megabuff[64];
    for (int i = 0; i < sizeof(megabuff); i++)
      megabuff[i] = i;
    RawHID.write(megabuff, sizeof(megabuff));

    // You can use print too, but better dont use a linefeed
    RawHID.println("Hello World");

    // And compare it to write:
    RawHID.write("Hello World\r\n");

    // simple debounce
    delay(300);
    digitalWrite(pinLed, LOW);
  }
}

/*
Expected output:

// manual with unintialized buff
recv 15 bytes:
01 55 C1 FF 01 01 01 00 00 01 00 00 01 00 20

// filled buff
recv 15 bytes:
2A 2A 2A 2A 2A 2A 2A 2A 2A 2A 2A 2A 2A 2A 2A

// single byte filled with zero
recv 15 bytes:
CD 00 00 00 00 00 00 00 00 00 00 00 00 00 00

// huge buffer filled with zero at the end
recv 15 bytes:
00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E

recv 15 bytes:
0F 10 11 12 13 14 15 16 17 18 19 1A 1B 1C 1D

recv 15 bytes:
1E 1F 20 21 22 23 24 25 26 27 28 29 2A 2B 2C

recv 15 bytes:
2D 2E 2F 30 31 32 33 34 35 36 37 38 39 3A 3B

recv 15 bytes:
3C 3D 3E 3F 00 00 00 00 00 00 00 00 00 00 00

// print
recv 15 bytes:
48 65 6C 6C 6F 20 57 6F 72 6C 64 00 00 00 00

//\r
recv 15 bytes:
0D 00 00 00 00 00 00 00 00 00 00 00 00 00 00

//\n
recv 15 bytes:
0A 00 00 00 00 00 00 00 00 00 00 00 00 00 00

//write
recv 15 bytes:
48 65 6C 6C 6F 20 57 6F 72 6C 64 0D 0A 00 00

*/