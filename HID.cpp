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

#include "HID.h"

//================================================================================
// HID Leonardo/Micro
//================================================================================

#if defined(USBCON)

HID_ HID;

HID_::HID_(void){
	// empty
}

void HID_::begin(void){
	// empty
}

void HID_::end(void){
	// empty
}

void HID_::sendReport(uint8_t ReportID, const void* HIDReport, uint8_t length){
	HID_SendReport(ReportID, HIDReport, length);
}


#ifdef HID_ENABLED

//================================================================================
//================================================================================

//	HID report descriptor

#define LSB(_x) ((_x) & 0xFF)
#define MSB(_x) ((_x) >> 8)

#define RAWHID_USAGE_PAGE	0xFFC0
#define RAWHID_USAGE		0x0C00
#define RAWHID_TX_SIZE 64
#define RAWHID_RX_SIZE 64

extern const u8 _hidReportDescriptor[] PROGMEM;
const u8 _hidReportDescriptor[] = {

#ifdef HID_MOUSE_ENABLE
	// Mouse
	0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)	// 54
	0x09, 0x02,                    // USAGE (Mouse)
	0xa1, 0x01,                    // COLLECTION (Application)
	0x09, 0x01,                    //   USAGE (Pointer)
	0xa1, 0x00,                    //   COLLECTION (Physical)
	0x85, HID_REPORTID_MouseReport,//     REPORT_ID
	// 5 buttons
	0x05, 0x09,                    //     USAGE_PAGE (Button)
	0x19, 0x01,                    //     USAGE_MINIMUM (Button 1)
	0x29, 0x05,                    //     USAGE_MAXIMUM (Button 5)
	0x15, 0x00,                    //     LOGICAL_MINIMUM (0)
	0x25, 0x01,                    //     LOGICAL_MAXIMUM (1)
	0x95, 0x05,                    //     REPORT_COUNT (5)
	0x75, 0x01,                    //     REPORT_SIZE (1)
	0x81, 0x02,                    //     INPUT (Data,Var,Abs)
	// reserved
	0x95, 0x01,                    //     REPORT_COUNT (1)
	0x75, 0x03,                    //     REPORT_SIZE (3)
	0x81, 0x03,                    //     INPUT (Cnst,Var,Abs)
	// x, y, wheel
	0x05, 0x01,                    //     USAGE_PAGE (Generic Desktop)
	0x09, 0x30,                    //     USAGE (X)
	0x09, 0x31,                    //     USAGE (Y)
	0x09, 0x38,                    //     USAGE (Wheel)
	0x15, 0x81,                    //     LOGICAL_MINIMUM (-127)
	0x25, 0x7f,                    //     LOGICAL_MAXIMUM (127)
	0x75, 0x08,                    //     REPORT_SIZE (8)
	0x95, 0x03,                    //     REPORT_COUNT (3)
	0x81, 0x06,                    //     INPUT (Data,Var,Rel)
	// end
	0xc0,                          //   END_COLLECTION
	0xc0,                          // END_COLLECTION
#endif

#ifdef HID_KEYBOARD_ENABLE
	// Keyboard
	0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
	0x09, 0x06,                    // USAGE (Keyboard)
	0xa1, 0x01,                    // COLLECTION (Application)
	0x85, HID_REPORTID_KeyboardReport, //   REPORT_ID
	0x05, 0x07,                    //   USAGE_PAGE (Keyboard)
	// modifiers
	0x19, 0xe0,                    //   USAGE_MINIMUM (Keyboard LeftControl)
	0x29, 0xe7,                    //   USAGE_MAXIMUM (Keyboard Right GUI)
	0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
	0x25, 0x01,                    //   LOGICAL_MAXIMUM (1)
	0x75, 0x01,                    //   REPORT_SIZE (1)
	0x95, 0x08,                    //   REPORT_COUNT (8)
	0x81, 0x02,                    //   INPUT (Data,Var,Abs)
	// reserved byte
	0x95, 0x01,                    //   REPORT_COUNT (1)
	0x75, 0x08,                    //   REPORT_SIZE (8)
	0x81, 0x03,                    //   INPUT (Cnst,Var,Abs)
	// Key[6] Array
	0x95, 0x06,                    //   REPORT_COUNT (6)
	0x75, 0x08,                    //   REPORT_SIZE (8)
	0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
	0x25, 0x65,                    //   LOGICAL_MAXIMUM (101)
	0x05, 0x07,                    //   USAGE_PAGE (Keyboard)
	0x19, 0x00,                    //   USAGE_MINIMUM (Reserved (no event indicated))
	0x29, 0x65,                    //   USAGE_MAXIMUM (Keyboard Application)
	0x81, 0x00,                    //   INPUT (Data,Ary,Abs)
	// LEDs for num lock etc
	0x05, 0x08,   /*   USAGE_PAGE (LEDs) */
	0x19, 0x01,   /*   USAGE_MINIMUM (Num Lock) */
	0x29, 0x05,   /*   USAGE_MAXIMUM (Kana) */
	0x95, 0x05,   /*   REPORT_COUNT (5) */
	0x75, 0x01,   /*   REPORT_SIZE (1) */
	0x91, 0x02,   /*   OUTPUT (Data,Var,Abs) */
	// Reserved 3 bits
	0x95, 0x01,   /*   REPORT_COUNT (1) */
	0x75, 0x03,   /*   REPORT_SIZE (3) */
	0x91, 0x03,   /*   OUTPUT (Cnst,Var,Abs) */
	// end
	0xc0,                          // END_COLLECTION
