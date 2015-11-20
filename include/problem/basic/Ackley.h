#ifndef ACKLEY_H
#define ACKLEY_H

#include <memory>
#include <string>
#include <cmath>
#include "Problem.h"
#include "Configuration.h"
#include "PrototypeManager.h"
#include "Individual.h"
#include "util/math_tool.h"

namespace adef {

/**
@brief Ackley function.

@par The configuration
Ackley has no extra configurations.@n
It has fixed configurations:
- kind: min
- dimension_of_objective_space: 1
.
It has default configurations:
- dimension_of_decision_space: 30
- lower_bound_of_decision_space: -32.0
- upper_bound_of_decision_space: 32.0
- optimal_solution: 0.0
.
See setup() for the details.
*/
class Ackley : public Problem
{
public:

/// @copydoc Problem::Object
    using Object = typename Problem::Object;

    Ackley() : Problem("Ackley")
    {
    }
    Ackley(const Ackley& rhs) = default;

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<Ackley> clone() const
    {
        return std::dynamic_pointer_cast<Ackley>(clone_impl());
    }
/**
@brief Set up the internal states.

If Ackley has the following configuration:
- dimension_of_decision_space: 30
- lower_bound_of_decision_space: -32.0
- upper_bound_of_decision_space: 32.0
- optimal_solution: 0.0
.
its configuration should be
- JSON configuration
@code
"Problem": {
    "classname" : "Ackley",
    "dimension_of_decision_space" : 30,
    "lower_bound_of_decision_space" : -32.0,
    "upper_bound_of_decision_space" : 32.0,
    "optimal_solution" : 0.0
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

        auto lb_ds_config = config.get_config("lower_bound_of_decision_space");
        auto lb_ds = lb_ds_config.is_null() ?
                            -32.0 : lb_ds_config.get_value<Object>();

        auto ub_ds_config = config.get_config("upper_bound_of_decision_space");
        auto ub_ds = ub_ds_config.is_null() ?
                            32.0 : ub_ds_config.get_value<Object>();
        boundaries_of_decision_space_.resize(dimension_of_decision_space_,
                                             Boundary(lb_ds, ub_ds));

        dimension_of_objective_space_ = 1;

        auto optimal_config = config.get_config("optimal_solution");
        optimal_solution_ = optimal_config.is_null() ?
                                0.0 : optimal_config.get_value<Object>();
    }

    void evaluation_function(std::shared_ptr<Individual> individual) const override
    {
        Object first = 0.0, second = 0.0;
        for (unsigned int i = 0; i < dimension_of_decision_space_; ++i) {
            Object ind_i = individual->variables(i);

            first += ind_i * ind_i;
            second += std::cos(2.0 * pi() * ind_i);
        }
        Object sum = -20.0 * std::exp(-0.2 * std::sqrt(first / dimension_of_decision_space_)) -
                     std::exp(second / dimension_of_decision_space_) +
                     20.0 +
                     std::exp(1.0);

        individual->objectives() = sum;
        individual->set_fitness_value(sum);
    }

private:

    std::shared_ptr<Prototype> clone_impl() const override
    {
        return std::make_shared<Ackley>(*this);
    }
};

}

#endif
