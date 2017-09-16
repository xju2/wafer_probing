#ifndef __WaferProb_Handler_H_
#define __WaferProb_Handler_H_

/*
 * A wrapper of all controls.
 * define our own commands to control the station.
 * Underlying implementations are taken care by MotionController
 * example commands:
 * MA X 10  // move X-axis w.r.t home position 10 micro-meter
 * MR X 10  // move X-axis w.r.t current position 10 micro-meter
 * SP X 10  // set speed in x-axis direction by 10 micro-meter/s
 * SH // set current position as HOME
 * SC // set needles contact with chip
 * SS // set needles separate from chip
 * SDZ 10 // set distance in z-axis in order to separate needle and chip.
 */
#include "MotionController.h"
#include <string>
#include <vector>

using namespace std;

class Handler {
private:
    MotionController* ctrl;
    vector<string>* supported_actions;

public:
    Handler();
    ~Handler();
    void write(const string& cmd);
    void print_cmd();
};

#endif
