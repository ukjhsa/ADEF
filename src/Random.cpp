#include <cstdlib>
#include "Random.h"
#include "Repository.h"
#include "Configuration.h"
#include "PrototypeManager.h"

namespace adef {

Random::Random() : seed_(0)
{
}

Random::Random(const Random& rhs) : seed_(rhs.seed_), generator_(rhs.seed_)
{
}

void Random::setup(const Configuration& config, const PrototypeManager& pm)
{
    seed_ = config.get_uint_value("seed");

    std::srand(static_cast<unsigned int>(seed_));
    generator_.seed(seed_);
}

int Random::random() const
{
    return std::rand();
}

}
