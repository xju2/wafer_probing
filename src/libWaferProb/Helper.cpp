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

}
