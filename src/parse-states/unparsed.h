#ifndef TOOREADABLE_PARSESTATES_UNPARSED_H
#define TOOREADABLE_PARSESTATES_UNPARSED_H

#include <string>
#include <algorithm>
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
    /**
     * @brief Create Unparsed from std::string and remove comments
     *
     * @param TheCode p_TheCode:...
     */
    Unparsed(std::string TheCode);

    // TODO: Write better docs
    /**
     * \param[in] continueWith String, that the program should continue with
     * \param[in] doThrow Whether the function should throw an exception when value of the \c continueWith arg wasn't found
     * 
     * \returns Empty string, if everything matched properly, else returns, what was found instead.
     */
    std::string ContinueWith(const std::string continueWith, const bool doThrow = true);

    /**
     * \param[in] skipTo String, to that we should skip.
     * \returns String, we just skipped.
     */
    std::string SkipTo(std::string skipTo);
    
    /**
     * \brief Expect the program to end.
     */
    void ExpectEnd();

    /**
     * \exception SkipToArgNotFoundException
     * 
     * TODO: Add an `insteadOf` member
     */
    class ArgNotFoundException:public Exception {
    public:
        ArgNotFoundException(
            const std::string whatNotFound,
            const unsigned int line)
            :whatNotFound(whatNotFound), line(line) {}
        std::string whatNotFound;
        unsigned int line;
        const std::string what()
        {
            return "'" + whatNotFound + "' not found in the code (line " + std::to_string(line) + ")!";
        };
    };
    
    /**
     * \exception ExpectedEndException
     * 
     * TODO: Add an `insteadOf` member
     */
    class ExpectedEndException:public Exception {
    public:
        ExpectedEndException(const unsigned int line):line(line) {}
        unsigned int line;
        const std::string what()
        {
            return "Expected the end of the code (line " + std::to_string(line) + ")!";
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
