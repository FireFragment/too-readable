#include "parsed.h"
#include "../builtinfunction.h"

TooReadable::ParseStates::Parsed::Parsed(Divided original)
{    
    // Copy name of original's functions to `funcs`.
    // Steps will be parsed soon.
    for (Divided::Function func : original.functions) { 
        funcs.push_back(new UserDefinedFunc(func.name));
        
        if (original.mainFunc == func.name)
            mainFunc = funcs.back();
    }
    
    // Parse steps
    // Iterate through `original.functions` and `funcs` at once.
    std::vector<UserDefinedFunc*>::iterator thisFunc = funcs.begin();
    for (Divided::Function func : original.functions) { // For each user-defined function in the program.
        std::vector<Step> steps; // Steps of `func`
        
        // Parse each step
        for (std::string stepStr : func.steps) 
            steps.push_back(Step(GetFuncNamed(stepStr))); // Add pointer to the function named `stepStr` to `funcs`.
            
        // Write steps to the function
        (*thisFunc)->body          = steps;
        (*thisFunc)->outOfLineArgs = func.outOfLineArgs;
        thisFunc++;
    }
}

TooReadable::ParseStates::Parsed::Function* TooReadable::ParseStates::Parsed::GetFuncNamed(const std::string name) {
    // Search through user-defined functions.
    for (Function* i : funcs)
        if (i->name == name) 
            return i;
        
    // Search through builtin functions.
    for (Function* i : BuiltinFuncs::list) {
        if (i->name == name) 
            return i;
    }
    
    // Nothing found.
    throw FuncNotDefined(name);
}

const void TooReadable::ParseStates::Parsed::Step::run() 
{
    toCall->run();
}

const void TooReadable::ParseStates::Parsed::UserDefinedFunc::run() 
{
    for (Step step : body) {
        step.run();
    }
}
