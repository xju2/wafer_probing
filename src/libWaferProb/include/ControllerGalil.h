#ifndef __WaferProb_ControllerGalil_H__
#define __WaferProb_ControllerGalil_H__


#ifndef I_7B02A40E_869B_4650_A5A8_859F0A6E3325
#define I_7B02A40E_869B_4650_A5A8_859F0A6E3325
#endif

#include "gclib.h"
#include "gclibo.h"

#define GALIL_EXAMPLE_OK G_NO_ERROR //return code for correct code execution
#define GALIL_EXAMPLE_ERROR -100 //return code for error in example code

#define DEFAULT_GALIL_POS -2

#include "ControllerBase.h"

#include <string>

using namespace std;
class ControllerGalil : public ControllerBase
{
private:
    GCon port; // port connected to Galil
    string dn; // device name

public:
    ControllerGalil(const char* device_name);
    ~ControllerGalil();

    int connect();
    int disconnect();

    int write(const string& cmd);

    int set_speed(int axis, float sp);

    int mv_abs(int axis, float value);
    int mv_rel(int axis, float value);

    int get_position();
    int get_speed();

    int set_home();
    int set_center();
private:
    inline bool check(GReturn rc){
        return (rc == G_NO_ERROR);
    }
    int convert_mm_to_turns(float value){
        return value*1112679/14.189;
    }
    float convert_turns_to_mm(float turns){
        float res = 14.189/1112679 * turns + 12.7315;
        res = (int)(res*100) / 100.;
        return res;
    }
    char axis_index_to_name(int axis){
        // ABC is for XYZ!
        // axis starts from 0 to 2;
        return 'A'+axis;
    }
    string generate_cmd(const char* cmd, int axis, int steps);
    void make_a_move(int axis);
    char buf[1024];

};

#endif
