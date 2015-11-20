#ifndef IMPROVED_PERCENTAGE_SCORING_FUNCTION_H
#define IMPROVED_PERCENTAGE_SCORING_FUNCTION_H

#include <memory>
#include "ScoringFunction.h"
#include "Configuration.h"
#include "PrototypeManager.h"
#include "Individual.h"

namespace adef {

/**
@brief ImprovedPercentageScoringFunction calculates the score by
the difference of inputs.

@par The configuration
ScoringFunction has no extra configurations.@n
See setup() for the details.
*/
class ImprovedPercentageScoringFunction : public ScoringFunction
{
public:

/// @copydoc ScoringFunction::Score
    using Score = typename ScoringFunction::Score;

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<ImprovedPercentageScoringFunction> clone() const
    {
        return std::dynamic_pointer_cast<ImprovedPercentageScoringFunction>(clone_impl());
    }
/**
@brief Set up the internal states.

If @em SomeThing is ImprovedPercentageScoringFunction,@n
its configuration should be
- JSON configuration
@code
"SomeThing": {
    "classname" : "ImprovedPercentageScoringFunction"
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
        return parent->fitness() - offspring->fitness();
    }

private:

    std::shared_ptr<Prototype> clone_impl() const override
    {
        return std::make_shared<ImprovedPercentageScoringFunction>(*this);
    }
};

}

#endif // IMPROVED_PERCENTAGE_SCORING_FUNCTION_H
