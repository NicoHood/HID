/*
Copyright (c) 2014 NicoHood
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

/** \file
*
*  Main source file for the VirtualSerialMouse demo. This file contains the main tasks of
*  the demo and is responsible for the initial application hardware configuration.
*/

#include "Hoodloader.h"


/** Circular buffer to hold data from the host before it is sent to the device via the serial port. */
//new important ram fix!! <--
static RingBuff_t USBtoUSART_Buffer;

/** Circular buffer to hold data from the serial port before it is sent to the host. */
static RingBuff_t USARTtoUSB_Buffer;

/** Pulse generation counters to keep track of the number of milliseconds remaining for each pulse type */
//new important ram fix!! <--
static volatile struct
{
	uint8_t TxLEDPulse; /**< Milliseconds remaining for data Tx LED pulse */
	uint8_t RxLEDPulse; /**< Milliseconds remaining for data Rx LED pulse */
	uint8_t PingPongLEDPulse; /**< Milliseconds remaining for enumeration Tx/Rx ping-pong LED pulse */
} PulseMSRemaining;


/** LUFA CDC Class driver interface configuration and state information. This structure is
*  passed to all CDC Class driver functions, so that multiple instances of the same class
*  within a device can be differentiated from one another.
*/
USB_ClassInfo_CDC_Device_t VirtualSerial_CDC_Interface =
{
	.Config =
	{
		.ControlInterfaceNumber         = INTERFACE_ID_CDC_CCI,
		.DataINEndpoint                 =
		{
			.Address                = CDC_TX_EPADDR,
			.Size                   = CDC_TXRX_EPSIZE,
			.Banks                  = 1,
		},
		.DataOUTEndpoint                =
			{
				.Address                = CDC_RX_EPADDR,
				.Size                   = CDC_TXRX_EPSIZE,
				.Banks                  = 1,
			},
			.NotificationEndpoint           =
				{
					.Address                = CDC_NOTIFICATION_EPADDR,
					.Size                   = CDC_NOTIFICATION_EPSIZE,
					.Banks                  = 1,
				},
	},
};

/** Buffer to hold the previously generated HID report, for comparison purposes inside the HID class driver. */
static uint8_t PrevHIDReportBuffer[sizeof(HID_HIDReport_Data_t)];
static uint8_t CurrentHIDReportBuffer[sizeof(HID_HIDReport_Data_t)];

static struct{
	// variable to perform a "HID flush" and to indicate what report should be written down
	uint8_t ID;
	// length of the report
	uint8_t length;
	// number of bytes received
	uint8_t recvlength;
	// should the report been written even if nothing changed? important for mouse
	bool forcewrite;
} HIDReportState;

/** LUFA HID Class driver interface configuration and state information. This structure is
*  passed to all HID Class driver functions, so that multiple instances of the same class
*  within a device can be differentiated from one another.
*/
USB_ClassInfo_HID_Device_t Device_HID_Interface =
{
	.Config =
	{
		.InterfaceNumber              = INTERFACE_ID_HID,
		.ReportINEndpoint             =
		{
			.Address              = HID_IN_EPADDR,
			.Size                 = HID_EPSIZE,
			.Banks                = 1,
		},
		.PrevReportINBuffer           = PrevHIDReportBuffer,
		.PrevReportINBufferSize       = sizeof(PrevHIDReportBuffer),
	},
};

