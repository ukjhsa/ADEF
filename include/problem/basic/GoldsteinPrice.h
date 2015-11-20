#ifndef GOLDSTEIN_PRICE_H
#define GOLDSTEIN_PRICE_H

#include <memory>
#include <string>
#include "Problem.h"
#include "Configuration.h"
#include "PrototypeManager.h"
#include "Individual.h"

namespace adef {

/**
@brief GoldsteinPrice function.

@par The configuration
GoldsteinPrice has no extra configurations.@n
It has fixed configurations:
- kind: min
- dimension_of_decision_space: 2
- lower_bound_of_decision_space: -2.0
- upper_bound_of_decision_space: 2.0
- dimension_of_objective_space: 1
- optimal_solution: 3.0
.
See setup() for the details.
*/
class GoldsteinPrice : public Problem
{
public:

/// @copydoc Problem::Object
    using Object = typename Problem::Object;

    GoldsteinPrice() : Problem("Goldstein-Price")
    {
    }
    GoldsteinPrice(const GoldsteinPrice& rhs) = default;

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<GoldsteinPrice> clone() const
    {
        return std::dynamic_pointer_cast<GoldsteinPrice>(clone_impl());
    }
/**
@brief Set up the internal states.

GoldsteinPrice's configuration should be
- JSON configuration
@code
"Problem": {
    "classname" : "GoldsteinPrice"
}
@endcode
.
*/
    void setup(const Configuration& config, const PrototypeManager& pm) override
    {
        problem_kind_ = MIN;
        dimension_of_decision_space_ = 2;
        boundaries_of_decision_space_.resize(dimension_of_decision_space_,
                                             Boundary(-2.0, 2.0));
        dimension_of_objective_space_ = 1;
        optimal_solution_ = 3.0;
    }

    void evaluation_function(std::shared_ptr<Individual> individual) const override
    {
        Object x1 = individual->variables(0),
               x2 = individual->variables(1);

        Object first = x1 + x2 + 1.0,
               second = 2.0 * x1 - 3.0 * x2;

        first = 1.0 + first * first * (19.0 -
                                       14.0 * x1 +
                                       3.0 * x1 * x1 -
                                       14.0 * x2 +
                                       6.0 * x1 * x2 +
                                       3 * x2 * x2);
        second = 30.0 + second * second * (18.0 -
                                           32.0 * x1 +
                                           12.0 * x1 * x1 +
                                           48.0 * x2 -
                                           36.0 * x1 * x2 +
                                           27.0 * x2 * x2);
        Object sum = first * second;

        individual->objectives() = sum;
        individual->set_fitness_value(sum);
    }

private:

    std::shared_ptr<Prototype> clone_impl() const override
    {
        return std::make_shared<GoldsteinPrice>(*this);
    }
};

}

#endif
