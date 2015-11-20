#include <memory>
#include "Evaluator.h"
#include "Configuration.h"
#include "PrototypeManager.h"
#include "Repository.h"
#include "Problem.h"
#include "Population.h"
#include "Statistics.h"

namespace adef {

void Evaluator::setup(const Configuration& config, const PrototypeManager& pm)
{
}

void Evaluator::init(std::shared_ptr<Repository> repos)
{
}

void Evaluator::evaluate(std::shared_ptr<Population> pop,
                         std::shared_ptr<const Problem> problem,
                         std::shared_ptr<Statistics> statistics) const
{
    auto size = pop->population_size();
    for (decltype(size) idx = 0; idx < size; ++idx) {
        problem->evaluate(pop->at(idx));
        statistics->increase_number_of_fitness_evaluations();
    }
}

}
