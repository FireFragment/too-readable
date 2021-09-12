#include "ReadFile.h"

std::string ReadFile ( std::ifstream& in )
{
    std::ostringstream sstr;
    sstr << in.rdbuf();
    return sstr.str();
}
