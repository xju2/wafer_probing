#include <stdio.h>
#include <stdlib.h>

#include "ControllerGalil.h"

#include <vector>
#include "Helper.h"

ControllerGalil::ControllerGalil(const char* device_name){
    char device[256];
    sprintf(device, "%s --subscribe ALL", device_name);
    dn = string(device);
    port = 0;
    m_position[0] = m_position[1] = m_position[2] = DEFAULT_GALIL_POS;
}

ControllerGalil::~ControllerGalil(){
    disconnect();
}

int ControllerGalil::connect(){
    printf("%s: connecting to device %s\n", __FUNCTION__, dn.c_str());
    if( check(GOpen(dn.c_str(), &port)) ){
        printf("%s connected\n", dn.c_str());
        status = 0;
    } else {
        printf("%s not connected\n", dn.c_str());
        status = 1;
    }
    return status;
}

int ControllerGalil::disconnect(){
    if(port != 0){
        GClose(port);
        port = 0;
    }
    return 0;
}

int ControllerGalil::write(const string& cmd){
    if (port == 0){
        printf("%s is not open\n", dn.c_str());
        return -1;
    }
    if( check(GCmd(port, cmd.c_str())) != 0){
        printf("%s is not recognised\n", cmd.c_str());
        return -2;
    }
    return 0;
}

int ControllerGalil::set_speed(int axis, float sp)
{
    int steps = convert_mm_to_turns(sp);

    char cmd[256];
    sprintf(cmd, "SP %d", steps);
    return write(cmd);
}

int ControllerGalil::mv_abs(int axis, float value){
    string cmd = generate_cmd("PA", axis, value);
    write(cmd);
    make_a_move(axis);
    return 0;
}

int ControllerGalil::mv_rel(int axis, float value){
    string cmd = generate_cmd("PR", axis, value);
    write(cmd);

    make_a_move(axis);
    return 0;
}

int ControllerGalil::get_position(){
    if(port == 0) return -1;

    char* trimmed;
    GCmdT(port, "RP", buf, sizeof(buf), &trimmed);
    string data(trimmed);

    vector<string> raw_items;
    WaferProb::tokenizeString(data, ' ', raw_items);
    for(int i = 0; i < (int) raw_items.size(); i++){
        m_position[i] = convert_turns_to_mm(atof(raw_items.at(i).c_str()));
    }
    return 0;
}

int ControllerGalil::set_home(){
    return 0;
}

int ControllerGalil::set_center(){
    return 0;
}

string ControllerGalil::generate_cmd(const char* cmd, int axis, float value){
    int steps = convert_mm_to_turns(value);
    char val_str[256];
    sprintf(val_str, "%d", steps);
    string cmd_val(",,");
    cmd_val.insert(axis, val_str);

    char res_str[256];
    sprintf(res_str, "%s %s", cmd, cmd_val.c_str());
    return string(res_str);
}

void ControllerGalil::make_a_move(int axis){
    char mv[256];
    char axis_name = axis_index_to_name(axis);
    sprintf(mv, "BG %c", axis_name);

    write(mv);
    // block until motion is complete.
    GMotionComplete(port, string(1, axis_name).c_str());
}
