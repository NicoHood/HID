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

void KeyboardAPI::begin(void)
{
	releaseAll();
}


void KeyboardAPI::end(void)
{
	releaseAll();
}


size_t KeyboardAPI::write(uint8_t k)
{	
	// Press and release key (if press was successfull)
	auto ret = press(k);
	if(ret){
		release(k);
	}
	return ret;
}


size_t KeyboardAPI::write(KeyboardKeycode k)
{	
	// Press and release key (if press was successfull)
	auto ret = press(k);
	if(ret){
		release(k);
	}
	return ret;
}


size_t KeyboardAPI::write(KeyboardModifier k)
{	
	// Press and release key (if press was successfull)
	auto ret = press(k);
	if(ret){
		release(k);
	}
	return ret;
}


size_t KeyboardAPI::write(ConsumerKeycode k)
{
	// Press and release key (if press was successfull)
	auto ret = press(k);
	if(ret){
		release(k);
	}
	return ret;
}


size_t KeyboardAPI::press(uint8_t k) 
{
	// Press key and send report to host
	auto ret = add(k);
	if(ret){
		send_now();
	}
	return ret;
}


size_t KeyboardAPI::press(KeyboardKeycode k) 
{
	// Press key and send report to host
	auto ret = add(k);
	if(ret){
		send_now();
	}
	return ret;
}


size_t KeyboardAPI::press(KeyboardModifier k) 
{
	// Press modifier key and send report to host
	auto ret = add(k);
	if(ret){
		send_now();
	}
	return ret;
}


size_t KeyboardAPI::press(ConsumerKeycode k)
{
	// Press key and send report to host
	auto ret = add(k);
	if(ret){
		send_now();
	}
	return ret;
}


size_t KeyboardAPI::add(uint8_t k) 
{
	// Ignore invalid input
	if(k >= sizeof(_asciimap)){
		setWriteError();
		return 0;
	}

	// Read key from ascii lookup table
	k = pgm_read_byte(_asciimap + k);
	auto ret = add(KeyboardKeycode(k & ~SHIFT));
	
	// Only press shift and send if keycode was successfully added
	if(ret && k & SHIFT){
		add(KEY_LEFT_SHIFT);
	}
	return ret;
}


size_t KeyboardAPI::add(KeyboardKeycode k) 
{
	// Add k to the key report only if it's not already present
	// and if there is an empty slot.
	for (uint8_t i = 0; i < sizeof(_keyReport.keys); i++)
	{
		// Is key already in the list or did we found an empty slot?
		auto key = _keyReport.keys[i];
		if (key == uint8_t(k) || key == KEY_RESERVED) {
			_keyReport.keys[i] = k;
			return 1;
		}
	}
	
	// No empty key position was found
	setWriteError();
	return 0;
}


size_t KeyboardAPI::add(KeyboardModifier k) 
{
	// Add modifier key
	_keyReport.modifiers |= k;
	return 1;
}


size_t KeyboardAPI::add(ConsumerKeycode k) 
{
	if(k > 0xFF){
		// No 2 byte keys are supported
		setWriteError();
		return 0;
	}
	
	// Place the key inside the reserved keyreport position.
	// This does not work on Windows.
	_keyReport.reserved = k;
	return 1;
}


size_t KeyboardAPI::release(uint8_t k) 
{
	// Release key and send report to host
	auto ret = remove(k);
	if(ret){
		send_now();
	}
	return ret;
}


size_t KeyboardAPI::release(KeyboardKeycode k) 
{
	// Release key and send report to host
	auto ret = remove(k);
	if(ret){
		send_now();
	}
	return ret;
}


size_t KeyboardAPI::release(KeyboardModifier k) 
{
	// Release modifier key and send report to host
	auto ret = remove(k);
	if(ret){
		send_now();
	}
	return ret;
}


size_t KeyboardAPI::release(ConsumerKeycode k) 
{
	// Release key and send report to host
	auto ret = remove(k);
	if(ret){
		send_now();
	}
	return ret;
}


size_t KeyboardAPI::remove(uint8_t k) 
{
	// Ignore invalid input
	if(k >= sizeof(_asciimap)){
		return 0;
	}

	// Read key from ascii lookup table
	k = pgm_read_byte(_asciimap + k);
	auto ret = remove(KeyboardKeycode(k & ~SHIFT));
	
	// Always try to release shift (if used)
	if(k & SHIFT){
		ret |= remove(KEY_LEFT_SHIFT);
	}
	return ret;
}


size_t KeyboardAPI::remove(KeyboardKeycode k) 
{
	// Test the key report to see if k is present. Clear it if it exists.
	for (uint8_t i = 0; i < 6; i++) {
		if (_keyReport.keys[i] == k) {
			_keyReport.keys[i] = KEY_RESERVED;
			return 1;
		}
	}
	
	// No pressed key was found
	return 0;
}


size_t KeyboardAPI::remove(KeyboardModifier k) 
{
	// Release modifier key
	auto oldModifier = _keyReport.modifiers;
	_keyReport.modifiers &= ~k;
	
	// Check if we actually released a key
	if(_keyReport.modifiers != oldModifier){
		return 1;
	}
	return 0;
}


size_t KeyboardAPI::remove(ConsumerKeycode k) 
{
	if(k > 0xFF){
		// No 2 byte keys are supported
		return 0;
	}
	
	// Always release the key, to make it simpler releasing a consumer key
	// without releasing all other normal keyboard keys.
	_keyReport.reserved = HID_CONSUMER_UNASSIGNED;
	return 1;
}


void KeyboardAPI::releaseAll(void)
{
	// Release all keys
	removeAll();
	send_now();
}


void KeyboardAPI::removeAll(void)
{
	// Release all keys
	memset(&_keyReport, 0x00, sizeof(_keyReport));
}


void KeyboardAPI::send_now(void){
	SendReport(&_keyReport, sizeof(_keyReport));
}


void KeyboardAPI::wakeupHost(void){
#ifdef USBCON
	USBDevice.wakeupHost();
#endif
}


