#include "adef.h"

int main(int argc, char *argv[])
{
    auto system = adef::init_adef(argc, argv);
    system->run();
}
