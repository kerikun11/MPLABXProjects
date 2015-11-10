---------------------------------------------------------------------------------
Summary
---------------------------------------------------------------------------------
The "windows_driver_installer_tool" software in this folder is an example program 
that uses the Microsoft DIFxAPIs to automate the Windows USB driver package 
installation process, and can be used with or without the hardware being attached 
to the system.  This example program is not specific to a given driver package, as
it checks the current folder (as the .exe file location) for any .inf files 
(.inf = driver package "information" files), and (pre-)installs any driver packages
that it finds.



---------------------------------------------------------------------------------
Background Info
---------------------------------------------------------------------------------
Some types of USB devices require that the end user install a vendor
supplied driver package onto their machine, in order to use the USB device.

USB Devices based on the Communication Device Class (CDC) and the vendor/custom
class WinUSB driver normally fall into this category (although WinUSB devices can
avoid a user installed driver package on Windows 8 and later, if the firmware implements
the right USB descriptors).


It is always possible to install driver packages manually by opening the Windows device 
manager, finding the (driverless) device, right clicking on it, selecting the update driver
option, and then manually browsing to the folder with the USB driver package .inf file.

This manual driver installation process is not ideal however for end consumers, and it is 
usually desirable to make the driver installation process more automated and easier for
the end consumer.  This can be achieved by using a software PC application program to
automatically install the USB driver package onto the machine, even if the USB hardware
device has not been attached to the system yet.  This software driver installer program 
could be implemented as either a stand alone PC application, or as part of the PC
application software that is normally intended to be used to interface with the USB device.

Microsoft provides some "DIFxAPI" DLL files that are useful for this purpose.  More information
about the DIFxAPIs can be found at:

http://msdn.microsoft.com/en-us/library/windows/hardware/ff544834(v=vs.85).aspx


