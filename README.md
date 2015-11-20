# ADEF
A Software Framework for Adaptive Differential Evolution

ADEF (A Software Framework for Adaptive Differential %Evolution) is a
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
Briefly, follow the step

```sh
mkdir build
cd build
cmake ..
make
```

or use the `cmake-gui` to set the compiler and configures.

## License
ADEF is under the [MIT License](LICENSE)

## third-party
ADEF uses the following libraryies:
- [JSON for Modern C++](https://github.com/nlohmann/json). its license found [here](thirdparty/json/LICENSE.MIT)
