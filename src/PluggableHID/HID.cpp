/* Copyright (c) 2015, Arduino LLC
**
** Original code (pre-library): Copyright (c) 2011, Peter Barrett
**
** Permission to use, copy, modify, and/or distribute this software for  
** any purpose with or without fee is hereby granted, provided that the  
** above copyright notice and this permission notice appear in all copies.  
** 
** THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL  
** WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED  
** WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR  
** BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES  
** OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,  
** WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,  
** ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS  
** SOFTWARE.  
*/

#include "PluggableUSB.h"
#include "HID.h"
#include "HIDDevice.h"
#include "HID-Project.h" // Only used for the BootKeyboard setting

#if defined(USBCON)

HID_ HID;

//================================================================================
//================================================================================

//	HID report descriptor

#define LSB(_x) ((_x) & 0xFF)
#define MSB(_x) ((_x) >> 8)

#define RAWHID_USAGE_PAGE	0xFFC0
#define RAWHID_USAGE		0x0C00
#define RAWHID_TX_SIZE 64
#define RAWHID_RX_SIZE 64

// Static variables
uint8_t HID_::HID_ENDPOINT_INT;
uint8_t HID_::HID_INTERFACE;
HIDDescriptor HID_::_hidInterface;
HIDDevice* HID_::rootDevice = NULL;
uint16_t HID_::sizeof_hidReportDescriptor = 0;
uint8_t HID_::modules_count = 0;
uint8_t HID_::_hid_protocol = 1;
uint8_t HID_::_hid_idle = 1;

//================================================================================
//================================================================================
//	Driver

int HID_::HID_GetInterface(u8* interfaceNum)
{
	interfaceNum[0] += 1;	// uses 1
	_hidInterface =
	{
#if defined(USE_BOOT_KEYBOARD_PROTOCOL)
		D_INTERFACE(HID_INTERFACE,1,3,1,1),
#elif defined(USE_BOOT_MOUSE_PROTOCOL)
		D_INTERFACE(HID_INTERFACE,1,3,1,2),
#else
		D_INTERFACE(HID_INTERFACE,1,3,0,0),
#endif
		D_HIDREPORT(sizeof_hidReportDescriptor),
		D_ENDPOINT(USB_ENDPOINT_IN (HID_ENDPOINT_INT),USB_ENDPOINT_TYPE_INTERRUPT,USB_EP_SIZE,0x01)
	};
	return USB_SendControl(0,&_hidInterface,sizeof(_hidInterface));
}

int HID_::HID_GetDescriptor(int8_t t)
{
	if (HID_REPORT_DESCRIPTOR_TYPE == t) {
		HIDDevice* current = rootDevice;
		int total = 0;
		while(current != NULL) {
			total += USB_SendControl(TRANSFER_PGM,current->descriptorData,current->descriptorLength);
			current = current->next;
		}
		return total;
	} else {
		return 0;
	}
}

void HID_::AppendDescriptor(HIDDevice *device)
{
	if (modules_count == 0) {
		rootDevice = device;
	} else {
		HIDDevice *current = rootDevice;
		while(current->next != NULL) {
			current = current->next;
		}
		current->next = device;
	}
	modules_count++;
	sizeof_hidReportDescriptor += (uint16_t)device->descriptorLength;
}

void HID_::SendReport(u8 id, const void* data, int len)
{
	// Only send report ID if it exists
	if(id){
#if defined(USE_BOOT_KEYBOARD_PROTOCOL) || defined(USE_BOOT_MOUSE_PROTOCOL)
		// Do not send a normal report while in Bootloader mode.
		if(_hid_protocol != 1){
			return;
		}
#endif
		USB_Send(HID_TX, &id, 1);
	}
	// Non reportID reports (rawHID) will still try to send data.
	// If this happens at PC boot this can cause wrong keypresses.
	// Normally any data > 8 byte should be ignored due to the USB specs.
	// To avoid this, use the getProtocol() function of the HIDDevice
	// inside the rawHID etc or disable the boot protocol.
	USB_Send(HID_TX | TRANSFER_RELEASE,data,len);
}

bool HID_::HID_Setup(USBSetup& setup, u8 i)
{
	if (HID_INTERFACE != i) {
		return false;
	} else {
		u8 r = setup.bRequest;
		u8 requestType = setup.bmRequestType;
		if (REQUEST_DEVICETOHOST_CLASS_INTERFACE == requestType)
		{
			if (HID_GET_REPORT == r)
			{
			//HID_GetReport();
				return true;
			}
			if (HID_GET_PROTOCOL == r)
			{
			//Send8(_hid_protocol);	// TODO
				return true;
			}
		}
		
		if (REQUEST_HOSTTODEVICE_CLASS_INTERFACE == requestType)
		{
			if (HID_SET_PROTOCOL == r)
			{
				_hid_protocol = setup.wValueL;
				return true;
			}

			if (HID_SET_IDLE == r)
			{
				_hid_idle = setup.wValueL;
				return true;
			}
			
			if (HID_SET_REPORT == r)
			{
				// Get reportID and search for the suited HIDDevice
				uint8_t ID = setup.wValueL;
				HIDDevice *current = rootDevice;

				while(current != NULL) 
				{
					// Search HIDDevice for report ID
					if(current->reportID == ID)
					{
						// Get the data length information and the corresponding bytes
						uint16_t length = (setup.wValueH << 8) | setup.wLength;

						// Ensure that there IS some data TODO needed?
						if(length)
						{
							void* data = malloc(length);
							if(data){
								uint16_t recvLength = length;
								//TODO loop can be improved maybe? Or does the compiler do this already?
								while(recvLength > USB_EP_SIZE){
									USB_RecvControl(data + (length - recvLength), USB_EP_SIZE);
									recvLength -= USB_EP_SIZE;
								}
								USB_RecvControl(data + (length - recvLength), recvLength);

								// Data may contain the report ID again (Keyboard), maybe not (RawHID)
								current->setReportData(data, length);
							}

							// Release data if the pointer still exists
							free(data);
						}

						// Dont search any further
						break;
					}
					current = current->next;
				}
			}
		}
		return false;
	}
}

HID_::HID_(void)
{
	static uint8_t endpointType[1];

	endpointType[0] = EP_TYPE_INTERRUPT_IN;

	static PUSBCallbacks cb = {
		.setup = HID_Setup,
		.getInterface = &HID_GetInterface,
		.getDescriptor = &HID_GetDescriptor,
		.numEndpoints = 1,
		.numInterfaces = 1,
		.endpointType = endpointType,
	};

	static PUSBListNode node(&cb);

	HID_ENDPOINT_INT = PUSB_AddFunction(&node, &HID_INTERFACE);
}

HID_::operator bool() {
	if(USBDevice.configured()){
		delay(10);
		return true;
	}
	else{
		return false;
	}
}

int HID_::begin(void)
{
}

#endif /* if defined(USBCON) */

