#include "value.h"
#include <algorithm>

const std::string TooReadable::Value::InvalidBoolConv::what() {
    return "You tried to convert " + badVal + " to YES/NO value, but I don't know, whether " + badVal + " is YES or NO.\nIt has to be one of: `yes`, `Yes`, `YES`, `no`, `No` or `NO`.";
}

TooReadable::Value::operator bool() const
{
    // When updating this function, don't forget to update also `InvalidBoolConv::what()` and documentation of `InvalidBoolConv`
    if (val == "YES" ||
        val == "Yes" ||
        val == "yes" )
        return true;

    if (val == "NO" ||
        val == "No" ||
        val == "no" )
        return false;

    throw InvalidBoolConv(val);
}

TooReadable::Value::Value(const bool _val)
{
    val = _val ? "YES" : "NO";
}

TooReadable::Value TooReadable::Value::FromLiteral(std::string literal)
{
    // String
    if (literal.front() == '`' &&
        literal.back()  == '`'
    ) {
        return literal.substr(1, literal.size() - 2);
    }
    
    // Number
    else if (IsNum(literal))
        return std::stoi(literal);
    else
        throw BadLiteral(literal);
}

bool TooReadable::Value::IsNum(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(), 
        s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}
