#include <stdio.h>

#include "ControllerZaber.h"

using namespace std;

ControllerZaber::ControllerZaber(const char* device_name):
    ControllerBase(),
    dn(device_name)
{
    port = -1;
}

int ControllerZaber::connect(){
    printf("%s:connecting to device %s", __FUNCTION__, dn.c_str());

    if( check(za_connect(&port, dn.c_str())) ) {
        printf("%s connected", dn.c_str());
        status = 0;
    } else {
        printf("%s not connected", dn.c_str());
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
    int n = sprintf(cmd, "/ %d set maxspeed %d\n", axis, steps);
    return write(cmd);
}

int ControllerZaber::mv_abs(int axis, float value){
    int steps = convert_mm_to_turns(value);
    char cmd[256];
    int n = sprintf(cmd, "/ %d move abs %d\n", axis, steps);
    return write(cmd);
}

int ControllerZaber::mv_rel(int axis, float value){
    int steps = convert_mm_to_turns(value);
    char cmd[256];
    int n = sprintf(cmd, "/ %d move rel %d\n", axis, steps);
    return write(cmd);
}

int ControllerZaber::get_position(int axis){
    char cmd[256];
    int n = sprintf(cmd, "/ %d get  pos\n", axis);
    return write(cmd);
}

int ControllerZaber::write(const string& cmd){
    if (port < 0){
        printf("%s is not open!", dn.c_str());
        return -1;
    }
    za_send(port, cmd.c_str());
    char reply[256] = {0};
    za_receive(port, reply, sizeof(reply));
    printf("%s\n", reply);
    return 0;
}

int ControllerZaber::convert_mm_to_turns(float value){
    // turns: 1952000 turns
    // length: 305000 micro-meter 
    return value / 0.15625; 
}

int ControllerZaber::set_home(){
    return write("/home\n");
}
