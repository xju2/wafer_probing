#include "Handler.h"
#include "Helper.h"

#include <vector>
#include <stdio.h>
#include <stdlib.h>

Handler::Handler(){
    ctrl = new MotionController();
    ctrl->connect();

    supported_actions = new vector<string>();
    /** To be deleted
    supported_actions->push_back("MA");
    supported_actions->push_back("MR");
    supported_actions->push_back("SP");
    supported_actions->push_back("SH");
    supported_actions->push_back("SC");
    supported_actions->push_back("SS");
    supported_actions->push_back("SDZ");
    **/
}

Handler::~Handler(){
    ctrl->disconnect();
    delete ctrl;
    delete supported_actions;
}


void Handler::write(const string& cmd) {
    if(cmd.empty()){
        return;
    }
    vector<string> items;
    WaferProb::tokenizeString(cmd, ' ', items);
    const string& action(items[0]);

    // Check each case..
    if(action == "MA"){
        if(items.size() != 3){
            printf("argument of MA is wrong\n"
                    "MA X/Y/Z 10\n");
            return;
        }
        int axis = axis_number(items[1]);
        ctrl->mv_abs(axis, atof(items[2].c_str()));
    } else if (action == "MR"){
        if(items.size() != 3){
            printf("argument of MV is wrong\n"
                    "MV X/Y/Z 10\n");
            return;
        }
        int axis = axis_number(items[1]);
        ctrl->mv_rel(axis, atof(items[2].c_str()));
    } else {
        printf("%s not supported yet!\n", action.c_str());
        // print_cmd();
    }
}

void Handler::print_cmd(){
    printf("MA X 10  // move X-axis w.r.t home position 10 micro-meter\n"
            "MR X 10  // move X-axis w.r.t current position 10 micro-meter\n"
            "SP X 10  // set speed in x-axis direction by 10 micro-meter/s\n"
            "SH // set current position as HOME\n"
            "SC // set needles contact with chip\n"
            "SS // set needles separate from chip\n"
            "SDZ 10 // set distance in z-axis in order to separate needle and chip.\n"
            );
}

bool Handler::is_supported(const string& action) const {
    vector<string>::iterator itr_sa = supported_actions->begin();
    vector<string>::iterator end_sa = supported_actions->begin();
    bool results = false;
    for(; itr_sa != end_sa; itr_sa){
        if( *itr_sa == action){
            results = true;
            break;
        }
    }
    return results;
}

int Handler::axis_number(const string& axis_str) const {
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
