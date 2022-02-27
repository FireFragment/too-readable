#include "expression.h"

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
