/*
Copyright (c) 2015 NicoHood
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

#ifndef HIDBRIDGE_H
#define HIDBRIDGE_H

#include <Arduino.h>
#include "NHP.h"

//================================================================================
// Settings
//================================================================================


//================================================================================
// Definitions
//================================================================================

#define HIDBRIDGE_TX_TIMEOUT 1000

#define HIDBRIDGE_ADDRESS_CONTROL 0

#define HIDBRIDGE_CONTROL_ISREADY 0
#define HIDBRIDGE_CONTROL_NOTREADY 1

#define HID_BRIDGE_ERR_TIMEOUT 0
#define HID_BRIDGE_ERR_NHP_ERR 1
#define HID_BRIDGE_ERR_COMMAND 2
#define HID_BRIDGE_ERR_ADDRESS 3
#define HID_BRIDGE_ERR_CONTROL 4


//================================================================================
// HIDBridge
//================================================================================


class HIDBridge_{
public:
	HIDBridge_(void);

	bool begin(void);
	void readSerial(void);
	bool waitForReady(void);
	bool isReady;
	void task(void);
	void err(uint8_t error);

	inline void write(void){} // TODO
};

extern HIDBridge_ HIDBridge;

//================================================================================
// Function prototypes
//================================================================================


#endif // include guard