#ifndef __MontionController_H_
#define __MontionController_H_

/*
 * A passive montion controller.
 * It controls the station to move in x-y-z directions,
 * but has no idea of stations's position,
 * yet it can give the position when inqury comes.
 */
#include "za_serial.h"
#include "gclib.h"

class MotionController{

private:

    z_port xy_ctrl; // xy-axis station is controlled by a machine from Zaber
    GCon z_ctrl;    // z-axis controled by a machine from Garlil

    int status;

public:
    MotionController();
    ~MotionController();

    int get_status();
    /*
     * set speed if you want
     */
    int set_speed(int axis, float sp);

    // move station
    int mv_abs(int axis, float value); // move w.r.t home-position
    int mv_rel(int axis, float value); // move w.r.t current-position

    // get current position
    int get_position(int axis);

private:
    int connect();
    int disconnect();

    // convert mili-meter to number of turns/steps
    int convert_mm_to_turns(float value);

    int send_cmd_to_xy(const char* cmd);

private:
    inline void check_xy(int rc){
        if(rc != Z_SUCCESS) throw rc;
    }
    inline void check_z(GReturn rc){
        if (rc != G_NO_ERROR)
            throw rc;
    }
};
#endif
