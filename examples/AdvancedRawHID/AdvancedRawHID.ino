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
 RAWHID_TX_SIZE 63 // 1 byte for report ID
 RAWHID_RX_SIZE 63 // 1 byte for report ID
 */

// not needed for Leonardo/Micro
#include <HID.h>

// for Leonardo/Micro: make sure to activate desired USB functions in HID_Reports.h

const int pinLed = 13;
const int pinButton = 8;

void setup() {
  pinMode(pinLed, OUTPUT);
  pinMode(pinButton, INPUT_PULLUP);

  // Starts Serial at baud 115200. end just ends the Serial
  // Make sure to end your special HIDs before, this does not clear them!
  // You need this baud for the HID library but still can use other bauds
  // without HID functions.
  // not needed for Leonado/Micro, Serial will not be set
  HID.begin();
}

void loop() {
  if (!digitalRead(pinButton)) {
    digitalWrite(pinLed, HIGH);

    // direct without library. Always send RAWHID_RX_SIZE bytes!
    uint8_t buff[RAWHID_RX_SIZE]; // unitialized, has random values
    HID.sendReport(HID_REPORTID_RawKeyboardReport, buff, sizeof(buff));

    // with library
    memset(&buff, 42, sizeof(buff));
    RawHID.write(buff, sizeof(buff));

    // write a single byte, will fill the rest with zeros
    RawHID.write(0xCD);

    // huge buffer with library, will fill the rest with zeros
    uint8_t megabuff[256];
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
recv 63 bytes:
1B B7 0B 88 1F 99 1F 5A 95 A9 F7 80 95 90 95 BC
01 CD 01 08 95 A1 E2 1A 2E AA 1B BB 1B FD 01 0D
C0 AA 1F BB 1F EE 1F FF 1F A2 17 B3 07 E4 07 F5
07 20 F0 A2 1B B3 0B E4 0B F5 0B 66 1F 77 1F

// filled buff
recv 63 bytes:
2A 2A 2A 2A 2A 2A 2A 2A 2A 2A 2A 2A 2A 2A 2A 2A
2A 2A 2A 2A 2A 2A 2A 2A 2A 2A 2A 2A 2A 2A 2A 2A
2A 2A 2A 2A 2A 2A 2A 2A 2A 2A 2A 2A 2A 2A 2A 2A
2A 2A 2A 2A 2A 2A 2A 2A 2A 2A 2A 2A 2A 2A 2A

// single byte filled with zero
recv 63 bytes:
CD 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00

// huge buffer filled with zero at the end
recv 63 bytes:
00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F
10 11 12 13 14 15 16 17 18 19 1A 1B 1C 1D 1E 1F
20 21 22 23 24 25 26 27 28 29 2A 2B 2C 2D 2E 2F
30 31 32 33 34 35 36 37 38 39 3A 3B 3C 3D 3E

recv 63 bytes:
3F 40 41 42 43 44 45 46 47 48 49 4A 4B 4C 4D 4E
4F 50 51 52 53 54 55 56 57 58 59 5A 5B 5C 5D 5E
5F 60 61 62 63 64 65 66 67 68 69 6A 6B 6C 6D 6E
6F 70 71 72 73 74 75 76 77 78 79 7A 7B 7C 7D

recv 63 bytes:
7E 7F 80 81 82 83 84 85 86 87 88 89 8A 8B 8C 8D
8E 8F 90 91 92 93 94 95 96 97 98 99 9A 9B 9C 9D
9E 9F A0 A1 A2 A3 A4 A5 A6 A7 A8 A9 AA AB AC AD
AE AF B0 B1 B2 B3 B4 B5 B6 B7 B8 B9 BA BB BC

recv 63 bytes:
BD BE BF C0 C1 C2 C3 C4 C5 C6 C7 C8 C9 CA CB CC
CD CE CF D0 D1 D2 D3 D4 D5 D6 D7 D8 D9 DA DB DC
DD DE DF E0 E1 E2 E3 E4 E5 E6 E7 E8 E9 EA EB EC
ED EE EF F0 F1 F2 F3 F4 F5 F6 F7 F8 F9 FA FB

recv 63 bytes:
FC FD FE FF 00 00 00 00 00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00

// print
recv 63 bytes:
48 65 6C 6C 6F 20 57 6F 72 6C 64 00 00 00 00 00
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00

//\r
recv 63 bytes:
0D 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00

//\n
recv 63 bytes:
0A 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00

//write
recv 63 bytes:
48 65 6C 6C 6F 20 57 6F 72 6C 64 0D 0A 00 00 00
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
*/