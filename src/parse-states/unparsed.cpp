#include "unparsed.h"

std::string TooReadable::ParseStates::Unparsed::ContinueWith(std::string continueWith) {
    // This string should be equal to continueWith.
    std::string importantPortion = TheCode.substr(currentPosForContinueWith, continueWith.length());

    std::string returnVal;
    if (importantPortion != continueWith)
        returnVal = importantPortion;
    else
        // Update `currentPos` for next run
        currentPosForContinueWith += continueWith.length();

    return returnVal;
};

std::string TooReadable::ParseStates::Unparsed::SkipTo(std::string skipTo) {
    
    size_t occurencePos = TheCode.find(skipTo, currentPosForContinueWith);
    if (occurencePos == std::string::npos) // `skipTo` not found in `TheCode`
        throw SkipToArgNotFoundException(skipTo);
    
    // Compute return value.
    std::string out = TheCode.substr(currentPosForContinueWith, occurencePos - currentPosForContinueWith);
    
    // Update `currentPos` for next run
    currentPosForContinueWith = occurencePos + skipTo.length();
    
    return out;
}
