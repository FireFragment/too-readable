#include "expression.h"

#include <algorithm>

using namespace TooReadable;

TooReadable::Value TooReadable::Expression::evaluate(const std::vector<Value>* vars, const std::vector<Value>* returnVals)
{
    const Type tp = type();
    switch (tp) {
        case Literal:     return std::get<Value>(value);
        case Variable:    return       vars->at(std::get<short int>(value));
        case ReturnValue: return returnVals->at(std::get<short int>(value));
    }
}

TooReadable::Expression::Type TooReadable::Expression::type()
{
    if (std::holds_alternative<Value>(value))
        return Literal;
    else if (isReturn)
        return ReturnValue;
    else
        return Variable;
}

TooReadable::Expression TooReadable::Expression::Parse(std::string code, std::vector<std::string> vars)
{
    // Value to be returned
    Expression retVal;

    if (code.rfind("Value we've got in step ", 0) == 0) { // It's return value of another step
        retVal.value = std::stoi(code.substr(24)) - 1; // Substracting 1 from number of step, because C++ counts from 0, but TooReadable from 1 (`Step 1` is at index 0)
        retVal.isReturn = true;
        return retVal;
    }

    try {
        // Check, if it's value literal. If isn't, exception's thrown
        retVal.value = Value::FromLiteral(code);
    } catch (Value::BadLiteral) {
        // Check if variable named `code` exists
        // If so, assign it's ID to `retVal`
        auto varNameIt = std::find(vars.begin(), vars.end(), code);
        if (varNameIt == vars.end())
            throw InvalidExpression(code);
        retVal.value = varNameIt - vars.begin();

        retVal.isReturn = false;
    }
    return retVal;
}
