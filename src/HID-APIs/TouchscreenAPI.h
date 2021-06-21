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

/// Maximum amount of fingers supported
#define HID_TOUCHSCREEN_MAXFINGERS 10
/// Number of fingers in a single report
#define HID_TOUCHSCREEN_REPORTFINGERS 2

// A report will always be the same size, even if you report fewer fingers than
// REPORTFINGERS. The unused finger entries will simply be zero. If more fingers
// are present than REPORTFINGERS, multiple reports will be sent to report all
// fingers. This is know as "Hybrid Mode" on MSDN. The number of supported
// fingers identified by Windows will still be MAXFINGERS. More than MAXFINGERS
// contacts may be ignored by Windows even with hybrid mode.


// Bit-mask flags for 'status' in the HID report
#define HID_TOUCHSCREEN_TOUCH_CONTACT 0x01
#define HID_TOUCHSCREEN_TOUCH_IN_RANGE 0x02

typedef struct ATTRIBUTE_PACKED {
	uint8_t status;
	uint8_t pressure;
	uint16_t x;
	uint16_t y;
} HID_Touchscreen_Finger_t;

typedef union ATTRIBUTE_PACKED {
	uint8_t whole8[0];
	uint16_t whole16[0];
	uint32_t whole32[0];
	struct ATTRIBUTE_PACKED {
		uint8_t count;
		struct ATTRIBUTE_PACKED {
			uint8_t identifier;
			HID_Touchscreen_Finger_t touch;
		} contacts[HID_TOUCHSCREEN_REPORTFINGERS];
	};
} HID_TouchscreenReport_Data_t;

class TouchscreenAPI
{
public:

	inline void begin();

	/**
	 * Set contact status for a finger in the internal data structure. You must
	 * call send manually after setting all fingers to flush them through USB.
	 *
	 * @param id Finger id. Must be in the range of 0-MAXFINGERS. Same finger
	 *           must have same id throughout contact. Allocations does not need
	 *           to be continuous.
	 * @param x, y Coordinates. Range 0-10000. (0,0) is top-left on Windows.
	 * @param pressure Contact pressure. Range 0-127. When set to 0, the touch
	 *                 is reported as hovering (in-range)
	 * @return 1 if success. 0 if id is out-of-bounds
	 */
	inline int setFinger(uint8_t id, uint16_t x, uint16_t y, uint8_t pressure=100);

	/**
	 * Release finger in the internal data structure. You must call send
	 * manually after setting all fingers to flush them through USB.
	 *
	 * @param id Finger id. Must be in the range of 0-MAXFINGERS. Same finger
	 *           must have same id throughout contact. Allocations does not need
	 *           to be continuous.
	 * @return 1 if success. 0 if id is out-of-bounds
	 */
	inline int releaseFinger(uint8_t id);

	/**
	 * Generates an HID report reflecting the currently recorded touch status
	 * and send through USB.
	 */
	inline int send();

	/// Send generated report. Needs to be implemented in a lower level
	virtual int sendReport(void *report, int length) = 0;
	virtual int sendReport(HID_TouchscreenReport_Data_t &report) = 0;

protected:

	/// Internal records of the current touch statuses. Status in this struct
	/// is used only internally and differs from the one in the report
	HID_Touchscreen_Finger_t _fingers[HID_TOUCHSCREEN_MAXFINGERS];
	/// Number of active contacts, including just release contacts
	uint8_t _fingers_count;
};

// Implementation is inline
#include "TouchscreenAPI.hpp"
