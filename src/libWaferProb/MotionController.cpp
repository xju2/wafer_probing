#include "MotionController.h"
#include <stdio.h>

#include <string>
#include <sstream>

using namespace std;
MotionController::MotionController(){
    status = connect();
}

MotionController::~MotionController(){
    status = disconnect();
}

int MotionController::get_status(){
    return status;
}

int MotionController::connect() {
    // connect x-y station
    const char* device_name = "/dev/ttyACM0";
    check_xy(za_connect(&xy_ctrl, device_name));
    printf("XY station is connected.\n");

    // connect z station
    /**
    const string& cmd_con("192.168.1.32 --subscribe ALL");
    check_z(GOpen(cmd_con.c_str(), &z_ctrl));
    printf("Z station is connected.\n");
    ***/
    return 0;
}

int MotionController::disconnect(){
    za_disconnect(xy_ctrl);

    return 0;
}

int MotionController::send_cmd_to_xy(const char* cmd){
    za_send(xy_ctrl, cmd);
    char reply[256] = {0};
    za_receive(xy_ctrl, reply, sizeof(reply));
    printf("%s\n", reply);
    return 0;
}

int MotionController::set_speed(int axis, float sp){
    if (axis == 0 || axis == 1) { // x-y-axis
        int steps = convert_mm_to_turns(sp);
        char cmd[256];
        int n = sprintf(cmd, "/ %d set maxspeed %d\n", axis+1, steps);
        send_cmd_to_xy(cmd);
    } else if (axis == 2) {
        // not yet
    } else {
        ;
    }
    return 0;
}

int MotionController::mv_abs(int axis, float value){
    if(axis == 0 || axis == 1){
        int steps = convert_mm_to_turns(value);
        char cmd[256];
        int n = sprintf(cmd, "/ %d move abs %d\n", axis+1, steps);
        send_cmd_to_xy(cmd);
    } else if (axis == 2){
        // not yet
        ;
    } else {
        ;
    }
    return 0;
}

int MotionController::mv_rel(int axis, float value) {
    if(axis == 0 || axis == 1){
        int steps = convert_mm_to_turns(value);
        char cmd[256];
        int n = sprintf(cmd, "/ %d move rel %d\n", axis+1, steps);
        send_cmd_to_xy(cmd);
    } else if (axis == 2) {
    } else {}
    return 0;
}

int MotionController::get_position(int axis){
    if(axis == 0 || axis == 1){
        char cmd[256];
        int n = sprintf(cmd, "/ %d get  pos\n", axis+1);
        send_cmd_to_xy(cmd);
    } else if (axis == 2) {
    } else {}
    return 0;
}
