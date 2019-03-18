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
	update();
}

void SurfaceDialAPI::click(void)
{
	_button = true;
	update();
	_button = false;
	update();
}

void SurfaceDialAPI::rotate(int16_t rotation)
{
	reportData(rotation, _xAxis, _yAxis);
}

void SurfaceDialAPI::position(int16_t x, int16_t y)
{
	reportData(0, x, y);
}

void SurfaceDialAPI::reportData(int16_t rotation, int16_t x, int16_t y)
{
	HID_SurfaceDialReport_Data_t report;
	_xAxis = x;
	_yAxis = y;
	report.button = _button;
	report.rotation = rotation;
	report.width = 3000;
	if(_onScreen)
	{
		report.xAxis = _xAxis;
		report.yAxis = _yAxis;
	}
	SendReport(&report, sizeof(report));
}

void SurfaceDialAPI::button(bool b)
{
	if (b != _button)
	{
		_button = b;
		update();
	}
}

void SurfaceDialAPI::xAxis(int16_t x)
{
	_xAxis = x;
	reportData(0, _xAxis, _yAxis);
}
void SurfaceDialAPI::yAxis(int16_t y)
{
	_yAxis = y;
	reportData(0, _xAxis, _yAxis);
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
	update();
}

void SurfaceDialAPI::onScreen(bool s)
{
	_onScreen = s;
	update();
}

void SurfaceDialAPI::update()
{
	HID_SurfaceDialReport_Data_t report;
	report.button = _button;
	report.rotation = 0;
	report.width = 3000;
	if(_onScreen)
	{
		report.xAxis = _xAxis;
		report.yAxis = _yAxis;
	}
	SendReport(&report, sizeof(report));
}

bool SurfaceDialAPI::isPressed()
{
	return _button;
}

bool SurfaceDialAPI::getOnScreen()
{
	return _onScreen;
}

int16_t SurfaceDialAPI::getX()
{
	return _xAxis;
}

int16_t SurfaceDialAPI::getY()
{
	return _yAxis;
}
