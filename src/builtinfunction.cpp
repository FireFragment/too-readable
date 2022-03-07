#include "builtinfunction.h"

using namespace TooReadable;

const TooReadable::Value TooReadable::BuiltinFunction::run(std::vector< TooReadable::Value > args)
{
    toRun(args);
    return Value();
}

void TooReadable::BuiltinFuncs::HelloWorld(std::vector<Value> args) {
    std::cout << "Hello world" << std::endl;
}

void TooReadable::BuiltinFuncs::Greet(std::vector<Value> args) {
    std::cout << "Hello my friend" << std::endl;
}

void TooReadable::BuiltinFuncs::Advert(std::vector<Value> args) {
    std::cout << "TooReadable is the best!" << std::endl;
}

void TooReadable::BuiltinFuncs::Echo (std::vector<Value> args)
{
    std::cout << (std::string)args[0] << std::endl;
}

void TooReadable::BuiltinFuncs::Test ( std::vector<Value> args )
{
    std::cout << "Testing function launched.\nFIRST ARGUMENT:" << (std::string)args[0]
        << "\nSECOND ARGUMENT: " << (std::string)args[1]
        << "\nTHIRD ARGUMENT: "  << (std::string)args[2];
}
