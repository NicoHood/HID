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

bool HIDBridge_::begin(Stream &s)
{
	begin((Stream*)&s);
}

bool HIDBridge_::begin(Stream* s)
{
	HIDStream = s;
}


void HIDBridge_::err(uint8_t error)
{
	if (!debug)
		return;
	debug->println("Softserial");
	debug->println(error);
}

void HIDBridge_::readSerial(void)
{
	// read as long as the Serial is available
	// but do not block forever
	for (rx_buffer_index_t i = 0; i < SERIAL_RX_BUFFER_SIZE; i++){
		// read in new Serial byte
		int b = Serial.read();
		if (b < 0)
			break;

		// process with NHP protocol
		bool newInput = NHPread(b, &nhp_read);

		// proceed new valid NHP input
		if (newInput) {
			if (nhp_read.mode == NHP_ADDRESS) {
				switch (nhp_read.address) {
					// received a control address command
				case HIDBRIDGE_ADDRESS_CONTROL:
					// acknowledge/request
					if (nhp_read.data == HIDBRIDGE_CONTROL_ISREADY)
						isReady = true;

					// pause
					else if (nhp_read.data == HIDBRIDGE_CONTROL_NOTREADY)
						isReady = false;

					// not
					else
						err(HIDBRIDGE_ERR_CONTROL);

					break;
					// received HID out report TODO
				default:
					err(HIDBRIDGE_ERR_ADDRESS);
					break;
				}
			}
			// received HID out report TODO
			else if (nhp_read.mode == NHP_COMMAND) {
				err(HIDBRIDGE_ERR_COMMAND);
			}
		}

		// NHP reading error
		else if (nhp_read.errorLevel) {
			err(HIDBRIDGE_ERR_NHP_ERR);
			// do not change isReady state because of a possible full buffer
			// which causes NHP corruption
		}
	}
}


bool HIDBridge_::waitForReady(void)
{
	// try to wait for a new request/acknowledge
	uint32_t currentMillis = millis();
	do{
		// check for new state information
		// maybe the host sended a pause signal
		readSerial();

		// check for timeout
		if ((millis() - currentMillis) > HIDBRIDGE_TX_TIMEOUT) {
			err(HIDBRIDGE_ERR_TIMEOUT);
			break;
		}
	} while (!isReady); //TODO andn no error in readSerial?

	return isReady;
}

void HIDBridge_::SendReport(uint8_t reportID, const void* data, int len)
{
	// check if stream pointer is set
	if (!HIDStream){
		err(HIDBRIDGE_ERR_NO_SPTR);
		return;
	}

	// check the latest request/acknowledge,a pause, error
	if (!waitForReady()){
		err(HIDBRIDGE_ERR_NOT_RDY);
		return;
	}

	// begin transfer with reportID as command
	HIDStream->write(NHPwriteCommand(reportID));

	// send data in 4 byte packets with the address of the reportID
	// the rest (if any, e.g. with 2 byte) is filled with random bytes
	NHP_Write_Data_t n;
	for (int i = 0; i < len; i += 4) {
		NHPwriteAddress(reportID, UINT32_AT_OFFSET(data, i), &n);
		HIDStream->write(n.writeBuffer, n.writeLength);
	}

	// end transfer with zero command
	HIDStream->write(NHPwriteCommand(0));

	// need a request/acknowledge next time again
	isReady = false;

	err(42);
}

// overwrites the HID_SendReport function which is empty/not used on a 328/2560
void HID_SendReport(uint8_t reportID, const void* data, int len)
{
	HIDBridge.SendReport(reportID, data, len);
}