#endif

#ifdef HID_RAWKEYBOARD_ENABLE
	// RAW HID
	0x06, 0xC0, 0xFF,
	0x0A, 0x00, 0x0C,

	0xA1, 0x01,								// Collection 0x01
	0x85, HID_REPORTID_RawKeyboardReport,	// REPORT_ID
	0x75, 0x08,								// report size = 8 bits
	0x15, 0x00,								// logical minimum = 0
	0x26, 0xFF, 0x00,						// logical maximum = 255

	0x95, 64,								// report count TX
	0x09, 0x01,								// usage
	0x81, 0x02,								// Input (array)

	0x95, 64,								// report count RX
	0x09, 0x02,								// usage
	0x91, 0x02,								// Output (array)
	0xC0,									// end collection
#endif

#ifdef HID_MEDIA_ENABLE
	// Media
	0x05, 0x0C,						// usage page (consumer device)
	0x09, 0x01,						// usage -- consumer control
	0xA1, 0x01,						// collection (application)
	0x85, HID_REPORTID_MediaReport, // report id
	// 4 media Keys
	0x15, 0x00,						//logical minimum
	0x26, 0xFF, 0xFF,				//logical maximum (3ff)
	0x19, 0x00,						// usage minimum (0)
	0x2A, 0xFF, 0xFF,				//usage maximum (3ff)
	0x95, 0x04,						//report count (4)
	0x75, 0x10,						//report size (16)
	0x81, 0x00,						//input
	0xC0,							//end collection
#endif

#ifdef HID_SYSTEM_ENABLE
	// System
	0x05, 0x01,							// USAGE_PAGE (Generic Desktop)
	0x09, 0x80,							// USAGE (System Control)
	0xa1, 0x01,							// COLLECTION (Application)
	0x85, HID_REPORTID_SystemReport,	//   REPORT_ID
	// 1 system key
	0x15, 0x00,							//   LOGICAL_MINIMUM (0)
	0x26, 0xff, 0x00,					//   LOGICAL_MAXIMUM (255)
	0x19, 0x00,							//   USAGE_MINIMUM (Undefined)
	0x29, 0xff,							//   USAGE_MAXIMUM (System Menu Down)
	0x95, 0x01,							//   REPORT_COUNT (1)
	0x75, 0x08,							//   REPORT_SIZE (8)
	0x81, 0x00,							//   INPUT (Data,Ary,Abs)
	0xc0,								// END_COLLECTION
#endif

