/*
Copyright (c) 2021 ilufang
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

#define _LSB(v) ((v >> 8) & 0xff)
#define _MSB(v) (v & 0xff)

void MultiTouchAPI::begin() {
	send();
}

int MultiTouchAPI::setFinger(uint8_t id, int16_t x, int16_t y, int8_t pressure) {
	if (id >= HID_MULTITOUCH_MAXFINGERS) {
		return 0;
	}
	if (_fingers[id].status == _MT_STATE_INACTIVE) {
		_fingers_count++;
	}
	_fingers[id].status = _MT_STATE_CONTACT;
	_fingers[id].pressure = pressure;
	_fingers[id].x = x;
	_fingers[id].y = y;
	return 1;
}

int MultiTouchAPI::releaseFinger(uint8_t id) {
	if (id >= HID_MULTITOUCH_MAXFINGERS) {
		return 0;
	}
	_fingers[id].status = _MT_STATE_RELEASED;
	return 1;
}

int MultiTouchAPI::send() {
	int ret = 0;

	// Craft report(s)
	_report.count = _fingers_count;

	int rptentry=0;
	for (int i = 0; i < HID_MULTITOUCH_MAXFINGERS; i++) {
		if (_fingers[i].status == _MT_STATE_INACTIVE)
			continue;

		_report.contacts[rptentry].identifier = i; // valid for first report only

		if (_fingers[i].status == _MT_STATE_RELEASED) {
			// Released contacts need to be reported once with TipSW=0
			_report.contacts[rptentry].touch = {};
			_fingers_count--;
			_fingers[i].status = _MT_STATE_INACTIVE;
		} else {
			// Active contacts must be reported even when not moved
			_report.contacts[rptentry].touch = _fingers[i].pressure > 0 ? 3 : 1;
			_report.contacts[rptentry].x1 = _MSB(_fingers[i].x);
			_report.contacts[rptentry].x0 = _LSB(_fingers[i].x);
			_report.contacts[rptentry].y1 = _MSB(_fingers[i].y);
			_report.contacts[rptentry].y0 = _LSB(_fingers[i].y);
			_report.contacts[rptentry].pressure = _fingers[i].pressure;
		}

		rptentry++;
		if (rptentry == HID_MULTITOUCH_REPORTFINGERS) {
			// Report full. Send now.
			// If there are more contacts, they will be sent in subsequent
			// reports with contact count set to 0
			// See "Hybrid Mode" on MSDN docs
			ret += _sendReport();
			rptentry = 0;
			_report.count = 0;
		}
	}

	if (rptentry != 0) {
		// Send remaining touches
		for (; rptentry != HID_MULTITOUCH_REPORTFINGERS; rptentry++) {
			_report.contacts[rptentry] = {};
		}
		ret += _sendReport();
	}

	return ret;
}
