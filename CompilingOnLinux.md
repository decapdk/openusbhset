#Howto to compile on linux

# Introduction #

To be able to compile this project on linux you need to install libusb 1.0. I cannot provide details on this. Please google it :-D

# Details #

To be able to compile on linux you need only the main.cpp file. Currently I am developing and debugging on a Windows XP based platform using Visual Studio 2010 C++ Express Edition.

As i am no coding guru please bare with me.

To be able to compile on Linux you need to edit the main.cpp file.

Please change the line:

#include "libusb.h"

to

#include "libusb-1.0/libusb.h"

And then run the compile (very generic) command:

g++ main.cpp -lusb-1.0

This should produce a output file a.out that should be executable...