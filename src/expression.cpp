#include "expression.h"

#include <algorithm>

using namespace TooReadable;

TooReadable::Value TooReadable::Expression::evaluate(const std::vector<Value>* vars)
{
    if (type() == Literal) return std::get<Value>(value);      // The expression holds literal
    else return vars->at(std::get<unsigned short int>(value)); // The expression holds variable
}

TooReadable::Expression::Type TooReadable::Expression::type()
{
    if (std::holds_alternative<Value>(value))
        return Literal;
    else
        return Variable;
}

TooReadable::Expression TooReadable::Expression::Parse(std::string code, std::vector<std::string> vars)
{
    // Value to be returned
    Expression retVal;
    try {
        // Check, if it's valie literal. If isn't, exception's thrown
        retVal.value = Value::FromLiteral(code);
    } catch (Value::BadLiteral) {
        // Check if variable named `code` exists
        // If so, assign it's ID to `retVal`
        auto varNameIt = std::find(vars.begin(), vars.end(), code);
        if (varNameIt == vars.end())
            throw InvalidExpression(code);
        retVal.value = varNameIt - vars.begin();
    }
    return retVal;
}