#ifdef HID_GAMEPAD1_ENABLE
	// Gamepad1
	0x05, 0x01,							// USAGE_PAGE (Generic Desktop)
	0x09, 0x05,							// USAGE (Game Pad)
	0xa1, 0x01,							// COLLECTION (Application)
	0x85, HID_REPORTID_Gamepad1Report,	//   REPORT_ID
	// 32 Buttons
	0x05, 0x09,							//   USAGE_PAGE (Button)
	0x19, 0x01,							//   USAGE_MINIMUM (Button 1)
	0x29, 0x20,							//   USAGE_MAXIMUM (Button 32)
	0x15, 0x00,							//   LOGICAL_MINIMUM (0)
	0x25, 0x01,							//   LOGICAL_MAXIMUM (1)
	0x75, 0x01,							//   REPORT_SIZE (1)
	0x95, 0x20,							//   REPORT_COUNT (32)
	0x81, 0x02,							//   INPUT (Data,Var,Abs)
	// 6 16bit Axis
	0x05, 0x01,							//   USAGE_PAGE (Generic Desktop)
	0xa1, 0x00,							//   COLLECTION (Physical)
	0x09, 0x30,							//     USAGE (X)
	0x09, 0x31,							//     USAGE (Y)
	0x09, 0x32,							//     USAGE (Z)
	0x09, 0x33,							//     USAGE (Rx)
	0x09, 0x34,							//     USAGE (Ry)
	0x09, 0x35,							//     USAGE (Rz)
	0x15, 0x00,							//     LOGICAL_MINIMUM (0)
	0x27, 0xff, 0xff, 0x00, 0x00,		//     LOGICAL_MAXIMUM (65535)
	0x75, 0x10,							//     REPORT_SIZE (16)
	0x95, 0x06,							//     REPORT_COUNT (6)
	0x81, 0x02,							//     INPUT (Data,Var,Abs)
	0xc0,								//   END_COLLECTION
	// 2 Hat Switches
	0x05, 0x01,							//   USAGE_PAGE (Generic Desktop)
	0x09, 0x39,							//   USAGE (Hat switch)
	0x09, 0x39,							//   USAGE (Hat switch)
	0x15, 0x01,							//   LOGICAL_MINIMUM (1)
	0x25, 0x08,							//   LOGICAL_MAXIMUM (8)
	0x95, 0x02,							//   REPORT_COUNT (2)
	0x75, 0x04,							//   REPORT_SIZE (4)
	0x81, 0x02,							//   INPUT (Data,Var,Abs)
	// 8bit Throttle + Rudder
	//0x05, 0x02,							//   USAGE_PAGE (Simulation Controls)
	//0xa1, 0x00,							//   COLLECTION (Physical)
	//0x15, 0x00,							//     LOGICAL_MINIMUM (0)
	//0x26, 0xff, 0x00,					//     LOGICAL_MAXIMUM (255)
	//0x09, 0xbb,							//     USAGE (Throttle)
	//0x09, 0xba,							//     USAGE (Rudder)
	//0x75, 0x08,							//     REPORT_SIZE (8)
	//0x95, 0x02,							//     REPORT_COUNT (2)
	//0x81, 0x02,							//     INPUT (Data,Var,Abs)
	//0xc0,								//   END_COLLECTION
	0xc0,								// END_COLLECTION
#endif

#ifdef HID_GAMEPAD2_ENABLE
	// Gamepad2
	0x05, 0x01,							// USAGE_PAGE (Generic Desktop)
	0x09, 0x05,							// USAGE (Game Pad)
	0xa1, 0x01,							// COLLECTION (Application)
	0x85, HID_REPORTID_Gamepad2Report,	//   REPORT_ID
	// 32 Buttons
	0x05, 0x09,							//   USAGE_PAGE (Button)
	0x19, 0x01,							//   USAGE_MINIMUM (Button 1)
	0x29, 0x20,							//   USAGE_MAXIMUM (Button 32)
	0x15, 0x00,							//   LOGICAL_MINIMUM (0)
	0x25, 0x01,							//   LOGICAL_MAXIMUM (1)
	0x75, 0x01,							//   REPORT_SIZE (1)
	0x95, 0x20,							//   REPORT_COUNT (32)
	0x81, 0x02,							//   INPUT (Data,Var,Abs)
	// 6 16bit Axis
	0x05, 0x01,							//   USAGE_PAGE (Generic Desktop)
	0xa1, 0x00,							//   COLLECTION (Physical)
	0x09, 0x30,							//     USAGE (X)
	0x09, 0x31,							//     USAGE (Y)
	0x09, 0x32,							//     USAGE (Z)
	0x09, 0x33,							//     USAGE (Rx)
	0x09, 0x34,							//     USAGE (Ry)
	0x09, 0x35,							//     USAGE (Rz)
	0x15, 0x00,							//     LOGICAL_MINIMUM (0)
	0x27, 0xff, 0xff, 0x00, 0x00,		//     LOGICAL_MAXIMUM (65535)
	0x75, 0x10,							//     REPORT_SIZE (16)
	0x95, 0x06,							//     REPORT_COUNT (6)
	0x81, 0x02,							//     INPUT (Data,Var,Abs)
	0xc0,								//   END_COLLECTION
	// 2 Hat Switches
	0x09, 0x39,							//   USAGE (Hat switch)
	0x09, 0x39,							//   USAGE (Hat switch)
	0x15, 0x01,							//   LOGICAL_MINIMUM (1)
	0x25, 0x08,							//   LOGICAL_MAXIMUM (8)
	0x95, 0x02,							//   REPORT_COUNT (2)
	0x75, 0x04,							//   REPORT_SIZE (4)
	0x81, 0x02,							//   INPUT (Data,Var,Abs)
	// 8bit Throttle + Rudder
	//0x05, 0x02,							//   USAGE_PAGE (Simulation Controls)
	//0xa1, 0x00,							//   COLLECTION (Physical)
	//0x15, 0x00,							//     LOGICAL_MINIMUM (0)
	//0x26, 0xff, 0x00,					//     LOGICAL_MAXIMUM (255)
	//0x09, 0xbb,							//     USAGE (Throttle)
	//0x09, 0xba,							//     USAGE (Rudder)
	//0x75, 0x08,							//     REPORT_SIZE (8)
	//0x95, 0x02,							//     REPORT_COUNT (2)
	//0x81, 0x02,							//     INPUT (Data,Var,Abs)
	//0xc0,								//   END_COLLECTION
	0xc0,								// END_COLLECTION
