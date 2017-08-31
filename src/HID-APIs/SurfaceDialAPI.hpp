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

SurfaceDialAPI::SurfaceDialAPI(void) : _button(false)
{
	// Empty
}

void SurfaceDialAPI::begin(void)
{
	end();
}

void SurfaceDialAPI::end(void)
{
	_button = false;
	rotate(0);
}

void SurfaceDialAPI::click(void)
{
	_button = true;
	rotate(0);
	_button = false;
	rotate(0);
}

void SurfaceDialAPI::rotate(int16_t rotation)
{
	HID_SurfaceDialReport_Data_t report;
	report.button = _button;
	report.rotation = rotation;
	//report.xAxis = x;
	//report.yAxis = y;

	SendReport(&report, sizeof(report));
}

void SurfaceDialAPI::button(bool b)
{
	if (b != _button)
	{
		_button = b;
		rotate(0);
	}
}

void SurfaceDialAPI::press(void)
{
	button(true);
}

void SurfaceDialAPI::release(void)
{
	button(false);
}

void SurfaceDialAPI::releaseAll(void)
{
	_button = false;
	rotate(0);
}

bool SurfaceDialAPI::isPressed()
{
	return _button;	
}