/** Main program entry point. This routine contains the overall program flow, including initial
*  setup of all components and the main program loop.
*/
int main(void)
{
	SetupHardware();

	RingBuffer_InitBuffer(&USBtoUSART_Buffer);
	RingBuffer_InitBuffer(&USARTtoUSB_Buffer);

	GlobalInterruptEnable();

	// Protocolsetup
	HIDReportState.recvlength=0;
	HIDReportState.ID=0;

	// Debug
	DDRB |= 0x08; //led out
	DDRB |= 0x02; //led out

	for (;;)
	{
		/* Only try to read in bytes from the CDC interface if the transmit buffer is not full */
		if (!(RingBuffer_IsFull(&USBtoUSART_Buffer)))
		{	
			int16_t ReceivedByte = CDC_Device_ReceiveByte(&VirtualSerial_CDC_Interface);

			/* Read bytes from the USB OUT endpoint into the USART transmit buffer */
			if (!(ReceivedByte < 0))
				RingBuffer_Insert(&USBtoUSART_Buffer, ReceivedByte);
		}

		/* Check if the UART receive buffer flush timer has expired or the buffer is nearly full */
		RingBuff_Count_t BufferCount = RingBuffer_GetCount(&USARTtoUSB_Buffer);
		if ((TIFR0 & (1 << TOV0)) || (BufferCount > BUFFER_NEARLY_FULL))
		{
			TIFR0 |= (1 << TOV0);

			if (USARTtoUSB_Buffer.Count) {
				LEDs_TurnOnLEDs(LEDMASK_TX);
				PulseMSRemaining.TxLEDPulse = TX_RX_LED_PULSE_MS;
			}

			/* Read bytes from the USART receive buffer*/
			while (BufferCount--){
				//new Protocol check<--
				// if a reading finished succesfull without valid checksum or an error occured (ignore a reset)
				if(NHPgetErrorLevel()&(~NHP_INPUT_RESET)){
					// check if previous reading was a valid Control Address and write it down
					if(HIDReportState.ID)
						checkNHPControlAddressError();

					// Write the last invalid signals. This will not write a possible new lead to keep
					// it for the next reading. This is implemented in the Protocol itself.
					writeNHPreadBuffer(NHPreadlength);
				}	

				//read newest byte and check for Protocol
				RingBuff_Data_t  b = RingBuffer_Remove(&USARTtoUSB_Buffer);
				checkNHPProtocol(b);
			}

			// if reading has timed out write the buffers down the serial and turn off the led
			if (PulseMSRemaining.TxLEDPulse && !(--PulseMSRemaining.TxLEDPulse)){

				// check if previous reading was a valid Control Address and write it down
				if(HIDReportState.ID)
					checkNHPControlAddressError();

				// only write if there is input (ignore a reset)
				if(!(NHPgetErrorLevel() & NHP_INPUT_RESET)){
					// Lead errors are not in the buff length to keep them for next reading.
					// But we want to write it down now after timeout.
					uint8_t len= NHPreadlength;
					if(NHPgetErrorLevel()& NHP_ERR_LEAD) len++;
					writeNHPreadBuffer(len);
				}
				// do not write again in the while loop above anyways
				NHPreset();

				/* Turn off TX LED(s) once the TX pulse period has elapsed */
				LEDs_TurnOffLEDs(LEDMASK_TX);
			}

			/* Turn off RX LED(s) once the RX pulse period has elapsed */
			if (PulseMSRemaining.RxLEDPulse && !(--PulseMSRemaining.RxLEDPulse))
				LEDs_TurnOffLEDs(LEDMASK_RX);
		}

		/* Load the next byte from the USART transmit buffer into the USART */
		if (!(RingBuffer_IsEmpty(&USBtoUSART_Buffer))) {
			Serial_SendByte(RingBuffer_Remove(&USBtoUSART_Buffer)); //<--new syntax

			LEDs_TurnOnLEDs(LEDMASK_RX);
			PulseMSRemaining.RxLEDPulse = TX_RX_LED_PULSE_MS;
		}

		//new Send reports <--
		CDC_Device_USBTask(&VirtualSerial_CDC_Interface);
		USB_USBTask();
	}
}

/** Configures the board hardware and chip peripherals for the demo's functionality. */
void SetupHardware(void)
{
	/* Disable watchdog if enabled by bootloader/fuses */
	MCUSR &= ~(1 << WDRF);
	wdt_disable();

	/* Hardware Initialization */
	Serial_Init(115200, true);

	/* Must turn off USART before reconfiguring it, otherwise incorrect operation may occur */
	// Added for correct Serial connection at baud 115200 <--
	PORTD |= (1 << PD3); // Turn ON Tx while USART is being reconfigured
	UCSR1B = 0;
	UCSR1A = 0;
	UCSR1C = 0;

	UCSR1C = ((1 << UCSZ11) | (1 << UCSZ10)); //C: 0x06
	UCSR1A = (1 << U2X1); //A: 0x02
	UCSR1B = ((1 << RXCIE1) | (1 << TXEN1) | (1 << RXEN1)); //B: 0x98
	PORTD &= ~(1 << PD3); // And turn OFF Tx once USART has been reconfigured (this is overridden by TXEN)

	LEDs_Init();
	USB_Init();

	/* Start the flush timer so that overflows occur rapidly to push received bytes to the USB interface */
	TCCR0B = (1 << CS02);

	/* Pull target /RESET line high */
	AVR_RESET_LINE_PORT |= AVR_RESET_LINE_MASK;
	AVR_RESET_LINE_DDR  |= AVR_RESET_LINE_MASK;

	// Hardwaresetup to turn off the HID function with shorting the MOSI pin with GND next to it
	AVR_NO_HID_DDR &= ~AVR_NO_HID_MASK; // Input
	AVR_NO_HID_PORT |= AVR_NO_HID_MASK; // Pullup
}

