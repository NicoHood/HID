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

void HIDBridge_::readSerial(void)
{
	static NHP_Read_Data_t n = { 0 };
	uint8_t error = 0x00;

	// read as long as the Serial is available
	// but do not block forever
	rx_buffer_index_t i = 0; //TODO availabel -> read -1
	while (Serial.available()) {
		// read in new Serial byte and process with NHP protocol
		uint8_t b = Serial.read();
		bool newInput = NHPread(b, &n);

		// proceed new valid NHP input
		if (newInput) {
			if (n.mode == NHP_ADDRESS) {
				switch (n.address) {
					// received a control address command
				case HIDBRIDGE_ADDRESS_CONTROL:
					// acknowledge/request
					if (n.data == HIDBRIDGE_CONTROL_ISREADY)
						isReady = true;

					// pause
					else if (n.data == HIDBRIDGE_CONTROL_NOTREADY)
						isReady = false;

					// not
					else
						err(HID_BRIDGE_ERR_CONTROL);

					break;
					// received HID out report TODO
				default:
					err(HID_BRIDGE_ERR_ADDRESS);
					break;
				}
			}
			// received HID out report TODO
			else if (n.mode == NHP_COMMAND) {
				error = 4;
			}
		}

		// NHP reading error
		else if (n.errorLevel) {
			error = 2;
		}

		// do not block forever
		if (++i >= SERIAL_RX_BUFFER_SIZE)
			break;
	}

	if (error){
		err(error);
		isReady = false; // revert
	}
}


bool HIDBridge_::waitForReady(void)
{

	uint32_t currentMillis = millis();
	do{
		// check for new state information
		// maybe the host sended a pause signal
		readSerial();

		// check for timeout //TODO move 1 up?
		if ((millis() - currentMillis) > HIDBRIDGE_TX_TIMEOUT) {
			err(1);
			return false;
		}
	}
	// try to wait for a new request/acknowledge
	while (!isReady)

	return isReady;

	//if (!isReady) { //TODO remove?
	//	// try to wait for a new request/acknowledge
	//	uint32_t currentMillis = millis();
	//	while (!isReady) {
	//		readSerial();
	//		// check for timeout //TODO move 1 up?
	//		if ((millis() - currentMillis) > HIDBRIDGE_TX_TIMEOUT) {
	//			err(1);
	//			return false;
	//		}
	//	}
	//}
	//return true;
}

// overwrites the HID_SendReport function which is empty/not used on a 328/2560
void HID_SendReport(uint8_t reportID, const void* data, int len)
{
	// check the latest request/acknowledge, pause, error
	if (!HIDBridge.waitForReady()){
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

	// need a request/acknowledge next time again
	HIDBridge.isReady = false;
}