/*
 * Here the example assumes a single device is connected to "/dev/ttyUSB0",
 * using the ASCII protocol at the default baud rate (115200). It also assumes
 * it is being compiled and run on a machine using glibc, eg. Linux.
 */

/* this #define is required for nanosleep: see feature_test_macros(7) */
#define _POSIX_C_SOURCE 199309L
#include <time.h>
#include <stdio.h>
#include <string.h>

#include "za_serial.h"

#include <string>
#include <iostream>
using namespace std;
void poll_until_idle(z_port port)
{
    char reply[256] = { 0 };
	struct za_reply decoded_reply;
    const struct timespec ts = { 0, 100000000 }; /* 100mil nanosec = 100ms */

	/* We use za_decode() to decode this string into more manageable parts,
	 * sorting them into the fields of a za_reply struct, then we test
	 * the device_status field. Possible values for device_status are "IDLE"
	 * and "BUSY". */
    for(;;)
    {
        za_send(port, "/\n");
        za_receive(port, reply, sizeof(reply));
		za_decode(&decoded_reply, reply);

        if(strncmp(decoded_reply.device_status, "BUSY", 4) == 0)
		{
            nanosleep(&ts, NULL); /* If we're busy, wait then try again */
		}
        else
		{
			break;
		}
    }
}

void send(z_port port, const char* cmd){
	char reply[256] = { 0 };

    za_send(port, cmd);
    za_receive(port, reply, sizeof(reply));

    printf("%s -> %s\n", cmd, reply);

    poll_until_idle(port);
}
/* We take some shortcuts here in main() for the sake of demonstration and code
 * clarity, namely not checking every function's return value. Special care has
 * been taken in this API to provide meaningful return values, and we encourage
 * you to check every one of them in your final production-quality code! */
int main(int argc, char** argv)
{
    // give the port number
    if (argc < 2){
        printf("%s device_name\n", argv[0]);
        printf("e.g: /dev/ttyACM0, /dev/tty.usbmodem1411\n");
        return 1;
    }
    z_port port;
	char *device_name = argv[1];

	if (za_connect(&port, device_name) != Z_SUCCESS)
	{
		printf("Could not connect to device %s.\n", device_name);
		return -1;
	} else {
        printf("%s is connected\n", device_name);
    }

    string input = "";
    while(true){
        printf("please enter commands, q for quit\n");
        getline(cin, input);
        if(input[0] == 'q') break;
        if(input[0] == '\n') continue;
        char cmd[256];
        int n = sprintf(cmd, "%s\n", input.c_str());
        send(port, cmd);
    }
    za_disconnect(port);

    return 0;
}

