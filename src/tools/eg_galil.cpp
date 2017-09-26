#include <stdio.h>
#include <iostream>
#include <string>

#include "ControllerGalil.h"

using namespace std;
int main(int argc, char** argv){
    ControllerGalil* ctrl = new ControllerGalil("192.168.0.11");
    ctrl->connect();

    string input = "";
    while(true){
        printf("please enter commands, q for quit\n");
        getline(cin, input);
        if(input[0] == 'q') break;
        if(input[0] == '\n') continue;
        char cmd[256];
        int n = sprintf(cmd, "%s\n", input.c_str());
        // ctrl->write(cmd);
        ctrl->mv_abs(1, 10.);
    }

    delete ctrl;
    return 0;
}
