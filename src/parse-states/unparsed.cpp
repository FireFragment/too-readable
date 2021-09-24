#include "unparsed.h"



std::string TooReadable::ParseStates::Unparsed::ContinueWith(std::string continueWith) {
    
    
    // This string should be equal to continueWith.
    std::string importantPortion = TheCode.substr(currentPosForContinueWith, continueWith.length());

    std::string returnVal;
    if (importantPortion != continueWith)
        returnVal = importantPortion;

    // Update `currentPos` for next run
    currentPosForContinueWith += continueWith.length();

    return returnVal;
};
