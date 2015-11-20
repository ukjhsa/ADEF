#ifndef GENERALIZED_SCHWEFEL_2PT26_H
#define GENERALIZED_SCHWEFEL_2PT26_H

#include <memory>
#include <string>
#include <cmath>
#include "Problem.h"
#include "Configuration.h"
#include "PrototypeManager.h"
#include "Individual.h"

namespace adef {

/**
@brief GeneralizedSchwefel2pt26 function.

@par The configuration
GeneralizedSchwefel2pt26 has no extra configurations.@n
It has fixed configurations:
- kind: min
- dimension_of_objective_space: 1
.
It has default configurations:
- dimension_of_decision_space: 30
- lower_bound_of_decision_space: -500.0
- upper_bound_of_decision_space: 500.0
- optimal_solution: -418.982887272433799807913601398 * dimension_of_decision_space
.
See setup() for the details.
*/
class GeneralizedSchwefel2pt26 : public Problem
{
public:

/// @copydoc Problem::Object
    using Object = typename Problem::Object;

    GeneralizedSchwefel2pt26() : Problem("Generalized Schwefel 2.26")
    {
    }
    GeneralizedSchwefel2pt26(const GeneralizedSchwefel2pt26& rhs) = default;

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<GeneralizedSchwefel2pt26> clone() const
    {
        return std::dynamic_pointer_cast<GeneralizedSchwefel2pt26>(clone_impl());
    }
/**
@brief Set up the internal states.

If GeneralizedSchwefel2pt26 has the following configuration:
- dimension_of_decision_space: 30
- lower_bound_of_decision_space: -500.0
- upper_bound_of_decision_space: 500.0
- optimal_solution: -12569.5
.
its configuration should be
- JSON configuration
@code
"Problem": {
    "classname" : "GeneralizedSchwefel2pt26",
    "dimension_of_decision_space" : 30,
    "lower_bound_of_decision_space" : -500.0,
    "upper_bound_of_decision_space" : 500.0,
    "optimal_solution" : -12569.5
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
                            -500.0 : lb_ds_config.get_value<Object>();

        auto ub_ds_config = config.get_config("upper_bound_of_decision_space");
        auto ub_ds = ub_ds_config.is_null() ?
                            500.0 : ub_ds_config.get_value<Object>();
        boundaries_of_decision_space_.resize(dimension_of_decision_space_,
                                             Boundary(lb_ds, ub_ds));

        dimension_of_objective_space_ = 1;

        Object optimal = -418.982887272433799807913601398 * dimension_of_decision_space_;
        auto optimal_config = config.get_config("optimal_solution");
        optimal_solution_ = optimal_config.is_null() ?
                                optimal : optimal_config.get_value<Object>();
    }

    void evaluation_function(std::shared_ptr<Individual> individual) const override
    {
        Object sum = 0.0;
        for (unsigned int idx = 0; idx < dimension_of_decision_space_; ++idx) {
            Object ind_i = individual->variables(idx);
            sum -= ind_i * std::sin(std::sqrt(std::abs(ind_i)));
        }
        individual->objectives() = sum;
        individual->set_fitness_value(sum);
    }

private:

    std::shared_ptr<Prototype> clone_impl() const override
    {
        return std::make_shared<GeneralizedSchwefel2pt26>(*this);
    }
};

}

#endif