/** Writes the NHP read buffer with the given length */
void writeNHPreadBuffer(uint8_t length){
	for(int i=0; i<length;i++){
		bool CurrentDTRState = (VirtualSerial_CDC_Interface.State.ControlLineStates.HostToDevice & CDC_CONTROL_LINE_OUT_DTR); //new <--
		if(CurrentDTRState)
			CDC_Device_SendByte(&VirtualSerial_CDC_Interface, NHPreadbuffer[i]);
	}
}

/** Checks for a valid protocol input and writes HID report */
void checkNHPProtocol(RingBuff_Data_t input){
	if(NHPreadChecksum(input)){
		// only process signal if HID is turned on
		// make sure that no report is still active (like holding down a keyboard key)!
		// remove later? <--
		if(!(AVR_NO_HID_PIN & AVR_NO_HID_MASK))
			return;

		// nearly the same priciple like the Protocol itself: check for control address
		if(NHPgetAddress()==NHP_ADDRESS_CONTROL && NHPgetChecksumData1() & NHP_USAGE_ARDUINOHID){

			// check if previous reading was a valid Control Address and write it down
			if(HIDReportState.ID)
				checkNHPControlAddressError();

			// get the new report ID and reset the buffer
			HIDReportState.ID = NHPgetChecksumData0();
			HIDReportState.recvlength=0;
			memset(CurrentHIDReportBuffer, 0, sizeof(CurrentHIDReportBuffer));

			/* Determine which interface must have its report generated */
			switch(HIDReportState.ID){
			case HID_REPORTID_MouseReport:
				HIDReportState.length=sizeof(HID_MouseReport_Data_t);
				HIDReportState.forcewrite=true;
				break;

			case HID_REPORTID_KeyboardReport:
				HIDReportState.length=sizeof(HID_KeyboardReport_Data_t);
				HIDReportState.forcewrite=false;
				break;

			case HID_REPORTID_MediaReport:
				HIDReportState.length=sizeof(HID_MediaReport_Data_t);
				HIDReportState.forcewrite=false;
				break;

			case HID_REPORTID_SystemReport:
				HIDReportState.length=sizeof(HID_SystemReport_Data_t);
				HIDReportState.forcewrite=false;
				break;

			case HID_REPORTID_Gamepad1Report:
			case HID_REPORTID_Gamepad2Report:
				HIDReportState.length=sizeof(HID_GamepadReport_Data_t);
				HIDReportState.forcewrite=false;
				break;

			case HID_REPORTID_Joystick1Report:
			case HID_REPORTID_Joystick2Report:
				HIDReportState.length=sizeof(HID_JoystickReport_Data_t);
				HIDReportState.forcewrite=false;
				break;

				// not supported yet <--
				//case HID_REPORTID_MidiReport:
				//HID_Report_Size=sizeof(HID_MidiReport_Data_t);
				//HID_Report_ForceWrite=false;
				//break;

			default : 
				// error
				checkNHPControlAddressError();
				break;
			} //end switch

			// The Protocol received a valid signal with inverse checksum
			// Do not write the buff in the loop above or below, filter it out
			NHPreset();
		} // end if control address byte

		else if(HIDReportState.ID){
			// check if the new Address is in correct order of HID reports.
			// the first 2 bytes are sent with Address 2 and so on.
			if(NHPgetAddress()==(((HIDReportState.recvlength+2)/2)+1)){
				// save the first byte
				CurrentHIDReportBuffer[HIDReportState.recvlength++]=NHPgetChecksumData0();

				// if there is another byte we need (for odd max HID reports important
				// to not write over the buff array)
				if(HIDReportState.length!=HIDReportState.recvlength)
					CurrentHIDReportBuffer[HIDReportState.recvlength++]=NHPgetChecksumData1();

				// we are ready to submit the new report to the usb host
				if(HIDReportState.length==HIDReportState.recvlength){
					// TODO timeout? <--
					while(HIDReportState.ID)
						HID_Device_USBTask(&Device_HID_Interface);
				}
				// The Protocol received a valid signal with inverse checksum
				// Do not write the buff in the loop above or below, filter it out
				NHPreset();
			}

			// we received a corrupt data packet
			else
				// check if previous reading was a valid Control Address and write it down
				checkNHPControlAddressError();

		} // end if HIDReportState.ID

		else {
			// just a normal Protocol outside our control address
		}
	} // end if readChecksum
}

