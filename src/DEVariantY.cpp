#include <vector>
#include <memory>
#include <stdexcept>
#include "DEVariantY.h"
#include "Configuration.h"
#include "PrototypeManager.h"
#include "Individual.h"
#include "Population.h"

namespace adef {

void DEVariantY::setup(const Configuration& config, const PrototypeManager& pm)
{
    number_of_difference_vector_ =
                        config.get_uint_value("number_of_difference_vector");
}

unsigned int DEVariantY::number_of_indexes() const
{
    return 2 * number_of_difference_vector_;
}

std::vector<std::shared_ptr<Individual>> DEVariantY::difference_vector(
                        const std::vector<std::size_t>& random_indexes,
                        std::shared_ptr<const Population> population) const
{
    std::vector<std::shared_ptr<Individual>> difference;
    difference.reserve(number_of_difference_vector_);

    std::size_t indexes_size = random_indexes.size();
    if ((indexes_size % 2) != 0) {
        throw std::logic_error("The number of random indexes required by \
                               difference vector is not even.");
    }
    if ((indexes_size % number_of_difference_vector_) != 0) {
        throw std::logic_error("The number of random indexes required by \
                               difference vector is not to be divisible by \
                               the number of difference vector.");
    }

    for (std::size_t i = 0, j = 1; i < indexes_size && j < indexes_size; i+=2, j+=2) {
        difference.push_back(make_difference(population->at(random_indexes[i]),
                                             population->at(random_indexes[j])));
    }
    return difference;
}

std::shared_ptr<Individual> DEVariantY::make_difference(
                            std::shared_ptr<const Individual> terminal,
                            std::shared_ptr<const Individual> initial) const
{
    auto indi = terminal->empty_clone();
    *indi = *terminal - *initial;
    return indi;
}

}
