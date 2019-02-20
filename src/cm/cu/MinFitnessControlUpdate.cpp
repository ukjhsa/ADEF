#include <memory>
#include <string>
#include <stdexcept>
#include "cm/cu/MinFitnessControlUpdate.h"
#include "cm/cp/BaseControlParameter.h"
#include "cm/cf/func/BaseFunction.h"
#include "Configuration.h"
#include "PrototypeManager.h"
#include "Repository.h"
#include "Population.h"
#include "Individual.h"

namespace adef {

void MinFitnessControlUpdate::setup(const Configuration & config, const PrototypeManager & pm)
{
}

void MinFitnessControlUpdate::update(std::shared_ptr<Repository> repos, std::shared_ptr<BaseControlParameter> parameter, std::shared_ptr<BaseFunction> function) const
{
    double min_fitness = find_min_fitness(repos->population());
    auto succ = function->record({ min_fitness }, "min");
    if (!succ) {
        throw std::runtime_error(
            "No functions accept parameters \"min\" "
            "in the \"" + function->function_name() + "\"");
    }
}

double MinFitnessControlUpdate::find_min_fitness(std::shared_ptr<const Population> pop) const
{
    auto pop_size = pop->population_size();

    double min = pop->at(0)->fitness();
    for (decltype(pop_size) idx = 0; idx < pop_size; ++idx) {
        auto current = pop->at(idx)->fitness();
        if (min > current) {
            min = current;
        }
    }
    return min;
}

}
