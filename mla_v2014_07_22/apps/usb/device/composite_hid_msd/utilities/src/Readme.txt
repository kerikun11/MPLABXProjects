This demo uses the same application level protocols and HID interface settings as the HID custom demo located in the "<install_directory>/apps/usb/device/hid_custom" folder.  The utilities for this demo are also generated from the same source base, located at "<install_directory>/apps/usb/device/hid_custom/utilities/src" folder.

The "plug_and_play_demo_composite_pid_0x0054.exe" executable program
was generated using the exact same source code as that used to create the
"plug_and_play_example.exe", with one exeception.

The "plug_and_play_example.exe" source code is found in the following directory (assuming default
installation directory):

"<install_directory>/apps/usb/device/hid_custom/utilities/src"

To create the "plug_and_play_demo_composite_pid_0x0054.exe" file, the source code was compiled, with the MY_DEVICE_ID
definition (declared near the top of Form1.h) set to:

#define MY_DEVICE_ID  "Vid_04d8&Pid_0054"

(if using the C# source code, the VID/PID is set in Form1.cs, in the line that reads:
String DeviceIDToFind = "Vid_04d8&Pid_003f";
in the CheckIfPresentAndGetUSBDevicePath() function)

The "simple_demo_composite_pid_0x0054.exe" executable
program was generated  using the exact same source code as that used to create the
"basic_example.exe", with one exeception.

The basic_example.exe source code is found in the following directory (assuming default
installation directory):

"<install_directory>/apps/usb/device/hid_custom/utilities/basic_example/windows/vc++2005_express/src"

To create the "simple_demo_composite_pid_0x0054.exe" file, the 
"basic_example.exe" source code was compiled, with the MY_DEVICE_ID
definition (declared near the top of Form1.h) set to:

#define MY_DEVICE_ID  "Vid_04d8&Pid_0054"