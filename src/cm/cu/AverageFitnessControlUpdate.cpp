#include <memory>
#include <stdexcept>
#include "cm/cu/AverageFitnessControlUpdate.h"
#include "cm/cp/BaseControlParameter.h"
#include "cm/cf/func/BaseFunction.h"
#include "Configuration.h"
#include "PrototypeManager.h"
#include "Repository.h"
#include "Population.h"
#include "Individual.h"

namespace adef {

void AverageFitnessControlUpdate::setup(const Configuration & config, const PrototypeManager & pm)
{
}

void AverageFitnessControlUpdate::update(std::shared_ptr<Repository> repos,
    std::shared_ptr<BaseControlParameter> parameter,
    std::shared_ptr<BaseFunction> function) const
{
    double average_fitness = find_average_fitness(repos->population());
    auto succ = function->record({ average_fitness }, "average");
    if (!succ) {
        throw std::runtime_error(
            "No functions accept parameters \"average\" "
            "in the \"" + function->function_name() + "\"");
    }
}

double AverageFitnessControlUpdate::find_average_fitness(std::shared_ptr<const Population> pop) const
{
    auto pop_size = pop->population_size();

    double average = 0;
    for (decltype(pop_size) idx = 0; idx < pop_size; ++idx) {
        average += pop->at(idx)->fitness();
    }
    if (pop_size != 0) {
        average /= pop_size;
    }
    return average;
}

}
