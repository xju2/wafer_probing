#include <stdio.h>
#include <string.h>

#include "ControllerZaber.h"

using namespace std;

ControllerZaber::ControllerZaber(const char* device_name):
    ControllerBase(),
    dn(device_name)
{
    port = -1;
}

int ControllerZaber::connect(){
    printf("%s:connecting to device %s\n", __FUNCTION__, dn.c_str());

    if( check(za_connect(&port, dn.c_str())) ) {
        printf("%s connected\n", dn.c_str());
        status = 0;
    } else {
        printf("%s not connected\n", dn.c_str());
        status = 1;
    }
    return status;
}

ControllerZaber::~ControllerZaber(){
    disconnect();
}

int ControllerZaber::disconnect(){
    if (port > 0){
        za_disconnect(port);
        port = -1;
    }
}

int ControllerZaber::set_speed(int axis, float value)
{
    int steps = convert_mm_to_turns(value);
    char cmd[256];
    int n = sprintf(cmd, "/1 %d set maxspeed %d\n", axis, steps);
    return write(cmd);
}

int ControllerZaber::mv_abs(int axis, float value){
    int steps = convert_mm_to_turns(value);
    char cmd[256];
    int n = sprintf(cmd, "/1 %d move abs %d\n", axis, steps);
    return write(cmd);
}

int ControllerZaber::mv_rel(int axis, float value){
    int steps = convert_mm_to_turns(value);
    char cmd[256];
    int n = sprintf(cmd, "/1 %d move rel %d\n", axis, steps);
    return write(cmd);
}

int ControllerZaber::get_position(int axis){
    char cmd[256];
    int n = sprintf(cmd, "/1 %d get  pos\n", axis);
    return write(cmd);
}


int ControllerZaber::set_home(){
    return write("/home\n");
}

int ControllerZaber::set_center(){
    // 1952000/2. = 976000
    return write("/move abs 976000\n");
}

int ControllerZaber::park(){
    return write("/tools parking park\n");
}

int ControllerZaber::write(const string& cmd)
{
    if (port < 0){
        printf("%s is not open!", dn.c_str());
        return -1;
    }
    za_send(port, cmd.c_str());
    char reply[256] = {0};
    za_receive(port, reply, sizeof(reply));
    printf("%s-> %s\n", cmd.c_str(), reply);

    poll_until_idle();
    return 0;
}

int ControllerZaber::convert_mm_to_turns(float value){
    // turns: 1952000 turns
    // length: 305000 micro-meter 
    return value / 0.15625; 
}

void ControllerZaber::poll_until_idle(){
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

const char* ControllerZaber::device_name(){
    return dn.c_str();
}
