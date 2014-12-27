void setup() {
  // put your setup code here, to run once:
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);

  // 6374 292
  Keyboard.begin();
  Gamepad.begin();
}

uint32_t eventBaud = 0;

void loop() {

  if (!digitalRead(7)) {
    digitalWrite(13, 1);
    Mouse.moveTo(1000, 1000);
    delay(300);
    digitalWrite(13, 0);
  }

  if (!digitalRead(8)) {
    digitalWrite(13, 1);
    Mouse.move(100, 0);
    delay(300);
    digitalWrite(13, 0);
  }

  if (!digitalRead(9)) {
    digitalWrite(13, 1);
    Mouse.move(-100, 0);
    delay(300);
    digitalWrite(13, 0);
  }

  if (!digitalRead(10)) {
    uint8_t k[8] = {0};
    k[1] = 1;

    k[2] = 4;
    k[3] = 5;
    HID_SendReport(HID_REPORTID_KEYBOARD, &k, sizeof(k));
    Keyboard.releaseAll();
    delay(300);
  }
  if (!digitalRead(2)) {
    digitalWrite(13, 1);
    System.write(SYSTEM_SLEEP);
    delay(300);
    digitalWrite(13, 0);
  }
  if (!digitalRead(3)) {
    digitalWrite(13, 1);
    USBDevice.wakeupHost();
    delay(300);
    digitalWrite(13, 0);
  }

  if (Serial.available()) {
    // let the Serial receive all bytes and discard the first bytes
    // this is to ensure you only input a single char and no string
    char c;
    delay(300);
    int length = Serial.available();
    while (Serial.available())
      c = Serial.read();
    if (length > 1) {
      Serial.println("Please only input a single character or deactivate linefeed!");
      return;
    }

    if (c != -1) {
      Serial.println(c);
      switch (c) {
        case 'a':
          Keyboard.write('b');
          break;

        case 'p':
          Consumer.write(MEDIA_PLAY_PAUSE);
          break;

        case 'o':
          {
            //            uint8_t k[8] = {0};
            //            k[1] = 1 << 4;
            //            //k[2] = 4;
            //            HID_SendReport(HID_REPORTID_KEYBOARD, &k, sizeof(k));
            //            Keyboard.releaseAll();
            break;
          }

        case 's':
          System.write(SYSTEM_SLEEP);
          break;

        case 'r':
          Mouse.move(100, 0);
          break;

        case 'l':
          Mouse.move(-100, 0);
          break;

        case 't':
          Mouse.moveTo(1000, 1000);
          break;

        case 'c':
        case 'C':
          Keyboard.write(KEY_CAPS_LOCK);
          Serial.println("Leds");
          Serial.println(Keyboard.getLEDs(), BIN);
          break;

        case 'k':
          Keyboard.print("Testing USB functions xyz");
          break;

        case '\r':
        case '\n':
          Serial.println("Please only input a single character!");
          break;

        case 'd':
          Serial.println("Serial");
          Serial.println(Serial.dtr());
          Serial.println(Serial.rts());
          Serial.println(Serial.baud());
          Serial.println(Serial.stopbits());
          Serial.println(Serial.paritytype());
          Serial.println(Serial.numbits());
          break;

        default:
          Serial.println("unknown");
      }
    }
  }


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
