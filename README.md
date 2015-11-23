# ADEF
ADEF (A Software Framework for Adaptive Differential Evolution) is a
framework supports a variety of adaptive differential evolution algorithms.

[Differential Evolution](https://en.wikipedia.org/wiki/Differential_evolution) (DE) is one of [Evolutionary algorithm](https://en.wikipedia.org/wiki/Evolutionary_algorithm). DE uses the differences of solutions to create new solutions and keeps each new solution if it is better.

The DE algorithm has parameters F (scaling factor) and CR (crossover rate) and there are many researches on how to adjust. ADEF not only implements some existing mechanism of parameter control, it also presents the flexible architecture of it.

## Features
ADEF has the following features:
- supports many adaptive DE procedure, including **DEPD**, **NSDE**, **SaDE**, **SaNSDE**, **jDE**, **ISADE**, **SDE**.
- changes parameters and implementation classes dynamically through configuration file rather than recompiling.
- provides the mechanism of the parameter control to use flexibly.
- outputs the statistics of experimental result automatically.

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
### Windows
1. Open `cmake-gui` and select the path to source code, suppose `X:/adef`.
1. specify the path to build, suppose `X:/adef/build`.
1. press the button "Configure".
1. specify the generator to "MinGW Makefiles". If the default compilers fails to find g++ (or mingw32-g++), specify them.
1. if the configuration changed, press the button "Configure" again.
1. press button "Generate".
1. Open the `cmd` and setting up environment with GCC. (if TDM-GCC used, click the "MinGW Command Prompt".)
1. change the current working directory to `X:/adef/build`.
1. type `mingw32-make`

### Unix-like

```sh
mkdir build
cd build
cmake ..
make
```

### Full Guide
1. [CMake configuration](#cmake-configuration). Here the use of the out-of-source build.
2. [Compile](#compile)

#### CMake configuration
There are two option to use CMake
- use the [command-line tools](#command-line).
- use the gui tool [cmake-gui](#cmake-gui).

##### command-line

```sh
mkdir build
cd build
cmake ..
```

Explanation:

1. create the directory for building, suppose it is named `build`.
1. change the path to it.
1. configure and generate generator from the root CMakeLists.txt.

or specify the generator like
- type `cmake -G "MinGW Makefiles" ..` to use Makefiles with MinGW to build
- type `cmake -G "CodeBlocks - MinGW Makefiles" ..` to use [Code::Bolcks](http://www.codeblocks.org/) with MinGW to build

##### cmake-gui
1. select the path to "Where is the source code"
1. specify the path "Where to build the binaries" to the directory `build` on the same path of source code.
1. press the button "Configure" and specify the generator and compilers.
1. if the configuration changed, press the button "Configure" again.
1. press the button "Generate"

#### Compile
use `make` or `mingw32-make` (in MinGW) or the specified generator to compile.

### Setting
The build of adef has two step:

1. build the library of adef.
1. generate the executable file by linking the provided `main.cpp` and the library of adef.

There are some optional configuration using CMake:
- BUILD_SHARED_LIBS: build adef as the shared library. the default is OFF (static.)
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
