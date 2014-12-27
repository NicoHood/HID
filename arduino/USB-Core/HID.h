/*
HID.h
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

#ifndef __HID__
#define __HID__

#include "Arduino.h"

// enable Led out report by default
#ifndef EXTERN_HID_REPORT
#define HID_KEYBOARD_LEDS_ENABLED
#endif

// HID report IDs
// note by NicoHood: I would not change the current IDs, since it can confuse the OS
// I had several problems if i change the report id and its use.
// It doesnt matter if a device is not presented and there is a lack of IDs (at least number 1 must be represented)
// Report IDs and the report itself can be overwritten by the pins_arduino.h
#ifndef HID_REPORTID_MOUSE
#define HID_REPORTID_MOUSE 1
#endif
#ifndef HID_REPORTID_KEYBOARD
#define HID_REPORTID_KEYBOARD 2
#endif
#ifndef HID_REPORTID_RAWHID
#define HID_REPORTID_RAWHID 3
#endif
#ifndef HID_REPORTID_CONSUMERCONTROL
#define HID_REPORTID_CONSUMERCONTROL 4
#endif
#ifndef HID_REPORTID_SYSTEMCONTROL
#define HID_REPORTID_SYSTEMCONTROL 5
#endif
#ifndef HID_REPORTID_GAMEPAD
#define HID_REPORTID_GAMEPAD 6
#endif
#ifndef HID_REPORTID_MOUSE_ABSOLUTE
#define HID_REPORTID_MOUSE_ABSOLUTE 7
#endif

// HID reports
// Report IDs and the report itself can be overwritten by the pins_arduino.h


#ifndef HID_REPORT_MOUSE
#define HID_REPORT_MOUSE(report_id) /*  Mouse relative */ \
    0x05, 0x01,                      /* USAGE_PAGE (Generic Desktop)	  54 */ \
    0x09, 0x02,                      /* USAGE (Mouse) */ \
    0xa1, 0x01,                      /* COLLECTION (Application) */ \
    0x85, report_id,				/*     REPORT_ID */ \
\
	/* 8 Buttons */ \
    0x05, 0x09,                      /*     USAGE_PAGE (Button) */ \
    0x19, 0x01,                      /*     USAGE_MINIMUM (Button 1) */ \
    0x29, 0x08,                      /*     USAGE_MAXIMUM (Button 8) */ \
    0x15, 0x00,                      /*     LOGICAL_MINIMUM (0) */ \
    0x25, 0x01,                      /*     LOGICAL_MAXIMUM (1) */ \
    0x95, 0x08,                      /*     REPORT_COUNT (8) */ \
    0x75, 0x01,                      /*     REPORT_SIZE (1) */ \
    0x81, 0x02,                      /*     INPUT (Data,Var,Abs) */ \
\
	/* X, Y, Wheel */ \
    0x05, 0x01,                      /*     USAGE_PAGE (Generic Desktop) */ \
    0x09, 0x30,                      /*     USAGE (X) */ \
    0x09, 0x31,                      /*     USAGE (Y) */ \
    0x09, 0x38,                      /*     USAGE (Wheel) */ \
    0x15, 0x81,                      /*     LOGICAL_MINIMUM (-127) */ \
    0x25, 0x7f,                      /*     LOGICAL_MAXIMUM (127) */ \
    0x75, 0x08,                      /*     REPORT_SIZE (8) */ \
    0x95, 0x03,                      /*     REPORT_COUNT (3) */ \
    0x81, 0x06,                      /*     INPUT (Data,Var,Rel) */ \
\
	/* End */ \
    0xc0                            /* END_COLLECTION */ 
#endif

#ifndef HID_REPORT_MOUSE_ABSOLUTE
#define HID_REPORT_MOUSE_ABSOLUTE(report_id) /*  Mouse absolute */ \
	0x05, 0x01,							/* Usage Page (Generic Desktop) */ \
	0x09, 0x02,							/* Usage (Mouse) */ \
	0xA1, 0x01,							/* Collection (Application) */ \
	0x85, report_id,					/* REPORT_ID */ \
	0x05, 0x01,							/* Usage Page (Generic Desktop) */ \
	0x09, 0x30,							/* Usage (X) */ \
	0x09, 0x31,							/* Usage (Y) */ \
	0x15, 0x00,							/* Logical Minimum (0) */ \
	0x26, 0xFF, 0x7F,					/* Logical Maximum (32767) */ \
	0x75, 0x10,							/* Report Size (16), */ \
	0x95, 0x02,							/* Report Count (2), */ \
	0x81, 0x02,							/* Input (Data, Variable, Absolute) */ \
	0xC0								/* End Collection */
#endif

