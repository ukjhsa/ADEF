#ifndef HARTMAN_NO1_H
#define HARTMAN_NO1_H

#include <memory>
#include <string>
#include <cmath>
#include <array>
#include "Problem.h"
#include "Configuration.h"
#include "PrototypeManager.h"
#include "Individual.h"

namespace adef {

/**
@brief HartmanNo1 function.

@par The configuration
HartmanNo1 has no extra configurations.@n
It has fixed configurations:
- kind: min
- dimension_of_decision_space: 3
- lower_bound_of_decision_space: 0.0
- upper_bound_of_decision_space: 1.0
- dimension_of_objective_space: 1
- optimal_solution: -3.86278214782076
.
See setup() for the details.
*/
class HartmanNo1 : public Problem
{
public:

/// @copydoc Problem::Object
    using Object = typename Problem::Object;

    HartmanNo1() : Problem("Hartman No.1")
    {
    }
    HartmanNo1(const HartmanNo1& rhs) = default;

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<HartmanNo1> clone() const
    {
        return std::dynamic_pointer_cast<HartmanNo1>(clone_impl());
    }
/**
@brief Set up the internal states.

HartmanNo1's configuration should be
- JSON configuration
@code
"Problem": {
    "classname" : "HartmanNo1"
}
@endcode
.
*/
    void setup(const Configuration& config, const PrototypeManager& pm) override
    {
        problem_kind_ = MIN;
        dimension_of_decision_space_ = 3;
        boundaries_of_decision_space_.resize(dimension_of_decision_space_,
                                             Boundary(0.0, 1.0));
        dimension_of_objective_space_ = 1;
        optimal_solution_ = -3.86278214782076;
    }

    void evaluation_function(std::shared_ptr<Individual> individual) const override
    {
        const unsigned int n = 3, row = 4;
        std::array< std::array<Object, n>, row>
            a =
            {{
                {{3.0, 10.0, 30.0}},
                {{0.1, 10.0, 35.0}},
                {{3.0, 10.0, 30.0}},
                {{0.1, 10.0, 35.0}}
            }},
            p =
            {{
                {{0.3689, 0.117, 0.2673}},
                {{0.4699, 0.4387, 0.747}},
                {{0.1091, 0.8732, 0.5547}},
                {{0.03815, 0.5743, 0.8828}}
            }};
        std::array<Object, row> c = {{1.0, 1.2, 3.0, 3.2}};

        Object outer = 0.0;
        for (unsigned int i = 0; i < row; ++i) {

            Object inner = 0.0;
            for (unsigned int j = 0; j < n; ++j) {
                Object temp = individual->variables(j) - p[i][j];
                inner += a[i][j] * temp * temp;
            }
            outer += c[i] * std::exp(0.0 - inner);
        }

        Object sum = 0.0 - outer;

        individual->objectives() = sum;
        individual->set_fitness_value(sum);
    }

private:

    std::shared_ptr<Prototype> clone_impl() const override
    {
        return std::make_shared<HartmanNo1>(*this);
    }
};

}

#endif
