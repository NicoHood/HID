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
*  Header file for Descriptors.c.
*/

#ifndef _DESCRIPTORS_H_
#define _DESCRIPTORS_H_

/* Includes: */
#include <avr/pgmspace.h>
#include <LUFA/Drivers/USB/USB.h>
#include <../HID_Source/HID_Reports.h>

/* Macros: */
/** Endpoint address of the CDC device-to-host notification IN endpoint. */
#define CDC_NOTIFICATION_EPADDR        (ENDPOINT_DIR_IN  | 2)

/** Endpoint address of the CDC device-to-host data IN endpoint. */
#define CDC_TX_EPADDR                  (ENDPOINT_DIR_IN  | 3)

/** Endpoint address of the CDC host-to-device data OUT endpoint. */
#define CDC_RX_EPADDR                  (ENDPOINT_DIR_OUT | 4)

/** Size in bytes of the CDC device-to-host notification IN endpoint. */
#define CDC_NOTIFICATION_EPSIZE        8

/** Size in bytes of the CDC data IN and OUT endpoints. */
#define CDC_TXRX_EPSIZE                64 //<--new


/** Endpoint address of the HID reporting IN endpoint. */
#define HID_IN_EPADDR				 (ENDPOINT_DIR_IN | 1)

/** Size in bytes of each of the HID reporting IN endpoint. */
// important: only use 8,16,32,64 here!! <--
#define HID_EPSIZE					32


/* Type Defines: */
/** Type define for the device configuration descriptor structure. This must be defined in the
*  application code, as the configuration descriptor contains several sub-descriptors which
*  vary between devices, and which describe the device's usage to the host.
*/
typedef struct
{
	USB_Descriptor_Configuration_Header_t    Config;

	// CDC Control Interface
	USB_Descriptor_Interface_Association_t   CDC_IAD; //<--new
	USB_Descriptor_Interface_t               CDC_CCI_Interface;
	USB_CDC_Descriptor_FunctionalHeader_t    CDC_Functional_Header;
	USB_CDC_Descriptor_FunctionalACM_t       CDC_Functional_ACM;
	USB_CDC_Descriptor_FunctionalUnion_t     CDC_Functional_Union;
	USB_Descriptor_Endpoint_t                CDC_NotificationEndpoint;

	// CDC Data Interface
	USB_Descriptor_Interface_t               CDC_DCI_Interface;
	USB_Descriptor_Endpoint_t                CDC_DataOutEndpoint;
	USB_Descriptor_Endpoint_t                CDC_DataInEndpoint;

	// HID Interface
	USB_Descriptor_Interface_t               HID_Interface;
	USB_HID_Descriptor_HID_t				 HID_HIDData;
	USB_Descriptor_Endpoint_t                HID_ReportINEndpoint;

} USB_Descriptor_Configuration_t;

/* Enums: */

/** Enum for the device interface descriptor IDs within the device. Each interface descriptor
*  should have a unique ID index associated with it, which can be used to refer to the
*  interface from other descriptors.
*/
enum InterfaceDescriptors_t
{
	INTERFACE_ID_CDC_CCI = 0, /**< CDC CCI interface descriptor ID */
	INTERFACE_ID_CDC_DCI = 1, /**< CDC DCI interface descriptor ID */
	INTERFACE_ID_HID	 = 2, /**< HID interface descriptor ID */
};

/** Enum for the device string descriptor IDs within the device. Each string descriptor should
*  have a unique ID index associated with it, which can be used to refer to the string from
*  other descriptors.
*/
enum StringDescriptors_t
{
	STRING_ID_Language     = 0, /**< Supported Languages string descriptor ID (must be zero) */
	STRING_ID_Manufacturer = 1, /**< Manufacturer string ID */
	STRING_ID_Product      = 2, /**< Product string ID */
};

/* Function Prototypes: */
uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue,
									const uint8_t wIndex,
									const void** const DescriptorAddress)
									ATTR_WARN_UNUSED_RESULT ATTR_NON_NULL_PTR_ARG(3);

#endif
