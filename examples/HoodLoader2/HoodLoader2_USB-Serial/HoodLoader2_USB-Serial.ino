/*
 Copyright (c) 2014 NicoHood
 See the readme for credit to other people.

 HoodLoader2 USB-Serial

 Transferes from USB to HW Serial and vice versa.
 It also resets the main MCU on a DTR rise.
 */

void setup() {
  // set main MCU by default active
  pinMode(MAIN_MCU_RESET_PIN, OUTPUT);
  digitalWrite(MAIN_MCU_RESET_PIN, HIGH);

  // Start USB and HW Serial
  Serial.begin(115200);
  Serial1.begin(115200);
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
    uint8_t buff[USB_EP_SIZE-1];
    int i = 0;
    for (i = 0; i < USB_EP_SIZE-1; i++) {
      if (Serial1.available())
        buff[i] = Serial1.read();
      else break;
    }
    Serial.write(buff, i);
  }

  // reset the main mcu if DTR goes HIGH
  static bool lastDTR = 0;
  bool newDTR = (Serial.lineState()&CDC_CONTROL_LINE_OUT_DTR) ? 1 : 0;
  if (lastDTR ^ newDTR)
    digitalWrite(MAIN_MCU_RESET_PIN, lastDTR);
  lastDTR = newDTR;
}

