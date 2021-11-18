#include "builtinfunction.h"

using namespace TooReadable;

const void TooReadable::BuiltinFunction::run() {
    toRun();
}

void TooReadable::BuiltinFuncs::HelloWorld() {
    std::cout << "Hello world" << std::endl;
}

void TooReadable::BuiltinFuncs::Greet() {
    std::cout << "Hello my friend" << std::endl;
}

void TooReadable::BuiltinFuncs::Advert() {
    std::cout << "TooReadable is the best!" << std::endl;
}
