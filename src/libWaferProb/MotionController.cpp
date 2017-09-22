#include "MotionController.h"
#include <stdio.h>

#include <string>
#include <sstream>

using namespace std;
MotionController::MotionController(const char* dn_1):
    ControllerBase()
{
    xy_ctrl = new ControllerZaber(dn_1);
    m_position[0] = m_position[1] = -2;
}

MotionController::~MotionController(){
    disconnect();
}

int MotionController::connect() {
    if(xy_ctrl->connect() != 0){ 
        return 1;
    }
    xy_ctrl->unpark();
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
    // before disconnect, park the device.
    xy_ctrl->park();
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

int MotionController::get_position(){
    xy_ctrl->get_position();
    m_position[0] = xy_ctrl->m_position[0];
    m_position[1] = xy_ctrl->m_position[1];
    return 0;
}

int MotionController::get_position(int axis){
    get_position();
    return m_position[axis];
}

int MotionController::write(int axis, const string& cmd) 
{
    if(axis == 0 || axis == 1){
        xy_ctrl->write(cmd);
    }
    return 0;
}

int MotionController::set_home(){
    return xy_ctrl->set_home();
}

int MotionController::set_center(){
    return xy_ctrl->set_center();
}
