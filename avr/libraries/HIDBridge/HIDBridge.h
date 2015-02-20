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

//TODO replace with USB and IO
#define HIDBRIDGE_SERIAL SERIAL_PORT_HARDWARE

#define HIDBRIDGE_BAUD 2000000 // transfer at highest possible baud

// use Arduino builtin serialEvent() function to call the HIDBridge task?
#define HIDBRIDGE_USE_SERIAL_EVENT

//#define DEBUG
#define USB_DEBUG

// which MCU should act as USB or IO part?
#ifdef USBCON
#define HIDBRIDGE_USB
#else
#define HIDBRIDGE_IO
#endif

// define if the MCU can do RX, TX or both
// minimal setup: USB RX, IO TX
#ifdef HIDBRIDGE_USB
#define HIDBRIDGE_RX
//#define HIDBRIDGE_TX
#endif
#ifdef HIDBRIDGE_IO
//#define HIDBRIDGE_RX
#define HIDBRIDGE_TX
#endif

//================================================================================
// Definitions
//================================================================================

#if defined(HIDBRIDGE_USB) && defined(HIDBRIDGE_IO)
#error Cannot send and receive at the same time
// also because it will create the instance of the class
// even if its not used, so we dont separate the TX and RX class names
// function names are kept similar
#endif

#define HIDBRIDGE_SERIAL_EVENT_WRAPPER_Serial serialEvent
#define HIDBRIDGE_SERIAL_EVENT_WRAPPER_Serial1 serialEvent1
#define HIDBRIDGE_SERIAL_EVENT HIDBRIDGE_SERIAL_EVENT_WRAPPER_ ## Serial1


#define HIDBRIDGE_TX_TIMEOUT 800 // should be smaller than RX
#define HIDBRIDGE_RX_TIMEOUT 1000

#define HIDBRIDGE_CONTROL_ADDRESS 0x00
#define HIDBRIDGE_CONTROL_NOTREADY 0
#define HIDBRIDGE_CONTROL_READY 1
#define HIDBRIDGE_CONTROL_NOTCONNECTED 2

#define HIDBRIDGE_COMMAND_END 0


#define HIDBRIDGE_ERR_TIMEOUT 0
#define HIDBRIDGE_ERR_NHP_ERR 1
#define HIDBRIDGE_ERR_COMMAND 2
#define HIDBRIDGE_ERR_ADDRESS 3
#define HIDBRIDGE_ERR_CONTROL 4
#define HIDBRIDGE_ERR_NOT_RDY 5
#define HIDBRIDGE_ERR_READ_TO 6
#define HIDBRIDGE_ERR_CMD_END 7
#define HIDBRIDGE_ERR_CMD_RID 8
#define HIDBRIDGE_ERR_MCU_RST 9
#define HIDBRIDGE_ERR_SERIALB 10


//================================================================================
// HIDBridge
//================================================================================


class HIDBridge_{
public:
	HIDBridge_(void);

	// user functions
	void begin(void);
	void end(void);

	void task(void);

	// advanced user functions
	void read(void);
	bool available(void);

	// public to access via HID_SendReport
	void SendReport(uint8_t reportID, const void* data, int len);

	// debug
	void err(uint8_t error);
	void writeState(void);

	inline void debugStream(Stream* s){
		debug = s;
	}
	Stream* debug;



	bool txReady;
	bool rxReady;
	

private:

	// inlined functions to clear the code
	// used in read(), not public accessible
	inline void proceedAddress(void); //TODO change to always inline?
	inline void proceedCommand(void);
	
	bool isConnected;
	uint32_t readTimeout;
	uint32_t writeTimeout;
	uint8_t recvLength;
	uint8_t reportID;
	uint8_t reportLength;
	uint8_t hidReport[USB_EP_SIZE - 1];

	// temporary NHP protocol read data
	NHP_Read_Data_t nhp_read;
};

extern HIDBridge_ HIDBridge;


//================================================================================
// Function prototypes
//================================================================================


#endif // include guard