# ADEF
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

## Compiling
### Use the gui tool `cmake-gui` and terminal (recommended to Windows user)
1. Open `cmake-gui` and select the path of "Where is the source code" to source code, suppose `X:/adef`.
1. specify the path of "Where to build the binaries" to build, suppose `X:/adef/build`.
1. press the button "Configure".
1. select the generator. If the default compilers fails to find, specify them.
    - "MinGW Makefiles" for Windows user. The compiler should be mingw32-g++.
1. if the configuration changed, press the button "Configure" again.
1. press button "Generate".
- or the specified generator to compile.
1. Open the terminal which has setting up environment with GCC.
    - use the "MinGW Command Prompt" if TDM-GCC installed for Windows user.
1. change the current working directory to `X:/adef/build`.
1. type `make` or `mingw32-make` (for MinGW user).

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
- type `cmake -G "MinGW Makefiles" ..` to use Makefiles with MinGW to build.
- type `cmake -G "CodeBlocks - MinGW Makefiles" ..` to use [Code::Bolcks](http://www.codeblocks.org/) with MinGW to build.

### Setting
The build of ADEF has two step:

1. build the library of ADEF.
1. generate the executable file by linking the provided `main.cpp` and the library of ADEF.

There are some optional configuration using CMake:
- BUILD_SHARED_LIBS: build ADEF as the shared library. the default is OFF (static.)
- CMAKE_BUILD_TYPE: the build type. the default is Release.
- GENERATE_EXECUTABLE: generate the executable file. the default is ON.

## Usage
- If generate the executable file, then
    - execute `adef`, it loads the configuration file `config.json` on the same path.
    - specify the configuration file by adding arguments `<-file> <file_name>`
        - `adef -file example/jDE.json` for the use of configuration from `example/jDE.json`
- If only build as the library, set the path to include and library, and use it by

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
