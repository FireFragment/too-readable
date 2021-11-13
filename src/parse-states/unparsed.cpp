#include "unparsed.h"

std::string TooReadable::ParseStates::Unparsed::ContinueWith(const std::string continueWith, const bool doThrow) {
    // This string should be equal to continueWith.
    std::string importantPortion = TheCode.substr(currentPosForContinueWith, continueWith.length());
    std::string returnVal;
    
    if (importantPortion != continueWith) // `TheCode` does not continue with `continueWith`.
        if (doThrow) {
            std::count(TheCode.begin(), TheCode.begin() + currentPosForContinueWith, '\n');
            throw ArgNotFoundException(
                continueWith,
                std::count(TheCode.begin(), TheCode.begin() + currentPosForContinueWith, '\n') + 1 // Get the line number
            );
        }
        else
            returnVal = importantPortion;
    else
        // Update `currentPos` for next run
        currentPosForContinueWith += continueWith.length();

    return returnVal;
};

std::string TooReadable::ParseStates::Unparsed::SkipTo(std::string skipTo) {
    
    size_t occurencePos = TheCode.find(skipTo, currentPosForContinueWith);
    if (occurencePos == std::string::npos) // `skipTo` not found in `TheCode`
        throw ArgNotFoundException(
            skipTo,
            std::count(TheCode.begin(), TheCode.begin() + currentPosForContinueWith, '\n') + 1 // Get the line number
        );
    
    // Compute return value.
    std::string out = TheCode.substr(currentPosForContinueWith, occurencePos - currentPosForContinueWith);
    
    // Update `currentPos` for next run
    currentPosForContinueWith = occurencePos + skipTo.length();
    
    return out;
}

void TooReadable::ParseStates::Unparsed::ExpectEnd() {
    if (currentPosForContinueWith != TheCode.length())
        throw ExpectedEndException(
            std::count(TheCode.begin(), TheCode.begin() + currentPosForContinueWith, '\n') + 1 // Get the line number TODO: Make standalone function
        );
}
