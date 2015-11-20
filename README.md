# ADEF
ADEF (A Software Framework for Adaptive Differential Evolution) is a
framework supports a variety of adaptive differential evolution algorithms.

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
1. Open cmake-gui and select the path to source code, suppose `X:/adef`.
1. specify the path to build, suppose `X:/adef/build`.
1. press the button "Configure".
1. specify the generator to "MinGW Makefiles". If the default compilers fails to find g++ (or mingw32-g++), specify them.
1. if the configuration changed, press the button "Configure" again.
1. press button "Generate".
1. Open the cmd and setting up environment with GCC. (if TDM-GCC used, click the "MinGW Command Prompt".)
1. change the current working directory to `X:/adef/build`.
1. `mingw32-make`

### Unix-like

```sh
mkdir build
cd build
cmake ..
make
```

### Full Guide
1. [CMake configuration](#CMake-configuration). Here the use of the out-of-source build.
2. [Compile](#Compile)

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
2. change the directory to it.
3. configure and generate generator from the root CMakeLists.txt.

##### cmake-gui
1. select the path to "Where is the source code"
2. specify the path "Where to build the binaries" to the directory `build` on the path to source code.
3. press the button "Configure" and specify the generator and compilers.
4. if the configuration changed, press the button "Configure" again.
5. press the button "Generate"

#### Compile
use `make` or the specified generator to compile.

## Setting
There are some optional configuration:
- BUILD_SHARED_LIBS
- CMAKE_BUILD_TYPE
- GENERATE_EXECUTABLE

## Documentation

[The documentation](doc/documentation.md)
[The API documentation](http://ukjhsa.github.io/adef/)

## License
ADEF is under the [MIT License](LICENSE)

## third-party library
ADEF uses the following libraryies:
- [JSON for Modern C++](https://github.com/nlohmann/json) and its license [here](thirdparty/json/LICENSE.MIT)
