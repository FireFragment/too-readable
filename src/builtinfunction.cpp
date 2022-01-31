#include "builtinfunction.h"

using namespace TooReadable;

const void TooReadable::BuiltinFunction::run(std::map<std::string, Value> args) {
    toRun(args);
}

void TooReadable::BuiltinFuncs::HelloWorld(std::map<std::string, Value> args) {
    std::cout << "Hello world" << std::endl;
}

void TooReadable::BuiltinFuncs::Greet(std::map<std::string, Value> args) {
    std::cout << "Hello my friend" << std::endl;
}

void TooReadable::BuiltinFuncs::Advert(std::map<std::string, Value> args) {
    std::cout << "TooReadable is the best!" << std::endl;
}

void TooReadable::BuiltinFuncs::Echo ( std::map<std::string, Value> args )
{
    std::cout << (std::string)args["The message to say"] << std::endl;
}