#endif

#ifdef HID_JOYSTICK1_ENABLE
	// Joystick1
	0x05, 0x01,							// USAGE_PAGE (Generic Desktop)
	0x09, 0x04,							// USAGE (Joystick)
	0xa1, 0x01,							// COLLECTION (Application)
	0x85, HID_REPORTID_Joystick1Report,	//   REPORT_ID
	0xa1, 0x00,							//   COLLECTION (Physical)
	0x05, 0x09,							//     USAGE_PAGE (Button)
	0x19, 0x01,							//     USAGE_MINIMUM (Button 1)
	0x29, 0x02,							//     USAGE_MAXIMUM (Button 2)
	0x15, 0x00,							//     LOGICAL_MINIMUM (0)
	0x25, 0x01,							//     LOGICAL_MAXIMUM (1)
	0x75, 0x01,							//     REPORT_SIZE (1)
	0x95, 0x02,							//     REPORT_COUNT (2)
	0x81, 0x02,							//     INPUT (Data,Var,Abs)
	0x05, 0x01,							//     USAGE_PAGE (Generic Desktop)
	0x09, 0x30,							//     USAGE (X)
	0x09, 0x31,							//     USAGE (Y)
	0x15, 0x00,							//     LOGICAL_MINIMUM (0)
	0x26, 0xff, 0x03,					//     LOGICAL_MAXIMUM (1023)
	0x75, 0x0a,							//     REPORT_SIZE (10)
	0x95, 0x02,							//     REPORT_COUNT (2)
	0x81, 0x02,							//     INPUT (Data,Var,Abs)
	0x75, 0x02,							//     REPORT_SIZE (2)
	0x95, 0x01,							//     REPORT_COUNT (1)
	0x81, 0x03,							//     INPUT (Cnst,Var,Abs)
	0xc0,								//   END_COLLECTION
	0xc0,								// END_COLLECTION
#endif

