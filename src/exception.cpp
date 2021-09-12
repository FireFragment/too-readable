#include "exception.h"

using namespace TooReadable;

unsigned short Exception::GetCode()
{
    return type + 1;
}
