#ifndef TOOREADABLE_PARSESTATES_PARSED_H
#define TOOREADABLE_PARSESTATES_PARSED_H

#include <vector>
#include "divided.h"

namespace TooReadable::ParseStates {

/**
 * \class Parsed parsed.h "parse-states/parsed.h"
 * \brief **Second stage of parsing:** fully parsed TOR program, ready to run.
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
        
        /**
         * \brief Execute the step
         */
        const void run();
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
         * \brief Execute the function
         */
        virtual const void run() = 0;
    };
    
    /**
     * \brief Function defined by user
     * 
     * Function defined by `How to` keyword by the user.
     */
    struct UserDefinedFunc : public Function {
        using Function::Function; // Inherit constructors
        
        /**
         * \brief The body of the function
         */
        std::vector<Step> body;
        const void run();
    };
    
    /**
     * \brief Find function by name.
     * 
     * If there isn't such a function, the \c FuncNotDefined exception is thrown.
     * 
     * \param[in] name Name of function to return.
     * \return User-defined or builtin TOR function named \c name.
     */
    Function* GetFuncNamed(std::string name);
    
    /**
     * \brief Main function - function ran when program starts
     */
    Function* mainFunc;
    
    /**
     * Functions of the program
     * TODO: Change to vector of UserDefinedFuncs
     */
    std::vector<UserDefinedFunc*> funcs;
    
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