#ifdef HID_JOYSTICK2_ENABLE
	// Joystick2
	0x05, 0x01,							// USAGE_PAGE (Generic Desktop)
	0x09, 0x04,							// USAGE (Joystick)
	0xa1, 0x01,							// COLLECTION (Application)
	0x85, HID_REPORTID_Joystick2Report,	//   REPORT_ID
	0xa1, 0x00,							//   COLLECTION (Physical)
	0x05, 0x09,							//     USAGE_PAGE (Button)
	0x19, 0x01,							//     USAGE_MINIMUM (Button 1)
	0x29, 0x02,							//     USAGE_MAXIMUM (Button 2)
	0x15, 0x00,							//     LOGICAL_MINIMUM (0)
	0x25, 0x01,							//     LOGICAL_MAXIMUM (1)
	0x75, 0x01,							//     REPORT_SIZE (1)
	0x95, 0x02,							//     REPORT_COUNT (2)
	0x81, 0x02,							//     INPUT (Data,Var,Abs)
	0x05, 0x01,							//     USAGE_PAGE (Generic Desktop)
	0x09, 0x30,							//     USAGE (X)
	0x09, 0x31,							//     USAGE (Y)
	0x15, 0x00,							//     LOGICAL_MINIMUM (0)
	0x26, 0xff, 0x03,					//     LOGICAL_MAXIMUM (1023)
	0x75, 0x0a,							//     REPORT_SIZE (10)
	0x95, 0x02,							//     REPORT_COUNT (2)
	0x81, 0x02,							//     INPUT (Data,Var,Abs)
	0x75, 0x02,							//     REPORT_SIZE (2)
	0x95, 0x01,							//     REPORT_COUNT (1)
	0x81, 0x03,							//     INPUT (Cnst,Var,Abs)
	0xc0,								//   END_COLLECTION
	0xc0								// END_COLLECTION
#endif
};

extern const HIDDescriptor _hidInterface PROGMEM;
const HIDDescriptor _hidInterface =
{
	D_INTERFACE(HID_INTERFACE,1,3,0,0),
	D_HIDREPORT(sizeof(_hidReportDescriptor)),
	D_ENDPOINT(USB_ENDPOINT_IN (HID_ENDPOINT_INT),USB_ENDPOINT_TYPE_INTERRUPT,0x40,0x01)
};

//================================================================================
//================================================================================
//	Driver

u8 _hid_protocol = 1;
u8 _hid_idle = 1;

#define WEAK __attribute__ ((weak))

int WEAK HID_GetInterface(u8* interfaceNum)
{
	interfaceNum[0] += 1;	// uses 1
	return USB_SendControl(TRANSFER_PGM,&_hidInterface,sizeof(_hidInterface));
}

int WEAK HID_GetDescriptor(int /* i */)
{
	return USB_SendControl(TRANSFER_PGM,_hidReportDescriptor,sizeof(_hidReportDescriptor));
}

void WEAK HID_SendReport(u8 id, const void* data, int len)
{
	USB_Send(HID_TX, &id, 1);
	USB_Send(HID_TX | TRANSFER_RELEASE,data,len);
}

bool WEAK HID_Setup(Setup& setup)
{
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
	}
	return false;
}

#endif

//================================================================================
// HID Uno/Mega
//================================================================================

#else /* if defined(USBCON) */

HID_ HID;

HID_::HID_(void){
	// empty
}

void HID_::begin(void){
	Serial.begin(115200);
}

void HID_::end(void){
	Serial.end();
}

void HID_::sendReport(uint8_t ReportID, const void* HIDReport, uint8_t length){
	// write the Report via Protocol and checksum. 16bit for each sending
	// send control address
	NHPwriteChecksum(NHP_ADDRESS_CONTROL, (NHP_USAGE_ARDUINOHID<<8)|ReportID);
	const uint8_t* report = (const uint8_t*)HIDReport;
	for(int i = 0; i<length;i++){
		uint8_t data0=report[i++];
		uint8_t data1=0;
		if(i!=length)
			data1=report[i];
		// valid HID reports start at Address 2
		NHPwriteChecksum(2+i/2,(data1<<8) | data0);
	}
}
#endif /* if defined(USBCON) */

// simple copy/modification of the NicoHoodProtocol writechecksum function
void HID_::NHPwriteChecksum(uint8_t address, uint16_t indata){
	// writes two bytes with its inverse
	uint32_t temp=~indata;
	uint32_t data=(temp<<16)|indata;

	// buffer for write operation
	uint8_t writebuffer[6];

	// start with the maximum size of blocks
	uint8_t blocks=7;

	// check for the first 7 bit block that doesnt fit into the first 3 bits
	while(blocks>2){
		uint8_t nextvalue=(data>>(7*(blocks-3)));
		if(nextvalue>NHP_MASK_DATA_3BIT){
			// special case for the MSB
			if(blocks==7) {
				writebuffer[0] = nextvalue;
				blocks--;
			}
			break;
		}
		else{
			// write the possible first 3 bits and check again after
			writebuffer[0] = nextvalue;
			blocks--;
		}
	}

	// write the rest of the data bits
	uint8_t datablocks=blocks-2;
	while(datablocks>0){
		writebuffer[datablocks] = data & NHP_MASK_DATA_7BIT;
		data>>=7;
		datablocks--;
	}

	// write lead + length mask
	writebuffer[0] |= NHP_MASK_LEAD | (blocks <<3);

	// write end mask
	writebuffer[blocks-1] = NHP_MASK_END | ((address-1) & NHP_MASK_ADDRESS);

	// write the buffer
	Serial.write(writebuffer, blocks);
}

