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

// Include guard
#pragma once

size_t DefaultKeyboardAPI::set(KeyboardKeycode k, bool s) 
{
	const auto keycodesEnd = &_keyReport.keycodes[sizeof(_keyReport.keycodes) / sizeof(_keyReport.keycodes[0])];
	size_t numKeysFound = 0;
	// It's a modifier key
	if (k >= KEY_LEFT_CTRL && k <= KEY_RIGHT_GUI)
	{
		// Convert key into bitfield (0 - 7)
		k = KeyboardKeycode(uint8_t(k) - uint8_t(KEY_LEFT_CTRL));
		if (s) {
			_keyReport.modifiers |= (1 << k);
		}
		else {
			_keyReport.modifiers &= ~(1 << k);
		}
		numKeysFound = 1;
	}
	// It's a normal key being pressed
	else {
		// Find the occurrence of k in .keycodes or the first empty slot
		auto p = _keyReport.keycodes;
		while (p < keycodesEnd && *p != k && *p != KEY_RESERVED) {
			++p;
		}

		// if we're pressing the key and we either found it already pressed or found an empty slot
		if (s && p < keycodesEnd) {
			*p = k;
			numKeysFound = 1;
		}
		// else if we're releasing and we found the key
		else if (!s && p < keycodesEnd && *p == k) {
			// Shift the remainder of the array (if any) up a slot
			for (;p + 1 < keycodesEnd && p[1] != KEY_RESERVED; ++p) {
				*p = p[1];
			}
			*p = KEY_RESERVED;
			numKeysFound = 1;
		}
		else {
			numKeysFound = 0;
		}
	}

	return numKeysFound;
}

size_t DefaultKeyboardAPI::removeAll(void)
{
	// Release all keys
	size_t ret = 0;
	for (uint8_t i = 0; i < sizeof(_keyReport.keys); i++)
	{
		// Is a key in the list or did we found an empty slot?
		if(_keyReport.keys[i]){
			ret++;
		}
		_keyReport.keys[i] = 0x00;
	}
	return ret;
}


size_t DefaultKeyboardAPI::write(ConsumerKeycode k)
{
	// Press and release key (if press was successfull)
	auto ret = press(k);
	if(ret){
		release(k);
	}
	return ret;
}


size_t DefaultKeyboardAPI::press(ConsumerKeycode k)
{
	// Press key and send report to host
	auto ret = add(k);
	if(ret){
		send();
	}
	return ret;
}


size_t DefaultKeyboardAPI::release(ConsumerKeycode k) 
{
	// Release key and send report to host
	auto ret = remove(k);
	if(ret){
		send();
	}
	return ret;
}


size_t DefaultKeyboardAPI::add(ConsumerKeycode k) 
{
	// No 2 byte keys are supported
	if(k > 0xFF){
		setWriteError();
		return 0;
	}
	
	// Place the key inside the reserved keyreport position.
	// This does not work on Windows.
	_keyReport.reserved = k;
	return 1;
}


size_t DefaultKeyboardAPI::remove(ConsumerKeycode k) 
{
	// No 2 byte keys are supported
	if(k > 0xFF){
		return 0;
	}
	
	// Always release the key, to make it simpler releasing a consumer key
	// without releasing all other normal keyboard keys.
	_keyReport.reserved = HID_CONSUMER_UNASSIGNED;
	return 1;
}
