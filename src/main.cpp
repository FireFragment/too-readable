#include <iostream>
#include <fstream>
#include <string>
#include "ReadFile.h"
#include "exception.h"
#include "parse-states/divided.h"
#include "parse-states/unparsed.h"

using namespace TooReadable;

int main ( int argc, char** argv )
{
    try {
        std::ifstream inputFile;

        // Load file if specified, else throw error.
        if ( argc < 2 ) {
            throw ( Exception("No input file specified!", Exception::bad_arguments) );
            return 1;
        }

        inputFile = std::ifstream ( argv[1] );
        ParseStates::Unparsed code = ReadFile ( inputFile ); 
        
    } catch ( Exception err ) {
        std::cout << "ERROR! " << err.what << std::endl;
        std::cout << "Error code: " << std::to_string ( err.GetCode() );
        return err.GetCode();
    }

    return 0;
}
