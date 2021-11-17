#ifndef TOOREADABLE_PARSESTATES_PARSED_H
#define TOOREADABLE_PARSESTATES_PARSED_H

#include <vector>
#include "divided.h"

namespace TooReadable::ParseStates {

/**
 * \brief Fully parsed TOR program, ready to run.
 */
class Parsed
{
public:
    
    struct Function; // Forward declaration
    
    /**
     * \brief \c Function call
     */
    struct Step {
        Step(Function* toCall):toCall(toCall) {};
        Function* toCall;
    };
    
    /**
     * \brief Function of TOR program
     */
    struct Function {
        Function() {}; // Default constructor
        Function(std::string name):name(name) {};
        
        /**
         * \brief The name of the function
         */
        std::string name;
        
        /**
         * \brief The body of the function
         */
        std::vector<Step> body;
    };
    
    /**
     * \brief Main function - function ran when program starts
     */
    Function* mainFunc;
    
    /**
     * Functions of the program
     */
    std::vector<Function> funcs;
    
    /**
     * \brief Parses \c original.
     * \param[in] original Program to parse
     */
    Parsed(Divided original);
    
    /**
     * \exception FuncNotDefined Call of non-existing function.
     * 
     * TODO: Add more members to help user find the issue.
     */
    class FuncNotDefined : public Exception {
    public:
        FuncNotDefined() {};
        FuncNotDefined(std::string FuncName) : FuncName(FuncName) {};
        
        const std::string what() {
            return "You didn't say me, how to " + FuncName + ", so I can't do it!";
        };
        
        /**
         * \brief The missing function user tried to call.
         */
        std::string FuncName;
    };
};

}

#endif // TOOREADABLE_PARSESTATES_PARSED_H
