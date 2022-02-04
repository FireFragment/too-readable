#include "parsed.h"
#include "../builtinfunction.h"

TooReadable::ParseStates::Parsed::Parsed(Divided original)
{    
    // Copy name of original's functions to `funcs`.
    // Steps will be parsed soon.
    for (Divided::Function dividedFunc : original.functions) { 
        UserDefinedFunc* parsedFunc = new UserDefinedFunc(dividedFunc.name);
        parsedFunc->outOfLineArgs = dividedFunc.outOfLineArgs;
        funcs.push_back(parsedFunc);
        
        if (original.mainFunc == dividedFunc.name)
            mainFunc = funcs.back();
    }
    
    // Parse steps
    // Iterate through `original.functions` and `funcs` at once.
    std::vector<UserDefinedFunc*>::iterator thisFunc = funcs.begin();
    for (Divided::Function func : original.functions) { // For each user-defined function in the program.
        std::vector<Step> steps; // Steps of `func`
        
        // Parse each step
        
        std::transform(
            func.steps.begin(),
            func.steps.end(),
            std::back_inserter(steps),
            [this](Divided::Step dividedStep) -> Step {
                return Step(dividedStep, this);
            }
        );
            
        // Write steps to the function
        (*thisFunc)->body          = steps;
        (*thisFunc)->outOfLineArgs = func.outOfLineArgs;
        thisFunc++;
    }
}

TooReadable::ParseStates::Parsed::Function* TooReadable::ParseStates::Parsed::GetFuncNamed(const std::string name) const {
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
    toCall->run(args);
}

const void TooReadable::ParseStates::Parsed::UserDefinedFunc::run(std::vector<Value> args) 
{
    for (Step step : body) {
        step.run();
    }
}

TooReadable::ParseStates::Parsed::Step::Step(const Divided::Step original, const Parsed* program)
{
    // ----- The function -----
    toCall = program->GetFuncNamed(original.funcName);
    
    args.reserve(toCall->outOfLineArgs.size());
    
    // ----- Out of line arguments -----
    for (auto dividedArg : original.outOfLineArgs) {
        // Get index of dividedArg
        unsigned short index = std::find(toCall->outOfLineArgs.begin(), toCall->outOfLineArgs.end(), dividedArg.name)- toCall->outOfLineArgs.begin();
        args.insert(args.begin() + index, Value::FromLiteral(dividedArg.value));
    }
}
