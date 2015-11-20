#include <memory>
#include <stdexcept>
#include <string>
#include "DEEnvironmentalSelection.h"
#include "Configuration.h"
#include "PrototypeManager.h"
#include "Repository.h"
#include "Population.h"
#include "Individual.h"
#include "Parameters.h"
#include "cm/ControlMechanism.h"

namespace adef {

void DEEnvironmentalSelection::setup(const Configuration& config,
                                     const PrototypeManager& pm)
{
}

void DEEnvironmentalSelection::init(std::shared_ptr<Repository> repos)
{
}

void DEEnvironmentalSelection::select(std::shared_ptr<Repository> repos) const
{
    // Call select of parameter f and cr for all individuals
    auto f = std::dynamic_pointer_cast<ControlMechanism<double>>(
        repos->parameters()->take_out<std::shared_ptr<BaseControlMechanism>>("f"));
    auto cr = std::dynamic_pointer_cast<ControlMechanism<double>>(
        repos->parameters()->take_out<std::shared_ptr<BaseControlMechanism>>("cr"));

    auto parent = repos->population();
    auto children = repos->offspring();
    auto pop_size = parent->population_size();
    if (pop_size != children->population_size()) {
        throw std::runtime_error("The size of two Population are not equal");
    }
    for (decltype(pop_size) idx = 0; idx < pop_size; ++idx) {
        repos->parameters()->store("target_index", idx);
        f->select(repos);
        cr->select(repos);

        *parent->at(idx) = *select(parent->at(idx), children->at(idx));
    }
}

std::shared_ptr<Individual> DEEnvironmentalSelection::select(
                                    std::shared_ptr<const Individual> lhs,
                                    std::shared_ptr<const Individual> rhs) const
{
    if (lhs->fitness() < rhs->fitness()) {
        return lhs->clone();
    }
    else {
        return rhs->clone();
    }
}

}
