/*
 Copyright (c) 2014 NicoHood
 See the readme for credit to other people.

 USB-Serial

 Transferes from USB to HW Serial and vice versa.
 It also resets the main MCU on a DTR rise.
 */

// define the reset pin to reset the destination MCU.
// this definition is made for HoodLoader2 (pin 20)
// but you still can use it with any other USB MCU or pin
const int resetPin = MAIN_MCU_RESET_PIN;

void setup() {
  // set main MCU by default active
  pinMode(resetPin, OUTPUT);
  digitalWrite(resetPin, HIGH);

  // Start USB Serial
  Serial.begin(115200);
}

void loop() {
  // USB -> Serial
  for (int i = 0; i < USB_EP_SIZE; i++) {
    // read maximum one EP_SIZE to not block
    if (Serial.available())
      Serial1.write(Serial.read());
    else break;
  }

  // Serial -> USB
  if (Serial1.available()) {
    Serial.flush();
    // send maximum one EP_SIZE to give the usb some time to flush the buffer
    uint8_t buff[USB_EP_SIZE - 1];
    int i = 0;
    for (i = 0; i < USB_EP_SIZE - 1; i++) {
      if (Serial1.available())
        buff[i] = Serial1.read();
      else break;
    }
    Serial.write(buff, i);
  }
}

void CDC_LineEncodingEvent(void)
{
  // start HW Serial with new baud rate
  Serial1.end();
  Serial1.begin(Serial.baud());
}

void CDC_LineStateEvent(void) {
  // reset the main mcu if DTR goes HIGH
  if (Serial.dtr())
    digitalWrite(resetPin, LOW);
  else
    digitalWrite(resetPin, HIGH);
}
