/*
 Copyright (c) 2014 NicoHood
 See the readme for credit to other people.
 
 Keyboard HoodLoader1 API Legacy example
 
 Legacy Example on how to access the Serial HID API of HoodLoader1.
 This methode is outdated, because you can now control the whole
 16u2 with HoodLoader2. It might be still usefull if you want the 328/2560
 keep control of the USB functions. Keep in mind that there is no such thing
 as flushing HID reports. If the USB Host is too slow HID reports might be missed.
 
 You can also adapt the sending method below to send Mouse/Keyboard/Media/System reports.
 Gamepads/RawHID have a general problem with the original HoodLoader1 firmware, so please avoid this.
 It might be compatible with the new HoodLoader2 port of the protocol later on.
 
 HID reports are converted into a special Serial Protocol with NHP.
 This sketch should only be used with a 328/2560, not a 16u2.
 The 16u2 has a HoodLoader1 compatible sketch/firmware loaded and will
 listen to the Serial Port for these Protocol packets on baud 115200.
 
 The HID_SendReport function is implemented weak, so we can overwrite it
 in this sketch below. A simple NHP implementation encapsulated the HID reports
 into NHP packets with correct addresses and checksums.
 
 Press a button to write some text to your pc.
 See official documentation for more infos
 */

// Serial to write Protocol data to. Default: Serial
#define HID_SERIAL Serial
#define SERIAL_HID_BAUD 115200

// extra delay for raspberry. Only needed for Hoodloader and slow devices
//#define HID_EXTRADELAY 20

const int pinLed = 13;
const int pinButton = 8;

void setup() {
  pinMode(pinLed, OUTPUT);
  pinMode(pinButton, INPUT_PULLUP);

  // Starts Serial at baud 115200 otherwise HID wont work with HoodLoader1.
  // This is not needed for Leonado/(Pro)Micro/16u2(HoodLoader2)
  Serial.begin(SERIAL_HID_BAUD);

  // Sends a clean report to the host. This is important on any Arduino type.
  // Make sure all desired USB functions are activated in USBAPI.h!
  Keyboard.begin();
}


void loop() {
  if (!digitalRead(pinButton)) {
    digitalWrite(pinLed, HIGH);

    // Same use as the official library, pretty much self explaining
    Keyboard.println("This message was sent with my Arduino.");
    Serial.println("Serial port is still working and not glitching out");

    // simple debounce
    delay(300);
    digitalWrite(pinLed, LOW);
  }
}

//================================================================================
// NHP
//================================================================================

// Start Mask
#define NHP_MASK_START		0xC0 //B11|000000 the two MSB bits
#define NHP_MASK_LEAD		0xC0 //B11|000000
#define NHP_MASK_DATA		0x00 //B0|0000000 only the first MSB is important
#define NHP_MASK_END		0x80 //B10|000000

// Content Mask
#define NHP_MASK_LENGTH		0x38 //B00|111|000
#define NHP_MASK_COMMAND	0x0F //B0000|1111
#define NHP_MASK_DATA_7BIT	0x7F //B0|1111111
#define NHP_MASK_DATA_4BIT	0x0F //B0000|1111
#define NHP_MASK_DATA_3BIT	0x07 //B00000|111
#define NHP_MASK_ADDRESS	0x3F //B00|111111

// Reserved Addresses
#define NHP_ADDRESS_CONTROL 0x01

// Reserved Usages
#define NHP_USAGE_ARDUINOHID 0x01

// overwrites the HID_SendReport function which is empty/not used on a 328/2560
void HID_SendReport(uint8_t id, const void* data, int len)
{
  // write the Report via Protocol and checksum. 16bit for each sending
  // send control address
  NHPwriteChecksum(NHP_ADDRESS_CONTROL, (NHP_USAGE_ARDUINOHID << 8) | id);
  const uint8_t* report = (const uint8_t*)data;
  for (int i = 0; i < len; i++) {
    uint8_t data0 = report[i++];
    uint8_t data1 = 0;
    if (i != len)
      data1 = report[i];
    // valid HID reports start at Address 2
    NHPwriteChecksum(2 + i / 2, (data1 << 8) | data0);
  }
#ifdef HID_EXTRADELAY
  delay(HID_EXTRADELAY);
#endif
}

// simple copy/modification of the NicoHoodProtocol writechecksum function
void NHPwriteChecksum(uint8_t address, uint16_t indata) {
  // writes two bytes with its inverse
  uint32_t temp = ~indata;
  uint32_t data = (temp << 16) | indata;

  // buffer for write operation
  uint8_t writebuffer[6];

  // start with the maximum size of blocks
  uint8_t blocks = 7;

  // check for the first 7 bit block that doesnt fit into the first 3 bits
  while (blocks > 2) {
    uint8_t nextvalue = (data >> (7 * (blocks - 3)));

    if (nextvalue > NHP_MASK_DATA_3BIT) {
      // special case for the MSB
      if (blocks == 7) {
        writebuffer[0] = nextvalue;
        blocks--;
      }
      // this block is too big, write this into the next data block
      break;
    }
    else {
      // write the possible first 3 bits and check again after if zero
      writebuffer[0] = nextvalue;
      blocks--;
      // we have our first bits, stop (nonzero)
      if (nextvalue)
        break;
    }
  }

  // write the rest of the data bits
  uint8_t datablocks = blocks - 2;
  while (datablocks > 0) {
    writebuffer[datablocks] = data & NHP_MASK_DATA_7BIT;
    data >>= 7;
    datablocks--;
  }

  // write lead + length mask
  writebuffer[0] |= NHP_MASK_LEAD | (blocks << 3);

  // write end mask
  writebuffer[blocks - 1] = NHP_MASK_END | ((address - 1) & NHP_MASK_ADDRESS);

  // write the buffer
  HID_SERIAL.write(writebuffer, blocks);
}
