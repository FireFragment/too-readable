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
    Value HelloWorld(std::vector<Value> args);
    Value Greet(std::vector<Value> args);
    Value Advert(std::vector<Value> args);
    Value Echo(std::vector<Value> args);
    Value Test(std::vector<Value> args);
    Value GetInput(std::vector<Value> args);

    /**
     * \brief List of all TooReadable builtin functions
     */
    const std::vector<BuiltinFunction*> list = {
        new BuiltinFunction("Greet the world",          &HelloWorld), // Prints `Hello world` to the standart output.
        new BuiltinFunction("Greet the user",           &Greet),      // Prints `Hello my friend` to the standart output.
        new BuiltinFunction("Propagate TooReadable",    &Advert),      // Prints `TooReadable is the best!` to the standart output.
        new BuiltinFunction("Say something to user",    &Echo,      {"The message to say"}),
        new BuiltinFunction("My testing function",      &Test,      {"First testing argument", "Second testing argument", "Third testing argument"}),
        new BuiltinFunction("Let user write something", &GetInput)
    };
    
}

}

#endif // TOOREADABLE_BUILTINFUNCTION_H
