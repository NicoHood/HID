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

#include "ImprovedKeyboard.h"

#if defined(_USING_HID)

//================================================================================
//================================================================================
//	Keyboard

static const u8 _hidReportDescriptor[] PROGMEM = {
    //  Keyboard
    0x05, 0x01,                      /* USAGE_PAGE (Generic Desktop)	  47 */
    0x09, 0x06,                      /* USAGE (Keyboard) */
    0xa1, 0x01,                      /* COLLECTION (Application) */
    0x85, HID_REPORTID_KEYBOARD,	 /*   REPORT_ID */
    0x05, 0x07,                      /*   USAGE_PAGE (Keyboard) */

    /* Keyboard Modifiers (shift, alt, ...) */
    0x19, 0xe0,                      /*   USAGE_MINIMUM (Keyboard LeftControl) */
    0x29, 0xe7,                      /*   USAGE_MAXIMUM (Keyboard Right GUI) */
    0x15, 0x00,                      /*   LOGICAL_MINIMUM (0) */
    0x25, 0x01,                      /*   LOGICAL_MAXIMUM (1) */
    0x75, 0x01,                      /*   REPORT_SIZE (1) */
	0x95, 0x08,                      /*   REPORT_COUNT (8) */
    0x81, 0x02,                      /*   INPUT (Data,Var,Abs) */

    /* Reserved byte */
    0x95, 0x01,                      /*   REPORT_COUNT (1) */
    0x75, 0x08,                      /*   REPORT_SIZE (8) */
    0x81, 0x03,                      /*   INPUT (Cnst,Var,Abs) */
    
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

    /* 6 Keyboard keys */
    0x95, 0x06,                      /*   REPORT_COUNT (6) */
    0x75, 0x08,                      /*   REPORT_SIZE (8) */
    0x15, 0x00,                      /*   LOGICAL_MINIMUM (0) */
    0x26, 0xE7, 0x00,                /*   LOGICAL_MAXIMUM (231) */
    0x05, 0x07,                      /*   USAGE_PAGE (Keyboard) */
    0x19, 0x00,                      /*   USAGE_MINIMUM (Reserved (no event indicated)) */
    0x29, 0xE7,                      /*   USAGE_MAXIMUM (Keyboard Right GUI) */
    0x81, 0x00,                      /*   INPUT (Data,Ary,Abs) */

    /* End */
    0xc0                            /* END_COLLECTION */
};

Keyboard_::Keyboard_(void) : 
HIDDevice((uint8_t*)_hidReportDescriptor, sizeof(_hidReportDescriptor), HID_REPORTID_KEYBOARD)
#if defined(HID_KEYBOARD_LEDS_ENABLED)
,leds(0)
#endif
{
	// HID Descriptor is appended via the inherited HIDDevice class
}

void Keyboard_::begin(void)
{
	releaseAll();
}

void Keyboard_::end(void)
{
	releaseAll();
}

void Keyboard_::sendReport(HID_KeyboardReport_Data_t* keys)
{
	// Call the inherited function.
	// This wrapper still saves us some bytes
#if defined(USE_BOOT_KEYBOARD_PROTOCOL)
	if(getProtocol() != 1){
		SendRawReport(keys,sizeof(HID_KeyboardReport_Data_t));
	}
	else
#endif
	SendReport(keys,sizeof(HID_KeyboardReport_Data_t));
}

void Keyboard_::send_now(void){
	sendReport(&_keyReport);
}

#if defined(HID_KEYBOARD_LEDS_ENABLED)
void Keyboard_::setReportData(const void* data, uint8_t len){
    // Save led state
    if(len == 2)
    	leds = *(uint8_t*)(data+1);
}

uint8_t Keyboard_::getLeds(void){
    return leds;
}
#endif


// press() adds the specified key (printing, non-printing, or modifier)
// to the persistent key report and sends the report.  Because of the way 
// USB HID works, the host acts like the key remains pressed until we 
// call release(), releaseAll(), or otherwise clear the report and resend.
size_t Keyboard_::press(uint8_t k) 
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
size_t Keyboard_::release(uint8_t k) 
{
	uint8_t i;
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
	
	// Test the key report to see if k is present.  Clear it if it exists.
	// Check all positions in case the key is present more than once (which it shouldn't be)
	for (i=0; i<6; i++) {
		if (0 != k && _keyReport.keys[i] == k) {
			_keyReport.keys[i] = 0x00;
		}
	}

	sendReport(&_keyReport);
	return 1;
}

