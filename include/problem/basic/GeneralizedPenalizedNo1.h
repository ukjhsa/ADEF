#ifndef GENERALIZED_PENALIZED_NO1_H
#define GENERALIZED_PENALIZED_NO1_H

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
@brief GeneralizedPenalizedNo1 function.

@par The configuration
GeneralizedPenalizedNo1 has no extra configurations.@n
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
class GeneralizedPenalizedNo1 : public Problem
{
public:

/// @copydoc Problem::Object
    using Object = typename Problem::Object;

    GeneralizedPenalizedNo1() : Problem("Generalized Penalized No.1")
    {
    }
    GeneralizedPenalizedNo1(const GeneralizedPenalizedNo1& rhs) = default;

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<GeneralizedPenalizedNo1> clone() const
    {
        return std::dynamic_pointer_cast<GeneralizedPenalizedNo1>(clone_impl());
    }
/**
@brief Set up the internal states.

If GeneralizedPenalizedNo1 has the following configuration:
- dimension_of_decision_space: 30
- lower_bound_of_decision_space: -50.0
- upper_bound_of_decision_space: 50.0
- optimal_solution: 0.0
.
its configuration should be
- JSON configuration
@code
"Problem": {
    "classname" : "GeneralizedPenalizedNo1",
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

        Object temp_sin = std::sin(pi() * y(individual->variables(0)));
        inner += 10.0 * temp_sin * temp_sin;
        for (unsigned int idx = 0; idx < dimension_of_decision_space_ - 1; ++idx) {
            Object temp = y(individual->variables(idx)) - 1;
            Object temp_sin = std::sin(pi() * y(individual->variables(idx+1)));
            inner += temp * temp * (1.0 + 10.0 * temp_sin * temp_sin);
        }

        Object temp = y(individual->variables(dimension_of_decision_space_ - 1)) - 1;
        inner += temp * temp;

        for (unsigned int idx = 0; idx < dimension_of_decision_space_; ++idx) {
            outer += u(individual->variables(idx), 10, 100, 4);
        }

        Object sum = pi() * inner / dimension_of_decision_space_ + outer;

        individual->objectives() = sum;
        individual->set_fitness_value(sum);
    }

private:

    double y(double x) const
    {
        return 1.0 + (x + 1.0) / 4.0;
    }

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
        return std::make_shared<GeneralizedPenalizedNo1>(*this);
    }
};

}

#endif
