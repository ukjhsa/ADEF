#include <memory>
#include "Evolution.h"
#include "Configuration.h"
#include "PrototypeManager.h"
#include "Repository.h"
#include "Initializer.h"
#include "Evaluator.h"
#include "Reproduction.h"
#include "EnvironmentalSelection.h"
#include "Problem.h"
#include "Population.h"
#include "Statistics.h"
#include "Parameters.h"

namespace adef {

void Evolution::setup(const Configuration& config, const PrototypeManager& pm)
{
    max_generation_ = config.get_uint_value("max_generation");
}

void Evolution::init(std::shared_ptr<Repository> repos)
{
}

void Evolution::evolve(std::shared_ptr<Repository> repos) const
{

    // initialization
    repos->initializer()->initialize(repos);

    // evaluation
    repos->evaluator()->evaluate(repos->population(),
                                 repos->problem(),
                                 repos->statistics());

    repos->statistics()->take_statistics(repos);

    // for each generation
    unsigned int gen = 1;
    while (gen <= max_generation_ && !is_evolve_terminated(repos)) {
        repos->parameters()->store("generation", gen);

        // reproduction
        repos->reproduction()->reproduce(repos);

        repos->evaluator()->evaluate(repos->offspring(),
                                     repos->problem(),
                                     repos->statistics());

        repos->statistics()->post_reproduction_statistic(repos);

        // environmental selection
        repos->environmental_selection()->select(repos);

        repos->statistics()->take_statistics(repos);
        // increase generation
        ++gen;
    }
}

bool Evolution::is_evolve_terminated(std::shared_ptr<const Repository> repos) const
{
    if (repos->statistics()->is_evolve_success(repos)) {
        return true;
    }
    else {
        return false;
    }
}

}