void checkNHPControlAddressError(void){
	// only write if it was just before, maybe it was a random valid address
	// but if we already received some data we handle this as corrupted data and just
	// discard all the bytes
	if(HIDReportState.recvlength==0){
		// write the cached buffer (recreate protocol)
		NHPwriteChecksum(NHP_ADDRESS_CONTROL, (NHP_USAGE_ARDUINOHID<<8) | HIDReportState.ID);
		for(int i = 0; i< NHPwritelength; i++){
			bool CurrentDTRState = (VirtualSerial_CDC_Interface.State.ControlLineStates.HostToDevice & CDC_CONTROL_LINE_OUT_DTR); //new <--
			if(CurrentDTRState)
				CDC_Device_SendByte(&VirtualSerial_CDC_Interface, NHPwritebuffer[i]);
		}
	}
	// reset any pending HID reports
	HIDReportState.ID=0;
}

/** Event handler for the library USB Connection event. */
void EVENT_USB_Device_Connect(void)
{
	//LEDs_SetAllLEDs(LEDMASK_USB_ENUMERATING);
}

/** Event handler for the library USB Disconnection event. */
void EVENT_USB_Device_Disconnect(void)
{
	//LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
}

/** Event handler for the library USB Configuration Changed event. */
void EVENT_USB_Device_ConfigurationChanged(void) //<--new
{
	bool ConfigSuccess = true;

	ConfigSuccess &= HID_Device_ConfigureEndpoints(&Device_HID_Interface);
	ConfigSuccess &= CDC_Device_ConfigureEndpoints(&VirtualSerial_CDC_Interface);

	// This seems to be for the HID to get accurate reports
	USB_Device_EnableSOFEvents(); //<--new

	// Turn off Leds if everything is okay
	LEDs_SetAllLEDs(ConfigSuccess ? LEDS_NO_LEDS : LEDS_ALL_LEDS); //<--new
}

/** Event handler for the library USB Unhandled Control Request event. */
void EVENT_USB_Device_UnhandledControlRequest(void)
{
	CDC_Device_ProcessControlRequest(&VirtualSerial_CDC_Interface);
}

/** Event handler for the CDC Class driver Line Encoding Changed event.
*
*  \param[in] CDCInterfaceInfo  Pointer to the CDC class interface configuration structure being referenced
*/
void EVENT_CDC_Device_LineEncodingChanged(USB_ClassInfo_CDC_Device_t* const CDCInterfaceInfo)
{
	uint8_t ConfigMask = 0;

	switch (CDCInterfaceInfo->State.LineEncoding.ParityType)
	{
	case CDC_PARITY_Odd:
		ConfigMask = ((1 << UPM11) | (1 << UPM10));	
		break;
	case CDC_PARITY_Even:
		ConfigMask = (1 << UPM11);		
		break;
	}

	if (CDCInterfaceInfo->State.LineEncoding.CharFormat == CDC_LINEENCODING_TwoStopBits)
		ConfigMask |= (1 << USBS1);

	switch (CDCInterfaceInfo->State.LineEncoding.DataBits)
	{
	case 6:
		ConfigMask |= (1 << UCSZ10);
		break;
	case 7:
		ConfigMask |= (1 << UCSZ11);
		break;
	case 8:
		ConfigMask |= ((1 << UCSZ11) | (1 << UCSZ10));
		break;
	}

	/* Must turn off USART before reconfiguring it, otherwise incorrect operation may occur */
	PORTD |= (1 << PD3); // Turn ON Tx while USART is being reconfigured
	UCSR1B = 0;
	UCSR1A = 0;
	UCSR1C = 0;

	/* Special case 57600 baud for compatibility with the ATmega328 bootloader. */	
	UBRR1  = (CDCInterfaceInfo->State.LineEncoding.BaudRateBPS == 57600)
		? SERIAL_UBBRVAL(CDCInterfaceInfo->State.LineEncoding.BaudRateBPS)
		: SERIAL_2X_UBBRVAL(CDCInterfaceInfo->State.LineEncoding.BaudRateBPS);	

	UCSR1C = ConfigMask;
	UCSR1A = (CDCInterfaceInfo->State.LineEncoding.BaudRateBPS == 57600) ? 0 : (1 << U2X1);
	UCSR1B = ((1 << RXCIE1) | (1 << TXEN1) | (1 << RXEN1));
	PORTD &= ~(1 << PD3); // And turn OFF Tx once USART has been reconfigured (this is overridden by TXEN)
}

