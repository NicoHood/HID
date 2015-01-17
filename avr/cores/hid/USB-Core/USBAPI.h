/*
  USBAPI.h
  Copyright (c) 2005-2014 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
  */

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

#ifndef __USBAPI__
#define __USBAPI__

#include <inttypes.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include <avr/interrupt.h>
#include <util/delay.h>

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

#include "Arduino.h"

// edit by NicoHood
// this definitions is usefull if you want to reduce the EP_SIZE to 16
// at the moment only 64 and 16 as EP_SIZE for all EPs are supported except the control endpoint
#ifndef USB_EP_SIZE
#define USB_EP_SIZE 64
#endif

#if defined(USBCON)

#include "USBDesc.h"
#include "USBCore.h"

//================================================================================
//================================================================================
//	USB

class USBDevice_
{
public:
	USBDevice_();
	bool configured();

	void attach();
	void detach();	// Serial port goes down too...
	void poll();
	bool wakeupHost(); // returns false, when wakeup cannot be processed
};
extern USBDevice_ USBDevice;

//================================================================================
//================================================================================
//	MSC 'Driver'

int		MSC_GetInterface(uint8_t* interfaceNum);
int		MSC_GetDescriptor(int i);
bool	MSC_Setup(Setup& setup);
bool	MSC_Data(uint8_t rx, uint8_t tx);

//================================================================================
//================================================================================
//	CSC 'Driver'

int		CDC_GetInterface(uint8_t* interfaceNum);
int		CDC_GetDescriptor(int i);
bool	CDC_Setup(Setup& setup);
void	CDC_LineEncodingEvent(void);
void	CDC_LineStateEvent(void);

//================================================================================
//================================================================================

#define TRANSFER_PGM		0x80
#define TRANSFER_RELEASE	0x40
#define TRANSFER_ZERO		0x20

int USB_SendControl(uint8_t flags, const void* d, int len);
int USB_RecvControl(void* d, int len);

uint8_t	USB_Available(uint8_t ep);
int USB_Send(uint8_t ep, const void* data, int len);	// blocking
int USB_Recv(uint8_t ep, void* data, int len);		// non-blocking
int USB_Recv(uint8_t ep);							// non-blocking
void USB_Flush(uint8_t ep);

#endif

#endif /* if defined(USBCON) */
