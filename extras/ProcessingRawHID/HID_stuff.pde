import com.codeminders.hidapi.HIDDeviceInfo;
import com.codeminders.hidapi.HIDManager;
import java.util.*;

HIDManager hid_mgr = null;

boolean thisIsWindows = false; //windows require a '0' report ID

public int init_HID() {

  String OS = System.getProperty("os.name", "generic").toLowerCase(Locale.ENGLISH);
  if (OS.indexOf("win") >= 0) {
    thisIsWindows = true;
  }

  try {
    ClassPathLibraryLoader.loadNativeHIDLibrary();
    hid_mgr = HIDManager.getInstance();
  }
  catch (Exception ex) {
    ex.printStackTrace();
    return 0;
  }
  return 1;
}

public int print_HID_devices() {
  if (hid_mgr==null) return 0;
  try {
    for (HIDDeviceInfo info : hid_mgr.listDevices ()) {
      //println(info.getProduct_string()+" "+info.getVendor_id()+" "+info.getProduct_id());
      println(info);
    }
  }
  catch (Exception ex) {
    ex.printStackTrace();
    return 0;
  }
  return 1;
}

public HIDDeviceInfo[] filter_HID_ID_usage(int vid, int pid, int usage_page, int usage) {
  if (hid_mgr==null) return null;
  List<HIDDeviceInfo> dev_list = new ArrayList<HIDDeviceInfo>();
  try {
    for (HIDDeviceInfo info : hid_mgr.listDevices ()) {
      if (info.getVendor_id()==vid && info.getProduct_id()==pid && info.getUsage_page()==usage_page && info.getUsage()==usage) {
        try {
          //println(info);
          dev_list.add(info);
        }
        catch (Exception ex) {
        }
      }
    }
  }
  catch (Exception ex) {
    ex.printStackTrace();
    return null;
  }

  HIDDeviceInfo[] dev_list_arr = new HIDDeviceInfo[ dev_list.size() ];
  dev_list.toArray( dev_list_arr );
  if (dev_list.size() > 0) println("Found " + dev_list.size() + " devices");
  return dev_list_arr;
}

public void HID_write_to_device (byte data[], HIDDevice device) {
  try {
    if (device!=null) {
      if (thisIsWindows) {
        byte dataWithReportID[] = new byte[data.length+1];
        dataWithReportID[0] = 0;
        System.arraycopy(data, 0, dataWithReportID, 1, data.length);
        device.write(dataWithReportID);
      } else {
        device.write(data);
      }
    }
  }
  catch (Exception ex) {
    ex.printStackTrace();
    target_device=null;
  }
}
public byte[] HID_read_from_device (HIDDevice device, int timeout) {
  byte buf[]=new byte[256];
  try {
    if (device!=null) {
      int returnedBytes = device.readTimeout(buf, timeout);
      byte retBuf[];
      retBuf=Arrays.copyOf(buf, returnedBytes);
      return retBuf;
    }
  }
  catch (Exception ex) {
    ex.printStackTrace();
  }
  return null;
}

void delay_ms(int ms) {
  try {    
    Thread.sleep(ms);
  }
  catch(Exception e) {
  }
}

