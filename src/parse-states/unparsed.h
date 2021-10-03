#ifndef TOOREADABLE_PARSESTATES_UNPARSED_H
#define TOOREADABLE_PARSESTATES_UNPARSED_H

#include <string>
#include "../exception.h"

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

    /**
     * \param[in] skipTo String, to that we should skip.
     * \returns String, we just skipped.
     */
    std::string SkipTo(std::string skipTo);

    /**
     * \exception SkipToArgNotFoundException
     */
    class SkipToArgNotFoundException:public Exception {
    public:
        SkipToArgNotFoundException(std::string whatNotFound):whatNotFound(whatNotFound) {}
        std::string whatNotFound;
        const std::string what()
        {
            return whatNotFound + " not found in the code!";
        };
    };

private:
    /**
     * Current position for \c ContinueWith function.
     */
    size_t currentPosForContinueWith = 0;
};

}

#endif // TOOREADABLE_PARSESTATES_UNPARSED_H
