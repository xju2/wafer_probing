#include "MotionController.h"
#include <stdio.h>

#include <string>
#include <sstream>

using namespace std;
MotionController::MotionController(const char* dn_1):
    ControllerBase()
{
    xy_ctrl = new ControllerZaber(dn_1);
}

MotionController::~MotionController(){
    disconnect();
}

int MotionController::connect() {
    xy_ctrl->connect();
    // xy_ctrl->set_home();

    // connect z station
    /**
    const string& cmd_con("192.168.1.32 --subscribe ALL");
    check_z(GOpen(cmd_con.c_str(), &z_ctrl));
    printf("Z station is connected.\n");
    ***/
    return 0;
}

int MotionController::disconnect(){
    /** 
     * dont' do that 
     before disconnect, park the device.
    if(xy_ctrl->park() == 0){
        printf("%s is parked\n", xy_ctrl->device_name());
    }
    ***/
    xy_ctrl->disconnect();
    return 0;
}

int MotionController::set_speed(int axis, float sp){
    if (axis == 0 || axis == 1) { // x-y-axis
        xy_ctrl->set_speed(axis+1, sp);
    } else if (axis == 2) {
        // not yet
    } else {
        ;
    }
    return 0;
}

int MotionController::mv_abs(int axis, float value){
    if(axis == 0 || axis == 1){
        xy_ctrl->mv_abs(axis+1, value);
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
        xy_ctrl->mv_rel(axis+1, value);
    } else if (axis == 2) {
    } else {}
    return 0;
}

int MotionController::get_position(int axis){
    if(axis == 0 || axis == 1){
        xy_ctrl->get_position(axis+1);
    } else if (axis == 2) {
    } else {}
    return 0;
}
int MotionController::write(int axis, const string& cmd) 
{
    if(axis == 0 || axis == 1){
        xy_ctrl->write(cmd);
    }
    return 0;
}

int MotionController::set_home(){
    xy_ctrl->set_home();
}

int MotionController::set_center(){
    xy_ctrl->set_center();
}
