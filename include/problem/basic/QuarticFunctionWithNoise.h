#ifndef QUARTIC_FUNCTION_WITH_NOISE_H
#define QUARTIC_FUNCTION_WITH_NOISE_H

#include <memory>
#include "Problem.h"

namespace adef {

class Configuration;
class PrototypeManager;
class Individual;

/**
@brief QuarticFunctionWithNoise function.

@par The configuration
QuarticFunctionWithNoise has no extra configurations.@n
It has fixed configurations:
- kind: min
- lower_bound_of_decision_space: -1.28
- upper_bound_of_decision_space: 1.28
- dimension_of_objective_space: 1
- optimal_solution: 0.0
.
It has default configurations:
- dimension_of_decision_space: 30
.
See setup() for the details.
*/
class QuarticFunctionWithNoise : public Problem
{
public:

/// @copydoc Problem::Object
    using Object = typename Problem::Object;

    QuarticFunctionWithNoise() : Problem("Quartic Function with Noise")
    {
    }
    QuarticFunctionWithNoise(const QuarticFunctionWithNoise& rhs) = default;

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<QuarticFunctionWithNoise> clone() const
    {
        return std::dynamic_pointer_cast<QuarticFunctionWithNoise>(clone_impl());
    }
/**
@brief Set up the internal states.

If QuarticFunctionWithNoise has the following configuration:
- dimension_of_decision_space: 30
.
its configuration should be
- JSON configuration
@code
"Problem": {
    "classname" : "QuarticFunctionWithNoise",
    "dimension_of_decision_space" : 30
}
@endcode
.
*/
    void setup(const Configuration& config, const PrototypeManager& pm) override;

    void evaluation_function(std::shared_ptr<Individual> individual) const override;

private:

    std::shared_ptr<Prototype> clone_impl() const override
    {
        return std::make_shared<QuarticFunctionWithNoise>(*this);
    }
};

}

#endif
