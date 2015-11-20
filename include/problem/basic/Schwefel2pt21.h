#ifndef SCHWEFEL_2PT21_H
#define SCHWEFEL_2PT21_H

#include <memory>
#include <string>
#include <cmath>
#include "Problem.h"
#include "Configuration.h"
#include "PrototypeManager.h"
#include "Individual.h"

namespace adef {

/**
@brief Schwefel2pt21 function.

@par The configuration
Schwefel2pt21 has no extra configurations.@n
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
class Schwefel2pt21 : public Problem
{
public:

/// @copydoc Problem::Object
    using Object = typename Problem::Object;

    Schwefel2pt21() : Problem("Schwefel 2.21")
    {
    }
    Schwefel2pt21(const Schwefel2pt21& rhs) = default;

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<Schwefel2pt21> clone() const
    {
        return std::dynamic_pointer_cast<Schwefel2pt21>(clone_impl());
    }
/**
@brief Set up the internal states.

If Schwefel2pt21 has the following configuration:
- dimension_of_decision_space: 30
- lower_bound_of_decision_space: -100.0
- upper_bound_of_decision_space: 100.0
- optimal_solution: 0.0
.
its configuration should be
- JSON configuration
@code
"Problem": {
    "classname" : "Schwefel2pt21",
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
        Object max = std::abs(individual->variables(0));
        for (unsigned int idx = 1; idx < dimension_of_decision_space_; ++idx) {
            Object temp = std::abs(individual->variables(idx));
            if (max < temp) {
                max = temp;
            }
        }
        individual->objectives() = max;
        individual->set_fitness_value(max);
    }

private:

    std::shared_ptr<Prototype> clone_impl() const override
    {
        return std::make_shared<Schwefel2pt21>(*this);
    }
};

}

#endif
