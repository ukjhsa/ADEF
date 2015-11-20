#ifndef GENERALIZED_PENALIZED_NO2_H
#define GENERALIZED_PENALIZED_NO2_H

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
@brief GeneralizedPenalizedNo2 function.

@par The configuration
GeneralizedPenalizedNo2 has no extra configurations.@n
It has fixed configurations:
- kind: min
- dimension_of_objective_space: 1
.
It has default configurations:
- dimension_of_decision_space: 30
- lower_bound_of_decision_space: -50.0
- upper_bound_of_decision_space: 50.0
- optimal_solution: 0.0
.
See setup() for the details.
*/

class GeneralizedPenalizedNo2 : public Problem
{
public:

/// @copydoc Problem::Object
    using Object = typename Problem::Object;

    GeneralizedPenalizedNo2() : Problem("Generalized Penalized No.2")
    {
    }
    GeneralizedPenalizedNo2(const GeneralizedPenalizedNo2& rhs) = default;

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<GeneralizedPenalizedNo2> clone() const
    {
        return std::dynamic_pointer_cast<GeneralizedPenalizedNo2>(clone_impl());
    }
/**
@brief Set up the internal states.

If GeneralizedPenalizedNo2 has the following configuration:
- dimension_of_decision_space: 30
- lower_bound_of_decision_space: -50.0
- upper_bound_of_decision_space: 50.0
- optimal_solution: 0.0
.
its configuration should be
- JSON configuration
@code
"Problem": {
    "classname" : "GeneralizedPenalizedNo2",
    "dimension_of_decision_space" : 30,
    "lower_bound_of_decision_space" : -50.0,
    "upper_bound_of_decision_space" : 50.0,
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
                            -50.0 : lb_ds_config.get_value<Object>();

        auto ub_ds_config = config.get_config("upper_bound_of_decision_space");
        auto ub_ds = ub_ds_config.is_null() ?
                            50.0 : ub_ds_config.get_value<Object>();
        boundaries_of_decision_space_.resize(dimension_of_decision_space_,
                                             Boundary(lb_ds, ub_ds));

        dimension_of_objective_space_ = 1;

        auto optimal_config = config.get_config("optimal_solution");
        optimal_solution_ = optimal_config.is_null() ?
                                0.0 : optimal_config.get_value<Object>();
    }

    void evaluation_function(std::shared_ptr<Individual> individual) const override
    {
        Object inner = 0.0, outer = 0.0;

        Object temp = std::sin(3.0 * pi() * individual->variables(0));
        inner += temp * temp;
        for (unsigned int idx = 0; idx < dimension_of_decision_space_ - 1; ++idx) {
            Object temp = individual->variables(idx) - 1;
            Object temp_sin = std::sin(3.0 * pi() * individual->variables(idx+1));
            inner += temp * temp * (1 + temp_sin * temp_sin);
        }
        temp = individual->variables(dimension_of_decision_space_ - 1) - 1;
        Object temp_sin = std::sin(2.0 * pi() *
                        individual->variables(dimension_of_decision_space_ - 1));
        inner += temp * temp * (1.0 + temp_sin * temp_sin);

        for (unsigned int idx = 0; idx < dimension_of_decision_space_; ++idx) {
            outer += u(individual->variables(idx), 5, 100, 4);
        }
        Object sum = 0.1 * inner + outer;

        individual->objectives() = sum;
        individual->set_fitness_value(sum);
    }

private:

    double u(double x, double a, double k, double m) const
    {
        if (x > a) {
            return k * std::pow(x - a, m);
        }
        else if (x < 0.0 - a) {
            return k * std::pow(0.0 - x - a, m);
        }
        else {
            return 0.0;
        }
    }

private:

    std::shared_ptr<Prototype> clone_impl() const override
    {
        return std::make_shared<GeneralizedPenalizedNo2>(*this);
    }
};

}

#endif
