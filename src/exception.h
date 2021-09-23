#pragma once
#include <string>

namespace TooReadable {

/** \class Exception exception.h "exception.h"
 *  Exception class, that is used in the interpreter.
 */
    
class Exception
{
public:

    enum ExceptionType {
        bad_arguments
    };
    /**
    * Default constructor
    */
    Exception(std::string what, ExceptionType type):type(type), what(what) {}

    ExceptionType type;
    std::string what;
    unsigned short GetCode();
};

}
