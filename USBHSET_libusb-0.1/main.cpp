#include <stdio.h>
#include <iostream>
#include "usb.h"

using namespace std;

// Device vendor and product id.
#define MY_VID 0x2001
#define MY_PID 0x3c05

usb_dev_handle *open_dev(void)
{
    struct usb_bus *bus;
    struct usb_device *dev;

    for (bus = usb_get_busses(); bus; bus = bus->next)
    {
        for (dev = bus->devices; dev; dev = dev->next)
        {
            if (dev->descriptor.idVendor == MY_VID
                    && dev->descriptor.idProduct == MY_PID)
            {
                return usb_open(dev);
            }
        }
    }
    return NULL;
}

int main()
{
	usb_dev_handle *dev = NULL; /* the device handle */

	char data[64];

    usb_init(); /* initialize the library */
    usb_find_busses(); /* find all busses */
    usb_find_devices(); /* find all connected devices */

    if (!(dev = open_dev()))
    {
        printf("error opening device: \n%s\n", usb_strerror());
        return 0;
    }
    else
    {
        printf("success: device %04X:%04X opened\n", MY_VID, MY_PID);
    }

	usb_control_msg(dev,0,3,2,0x0400,data,0,1000);

	usb_close(dev);
	
	cin.sync();
	cin.get();

	return 0;
}