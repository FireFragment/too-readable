#include "unparsed.h"
#include <iostream>

TooReadable::ParseStates::Unparsed::Unparsed(std::string _TheCode) {
    TheCode = _TheCode;

    std::string sub = " > NOTE:";

    std::vector<size_t> positions; // holds all the positions that sub occurs within str

    size_t pos = TheCode.find(sub, 0);
    while(pos != std::string::npos)
    {
        TheCode.erase(pos, TheCode.find('\n', pos) - pos + 1);
        pos = TheCode.find(sub,pos+1);
    }
}


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
            // Return " " when `importantPortion` is "" (returning "" may cause program to thinking, that `continueWith` has been found)
            return importantPortion == "" ? " " : importantPortion; // FIXME: This is very dirty. Return type of this function should be `std::optional<std::string>>` instead
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
