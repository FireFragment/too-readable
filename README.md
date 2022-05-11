TooReadable
===========

[![forthebadge](https://forthebadge.com/images/badges/powered-by-electricity.svg)](https://forthebadge.com)
[![forthebadge](https://forthebadge.com/images/badges/works-on-my-machine.svg)](https://forthebadge.com)

**The programming language readable by non-developers!**

> **Note:** This project is in early development.  
>  It means, that it runs programs, but lacks some key features programming language should have and isn't turing complete yet.

Building & running
------------------

This project uses CMake as build system.  
Steps below were tested on Linux.

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

In the build directory, run:

```bash
./tooreadable ./test_code/testing_code.tor
```

It should print output of the sample program.  
Then try editing`testing_code.tor`yourself (eg. change order of commands, create your own functions, etc.) and run it agin!

### Testing

I use GTest framework for testing the code.  
To run tests, run:

```bash
./tests
```

in the `build` directory.
