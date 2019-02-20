#include <memory>
#include <random>
#include "problem/basic/QuarticFunctionWithNoise.h"
#include "Configuration.h"
#include "PrototypeManager.h"
#include "Individual.h"
#include "Random.h"

namespace adef {

void QuarticFunctionWithNoise::setup(const Configuration& config, const PrototypeManager& pm)
{
    problem_kind_ = MIN;

    auto dim_ds_config = config.get_config("dimension_of_decision_space");
    dimension_of_decision_space_ = dim_ds_config.is_null() ?
        30 : dim_ds_config.get_uint_value();

    boundaries_of_decision_space_.resize(dimension_of_decision_space_,
        Boundary(-1.28, 1.28));

    dimension_of_objective_space_ = 1;

    optimal_solution_ = 0.0;
}

void QuarticFunctionWithNoise::evaluation_function(std::shared_ptr<Individual> individual) const
{
    Object sum = 0.0;
    for (unsigned int idx = 0; idx < dimension_of_decision_space_; ++idx) {

        Object temp = individual->variables(idx);
        sum += (idx + 1.0) * temp * temp * temp * temp;
    }
    std::uniform_real_distribution<> uniform(0.0, 1.0);
    sum += random_->generate(uniform);

    individual->objectives() = sum;
    individual->set_fitness_value(sum);
}

}