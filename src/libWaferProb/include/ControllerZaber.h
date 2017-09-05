#ifndef __WaferProb_ControllerZaber_H__
#define __WaferProb_ControllerZaber_H__

#include <string>

#include "za_serial.h" // Driver of Zaber
#include "ControllerBase.h"

using namespace std;
class ControllerZaber : public ControllerBase{
private:
    z_port port; //port connected to Zaber
    string dn; // device name

public:
    ControllerZaber(const char* device_name);
    ~ControllerZaber();

    int connect();
    int disconnect();

    int set_home();
    int set_speed(int axis, float sp);

    int mv_abs(int axis, float value); // move w.r.t home-position
    int mv_rel(int axis, float value); // move w.r.t current-position

    // get current position
    int get_position(int axis);

    int write(const string& cmd);

private:
    // convert mili-meter to number of turns/steps
    int convert_mm_to_turns(float value);

    inline bool check(int rc){
        // if(rc != Z_SUCCESS) throw rc;
        return rc == Z_SUCCESS;
    }
};
#endif
