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
            throw ( NoInputFileException() );
            return 1;
        }

        inputFile = std::ifstream ( argv[1] );
        ParseStates::Unparsed code = ReadFile ( inputFile );
        ParseStates::Divided dividedCode = code;
        
    } catch ( Exception& err ) {
        std::cout << "ERROR! " << err.what() << std::endl;
        return 1;
    }

    return 0;
}
