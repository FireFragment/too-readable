#include "divided.h"

TooReadable::ParseStates::Divided::Divided(Unparsed original)
{
    // If it isn't a library, the "please" definition of the main function.
    try {
        original.ContinueWith("Please ") == ""; 
        mainFunc = original.SkipTo(".\n\n");
    } catch (Unparsed::ArgNotFoundException err) {}
    
    // Functions
    try {
        while (true) {
            
            // Function header
            original.ContinueWith("How to ");
            Function func;
            func.name = original.SkipTo("\n");
            
            // TODO: Replace `7` with something more clear (it's length of "How to ")
            original.ContinueWith(std::string(func.name.length() + 7, '=') + "\n\n");
            
            // Function steps
            int i = 1;
            
            // Catch thrown exception, when last step of the function reached.
            try {
                while (true) {
                    original.ContinueWith(" " + std::to_string(i) + ". "); // May throw exception
                    func.steps.push_back(original.SkipTo(".\n"));
                    
                    i++;
                }
            } catch (Unparsed::ArgNotFoundException err) {}
            
            functions.push_back(func);
            
            
            original.ContinueWith("\n");
        }
    } catch (Unparsed::ArgNotFoundException err) {}
    
}
