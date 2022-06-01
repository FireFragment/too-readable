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
        /** Steps of `func` */
        std::vector<Step> steps;
        
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

const TooReadable::Value TooReadable::ParseStates::Parsed::Step::run(const std::vector<Value>* argVals, const std::vector<Value>* returns, int* gotoStep)
{
    // Handle goto statements
    if (isGoto()) {
        *gotoStep = gotoDestination;
        return "";
    }
    *gotoStep = -1;

    // Handle normal steps
    std::vector<Value> evaluatedArgs;
    for (auto argument : args)
        evaluatedArgs.push_back(argument.evaluate(argVals, returns));

    // Do not execute the function if it has condition which isn't fullfilled
    if (isCondition()) {
        if (bool(toCall->run(evaluatedArgs)))
            return conditionalCommand->run(argVals, returns, gotoStep);
        else if (elseCommand != NULL) // It has else branch
            return elseCommand->run(argVals, returns, gotoStep);
        else
            return Value();
    }
    return toCall->run(evaluatedArgs);
}

const TooReadable::Value TooReadable::ParseStates::Parsed::UserDefinedFunc::run(std::vector< TooReadable::Value > args)
{
    /**
     Values returned from previously done steps.
     Index 0 should corresponds to return value of first step.
    */
    std::vector<Value> returnedVals(body.size());
    for (auto it = body.begin(); it != body.end(); /** We don't increment iterator here, because of goto statements */) {
        /** Number of step to go to */
        int gotoStep;
        returnedVals[it - body.begin()] = it->run(&args, &returnedVals, &gotoStep); // Run the command and save its return value
        if (gotoStep == -1)
            it++; // We don't increment iterator in for loop, we have to do it here
        else
            it = body.begin() + gotoStep;
    }
    return Value();
}

TooReadable::ParseStates::Parsed::Step::Step(const Divided::Step original, const Parsed* program)
{
    if (original.funcName.rfind("go to step ", 0) == 0) { // It's goto statement
        makeGoto(std::stoi(original.funcName.substr(11)) - 1);
        return;
    }
    // ----- The function to call -----
    toCall = program->GetFuncNamed(original.funcName);

    // ----- The parent function -----
    parentFunc = program->GetFuncNamed(original.parentFunc);

    // ----- Conditional function -----

    if (original.conditionalCommand != NULL) {
        conditionalCommand = new Parsed::Step(*original.conditionalCommand, program);
        if (original.elseCommand != NULL)
            elseCommand = new Parsed::Step(*original.elseCommand, program);
    }
    
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