#ifndef HID_REPORT_KEYBOARD_LEDS
#define HID_REPORT_KEYBOARD_LEDS(report_id)    /*  Keyboard */ \
    0x05, 0x01,                      /* USAGE_PAGE (Generic Desktop)	  47 */ \
    0x09, 0x06,                      /* USAGE (Keyboard) */ \
    0xa1, 0x01,                      /* COLLECTION (Application) */ \
    0x85, report_id,				 /*   REPORT_ID */ \
    0x05, 0x07,                      /*   USAGE_PAGE (Keyboard) */ \
\
      /* Keyboard Modifiers (shift, alt, ...) */ \
    0x19, 0xe0,                      /*   USAGE_MINIMUM (Keyboard LeftControl) */ \
    0x29, 0xe7,                      /*   USAGE_MAXIMUM (Keyboard Right GUI) */ \
    0x15, 0x00,                      /*   LOGICAL_MINIMUM (0) */ \
    0x25, 0x01,                      /*   LOGICAL_MAXIMUM (1) */ \
    0x75, 0x01,                      /*   REPORT_SIZE (1) */ \
	0x95, 0x08,                      /*   REPORT_COUNT (8) */ \
    0x81, 0x02,                      /*   INPUT (Data,Var,Abs) */ \
\
      /* Reserved byte */ \
    0x95, 0x01,                      /*   REPORT_COUNT (1) */ \
    0x75, 0x08,                      /*   REPORT_SIZE (8) */ \
    0x81, 0x03,                      /*   INPUT (Cnst,Var,Abs) */ \
\
	/* 5 LEDs for num lock etc */ \
	0x05, 0x08,						 /*   USAGE_PAGE (LEDs) */ \
	0x19, 0x01,						 /*   USAGE_MINIMUM (Num Lock) */ \
	0x29, 0x05,						 /*   USAGE_MAXIMUM (Kana) */ \
	0x95, 0x05,						 /*   REPORT_COUNT (5) */ \
	0x75, 0x01,						 /*   REPORT_SIZE (1) */ \
	0x91, 0x02,						 /*   OUTPUT (Data,Var,Abs) */ \
	/*  Reserved 3 bits */ \
	0x95, 0x01,						 /*   REPORT_COUNT (1) */ \
	0x75, 0x03,						 /*   REPORT_SIZE (3) */ \
	0x91, 0x03,						 /*   OUTPUT (Cnst,Var,Abs) */ \
\
      /* 6 Keyboard keys */ \
    0x95, 0x06,                      /*   REPORT_COUNT (6) */ \
    0x75, 0x08,                      /*   REPORT_SIZE (8) */ \
    0x15, 0x00,                      /*   LOGICAL_MINIMUM (0) */ \
    0x26, 0xE7, 0x00,                /*   LOGICAL_MAXIMUM (231) */ \
    0x05, 0x07,                      /*   USAGE_PAGE (Keyboard) */ \
    0x19, 0x00,                      /*   USAGE_MINIMUM (Reserved (no event indicated)) */ \
    0x29, 0xE7,                      /*   USAGE_MAXIMUM (Keyboard Right GUI) */ \
    0x81, 0x00,                      /*   INPUT (Data,Ary,Abs) */ \
\
      /* End */ \
    0xc0                            /* END_COLLECTION */
#endif

#ifndef HID_REPORT_KEYBOARD_KEYS
#define HID_REPORT_KEYBOARD_KEYS(report_id)    /*  Keyboard */ \
    0x05, 0x01,                      /* USAGE_PAGE (Generic Desktop)	  47 */ \
    0x09, 0x06,                      /* USAGE (Keyboard) */ \
    0xa1, 0x01,                      /* COLLECTION (Application) */ \
    0x85, report_id,				 /*   REPORT_ID */ \
    0x05, 0x07,                      /*   USAGE_PAGE (Keyboard) */ \
\
      /* Keyboard Modifiers (shift, alt, ...) */ \
    0x19, 0xe0,                      /*   USAGE_MINIMUM (Keyboard LeftControl) */ \
    0x29, 0xe7,                      /*   USAGE_MAXIMUM (Keyboard Right GUI) */ \
    0x15, 0x00,                      /*   LOGICAL_MINIMUM (0) */ \
    0x25, 0x01,                      /*   LOGICAL_MAXIMUM (1) */ \
    0x75, 0x01,                      /*   REPORT_SIZE (1) */ \
	0x95, 0x08,                      /*   REPORT_COUNT (8) */ \
    0x81, 0x02,                      /*   INPUT (Data,Var,Abs) */ \
\
      /* Reserved byte */ \
    0x95, 0x01,                      /*   REPORT_COUNT (1) */ \
    0x75, 0x08,                      /*   REPORT_SIZE (8) */ \
    0x81, 0x03,                      /*   INPUT (Cnst,Var,Abs) */ \
