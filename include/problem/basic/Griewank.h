#ifndef GRIEWANK_H
#define GRIEWANK_H

#include <memory>
#include <string>
#include <cmath>
#include "Problem.h"
#include "Configuration.h"
#include "PrototypeManager.h"
#include "Individual.h"

namespace adef {

/**
@brief Griewank function.

@par The configuration
Griewank has no extra configurations.@n
It has fixed configurations:
- kind: min
- dimension_of_objective_space: 1
.
It has default configurations:
- dimension_of_decision_space: 30
- lower_bound_of_decision_space: -600.0
- upper_bound_of_decision_space: 600.0
- optimal_solution: 0.0
.
See setup() for the details.
*/
class Griewank : public Problem
{
public:

/// @copydoc Problem::Object
    using Object = typename Problem::Object;

    Griewank() : Problem("Griewank")
    {
    }
    Griewank(const Griewank& rhs) = default;

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<Griewank> clone() const
    {
        return std::dynamic_pointer_cast<Griewank>(clone_impl());
    }
/**
@brief Set up the internal states.

If Griewank has the following configuration:
- dimension_of_decision_space: 30
- lower_bound_of_decision_space: -600.0
- upper_bound_of_decision_space: 600.0
- optimal_solution: 0.0
.
its configuration should be
- JSON configuration
@code
"Problem": {
    "classname" : "Griewank",
    "dimension_of_decision_space" : 30,
    "lower_bound_of_decision_space" : -600.0,
    "upper_bound_of_decision_space" : 600.0,
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
                            -600.0 : lb_ds_config.get_value<Object>();

        auto ub_ds_config = config.get_config("upper_bound_of_decision_space");
        auto ub_ds = ub_ds_config.is_null() ?
                            600.0 : ub_ds_config.get_value<Object>();
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
        Object first = 0.0, second = 1.0;

        for (unsigned int idx = 0; idx < dimension_of_decision_space_; ++idx) {
            Object ind_i = individual->variables(idx);

            first += ind_i * ind_i;
            second *= std::cos(ind_i / std::sqrt(idx + 1.0));
        }
        sum = first / 4000.0 - second + 1.0;

        individual->objectives() = sum;
        individual->set_fitness_value(sum);
    }

private:

    std::shared_ptr<Prototype> clone_impl() const override
    {
        return std::make_shared<Griewank>(*this);
    }
};

}

#endif
