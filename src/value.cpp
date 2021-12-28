#include "value.h"

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
