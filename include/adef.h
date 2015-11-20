#ifndef ADEF_H
#define ADEF_H

/**
\mainpage ADEF

The API documentation.

\sa https://github.com/ukjhsa/adef to download the source code.
*/

#include <memory>
#include "System.h"

/// namespace for ADEF
namespace adef {

/**
@brief Initialize the ADEF.
@param argc The argument count.
@param argv The argument vector.
@return The System of ADEF to use.
*/
std::shared_ptr<System> init_adef(int argc, char *argv[]);

}

#endif // ADEF_H
