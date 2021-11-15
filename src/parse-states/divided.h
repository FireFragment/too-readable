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
     * \brief Function of TOR program.
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

        /**
         * \brief Name of the function.
         */
        std::string name;
        /**
         * \brief Steps of the function.
         */
        std::vector<std::string> steps;
    };
    
    /**
     * Default constructor
     */
    Divided() {}
    /**
     * \brief Divides \c original to this class.
     * \param[in] original The program to parse.
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
