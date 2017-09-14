#include <stdio.h>
#include <iostream>
#include <string>

#include "Handler.h"

using namespace std;
int main(int argc, char** argv){
    // create a real controller
    Handler* handle = new Handler();
    cout << "controller is initialized" << endl;
    handle->print_cmd();
    string input = "";
    while(true){
        cout << "Please enter commands, Q for quit" << endl;
        getline(cin, input);
        // cout <<"You entered: " << input << endl;
        if(input[0] == 'Q' || input[0] == 'q') break;
        if(input[0] == '\n') continue;
        handle->write(input);
    }
    delete handle;

    cout << "good bye" << endl;
}
