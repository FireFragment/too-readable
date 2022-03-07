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

const TooReadable::Value TooReadable::ParseStates::Parsed::Step::run(const std::vector<Value>* argVals, const std::vector<Value>* returns)
{
    std::vector<Value> evaluatedArgs;
    for (auto argument : args)
        evaluatedArgs.push_back(argument.evaluate(argVals, returns));

    return toCall->run(evaluatedArgs);
}

const TooReadable::Value TooReadable::ParseStates::Parsed::UserDefinedFunc::run(std::vector< TooReadable::Value > args)
{
    /**
     Values returned from previously done steps.
     Index 0 should corresponds to return value of first step.
    */
    std::vector<Value> returnedVals;
    for (Step step : body) {
        returnedVals.push_back(step.run(&args, &returnedVals));
    }
    return Value();
}

TooReadable::ParseStates::Parsed::Step::Step(const Divided::Step original, const Parsed* program)
{
    // ----- The function to call -----
    toCall = program->GetFuncNamed(original.funcName);

    // ----- The parent function -----
    parentFunc = program->GetFuncNamed(original.parentFunc);

    
    // ----- Out of line arguments -----
    args.reserve(toCall->outOfLineArgs.size());
    
    // The index of following loop
    unsigned int i = 0;
    for (auto it = toCall->outOfLineArgs.begin(); it != toCall->outOfLineArgs.end(); it++) {
        // Copy values of arguments to corresponding indexes. 
        // Fining is needed, because in step, arguments may be listed in different order, than in the definition.
        args.insert(args.begin() + i, Expression::Parse(std::find_if(original.outOfLineArgs.begin(), original.outOfLineArgs.end(), [it](Divided::Step::OutOfLineArgument arg) -> bool {
            return arg.name == *it;
        })->value, parentFunc->outOfLineArgs));
        i++;
    }
}
