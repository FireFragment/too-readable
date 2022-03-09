#include "builtinfunction.h"

using namespace TooReadable;

const TooReadable::Value TooReadable::BuiltinFunction::run(std::vector< TooReadable::Value > args)
{
    return toRun(args);
}

Value TooReadable::BuiltinFuncs::Echo (std::vector<Value> args)
{
    std::cout << (std::string)args[0] << std::endl;
    return Value();
}

TooReadable::Value TooReadable::BuiltinFuncs::GetInput(std::vector<Value> args)
{
    std::string str;
    std::getline(std::cin, str);
    return str;
}
