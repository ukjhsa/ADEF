#ifndef HARTMAN_NO2_H
#define HARTMAN_NO2_H

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
@brief HartmanNo2 function.

@par The configuration
HartmanNo2 has no extra configurations.@n
It has fixed configurations:
- kind: min
- dimension_of_decision_space: 6
- lower_bound_of_decision_space: 0.0
- upper_bound_of_decision_space: 1.0
- dimension_of_objective_space: 1
- optimal_solution: -3.32
.
See setup() for the details.

\xrefitem success_error "Success Error" "Success Errors"
If the optimal solution set to the accurate value -3.32236801141551,
then many algorithms can @em NOT solve this problem.
*/
class HartmanNo2 : public Problem
{
public:

/// @copydoc Problem::Object
    using Object = typename Problem::Object;

    HartmanNo2() : Problem("Hartman No.2")
    {
    }
    HartmanNo2(const HartmanNo2& rhs) = default;

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<HartmanNo2> clone() const
    {
        return std::dynamic_pointer_cast<HartmanNo2>(clone_impl());
    }
/**
@brief Set up the internal states.

HartmanNo2's configuration should be
- JSON configuration
@code
"Problem": {
    "classname" : "HartmanNo2"
}
@endcode
.
*/
    void setup(const Configuration& config, const PrototypeManager& pm) override
    {
        problem_kind_ = MIN;
        dimension_of_decision_space_ = 6;
        boundaries_of_decision_space_.resize(dimension_of_decision_space_,
                                             Boundary(0.0, 1.0));
        dimension_of_objective_space_ = 1;
        optimal_solution_ = -3.32;
    }

    void evaluation_function(std::shared_ptr<Individual> individual) const override
    {
        const unsigned int n = 6, row = 4;
        std::array< std::array<Object, n>, row>
            a =
            {{
                {{10.0, 3.0, 17.0, 3.5, 1.7, 8.0}},
                {{0.05, 10.0, 17.0, 0.1, 8.0, 14.0}},
                {{3.0, 3.5, 1.7, 10.0, 17.0, 8.0}},
                {{17.0, 8.0, 0.05, 10.0, 0.1, 14.0}}
            }},
            p =
            {{
                {{0.1312, 0.1696, 0.5569, 0.0124, 0.8283, 0.5886}},
                {{0.2329, 0.4135, 0.8307, 0.3736, 0.1004, 0.9991}},
                {{0.2348, 0.1415, 0.3522, 0.2883, 0.3047, 0.665}},
                {{0.4047, 0.8828, 0.8732, 0.5743, 0.1091, 0.0381}}
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
        return std::make_shared<HartmanNo2>(*this);
    }
};

}

#endif
