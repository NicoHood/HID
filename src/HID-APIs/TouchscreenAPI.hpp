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

enum _finger_status_t {
	_MT_STATE_INACTIVE = 0,
	_MT_STATE_CONTACT,
	_MT_STATE_RELEASED
};

void TouchscreenAPI::begin() {
	send();
}

int TouchscreenAPI::setFinger(uint8_t id, uint16_t x, uint16_t y, uint8_t pressure) {
	if (id >= HID_TOUCHSCREEN_MAXFINGERS) {
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

int TouchscreenAPI::releaseFinger(uint8_t id) {
	if (id >= HID_TOUCHSCREEN_MAXFINGERS) {
		return 0;
	}
	_fingers[id].status = _MT_STATE_RELEASED;
	return 1;
}

int TouchscreenAPI::send() {
	int ret = 0;
	HID_TouchscreenReport_Data_t report;

	// Craft report(s)
	report.count = _fingers_count;

	int rptentry=0;
	for (int i = 0; i < HID_TOUCHSCREEN_MAXFINGERS; i++) {
		if (_fingers[i].status == _MT_STATE_INACTIVE)
			continue;

		report.contacts[rptentry].identifier = i; // valid for first report only

		if (_fingers[i].status == _MT_STATE_RELEASED) {
			// Released contacts need to be reported once with TipSW=0
			report.contacts[rptentry].touch = {};
			_fingers_count--;
			_fingers[i].status = _MT_STATE_INACTIVE;
		} else {
			// Active contacts must be reported even when not moved
			report.contacts[rptentry].touch.status = HID_TOUCHSCREEN_TOUCH_IN_RANGE;
			if (_fingers[i].pressure > 0)
				report.contacts[rptentry].touch.status |= HID_TOUCHSCREEN_TOUCH_CONTACT;
			report.contacts[rptentry].touch.x = _fingers[i].x;
			report.contacts[rptentry].touch.y = _fingers[i].y;
			report.contacts[rptentry].touch.pressure = _fingers[i].pressure;
		}

		rptentry++;
		if (rptentry == HID_TOUCHSCREEN_REPORTFINGERS) {
			// Report full. Send now.
			// If there are more contacts, they will be sent in subsequent
			// reports with contact count set to 0
			// See "Hybrid Mode" on MSDN docs
			ret += sendReport(report);
			rptentry = 0;
			report.count = 0;
		}
	}

	if (rptentry != 0) {
		// Send remaining touches
		for (; rptentry != HID_TOUCHSCREEN_REPORTFINGERS; rptentry++) {
			report.contacts[rptentry] = {};
		}
		ret += sendReport(report);
	}

	return ret;
}
