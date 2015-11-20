#ifndef SHEKEL_FOXHOLES_H
#define SHEKEL_FOXHOLES_H

#include <memory>
#include <string>
#include <array>
#include "Problem.h"
#include "Configuration.h"
#include "PrototypeManager.h"
#include "Individual.h"

namespace adef {

/**
@brief ShekelFoxholes function.

@par The configuration
ShekelFoxholes has no extra configurations.@n
It has fixed configurations:
- kind: min
- dimension_of_decision_space: 2
- lower_bound_of_decision_space: -65.536
- upper_bound_of_decision_space: 65.536
- dimension_of_objective_space: 1
- optimal_solution: 0.998004
.
See setup() for the details.
*/
class ShekelFoxholes : public Problem
{
public:

/// @copydoc Problem::Object
    using Object = typename Problem::Object;

    ShekelFoxholes() : Problem("Shekel Foxholes")
    {
    }
    ShekelFoxholes(const ShekelFoxholes& rhs) = default;

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<ShekelFoxholes> clone() const
    {
        return std::dynamic_pointer_cast<ShekelFoxholes>(clone_impl());
    }
/**
@brief Set up the internal states.

ShekelFoxholes's configuration should be
- JSON configuration
@code
"Problem": {
    "classname" : "ShekelFoxholes"
}
@endcode
.
*/
    void setup(const Configuration& config, const PrototypeManager& pm) override
    {
        problem_kind_ = MIN;
        dimension_of_decision_space_ = 2;
        boundaries_of_decision_space_.resize(dimension_of_decision_space_,
                                             Boundary(-65.536, 65.536));
        dimension_of_objective_space_ = 1;
        optimal_solution_ = 0.998004;
    }

    void evaluation_function(std::shared_ptr<Individual> individual) const override
    {
        const unsigned int row_param = 2, col_param = 25;
        std::array< std::array<Object, col_param> , row_param> param_a =
            {{
                {{-32.0, -16.0, 0.0, 16.0, 32.0, -32.0, -16.0, 0.0, 16.0, 32.0,
                 -32.0, -16.0, 0.0, 16.0, 32.0, -32.0, -16.0, 0.0, 16.0, 32.0,
                 -32.0, -16.0, 0.0, 16.0, 32.0}},
                {{-32.0, -32.0, -32.0, -32.0, -32.0,
                  -16.0, -16.0, -16.0, -16.0, -16.0,
                  0.0, 0.0, 0.0, 0.0, 0.0,
                  16.0, 16.0, 16.0, 16.0, 16.0,
                  32.0, 32.0, 32.0, 32.0, 32.0}}
            }};

        Object right_part = 0.0;
        for (unsigned int j = 0; j < col_param; ++j) {
            Object i_part = 0.0;
            for (unsigned int i = 0; i < row_param; ++i) {
                Object temp = individual->variables(i) - param_a[i][j];
                i_part += temp * temp * temp * temp * temp * temp;
            }
            right_part += 1.0 / ((j+1.0) + i_part);
        }
        Object sum = 1.0 / (0.002 + right_part);

        individual->objectives() = sum;
        individual->set_fitness_value(sum);
    }

private:

    std::shared_ptr<Prototype> clone_impl() const override
    {
        return std::make_shared<ShekelFoxholes>(*this);
    }
};

}

#endif
