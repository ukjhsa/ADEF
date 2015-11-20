#ifndef HGBAT_H
#define HGBAT_H

#include <memory>
#include <string>
#include <cmath>
#include "Problem.h"
#include "Configuration.h"
#include "PrototypeManager.h"
#include "Individual.h"

namespace adef {

/**
@brief HGBat function.

@par The configuration
HGBat has extra configurations:
- member (optional)
    - name: "alpha"
    - value: @c double
.
It has fixed configurations:
- kind: min
- dimension_of_objective_space: 1
.
It has default configurations:
- dimension_of_decision_space: 30
- lower_bound_of_decision_space: -100.0
- upper_bound_of_decision_space: 100.0
- optimal_solution: 0.0
- alpha: 0.25
.
See setup() for the details.

@sa HappyCat
*/
class HGBat : public Problem
{
public:

/// @copydoc Problem::Object
    using Object = typename Problem::Object;

    HGBat() : Problem("HGBat")
    {
    }
    HGBat(const HGBat& rhs) = default;

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<HGBat> clone() const
    {
        return std::dynamic_pointer_cast<HGBat>(clone_impl());
    }
/**
@brief Set up the internal states.

If HGBat has the following configuration:
- dimension_of_decision_space: 30
- lower_bound_of_decision_space: -100.0
- upper_bound_of_decision_space: 100.0
- optimal_solution: 0.0
- alpha: 0.25
.
its configuration should be
- JSON configuration
@code
"Problem": {
    "classname" : "HGBat",
    "dimension_of_decision_space" : 30,
    "lower_bound_of_decision_space" : -100.0,
    "upper_bound_of_decision_space" : 100.0,
    "optimal_solution" : 0.0,
    "alpha" : 0.25
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

        auto alpha_config = config.get_config("alpha");
        alpha_ = alpha_config.is_null() ?
                                0.25 : alpha_config.get_value<Object>();
    }

    void evaluation_function(std::shared_ptr<Individual> individual) const override
    {
        Object sum = 0.0, sum_square = 0.0;
        for (unsigned int idx = 0; idx < dimension_of_decision_space_; ++idx) {
            Object ind_i = individual->variables(idx);

            sum += ind_i;
            sum_square += ind_i * ind_i;
        }
        Object result = std::pow(sum_square * sum_square - sum * sum,
                                 2 * alpha_) +
                        (0.5*sum_square + sum) / dimension_of_decision_space_ +
                        0.5;

        individual->objectives() = result;
        individual->set_fitness_value(result);
    }

private:

    Object alpha_;

private:

    std::shared_ptr<Prototype> clone_impl() const override
    {
        return std::make_shared<HGBat>(*this);
    }
};

}

#endif // HGBAT_H
