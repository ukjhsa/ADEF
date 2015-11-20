#ifndef SUCCESS_SCORING_FUNCTION_H
#define SUCCESS_SCORING_FUNCTION_H

#include <memory>
#include "ScoringFunction.h"
#include "Configuration.h"
#include "PrototypeManager.h"
#include "Individual.h"

namespace adef {

/**
@brief SuccessScoringFunction calculates the score by
the comparison of inputs.

@par The configuration
ScoringFunction has no extra configurations.@n
See setup() for the details.
*/
class SuccessScoringFunction : public ScoringFunction
{
public:

/// @copydoc ScoringFunction::Score
    using Score = typename ScoringFunction::Score;

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<SuccessScoringFunction> clone() const
    {
        return std::dynamic_pointer_cast<SuccessScoringFunction>(clone_impl());
    }
/**
@brief Set up the internal states.

If @em SomeThing is SuccessScoringFunction,@n
its configuration should be
- JSON configuration
@code
"SomeThing": {
    "classname" : "SuccessScoringFunction"
}
@endcode
.
*/
    void setup(const Configuration& config, const PrototypeManager& pm) override
    {
    }

    Score calculate_score(std::shared_ptr<const Individual> parent,
                          std::shared_ptr<const Individual> offspring) const override
    {
        if (offspring->fitness() < parent->fitness()) {
            return 1;
        }
        else {
            return 0;
        }
    }

private:

    std::shared_ptr<Prototype> clone_impl() const override
    {
        return std::make_shared<SuccessScoringFunction>(*this);
    }
};

}

#endif // SUCCESS_SCORING_FUNCTION_H
