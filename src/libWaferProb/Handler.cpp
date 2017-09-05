#include "Handler.h"
#include "Helper.h"

#include <vector>
#include <stdio.h>
#include <stdlib.h>

Handler::Handler(){
    ctrl = new MotionController("/dev/ttyACM0");
    ctrl->connect();
}

Handler::~Handler(){
    ctrl->disconnect();
    delete ctrl;
}


int Handler::axis_number(const string& axis_str) const {
    // need to do better than this!
    int axis = -1;
    if(axis_str == "X" or axis_str == "x") {
        axis = 0;
    }
    if(axis_str == "Y" or axis_str == "y") {
        axis = 1;
    }
    if(axis_str == "Z" or axis_str == "z") {
        axis = 2;
    }
    if (axis < 0) {
        printf("Axis is wrong. Use X instead.");
        axis = 0;
    }
    return axis;
}

void Handler::print_cmd(){
    printf("MA X 10  --> move X-axis w.r.t home position 10 micro-meter\n"
            "MR X 10 --> move X-axis w.r.t current position 10 micro-meter\n"
            "SP X 10  --> set speed in x-axis direction by 10 micro-meter/s\n"
            "SH --> move to HOME\n"
            "SM --> move to center\n"
            "SZC --> set needles contact with chip\n"
            "SZS --> set needles separate from chip\n"
            "SZD 10 --> set distance in z-axis in order to separate needle and chip.\n"
            "----------------------------------------------------------\n"
            // "MVC X P --> move to positive x-axis direction, continuously\n" 
            // "MVC X N --> move to negative x-axis direction, continuously\n"  
            );
}

void Handler::write(const string& cmd) {
    if(cmd.empty()){
        return;
    }
    vector<string> items;
    WaferProb::tokenizeString(cmd, ' ', items);
    const string& action(items[0]);

    // Check each case..
    if (action == "MA")
    {
        if(items.size() != 3){
            printf("argument of MA is wrong\n"
                    "MA X/Y/Z 10\n");
            return;
        }
        int axis = axis_number(items[1]);
        ctrl->mv_abs(axis, atof(items[2].c_str()));
    } else if (action == "MR")
    {
        if(items.size() != 3){
            printf("argument of MR is wrong\n"
                    "MR X/Y/Z 10\n");
            return;
        }
        int axis = axis_number(items[1]);
        ctrl->mv_rel(axis, atof(items[2].c_str()));
    } else if (action == "SH")
    {
        ctrl->set_home();
    } else if (action == "SM")
    {
        ctrl->set_center();
    } else if (action == "SP")
    {
        if (items.size() != 3){
            printf("argument of SP is wrong\n"
                    "SP X/Y/Z 10000\n");
            return;
        }
        int axis = axis_number(items[1]);
        ctrl->set_speed(axis, atof(items[2].c_str()));
    } else {
        printf("%s not supported yet!\n", action.c_str());
        // print_cmd();
    }
}
