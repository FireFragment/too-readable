#ifndef TOOREADABLE_BUILTINFUNCTION_H
#define TOOREADABLE_BUILTINFUNCTION_H

#include <iostream>
#include <vector>
#include "parse-states/parsed.h"

namespace TooReadable
{

/**
 * \brief Builtin TooReadable function
 */
class BuiltinFunction : public ParseStates::Parsed::Function
{
public:
    
    BuiltinFunction() {};
    BuiltinFunction(std::string name_, Value (*toRun)(std::vector<Value> args), std::vector<std::string> _outOfLineArgs = {})
        :toRun(toRun) {outOfLineArgs = _outOfLineArgs; name = name_;};
    
    /**
     * \brief What should be ran when calling this function
     */
    Value (*toRun)(std::vector<Value> args);
    
    /**
     * \brief Run the function
     */    
    const Value run(std::vector<Value> args) override;
};


namespace BuiltinFuncs
{
    Value Echo(std::vector<Value> args);
    Value GetInput(std::vector<Value> args);

    #define BUILTIN_FUNC_BODY [](std::vector<Value> args) -> Value

    /**
     * \brief List of all TooReadable builtin functions
     */
    const std::vector<BuiltinFunction*> list = {
        new BuiltinFunction("Say something to user",    &Echo,      {"The message to say"}),
        new BuiltinFunction("Let user write something", &GetInput),

        new BuiltinFunction("Join two texts", BUILTIN_FUNC_BODY {
            return (std::string)args[0] + (std::string)args[1];
        }, {"First text", "Second text"}),

        new BuiltinFunction("Add two numbers", BUILTIN_FUNC_BODY {
            return (int)args[0] + (int)args[1];
        }, {"First number", "Second number"}),

        new BuiltinFunction("Multilply two numbers", BUILTIN_FUNC_BODY {
            return (int)args[0] * (int)args[1];
        }, {"First number", "Second number"}),

        new BuiltinFunction("Substract a number from another number", BUILTIN_FUNC_BODY {
            return (int)args[0] + (int)args[1];
        }, {"Minuend", "Subtrahend"}),

        new BuiltinFunction("Divide a number", BUILTIN_FUNC_BODY {
            return (int)args[0] / (int)args[1];
        }, {"Dividend", "Divisor"}),

        new BuiltinFunction("True", BUILTIN_FUNC_BODY {
            return "Yes";
        }, {}),
        new BuiltinFunction("False", BUILTIN_FUNC_BODY {
            return "No";
        }, {}),

        new BuiltinFunction("Compare", BUILTIN_FUNC_BODY {
            return Value((std::string)args[0] == (std::string)args[1]);
        }, {"First", "Second"})
    };

}

}

#endif // TOOREADABLE_BUILTINFUNCTION_H
