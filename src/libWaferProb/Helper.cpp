#include "Helper.h"
#include <sstream>
#include <locale>

namespace WaferProb{

void tokenizeString(const string& str, char delim, vector<string>& tokens)
{
    tokens.clear();
    istringstream iss(str);
    string token;
    while ( getline(iss, token, delim) ){
        // boost::algorithm::trim(token);
        tokens.push_back(token);
    }
}

string toUpper(const string& str)
{
    std::locale loc;
    string new_str(str);
    for(string::size_type i = 0; i < str.length(); ++i){
        new_str[i] = std::toupper(str[i], loc); 
    }
    return new_str;
}

int axis_number(const string& axis_str)
{
    // need to do better than this!
    int axis = -1;
    if(axis_str == "X" or axis_str == "x") {
        axis = 0;
    }
    if(axis_str == "Y" or axis_str == "y") {
        axis = 1;
    }
    if(axis_str == "Z" or axis_str == "z") {
        axis = 2;
    }
    if (axis < 0) {
        printf("Axis is wrong. Use X instead.");
        axis = 0;
    }
    return axis;
}

}