/** ISR to manage the reception of data from the serial port, placing received bytes into a circular buffer
*  for later transmission to the host.
*/
ISR(USART1_RX_vect, ISR_BLOCK)
{
	uint8_t ReceivedByte = UDR1;

	if (USB_DeviceState == DEVICE_STATE_Configured)
		RingBuffer_Insert(&USARTtoUSB_Buffer, ReceivedByte);
}

/** Event handler for the CDC Class driver Host-to-Device Line Encoding Changed event.
*
*  \param[in] CDCInterfaceInfo  Pointer to the CDC class interface configuration structure being referenced
*/
void EVENT_CDC_Device_ControLineStateChanged(USB_ClassInfo_CDC_Device_t* const CDCInterfaceInfo)
{
	bool CurrentDTRState = (CDCInterfaceInfo->State.ControlLineStates.HostToDevice & CDC_CONTROL_LINE_OUT_DTR);

	if (CurrentDTRState){
		AVR_RESET_LINE_PORT &= ~AVR_RESET_LINE_MASK;
	}
	else{
		AVR_RESET_LINE_PORT |= AVR_RESET_LINE_MASK;
		LEDs_SetAllLEDs(LEDS_NO_LEDS); //<--new
	}
}

/** Event handler for the library USB Control Request reception event. */
void EVENT_USB_Device_ControlRequest(void)
{
	CDC_Device_ProcessControlRequest(&VirtualSerial_CDC_Interface);
	HID_Device_ProcessControlRequest(&Device_HID_Interface); //<--new
}

/** Event handler for the USB device Start Of Frame event. */
void EVENT_USB_Device_StartOfFrame(void)
{
	HID_Device_MillisecondElapsed(&Device_HID_Interface);
}

/** HID class driver callback function for the creation of HID reports to the host.
*
*  \param[in]     HIDInterfaceInfo  Pointer to the HID class interface configuration structure being referenced
*  \param[in,out] ReportID    Report ID requested by the host if non-zero, otherwise callback should set to the generated report ID
*  \param[in]     ReportType  Type of the report to create, either HID_REPORT_ITEM_In or HID_REPORT_ITEM_Feature
*  \param[out]    ReportData  Pointer to a buffer where the created report should be stored
*  \param[out]    ReportSize  Number of bytes written in the report (or zero if no report is to be sent)
*
*  \return Boolean \c true to force the sending of the report, \c false to let the library determine if it needs to be sent
*/
bool CALLBACK_HID_Device_CreateHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
										 uint8_t* const ReportID,
										 const uint8_t ReportType,
										 void* ReportData,
										 uint16_t* const ReportSize)
{
	//write report and reset ID
	memcpy(ReportData, CurrentHIDReportBuffer, HIDReportState.length);
	*ReportID   = HIDReportState.ID;
	*ReportSize = HIDReportState.length;
	HIDReportState.ID=0;
	return HIDReportState.forcewrite;
}

/** HID class driver callback function for the processing of HID reports from the host.
*
*  \param[in] HIDInterfaceInfo  Pointer to the HID class interface configuration structure being referenced
*  \param[in] ReportID    Report ID of the received report from the host
*  \param[in] ReportType  The type of report that the host has sent, either HID_REPORT_ITEM_Out or HID_REPORT_ITEM_Feature
*  \param[in] ReportData  Pointer to a buffer where the received report has been stored
*  \param[in] ReportSize  Size in bytes of the received HID report
*/
void CALLBACK_HID_Device_ProcessHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
										  const uint8_t ReportID,
										  const uint8_t ReportType,
										  const void* ReportData,
										  const uint16_t ReportSize)
{
	// Unused (but mandatory for the HID class driver) in this demo, since there are no Host->Device reports
	//	uint8_t* LEDReport = (uint8_t*)ReportData;
}

