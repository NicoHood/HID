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
// HIDBridge TX
//================================================================================

#ifdef HIDBRIDGE_TX

HIDBridge_ HIDBridge;

HIDBridge_::HIDBridge_(void){
	// empty
}

void HIDBridge_::begin(void)
{
	// start the serial at our own baud rate
	HIDBRIDGE_TX_SERIAL.begin(HIDBRIDGE_BAUD);

	// wait for the first request to see if usb device is connected
	available();
}

void HIDBridge_::end(void)
{
	// end the serial transmission and reset our helper values
	HIDBRIDGE_TX_SERIAL.end();
	nhp_read.mode = NHP_RESET;
	isReady = false;
	isConnected = false;
}


void HIDBridge_::err(uint8_t error)
{
	if (!debug)
		return;
	debug->print("Bridge Err TX: ");
	debug->println(error);
}

void HIDBridge_::read(void)
{
	// read as long as the Serial is available
	// but do not block forever
	for (rx_buffer_index_t i = 0; i < SERIAL_RX_BUFFER_SIZE; i++){

		// read in new Serial byte
		int b = HIDBRIDGE_TX_SERIAL.read();
		if (b < 0)
			break;

		// process with NHP protocol
		bool newInput = readNHP(b, &nhp_read);

		// proceed new valid NHP input
		if (newInput) {

			// NHP address contains control data or out report data
			if (nhp_read.mode == NHP_ADDRESS) {

				// received a control address command
				if (nhp_read.address == HIDBRIDGE_ADDRESS_CONTROL) {
					// acknowledge/request
					if (nhp_read.data == HIDBRIDGE_CONTROL_ISREADY){
						isReady = true;
						isConnected = true;
					}

					// pause
					else if (nhp_read.data == HIDBRIDGE_CONTROL_NOTREADY){
						isReady = false;
						isConnected = true;
					}

					// usb device detached
					else if (nhp_read.data == HIDBRIDGE_CONTROL_NOTCONNECTED){
						isReady = false;
						isConnected = false;
					}
					
					// not defined control command
					else
						err(HIDBRIDGE_ERR_CONTROL);
				}

				// received HID out report TODO
				else
					err(HIDBRIDGE_ERR_ADDRESS);
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


bool HIDBridge_::available(void)
{
	// try to wait for a new request/acknowledge
	uint32_t currentMillis = millis();
	do{
		// check for new state information
		// maybe the host sended a pause signal
		read();

		// check for timeout, do not wait longer if usb device is not connected
		if (!isConnected || (millis() - currentMillis) > HIDBRIDGE_TX_TIMEOUT) {
			err(HIDBRIDGE_ERR_TIMEOUT);
			break;
		}
	} while (!isReady);

	return isReady;
}

void HIDBridge_::SendReport(uint8_t reportID, const void* data, int len)
{
	// check the latest request/acknowledge, pause or error
	if (!available()){
		err(HIDBRIDGE_ERR_NOT_RDY);
		return;
	}

	// begin transfer with reportID as command
	HIDBRIDGE_TX_SERIAL.write(writeNHPCommand(reportID));

	// send data in 4 byte packets with the address of the reportID
	// the rest (if any, e.g. with 2 byte) is filled with random bytes
	NHP_Write_Data_t n;
	for (int i = 0; i < len; i += 4) {
		writeNHPAddress(reportID, UINT32_AT_OFFSET(data, i), &n);
		HIDBRIDGE_TX_SERIAL.write(n.writeBuffer, n.writeLength);
	}

	// end transfer with zero command
	HIDBRIDGE_TX_SERIAL.write(writeNHPCommand(0));

	// need a request/acknowledge next time again
	isReady = false;

	err(42);
}

// overwrites the HID_SendReport function which is empty/not used on a 328/2560
void HID_SendReport(uint8_t reportID, const void* data, int len)
{
	HIDBridge.SendReport(reportID, data, len);
}

#endif // #ifdef HIDBRIDGE_TX

//================================================================================
// HIDBridge RX
//================================================================================

#ifdef HIDBRIDGE_RX

#endif // #ifdef HIDBRIDGE_RX