# First PlatformIO Arduino Project
This project will be used to guide initial setup of the Visual Studio Code IDE with the PlatformIO extension.  We will demonstrate a blinky LED, using the debugger, and using the logic analyzer.

## Installation steps
So far these have been tested on Linux (Fedora). We will need them for linux, mac, and windows to be safe.  It's also possible that there are many more dependencies folks will need to install if they are starting from scratch.

1. Install VSCode from Microsoft https://code.visualstudio.com/download 
2. Within VSCode, install the extensions: PlatformIO IDE, C/C++, C/C++ DevTools
3.  Fix the embedded debugger using the instructions here: https://github.com/platformio/platform-atmelavr/issues/313  (create a symbolic link between version 5 and version 6 libraries)
4. Try out the logic analyzer.  Packages required: pulseview, sigrok-firmware-fx2lafw  Tutorial: https://learn.sparkfun.com/tutorials/using-the-usb-logic-analyzer-with-sigrok-pulseview/all

## Other useful things
- Link to the datasheet for our microprocessor: https://www.microchip.com/en-us/product/ATmega2560 
- ELEGOO Tutorial and example code: https://www.elegoo.com/blogs/arduino-projects/elegoo-mega-2560-the-most-complete-starter-kit-tutorial 
-- This tutorial uses Arduino IDE which is an OK option as well, but will not allow you to use the debugger.  VSCode is highly recommended.
