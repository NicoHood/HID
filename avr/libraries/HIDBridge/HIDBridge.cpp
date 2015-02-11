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

#include "HIDBridge.h"

//================================================================================
// HIDBridge
//================================================================================

HIDBridge_ HIDBridge;

HIDBridge_::HIDBridge_(void){
	// empty
}

bool HIDBridge_::begin(void)
{

}

void HIDBridge_::err(uint8_t error)
{

}

void HIDBridge_::task(void)
{
	static NHP_Read_Data_t n = { 0 };
	uint8_t error = 0x00;

	while (Serial.available()) {
		if (NHPread(Serial.read(), &n)) {
			if (n.mode == NHP_ADDRESS) {
				switch (n.address) {
				case 0:
					// received a control address command
					if (n.data == 0) {
						isReady = true;
						return;
					}
					else
						error = 3;
					break;
				default:
					error = 1;
					break;

				}
			}
			else  if (n.mode == NHP_COMMAND) {

			}
			else {
				error = 2;
			}

		}
	}

	if (error)
		err(error);
}

bool HIDBridge_::ready(void)
{
	//if (!hidReady) {
	//	// try to wait for a new request/acknowledge
	//	uint32_t currentMillis = millis();
	//	while (!hidReady) {
	//		readHIDReady();
	//		if ((millis() - currentMillis) > 1000) {
	//			errorHID(0);
	//			return;
	//		}
	//	}
	//}
}

// overwrites the HID_SendReport function which is empty/not used on a 328/2560
void HID_SendReport(uint8_t reportID, const void* data, int len)
{
	// check if we got a request/acknowledge
	if (!HIDBridge.ready()){
		HIDBridge.err(0);
		return;
	}

	// begin transfer with reportID as command
	Serial.write(NHPwriteCommand(reportID));

	// send data in 4 byte packets with the address of the reportID
	// the rest (if any, e.g. with 2 byte) is filled with random bytes
	NHP_Write_Data_t n;
	for (int i = 0; i < len; i += 4) {
		NHPwriteAddress(reportID, UINT32_AT_OFFSET(data, i), &n);
		Serial.write(n.writeBuffer, n.writeLength);
	}

	// end transfer with zero command
	Serial.write(NHPwriteCommand(0));
}