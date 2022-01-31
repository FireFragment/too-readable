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
    BuiltinFunction(std::string name_, void (*toRun)(std::map<std::string, Value> args)): toRun(toRun) {name = name_;};
    
    /**
     * \brief What should be ran when calling this function
     */
    void (*toRun)(std::map<std::string, Value> args);
    
    /**
     * \brief Run the function
     */
    const void run(std::map<std::string, Value> args);
};


namespace BuiltinFuncs
{
    void HelloWorld(std::map<std::string, Value> args);
    void Greet(std::map<std::string, Value> args);
    void Advert(std::map<std::string, Value> args);
    void Echo(std::map<std::string, Value> args);
    
    /**
     * \brief List of all TooReadable builtin functions
     */
    const std::vector<BuiltinFunction*> list = {
        new BuiltinFunction("Greet the world",        &HelloWorld), // Prints `Hello world` to the standart output.
        new BuiltinFunction("Greet the user",         &Greet),      // Prints `Hello my friend` to the standart output.
        new BuiltinFunction("Propagate TooReadable",  &Advert),      // Prints `TooReadable is the best!` to the standart output.
        new BuiltinFunction("Say something to user",  &Echo)
    };
    
}

}

#endif // TOOREADABLE_BUILTINFUNCTION_H
