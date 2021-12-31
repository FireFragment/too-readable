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
     * \brief \c Function call
     */
    class Step {
    public:
        Step(std::string funcName) : funcName(funcName) {};
        
        bool operator== (Step rhs) const {
            return (rhs.funcName == funcName) && (rhs.outOfLineArgs == outOfLineArgs);
        };
        /**
         * @brief Out-of-line argument assignment when calling function
         */
        class OutOfLineArgument {
        public:
            bool operator== (OutOfLineArgument rhs) const {
                return (rhs.name == name) && (rhs.value == value);
            };
            /**
             * @brief The name of the argument
             */
            std::string name;
            /**
             * @brief The assigned value
             */
            std::string value;
        };
        
        /**
         * @brief The name of the called function
         */
        std::string funcName;
        /**
         * @brief Out-of-line arguments passed to the function
         */
        std::vector<OutOfLineArgument> outOfLineArgs;
    };
    
    /**
     * \brief Function of TOR program.
     */
    class Function {
    public:
        
        Function(
            const std::string name,
            std::vector<Step> steps
        ):name(name), steps(steps) {};
        Function() {};

        bool operator== (Function rhs) const {
            return (rhs.name == name) && (rhs.steps == steps);
        };
        
        /**
         * @brief Out-of-line arguments of the function
         * 
         * Out-of-line arguments are assigned in function call this way:
         * ~~~~{.tor}
         * 1. Do something
         *     - Inline argument 1: "Value of the argument"
         *     - Inline argument 2: "Value of the second argument"
         * ~~~~
         * 
         * Out-of-line arguments are defined in function definition this way:
         * ~~~~{.tor}
         * How to do something
         * ===================
         * 
         * What do we need to know
         * -----------------------
         * 
         * To do something, we need to also know theese values:
         * 
         *  - Inline argument 1
         *  - Inline argument 2
         * 
         * Instructions
         * ------------
         * 
         *  1. Here is the function body
         *  2. Second step
         * ~~~~
         */
        std::vector<std::string> outOfLineArgs;

        /**
         * \brief Name of the function.
         */
        std::string name;
        /**
         * \brief Steps of the function.
         */
        std::vector<Step> steps;
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
