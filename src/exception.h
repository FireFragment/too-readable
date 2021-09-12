#pragma once
#include <string>

/**
 * @todo write docs
 */

namespace TooReadable {

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
