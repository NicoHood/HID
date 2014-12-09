// simply, ugly code to test the new functions

void setup() {
  Serial.begin(1);
}

uint32_t eventBaud = 0;

void loop() {
  if (Serial.available()) {
    while (Serial.read() != -1);
    Serial.println("Serial Port working");
    Keyboard.println("Nico is cool");
    delay(3000);
  }

  delay(3000);
  Serial.println(Serial.dtr());
  Serial.println(Serial.rts());
  Serial.println(Serial.baud());
  Serial.println(Serial.stopbits());
  Serial.println(Serial.paritytype());
  Serial.println(Serial.numbits());

  if (eventBaud) {
    Serial.println("Event");
    Serial.println(eventBaud);
    eventBaud = 0;
  }
}

void CDC_LineEncodingEvent(void)
{
  eventBaud = Serial.baud();
}
