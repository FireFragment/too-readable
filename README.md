TooReadable
===========

**The programming language readable by non-developers!**

> **Note:** This project is in early development.  
>  It means, that it does not run programs yet, but parses them inside.

Building & running
------------------

This project uses CMake as build system.  
Steps below were tested on Linux, but I think it should work also on Windows and MacOS.

### Building

First of all, ensure you have CMake installed.  
Then run theese commands:

```bash
git clone https://github.com/FireFragment/too-readable.git
cd too-readable
mkdir build
cd build
cmake ..
make
```

### Running

Then write your program, name the file `program.tor`, place it in the build directory and run:

```bash
./tooreadable program.tor
```

and it should... *do nothing*! - We are in early development yet.

### Testing

I use GTest framework for testing the code.  
To run tests, run:

```bash
./tests
```

in the `build` directory.
