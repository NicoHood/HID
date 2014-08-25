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

#include "Joystick.h"

//================================================================================
// Joystick
//================================================================================

Joystick_ Joystick1(HID_REPORTID_Joystick1Report);
Joystick_ Joystick2(HID_REPORTID_Joystick2Report);

Joystick_::Joystick_(uint8_t reportID){
	_reportID = reportID;
}

void Joystick_::begin(void){
	memset(&_report, 0, sizeof(_report));
	HID_SendReport(_reportID, &_report, sizeof(_report));
}

void Joystick_::end(void){
	begin();
}

void Joystick_::write(void){
	HID_SendReport(_reportID, &_report, sizeof(_report));;
}

void Joystick_::press(uint8_t b){
	if (b == 1) _report.button1 = 1;
	else if (b == 2) _report.button2 = 1;
}

void Joystick_::release(uint8_t b){
	if (b == 1) _report.button1 = 0;
	else if (b == 2) _report.button2 = 0;
}

void Joystick_::releaseAll(void){
	_report.button1 = 0;
	_report.button2 = 0;
}