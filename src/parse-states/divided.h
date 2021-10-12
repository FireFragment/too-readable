#pragma once

#include <string>
#include <vector>
#include "unparsed.h"

namespace TooReadable::ParseStates {

/** \class Divided divided.h "parse-states/divided.h"
 *  \brief **First stage of parsing:** divided to basic parts.
 */
class Divided
{
public:
    /**
     * Default constructor
     */
    Divided(Unparsed original);
    
    /**
     * \brief The main function of the program.
     * 
     * Empty string means, that program is a library hasn't main function;
     */
    std::string mainFunc;
    
    /**
     * \brief Functions of the program.
     */
    std::vector<Function> functions;
};

}

#pragma once