//================================================================================
// Mouse
//================================================================================

Mouse_ Mouse;

Mouse_::Mouse_(void){
	// empty
}

void Mouse_::begin(void){
	memset(&_report, 0, sizeof(_report));
	HID.sendReport(HID_REPORTID_MouseReport, &_report, sizeof(_report));
}

void Mouse_::end(void){
	begin();
}

void Mouse_::click(uint8_t b){
	_report.buttons = b;
	move(0,0,0);
	_report.buttons = 0;
	move(0,0,0);
}

void Mouse_::move(signed char x, signed char y, signed char wheel){
	_report.xAxis=x;
	_report.yAxis=y;
	_report.wheel=wheel;
	HID.sendReport(HID_REPORTID_MouseReport, &_report, sizeof(HID_MouseReport_Data_t));
}

void Mouse_::buttons(uint8_t b){
	if (b != _report.buttons)	{
		_report.buttons = b;
		move(0,0,0);
	}
}

void Mouse_::press(uint8_t b){
	buttons(_report.buttons | b);
}

void Mouse_::release(uint8_t b){
	buttons(_report.buttons & ~b);
}

void Mouse_::releaseAll(void){
	begin();
}

bool Mouse_::isPressed(uint8_t b){
	if ((b & _report.buttons) > 0) 
		return true;
	return false;
}

//================================================================================
// Keyboard
//================================================================================

Keyboard_ Keyboard;

Keyboard_::Keyboard_(void){
	// empty
}

void Keyboard_::begin(void){
	memset(&_report, 0, sizeof(_report));
	HID.sendReport(HID_REPORTID_KeyboardReport, &_report, sizeof(_report));
}

void Keyboard_::end(void){
	begin();
}

extern
	const uint8_t _asciimap[128] PROGMEM;

#define SHIFT 0x80
const uint8_t _asciimap[128] =
{
	0x00,             // NUL
	0x00,             // SOH
	0x00,             // STX
	0x00,             // ETX
	0x00,             // EOT
	0x00,             // ENQ
	0x00,             // ACK  
	0x00,             // BEL
	0x2a,			// BS	Backspace
	0x2b,			// TAB	Tab
	0x28,			// LF	Enter
	0x00,             // VT 
	0x00,             // FF 
	0x00,             // CR 
	0x00,             // SO 
	0x00,             // SI 
	0x00,             // DEL
	0x00,             // DC1
	0x00,             // DC2
	0x00,             // DC3
	0x00,             // DC4
	0x00,             // NAK
	0x00,             // SYN
	0x00,             // ETB
	0x00,             // CAN
	0x00,             // EM 
	0x00,             // SUB
	0x00,             // ESC
	0x00,             // FS 
	0x00,             // GS 
	0x00,             // RS 
	0x00,             // US 

	0x2c,		   //  ' '
	0x1e|SHIFT,	   // !
	0x34|SHIFT,	   // "
	0x20|SHIFT,    // #
	0x21|SHIFT,    // $
	0x22|SHIFT,    // %
	0x24|SHIFT,    // &
	0x34,          // '
	0x26|SHIFT,    // (
	0x27|SHIFT,    // )
	0x25|SHIFT,    // *
	0x2e|SHIFT,    // +
	0x36,          // ,
	0x2d,          // -
	0x37,          // .
	0x38,          // /
	0x27,          // 0
	0x1e,          // 1
	0x1f,          // 2
	0x20,          // 3
	0x21,          // 4
	0x22,          // 5
	0x23,          // 6
	0x24,          // 7
	0x25,          // 8
	0x26,          // 9
	0x33|SHIFT,      // :
	0x33,          // ;
	0x36|SHIFT,      // <
	0x2e,          // =
	0x37|SHIFT,      // >
	0x38|SHIFT,      // ?
	0x1f|SHIFT,      // @
	0x04|SHIFT,      // A
	0x05|SHIFT,      // B
	0x06|SHIFT,      // C
	0x07|SHIFT,      // D
	0x08|SHIFT,      // E
	0x09|SHIFT,      // F
	0x0a|SHIFT,      // G
	0x0b|SHIFT,      // H
	0x0c|SHIFT,      // I
	0x0d|SHIFT,      // J
	0x0e|SHIFT,      // K
	0x0f|SHIFT,      // L
	0x10|SHIFT,      // M
	0x11|SHIFT,      // N
	0x12|SHIFT,      // O
	0x13|SHIFT,      // P
	0x14|SHIFT,      // Q
	0x15|SHIFT,      // R
	0x16|SHIFT,      // S
	0x17|SHIFT,      // T
	0x18|SHIFT,      // U
	0x19|SHIFT,      // V
	0x1a|SHIFT,      // W
	0x1b|SHIFT,      // X
	0x1c|SHIFT,      // Y
	0x1d|SHIFT,      // Z
	0x2f,          // [
	0x31,          // bslash
	0x30,          // ]
	0x23|SHIFT,    // ^
	0x2d|SHIFT,    // _
	0x35,          // `
	0x04,          // a
	0x05,          // b
	0x06,          // c
	0x07,          // d
	0x08,          // e
	0x09,          // f
	0x0a,          // g
	0x0b,          // h
	0x0c,          // i
	0x0d,          // j
	0x0e,          // k
	0x0f,          // l
	0x10,          // m
	0x11,          // n
	0x12,          // o
	0x13,          // p
	0x14,          // q
	0x15,          // r
	0x16,          // s
	0x17,          // t
	0x18,          // u
	0x19,          // v
	0x1a,          // w
	0x1b,          // x
	0x1c,          // y
	0x1d,          // z
	0x2f|SHIFT,    // 
	0x31|SHIFT,    // |
	0x30|SHIFT,    // }
	0x35|SHIFT,    // ~
	0				// DEL
};

