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
	// Force API to send a clean report.
	// This is important for and HID bridge where the receiver stays on,
	// while the sender is resetted.
	removeAll();
	send();
}


void KeyboardAPI::end(void)
{
	releaseAll();
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


size_t KeyboardAPI::press(KeyboardKeycode k) 
{
	// Press key and send report to host
	auto ret = add(k);
	if(ret){
		send();
	}
	return ret;
}


size_t KeyboardAPI::release(KeyboardKeycode k) 
{
	// Release key and send report to host
	auto ret = remove(k);
	if(ret){
		send();
	}
	return ret;
}


size_t KeyboardAPI::add(KeyboardKeycode k) 
{
	// Add key to report
	return set(k, true);
}


size_t KeyboardAPI::remove(KeyboardKeycode k) 
{
	// Remove key from report
	return set(k, false);
}


size_t KeyboardAPI::releaseAll(void)
{
	// Release all keys
	auto ret = removeAll();
	if(ret){
		send();
	}
	return ret;
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


size_t KeyboardAPI::press(uint8_t k) 
{
	// Press key and send report to host
	auto ret = add(k);
	if(ret){
		send();
	}
	return ret;
}


size_t KeyboardAPI::release(uint8_t k) 
{
	// Release key and send report to host
	auto ret = remove(k);
	if(ret){
		send();
	}
	return ret;
}


size_t KeyboardAPI::add(uint8_t k) 
{
	// Add key to report
	return set(k, true);
}


size_t KeyboardAPI::remove(uint8_t k) 
{
	// Remove key from report
	return set(k, false);
}


size_t KeyboardAPI::set(uint8_t k, bool s){
	// Ignore invalid input
	if(k >= sizeof(_asciimap)/sizeof(_asciimap[0])){
		setWriteError();
		return 0;
	}

	// Read key from ascii lookup table
	uint16_t key = pgm_read_word(_asciimap + k);
	auto ret = set(KeyboardKeycode((uint8_t)(key & 0xFF)), s);
	
	// Only add modifier if keycode was successfully added before.
	// Always try to release modifier (if used).
	if(ret || !s){
		if (key & MOD_LEFT_CTRL) {
			ret |= set(KEY_LEFT_CTRL, s);
		}
		if (key & MOD_LEFT_SHIFT) {
			ret |= set(KEY_LEFT_SHIFT, s);
		}
		if (key & MOD_LEFT_ALT) {
			ret |= set(KEY_LEFT_ALT, s);
		}
		if (key & MOD_LEFT_GUI) {
			ret |= set(KEY_LEFT_GUI, s);
		}
		if (key & MOD_RIGHT_CTRL) {
			ret |= set(KEY_RIGHT_CTRL, s);
		}
		if (key & MOD_RIGHT_SHIFT) {
			ret |= set(KEY_RIGHT_SHIFT, s);
		}
		if (key & MOD_RIGHT_ALT) {
			ret |= set(KEY_RIGHT_ALT, s);
		}
		if (key & MOD_RIGHT_GUI) {
			ret |= set(KEY_RIGHT_GUI, s);
		}
	}
	

	return ret;
}

