#ifndef SCORING_FUNCTION_H
#define SCORING_FUNCTION_H

#include <memory>
#include "Prototype.h"

namespace adef {

class Configuration;
class PrototypeManager;
class Individual;

/**
@brief ScoringFunction is the abstract base class of calculating score.

@par The configuration
ScoringFunction has no extra configurations.@n
See setup() for the details.
*/
class ScoringFunction : public Prototype
{
public:

/// The type of score
    using Score = double;

    virtual ~ScoringFunction() = default;

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<ScoringFunction> clone() const
    {
        return std::dynamic_pointer_cast<ScoringFunction>(clone_impl());
    }
/**
@brief Set up the internal states.

If @em SomeThing is @em Class which is derived from ScoringFunction,@n
its configuration should be
- JSON configuration
@code
"SomeThing": {
    "classname" : "Class"
}
@endcode
.
*/
    virtual void setup(const Configuration& config,
                       const PrototypeManager& pm) override = 0;
/**
@brief Calculate the score by the given function.
*/
    virtual Score calculate_score(std::shared_ptr<const Individual> parent,
                                  std::shared_ptr<const Individual> offspring) const = 0;

private:

    virtual std::shared_ptr<Prototype> clone_impl() const override = 0;
};

}

#endif // SCORING_FUNCTION_H
