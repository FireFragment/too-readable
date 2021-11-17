#include "parsed.h"

TooReadable::ParseStates::Parsed::Parsed(Divided original)
{    
    // Copy name of original's functions to `funcs`.
    // Steps will be parsed soon.
    for (Divided::Function func : original.functions) { 
        funcs.push_back(Function(func.name));
        
        if (original.mainFunc == func.name)
            mainFunc = &(funcs.back());
    }
    
    // Parse steps
    // Iterate through `original.functions` and `funcs` at once.
    std::vector<Function>::iterator thisFunc = funcs.begin();
    for (Divided::Function func : original.functions) {
        std::vector<Step> steps; // Steps of `func`
        
        // Parse each step
        for (std::string stepStr : func.steps) {
            
            Function* stepFunc = 0x000000;
            
            // Find function named `step` and save it to `stepFunc`
            for (Function& i : funcs)
                if (i.name == stepStr) {
                    stepFunc = &i;
                    break;
                }
            
            if (stepFunc == 0x000000) { // No function named `step` found
                throw FuncNotDefined(stepStr);
            }
            
            steps.push_back(Step(stepFunc));
        }
        
        thisFunc->body = steps;
        thisFunc++;
    }
}

void TooReadable::ParseStates::Parsed::Step::run() 
{
    toCall->run();
}

void TooReadable::ParseStates::Parsed::Function::run() 
{
    for (Step step : body) {
        step.run();
    }
}
