#ifndef __WaferProb_ControllerZaber_H__
#define __WaferProb_ControllerZaber_H__

#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 199309L
#endif

#include <string>

#include "za_serial.h" // Driver of Zaber
#include "ControllerBase.h"

using namespace std;
class ControllerZaber : public ControllerBase{
private:
    z_port port; //port connected to Zaber
    string dn; // device name

public: // implement controller's interface
    ControllerZaber(const char* device_name);
    ~ControllerZaber();

    int connect();
    int disconnect();

    int set_speed(int axis, float sp);

    int mv_abs(int axis, float value); // move w.r.t home-position
    int mv_rel(int axis, float value); // move w.r.t current-position

    // get current position
    int get_position(int axis);

    int set_home();
    int set_center();

    int write(const string& cmd);
    const char* device_name();

public:
    // park the device: lock it so that when powered up, 
    // don't need to homed.
    int park(); 
    int unpark(); 

private:
    // convert mili-meter to number of turns/steps
    int convert_mm_to_turns(float value);

    inline bool check(int rc){
        // if(rc != Z_SUCCESS) throw rc;
        return rc == Z_SUCCESS;
    }
    void poll_until_idle();
};
#endif
