#ifndef _WaferProbe_helper_H_
#define _WaferProbe_helper_H_

#include <string>
#include <vector>

using namespace std;

// define some global code.
#define DEFAULT_ZABER_POS -3

namespace WaferProb{
    void tokenizeString(const string& str, char delim, vector<string>& tokens);
    string toUpper(const string& str);
    int axis_number(const string& axis_str);
}

#endif
