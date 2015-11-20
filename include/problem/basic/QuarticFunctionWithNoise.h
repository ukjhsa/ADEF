#ifndef QUARTIC_FUNCTION_WITH_NOISE_H
#define QUARTIC_FUNCTION_WITH_NOISE_H

#include <memory>
#include <string>
#include <random>
#include "Problem.h"
#include "Configuration.h"
#include "PrototypeManager.h"
#include "Individual.h"

namespace adef {

/**
@brief QuarticFunctionWithNoise function.

@par The configuration
QuarticFunctionWithNoise has no extra configurations.@n
It has fixed configurations:
- kind: min
- lower_bound_of_decision_space: -1.28
- upper_bound_of_decision_space: 1.28
- dimension_of_objective_space: 1
- optimal_solution: 0.0
.
It has default configurations:
- dimension_of_decision_space: 30
.
See setup() for the details.
*/
class QuarticFunctionWithNoise : public Problem
{
public:

/// @copydoc Problem::Object
    using Object = typename Problem::Object;

    QuarticFunctionWithNoise() : Problem("Quartic Function with Noise")
    {
    }
    QuarticFunctionWithNoise(const QuarticFunctionWithNoise& rhs) = default;

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<QuarticFunctionWithNoise> clone() const
    {
        return std::dynamic_pointer_cast<QuarticFunctionWithNoise>(clone_impl());
    }
/**
@brief Set up the internal states.

If QuarticFunctionWithNoise has the following configuration:
- dimension_of_decision_space: 30
.
its configuration should be
- JSON configuration
@code
"Problem": {
    "classname" : "QuarticFunctionWithNoise",
    "dimension_of_decision_space" : 30
}
@endcode
.
*/
    void setup(const Configuration& config, const PrototypeManager& pm) override
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

    void evaluation_function(std::shared_ptr<Individual> individual) const override
    {
        Object sum = 0.0;
        for (unsigned int idx = 0; idx < dimension_of_decision_space_; ++idx) {

            Object temp = individual->variables(idx);
            sum += (idx + 1.0) * temp * temp * temp * temp;
        }
        std::mt19937 gen(std::rand());
        std::uniform_real_distribution<> uniform(0.0, 1.0);
        sum += uniform(gen);

        individual->objectives() = sum;
        individual->set_fitness_value(sum);
    }

private:

    std::shared_ptr<Prototype> clone_impl() const override
    {
        return std::make_shared<QuarticFunctionWithNoise>(*this);
    }
};

}

#endif
