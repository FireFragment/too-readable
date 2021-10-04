#include "divided.h"

TooReadable::ParseStates::Divided::Divided(Unparsed original)
{
    // If it isn't a library, the "please" definition of the main function.
    if (original.ContinueWith("Please ", false) == "")
        mainFunc = original.SkipTo(".\n");
    original.ContinueWith("\n");
}