// removed <--
//uint8_t USBPutChar(uint8_t c);

size_t Keyboard_::write(uint8_t c)
{	
	uint8_t p = press(c);		// Keydown
	//uint8_t r = 
	release(c);		// Keyup
	return (p);					// just return the result of press() since release() almost always returns 1
}

// press() adds the specified key (printing, non-printing, or modifier)
// to the persistent key report and sends the report.  Because of the way 
// USB HID works, the host acts like the key remains pressed until we 
// call release(), releaseAll(), or otherwise clear the report and resend.
size_t Keyboard_::press(uint8_t k) 
{
	uint8_t i;
	if (k >= 136) {			// it's a non-printing key (not a modifier)
		k = k - 136;
	} else if (k >= 128) {	// it's a modifier key
		_report.modifiers |= (1<<(k-128));
		k = 0;
	} else {				// it's a printing key
		k = pgm_read_byte(_asciimap + k);
		if (!k) {
			setWriteError();
			return 0;
		}
		if (k & 0x80) {						// it's a capital letter or other character reached with shift
			_report.modifiers |= 0x02;	// the left shift modifier
			k &= 0x7F;
		}
	}

	// Add k to the key report only if it's not already present
	// and if there is an empty slot.
	if (_report.keys[0] != k && _report.keys[1] != k && 
		_report.keys[2] != k && _report.keys[3] != k &&
		_report.keys[4] != k && _report.keys[5] != k) {

			for (i=0; i<6; i++) {
				if (_report.keys[i] == 0x00) {
					_report.keys[i] = k;
					break;
				}
			}
			if (i == 6) {
				setWriteError();
				return 0;
			}	
	}
	HID.sendReport(HID_REPORTID_KeyboardReport, &_report, sizeof(_report));
	return 1;
}

// release() takes the specified key out of the persistent key report and
// sends the report.  This tells the OS the key is no longer pressed and that
// it shouldn't be repeated any more.
size_t Keyboard_::release(uint8_t k) 
{
	uint8_t i;
	if (k >= 136) {			// it's a non-printing key (not a modifier)
		k = k - 136;
	} else if (k >= 128) {	// it's a modifier key
		_report.modifiers &= ~(1<<(k-128));
		k = 0;
	} else {				// it's a printing key
		k = pgm_read_byte(_asciimap + k);
		if (!k) {
			return 0;
		}
		if (k & 0x80) {							// it's a capital letter or other character reached with shift
			_report.modifiers &= ~(0x02);	// the left shift modifier
			k &= 0x7F;
		}
	}

	// Test the key report to see if k is present.  Clear it if it exists.
	// Check all positions in case the key is present more than once (which it shouldn't be)
	for (i=0; i<6; i++) {
		if (0 != k && _report.keys[i] == k) {
			_report.keys[i] = 0x00;
		}
	}

	HID.sendReport(HID_REPORTID_KeyboardReport, &_report, sizeof(_report));
	return 1;
}

