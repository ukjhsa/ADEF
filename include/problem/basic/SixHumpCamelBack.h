#ifndef SIX_HUMP_CAMEL_BACK_H
#define SIX_HUMP_CAMEL_BACK_H

#include <memory>
#include <string>
#include "Problem.h"
#include "Configuration.h"
#include "PrototypeManager.h"
#include "Individual.h"

namespace adef {

/**
@brief SixHumpCamelBack function.

@par The configuration
SixHumpCamelBack has no extra configurations.@n
It has fixed configurations:
- kind: min
- dimension_of_decision_space: 2
- lower_bound_of_decision_space: -5.0
- upper_bound_of_decision_space: 5.0
- dimension_of_objective_space: 1
- optimal_solution: -1.031628453489877
.
See setup() for the details.
*/
class SixHumpCamelBack : public Problem
{
public:

/// @copydoc Problem::Object
    using Object = typename Problem::Object;

    SixHumpCamelBack() : Problem("Six-Hump Camel-Back")
    {
    }
    SixHumpCamelBack(const SixHumpCamelBack& rhs) = default;

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<SixHumpCamelBack> clone() const
    {
        return std::dynamic_pointer_cast<SixHumpCamelBack>(clone_impl());
    }
/**
@brief Set up the internal states.

SixHumpCamelBack's configuration should be
- JSON configuration
@code
"Problem": {
    "classname" : "SixHumpCamelBack"
}
@endcode
.
*/
    void setup(const Configuration& config, const PrototypeManager& pm) override
    {
        problem_kind_ = MIN;
        dimension_of_decision_space_ = 2;
        boundaries_of_decision_space_.resize(dimension_of_decision_space_,
                                             Boundary(-5.0, 5.0));
        dimension_of_objective_space_ = 1;
        optimal_solution_ = -1.031628453489877;
    }

    void evaluation_function(std::shared_ptr<Individual> individual) const override
    {
        Object x1 = individual->variables(0),
               x2 = individual->variables(1);

        Object sum = 4.0 * x1 * x1 -
                     2.1 * x1 * x1 * x1 * x1 +
                     x1 * x1 * x1 * x1 * x1 * x1 / 3.0 +
                     x1 * x2 -
                     4.0 * x2 * x2 +
                     4.0 * x2 * x2 * x2 * x2;

        individual->objectives() = sum;
        individual->set_fitness_value(sum);
    }

private:

    std::shared_ptr<Prototype> clone_impl() const override
    {
        return std::make_shared<SixHumpCamelBack>(*this);
    }
};

}

#endif