void Keyboard_::releaseAll(void)
{
	// release all keys
	memset(&_keyReport, 0x00, sizeof(_keyReport));
	sendReport(&_keyReport);
}

size_t Keyboard_::write(uint8_t c)
{	
	uint8_t p = press(c);  // Keydown
	release(c);            // Keyup
	return p;              // just return the result of press() since release() almost always returns 1
}

// pressKeycode() adds the specified key (printing, non-printing, or modifier)
// to the persistent key report and sends the report.  Because of the way 
// USB HID works, the host acts like the key remains pressed until we 
// call releaseKeycode(), releaseAll(), or otherwise clear the report and resend.
size_t Keyboard_::pressKeycode(uint8_t k)
{
	if (!addKeycodeToReport(k)) {
		return 0;
	}
	sendReport(&_keyReport);
}

size_t Keyboard_::addKeyToReport(uint8_t k)
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

size_t Keyboard_::addKeycodeToReport(uint8_t k)
{
	uint8_t index = 0;
	uint8_t done = 0;

	if ((k >= HID_KEYBOARD_LEFT_CONTROL) && (k <= HID_KEYBOARD_RIGHT_GUI)) {
		// it's a modifier key
		_keyReport.modifiers |= (0x01 << (k - HID_KEYBOARD_LEFT_CONTROL));
	}
	else {
		// it's some other key:
		// Add k to the key report only if it's not already present
		// and if there is an empty slot.
		for (index = 0; index < sizeof(_keyReport.keys); index++) {
			if (_keyReport.keys[index] != k) { // is k already in list?
				if (0 == _keyReport.keys[index]) { // have we found an empty slot?
					_keyReport.keys[index] = k;
					done = 1;
					break;
				}
			}
			else {
				done = 1;
				break;
			}

		}

		// use separate variable to check if slot was found
		// for style reasons - we do not know how the compiler
		// handles the for() index when it leaves the loop
		if (0 == done) {
			setWriteError();
			return 0;
		}
	}

	return 1;
}


// releaseKeycode() takes the specified key out of the persistent key report and
// sends the report.  This tells the OS the key is no longer pressed and that
// it shouldn't be repeated any more.
// When send is set to FALSE (= 0) no sendReport() is executed. This comes in
// handy when combining key releases (e.g. SHIFT+A).
size_t Keyboard_::releaseKeycode(uint8_t k)
{
	if (!removeKeycodeFromReport(k)) {
		return 0;
	}
	sendReport(&_keyReport);
}

size_t Keyboard_::removeKeyFromReport(uint8_t k)
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

size_t Keyboard_::removeKeycodeFromReport(uint8_t k)
{
	uint8_t indexA;
	uint8_t indexB;
	uint8_t count;

	if ((k >= HID_KEYBOARD_LEFT_CONTROL) && (k <= HID_KEYBOARD_RIGHT_GUI)) {
		// it's a modifier key
		_keyReport.modifiers = _keyReport.modifiers & (~(0x01 << (k - HID_KEYBOARD_LEFT_CONTROL)));
	}
	else {
		// it's some other key:
		// Test the key report to see if k is present.  Clear it if it exists.
		// Check all positions in case the key is present more than once (which it shouldn't be)
		for (indexA = 0; indexA < sizeof(_keyReport.keys); indexA++) {
			if (_keyReport.keys[indexA] == k) {
				_keyReport.keys[indexA] = 0;
			}
		}

		// finally rearrange the keys list so that the free (= 0x00) are at the
		// end of the keys list - some implementations stop for keys at the
		// first occurence of an 0x00 in the keys list
		// so (0x00)(0x01)(0x00)(0x03)(0x02)(0x00) becomes 
		//    (0x01)(0x03)(0x02)(0x00)(0x00)(0x00)
		count = 0; // holds the number of zeros we've found
		indexA = 0;
		while ((indexA + count) < sizeof(_keyReport.keys)) {
			if (0 == _keyReport.keys[indexA]) {
				count++; // one more zero
				for (indexB = indexA; indexB < sizeof(_keyReport.keys) - count; indexB++) {
					_keyReport.keys[indexB] = _keyReport.keys[indexB + 1];
				}
				_keyReport.keys[sizeof(_keyReport.keys) - count] = 0;
			}
			else {
				indexA++; // one more non-zero
			}
		}
	}

	return 1;
}


size_t Keyboard_::writeKeycode(uint8_t c)
{
	uint8_t p = pressKeycode(c);	// Keydown
	releaseKeycode(c);				// Keyup
	return (p);						// just return the result of pressKeycode() since release() almost always returns 1
}

Keyboard_ Keyboard;

#endif
