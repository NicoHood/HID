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

#include "NKROKeyboard.h"

#if defined(_USING_HID)

//================================================================================
//================================================================================
//	NKROKeyboard

static const u8 _hidReportDescriptor[] PROGMEM = {
    //  NKRO Keyboard
    0x05, 0x01,                      /* USAGE_PAGE (Generic Desktop)	  47 */
    0x09, 0x06,                      /* USAGE (Keyboard) */
    0xa1, 0x01,                      /* COLLECTION (Application) */
    0x85, HID_REPORTID_NKRO_KEYBOARD,	 /*   REPORT_ID */
    0x05, 0x07,                      /*   USAGE_PAGE (Keyboard) */

    /* Keyboard Modifiers (shift, alt, ...) */
    0x19, 0xe0,                      /*   USAGE_MINIMUM (Keyboard LeftControl) */
    0x29, 0xe7,                      /*   USAGE_MAXIMUM (Keyboard Right GUI) */
    0x15, 0x00,                      /*   LOGICAL_MINIMUM (0) */
    0x25, 0x01,                      /*   LOGICAL_MAXIMUM (1) */
    0x75, 0x01,                      /*   REPORT_SIZE (1) */
	0x95, 0x08,                      /*   REPORT_COUNT (8) */
    0x81, 0x02,                      /*   INPUT (Data,Var,Abs) */

#if defined(HID_KEYBOARD_LEDS_ENABLED)
	/* 5 LEDs for num lock etc, 3 left for advanced, custom usage */
	0x05, 0x08,						 /*   USAGE_PAGE (LEDs) */
	0x19, 0x01,						 /*   USAGE_MINIMUM (Num Lock) */
	0x29, 0x05,						 /*   USAGE_MAXIMUM (Kana) */
	0x95, 0x08,						 /*   REPORT_COUNT (8) */
	0x75, 0x01,						 /*   REPORT_SIZE (1) */
	0x91, 0x02,						 /*   OUTPUT (Data,Var,Abs) */
	/*  Reserved 3 bits */
	//0x95, 0x01,						 /*   REPORT_COUNT (1) */
	//0x75, 0x03,						 /*   REPORT_SIZE (3) */
	//0x91, 0x03,						 /*   OUTPUT (Cnst,Var,Abs) */
#endif

	/* 104 Keys as bitmap */
	0x05, 0x07,						/*   Usage Page (Key Codes) */
	0x19, 0x00,						/*   Usage Minimum (0) */
	0x29, NKRO_KEY_COUNT - 1,		/*   Usage Maximum (103) */
	0x15, 0x00,						/*   Logical Minimum (0) */
	0x25, 0x01,						/*   Logical Maximum (1) */
	0x75, 0x01,						/*   Report Size (1) */
	0x95, NKRO_KEY_COUNT,			/*   Report Count (104) */
	0x81, 0x02,						/*   Input (Data, Variable, Absolute) */

    /* 1 Custom Keyboard key */
    0x95, 0x01,                      /*   REPORT_COUNT (1) */
    0x75, 0x08,                      /*   REPORT_SIZE (8) */
    0x15, 0x00,                      /*   LOGICAL_MINIMUM (0) */
    0x26, 0xE7, 0x00,                /*   LOGICAL_MAXIMUM (231) */
    /*0x05, 0x07,                         USAGE_PAGE (Keyboard) */
    0x19, 0x00,                      /*   USAGE_MINIMUM (Reserved (no event indicated)) */
    0x29, 0xE7,                      /*   USAGE_MAXIMUM (Keyboard Right GUI) */
    0x81, 0x00,                      /*   INPUT (Data,Ary,Abs) */

    /* End */
	0xC0						     /*   End Collection */
};

NKROKeyboard_::NKROKeyboard_(void) : 
HIDDevice((uint8_t*)_hidReportDescriptor, sizeof(_hidReportDescriptor), HID_REPORTID_NKRO_KEYBOARD)
#if defined(HID_KEYBOARD_LEDS_ENABLED)
,leds(0)
#endif
{
	// HID Descriptor is appended via the inherited HIDDevice class
}

void NKROKeyboard_::begin(void)
{
	releaseAll();
}

void NKROKeyboard_::end(void)
{
	releaseAll();
}

void NKROKeyboard_::sendReport(HID_NKROKeyboardReport_Data_t* keys)
{
	// Call the inherited function.
	// This wrapper still saves us some bytes
#if defined(USE_BOOT_KEYBOARD_PROTOCOL)
	if(getProtocol() != 1){
		SendRawReport(keys, sizeof(HID_NKROKeyboardReport_Data_t));
	}
	else
#endif
	SendReport(keys, sizeof(HID_NKROKeyboardReport_Data_t));
}

void NKROKeyboard_::send_now(void){
	sendReport(&_keyReport);
}

#if defined(HID_KEYBOARD_LEDS_ENABLED)
void NKROKeyboard_::setReportData(void* &data, uint16_t len){
    // Save led state
    if(len == 2)
    	leds = *(uint8_t*)(data+1);
}

uint8_t NKROKeyboard_::getLeds(void){
    return leds;
}
#endif

