#ifndef TOOREADABLE_PARSESTATES_UNPARSED_H
#define TOOREADABLE_PARSESTATES_UNPARSED_H

#include <string>

namespace TooReadable::ParseStates
{

/** \class Unparsed unparsed.h "parse-states/unparsed.h"
 *  \brief This class represents non-parsed TOR program.
 * 
 *  Adds some useful functions
 */
class Unparsed
{
public:
    std::string TheCode;
    Unparsed(std::string TheCode):TheCode(TheCode) {};
    
    // TODO: Write better docs
    /**
     * \param[in] continueWith String, that the program should continue with
     */
    std::string ContinueWith(std::string continueWith);
    
private:
    /**
     * Current position for \c ContinueWith function.
     */
    size_t currentPosForContinueWith = 0;
};

}

#endif // TOOREADABLE_PARSESTATES_UNPARSED_H
