#pragma once
#include <string>

namespace TooReadable
{

/** \class Exception exception.h "exception.h"
 *  Exception class, that is used in the interpreter.
 */

class Exception
{
public:

    /**
    * Default constructor
    */
    Exception() {}

    virtual const std::string what()
    {
        return "";
    };
};

/**
 * \exception NoInputFileException The input file is missing.
 */
class NoInputFileException: public Exception
{
public:
    const std::string what()
    {
        return "No input file specified!";
    };    
};

}
