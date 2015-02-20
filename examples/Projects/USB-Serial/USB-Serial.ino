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
  uint8_t i;
  for (i = 0; i < USB_EP_SIZE; i++) {
    // read maximum one EP_SIZE to not block
    int b = Serial.read();
    if (b < 0)
      break;
    Serial1.write(b);
  }

  // Serial -> USB
  uint8_t buff[USB_EP_SIZE];
  for (i = 0; i < sizeof(buff); i++) {
    // read maximum one EP_SIZE to not block
    int b = Serial1.read();
    if (b < 0)
      break;
    buff[i] = b;
  }
  // send maximum one EP_SIZE to give the usb some time to flush the buffer
  Serial.write(buff, i);
}

void CDC_LineEncodingEvent(void) {
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
