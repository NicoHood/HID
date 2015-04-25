/*
 * Edited by Ringo Martens on 04/25/2015 to port keyboard class to arduino
 */

#ifndef __teensy_KEYBOARDAPI__
#define __teensy_KEYBOARDAPI__

#include "Arduino.h"
#include "teensy_Keylayouts.h"

typedef union{
	// Low level key report: up to 6 keys and shift, ctrl etc at once
	uint8_t whole8[];
	uint16_t whole16[];
	uint32_t whole32[];
	struct{
		uint8_t modifiers;
		uint8_t reserved;
		uint8_t keys[6];
	};
} teensy_HID_KeyboardReport_Data_t;


class usb_keyboard_class : public Print
{
        protected:
	teensy_HID_KeyboardReport_Data_t _keyReport;
	void sendReport(teensy_HID_KeyboardReport_Data_t* keys);
	public:
	void begin(void) {
                end();
        }
	void end(void) {
            releaseAll();
        }
#if ARDUINO >= 100
	virtual size_t write(uint8_t);
#else
	virtual void write(uint8_t);
#endif
	using Print::write;
	void write_unicode(uint16_t unicode) { write_keycode(unicode_to_keycode(unicode)); }
	void set_modifier(uint8_t);
	void set_key1(uint8_t);
	void set_key2(uint8_t);
	void set_key3(uint8_t);
	void set_key4(uint8_t);
	void set_key5(uint8_t);
	void set_key6(uint8_t);
	void press(uint16_t n);
	void release(uint16_t n);
	void releaseAll(void);
	void send_now(void);
	private:
	KEYCODE_TYPE unicode_to_keycode(uint16_t unicode);
	KEYCODE_TYPE deadkey_to_keycode(KEYCODE_TYPE keycode);
	uint8_t keycode_to_modifier(KEYCODE_TYPE keycode);
	uint8_t keycode_to_key(KEYCODE_TYPE keycode);
	void presskey(uint8_t key, uint8_t modifier);
	void releasekey(uint8_t key, uint8_t modifier);
	void write_keycode(KEYCODE_TYPE key);
	void write_key(KEYCODE_TYPE code);
	uint8_t utf8_state;
	uint16_t unicode_wchar;
};

extern usb_keyboard_class teensy_Keyboard;

#endif