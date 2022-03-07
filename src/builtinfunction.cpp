#include "builtinfunction.h"

using namespace TooReadable;

const TooReadable::Value TooReadable::BuiltinFunction::run(std::vector< TooReadable::Value > args)
{
    return toRun(args);
}

Value TooReadable::BuiltinFuncs::HelloWorld(std::vector<Value> args) {
    std::cout << "Hello world" << std::endl;
    return Value();
}

Value TooReadable::BuiltinFuncs::Greet(std::vector<Value> args) {
    std::cout << "Hello my friend" << std::endl;
    return Value();
}

Value TooReadable::BuiltinFuncs::Advert(std::vector<Value> args) {
    std::cout << "TooReadable is the best!" << std::endl;
    return Value();
}

Value TooReadable::BuiltinFuncs::Echo (std::vector<Value> args)
{
    std::cout << (std::string)args[0] << std::endl;
    return Value();
}

Value TooReadable::BuiltinFuncs::Test ( std::vector<Value> args )
{
    std::cout << "Testing function launched.\nFIRST ARGUMENT:" << (std::string)args[0]
        << "\nSECOND ARGUMENT: " << (std::string)args[1]
        << "\nTHIRD ARGUMENT: "  << (std::string)args[2];
    return Value();
}

TooReadable::Value TooReadable::BuiltinFuncs::GetInput(std::vector<Value> args)
{
    std::string str;
    std::getline(std::cin, str);
    return str;
}
