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

HIDBridge_ HIDBridge;

HIDBridge_::HIDBridge_(void){
	// empty
}

void HIDBridge_::begin(void)
{
	// start the serial at our own baud rate
	HIDBRIDGE_SERIAL.begin(HIDBRIDGE_BAUD);

	rxReady = true;
	txReady = false; //move to end?

	// wait for/send the first request to see if usb device is connected
	available();
}

void HIDBridge_::end(void)
{
	// end the serial transmission and reset our helper values
	HIDBRIDGE_SERIAL.end();
	nhp_read.mode = NHP_RESET;
	rxReady = false; //TODO
	isConnected = false;
	//TODO reset more stuff
}


void HIDBridge_::err(uint8_t error)
{
	if (!debug)
		return;
	debug->print("err");
	debug->println(error);
}


void HIDBridge_::writeState(void) {
	// send the current state to the other mcu
	NHP_Write_Data_t n;
	writeNHPAddress(HIDBRIDGE_CONTROL_ADDRESS, rxReady, &n);
	HIDBRIDGE_SERIAL.write(n.writeBuffer, n.writeLength);

	// save new timeout
	writeTimeout = millis();
}

void HIDBridge_::task(void){
	//TODO implement Serialevent strong for this task?
#ifdef HIDBRIDGE_RX
	// if hid request timed out, send a new one
	// this is important if the main mcu gets a reset or misses an acknowledge
	uint32_t currentMillis = millis();
	if ((currentMillis - writeTimeout) > HIDBRIDGE_TX_TIMEOUT) {
		writeState();
		// do not write timeout value, will be written in the function above
#ifdef USB_DEBUG
		debug->println("ack 1s");
#endif
	}
#endif

	// read in new controls or data
	read();
}

void HIDBridge_::read(void)
{
	// check for read timeout only if really needed
	if (!nhp_read.mode){
		if (millis() - readTimeout > HIDBRIDGE_RX_TIMEOUT) {
			// reset reportID and NHP if we have a timeout
			reportID = 0;
			nhp_read.mode = NHP_RESET;
			err(HIDBRIDGE_ERR_READ_TO);
		}
	}

	// read as long as the Serial is available
	// but do not block forever
	rx_buffer_index_t i;
	for (i = 0; i < SERIAL_RX_BUFFER_SIZE; i++){

		// read in new Serial byte
		int b = HIDBRIDGE_SERIAL.read();
		if (b < 0)
			break;

		// process with NHP protocol
		if (readNHP(b, &nhp_read)) {

			// command indicates a new hidReport (command==reportID) or the end (command==0)
			if (nhp_read.mode == NHP_COMMAND)
				proceedCommand();

			// NHP address contains control data or hid in/out report data
			else if (nhp_read.mode == NHP_ADDRESS)
				proceedAddress();
		}

		// NHP reading error
		else if (nhp_read.errorLevel) {
			// ASCII
			if (b < 128) {
				// possible main mcu reset
				if (!b)
					err(HIDBRIDGE_ERR_MCU_RST);
				else { //TODO different errors?
					err(HIDBRIDGE_ERR_SERIALB);
				}
			}
			else
				err(HIDBRIDGE_ERR_SERIALB);

			// do not change rxReady state because of a possible full buffer
			// which causes NHP corruption
			err(HIDBRIDGE_ERR_NHP_ERR);
		}
	} // end of for reading loop

	// save new time
	if (i)		
		readTimeout = millis();
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
	} while (!txReady);

	return txReady;
}