\
	HID_REPORT_KEYBOARD_LEDS \
      /* 6 Keyboard keys */ \
    0x95, 0x06,                      /*   REPORT_COUNT (6) */ \
    0x75, 0x08,                      /*   REPORT_SIZE (8) */ \
    0x15, 0x00,                      /*   LOGICAL_MINIMUM (0) */ \
    0x26, 0xE7, 0x00,                /*   LOGICAL_MAXIMUM (231) */ \
    0x05, 0x07,                      /*   USAGE_PAGE (Keyboard) */ \
    0x19, 0x00,                      /*   USAGE_MINIMUM (Reserved (no event indicated)) */ \
    0x29, 0xE7,                      /*   USAGE_MAXIMUM (Keyboard Right GUI) */ \
    0x81, 0x00,                      /*   INPUT (Data,Ary,Abs) */ \
\
      /* End */ \
    0xc0                            /* END_COLLECTION */
#endif

//TODO limit to system keys only?
#ifndef HID_REPORT_SYSTEMCONTROL
#define HID_REPORT_SYSTEMCONTROL(report_id) /*  System Control (Power Down, Sleep, Wakeup, ...) */ \
	0x05, 0x01,								/* USAGE_PAGE (Generic Desktop) */ \
	0x09, 0x80,								/* USAGE (System Control) */ \
	0xa1, 0x01, 							/* COLLECTION (Application) */ \
	0x85, report_id,						/* REPORT_ID */ \
	/* 1 system key */ \
	0x15, 0x00, 							/* LOGICAL_MINIMUM (0) */ \
	0x26, 0xff, 0x00, 						/* LOGICAL_MAXIMUM (255) */ \
	0x19, 0x00, 							/* USAGE_MINIMUM (Undefined) */ \
	0x29, 0xff, 							/* USAGE_MAXIMUM (System Menu Down) */ \
	0x95, 0x01, 							/* REPORT_COUNT (1) */ \
	0x75, 0x08, 							/* REPORT_SIZE (8) */ \
	0x81, 0x00, 							/* INPUT (Data,Ary,Abs) */ \
	0xc0 									/* END_COLLECTION */
#endif

#ifndef HID_REPORT_CONSUMERCONTROL
#define HID_REPORT_CONSUMERCONTROL(report_id)	/* Consumer Control (Sound/Media keys) */ \
	0x05, 0x0C,									/* usage page (consumer device) */ \
	0x09, 0x01, 								/* usage -- consumer control */ \
	0xA1, 0x01, 								/* collection (application) */ \
	0x85, report_id, 							/* report id */ \
	/* 4 Media Keys */ \
	0x15, 0x00, 								/* logical minimum */ \
	0x26, 0xFF, 0x03, 							/* logical maximum (3ff) */ \
	0x19, 0x00, 								/* usage minimum (0) */ \
	0x2A, 0xFF, 0x03, 							/* usage maximum (3ff) */ \
	0x95, 0x04, 								/* report count (4) */ \
	0x75, 0x10, 								/* report size (16) */ \
	0x81, 0x00, 								/* input */ \
	0xC0 /* end collection */
#endif

