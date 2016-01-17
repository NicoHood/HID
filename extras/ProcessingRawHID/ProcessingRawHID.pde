/*
Copyright (c) 2016 Deqing Sun

This is a simple Processing sketch that talks to Arduino with RawHID firmware.

"javahidapi" from "Codeminders" is used for this sketch to do lower level communication. 
javahidapi is available on https://code.google.com/p/javahidapi/
*/
HIDDevice target_device=null;

void init_device() {
  //print_HID_devices();
  //This funtion uses Arduino Micro VID/PID pair, change it if you use other Arduino
  HIDDeviceInfo[] dev_list=filter_HID_ID_usage(0x2341, 0x8037, 65472, 3072); //VID PID usage_page usage
  if (dev_list!=null && dev_list.length>0) {
    //println(dev_list);   
    try {
      target_device=dev_list[0].open();
    }
    catch (Exception ex) {
      ex.printStackTrace();
    }
  } else {
    //println("DEV not found");
  }
}

void setup() {
  init_HID();
  //print_HID_devices();

  init_device();
  frameRate(30);
}

void draw() {
  background(0);
  if (target_device!=null) {  
    byte buf[]=HID_read_from_device (target_device, 10);
    if (buf!=null) {
      if (buf.length>0) {
        println(buf);
      }
    }else{
      target_device=null;
    }
  } else {
    init_device();  //this part handles hot plugging
  }
}

void keyPressed() {
  if (key == ' ') {
    if (target_device!=null) {
      byte buf[]=new byte[4];
      buf[0]=(byte)1;
      buf[1]=(byte)2;
      buf[2]=(byte)3;
      buf[3]=(byte)4;
      HID_write_to_device(buf, target_device);
    }
  }
}