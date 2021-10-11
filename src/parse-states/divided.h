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
     * \brief Function divided to basic parts.
     */
    class Function {
    public:
        Function(
            const std::string name,
            std::vector<std::string> steps
            ):name(name), steps(steps) {};
        Function() {};
        
        bool operator== (Function rhs) const {
            return (rhs.name == name) && (rhs.steps == steps);
        };
        
        std::string name;
        std::vector<std::string> steps;
    };
    
    /**
     * \brief Functions of the program.
     */
    std::vector<Function> functions;
};

}

#pragma once
