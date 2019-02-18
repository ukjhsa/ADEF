#include <memory>
#include <string>
#include <stdexcept>
#include "cm/cu/CurrentFitnessControlUpdate.h"
#include "cm/cp/BaseControlParameter.h"
#include "cm/cf/func/BaseFunction.h"
#include "Configuration.h"
#include "PrototypeManager.h"
#include "Repository.h"
#include "Population.h"
#include "Parameters.h"
#include "Individual.h"

namespace adef {

void CurrentFitnessControlUpdate::setup(const Configuration & config, const PrototypeManager & pm)
{
}

void CurrentFitnessControlUpdate::update(std::shared_ptr<Repository> repos, std::shared_ptr<BaseControlParameter> parameter, std::shared_ptr<BaseFunction> function) const
{
    auto index = repos->parameters()->take_out<std::size_t>("target_index");
    auto current_fitness = repos->population()->at(index)->fitness();
    auto succ = function->record({ current_fitness }, "current");
    if (!succ) {
        throw std::runtime_error(
            "No functions accept parameters \"current\" "
            "in the \"" + function->function_name() + "\"");
    }
}

}
