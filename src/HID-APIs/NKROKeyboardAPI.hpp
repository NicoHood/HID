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


size_t NKROKeyboardAPI::set(KeyboardKeycode k, bool s) 
{
	// Press keymap key
	if (k < NKRO_KEY_COUNT){
		uint8_t bit = 1 << (uint8_t(k) % 8);
		if(s){
			_keyReport.keys[k / 8] |= bit;
		}
		else{
			_keyReport.keys[k / 8] &= ~bit;
		}
		return 1;
	}

	// It's a modifier key
	else if(k >= KEY_LEFT_CTRL && k <= KEY_RIGHT_GUI)
	{
		// Convert key into bitfield (0 - 7)
		k = KeyboardKeycode(uint8_t(k) - uint8_t(KEY_LEFT_CTRL));
		if(s){
			_keyReport.modifiers |= (1 << k);
		}
		else{
			_keyReport.modifiers &= ~(1 << k);
		}
		return 1;
	}
	
	// Its a custom key (outside our keymap)
	else{
		// Add k to the key report only if it's not already present
		// and if there is an empty slot. Remove the first available key.
		auto key = _keyReport.key;
		
		// Is key already in the list or did we found an empty slot?
		if (s && (key == uint8_t(k) || key == KEY_RESERVED)) {
			_keyReport.key = k;
			return 1;
		}
		
		// Test the key report to see if k is present. Clear it if it exists.
		if (!s && (key == k)) {
			_keyReport.key = KEY_RESERVED;
			return 1;
		}
	}
	
	// No empty/pressed key was found
	return 0;
}

size_t NKROKeyboardAPI::removeAll(void)
{
	// Release all keys
	size_t ret = 0;
	for (uint8_t i = 0; i < sizeof(_keyReport.allkeys); i++)
	{
		// Is a key in the list or did we found an empty slot?
		auto bits = _keyReport.allkeys[i];
		do {
			if(bits & 0x01){
				ret++;
			}
			bits >>=1;
		}
		while(bits);
		_keyReport.allkeys[i] = 0x00;
	}
	return ret;
}

