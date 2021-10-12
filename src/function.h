#ifndef TOOREADABLE_FUNCTION_H
#define TOOREADABLE_FUNCTION_H

#include <string>
#include <vector>

namespace TooReadable {

/**
* \brief Function of TOR program.
*/
class Function {
public:
    Function(
        const std::string name,
        std::vector<std::string> steps
    ):name(name), steps(steps) {};
    Function() {};

    bool operator== (Function rhs) const {
        return (rhs.name == name) && (rhs.steps == steps);
    };

    std::string name;
    std::vector<std::string> steps;
};

}

#endif // TOOREADABLE_FUNCTION_H
