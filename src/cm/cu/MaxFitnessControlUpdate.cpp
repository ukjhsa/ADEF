#include <memory>
#include <string>
#include <stdexcept>
#include "cm/cu/MaxFitnessControlUpdate.h"
#include "cm/cp/BaseControlParameter.h"
#include "cm/cf/func/BaseFunction.h"
#include "Configuration.h"
#include "PrototypeManager.h"
#include "Repository.h"
#include "Population.h"
#include "Individual.h"

namespace adef {

void MaxFitnessControlUpdate::setup(const Configuration & config, const PrototypeManager & pm)
{
}

void MaxFitnessControlUpdate::update(std::shared_ptr<Repository> repos, std::shared_ptr<BaseControlParameter> parameter, std::shared_ptr<BaseFunction> function) const
{
    double max_fitness = find_max_fitness(repos->population());
    auto succ = function->record({ max_fitness }, "max");
    if (!succ) {
        throw std::runtime_error(
            "No functions accept parameters \"max\" "
            "in the \"" + function->function_name() + "\"");
    }
}

double MaxFitnessControlUpdate::find_max_fitness(std::shared_ptr<const Population> pop) const
{
    auto pop_size = pop->population_size();

    double max = pop->at(0)->fitness();
    for (decltype(pop_size) idx = 0; idx < pop_size; ++idx) {
        double current = pop->at(idx)->fitness();
        if (max < current) {
            max = current;
        }
    }
    return max;
}

}
