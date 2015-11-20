#include <memory>
#include <cstddef>
#include <vector>
#include "DERand.h"
#include "Configuration.h"
#include "PrototypeManager.h"
#include "Individual.h"
#include "Population.h"

namespace adef {

void DERand::setup(const Configuration& config, const PrototypeManager& pm)
{
}

unsigned int DERand::number_of_indexes() const
{
    return 1;
}

std::shared_ptr<Individual> DERand::base_vector(
                            std::size_t target_index,
                            const std::vector<std::size_t>& random_indexes,
                            std::shared_ptr<const Population> population) const
{
    auto idx = random_indexes.front();
    return population->at(idx)->clone();
}

}
