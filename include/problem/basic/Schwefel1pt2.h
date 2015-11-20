#ifndef SCHWEFEL_1PT2_H
#define SCHWEFEL_1PT2_H

#include <memory>
#include <string>
#include <cmath>
#include "Problem.h"
#include "Configuration.h"
#include "PrototypeManager.h"
#include "Individual.h"

namespace adef {

/**
@brief Schwefel1pt2 function.

@par The configuration
Schwefel1pt2 has no extra configurations.@n
It has fixed configurations:
- kind: min
- dimension_of_objective_space: 1
.
It has default configurations:
- dimension_of_decision_space: 30
- lower_bound_of_decision_space: -100.0
- upper_bound_of_decision_space: 100.0
- optimal_solution: 0.0
.
See setup() for the details.
*/
class Schwefel1pt2 : public Problem
{
public:

/// @copydoc Problem::Object
    using Object = typename Problem::Object;

    Schwefel1pt2() : Problem("Schwefel 1.2")
    {
    }
    Schwefel1pt2(const Schwefel1pt2& rhs) = default;

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<Schwefel1pt2> clone() const
    {
        return std::dynamic_pointer_cast<Schwefel1pt2>(clone_impl());
    }
/**
@brief Set up the internal states.

If Schwefel1pt2 has the following configuration:
- dimension_of_decision_space: 30
- lower_bound_of_decision_space: -100.0
- upper_bound_of_decision_space: 100.0
- optimal_solution: 0.0
.
its configuration should be
- JSON configuration
@code
"Problem": {
    "classname" : "Schwefel1pt2",
    "dimension_of_decision_space" : 30,
    "lower_bound_of_decision_space" : -100.0,
    "upper_bound_of_decision_space" : 100.0,
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
                            -100.0 : lb_ds_config.get_value<Object>();

        auto ub_ds_config = config.get_config("upper_bound_of_decision_space");
        auto ub_ds = ub_ds_config.is_null() ?
                            100.0 : ub_ds_config.get_value<Object>();
        boundaries_of_decision_space_.resize(dimension_of_decision_space_,
                                             Boundary(lb_ds, ub_ds));

        dimension_of_objective_space_ = 1;

        auto optimal_config = config.get_config("optimal_solution");
        optimal_solution_ = optimal_config.is_null() ?
                                0.0 : optimal_config.get_value<Object>();
    }

    void evaluation_function(std::shared_ptr<Individual> individual) const override
    {
        Object sum = 0.0;
        for (unsigned int i = 0; i < dimension_of_decision_space_; ++i) {
            Object inner_part = 0;
            for (unsigned int j = 0; j <= i; ++j) {
                inner_part += individual->variables(j);
            }
            sum += inner_part * inner_part;
        }
        individual->objectives() = sum;
        individual->set_fitness_value(sum);
    }

private:

    std::shared_ptr<Prototype> clone_impl() const override
    {
        return std::make_shared<Schwefel1pt2>(*this);
    }
};

}

#endif
