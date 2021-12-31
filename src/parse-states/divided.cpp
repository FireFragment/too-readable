#include "divided.h"

TooReadable::ParseStates::Divided::Divided(Unparsed original)
{
    // If it isn't a library, the "please" definition of the main function.
    try {
        original.ContinueWith("Please ") == ""; 
        mainFunc = original.SkipTo(".\n\n");
        mainFunc[0] = toupper(mainFunc[0]); 
    } catch (Unparsed::ArgNotFoundException err) {}
    
    // Functions
    while (true) {
        
        // ----- FUNCTION HEADER -----
        original.ContinueWith("How to ");
        
        Function func;
        func.name = original.SkipTo("\n");
        func.name[0] = toupper(func.name[0]); // Capitalize the first letter of the function name.
        
        // Underline of the header
        // TODO: Replace `7` with something more clear (it's length of "How to ")
        original.ContinueWith(std::string(func.name.length() + 7, '=') + "\n\n");
        
        // ----- OUT-OF-LINE ARGUMENTS -----
        
        // True, if there's `What do we need to know` section.
        const bool thereAreOutOfLineArgs = 
            original.ContinueWith("What do we need to know\n-----------------------\n\nTo " + func.name + ", we need to also know theese values:\n", false) == "";
            
        if (thereAreOutOfLineArgs) {
            // In `What do we need to know` section, there must be at least one out-of-line argument
            original.ContinueWith(" - ");
            func.outOfLineArgs.push_back(original.SkipTo("\n"));
            while (true) {
                // There isn't next argument
                if (original.ContinueWith(" - ", false) != "")
                    break;
                func.outOfLineArgs.push_back(original.SkipTo("\n"));
            }
            original.ContinueWith("\nInstructions\n------------\n\n");
        }
        
        // ----- FUNCTION BODY -----
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
        
        
        // Catch the exception thrown when we are at the end of the file
        try {
            original.ContinueWith("\n");
        } catch (Unparsed::ArgNotFoundException err) { break; }
    }
    original.ExpectEnd();
}
