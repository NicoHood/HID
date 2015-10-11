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

GamepadAPI::GamepadAPI(void)
{
	// Empty
}

void GamepadAPI::begin(void){
	// release all buttons
	end();
}

void GamepadAPI::end(void){
	memset(&_report, 0x00, sizeof(_report));
	SendReport(&_report, sizeof(_report));
}

void GamepadAPI::write(void){ 
	SendReport(&_report, sizeof(_report)); 
}


void GamepadAPI::press(uint8_t b){ 
	_report.buttons |= (uint32_t)1 << (b - 1); 
}


void GamepadAPI::release(uint8_t b){ 
	_report.buttons &= ~((uint32_t)1 << (b - 1)); 
}


void GamepadAPI::releaseAll(void){ 
	memset(&_report, 0x00, sizeof(_report)); 
}

void GamepadAPI::buttons(uint32_t b){ 
	_report.buttons = b; 
}


void GamepadAPI::xAxis(int16_t a){ 
	_report.xAxis = a; 
}


void GamepadAPI::yAxis(int16_t a){ 
	_report.yAxis = a; 
}


void GamepadAPI::zAxis(int8_t a){ 
	_report.zAxis = a; 
}


void GamepadAPI::rxAxis(int16_t a){ 
	_report.rxAxis = a; 
}


void GamepadAPI::ryAxis(int16_t a){ 
	_report.ryAxis = a; 
}


void GamepadAPI::rzAxis(int8_t a){ 
	_report.rzAxis = a; 
}


void GamepadAPI::dPad1(int8_t d){ 
	_report.dPad1 = d; 
}


void GamepadAPI::dPad2(int8_t d){ 
	_report.dPad2 = d; 
}

