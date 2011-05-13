#include <stdio.h>
#include <iostream>
#include "libusb.h"

using namespace std;

#define DATA_SIZE 64

void SetVIDPID(void);
uint8_t TypeSelector(void);
uint8_t TestSelector(void);

uint16_t vid = 0;
uint16_t pid = 0;

int main()
{
	// Enumerators
	//enum eTestSelector {Reserved=0,Test_J=1,Test_K=2,Test_SE0_NAK=3,Test_Packet=4,Test_Force_Enable=5};

	// USB parameters
	libusb_device_handle *handle;
	
	//eTestSelector ts;
	
	uint8_t data[DATA_SIZE];

	char type;
	char test;
	char port;
	char port_cnt;
	int tmp_test;
	int tmp_port;
	int tmp_port_cnt;

	int r = libusb_init(NULL);
	if (r < 0)
		return r;

	//Input Vendor ID (vid) and Product ID (pid)
	cout << "+-----------------------------------------------+" << endl;
	cout << "|                                               |" << endl;
	cout << "|       Welcome to USBHSET for libusb 1.0       |" << endl;
	cout << "|          Designed by: René Haunstrup          |" << endl;
	cout << "|                                               |" << endl;
	cout << "+-----------------------------------------------+" << endl << endl;

SETTYPE:
	type = TypeSelector();
	//type = '3';

SETUSBID:
	SetVIDPID();	// Black USB hub

	//vid = 0x1a40;
	//pid = 0x0101;

	printf("Searching for USB device with VID: %04x and PID: %04x...",pid,vid);
	cout << endl;

	//Get usb handle
	handle = libusb_open_device_with_vid_pid(NULL,vid,pid);
	if (handle == NULL) {
		printf("Failed to find device.\n");
		goto SETUSBID; }
	else{ printf("Found device...\n"); }

SETTEST:
	test = TestSelector();
	tmp_test = test-48;
	//test = '4';

	switch(type)
	{
	case '1':
		{
			//Host Testing
			break;
		}
	case '2':
		{
			//Device Testing
			libusb_control_transfer(handle,0,3,2,tmp_test<<8,data,0,1000);
		}
	case '3':
		{
			////Hub Testing
			// Get port and port count
			cout << " Please specify ports on hub: ";
			port_cnt = 0;
			while(port_cnt < '1' || port_cnt > '9')
			{
				port_cnt = cin.get();
			}
			cout << endl;
			cout << "Please input port to test: ";
			port = 0;
			while(port < '1' || port > port_cnt)
			{
				port = cin.get();
			}
			cout << endl;

			tmp_port = port-48;
			tmp_port_cnt = port_cnt-48;

			// Suspend Other ports
			for(int i=1; i<=tmp_port_cnt;i++)
			{
				if(i!=tmp_port)
					libusb_control_transfer(handle,0x23,3,2,i,data,0,1000);
			}
			libusb_control_transfer(handle,0x23,3,21,tmp_test<<8|tmp_port,data,0,1000);
		}
	}

	libusb_exit(NULL);

	cout << "Press Enter to exit...";
	cin.sync();
	cin.get();

	return 0;
}

void SetVIDPID()
{
	cout << "Please use lsusb to locate your device PID " << endl;
	cout << "and VID before continuing..." << endl << endl;

	cout << "Please input Vendor ID (as Hex): ";
	cin >> hex >> vid;
	cout << "Please input Product ID (as Hex): ";
	cin >> hex >> pid;
}

uint8_t TypeSelector()
{
	cout << "+-----------------------------------------------+" << endl;
	cout << "|                                               |" << endl;
	cout << "|  Available Tests                              |" << endl;
	cout << "|    1) Host                                    |" << endl;
	cout << "|    2) Device                                  |" << endl;
	cout << "|    3) Hub                                     |" << endl;
	cout << "|                                               |" << endl;
	cout << "+-----------------------------------------------+" << endl << endl;
	cout << "Please select type of test: ";


	uint8_t selection = 0;
	while(selection < '1' || selection > '3')
	{
		selection = cin.get();
	}
	cout << endl;

	switch(selection)
	{
	case '1':
		{
			cout << "+-----------------------------------------------+" << endl;
			cout << "|                                               |" << endl;
			cout << "|         Host testing not implemented          |" << endl;
			cout << "|                                               |" << endl;
			cout << "+-----------------------------------------------+" << endl << endl;
			break;
		}
	case '2':
		{
			cout << "+-----------------------------------------------+" << endl;
			cout << "|                                               |" << endl;
			cout << "|            DEVICE TESTING ACTIVE              |" << endl;
			cout << "|                                               |" << endl;
			cout << "+-----------------------------------------------+" << endl << endl;
			break;
		}
	case '3':
		{
			cout << "+-----------------------------------------------+" << endl;
			cout << "|                                               |" << endl;
			cout << "|              HUB TESTING ACTIVE               |" << endl;
			cout << "|                                               |" << endl;
			cout << "+-----------------------------------------------+" << endl << endl;
			break;
		}
	}
	return selection;
}

uint8_t TestSelector()
{
	cout << "+-----------------------------------------------+" << endl;
	cout << "|                                               |" << endl;
	cout << "|  Available Tests Types                        |" << endl;
	cout << "|    0) None                                    |" << endl;
	cout << "|    1) Test J                                  |" << endl;
	cout << "|    2) Test K                                  |" << endl;
	cout << "|    3) Test SE0 NAK                            |" << endl;
	cout << "|    4) Test Packet                             |" << endl;
	cout << "|    5) Test Force Enable                       |" << endl;
	cout << "|                                               |" << endl;
	cout << "+-----------------------------------------------+" << endl << endl;
	cout << "Please select type of test: ";

	uint8_t selection = 255;
	while(selection < '0' || selection > '5')
	{
		selection = cin.get();
	}

	switch(selection)
	{
	case '0':
		{
			cout << "None selected...";
			break;
		}
	case '1':
		{
			cout << "Test J selected...";
			break;
		}
	case '2':
		{
			cout << "Test K selected...";
			break;
		}
	case '3':
		{
			cout << "Test SE0 NAK selected...";
			break;
		}
	case '4':
		{
			cout << "Test Packet selected...";
			break;
		}
	case '5':
		{
			cout << "Test Force Enable selected...";
			break;
		}
	}

	return selection;
}