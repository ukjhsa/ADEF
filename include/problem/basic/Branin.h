#ifndef BRANIN_H
#define BRANIN_H

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
@brief Branin function.

@par The configuration
Branin has no extra configurations.@n
It has fixed configurations:
- kind: min
- dimension_of_decision_space: 2
- lower_bound_of_decision_space: [-5.0, 0.0]
- upper_bound_of_decision_space: [10.0, 15.0]
- dimension_of_objective_space: 1
- optimal_solution: 0.39788735772973816
.
See setup() for the details.
*/
class Branin : public Problem
{
public:

/// @copydoc Problem::Object
    using Object = typename Problem::Object;

    Branin() : Problem("Branin")
    {
    }
    Branin(const Branin& rhs) = default;

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<Branin> clone() const
    {
        return std::dynamic_pointer_cast<Branin>(clone_impl());
    }
/**
@brief Set up the internal states.

Branin's configuration should be
- JSON configuration
@code
"Problem": {
    "classname" : "Branin"
}
@endcode
.
*/
    void setup(const Configuration& config, const PrototypeManager& pm) override
    {
        problem_kind_ = MIN;
        dimension_of_decision_space_ = 2;
        boundaries_of_decision_space_.resize(dimension_of_decision_space_);
        boundaries_of_decision_space_[0].lower_bound_ = -5.0;
        boundaries_of_decision_space_[1].lower_bound_ = 0.0;
        boundaries_of_decision_space_[0].upper_bound_ = 10.0;
        boundaries_of_decision_space_[1].upper_bound_ = 15.0;
        dimension_of_objective_space_ = 1;
        optimal_solution_ = 0.39788735772973816;
    }

    void evaluation_function(std::shared_ptr<Individual> individual) const override
    {
        Object x1 = individual->variables(0),
               x2 = individual->variables(1);

        Object first = x2 -
                       5.1 * x1 * x1 / (4.0 * pi() * pi()) +
                       5.0 * x1 / pi() -
                       6.0;

        Object sum = first * first +
                     10.0 * (1.0 - 1.0 / (8.0 * pi())) * std::cos(x1) +
                     10.0;

        individual->objectives() = sum;
        individual->set_fitness_value(sum);
    }

private:

    std::shared_ptr<Prototype> clone_impl() const override
    {
        return std::make_shared<Branin>(*this);
    }
};

}

#endif
