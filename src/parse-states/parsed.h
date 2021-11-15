#ifndef TOOREADABLE_PARSESTATES_PARSED_H
#define TOOREADABLE_PARSESTATES_PARSED_H

#include <vector>
#include "divided.h"

namespace TooReadable::ParseStates {

/**
 * \brief Fully parsed TOR program, ready to run.
 */
class Parsed
{
public:
    
    class Function; // Forward declaration
    
    /**
     * \brief \c Function call
     */
    class Step {
        Function* toCall;
    };
    
    /**
     * \brief Function of TOR program
     */
    class Function {
        std::string name;
        std::vector<Step> body;
    };
    
    /**
     * \brief Parses \c original.
     * \param[in] original Program to parse
     */
    Parsed(Divided original);
};

}

#endif // TOOREADABLE_PARSESTATES_PARSED_H