void HIDBridge_::proceedCommand(void){
#ifdef DEBUG
	debug->print("c");
	debug->println(nhp_read.command);
#endif

#ifdef HIDBRIDGE_RX
	// proceed a possible end flag
	if (nhp_read.command == HIDBRIDGE_COMMAND_END) {

		// we've got a correct USB protocol received. Write it to the host now.
		if (reportID && (recvLength == reportLength)) {
			rxReady = false; //TODO not needed?
#ifdef USB_DEBUG
			// debug print HID reports
			debug->print("USBk ");
			debug->print(reportID, DEC);
			for (uint8_t i = 0; i < reportLength; i++) {
				debug->print(", 0x");
				debug->print(hidReport[i], HEX);
			}
			debug->println();
#endif
			HID_SendReport(reportID, hidReport, reportLength);

			// acknowledge signal
			rxReady = true;
			writeState();
		}
		// log an error
		else
			err(HIDBRIDGE_ERR_CMD_END);

		// reset reportID in any case
		reportID = 0;
	}

	// proceed a possible new reportID lead
	else {
		// flag an error if we have a pending report
		if (reportID)
			err(HIDBRIDGE_ERR_CMD_RID);

		// determine the new report length
		switch (nhp_read.command) { //TODO progmem lookup table
#ifdef HID_MOUSE_ENABLE
		case HID_REPORTID_MOUSE:
			reportLength = sizeof(HID_MouseReport_Data_t);
			break;
#endif

#ifdef HID_MOUSE_ABSOLUTE_ENABLE
		case HID_REPORTID_MOUSE_ABSOLUTE:
			reportLength = sizeof(HID_MouseAbsoluteReport_Data_t);
			break;
#endif

#ifdef HID_KEYBOARD_ENABLE
		case HID_REPORTID_KEYBOARD:
			reportLength = sizeof(HID_KeyboardReport_Data_t);
			break;
#endif

#ifdef HID_CONSUMERCONTROL_ENABLE
		case HID_REPORTID_CONSUMERCONTROL:
			reportLength = sizeof(HID_ConsumerControlReport_Data_t);
			break;
#endif

#ifdef HID_SYSTEMCONTROL_ENABLE
		case HID_REPORTID_SYSTEMCONTROL:
			reportLength = sizeof(HID_SystemControlReport_Data_t);
			break;
#endif

#ifdef HID_GAMEPAD_ENABLE
		case HID_REPORTID_GAMEPAD:
			reportLength = sizeof(HID_GamepadReport_Data_t);
			break;
#endif

		default:
			// error
			reportLength = 0;
			break;
		}

		if (reportLength) {
			// save new report properties
			reportID = nhp_read.command;
			recvLength = 0;
		}
		else {
			// new reportID is not supported
			//TODO recv length =0?
			reportID = 0;
			err(HIDBRIDGE_ERR_COMMAND);
		}
	}
#else // ifdef HIDBRIDGE_RX
	err(HIDBRIDGE_ERR_COMMAND);
#endif
}


void HIDBridge_::proceedAddress(void){
#ifdef DEBUG
	debug->print("a");
	debug->print(nhp_read.address);
	debug->print(", ");
	debug->println(nhp_read.data, HEX);
#endif

	// received a control address
	if (nhp_read.address == HIDBRIDGE_CONTROL_ADDRESS) {
		reportID = 0;

		// acknowledge/request
		if (nhp_read.data == HIDBRIDGE_CONTROL_READY){
			txReady = true;
			isConnected = true;
		}

		// pause
		else if (nhp_read.data == HIDBRIDGE_CONTROL_NOTREADY){
			txReady = false;
			isConnected = true;
		}

		// usb device detached
		else if (nhp_read.data == HIDBRIDGE_CONTROL_NOTCONNECTED){
			txReady = false;
			isConnected = false;
		}

		// not defined control command
		else
			err(HIDBRIDGE_ERR_CONTROL);
	}
#ifdef HIDBRIDGE_RX
	// received correct reportID (in/out)
	else if (reportID && (reportID == nhp_read.address) && (recvLength < reportLength)) {
		for (uint8_t i = 0; i < 4; i++) {
			// save hidReport
			hidReport[recvLength++] = nhp_read.data8[i];

			// abort if report finished
			if (recvLength == reportLength)
				break;
		}
	}
#endif
	// received wrong data: lead command missing/wrong reportID/report too long
	else {
		reportID = 0;
		err(HIDBRIDGE_ERR_ADDRESS);
	}
}


void HIDBridge_::SendReport(uint8_t reportID, const void* data, int len)
{
	// check the latest request/acknowledge, pause or error
	if (!available()){
		err(HIDBRIDGE_ERR_NOT_RDY);
		return;
	}

	// begin transfer with reportID as command
	HIDBRIDGE_SERIAL.write(writeNHPCommand(reportID));

	// send data in 4 byte packets with the address of the reportID
	// the rest (if any, e.g. with 2 byte) is filled with random bytes
	NHP_Write_Data_t n;
	for (int i = 0; i < len; i += 4) {
		writeNHPAddress(reportID, UINT32_AT_OFFSET(data, i), &n);
		HIDBRIDGE_SERIAL.write(n.writeBuffer, n.writeLength);
	}

	// end transfer with zero command
	HIDBRIDGE_SERIAL.write(writeNHPCommand(0));

	// need a request/acknowledge next time again
	txReady = false;

	err(42);
}

//================================================================================
// Strong function implementations
//================================================================================

// IO MCU only
#ifdef HIDBRIDGE_IO
#ifdef HIDBRIDGE_TX
// overwrites the HID_SendReport function which is empty/not used on a 328/2560
void HID_SendReport(uint8_t reportID, const void* data, int len)
{
	HIDBridge.SendReport(reportID, data, len);
}
#endif
#endif // #ifdef HIDBRIDGE_IO


#ifdef HIDBRIDGE_USE_SERIAL_EVENT
/*
SerialEvent occurs whenever a new data comes in the
hardware serial RX.  This routine is run between each
time loop() runs, so using delay inside loop can delay
response.  Multiple bytes of data may be available.
*/
void HIDBRIDGE_SERIAL_EVENT(void) {
	HIDBridge.task();
	Serial.println("kk");
}
#endif
