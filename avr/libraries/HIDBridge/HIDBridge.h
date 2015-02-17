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

#define HIDBRIDGE_TX_SERIAL Serial

#ifdef HOODLOADER2
#define HIDBRIDGE_RX
#else
#define HIDBRIDGE_TX
#endif

//================================================================================
// Definitions
//================================================================================

#if defined(HIDBRIDGE_RX) && defined(HIDBRIDGE_TX)
#error Cannot send and receive at the same time
// also because it will create the instance of the class
// even if its not used, so we dont separate the TX and RX class names
// function names are kept similar
#endif

#define HIDBRIDGE_TX_TIMEOUT 1000

#define HIDBRIDGE_BAUD 2000000

#define HIDBRIDGE_ADDRESS_CONTROL 0

#define HIDBRIDGE_CONTROL_ISREADY 0
#define HIDBRIDGE_CONTROL_NOTREADY 1
#define HIDBRIDGE_CONTROL_NOTCONNECTED 1

#define HIDBRIDGE_ERR_TIMEOUT 0
#define HIDBRIDGE_ERR_NHP_ERR 1
#define HIDBRIDGE_ERR_COMMAND 2
#define HIDBRIDGE_ERR_ADDRESS 3
#define HIDBRIDGE_ERR_CONTROL 4
#define HIDBRIDGE_ERR_NOT_RDY 5


//================================================================================
// HIDBridge TX
//================================================================================

#ifdef HIDBRIDGE_TX
class HIDBridge_{
public:
	HIDBridge_(void);

	// user functions
	void begin(void);
	void end(void);

	// advanced user functions
	void read(void);
	bool available(void);

	// public to access via HID_SendReport
	void SendReport(uint8_t reportID, const void* data, int len);

	// debug
	void err(uint8_t error);
	inline void debugStream(Stream* s){
		debug = s;
	}
	Stream* debug;

private:
	bool isReady;
	bool isConnected;

	// temporary NHP protocol read data
	NHP_Read_Data_t nhp_read;
};

extern HIDBridge_ HIDBridge;
#endif

//================================================================================
// HIDBridge RX
//================================================================================

#ifdef HIDBRIDGE_RX
class HIDBridge_{
public:
	HIDBridge_(void);

	// user functions
	void begin(void);
	void end(void);

	// advanced user functions
	void read(void);
	bool available(void);

	// public to access via HID_SendReport
	void SendReport(uint8_t reportID, const void* data, int len);

	// debug
	void err(uint8_t error);
	inline void debugStream(Stream* s){
		debug = s;
	}
	Stream* debug;

private:
	bool isReady;

	// temporary NHP protocol read data
	NHP_Read_Data_t nhp_read;
};

extern HIDBridge_ HIDBridge;
#endif

//================================================================================
// Function prototypes
//================================================================================


#endif // include guard