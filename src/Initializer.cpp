#include <memory>
#include <functional>
#include <random>
#include "Initializer.h"
#include "Configuration.h"
#include "PrototypeManager.h"
#include "Repository.h"
#include "Random.h"
#include "Problem.h"
#include "Population.h"
#include "Individual.h"

namespace adef {

void Initializer::setup(const Configuration& config, const PrototypeManager& pm)
{
}

void Initializer::init(std::shared_ptr<Repository> repos)
{
    random_ = repos->random();
}

void Initializer::initialize(std::shared_ptr<Repository> repos) const
{
    auto func = std::bind(&Initializer::initialization_function,
            std::ref(*this), repos->problem(), std::placeholders::_1);
    repos->population()->apply_to_each_individual(func);
}

void Initializer::initialization_function(
                                  std::shared_ptr<const Problem> problem,
                                  std::shared_ptr<Individual> individual) const
{
    std::mt19937 gen(random_->random());
    for (unsigned int idx = 0; idx < problem->dimension_of_decision_space(); ++idx) {
        std::uniform_real_distribution<> uniform(
                                 problem->lower_bound_of_decision_space(idx),
                                 problem->upper_bound_of_decision_space(idx));
        individual->variables(idx) = uniform(gen);
    }
}

}
