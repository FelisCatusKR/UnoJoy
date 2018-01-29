
UnoJoy IIDX
===========

Introduction
------------
UnoJoy IIDX is a sketch for Arduino Uno which allows you to easily turn your Arduino Uno (or Mega or any compatible boards with ATmega8u2) into a PC converter for Beatmania IIDX controllers. It uses [UnoJoy](https://github.com/AlanChatham/UnoJoy) as PC driver module, [Arduino_PSXPad](https://github.com/AZO234/Arduino_PSXPad) as library for Beatmania IIDX controllers.  
UnoJoy IIDX is licensed under the [GNU General Public License v3.0](https://www.gnu.org/licenses/gpl-3.0.en.html).

Getting Started
---------------
It is a three-part system:
1. Drivers - Needed to re-flash the Arduino's USB communication chip
2. Software - The UnoJoy library for Arduino
3. Firmware - Code to load onto Arduino's USB communication chip
In order to make UnoJoy IIDX work, you'll need to take care of all parts.

Connecting Controller(s)
------------------------
Before you start setting UnoJoy IIDX, you have to make circuit for controllers. PS2 controller port has 9 pins: 
>     ───────────── 
>     │123|456|789│ (controller side)
>     └───────────┘
> 1 : DAT -> Arduino 12 MISO [need pullup by 1k owm registor to 5V]  
2 : CMD -> Arduino 11 MOSI  
3 : 9V (for motor, won't use)
> 
> 4 : GND  
5 : 3.3V  
6 : Attention -> Arduino 2 DigitalPin (can be changed)
>
> 7 : SCK -> Arduino 13 SCK  
8 : NC (won't use)  
9 : ACK (won't use)

If you want to use 2 controllers, you should connect DAT, CMD, SCK of both controllers as SS line of SPI bus, Attention to Arduino 3 DigitalPin (which also can be changed). If you are not familiar at SS line, check [here](https://learn.sparkfun.com/tutorials/serial-peripheral-interface-spi/slave-select-ss).

Installing Drivers
------------------
In the Drivers directory, there are installer files for the drivers you'll need for the DFU bootloader.

**On Windows**, you should run *UnoJoyDriverInstaller.bat*. you'll also need to download and install [Atmel's FLIP tool](http://www.atmel.com/tools/FLIP.aspx).  
**On Mac OS X**, you should run one of these files, *LionUnoJoyDrivers.pkg* or *SnowLeopardUnoJoyDrivers.pkg*, depends on your system.  
**On Linux**, you'll need to install *dfu-programmer*. you can get it by typing to your terminal:
>     sudo apt-get install dfu-programmer
or
>     sudo aptitude install dfu-programmer 
depending on your distribution. You can also build it from [source](https://github.com/dfu-programmer/dfu-programmer). You also have to make the flashing script runnable by typing:
>     chmod +x TurnIntoAJoystick.sh
into your terminal when in UnoJoy directory.

Uploading Sketch
----------------
There are two versions of UnoJoy IIDX: *UnoJoy-IIDX* and *DoubleJoy-IIDX*. **UnoJoy-IIDX** is a version for connecting one controller. On the other hand, **DoubleJoy-IIDX** allows you to connect two controllers. You can use DoubleJoy-IIDX for connecting just one controller, but it may slows down the response time so be careful.

After selecting the version of UnoJoy, you have to upload the sketch to your Arduino. Open the
> *(root_of_UnoJoy_IIDX)*/Software/*(your_version_of_UnoJoy_IIDX)*/*(your_version_of_UnoJoy_IIDX)*.ino

with Arduino IDE and upload it. Be sure you already have installed the library.

Configuring Hardware
--------------------
Now that we have the proper code on the Arduino, you need to reprogram the communications chip on the Arduino. In order to do this, you need to first put the Arduino into 'Arduino UNO DFU' mode. The official documentation for this is [here](http://arduino.cc/en/Hacking/DFUProgramming8U2)

You do that by shorting two of the pins on the block of 6 pins between the USB connector.  Using a piece of wire or other small metal object, connect the 2 pins closes to the USB connector together. (the ones that turn from o to | in the diagram)
>              o o o                    | o o 
>     |----|   o o o           |----|   | o o
>     |    |                   |    |
>     |USB |          ---->    |USB |
>     |    |                   |    |
>     |----|                   |----|

It should disconnect (be-dun.) and reconnect (buh-din!) and now show up to your system as 'Arduino UNO DFU'. In OSX, you will get no feedback from your computer, but the lights on the Arduino will stop flashing.

Once the Arduino is in DFU mode, to update the firmware, simply click:
> Windows: TurnIntoAJoystick.bat  
OSX:     TurnIntoAJoystick.command  
Linux:   ./TurnIntoAJoystic.sh

> IMPORTANT: Once you update the firmware, you'll need to unplug and plug the Arduino back in for it to show up with the new firmware - it'll just hang out in DFU mode until you do.

When you plug the Arduino in again now, it will show up to your computer as an 'UnoJoy Joystick'. You can check this by doing the steps in the next section.

HOW TO CHECK WHICH MODE YOU ARE IN
----------------------------------
**On Windows 7 or above**, you can check it out by going to:
> Start->Devices and Printers  
and you should see it there under 'Unspecified'
>
> In Arduino mode, it will appear as 'Arduino UNO (COM 23)'  
In DFU mode, it will appear as 'Arduino UNO DFU'  
In UnoJoy mode, it will appear at the top as 'UnoJoy Joystick'

**On OSX**, you should see it:
> **Snow Leopard**: Apple->About This Mac->More Info...->USB  
**Lion**: Apple->About This Mac->More Info...->System Report->USB  
You may need to refresh (command-R) to see it update.
> 
> In Arduino mode, it will appear as 'Arduino UNO'  
In DFU mode, it will appear as 'Arduino UNO DFU'  
In UnoJoy mode, it will appear at the top as 'UnoJoy Joystick'

**On Linux**, you can type lsusb to your terminal.
> In response you'll get list of all connected usb devices.
>
> From there you should find:  
In Arduino mode, you should see  a device named Arduino Uno etc.  
In DFU mode, you should see  a device named Atmel corp. etc.  
In UnoJoy mode, you should see a device named Cygnal Integrated Products etc.