// press() adds the specified key (printing, non-printing, or modifier)
// to the persistent key report and sends the report.  Because of the way 
// USB HID works, the host acts like the key remains pressed until we 
// call release(), releaseAll(), or otherwise clear the report and resend.
size_t NKROKeyboard_::press(uint8_t k)
{
	size_t ret = addKeyToReport(k);
	if(ret){
		sendReport(&_keyReport);
	}
	return ret;
}

// release() takes the specified key out of the persistent key report and
// sends the report.  This tells the OS the key is no longer pressed and that
// it shouldn't be repeated any more.
size_t NKROKeyboard_::release(uint8_t k)
{
	// it's a non-printing key (not a modifier)
	if (k >= 136)
		k = k - 136;

	// it's a modifier key
	else if (k >= 128)
		k = k - 128;

	// it's a printing key
	else {
		k = pgm_read_byte(_asciimap + k);
		if (!k)
			return 0;

		// it's a capital letter or other character reached with shift
		if (k & SHIFT) {
			// the left shift modifier		
			_keyReport.modifiers &= ~(0x02);
			k = k ^ SHIFT;
		}
	}

	removeKeycodeFromReport(k);
	sendReport(&_keyReport);

	return 1;
}

void NKROKeyboard_::releaseAll(void)
{
	// release all keys
	memset(&_keyReport, 0x00, sizeof(_keyReport));
	sendReport(&_keyReport);
}

size_t NKROKeyboard_::write(uint8_t c)
{
	uint8_t p = press(c);  // Keydown
	release(c);            // Keyup
	return p;              // just return the result of press() since release() almost always returns 1
}


// pressKeycode() adds the specified key (printing, non-printing, or modifier)
// to the persistent key report and sends the report.  Because of the way 
// USB HID works, the host acts like the key remains pressed until we 
// call releaseKeycode(), releaseAll(), or otherwise clear the report and resend.
size_t NKROKeyboard_::pressKeycode(uint8_t k)
{
	if (!addKeycodeToReport(k)) {
		return 0;
	}
	sendReport(&_keyReport);
}

size_t NKROKeyboard_::addKeyToReport(uint8_t k)
{
	if (k >= 136) {			// it's a non-printing key (not a modifier)
		k = k - 136;
	} else if (k >= 128) {	// it's a modifier key
		_keyReport.modifiers |= (1<<(k-128));
		k = 0;
	} else {				// it's a printing key
		k = pgm_read_byte(_asciimap + k);
		if (!k) {
			setWriteError();
			return 0;
		}
		if (k & SHIFT) {						// it's a capital letter or other character reached with shift
			_keyReport.modifiers |= 0x02;	// the left shift modifier
			k = k ^ SHIFT;
		}
	}

	return addKeycodeToReport(k);
}

size_t NKROKeyboard_::addKeycodeToReport(uint8_t k)
{
	// keymap key
	if (k < NKRO_KEY_COUNT)
		_keyReport.keys[k / 8] |= 1 << (k % 8);

	// it's a modifier key
	else if ((k >= HID_KEYBOARD_LEFT_CONTROL) && (k <= HID_KEYBOARD_RIGHT_GUI))
		_keyReport.modifiers |= (0x01 << (k - HID_KEYBOARD_LEFT_CONTROL));

	// custom key
	else
		_keyReport.key = k;

	return 1;
}


// releaseKeycode() takes the specified key out of the persistent key report and
// sends the report.  This tells the OS the key is no longer pressed and that
// it shouldn't be repeated any more.
// When send is set to FALSE (= 0) no sendReport() is executed. This comes in
// handy when combining key releases (e.g. SHIFT+A).
size_t NKROKeyboard_::releaseKeycode(uint8_t k)
{
	if (!removeKeycodeFromReport(k)) {
		return 0;
	}
	sendReport(&_keyReport);
}

size_t NKROKeyboard_::removeKeyFromReport(uint8_t k)
{
	if (k >= 136) {			// it's a non-printing key (not a modifier)
		k = k - 136;
	} else if (k >= 128) {	// it's a modifier key
		_keyReport.modifiers &= ~(1<<(k-128));
		k = 0;
	} else {				// it's a printing key
		k = pgm_read_byte(_asciimap + k);
		if (!k) {
			return 0;
		}
		if (k & SHIFT) {							// it's a capital letter or other character reached with shift
			_keyReport.modifiers &= ~(0x02);	// the left shift modifier
			k = k ^ SHIFT;
		}
	}
	
	return removeKeycodeFromReport(k);
}

size_t NKROKeyboard_::removeKeycodeFromReport(uint8_t k)
{
	// keymap key
	if (k < NKRO_KEY_COUNT)
		_keyReport.keys[k / 8] &= ~(1 << (k % 8));

	// it's a modifier key
	else if ((k >= HID_KEYBOARD_LEFT_CONTROL) && (k <= HID_KEYBOARD_RIGHT_GUI))
		_keyReport.modifiers &= ~(0x01 << (k - HID_KEYBOARD_LEFT_CONTROL));

	// custom key
	else
		_keyReport.key = 0x00;

	return 1;
}


size_t NKROKeyboard_::writeKeycode(uint8_t c)
{
	uint8_t p = pressKeycode(c);	// Keydown
	releaseKeycode(c);				// Keyup
	return (p);						// just return the result of pressKeycode() since release() almost always returns 1
}

NKROKeyboard_ NKROKeyboard;

#endif