#ifndef HID_REPORT_GAMEPAD
#define HID_REPORT_GAMEPAD(report_id) /* Gamepad with 32 buttons and 6 axis*/ \
	0x05, 0x01,							/* USAGE_PAGE (Generic Desktop) */ \
	0x09, 0x04,							/* USAGE (Joystick) */ \
	0xa1, 0x01,							/* COLLECTION (Application) */ \
	0x85, HID_REPORTID_GAMEPAD,	/*   REPORT_ID */ \
	/* 32 Buttons */ \
	0x05, 0x09,							/*   USAGE_PAGE (Button) */ \
	0x19, 0x01,							/*   USAGE_MINIMUM (Button 1) */ \
	0x29, 0x20,							/*   USAGE_MAXIMUM (Button 32) */ \
	0x15, 0x00,							/*   LOGICAL_MINIMUM (0) */ \
	0x25, 0x01,							/*   LOGICAL_MAXIMUM (1) */ \
	0x75, 0x01,							/*   REPORT_SIZE (1) */ \
	0x95, 0x20,							/*   REPORT_COUNT (32) */ \
	0x81, 0x02,							/*   INPUT (Data,Var,Abs) */ \
	/* 4 16bit Axis */ \
	0x05, 0x01,							/*   USAGE_PAGE (Generic Desktop) */ \
	0xa1, 0x00,							/*   COLLECTION (Physical) */ \
	0x09, 0x30,							/*     USAGE (X) */ \
	0x09, 0x31,							/*     USAGE (Y) */ \
	0x09, 0x33,							/*     USAGE (Rx) */ \
	0x09, 0x34,							/*     USAGE (Ry) */ \
	0x16, 0x00, 0x80,					/*     LOGICAL_MINIMUM (-32768) */ \
	0x26, 0xFF, 0x7F,					/*     LOGICAL_MAXIMUM (32767) */ \
	0x75, 0x10,							/*     REPORT_SIZE (16) */ \
	0x95, 0x04,							/*     REPORT_COUNT (4) */ \
	0x81, 0x02,							/*     INPUT (Data,Var,Abs) */ \
	/* 2 8bit Axis */ \
	0x09, 0x32,							/*     USAGE (Z) */ \
	0x09, 0x35,							/*     USAGE (Rz) */ \
	0x15, 0x80,							/*     LOGICAL_MINIMUM (-128) */ \
	0x25, 0x7F,							/*     LOGICAL_MAXIMUM (127) */ \
	0x75, 0x08,							/*     REPORT_SIZE (8) */ \
	0x95, 0x02,							/*     REPORT_COUNT (2) */ \
	0x81, 0x02,							/*     INPUT (Data,Var,Abs) */ \
	0xc0,								/*   END_COLLECTION */ \
	/* 2 Hat Switches */ \
	0x05, 0x01,							/*   USAGE_PAGE (Generic Desktop) */ \
	0x09, 0x39,							/*   USAGE (Hat switch) */ \
	0x09, 0x39,							/*   USAGE (Hat switch) */ \
	0x15, 0x01,							/*   LOGICAL_MINIMUM (1) */ \
	0x25, 0x08,							/*   LOGICAL_MAXIMUM (8) */ \
	0x95, 0x02,							/*   REPORT_COUNT (2) */ \
	0x75, 0x04,							/*   REPORT_SIZE (4) */ \
	0x81, 0x02,							/*   INPUT (Data,Var,Abs) */ \
	0xc0								/* END_COLLECTION */
#endif

// note by NicoHood: RawHID might never work with multireports, because of OS problems
// therefore we have to make it a single report with no idea. No other HID device will be supported then.
#define RAWHID_USAGE_PAGE	0xFFC0 // recommended: 0xFF00 to 0xFFFF
#define RAWHID_USAGE		0x0C00 // recommended: 0x0100 to 0xFFFF
#define RAWHID_TX_SIZE (USB_EP_SIZE-1)
#define RAWHID_RX_SIZE (USB_EP_SIZE-1)

#define LSB(_x) ((_x) & 0xFF)
#define MSB(_x) ((_x) >> 8)

#ifndef HID_REPORT_RAWHID
#define HID_REPORT_RAWHID(report_id) /*    RAW HID */ \
    0x06, LSB(RAWHID_USAGE_PAGE), MSB(RAWHID_USAGE_PAGE),      /* 30 */ \
    0x0A, LSB(RAWHID_USAGE), MSB(RAWHID_USAGE), \
\
    0xA1, 0x01,                  /* Collection 0x01 */ \
    0x85, report_id,			 /* REPORT_ID */ \
    0x75, 0x08,                  /* report size = 8 bits */ \
    0x15, 0x00,                  /* logical minimum = 0 */ \
    0x26, 0xFF, 0x00,            /* logical maximum = 255 */ \
\
    0x95, RAWHID_TX_SIZE,        /* report count TX */ \
    0x09, 0x01,                  /* usage */ \
    0x81, 0x02,                  /* Input (array) */ \
\
    0x95, RAWHID_RX_SIZE,        /* report count RX */ \
    0x09, 0x02,                  /* usage */ \
    0x91, 0x02,                  /* Output (array) */ \
    0xC0                         /* end collection */ 
#endif

#if defined(USBCON)

#include "USBDesc.h"
#include "USBCore.h"
// only include HIDAPI if we have an USB AVR MCU.
// The use can overwrite HID_SendReport() and manually include the APIs.
#include "HIDAPI.h"

//================================================================================
//================================================================================
//	HID 'Driver'

int		HID_GetInterface(uint8_t* interfaceNum);
int		HID_GetDescriptor(int i);
bool	HID_Setup(Setup& setup);
void	HID_SendReport(uint8_t id, const void* data, int len);
#if defined(HID_KEYBOARD_LEDS_ENABLED)
void	HID_SetKeyboardLedReport(uint8_t leds);
#endif

#else /* if defined(USBCON) */

// (weak) function prototype to let the user use the HIDAPI for different use
// if he include the api himself
void	HID_SendReport(uint8_t id, const void* data, int len);

#endif /* if defined(USBCON) */

#endif