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
    BuiltinFunction(std::string name_, void (*toRun)()): toRun(toRun) {name = name_;};
    
    /**
     * \brief What should be ran when calling this function
     */
    void (*toRun)();
    
    /**
     * \brief Run the function
     */
    void run();
};


namespace BuiltinFuncs
{
    void HelloWorld();
    void Greet();
    void Advert();
    
    /**
     * \brief List of all TooReadable builtin functions
     */
    const std::vector<BuiltinFunction*> list = {
        new BuiltinFunction("Greet the world",        &HelloWorld), // Prints `Hello world` to the standart output.
        new BuiltinFunction("Greet the user",         &Greet),      // Prints `Hello my friend` to the standart output.
        new BuiltinFunction("Propagate TooReadable",  &Advert)      // Prints `TooReadable is the best!` to the standart output.
    };
    
}

}

#endif // TOOREADABLE_BUILTINFUNCTION_H
