#ifndef KOWALIK_H
#define KOWALIK_H

#include <memory>
#include <string>
#include <array>
#include "Problem.h"
#include "Configuration.h"
#include "PrototypeManager.h"
#include "Individual.h"

namespace adef {

/**
@brief Kowalik function.

@par The configuration
Kowalik has no extra configurations.@n
It has fixed configurations:
- kind: min
- dimension_of_decision_space: 4
- lower_bound_of_decision_space: -5.0
- upper_bound_of_decision_space: 5.0
- dimension_of_objective_space: 1
- optimal_solution: 0.0003075
.
See setup() for the details.
*/
class Kowalik : public Problem
{
public:

/// @copydoc Problem::Object
    using Object = typename Problem::Object;

    Kowalik() : Problem("Kowalik")
    {
    }
    Kowalik(const Kowalik& rhs) = default;

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<Kowalik> clone() const
    {
        return std::dynamic_pointer_cast<Kowalik>(clone_impl());
    }
/**
@brief Set up the internal states.

Kowalik's configuration should be
- JSON configuration
@code
"Problem": {
    "classname" : "Kowalik"
}
@endcode
.
*/
    void setup(const Configuration& config, const PrototypeManager& pm) override
    {
        problem_kind_ = MIN;
        dimension_of_decision_space_ = 4;
        boundaries_of_decision_space_.resize(dimension_of_decision_space_,
                                             Boundary(-5.0, 5.0));
        dimension_of_objective_space_ = 1;
        optimal_solution_ = 0.0003075;
    }

    void evaluation_function(std::shared_ptr<Individual> individual) const override
    {
        const unsigned int param_size = 11;
        std::array< Object , param_size>
            a =
            {{
                0.1957, 0.1947, 0.1735, 0.16, 0.0844, 0.0627,
                0.0456, 0.0342, 0.0323, 0.0235, 0.0246
            }},
            b =
            {{
                1.0/0.25, 1.0/0.5, 1.0/1.0, 1.0/2.0, 1.0/4.0, 1.0/6.0,
                1.0/8.0, 1.0/10.0, 1.0/12.0, 1.0/14.0, 1.0/16.0
            }};

        Object sum = 0.0;
        for (unsigned int i = 0; i < param_size; ++i) {

            Object numerator = individual->variables(0) *
                               (b[i] * b[i] + b[i] * individual->variables(1));
            Object denominator = b[i] * b[i] +
                                 b[i] * individual->variables(2) +
                                 individual->variables(3);

            Object temp = a[i] - numerator / denominator;
            sum += temp * temp;
        }
        individual->objectives() = sum;
        individual->set_fitness_value(sum);
    }

private:

    std::shared_ptr<Prototype> clone_impl() const override
    {
        return std::make_shared<Kowalik>(*this);
    }
};

}

#endif