void Keyboard_::releaseAll(void){
	begin();
}

//================================================================================
// Media
//================================================================================

Media_ Media;

Media_::Media_(void){
	// empty
}

void Media_::begin(void){
	memset(&_report, 0, sizeof(_report));
	HID.sendReport(HID_REPORTID_MediaReport, &_report, sizeof(_report));
}

void Media_::end(void){
	begin();
}

void Media_::write(uint16_t m){
	press(m);
	release(m);
}

void Media_::press(uint16_t m){
	// search for a free spot
	for (int i=0; i<sizeof(HID_MediaReport_Data_t)/2; i++) {
		if(_report.whole16[i] == 0x00) {
			_report.whole16[i] = m;
			break;
		}
	}
	HID.sendReport(HID_REPORTID_MediaReport, &_report, sizeof(_report));
}

void Media_::release(uint16_t m){
	// search and release the keypress
	for (int i=0; i<sizeof(HID_MediaReport_Data_t)/2; i++) {
		if (_report.whole16[i] == m) {
			_report.whole16[i] = 0x00;
			// no break to delete multiple keys
		}
	}
	HID.sendReport(HID_REPORTID_MediaReport, &_report, sizeof(_report));
}

void Media_::releaseAll(void){
	begin();
}

//================================================================================
// System
//================================================================================

System_ System;

System_::System_(void){
	// empty
}

void System_::begin(void){
	uint8_t _report = 0;
	HID.sendReport(HID_REPORTID_SystemReport, &_report, sizeof(_report));
}

void System_::end(void){
	begin();
}

void System_::write(uint8_t s){
	press(s);
	release();
}

void System_::press(uint8_t s){
	HID.sendReport(HID_REPORTID_SystemReport, &s, sizeof(s));
}

void System_::release(void){
	begin();
}

void System_::releaseAll(void){
	begin();
}

//================================================================================
// Gamepad
//================================================================================

Gamepad_ Gamepad1(HID_REPORTID_Gamepad1Report);
Gamepad_ Gamepad2(HID_REPORTID_Gamepad2Report);

Gamepad_::Gamepad_(uint8_t reportID){
	_reportID = reportID;
	// empty
}

void Gamepad_::begin(void){
	memset(&_report, 0, sizeof(_report));
	HID.sendReport(_reportID, &_report, sizeof(_report));
}

void Gamepad_::end(void){
	begin();
}

void Gamepad_::write(void){
	HID.sendReport(_reportID, &_report, sizeof(_report));
}

void Gamepad_::press(uint8_t b){
	_report.buttons|=(uint32_t)1<<(b-1);
}

void Gamepad_::release(uint8_t b){
	_report.buttons&=~((uint32_t)1<<(b-1));
}

void Gamepad_::releaseAll(void){
	_report.buttons=0;
}

//================================================================================
// Joystick
//================================================================================

Joystick_ Joystick1(HID_REPORTID_Joystick1Report);
Joystick_ Joystick2(HID_REPORTID_Joystick2Report);

Joystick_::Joystick_(uint8_t reportID){
	_reportID = reportID;
	// empty
}

void Joystick_::begin(void){
	memset(&_report, 0, sizeof(_report));
	HID.sendReport(_reportID, &_report, sizeof(_report));
}

void Joystick_::end(void){
	begin();
}

void Joystick_::write(void){
	HID.sendReport(_reportID, &_report, sizeof(_report));;
}

void Joystick_::press(uint8_t b){
	if(b==1) _report.button1=1;
	else if(b==2) _report.button2=1;
}

void Joystick_::release(uint8_t b){
	if(b==1) _report.button1=0;
	else if(b==2) _report.button2=0;
}

void Joystick_::releaseAll(void){
	_report.button1=0;
	_report.button2=0;
}