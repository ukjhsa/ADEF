#ifndef SHEKEL_NO2_H
#define SHEKEL_NO2_H

#include <memory>
#include <string>
#include <vector>
#include <array>
#include "Problem.h"
#include "Configuration.h"
#include "PrototypeManager.h"
#include "Individual.h"

namespace adef {

/**
@brief ShekelNo2 function.

@par The configuration
ShekelNo2 has no extra configurations.@n
It has fixed configurations:
- kind: min
- dimension_of_decision_space: 4
- lower_bound_of_decision_space: 0.0
- upper_bound_of_decision_space: 10.0
- dimension_of_objective_space: 1
- optimal_solution: -10.4029
.
See setup() for the details.
*/
class ShekelNo2 : public Problem
{
public:

/// @copydoc Problem::Object
    using Object = typename Problem::Object;

    ShekelNo2() : Problem("Shekel No.2")
    {
    }
    ShekelNo2(const ShekelNo2& rhs) = default;

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<ShekelNo2> clone() const
    {
        return std::dynamic_pointer_cast<ShekelNo2>(clone_impl());
    }
/**
@brief Set up the internal states.

ShekelNo2's configuration should be
- JSON configuration
@code
"Problem": {
    "classname" : "ShekelNo2"
}
@endcode
.
*/
    void setup(const Configuration& config, const PrototypeManager& pm) override
    {
        problem_kind_ = MIN;
        dimension_of_decision_space_ = 4;
        boundaries_of_decision_space_.resize(dimension_of_decision_space_,
                                             Boundary(0.0, 10.0));
        dimension_of_objective_space_ = 1;
        optimal_solution_ = -10.4029;
    }

    void evaluation_function(std::shared_ptr<Individual> individual) const override
    {
        const unsigned int row = 7, col = 4;
        std::array< std::array<Object, col>, row>
            a =
            {{
                {{4.0, 4.0, 4.0, 4.0}},
                {{1.0, 1.0, 1.0, 1.0}},
                {{8.0, 8.0, 8.0, 8.0}},
                {{6.0, 6.0, 6.0, 6.0}},
                {{3.0, 7.0, 3.0, 7.0}},
                {{2.0, 9.0, 2.0, 9.0}},
                {{5.0, 5.0, 3.0, 3.0}}
            }};
        std::array<Object, row> c = {{0.1, 0.2, 0.2, 0.4, 0.4, 0.6, 0.3}};

        Object sum = 0.0;
        for (unsigned int i = 0; i < row; ++i) {

            // calculate vector: x - a_i
            std::vector<Object> temp(dimension_of_decision_space_);
            for (unsigned int idx = 0; idx < dimension_of_decision_space_; ++idx) {
                temp[idx] = individual->variables(idx) - a[i][idx];
            }
            // calculate value: a inner dot b
            Object temp_value = 0.0;
            for (unsigned int idx = 0; idx < temp.size(); ++idx) {
                temp_value += temp[idx] * temp[idx];
            }

            temp_value = temp_value + c[i];
            sum += 1.0 / temp_value;
        }

        individual->objectives() = 0.0 - sum;
        individual->set_fitness_value(0.0 - sum);
    }

private:

    std::shared_ptr<Prototype> clone_impl() const override
    {
        return std::make_shared<ShekelNo2>(*this);
    }
};

}

#endif
