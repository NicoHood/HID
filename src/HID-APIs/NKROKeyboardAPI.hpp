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

// Include guard
#pragma once

NKROKeyboardAPI::NKROKeyboardAPI(void)
{
	// Empty
}

void NKROKeyboardAPI::begin(void)
{
	releaseAll();
}

void NKROKeyboardAPI::end(void)
{
	releaseAll();
}

void NKROKeyboardAPI::send_now(void){
	SendReport(&_keyReport, sizeof(_keyReport));
}

// press() adds the specified key (printing, non-printing, or modifier)
// to the persistent key report and sends the report.  Because of the way 
// USB HID works, the host acts like the key remains pressed until we 
// call release(), releaseAll(), or otherwise clear the report and resend.
size_t NKROKeyboardAPI::press(uint8_t k)
{
	size_t ret = addKeyToReport(k);
	if(ret){
		send_now();
	}
	return ret;
}

// release() takes the specified key out of the persistent key report and
// sends the report.  This tells the OS the key is no longer pressed and that
// it shouldn't be repeated any more.
size_t NKROKeyboardAPI::release(uint8_t k)
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
	send_now();

	return 1;
}

void NKROKeyboardAPI::releaseAll(void)
{
	// release all keys
	memset(&_keyReport, 0x00, sizeof(_keyReport));
	send_now();
}

size_t NKROKeyboardAPI::write(uint8_t c)
{
	uint8_t p = press(c);  // Keydown
	release(c);            // Keyup
	return p;              // just return the result of press() since release() almost always returns 1
}


// pressKeycode() adds the specified key (printing, non-printing, or modifier)
// to the persistent key report and sends the report.  Because of the way 
// USB HID works, the host acts like the key remains pressed until we 
// call releaseKeycode(), releaseAll(), or otherwise clear the report and resend.
size_t NKROKeyboardAPI::pressKeycode(uint8_t k)
{
	if (!addKeycodeToReport(k)) {
		return 0;
	}
	send_now();
}

size_t NKROKeyboardAPI::addKeyToReport(uint8_t k)
{
	if (k >= 136) {			// it's a non-printing key (not a modifier)
		k = k - 136;
	} else if (k >= 128) {	// it's a modifier key
		_keyReport.modifiers |= (1<<(k-128));
		k = 0; //TODO return 1??
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

size_t NKROKeyboardAPI::addKeycodeToReport(uint8_t k)
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
size_t NKROKeyboardAPI::releaseKeycode(uint8_t k)
{
	if (!removeKeycodeFromReport(k)) {
		return 0;
	}
	send_now();
}

size_t NKROKeyboardAPI::removeKeyFromReport(uint8_t k)
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

size_t NKROKeyboardAPI::removeKeycodeFromReport(uint8_t k)
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


size_t NKROKeyboardAPI::writeKeycode(uint8_t c)
{
	uint8_t p = pressKeycode(c);	// Keydown
	releaseKeycode(c);				// Keyup
	return (p);						// just return the result of pressKeycode() since release() almost always returns 1
}
