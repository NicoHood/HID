/*
Copyright (c) 2014-2015 NicoHood
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

#pragma once

#include "HID.h"

#if !defined(_USING_HID)

#warning "Using legacy HID core (non pluggable)"

#else

#include "HID-Project.h"

//================================================================================
// RawHID
//================================================================================

// RawHID might never work with multireports, because of OS problems
// therefore we have to make it a single report with no idea. No other HID device will be supported then.
#undef RAWHID_USAGE_PAGE
#define RAWHID_USAGE_PAGE	0xFFC0 // recommended: 0xFF00 to 0xFFFF

#undef RAWHID_USAGE
#define RAWHID_USAGE		0x0C00 // recommended: 0x0100 to 0xFFFF

// Keep one byte offset for the reportID if used
#if (HID_REPORTID_RAWHID)
#define RAWHID_SIZE (USB_EP_SIZE-1)
#else
#define RAWHID_SIZE (USB_EP_SIZE)
#endif

#undef RAWHID_TX_SIZE
#define RAWHID_TX_SIZE RAWHID_SIZE

#undef RAWHID_RX_SIZE
#define RAWHID_RX_SIZE RAWHID_SIZE

#define LSB(_x) ((_x) & 0xFF)
#define MSB(_x) ((_x) >> 8)

static const uint8_t _rawhidReportDescriptor[] PROGMEM = {
	/*    RAW HID */
    0x06, LSB(RAWHID_USAGE_PAGE), MSB(RAWHID_USAGE_PAGE),      /* 30 */
    0x0A, LSB(RAWHID_USAGE), MSB(RAWHID_USAGE),

    0xA1, 0x01,                  /* Collection 0x01 */
#if (HID_REPORTID_RAWHID)
    0x85, HID_REPORTID_RAWHID,			 /* REPORT_ID */
#endif
    0x75, 0x08,                  /* report size = 8 bits */
    0x15, 0x00,                  /* logical minimum = 0 */
    0x26, 0xFF, 0x00,            /* logical maximum = 255 */

    0x95, RAWHID_TX_SIZE,        /* report count TX */
    0x09, 0x01,                  /* usage */
    0x81, 0x02,                  /* Input (array) */

    0x95, RAWHID_RX_SIZE,        /* report count RX */
    0x09, 0x02,                  /* usage */
    0x91, 0x02,                  /* Output (array) */
    0xC0                         /* end collection */ 
};

typedef union{
	// a RAWHID_TX_SIZE byte buffer for tx
	uint8_t whole8[];
	uint16_t whole16[];
	uint32_t whole32[];
	uint8_t buff[RAWHID_TX_SIZE];
} HID_RawKeyboardTXReport_Data_t;

typedef union{
	// a RAWHID_TX_SIZE byte buffer for rx
	uint8_t whole8[];
	uint16_t whole16[];
	uint32_t whole32[];
	uint8_t buff[RAWHID_RX_SIZE];
} HID_RawKeyboardRXReport_Data_t;

class RawHID_ : public Stream, private HIDDevice
{
public:
	RawHID_(void) :
	HIDDevice((uint8_t*)_rawhidReportDescriptor, sizeof(_rawhidReportDescriptor), HID_REPORTID_RAWHID),
	dataLength(0)
	{
		// HID Descriptor is appended via the inherited HIDDevice class
	}

	void begin(void){
		// empty
	}

	void end(void){
		// empty
	}
	
	virtual int available(void){
		return dataLength;
	}
	
	virtual int read(){
		if(dataLength){
			// Get next data byte
			uint8_t data = *(dataTail - dataLength);
			dataLength--;
			
			// Release buffer if its read fully
			if(!dataLength){
				free(dataHead);
			}

			return data;
		}
		return -1;
	}
	
	virtual int peek(){
		if(dataLength){
			return *(dataTail - dataLength);
		}
		return -1;
	}
	
	virtual void flush(void){
		// Delete all incoming bytes
		if(dataLength){
			free(dataHead);
			dataLength = 0;
		}
	}

	using Print::write;
	virtual size_t write(uint8_t b){
		return write(&b, 1);
	}

	virtual size_t write(const uint8_t *buffer, size_t size){
		// TODO this only sends the report ID in the first packat
		// TODO this will split the data into USB_EP_SIZE packets
		SendReport(buffer, size);
		return size;
	
		size_t bytesleft = size;
		// First work through the buffer thats already there
		while (bytesleft >= RAWHID_TX_SIZE){
			SendReport(&buffer[size - bytesleft], RAWHID_TX_SIZE);
			bytesleft -= RAWHID_TX_SIZE;
		}
		
		// Write down the leftover bytes and fill with zeros
		if (bytesleft){
			SendReport(&buffer[size - bytesleft], bytesleft);
		}
		
		return size;
	}
	
private:
	virtual void setReportData(void* &data, int len){
		// Only overwrite the buffer if its empty.
		// This avoids corrupted data while reading.
		if(!dataLength){
			// Save new data
			dataLength = len;
			dataHead = (uint8_t*) data;
			dataTail = (uint8_t*)(data) + len;
						
			// Clear the passed in pointer to not free the data
			data = NULL;
		}
	}
	
	// Buffer pointers to hold the received data
	int dataLength;
	uint8_t* dataHead;
	uint8_t* dataTail;
};
extern RawHID_ RawHID;

#endif
