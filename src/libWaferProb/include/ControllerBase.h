#ifndef __WaferProb_ControllerBase_H__
#define __WaferProb_ControllerBase_H__

/*
 * Define a general interface for a controller.
 */
#include <string>

using namespace std;
class ControllerBase{

protected:

    int status; // 0 is ok, non-zero indicates problems

public:
    ControllerBase();
    virtual ~ControllerBase();
    int get_status();

    virtual int connect() = 0;
    virtual int disconnect() = 0;

    // unit of length: micro-meter
    virtual int set_speed(int axis, float value) = 0;

    virtual int mv_abs(int axis, float value) = 0; // move w.r.t home-position
    virtual int mv_rel(int axis, float value) = 0; // move w.r.t current-position

    virtual int get_position(int axis) = 0; // report current position

    virtual int set_home() = 0;
    virtual int set_center() = 0;

    virtual int write(const string& cmd) = 0; // send command to device
};
#endif
