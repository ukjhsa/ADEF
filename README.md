# ADEF

[![API Documentation](https://img.shields.io/badge/API doc-doxygen-blue.svg)](http://ukjhsa.github.io/adef)
[![Documentation](https://img.shields.io/badge/doc-Markdown-blue.svg)](doc/documentation.md)
[![Releases](https://img.shields.io/github/release/ukjhsa/adef.svg)](https://github.com/ukjhsa/adef/releases)
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
[![Issues](https://img.shields.io/github/issues/ukjhsa/adef.svg)](https://github.com/ukjhsa/adef/issues)

## Description
ADEF (A Software Framework for Adaptive Differential Evolution) is a
framework supports a variety of adaptive differential evolution algorithms.

[Differential Evolution](https://en.wikipedia.org/wiki/Differential_evolution) (DE) is one of [Evolutionary algorithm](https://en.wikipedia.org/wiki/Evolutionary_algorithm). DE uses the differences of solutions to create new solutions and keeps each new solution if it is better.

The DE algorithm has parameters F (scaling factor) and CR (crossover rate) and there are many researches on how to adjust. ADEF not only implements some existing mechanism of parameter control, it also presents the flexible architecture of it.

## Features
ADEF has the following features:
- DE and a variety of adaptive DE procedures
    - DE variant *x*/*y*/*z*:
        - *x*: *rand*
        - *y*: positive integer
        - *z*: *bin*
    - adaptive DE procedure, including **DEPD**, **NSDE**, **SaDE**, **SaNSDE**, **jDE**, **ISADE**, **SDE**.
- the mechanism of the parameter control to use.
- parameters and implementation classes changed dynamically by the configuration file rather than recompiling.
- the statistics of experimental result automatically.

## Requirements
- [CMake](https://cmake.org/) 3.1 or the newer.
- C++ compiler with C++14 supported.

Tested environments:
- Windows
    - [TDM-GCC](http://tdm-gcc.tdragon.net/) 32-bit 5.1.0
- Ubuntu
    - g++ 5.2.1
    - clang++ 3.5
- Mac OS X
    - clang++ 3.5

Note that the MSVC is **NOT** supported.

## Build
### Use the gui tool `cmake-gui` (recommended to Windows user)
1. open `cmake-gui` and select the path of "Where is the source code" to source code, suppose `X:/adef`.
1. specify the path of "Where to build the binaries" to build, suppose `X:/adef/build`.
1. press the button "Configure".
1. select the generator. If the default compilers fails to find, specify them.
    - "MinGW Makefiles" for Windows user. The compiler should be mingw32-g++.
    - "Unix Makefiles" for Unix user.
    - "CodeBlocks - MinGW Makefiles" if you want to use [Code::Bolcks](http://www.codeblocks.org/) with MinGW compiler.
1. if the configuration changed, press the button "Configure" again.
1. press button "Generate".
1. compile from the generator
    - "MinGW Makefiles"
        1. open the `cmd` and set up environment with MinGW. (use the "MinGW Command Prompt" if TDM-GCC installed.)
        1. change the current working directory to `X:/adef/build`.
        1. type `mingw32-make`.
    - "Unix Makefiles"
        1. open the terminal and change the current working directory to `X:/adef/build`.
        1. type `make`
    - "CodeBlocks - MinGW Makefiles"
        1. open `adef.cbp` by Code::Bolcks and build.
    - or other specified generator to build.

### Use the terminal

1. create the directory for building, suppose it is named `build`.
1. change the current working directory to it.
1. configure and generate generator from the root CMakeLists.txt.
1. compile it.

```sh
mkdir build
cd build
cmake ..
make
```

or specify the generator such as
- type `cmake -G "MinGW Makefiles" ..` to use Makefiles with MinGW compiler.
- type `cmake -G "CodeBlocks - MinGW Makefiles" ..` to use [Code::Bolcks](http://www.codeblocks.org/) with MinGW compiler.

then compile from the generator.

### Configuration of CMake
The build of ADEF has two choices:
- build the library of ADEF.
- build the executable file by linking the provided `main.cpp` and the library of ADEF.

There are some optional configuration using CMake:
- BUILD_SHARED_LIBS: build ADEF as the shared library. default is OFF (i.e., static)
- CMAKE_BUILD_TYPE: the build type. default is Release.
- GENERATE_EXECUTABLE: generate the executable file. default is ON. If it set to OFF, then it only build the library.

## Usage
If generate the executable file, then
- execute it and it use the default configuration file named `config.json` on the same path.
- specify the configuration file by adding arguments `<-file> <file_name>`.
    - `adef -file example/jDE.json` to use configuration from file `example/jDE.json`.

If build as the library, set the include path and library path then use it by

```cpp
#include "adef.h"
int main(int argc, char *argv[])
{
    auto system = adef::init_adef(argc, argv);
    system->run();
}
```

See also the [src/main.cpp](src/main.cpp).

## Documentation

[The documentation](doc/documentation.md)

[The API documentation](http://ukjhsa.github.io/adef/)

## License
ADEF is under the [MIT License](LICENSE)

## third-party library
ADEF uses the following libraryies:
- [JSON for Modern C++](https://github.com/nlohmann/json) and its license [here](thirdparty/json/LICENSE.MIT)
