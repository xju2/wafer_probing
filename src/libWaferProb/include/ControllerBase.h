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
    bool m_is_connected;

public:
    float m_position[3];
    // float m_speed[3];

public:
    ControllerBase();
    virtual ~ControllerBase();
    int get_status() { return status; }
    bool is_connected() { return m_is_connected; }

    virtual int connect() = 0;
    virtual int disconnect() = 0;

    virtual int write(const string& cmd) = 0; // send command to device

    // unit of length: micro-meter
    virtual int set_speed(int axis, float value) = 0;

    virtual int mv_abs(int axis, float value) = 0; // move w.r.t home-position
    virtual int mv_rel(int axis, float value) = 0; // move w.r.t current-position

    virtual int stop() = 0; // stop motion immediately

    virtual int get_position() = 0;
    // virtual int get_speed() = 0;

    virtual int set_home() = 0;
    virtual int set_center() = 0;

};
#endif
