#ifndef ROSENBROCK_H
#define ROSENBROCK_H

#include <memory>
#include <string>
#include "Problem.h"
#include "Configuration.h"
#include "PrototypeManager.h"
#include "Individual.h"

namespace adef {

/**
@brief Rosenbrock function.

@par The configuration
Rosenbrock has no extra configurations.@n
It has fixed configurations:
- kind: min
- dimension_of_objective_space: 1
.
It has default configurations:
- dimension_of_decision_space: 30
- lower_bound_of_decision_space: -30.0
- upper_bound_of_decision_space: 30.0
- optimal_solution: 0.0
.
See setup() for the details.
*/
class Rosenbrock : public Problem
{
public:

/// @copydoc Problem::Object
    using Object = typename Problem::Object;

    Rosenbrock() : Problem("Rosenbrock")
    {
    }
    Rosenbrock(const Rosenbrock& rhs) = default;

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<Rosenbrock> clone() const
    {
        return std::dynamic_pointer_cast<Rosenbrock>(clone_impl());
    }
/**
@brief Set up the internal states.

If Rosenbrock has the following configuration:
- dimension_of_decision_space: 30
- lower_bound_of_decision_space: -30.0
- upper_bound_of_decision_space: 30.0
- optimal_solution: 0.0
.
its configuration should be
- JSON configuration
@code
"Problem": {
    "classname" : "Rosenbrock",
    "dimension_of_decision_space" : 30,
    "lower_bound_of_decision_space" : -30.0,
    "upper_bound_of_decision_space" : 30.0,
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
                            -30.0 : lb_ds_config.get_value<Object>();

        auto ub_ds_config = config.get_config("upper_bound_of_decision_space");
        auto ub_ds = ub_ds_config.is_null() ?
                            30.0 : ub_ds_config.get_value<Object>();
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
        for (unsigned int idx = 0; idx < dimension_of_decision_space_ - 1; ++idx) {

            Object ind_i = individual->variables(idx),
                   ind_iplus1 = individual->variables(idx+1);

            Object first_part = ind_iplus1 - ind_i * ind_i,
                   second_part = ind_i - 1.0;

            sum += 100.0 * first_part * first_part + second_part * second_part;
        }
        individual->objectives() = sum;
        individual->set_fitness_value(sum);
    }

private:

    std::shared_ptr<Prototype> clone_impl() const override
    {
        return std::make_shared<Rosenbrock>(*this);
    }
};

}

#endif // ROSENBROCK_H
