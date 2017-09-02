#include "Helper.h"
#include <sstream>

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

}
