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
	// It's a modifier key
	if(k >= KEY_LEFT_CTRL && k <= KEY_RIGHT_GUI)
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
	// Its a normal key
	else{
		// get size of keycodes during compile time
		const uint8_t keycodesSize = sizeof(_keyReport.keycodes);

		// if we are adding an element to keycodes
		if (s){
			// iterate through the keycodes
			for (uint8_t i = 0; i < keycodesSize; i++)
			{
				auto key = _keyReport.keycodes[i];

				// write to keycodes on first instance of k or null in keycodes
				if (key == uint8_t(k) || key == KEY_RESERVED) {
					_keyReport.keycodes[i] = k;
					return 1;
				}
			}
		} else { // we are removing k from keycodes
			// this will replace the first instance of k with the last entry in the pseudo-linkedlist

			uint8_t keyIndex = 255; // if keyIndex == 255 then k does not exist in keycodes

			// iterate through the keycodes
			for (uint8_t i = 0; i < keycodesSize; i++)
			{
				auto key = _keyReport.keycodes[i];

				// if target key is found
				if (key == uint8_t(k)) {
					// record target key index to keyIndex;
					keyIndex = i;
					break;
				}
			}

			// if the target key is found (AKA if there is a key to remove)
			if (keyIndex != 255)
			{
				// iterate through the keycodes from the back
				KeyboardKeycode lastElement;
				for (uint8_t i = keycodesSize; i > 0; --i)
				{
					// slot is occupied
					if (_keyReport.keycodes[i] != KEY_RESERVED)
					{
						_keyReport.keycodes[i] = KEY_RESERVED; // remove last element

						// target key is the last non-null element in the pseudo-linkedlist
						if (i == keyIndex)
						{
							return 1; // no further operations needed, exit now
						}
						lastElement = _keyReport.keycodes[i]; // copy current element to temp
						break;
					}
				}
				_keyReport.keycodes[keyIndex] = lastElement; // replace k with last element
				return 1;
			}
		}
	}
	// No empty/pressed key was found
	return 0;
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
