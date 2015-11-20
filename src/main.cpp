#include <ctime>
#include <cstdlib>
#include "adef.h"

int main(int argc, char *argv[])
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    auto system = adef::init_adef(argc, argv);
    system->run();
}
